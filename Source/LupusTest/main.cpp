#include <cstdlib>
#include "../LupusCore/String.h"
#include "../LupusCore/Stream.h"
#include "../LupusCore/IPAddress.h"
#include "../LupusCore/IPEndPoint.h"
#include "../LupusCore/Version.h"
#include "../LupusCore/Uri.h"
#include "../LupusCore/Encoding.h"
#include "../LupusCore/HttpListenerRequest.h"

using namespace std;
using namespace Lupus;
using namespace Lupus::Text;
using namespace Lupus::Net;

const String testRequest1 = "GET /tutorials/other/top-20-mysql-best-practices/ HTTP/1.1\r\n"
"Host: net.tutsplus.com\r\n"
"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.5) Gecko/20091102 Firefox/3.5.5 (.NET CLR 3.5.30729)\r\n"
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
"Accept-Language: en-us,en;q=0.5\r\n"
"Accept-Encoding: gzip,deflate\r\n"
"Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n"
"Keep-Alive: 300\r\n"
"Connection: keep-alive\r\n"
"Cookie: PHPSESSID=r2t5uvjq435r4q7ib3vtdjq120\r\n"
"Pragma: no-cache\r\n"
"Cache-Control: no-cache\r\n\r\n";

int main(int argc, char** argv)
{
    auto request = shared_ptr<HttpListenerRequest>(new HttpListenerRequest(Encoding::ASCII()->GetBytes(testRequest1), nullptr, nullptr));

    wprintf(request->RawHeader().Data());
    wprintf((L"HTTP/" + request->ProtocolVersion()->ToString() + L'\n').Data());
    wprintf((request->Url()->ToString() + L'\n').Data());
    getchar();

    return EXIT_SUCCESS;
}