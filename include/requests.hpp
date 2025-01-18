#pragma once

#include <memory>


enum class HttpMethod {
    OPTIONS,
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    TRACE,
    extensionmethod 
};

class RequestHandler {
public:
    static RequestHandler * getHandler();
    static void clearHandler();
    
private:
    RequestHandler();
    ~RequestHandler();

    static RequestHandler * instance;
};


class Request {
public:
    ~Request ();
    static std::unique_ptr<Request> create();
private:
    Request ();

    HttpMethod method; 
};
