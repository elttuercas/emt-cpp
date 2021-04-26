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

#include "RedirectException.h"

RedirectException::RedirectException(
        const int &errorLine,
        const drogon::HttpStatusCode &httpStatusCode,
        std::map<std::string, std::string> &&errorDetails
) noexcept: m_iErrorLine(errorLine), m_httpStatusCode(httpStatusCode), m_rgErrorDetails(errorDetails)
{
}

RedirectException::RedirectException(
        const int &errorLine,
        const drogon::HttpStatusCode &httpStatusCode
) noexcept: m_iErrorLine(errorLine), m_httpStatusCode(httpStatusCode),
            m_rgErrorDetails(std::move(std::map<std::string, std::string>()))
{
}

int RedirectException::getErrorLine() const
{
    return m_iErrorLine;
}

drogon::HttpStatusCode RedirectException::getHttpStatusCode() const
{
    return m_httpStatusCode;
}

std::map<std::string, std::string> &&RedirectException::getErrorDetails()
{
    return std::move(m_rgErrorDetails);
}
