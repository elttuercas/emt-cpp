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

#include <drogon/plugins/Plugin.h>
#include <drogon/HttpAppFramework.h>

/**
 * Class GlobalTmplBootstrap
 *
 * This class
 *
 * @author Carlos Amores
 */
class GlobalTmplBootstrap : public drogon::Plugin<GlobalTmplBootstrap>
{
public:
    GlobalTmplBootstrap() = default;
    /**
     * Method is called by the framework to initialise and start the plugin.
     * @param config
     */
    void initAndStart(const Json::Value &config) override;
    /**
     * Method is called by the framework to shutdown the plugin.
     */
    void shutdown() override;
    /**
     * Create an HTTP view response similar to Drogon's base method except this method is intended to be used with
     * views which implement the global layout by already loading the template parameters used by the global layout.
     *
     * @param viewName
     * @param data
     * @param viewTitle
     * @return
     */
    drogon::HttpResponsePtr
    newHttpViewResponse(const std::string &viewName, const std::string &viewTitle, drogon::HttpViewData data);

    drogon::HttpResponsePtr newHttpViewResponse(const std::string &viewName, const std::string &viewTitle);
};
