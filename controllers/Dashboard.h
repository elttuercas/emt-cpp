#pragma once

#include <drogon/HttpController.h>
#include <cmath>

using namespace drogon;

/**
 * Root path controller. Displays recently hosted events by default. Handles pagination of the recently hosted events table
 * when necessary.
 *
 * @author Carlos Amores
 */
class Dashboard : public drogon::HttpController<Dashboard>
{
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(Dashboard::get, "/dashboard", Get);
        ADD_METHOD_TO(Dashboard::getPaginated, "/dashboard/{1:page}/", Get);
    METHOD_LIST_END

    void get(const drogon::HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback);
    void getPaginated(const drogon::HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback,
                      int page);
};
