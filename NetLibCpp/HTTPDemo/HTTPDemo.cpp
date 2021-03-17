// HTTPDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<fstream>
#include"../NetLib/NetHttp.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\LibD\\NetLib.lib")
#else
#pragma comment(lib, "..\\Lib\\NetLib.lib")
#endif
#

bool test_google(CNetHttp& http, std::vector<std::string>& headers, std::string packetname, std::string& appname)
{
	std::string host = "https://play.google.com";
	std::string url = "/store/apps/details";
	unsigned int port = 443;

	ByteBuffer response;
	std::string querystring = "?id=" + packetname + "&hl=zh&gl=US";
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
		appname = value.substr(pos + 0x25, 0x50);
		pos = appname.find_first_of('<');
		appname = appname.substr(0, pos);
		return true;
	}
	appname = "";
	return false;
}

bool test_yingyongbao(CNetHttp& http, std::vector<std::string>& headers, std::string packetname, std::string& appname)
{
	std::string host = "https://a.app.qq.com";
	std::string url = "/o/simple.jsp";
	unsigned int port = 443;
	
	ByteBuffer response;
	std::string querystring = "?pkgname=" + packetname;
	http.perform_get(host, url, port, querystring, headers, &response);
	//查找结果
	std::string value;
	value.append((char*)response.contents(), response.size());
	const char* notfindtag = "http://a.app.qq.com/error_pages/noApp.jsp";
	const char* findtag = "itemprop=\"name\"";
	int pos = value.find(findtag);
	if (pos != -1)
	{
		//找到了
		appname = value.substr(pos + 25, 0x50);
		pos = appname.find_first_of('"');
		appname = appname.substr(0, pos);
		return true;
	}
	appname = "";
	return false;
}

bool test_xiaomi(CNetHttp& http,std::vector<std::string> &headers,std::string packetname,std::string &appname)
{
	std::string host = "https://app.mi.com";
	std::string url = "/details";
	unsigned int port = 443;

	ByteBuffer response;
	std::string querystring = "?id=" + packetname;
	http.perform_get(host, url, port, querystring, headers, &response);
	//查找结果
	std::string value;
	value.append((char*)response.contents(), response.size());
	const char* notfindtag = "The URL has moved <a href=";
	const char* findtag = "class=\"intro-titles\"";
	int pos = value.find(findtag);
	if (pos != -1)
	{
		//找到了
		appname = value.substr(pos + 50, 0x50);
		pos = appname.find_first_of('<');
		appname = appname.substr(0, pos);
		return true;
	}
	appname = "";
	return false;
}

void common_get()
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
	std::string file = "C:\\Users\\taiji\\Desktop\\query\\in\\39.txt";
	std::ifstream in(file);
	//输出文件
	std::fstream fusername1("C:\\Users\\taiji\\Desktop\\query\\out\\39.txt", std::ios::out | std::ios::app);
	std::fstream fusername2("C:\\Users\\taiji\\Desktop\\query\\out\\39unknow.txt", std::ios::out | std::ios::app);
	std::string packetname;
	std::string appname = "";
	while (getline(in, packetname))
	{
		//if (test_xiaomi(http, headers, packetname, appname))
		//{
		//	//先查询小米
		//	fusername1 << packetname.c_str() << ":" << appname.c_str() << std::endl;
		//}
		//else
		//{
		//	//再查询腾讯应用宝
		//	if (test_yingyongbao(http, headers, packetname, appname))
		//	{
		//		fusername1 << packetname.c_str() << ":" << appname.c_str() << std::endl;
		//	}else
		//		fusername2 << packetname.c_str()  << std::endl;
		//}

		//查询google
		if (test_google(http, headers, packetname, appname))
		{
			fusername1 << packetname.c_str() << ":" << appname.c_str() << std::endl;
		}
		else
		{
			fusername2 << packetname.c_str() << std::endl;
		}
	}
	fusername1.close();
	fusername2.close();
	http.UnInitialize();
}

int main()
{
	// TODO: 在此添加控件通知处理程序代码
	common_get();
}