/**
 *
 *  LoggedOutFilter.cc
 *
 */

#include "LoggedOutFilter.h"

using namespace drogon;

void LoggedOutFilter::doFilter(const drogon::HttpRequestPtr &req, drogon::FilterCallback &&fcb,
                               drogon::FilterChainCallback &&fccb)
{
    if (!req->session()->get<bool>("loggedIn"))
    {
        // The user is not logged in, let them through.
        fccb();
        return;
    }

    // User is logged in, take them to the dashboard view.
    drogon::HttpResponsePtr pResponse = drogon::HttpResponse::newRedirectionResponse("/dashboard/");
    fcb(pResponse);
}
