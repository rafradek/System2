/**
 * -----------------------------------------------------
 * File        RequestNatives.cpp
 * Authors     David Ordnung
 * License     GPLv3
 * Web         http://dordnung.de
 * -----------------------------------------------------
 *
 * Copyright (C) 2013-2017 David Ordnung
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>
 */

#include "Request.h"
#include "HTTPRequest.h"
#include "FTPRequest.h"
#include "RequestHandler.h"


cell_t NativeRequest_SetResponseCallback(IPluginContext *pContext, const cell_t *params) {
    Request *request = Request::convertRequest<Request>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->responseCallback = pContext->GetFunctionById(params[2]);
    return 1;
}

cell_t NativeRequest_SetProgressCallback(IPluginContext *pContext, const cell_t *params) {
    Request *request = Request::convertRequest<Request>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->progressCallback = pContext->GetFunctionById(params[2]);
    return 1;
}

cell_t NativeRequest_SetURL(IPluginContext *pContext, const cell_t *params) {
    Request *request = Request::convertRequest<Request>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    char *url;
    pContext->LocalToString(params[2], &url);

    request->url = url;
    return 1;
}

cell_t NativeRequest_GetURL(IPluginContext *pContext, const cell_t *params) {
    Request *request = Request::convertRequest<Request>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    pContext->StringToLocalUTF8(params[2], params[3], request->url.c_str(), NULL);
    return 1;
}

cell_t NativeRequest_SetPort(IPluginContext *pContext, const cell_t *params) {
    Request *request = Request::convertRequest<Request>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->port = params[2];
    return 1;
}

cell_t NativeRequest_GetPort(IPluginContext *pContext, const cell_t *params) {
    Request *request = Request::convertRequest<Request>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    return request->port;
}

cell_t NativeRequest_GetAutoClean(IPluginContext *pContext, const cell_t *params) {
    Request *request = Request::convertRequest<Request>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    return request->autoClean;
}

cell_t NativeRequest_SetAutoClean(IPluginContext *pContext, const cell_t *params) {
    Request *request = Request::convertRequest<Request>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->autoClean = params[2];
    return 1;
}

cell_t NativeRequest_GetTimeout(IPluginContext *pContext, const cell_t *params) {
    Request *request = Request::convertRequest<Request>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    return request->timeout;
}

cell_t NativeRequest_SetTimeout(IPluginContext *pContext, const cell_t *params) {
    Request *request = Request::convertRequest<Request>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->timeout = params[2];
    return 1;
}

cell_t NativeRequest_GetAnyData(IPluginContext *pContext, const cell_t *params) {
    Request *request = Request::convertRequest<Request>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    return request->any;
}

cell_t NativeRequest_SetAnyData(IPluginContext *pContext, const cell_t *params) {
    Request *request = Request::convertRequest<Request>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->any = params[2];
    return 1;
}


cell_t NativeHTTPRequest_HTTPRequest(IPluginContext *pContext, const cell_t *params) {
    char *url;
    pContext->LocalToString(params[2], &url);

    HTTPRequest *request = new HTTPRequest(url, pContext->GetFunctionById(params[3]));
    if (!request) {
        return BAD_HANDLE;
    }

    return handlesys->CreateHandle(requestHandleType,
                                   request,
                                   pContext->GetIdentity(),
                                   myself->GetIdentity(),
                                   NULL);
}

cell_t NativeHTTPRequest_SetData(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    char *data;
    pContext->LocalToString(params[2], &data);

    request->data = data;
    return 1;
}

cell_t NativeHTTPRequest_GetData(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    pContext->StringToLocalUTF8(params[2], params[3], request->data.c_str(), NULL);
    return 1;
}

cell_t NativeHTTPRequest_SetOutputFile(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    char *outputFile;
    pContext->LocalToString(params[2], &outputFile);

    request->outputFile = outputFile;
    return 1;
}

cell_t NativeHTTPRequest_GetOutputFile(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    pContext->StringToLocalUTF8(params[2], params[3], request->outputFile.c_str(), NULL);
    return 1;
}

cell_t NativeHTTPRequest_SetHeader(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    char *header;
    char *value;
    pContext->LocalToString(params[2], &header);
    pContext->LocalToString(params[3], &value);

    request->headers[header] = value;
    return 1;
}

cell_t NativeHTTPRequest_GetHeader(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    char *header;
    pContext->LocalToString(params[2], &header);

    if (request->headers.find(header) == request->headers.end()) {
        return false;
    }

    pContext->StringToLocalUTF8(params[3], params[4], request->headers[header].c_str(), NULL);
    return 1;
}

