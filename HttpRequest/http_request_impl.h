#ifndef _HTTP_REQUEST_IMPL_H_
#define _HTTP_REQUEST_IMPL_H_

namespace http_request
{

struct SyncHttpRequestParam;
struct HttpRequestParam;
struct HttpRequestRet;
struct AsncHttpRequestParam;
enum HTTP_REQUEST_ERROR;
class  CHttpRequestImpl
{
public:
    static CHttpRequestImpl* GetInstance();
    bool Init();


    HTTP_REQUEST_ERROR SyncHttpRequest(SyncHttpRequestParam& param,
        HttpRequestRet& httpRequestRet);

    HTTP_REQUEST_ERROR CHttpRequestImpl::AsncHttpRequest(
        AsncHttpRequestParam& userParam);

private: 
    HTTP_REQUEST_ERROR InternetOpenAndRequest(HttpRequestParam& httpRequestParam);

    static CHttpRequestImpl* httpIns;
};

}

#endif