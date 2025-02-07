#include <memory>
#include <sys/socket.h>
#include <iostream>

#include "requests.hpp"
#include "defaults.h"
#include "enums.hpp"
#include "utils.hpp"


RequestHandler::RequestHandler() {};


RequestHandler::~RequestHandler() {};


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


void RequestHandler::validateRequest(const std::unique_ptr<Request> & request, LibWebDevError & error) {
    error = LibWebDevError.None;

    const HttpMethod methodsWithBody[] = {
        HttpMethod.PUT,
        HttpMethod.POST,
        HttpMethod.PATCH
    };

    // TODO tbh std::vector may be a better option than c-style array 
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

    std::cout << "headers: \n";
    for (auto const& param : this->headers) {
        std::cout << param.first << " -> " << param.second << '\n';
    }
    std::cout << "------ request description end -----" << '\n';
};


void Request::setMethod(const HttpMethod & method) {
    this->method = method;
};


void Request::addHeader(const std::string & name, const std::string & value) {
    this->headers[name] = value;
};


void setPreferedStandard(const HttpStandard & standard) {
    this->standard = standard;
};


void setRawBody(const std::string & raw) {
    this->body = RequestBody::fromRaw(raw);
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


RequestBody::RequestBody() {};

RequestBody::~RequestBody() {};


std::unique_ptr<RequestBody> RequestBody::fromRaw(const std::string & raw) {
    this->raw = raw;
};
