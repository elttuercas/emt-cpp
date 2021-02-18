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

#include <drogon/WebSocketController.h>

using namespace drogon;
namespace Log
{
    /**
     * Class Log::ViewSocket. This class handles websocket connections from the event log view page to update
     * the attendance table periodically whenever an user joins or leaves the event channel in Discord.
     *
     * @author Carlos Amores
     */
    class ViewSocket : public drogon::WebSocketController<ViewSocket>
    {
    public:
        /**
         * Function called when a new message is received from a client currently connected to the websocket.
         */
        virtual void handleNewMessage(const WebSocketConnectionPtr &,
                                      std::string &&,
                                      const WebSocketMessageType &) override;
        /**
         * Function called when a new connection is made from a client to the websocket path specified in this
         * controller.
         */
        virtual void handleNewConnection(const HttpRequestPtr &,
                                         const WebSocketConnectionPtr &) override;
        /**
         * Function called when a connection made to the path specified in this controller is closed.
         */
        virtual void handleConnectionClosed(const WebSocketConnectionPtr &) override;

        WS_PATH_LIST_BEGIN
            WS_PATH_ADD("/log/view/");
        WS_PATH_LIST_END
    };
}
