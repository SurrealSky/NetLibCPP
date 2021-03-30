#include <iostream>
#include<fstream>
#include<map>
#include"common.h"


bool get_valide(CNetHttp& http, std::string url,std::vector<std::string>& headers)
{
	unsigned int port = 80;
	if (url.find("https") != -1)
	{
		port = 443;
	}
	ByteBuffer response;
	http.http.url = url;
	http.http.dwPort = port;
	http.http.headers = headers;
	http.perform_get(false,false,&response);
	if (true)
	{
		//找到了
		return true;
	}
	return false;
}

void host_valide(const char *filepath,const char *result)
{
	CNetHttp http;
	http.CoInitialize();
	std::vector<std::string> headers;
	headers.push_back("Accept-Encoding: gzip, deflate");
	headers.push_back("Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, application/x-ms-application, application/x-ms-xbap, application/vnd.ms-xpsdocument, application/xaml+xml, */*");
	headers.push_back("Accept-Language: zh-cn");
	headers.push_back("User-Agent: Mozilla/5.0");
	headers.push_back("Connection: close");

	//输入文件
	std::string file = filepath;
	std::ifstream in(file);
	//输出文件
	std::fstream fresult(result, std::ios::out | std::ios::app);
	std::string url;
	while (getline(in, url))
	{
		if (get_valide(http, url,headers))
		{
			fresult << url.c_str() << ":" << "ok" << std::endl;
		}
	}
	fresult.close();
	http.UnInitialize();
}