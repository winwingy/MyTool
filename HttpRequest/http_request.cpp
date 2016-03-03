#define HTTP_API_EXPORT
#include "http_request.h"
#include "http_request_impl.h"

namespace http_request
{
HttpRequest* HttpRequest::httpIns = NULL;

HttpRequest* HttpRequest::GetInstance()
{
    if (httpIns == NULL)
    {
        httpIns = new HttpRequest();
    }
    return httpIns;
}

bool HttpRequest::Init()
{
    return CHttpRequestImpl::GetInstance()->Init();
}


HTTP_REQUEST_ERROR HttpRequest::SyncHttpRequest(SyncHttpRequestParam& syncparam,
    HttpRequestRet& httpRequestRet)
{
    return CHttpRequestImpl::GetInstance()->SyncHttpRequest(
        syncparam, httpRequestRet);
}

HTTP_REQUEST_ERROR HttpRequest::AsncHttpRequest(
    AsncHttpRequestParam& requestParam)
{
    return CHttpRequestImpl::GetInstance()->AsncHttpRequest(requestParam);
}

}