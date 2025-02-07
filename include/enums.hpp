#pragma once


enum class LibWebDevError {
    None = 0,
    UrlUnsupportedProtocol = 1
};


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


enum class Protocol {
    HTTP,
    HTTPS,
    unsupported
};


enum class HttpStandard {
    HTTP_1_0,
    HTTP_1_1,
    HTTP_2_0
};
