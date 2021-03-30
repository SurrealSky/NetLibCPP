#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CNetHttp_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CNetHttp_API __declspec(dllimport)
#endif

#include<string>
#include<vector>
#include"ByteBuffer.h"


enum HTTP_TYPE
{
	TYPE_POST,
	TYPE_GET
};

typedef struct _HttpStruct
{
	std::string host;
	std::string url;
	std::string querystring;
	unsigned int dwPort;
	std::vector<std::string> headers;
	std::string proxy;
	unsigned int proxyport;
	unsigned int retCode;
	ByteBuffer	response;
}HttpStruct,*PHttpStruct;

class DIPPEREXPORTS_CNetHttp_API CNetHttp
{
public:
	CNetHttp(void);
	~CNetHttp(void);
public:
	HttpStruct	http;
public:
	bool CoInitialize();
	void UnInitialize();
	bool perform(HTTP_TYPE,std::string,unsigned int,ByteBuffer*);
	bool perform_get(bool isProxy,bool isdefinePort);
	bool perform_post(bool isProxy, bool isdefinePort);
};

size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p);
