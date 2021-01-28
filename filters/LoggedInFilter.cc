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

#include "LoggedInFilter.h"

void LoggedInFilter::doFilter(const drogon::HttpRequestPtr &req, drogon::FilterCallback &&fcb,
                              drogon::FilterChainCallback &&fccb)
{
    if (req->session()->get<bool>("loggedIn"))
    {
        // The user is logged in, let them through.
        fccb();
        return;
    }

    // User is not logged in, take them to the public dashboard view.
    drogon::HttpResponsePtr pResponse = drogon::HttpResponse::newRedirectionResponse("/dashboard/");
    fcb(pResponse);
}
