#include <memory>
#include <sys/socket.h>
#include <iostream>

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


void Request::describe() {
    std::cout << "----- libwebdev request description -----\n";
    std::cout << "protocol: ";
    switch(this->protocol) {
    case Protocol::HTTP: 
        std::cout << "HTTP";
        break;
    case Protocol::HTTPS: 
        std::cout << "HTTPS";
        break;
    case Protocol::unsupported: 
        std::cout << "unsupported";
        break;
    }
    std::cout << '\n';

    std::cout << "method: ";
    switch(this->method) {
    case HttpMethod::OPTIONS: 
        std::cout << "OPTIONS";
        break;
    case HttpMethod::GET:
        std::cout << "GET";
        break;
    case HttpMethod::HEAD:
        std::cout << "HEAD";
        break;
    case HttpMethod::POST:
        std::cout << "POST";
        break;
    case HttpMethod::PUT:
        std::cout << "PUT";
        break;
    case HttpMethod::DELETE:
        std::cout << "DELETE";
        break;
    case HttpMethod::TRACE:
        std::cout << "TRACE";
        break;
    case HttpMethod::extensionmethod: 
        std::cout << "extensionmethod";
        break;
    }

    std::cout << '\n';

    std::cout << "query params: \n";
    for (auto const& param : this->queryParams) {
        std::cout << param.first << " -> " << param.second << '\n';
    }
    std::cout << "------ request description end -----" << '\n';
}


void Request::setMethod(const HttpMethod & method) {
    this->method = method;
}


std::unique_ptr<Request> Request::create(const std::string & url, LibWebDevError & error) {
    error = LibWebDevError::None;

    std::unique_ptr<Request> request = std::unique_ptr<Request>(new Request()); 

    request->setMethod(HttpMethod::GET);
    request->url = url;
    request->protocol = url_to_protocol(url);

    if (request->protocol == Protocol::unsupported) {
        error = LibWebDevError::UrlUnsupportedProtocol;
    }

    request->queryParams = url_to_query_params(url);

    return std::move(request);
};
