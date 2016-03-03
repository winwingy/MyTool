#include "http_request_impl.h"
#include <memory>

#include <Windows.h>
#include <WinInet.h>
#include <Shlwapi.h>

#include "StrAssist.h"
#include "http_request_implRef.h"
#include "HttpRequestRef.h"
#include "InstrusivePtr.h"
#include "../Log/Log.h"

#pragma comment(lib, "WinInet.lib")
#pragma comment(lib, "Shlwapi.lib")


namespace http_request
{
CHttpRequestImpl* CHttpRequestImpl::httpIns = NULL;


struct ProxyWinInetType
{
    PROXY_TYPE_PARAM ProxyType;
    int WinInetType;
};

const int ProxyTypeCount = 4;
const ProxyWinInetType ProxyTypeTOInterNetOpenType[ProxyTypeCount] = 
{
    {PT_DIRECT,  INTERNET_OPEN_TYPE_DIRECT},
    {PT_PRECONFIG,  INTERNET_OPEN_TYPE_PRECONFIG},
    {PT_PRECONFIG_WITH_NO_AUTOPROXY,  
    INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY},
    {PT_NAME_PROXY,  INTERNET_OPEN_TYPE_PROXY},    
};


int TranslateProxyTypeParamToWinInetType(PROXY_TYPE_PARAM proxyType)
{   
    for (int i = 0; i < ProxyTypeCount; ++i)
    {
        if (ProxyTypeTOInterNetOpenType[i].ProxyType == proxyType)
        {
            return ProxyTypeTOInterNetOpenType[i].WinInetType;
        }
    }
    return INTERNET_OPEN_TYPE_PRECONFIG;
}

BOOL ParseURLWorker( const char* pstrURL,
    LPURL_COMPONENTSA lpComponents, DWORD& dwServiceType,
    INTERNET_PORT& nPort, DWORD dwFlags )
{
    char* pstrCanonicalizedURL;
    char szCanonicalizedURL[INTERNET_MAX_URL_LENGTH];
    DWORD dwNeededLength = INTERNET_MAX_URL_LENGTH;
    BOOL bRetVal;
    BOOL bMustFree = FALSE;

    // Decoding is done in InternetCrackUrl/UrlUnescape 
    // so we don't need the ICU_DECODE flag here.

    DWORD dwCanonicalizeFlags = dwFlags &
        (ICU_NO_ENCODE | ICU_NO_META |
        ICU_ENCODE_SPACES_ONLY | ICU_BROWSER_MODE);

    DWORD dwCrackFlags = dwFlags & ICU_USERNAME;

    BOOL bUnescape = FALSE;

    if((dwFlags & (ICU_ESCAPE | ICU_DECODE)) && (lpComponents->dwUrlPathLength != 0) )
    {

        // We use only the ICU_ESCAPE flag for decoding even if
        // ICU_DECODE is passed.

        // Also, if ICU_BROWSER_MODE is passed we do the unescaping
        // manually because InternetCrackUrl doesn't do
        // Browser mode unescaping

        if (dwFlags & ICU_BROWSER_MODE)
            bUnescape = TRUE;
        else
            dwCrackFlags |= ICU_ESCAPE;
    }

    bRetVal = InternetCanonicalizeUrlA(pstrURL, szCanonicalizedURL,
        &dwNeededLength, dwCanonicalizeFlags);

    if (!bRetVal)
    {
        if (::GetLastError() != ERROR_INSUFFICIENT_BUFFER)
            return FALSE;

        pstrCanonicalizedURL = new char[dwNeededLength];
        if (pstrCanonicalizedURL == NULL)
            return FALSE;

        bMustFree = TRUE;
        bRetVal = InternetCanonicalizeUrlA(pstrURL, pstrCanonicalizedURL,
            &dwNeededLength, dwCanonicalizeFlags);
        if (!bRetVal)
        {
            delete [] pstrCanonicalizedURL;
            return FALSE;
        }
    }
    else
        pstrCanonicalizedURL = szCanonicalizedURL;

    // now that it's safely canonicalized, crack it

    bRetVal = InternetCrackUrlA(pstrCanonicalizedURL, 0,
        dwCrackFlags, lpComponents);

    if(bUnescape)
    {
        if(FAILED(UrlUnescapeA(lpComponents->lpszUrlPath,NULL,NULL,URL_UNESCAPE_INPLACE | URL_DONT_UNESCAPE_EXTRA_INFO)))
        {
            if (bMustFree)
                delete [] pstrCanonicalizedURL;

            return FALSE;
        }

        lpComponents->dwUrlPathLength = lstrlenA(lpComponents->lpszUrlPath);
    }

    if (bMustFree)
        delete [] pstrCanonicalizedURL;

    // convert to MFC-style service ID

    if (!bRetVal)
        dwServiceType = INTERNET_SCHEME_DEFAULT;
    else
    {
        nPort = lpComponents->nPort;
        dwServiceType = lpComponents->nScheme;
    }

    return bRetVal;
}

BOOL ParseURL( const char* pstrURL, DWORD& dwServiceType,
    string& strServer, string& strObject, INTERNET_PORT& nPort )
{
    dwServiceType = INTERNET_SCHEME_DEFAULT;

    if( pstrURL == NULL )
    {
        return FALSE;
    }

    URL_COMPONENTSA urlComponents;
    memset(&urlComponents, 0, sizeof(URL_COMPONENTS));
    urlComponents.dwStructSize = sizeof(URL_COMPONENTS);

    CHAR szServer[ INTERNET_MAX_URL_LENGTH ] = { NULL };
    urlComponents.dwHostNameLength = INTERNET_MAX_URL_LENGTH;
    urlComponents.lpszHostName = szServer;

    CHAR szUrl[ INTERNET_MAX_URL_LENGTH ] = { NULL };
    urlComponents.dwUrlPathLength = INTERNET_MAX_URL_LENGTH;
    urlComponents.lpszUrlPath = szUrl;

    BOOL bRetVal = ParseURLWorker( pstrURL, &urlComponents,
        dwServiceType, nPort, ICU_BROWSER_MODE );

    strServer = szServer;
    strObject = szUrl;

    return bRetVal;
}

CHttpRequestImpl* CHttpRequestImpl::GetInstance()
{
    if (httpIns == NULL)
    {
        httpIns = new CHttpRequestImpl();
    }
    return httpIns;
}

bool CHttpRequestImpl::Init()
{
    return true;
}


HTTP_REQUEST_ERROR CHttpRequestImpl::SyncHttpRequest(SyncHttpRequestParam& param,
    HttpRequestRet& httpRequestRet)
{
    HTTP_REQUEST_ERROR error = HTTP_REQUEST_ERROR_SUCCESS;
    do 
    {
        HttpRequestParam httpRequestParam;
        httpRequestParam.URL = param.URL;
        httpRequestParam.method = param.method;
        httpRequestParam.header = param.header;
        httpRequestParam.connectTimeOut = param.connectTimeOut;
        httpRequestParam.body = param.body;

        error = GetInstance()->
            InternetOpenAndRequest(httpRequestParam);       
        if (error != HTTP_REQUEST_ERROR_SUCCESS)
        {
            break;     
        }
        char szBuffer[1024*4] = {0};
        DWORD bufferLen = sizeof(szBuffer);
        BOOL query = HttpQueryInfoA(httpRequestParam.hRequest, 
            HTTP_QUERY_STATUS_CODE, (void*)szBuffer, &bufferLen, NULL);
        if (query)
        {            
            httpRequestRet.HTTPCode = StrToIntA(szBuffer);
        }
        if (httpRequestRet.HTTPCode < 200 || httpRequestRet.HTTPCode > 300)
        {
            break;
        }

        bufferLen = sizeof(szBuffer);
        query = HttpQueryInfoA(httpRequestParam.hRequest, 
            HTTP_QUERY_RAW_HEADERS_CRLF, (void*)szBuffer, &bufferLen, NULL);
        if (query)
        {
            httpRequestRet.Header = szBuffer;
        }


        DWORD dwReaded = 0;
        do 
        {
            dwReaded = 0;
            bufferLen = sizeof(szBuffer);            
            if(!::InternetReadFile(httpRequestParam.hRequest, (void*)szBuffer, 
                bufferLen, &dwReaded))
            {
                error = HTTP_REQUEST_ERROR_INTERNET_READ_FILE;
                break;
            }
            else
            {
                httpRequestRet.Body.append(szBuffer, dwReaded);
            }
        } while (dwReaded);


    } while (0);

    return error;
}

void AsyncCallbackUser(HttpRequestParam* requestParam)
{
    requestParam->httpRequestRet.userValue = requestParam->userValue;
    requestParam->userCallbackFun(requestParam->httpRequestRet);
}



void CALLBACK AyscHttpCallback(
    HINTERNET hInternet,
    DWORD_PTR dwContext,
    DWORD dwInternetStatus,
    LPVOID lpvStatusInformation,
    DWORD dwStatusInformationLength
    )
{
    switch(dwInternetStatus)
    {
    case INTERNET_STATUS_REQUEST_COMPLETE:
        {
            
            LPINTERNET_ASYNC_RESULT lpInternetAsyncResult = 
                (LPINTERNET_ASYNC_RESULT)lpvStatusInformation; 
            HttpRequestParam* requestParam(
                (HttpRequestParam*)dwContext); 
           
            if (lpInternetAsyncResult->dwError == ERROR_SUCCESS)
            {       
                char szBuffer[1024*4] = {0};
                DWORD bufferLen = sizeof(szBuffer);
                BOOL query = HttpQueryInfoA(hInternet, 
                    HTTP_QUERY_STATUS_CODE, (void*)szBuffer, &bufferLen, NULL);
                if (query)
                {            
                    requestParam->httpRequestRet.HTTPCode = StrToIntA(szBuffer);
                } 
                bufferLen = sizeof(szBuffer);
                query = HttpQueryInfoA(hInternet, 
                    HTTP_QUERY_RAW_HEADERS_CRLF, (void*)szBuffer, &bufferLen,
                    NULL);
                if (query)
                {
                    requestParam->httpRequestRet.Header = szBuffer;
                }

                DWORD dwReaded = 0;
                BOOL readRet = FALSE;
                do 
                {
                    dwReaded = 0;
                    bufferLen = sizeof(szBuffer); 
                    readRet = ::InternetReadFile(hInternet, (void*)szBuffer, 
                        bufferLen, &dwReaded);
                    if(!readRet)
                    {
                        if (GetLastError() == ERROR_IO_PENDING)
                        {
                            break;
                        }
                        else
                        {
                            requestParam->httpRequestRet.SDKError = 
                                HTTP_REQUEST_ERROR_INTERNET_READ_FILE;                         
                        }
                    }
                    else
                    {
                        requestParam->httpRequestRet.Body.append(szBuffer, 
                            dwReaded);
                    }
                } while (dwReaded);       
              
            }//end of if (lpInternetAsyncResult == ERROR_SUCCESS)  
            else
            {
                requestParam->httpRequestRet.SDKError =
                    HTTP_REQUEST_ERROR_HTTP_SEND_REQUESTEX;
            }
            AsyncCallbackUser(requestParam);         
            TRACE_W("%d", requestParam->GetCount());
            requestParam->Release();
            break;
        }
    default:
        {
            break;
        }
    }



}



HTTP_REQUEST_ERROR CHttpRequestImpl::AsncHttpRequest(
    AsncHttpRequestParam& userParam)
{
    HTTP_REQUEST_ERROR error = HTTP_REQUEST_ERROR_SUCCESS;

    HttpRequestParam* httpRequestParam(new HttpRequestParam);     
    httpRequestParam->URL = userParam.URL;
    httpRequestParam->method = userParam.method;
    httpRequestParam->header = userParam.header;
    httpRequestParam->connectTimeOut = userParam.connectTimeOut;
    httpRequestParam->body = userParam.body;  
    httpRequestParam->winInetCallback = (void*)AyscHttpCallback;
    httpRequestParam->dwContext = (DWORD)httpRequestParam;    
    httpRequestParam->isAsync = true;
    httpRequestParam->userCallbackFun = userParam.callbackFun;
    httpRequestParam->userValue = userParam.userValue;
    httpRequestParam->AddRef();
    TRACE_W("useCount=%d", httpRequestParam->GetCount());

    error = GetInstance()->
        InternetOpenAndRequest(*httpRequestParam);       
    if (error != HTTP_REQUEST_ERROR_SUCCESS)
    {
        httpRequestParam->Release();
    }      
    httpRequestParam->Release();
    return error;
}


HTTP_REQUEST_ERROR CHttpRequestImpl::InternetOpenAndRequest(
    HttpRequestParam& httpRequestParam)
{
    std::string proxyName;
    char* proxyNamePtr = NULL;
    std::string byPass;
    char* byPassPtr = NULL;
    switch(httpRequestParam.ProxyTypeParam)
    {
    case PT_DIRECT:
        {
            break;
        }
    case PT_PRECONFIG:
        {
            break;
        }
    case PT_NAME_PROXY:
        {
            proxyName = httpRequestParam.proxyIP + ":" +
                httpRequestParam.proxyPort;
            proxyNamePtr = const_cast<char*>(proxyName.c_str());           
            byPass = "<local>";
            byPassPtr = const_cast<char*>(byPass.c_str());
            break;
        }
    case PT_PRECONFIG_WITH_NO_AUTOPROXY:
        {
            break;
        }
    default:
        {
            break;
        }
    }

    HTTP_REQUEST_ERROR returnError = HTTP_REQUEST_ERROR_SUCCESS;

    do 
    {
        std::string byPass;
        DWORD ayscFlag;
        ayscFlag = httpRequestParam.isAsync?INTERNET_FLAG_ASYNC:0;
        httpRequestParam.hOpen = InternetOpenA(NULL,
            TranslateProxyTypeParamToWinInetType(httpRequestParam.ProxyTypeParam),
            proxyNamePtr, byPassPtr, ayscFlag);
        if (httpRequestParam.hOpen == NULL)
        {
            returnError = HTTP_REQUEST_ERROR_INTERNET_OPEN;
            break;
        }
        if (ayscFlag)
        {
            if(INTERNET_INVALID_STATUS_CALLBACK ==
                InternetSetStatusCallbackW(httpRequestParam.hOpen, 
                    (INTERNET_STATUS_CALLBACK)httpRequestParam.winInetCallback))
            {
                returnError = HTTP_REQUEST_ERROR_INTERNET_SET_STATUS_CALLBACK;
                break;
            }
        }

        DWORD dwServiceType;
        string strServer;
        string strObject;
        INTERNET_PORT nPort;        
        if (!ParseURL(
            httpRequestParam.URL.c_str(), 
            dwServiceType, strServer, strObject, nPort))
        {
            returnError = HTTP_REQUEST_ERROR_PARSE_URL;
            break;
        }

        httpRequestParam.hConnect = InternetConnectA(httpRequestParam.hOpen, 
            strServer.c_str(), nPort, NULL, NULL, INTERNET_SERVICE_HTTP, NULL,  
            httpRequestParam.dwContext);
        if (!httpRequestParam.hConnect)
        {
            returnError = HTTP_REQUEST_ERROR_CONNECT;
            break;
        }
        if (httpRequestParam.ProxyTypeParam ==  PT_NAME_PROXY)
        {
            BOOL success(FALSE);
            success = ::InternetSetOptionA(httpRequestParam.hConnect, 
                INTERNET_OPTION_PROXY_USERNAME, 
                (LPVOID)httpRequestParam.proxyLoginName.c_str(), 
                httpRequestParam.proxyLoginName.length());
            if (success == FALSE)
            {
                returnError = HTTP_REQUEST_ERROR_PROXY_USERNAME;
                break;
            }
            success = ::InternetSetOptionA(httpRequestParam.hConnect, 
                INTERNET_OPTION_PROXY_PASSWORD, 
                (LPVOID)httpRequestParam.proxyPassword.c_str(),
                httpRequestParam.proxyPassword.length());
            if (success == FALSE)
            {
                returnError = HTTP_REQUEST_ERROR_PROXY_PASSWORD;
                break;
            }
        }

        int flags = INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_KEEP_CONNECTION |
            INTERNET_FLAG_RELOAD | 
            INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_KEEP_CONNECTION;

        if (!httpRequestParam.URL.compare(0, 5, "https"))
        {
            flags |= INTERNET_FLAG_SECURE |
                INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
                INTERNET_FLAG_IGNORE_CERT_DATE_INVALID |
                INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS;
        }

        InternetSetOptionA(httpRequestParam.hConnect, INTERNET_OPTION_CONNECT_TIMEOUT,
            (VOID*)(&httpRequestParam.connectTimeOut),
            sizeof(httpRequestParam.connectTimeOut));

        httpRequestParam.hRequest = HttpOpenRequestA(httpRequestParam.hConnect, 
            httpRequestParam.method.c_str(),
            strObject.c_str(), "HTTP/1.1", NULL, 
            NULL, flags, httpRequestParam.dwContext);
        if (!httpRequestParam.hRequest)
        {
            returnError = HTTP_REQUEST_ERROR_OPERN_REQUEST;
            break;
        }

        if (httpRequestParam.header.empty())
        {
            httpRequestParam.header = 
                "Content-Type: text/xml\r\npragma: no-cache\r\n";
        }
        if (!HttpAddRequestHeadersA(httpRequestParam.hRequest,
            httpRequestParam.header.c_str(), httpRequestParam.header.length(),
            HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE))
        {
            returnError = HTTP_REQUEST_ERROR_ADD_REQUEST_HEADERS;
            break;
        }
        
        int retryCnt = 0;

        INTERNET_BUFFERSA buffInternet = {0};
        if (httpRequestParam.requesstEx)
        {            
            buffInternet.dwStructSize = sizeof(INTERNET_BUFFERS);
            buffInternet.lpvBuffer = (LPVOID)httpRequestParam.body.c_str();
            buffInternet.dwBufferLength = httpRequestParam.body.size();
        }

        for (int i = 0; i < 3; ++i)
        {            
            BOOL send = FALSE;
            if (httpRequestParam.requesstEx)
            {
                send = HttpSendRequestExA(httpRequestParam.hRequest, &buffInternet, NULL,
                    NULL, (DWORD)(&httpRequestParam));
            }
            else
            {
                send = HttpSendRequestA(httpRequestParam.hRequest, NULL, NULL, 
                    (LPVOID)httpRequestParam.body.c_str(),
                    (DWORD)(httpRequestParam.body.size()));
            }

            if (!send)
            {
                DWORD lastError = GetLastError();
                if (lastError == ERROR_IO_PENDING)
                {
                    returnError = HTTP_REQUEST_ERROR_SUCCESS;
                    break;
                }
                else if (lastError == ERROR_INTERNET_INVALID_CA)
                {
                    DWORD dwFlags;
                    DWORD dwBufferLen = sizeof(dwFlags);
                    InternetQueryOptionW(httpRequestParam.hRequest,
                        INTERNET_OPTION_SECURITY_FLAGS, 
                        (VOID*)(&dwFlags), &dwBufferLen);
                    dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
                    InternetSetOptionW(httpRequestParam.hRequest, 
                        INTERNET_OPTION_SECURITY_FLAGS, 
                        (void*)&dwFlags, dwBufferLen);
                }
                else
                {
                    returnError = HTTP_REQUEST_ERROR_HTTP_SEND_REQUESTEX;
                    break;
                }
            }
            else
            {
                returnError = HTTP_REQUEST_ERROR_SUCCESS;                   
                break;
            }
        }// end  for (int i = 0; i < 3; ++i)        

    } while (0);
    return returnError;
}

}