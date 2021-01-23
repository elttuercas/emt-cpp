#include "Index.h"
void Index::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    drogon::HttpResponsePtr response = drogon::HttpResponse::newHttpViewResponse("./views/index.csp");
    callback(response);
}