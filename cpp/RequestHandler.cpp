#include <sys/socket.h>

#include "RequestHandler.hpp"
#include "defaults.h"


RequestHandler::RequestHandler() {

}



RequestHandler::~RequestHandler() {

}


RequestHandler * instance = nullptr;


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



