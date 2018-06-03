//
// Created by suson on 5/9/18.
//

#ifndef CHAT_CONFIG_H
#define CHAT_CONFIG_H


#include <string>

class Config {
public:
    const std::string layout_path = "../layout.glade";
    const std::string css_path = "../style.css";

    const std::string base_url = "http://localhost/college/server/public/";
    const std::string api_url = base_url + "api/";

    const std::string grant_type = "password";
    const std::string client_id = "2";
    const std::string client_secret = "mdSbxNwzCtZgCr57W9SzDT8F6wdzfb0PAFqIHxSb";

    const std::string auth_file = "auth.json";
};


#endif //CHAT_CONFIG_H
