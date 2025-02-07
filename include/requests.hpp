#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>

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
    void describe();
    static std::unique_ptr<Request> create(const std::string & url, LibWebDevError & error);

    void setMethod(const HttpMethod & method);
    void addHeader(const std::string & name, const std::string & value);
    void setPreferedStandard(const HttpStandard & standard);
    void setRawBody(const std::string & raw);

    std::string getRaw();

private:
    Request();

    HttpMethod method;
    Protocol protocol;
    HttpStandard standard;
    std::string url;
    std::map<std::string, std::string> queryParams = {};
    std::map<std::string, std::string> headers = {};
    std::unique_ptr<RequestBody> body = nullptr;
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
    void validateRequest(const std::unique_ptr<Request> & request, LibWebDevError & error);
};


class RequestBody {
public:
    ~RequestBody();
    static std::unique_ptr<RequestBody> fromRaw(const std::string & raw);

private:
    RequestBody();
    std::string raw;
}
