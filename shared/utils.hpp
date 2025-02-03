#pragma once

#include <string>
#include <algorithm>
#include <map>

#include "enums.hpp"


Protocol url_to_protocol(const std::string & url) {
    std::string urlLowerCase = url; 
    std::transform(urlLowerCase.begin(), urlLowerCase.end(), urlLowerCase.begin(), ::tolower);

    if (urlLowerCase.rfind(std::string("http"), 0)) {
        return Protocol::HTTP;
    }

    if (urlLowerCase.rfind(std::string("https"), 0)) {
        return Protocol::HTTPS;
    }

    return Protocol::unsupported;
};


std::map<std::string, std::string> url_to_query_params(const std::string & url) {
    std::map<std::string, std::string> output = {};

    const char first = '?';
    const char second = '&';
    const char splitter = '=';

    std::string value = "";
    std::string name = "";
    bool is_first = true;
    bool parsing_name = false;
    bool parsing_value = false;

    for(const char & c : url) {
        if (is_first && c == first) {
            is_first = false;
            parsing_name = true;
            parsing_value = false;

            if (name.length() > 0 && value.length() > 0) {
                output[name] = value;
            }

            name = "";
            value = "";

            continue;
        }

        if(!is_first && c == second) {
            parsing_name = true;
            parsing_value = false;

            if (name.length() > 0 && value.length() > 0) {
                output[name] = value;
            }

            name = "";
            value = "";

            continue;
        }

        if(parsing_name && c == splitter) {
            parsing_name = false;
            parsing_value = true;
            continue;
        }

        if(parsing_name) name += c;

        if(parsing_value) value += c;
    }

    if (name.length() > 0 && value.length() > 0) {
        output[name] = value;
    }

    return output;
}
