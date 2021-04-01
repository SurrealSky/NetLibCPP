#include <iostream>
#include<fstream>
#include<map>
#include"common.h"
#include<xlnt\xlnt.hpp>

#ifdef _DEBUG
#pragma comment(lib, "Debug\\xlntd.lib")
#else
#pragma comment(lib, "Release\\xlnt.lib")
#endif


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
	http.perform_get(false,false);
	if (http.http.retCode == 200 || (http.http.retCode >= 300 && http.http.retCode < 400))
	{
		return true;
	}
	return false;
}

void txt_host_valide(const char *filepath,const char *result)
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
			fresult << url.c_str() << ":" <<http.http.retCode<< std::endl;
		}
	}
	fresult.close();
	http.UnInitialize();
}

void xlsx_host_valide(const char* filepath, const char* result)
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
	int err = 0;
	xlnt::workbook wb;
	wb.load(filepath);

	std::vector<std::string> names = wb.sheet_titles();
	for (int i = 0; i < names.size(); i++)
	{
		xlnt::worksheet ws = wb.sheet_by_title(names[i]);
		xlnt::range cols = ws.columns();
		xlnt::range rows = ws.rows();
		int ColLength = cols.length();
		int RowLength = rows.length();
		//std::cout << "test有效列数为: " << ColLength << std::endl;
		//std::cout << "test有效行数为: " << RowLength << std::endl;
		for (int i = 10; i < 15/*RowLength*/; i++)
		{
			//取出host
			std::string host = rows[i][1].value<std::string>();
			bool isValide = false;
			//尝试拼接HTTP
			std::string httphost = "http://" + host;
			if (get_valide(http, httphost, headers))
			{
				isValide = true;
			}
			else
			{
				//尝试拼接HTTPS
				std::string httpshost = "https://" + host;
				if (get_valide(http, httpshost, headers))
				{
					isValide = true;
				}
			}
			if (!isValide)
			{
				//打开网站失败
				ws.cell(3, i+1).value("open failed!");
			}
			else
			{
				ws.cell(3, i+1).value("open succ!");
			}
		}
	}
	wb.save("C:\\Users\\taiji\\Desktop\\3.xlsx");
	http.UnInitialize();
}