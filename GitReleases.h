//
// Created by Javier Alonso Silva on 22/08/2017.
//

#ifndef REPAIR_TOOL_GITRELEASES_H
#define REPAIR_TOOL_GITRELEASES_H
#include "rapidjson/document.h"

#include <windows.h>
#include <wininet.h>
#include <tchar.h>

#include <cstddef>
#include <ctime>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

namespace json = rapidjson;

class HInternet
{
  public:
    HInternet(const HINTERNET handle)
      : m_handle(handle)
    {
    }

    ~HInternet()
    {
        if (m_handle != nullptr)
            InternetCloseHandle(m_handle);
    }

    operator HINTERNET() const
    {
        return m_handle;
    }

  private:
    const HINTERNET m_handle;
};

DWORD query_release_information(std::string& response)
{
    static const TCHAR* Host = _T("api.github.com");
    static const TCHAR* Path = _T("/repos/Javinator9889/WinRepairTool/releases");

    response.clear();

    const HInternet session =
        InternetOpen(
            _T("appleseed"),
            INTERNET_OPEN_TYPE_DIRECT,
            nullptr,
            nullptr,
            0);
    if (!session)
        return GetLastError();

    const HInternet connection =
        InternetConnect(
            session,
            Host,
            INTERNET_DEFAULT_HTTPS_PORT,
            nullptr,
            nullptr,
            INTERNET_SERVICE_HTTP,
            0,
            0);
    if (!connection)
        return GetLastError();

    static const TCHAR* AcceptTypes[] = { _T("application/json"), nullptr };
    const HInternet request =
        HttpOpenRequest(
            connection,
            _T("GET"),
            Path,
            nullptr,
            nullptr,
            AcceptTypes,
            INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_UI | INTERNET_FLAG_RELOAD,
            0);
    if (!request)
        return GetLastError();

    if (!HttpSendRequest(request, nullptr, 0, nullptr, 0))
        return GetLastError();

    std::vector<char> buffer(4096);

    while (true)
    {
        DWORD bytes_read;
        if (!InternetReadFile(request, &buffer[0], buffer.size(), &bytes_read))
        {
            const DWORD last_error = GetLastError();
            if (last_error == ERROR_INSUFFICIENT_BUFFER)
                buffer.resize(buffer.size() * 2);
            else return last_error;
        }

        if (bytes_read > 0)
            response.append(&buffer[0], bytes_read);
        else return ERROR_SUCCESS;
    }
}

struct JSONMemberNotFound : public std::exception {};

const json::Value& get_member(const json::Value& parent, const json::Value::Ch* member)
{
    if (!parent.HasMember(member))
        throw JSONMemberNotFound();
    return parent[member];
}

const json::Value& get_index(const json::Value& parent, const std::size_t index)
{
    if (!parent.IsArray() || index >= parent.Size())
        throw JSONMemberNotFound();
    return parent[index];
}
#endif //REPAIR_TOOL_GITRELEASES_H
