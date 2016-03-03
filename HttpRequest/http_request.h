
#ifndef _HTTP_REQUEST_H_
#define _HTTP_REQUEST_H_
#include "HttpRequestRef.h"

#ifdef HTTP_API_EXPORT
#define HTTP_API __declspec(dllexport)
#else
#define HTTP_API __declspec(dllimport)
#endif

namespace http_request
{

class HTTP_API HttpRequest
{
public:
    static HttpRequest* GetInstance();
    bool Init();

    
    HTTP_REQUEST_ERROR SyncHttpRequest(SyncHttpRequestParam& syncparam,
        HttpRequestRet& httpRequestRet);

    HTTP_REQUEST_ERROR AsncHttpRequest(AsncHttpRequestParam& requestParam);
   
private: 
    static HttpRequest* httpIns;
};

}


#endif