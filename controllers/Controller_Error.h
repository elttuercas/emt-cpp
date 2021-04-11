/*
 * __/\\\\\\\\\\\\\\\__/\\\\____________/\\\\__/\\\\\\\\\\\\\\\_
 *  _\/\\\///////////__\/\\\\\\________/\\\\\\_\///////\\\/////__
 *   _\/\\\_____________\/\\\//\\\____/\\\//\\\_______\/\\\_______
 *    _\/\\\\\\\\\\\_____\/\\\\///\\\/\\\/_\/\\\_______\/\\\_______
 *     _\/\\\///////______\/\\\__\///\\\/___\/\\\_______\/\\\_______
 *      _\/\\\_____________\/\\\____\///_____\/\\\_______\/\\\_______
 *       _\/\\\_____________\/\\\_____________\/\\\_______\/\\\_______
 *        _\/\\\\\\\\\\\\\\\_\/\\\_____________\/\\\_______\/\\\_______
 *         _\///////////////__\///______________\///________\///________
 */

#pragma once

#include <drogon/HttpSimpleController.h>
#include <fstream>
#include "plugins/GlobalTmplBootstrap.h"

using namespace drogon;
namespace Controller
{
    /**
     * Class Controller::Error
     *
     * This class handles displaying an error page showing the relevant code lines as well as providing a link to the
     * github page for any people who wish to contribute to the project and fix the issue. In short it's a crappier
     * version of filp/whoops.
     * TODO: Make code output pretty.
     *
     * @author Carlos Amores
     * @see https://github.com/filp/whoops
     */
    class Error : public drogon::HttpSimpleController<Error>
    {
    public:
        void asyncHandleHttpRequest(const HttpRequestPtr &req,
                                    std::function<void(const HttpResponsePtr &)> &&callback) override;

        PATH_LIST_BEGIN
            PATH_ADD("/error/", HttpMethod::Get);
        PATH_LIST_END
    };
}
