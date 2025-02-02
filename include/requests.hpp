#pragma once

#include <memory>
#include <vector>
#include <string>

#include "enums.hpp"


class Response {
public:
    ~Response();
    static std::unique_ptr<Response> create();

private:
    Response();
    std::string raw;
};


class Request {
public:
    ~Request();
    static std::unique_ptr<Request> create(const std::string & url, LibWebDevError & error);
    void setMethod(HttpMethod method);
    void addHeader(const std::string & name, const std::string & value);

private:
    Request();

    HttpMethod method;
    Protocol protocol;
    std::string url;
    std::vector<std::pair<std::string, std::string>> queryParams = {};
    std::vector<std::pair<std::string, std::string>> headers = {};
};


class RequestHandler {
public:
    static RequestHandler * getHandler();
    static void clearHandler();

    std::unique_ptr<Response> send(const std::unique_ptr<Request> & request);
    
private:
    RequestHandler();
    ~RequestHandler();

    static RequestHandler * instance;
};

