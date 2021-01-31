#include "LogoutController.h"

void LogoutController::asyncHandleHttpRequest(const drogon::HttpRequestPtr &req,
                                              std::function<void(const drogon::HttpResponsePtr &)> &&callback)
{
    req->session()->clear();
    callback(drogon::HttpResponse::newRedirectionResponse("/dashboard/"));
}
