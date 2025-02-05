#include <stdio.h>
#include "webdev/requests.hpp"


int main(void) {
    printf("starting\n");

    RequestHandler * handler = RequestHandler::getHandler();

    LibWebDevError err;
    auto request = Request::create("http://hekciu.xyz?param1=value1&param2=value2", err);

    request->describe();

    RequestHandler::clearHandler();
}
