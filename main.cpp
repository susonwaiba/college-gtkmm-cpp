#include <iostream>
#include <gtkmm.h>
#include <cpr/cpr.h>
#include <json.hpp>
#include <fstream>
#include "include/Config.h"
#include "windows/Login.h"
#include "windows/Home.h"

int main(int argc, char **argv) {
    Config config;

    auto appRef = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    auto builderRef = Gtk::Builder::create();

    try {
        builderRef->add_from_file(config.layout_path);
    } catch (const Glib::FileError &ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    } catch (const Glib::MarkupError &ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    } catch (const Gtk::BuilderError &ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }

    std::ifstream file;
    file.open(config.auth_file, std::ios::binary);
    file.seekg(0, std::ios::end);
    int fileLength = file.tellg();

    if (fileLength == 0) {
        Login login;
        login.init(appRef, builderRef);
        login.show_window();
    } else {
        file.seekg(0, std::ios::beg);
        nlohmann::json json;
        file >> json;
        std::string token = json["access_token"];
        auto response = cpr::Get(
                cpr::Url{config.api_url + "profile"},
                cpr::Header{{"Authorization", "Bearer " + token}}
        );
        auto json2 = nlohmann::json::parse(response.text);
        switch (response.status_code) {
            case 200: {
                int current_user_id = json2["id"];
                std::string current_user_name = json2["name"];
                Home home(token, current_user_id, current_user_name);
                home.init(appRef, builderRef);
                home.show_window();
                break;
            }
            default: {
                std::ofstream authFile;
                authFile.open(config.auth_file);
                authFile << "";
                authFile.close();
                system("./Chat &");
            }
        }

    }

    file.close();
    return 0;
}