#include "Dashboard.h"

void Dashboard::get(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback)
{
    // Sample vector of events to be displayed.
    std::vector<std::map<std::string, std::string>> rgEvents = {
            {
                    {"id", "1"},
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
                    {"id", "3"},
                    {"host", "DonutKnight"},
                    {"name", "[SMILE] Apex Slave"},
                    {"platform", "Discord"},
                    {"rate", "0.0028 REP/s"},
                    {"startTime", "2019-05-24 22:05 CET"}
            }
    };

    // Keep a maximum of 25 events in the vector.
    if (rgEvents.size() > 25)
    {
        rgEvents.resize(25);
    }

    // Data object to be fed to the view.
    drogon::HttpViewData data;
    data.insert("events", rgEvents);

    drogon::HttpResponsePtr pResponse = drogon::HttpResponse::newHttpViewResponse("./views/dashboard.csp", data);
    callback(pResponse);
}

void Dashboard::getPaginated(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback,
                             int page)
{
    // Sample vector of events to be displayed.
    std::vector<std::map<std::string, std::string>> rgEvents = {
            {
                    {"id", "1"},
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
                    {"id", "3"},
                    {"host", "DonutKnight"},
                    {"name", "[SMILE] Apex Slave"},
                    {"platform", "Discord"},
                    {"rate", "0.0028 REP/s"},
                    {"startTime", "2019-05-24 22:05 CET"}
            }
    };

    if (page < 1)
    {
        /*
         * Assuming that only 25 events are shown per page (as that seems reasonable) multiply the page counter
         * minus one by 25 and thus slice them off.
         */
        page = 1;
    }

    const int iEventsToSlice = (page - 1) * 25;
    if (rgEvents.size() < iEventsToSlice)
    {
        /*
         * Check if there are enough events to display something in the requested page. If there aren't, redirect
         * to the last possible page.
         */
        const int               iLastPage = static_cast<int>(std::ceil(rgEvents.size() / 25)) ?: 1;
        drogon::HttpResponsePtr pResponse = drogon::HttpResponse::newRedirectionResponse(
                "/dashboard/" + std::to_string(iLastPage) + '/'
        );
        callback(pResponse);
        return;
    }

    std::vector<decltype(rgEvents)::value_type>(rgEvents.begin() + iEventsToSlice, rgEvents.end()).swap(rgEvents);

    // From this point forth, the process is the same as when displaying the first 25 events by default.
    if (rgEvents.size() > 25)
    {
        rgEvents.resize(25);
    }

    drogon::HttpViewData data;
    data.insert("events", rgEvents);

    drogon::HttpResponsePtr pResponse = drogon::HttpResponse::newHttpViewResponse("./views/dashboard.csp", data);
    callback(pResponse);
}
