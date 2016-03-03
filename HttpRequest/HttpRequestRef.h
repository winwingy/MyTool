#ifndef _HTTP_REQUEST_REF_H_
#define _HTTP_REQUEST_REF_H_

#include <string>
#include <functional>

namespace http_request
{
enum PROXY_TYPE_PARAM
{
    PT_DIRECT,     //直连
    PT_PRECONFIG, //有IE代理先用IE代理,没有就直连
    PT_PRECONFIG_WITH_NO_AUTOPROXY,
    PT_NAME_PROXY,  //有名代理
};


enum HTTP_REQUEST_ERROR
{
    HTTP_REQUEST_ERROR_SUCCESS = 0,
    HTTP_REQUEST_ERROR_INTERNET_OPEN,
    HTTP_REQUEST_ERROR_INTERNET_SET_STATUS_CALLBACK,
    HTTP_REQUEST_ERROR_PARSE_URL,
    HTTP_REQUEST_ERROR_CONNECT,
    HTTP_REQUEST_ERROR_PROXY_USERNAME,
    HTTP_REQUEST_ERROR_PROXY_PASSWORD,
    HTTP_REQUEST_ERROR_OPERN_REQUEST,
    HTTP_REQUEST_ERROR_ADD_REQUEST_HEADERS,
    HTTP_REQUEST_ERROR_HTTP_SEND_REQUESTEX,
    HTTP_REQUEST_ERROR_INTERNET_READ_FILE,

};

struct HttpRequestRet
{
    HTTP_REQUEST_ERROR SDKError;
    int HTTPCode;   
    std::string Header;
    std::string Body;  

    HttpRequestRet()
        : SDKError(HTTP_REQUEST_ERROR_SUCCESS)
        , HTTPCode(-1)
    {

    }
};

struct AsyncHttpRequestRet
    :public HttpRequestRet
{
    void* userValue;

    AsyncHttpRequestRet()
        : userValue(NULL)
    {

    }


};


struct SyncHttpRequestParam
{
    std::string URL;
    std::string method;
    std::string header;
    std::string body;
    int connectTimeOut; //60*1000ms    

    SyncHttpRequestParam()
        : connectTimeOut(60*1000)
    {

    }
};

struct AsncHttpRequestParam
{
    std::string URL;
    std::string method;
    std::string header;
    std::string body;
    int connectTimeOut; //60*1000ms    
    void* userValue;    
    std::function<void (const AsyncHttpRequestRet&)> callbackFun;

    AsncHttpRequestParam()
        : connectTimeOut(60*1000)
        , userValue(NULL)
    {

    }
};


}

#endif