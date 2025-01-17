class RequestHandler {
public:
    static RequestHandler * getHandler();

    static void clearHandler();
private:
    RequestHandler();
    ~RequestHandler();

    static RequestHandler * instance;
};

