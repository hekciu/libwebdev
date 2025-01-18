#include <memory>
#include <sys/socket.h>

#include "requests.hpp"
#include "defaults.h"


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


Request::Request() {
    this->method = HttpMethod::GET;
};
Request::~Request() {};

std::unique_ptr<Request> Request::create() {
    return std::unique_ptr<Request>(new Request());  
};
