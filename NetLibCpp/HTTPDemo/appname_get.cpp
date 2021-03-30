#include <iostream>
#include<fstream>
#include<map>
#include"common.h"


bool test_google(CNetHttp& http, std::vector<std::string>& headers, std::string packetname, std::string& appname)
{
	http.http.host= "https://play.google.com";
	http.http.url= "/store/apps/details";
	http.http.dwPort = 443;
	http.http.querystring= "?id=" + packetname + "&hl=zh&gl=US";
	http.http.headers = headers;
	http.http.proxy = "127.0.0.1";
	http.http.proxyport = 9999;
	http.perform_get(true,false);
	//查找结果
	std::string value;
	value.append((char*)http.http.response.contents(), http.http.response.size());
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
	ByteBuffer response;
	http.http.host = "https://a.app.qq.com";
	http.http.url = "/o/simple.jsp";
	http.http.dwPort = 443;
	http.http.querystring = "?pkgname=" + packetname;
	http.http.headers = headers;

	http.perform_get(false, false);
	//查找结果
	std::string value;
	value.append((char*)http.http.response.contents(), http.http.response.size());
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

bool test_xiaomi(CNetHttp& http, std::vector<std::string>& headers, std::string packetname, std::string& appname)
{
	ByteBuffer response;
	http.http.host = "https://app.mi.com";
	http.http.url = "/details";
	http.http.dwPort = 443;
	http.http.querystring = "?id=" + packetname;
	http.http.headers = headers;
	http.perform_get(false,false);
	//查找结果
	std::string value;
	value.append((char*)http.http.response.contents(), http.http.response.size());
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

std::map<std::string, std::string> allresult;
std::map<std::string, std::string> lbskey;
std::map<std::string, std::string> yjtzmkey;

void cls_repeated()
{
	//去重并读入到map


	//读取LBS应用字典
	std::string file_lbs = "C:\\Users\\taiji\\Desktop\\query\\in\\LBS.txt";
	std::ifstream in1(file_lbs);
	std::string line = "";
	while (getline(in1, line))
	{
		if (lbskey.find(line) == lbskey.end())
		{
			lbskey.insert(std::pair<std::string, std::string>(line, line));
		}
	}
	in1.close();
	//读取硬件特征码字典
	std::string file_yjtzm = "C:\\Users\\taiji\\Desktop\\query\\in\\yingjiantezhengma.txt";
	std::ifstream in2(file_yjtzm);
	line = "";
	while (getline(in2, line))
	{
		if (yjtzmkey.find(line) == yjtzmkey.end())
		{
			yjtzmkey.insert(std::pair<std::string, std::string>(line, line));
		}
	}
	in1.close();

	//输出文件
	std::fstream fusername1("C:\\Users\\taiji\\Desktop\\query\\out_result\\out_LBS.txt", std::ios::out | std::ios::app);
	std::fstream fusername2("C:\\Users\\taiji\\Desktop\\query\\out_result\\out_YJTZM.txt", std::ios::out | std::ios::app);

	std::string file = "C:\\Users\\taiji\\Desktop\\query\\out_result\\1.txt";
	std::ifstream in(file);
	std::string packetname = "";
	std::string appname = "";
	line = "";
	while (getline(in, line))
	{
		int pos = line.find_first_of(':');
		if (pos == -1) continue;
		packetname = line.substr(0, pos);
		appname = line.substr(pos + 1);

		if (allresult.find(packetname) == allresult.end())
		{
			//没找到
			allresult.insert(std::pair<std::string, std::string>(packetname, appname));
			if (lbskey.find(packetname) != lbskey.end())
			{
				fusername1 << packetname << ":" << appname << std::endl;
			}
			if (yjtzmkey.find(packetname) != yjtzmkey.end())
			{
				fusername2 << packetname << ":" << appname << std::endl;
			}
		}
	}
	in.close();

	fusername1.close();
	fusername2.close();
}