cell_t NativeHTTPRequest_GetHeadersCount(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    return request->headers.size();
}

cell_t NativeHTTPRequest_GetHeadersArray(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    cell_t *array;
    pContext->LocalToPhysAddr(params[2], &array);

    cell_t index = 0;
    std::map<std::string, std::string>::iterator it;
    for (it = request->headers.begin(); it != request->headers.end() && index < params[3]; it++) {
        pContext->StringToLocalUTF8(array[index], params[4], it->first.c_str(), NULL);
        index++;
    }

    return 1;
}

cell_t NativeHTTPRequest_SetBasicAuthentication(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    char *username;
    char *password;
    pContext->LocalToString(params[2], &username);
    pContext->LocalToString(params[3], &password);

    request->username = username;
    request->password = password;
    return 1;
}

cell_t NativeHTTPRequest_GET(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->Get(params[1], pContext->GetIdentity());
    return 1;
}

cell_t NativeHTTPRequest_POST(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->Post(params[1], pContext->GetIdentity());
    return 1;
}

cell_t NativeHTTPRequest_PUT(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->Put(params[1], pContext->GetIdentity());
    return 1;
}

cell_t NativeHTTPRequest_PATCH(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->Patch(params[1], pContext->GetIdentity());
    return 1;
}

cell_t NativeHTTPRequest_DELETE(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->Delete(params[1], pContext->GetIdentity());
    return 1;
}

cell_t NativeHTTPRequest_HEAD(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->Head(params[1], pContext->GetIdentity());
    return 1;
}

cell_t NativeHTTPRequest_GetFollowRedirects(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    return request->followRedirects;
}

cell_t NativeHTTPRequest_SetFollowRedirects(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->followRedirects = params[2];
    return 1;
}

cell_t NativeHTTPRequest_GetAutoReferer(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    return request->autoReferer;
}

cell_t NativeHTTPRequest_SetAutoReferer(IPluginContext *pContext, const cell_t *params) {
    HTTPRequest *request = Request::convertRequest<HTTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->autoReferer = params[2];
    return 1;
}


cell_t NativeFTPRequest_FTPRequest(IPluginContext *pContext, const cell_t *params) {
    char *url;
    pContext->LocalToString(params[2], &url);

    FTPRequest *request = new FTPRequest(url, pContext->GetFunctionById(params[3]));
    if (!request) {
        return BAD_HANDLE;
    }

    return handlesys->CreateHandle(requestHandleType,
                                   request,
                                   pContext->GetIdentity(),
                                   myself->GetIdentity(),
                                   NULL);
}

cell_t NativeFTPRequest_SetAuthentication(IPluginContext *pContext, const cell_t *params) {
    FTPRequest *request = Request::convertRequest<FTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    char *username;
    char *password;
    pContext->LocalToString(params[2], &username);
    pContext->LocalToString(params[3], &password);

    request->username = username;
    request->password = password;
    return 1;
}

cell_t NativeFTPRequest_Download(IPluginContext *pContext, const cell_t *params) {
    FTPRequest *request = Request::convertRequest<FTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    char *outputFile;
    pContext->LocalToString(params[2], &outputFile);

    request->file = outputFile;
    request->Download(params[1], pContext->GetIdentity());
    return 1;
}

cell_t NativeFTPRequest_Upload(IPluginContext *pContext, const cell_t *params) {
    FTPRequest *request = Request::convertRequest<FTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    char *inputFile;
    pContext->LocalToString(params[2], &inputFile);

    request->file = inputFile;
    request->Upload(params[1], pContext->GetIdentity());
    return 1;
}

cell_t NativeFTPRequest_GetAppendToFile(IPluginContext *pContext, const cell_t *params) {
    FTPRequest *request = Request::convertRequest<FTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    return request->appendToFile;
}

cell_t NativeFTPRequest_SetAppendToFile(IPluginContext *pContext, const cell_t *params) {
    FTPRequest *request = Request::convertRequest<FTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->appendToFile = params[2];
    return 1;
}

cell_t NativeFTPRequest_GetCreateMissingDirs(IPluginContext *pContext, const cell_t *params) {
    FTPRequest *request = Request::convertRequest<FTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    return request->createMissingDirs;
}

cell_t NativeFTPRequest_SetCreateMissingDirs(IPluginContext *pContext, const cell_t *params) {
    FTPRequest *request = Request::convertRequest<FTPRequest>(params[1], pContext);
    if (request == NULL) {
        return 0;
    }

    request->createMissingDirs = params[2];
    return 1;
}