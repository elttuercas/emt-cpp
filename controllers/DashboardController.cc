/*
 * __/\\\\\\\\\\\\\\\__/\\\\____________/\\\\__/\\\\\\\\\\\\\\\_
 *  _\/\\\///////////__\/\\\\\\________/\\\\\\_\///////\\\/////__
 *   _\/\\\_____________\/\\\//\\\____/\\\//\\\_______\/\\\_______
 *    _\/\\\\\\\\\\\_____\/\\\\///\\\/\\\/_\/\\\_______\/\\\_______
 *     _\/\\\///////______\/\\\__\///\\\/___\/\\\_______\/\\\_______
 *	    _\/\\\_____________\/\\\____\///_____\/\\\_______\/\\\_______
 *	     _\/\\\_____________\/\\\_____________\/\\\_______\/\\\_______
 *        _\/\\\\\\\\\\\\\\\_\/\\\_____________\/\\\_______\/\\\_______
 *         _\///////////////__\///______________\///________\///________
 */

#include "DashboardController.h"

// Leaving this here as a placeholder until I write the code to read from the database.
std::vector<std::map<std::string, std::string>> rgSampleEvents = {};

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
    callback(drogon::HttpResponse::newHttpViewResponse("./views/dashboard.csp", data));
}

void DashboardController::getPaginated(const drogon::HttpRequestPtr &req,
                                       std::function<void(const drogon::HttpResponsePtr &)> &&callback,
                                       int page)
{
    if (page < 1)
    {
        /*
         * Assuming that only 25 events are shown per page (as that seems reasonable) multiply the page counter
         * minus one by 25 and then slice them off.
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
        const int iLastPage = static_cast<int>(std::ceil(rgSampleEvents.size() / 25)) ?: 1;
        callback(drogon::HttpResponse::newRedirectionResponse("/dashboard/" + std::to_string(iLastPage) + '/'));
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
    callback(drogon::HttpResponse::newHttpViewResponse("./views/dashboard.csp", data));
}
