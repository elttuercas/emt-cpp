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

#include "Log_ViewSocket.h"

using namespace Log;

void ViewSocket::handleNewMessage(
        const WebSocketConnectionPtr &wsConnPtr,
        std::string &&message,
        const WebSocketMessageType &type
)
{

}

void ViewSocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr)
{
}

void ViewSocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr)
{
    //write your application logic here
}
