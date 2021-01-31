#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

/**
 * Class LogoutController. Handles removal of all session data, thus logging the user out.
 *
 * @author Carlos Amores
 */
class LogoutController : public drogon::HttpSimpleController<LogoutController>
{
public:
    PATH_LIST_BEGIN
        PATH_ADD("/logout/", "LoggedInFilter", HttpMethod::Get);
    PATH_LIST_END

    void
    asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
};
