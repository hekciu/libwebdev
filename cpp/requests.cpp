#include <memory>
#include <sys/socket.h>

#include "requests.hpp"
#include "defaults.h"
#include "enums.hpp"
#include "utils.hpp"


RequestHandler::RequestHandler() {}


RequestHandler::~RequestHandler() {}


RequestHandler * RequestHandler::instance = nullptr;


RequestHandler * RequestHandler::getHandler() {
    if (RequestHandler::instance == nullptr) {
        RequestHandler::instance = new RequestHandler();
    }

    return RequestHandler::instance;
}


void RequestHandler::clearHandler() {
    if (RequestHandler::instance != nullptr) {
        delete RequestHandler::instance; 
    }
}


Request::Request() {};
Request::~Request() {};


std::unique_ptr<Request> Request::create(const std::string & url, LibWebDevError & error) {
    error = LibWebDevError::None;

    std::unique_ptr<Request> request = std::unique_ptr<Request>(new Request()); 

    request->setMethod(HttpMethod::GET);
    request->url = url;
    request->protocol = url_to_protocol(url);

    if (request->protocol == Protocol::unsupported) {
        error = LibWebDevError::UrlUnsupportedProtocol;
        return nullptr;
    }


    return std::move(request);
};
