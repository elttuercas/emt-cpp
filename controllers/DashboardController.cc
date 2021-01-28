/*
 * __/\\\\\\\\\\\\\\\__/\\\\____________/\\\\__/\\\\\\\\\\\\\\\_
 *  _\/\\\///////////__\/\\\\\\________/\\\\\\_\///////\\\/////__
 *   _\/\\\_____________\/\\\//\\\____/\\\//\\\_______\/\\\_______
 *    _\/\\\\\\\\\\\_____\/\\\\///\\\/\\\/_\/\\\_______\/\\\_______
 *     _\/\\\///////______\/\\\__\///\\\/___\/\\\_______\/\\\_______
 *	_\/\\\_____________\/\\\____\///_____\/\\\_______\/\\\_______
 *	 _\/\\\_____________\/\\\_____________\/\\\_______\/\\\_______
 *        _\/\\\\\\\\\\\\\\\_\/\\\_____________\/\\\_______\/\\\_______
 *         _\///////////////__\///______________\///________\///________
 */

#include "DashboardController.h"

std::vector<std::map<std::string, std::string>> rgSampleEvents = {
        {
                {"id", "3"},
                {"host", "Silent"},
                {"name", "[L2] Rust Wipe"},
                {"platform", "Discord"},
                {"rate", "0.0028 REP/s"},
                {"startTime", "2021-01-25 23:05 CET"}
        },
        {
                {"id", "2"},
                {"host", "Eltu"},
                {"name", "[DevOps] Test Event"},
                {"platform", "Discord"},
                {"rate", "0.0028 REP/s"},
                {"startTime", "2021-01-24 21:09 CET"}
        },
        {
                {"id", "1"},
                {"host", "DonutKnight"},
                {"name", "[SMILE] Apex Slave"},
                {"platform", "Discord"},
                {"rate", "0.0028 REP/s"},
                {"startTime", "2019-05-24 22:05 CET"}
        }
};

void DashboardController::get(const drogon::HttpRequestPtr &req,
                              std::function<void(const drogon::HttpResponsePtr &)> &&callback)
{
    // Keep a maximum of 25 events in the vector.
    if (rgSampleEvents.size() > 25)
    {
        rgSampleEvents.resize(25);
    }

    // Data object to be fed to the view.
    drogon::HttpViewData data;
    data.insert("events", rgSampleEvents);
    data.insert("loggedIn", req->session()->get<bool>("loggedIn"));

    drogon::HttpResponsePtr pResponse = drogon::HttpResponse::newHttpViewResponse("./views/dashboard.csp", data);
    callback(pResponse);
}

void DashboardController::getPaginated(const drogon::HttpRequestPtr &req,
                                       std::function<void(const drogon::HttpResponsePtr &)> &&callback,
                                       int page)
{
    if (page < 1)
    {
        /*
         * Assuming that only 25 events are shown per page (as that seems reasonable) multiply the page counter
         * minus one by 25 and thus slice them off.
         */
        page = 1;
    }

    const int iEventsToSlice = (page - 1) * 25;
    if (rgSampleEvents.size() < iEventsToSlice)
    {
        /*
         * Check if there are enough events to display something in the requested page. If there aren't, redirect
         * to the last possible page.
         */
        const int               iLastPage = static_cast<int>(std::ceil(rgSampleEvents.size() / 25)) ?: 1;
        drogon::HttpResponsePtr pResponse = drogon::HttpResponse::newRedirectionResponse(
                "/dashboard/" + std::to_string(iLastPage) + '/'
        );
        callback(pResponse);
        return;
    }

    std::vector<decltype(rgSampleEvents)::value_type>(rgSampleEvents.begin() + iEventsToSlice,
                                                      rgSampleEvents.end()).swap(rgSampleEvents);

    // From this point forth, the process is the same as when displaying the first 25 events by default.
    if (rgSampleEvents.size() > 25)
    {
        rgSampleEvents.resize(25);
    }

    drogon::HttpViewData data;
    data.insert("events", rgSampleEvents);
    data.insert("loggedIn", req->session()->get<bool>("loggedIn"));

    drogon::HttpResponsePtr pResponse = drogon::HttpResponse::newHttpViewResponse("./views/dashboard.csp", data);
    callback(pResponse);
}
