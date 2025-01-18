#include <stdio.h>
#include "webdev/requests.hpp"


int main(void) {
    printf("starting\n");

    RequestHandler * handler = RequestHandler::getHandler();

    std::unique_ptr<Request> request = Request::create();

    RequestHandler::clearHandler();
}
