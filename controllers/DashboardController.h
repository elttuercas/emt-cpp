#pragma once

#include <drogon/HttpController.h>
#include <cmath>

using namespace drogon;

/**
 * Class DashboardController. Displays recently hosted events by default. Handles pagination of the
 * recently hosted events table when necessary.
 *
 * @author Carlos Amores
 */
class DashboardController : public drogon::HttpController<DashboardController>
{
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(DashboardController::get, "/dashboard", Get);
        ADD_METHOD_TO(DashboardController::getPaginated, "/dashboard/{1:page}/", Get);
    METHOD_LIST_END

    /**
     * Handle a default get request without pagination parameters. Displays a table with the last 25 events
     * at most by default.
     *
     * @param request
     * @param callback
     */
    void get(const drogon::HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback);
    /**
     * Handle a get request with pagination data. Display the events corresponding to the requested page
     * to a maximum of 25 events.
     *
     * @param request
     * @param callback
     * @param page
     */
    void getPaginated(const drogon::HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback,
                      int page);
};
