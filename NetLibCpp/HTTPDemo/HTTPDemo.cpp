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

int main()
{
	// TODO: 在此添加控件通知处理程序代码
	CNetHttp http;
	http.CoInitialize();
	std::string host = "https://play.google.com";
	std::string url = "/store/apps/details";
	unsigned int port = 443;
	std::string querystring = "?id=com.tencent.mobileqq&hl=zh&gl=US";
	std::string body = "111";
	std::vector<std::string> headers;
	headers.push_back("Accept-Encoding: gzip, deflate");
	headers.push_back("Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, application/x-ms-application, application/x-ms-xbap, application/vnd.ms-xpsdocument, application/xaml+xml, */*");
	headers.push_back("Accept-Language: zh-cn");
	headers.push_back("User-Agent: Mozilla/5.0");
	headers.push_back("Connection: close");
	
	//输入文件
	std::string file = "C:\\Users\\taiji\\Desktop\\1.txt";
	std::ifstream in(file);
	//输出文件
	std::fstream fusername("C:\\Users\\taiji\\Desktop\\out.txt", std::ios::out | std::ios::app);
	std::string packetname;
	while (getline(in, packetname))
	{
		ByteBuffer response;
		querystring = "?id=" + packetname + "&hl=zh&gl=US";
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
			std::string packetname = value.substr(pos,0x20);
			fusername << packetname.c_str() << ":" <<"" <<std::endl;
		}
		else
		{
			pos = value.find(notfindtag);
			if (pos != -1)
			{
				//没有找到
				fusername << packetname.c_str() << ":" << std::endl;
			}
		}
	}
	fusername.close();
	http.UnInitialize();
}