// HTTPDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"../NetLib/NetHttp.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\LibD\\NetLib.lib")
#else
#pragma comment(lib, "..\\Lib\\NetLib.lib")
#endif
#

int main()
{
	// TODO: 在此添加控件通知处理程序代码
	CNetHttp http;
	http.CoInitialize();
	std::string host = "https://play.google.com";
	std::string url = "/store/apps/details";
	unsigned int port = 443;
	std::string querystring = "?id=com.tencent.mobileqq2&hl=zh&gl=US";
	std::string body = "111";
	std::vector<std::string> headers;
	headers.push_back("Accept-Encoding: gzip, deflate");
	headers.push_back("Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, application/x-ms-application, application/x-ms-xbap, application/vnd.ms-xpsdocument, application/xaml+xml, */*");
	headers.push_back("Accept-Language: zh-cn");
	headers.push_back("User-Agent: Mozilla/5.0");
	headers.push_back("Connection: close");
	ByteBuffer response;
	http.perform_get(host, url, port, querystring, headers, &response);

	//查找结果
	std::string value;
	value.append((char*)response.contents(), response.size());
	const char* notfindtag = "class=\"uaxL4e\"";
	const char* findtag = "class=\"AHFaub\"";
	int pos = value.find(findtag);
	if (pos != -1)
	{
		//找到了
		printf("find!\n");
	}
	else
	{
		pos = value.find(notfindtag);
		if (pos != -1)
		{
			//没有找到
			printf("no find!\n");
		}
	}

	http.UnInitialize();
}