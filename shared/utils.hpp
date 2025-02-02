#pragma once

#include <string>
#include <algorithm>

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

