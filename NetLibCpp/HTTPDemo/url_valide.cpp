#include <iostream>
#include<fstream>
#include<map>
#include<vector>
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
	http.http.retCode = 0;//重置
	bool isSucc=http.perform_get(false,false);
	if (!isSucc) return false;
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
		xlnt::workbook wbsave;
		xlnt::worksheet wssave = wbsave.active_sheet();
		for (int i = 1,j=0; i < /*RowLength*/146; i++,j++)
		{
			//取出host
			std::string host = rows[i][3].value<std::string>();
			if (get_valide(http, host, headers))
			{
				wssave.cell(1, j).value(host.c_str());
			}
			//if (host.find("http://") != host.npos)
			//{
			//	host = host.substr(7, host.size() - 7);
			//}
			//else if (host.find("https://") != host.npos)
			//{
			//	host = host.substr(8, host.size() - 8);
			//}
			//bool isValide = false;
			////尝试拼接HTTP
			//std::string httphost = "http://" + host;
			//if (get_valide(http, httphost, headers))
			//{
			//	isValide = true;
			//}
			//else
			//{
			//	//尝试拼接HTTPS
			//	std::string httpshost = "https://" + host;
			//	if (get_valide(http, httpshost, headers))
			//	{
			//		isValide = true;
			//	}
			//}
			//if (isValide)
			//{
			//	//打开网站成功
			//	wssave.cell(1, i - 9).value(host.c_str());
			//	
			//}
		}
		wbsave.save("C:\\Users\\taiji\\Desktop\\2.xlsx");
	}
	http.UnInitialize();
}

void xlsx_fz_convert(const char* filepath, const char* result)
{
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
		xlnt::workbook wbbook;
		xlnt::worksheet wssheet = wbbook.active_sheet();
		wssheet.cell(1, 1).value("keywords");
		wssheet.cell(2, 1).value("alarmDefraudType");
		wssheet.cell(3, 1).value("convert");
		for (int i = 2; i < RowLength; i++)
		{
			//取出说明
			std::string keywords = rows[i][0].value<std::string>();
			std::string alarmDefraudType = rows[i][1].value<std::string>();
			//计算covert
			std::string convert = keywords;
			std::string strand = " and ";
			while (true) {
				std::string::size_type   pos(0);
				if ((pos = convert.find(strand.c_str())) != std::string::npos)
					convert.replace(pos, strand.size(), "AND");
				else   
					break;
			}
			//if (keywords.find(' ') != std::string::npos)
			//{
			//	//找到空格
			//	char* p;
			//	const char *d = " ";
			//	std::vector<std::string> strs;
			//	p = strtok((char*)(keywords.c_str()), d);
			//	while (p)
			//	{
			//		if (strcmp(p, "and") == 0)
			//		{
			//			strs.push_back("AND");
			//		}
			//			strs.push_back(p);
			//		}
			//		p = strtok(NULL, d);
			//	}
			//	//转换拼接
			//	for (int i = 0; i < strs.size(); i++)
			//	{
			//		convert += strs[i];
			//	}
			//}
			//else
			//{
			//	//没有空格
			//	convert = keywords;
			//}
			wssheet.cell(1, i).value(keywords.c_str());
			wssheet.cell(2, i).value(alarmDefraudType.c_str());
			wssheet.cell(3, i).value(convert.c_str());
		}
		wbbook.save("C:\\Users\\taiji\\Desktop\\2.xlsx");
	}
}