// HTTPDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<string>

extern void txt_host_valide(const char* filepath, const char* result);


int main()
{
	//const char* srcfile = "C:\\Users\\taiji\\Desktop\\DOMAIN_nb_1.txt";
	//const char* dstfile = "C:\\Users\\taiji\\Desktop\\DOMAIN_nb_1_result.txt";
	//txt_host_valide(srcfile,dstfile);

	const char* srcfile = "C:\\Users\\taiji\\Desktop\\1.txt";
	std::string dstfile = srcfile;
	dstfile += "result.txt";
	txt_host_valide(srcfile, dstfile.c_str());
}