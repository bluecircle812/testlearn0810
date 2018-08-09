#pragma once
#include<string>
class HttpConnect
{
public:
	HttpConnect(void);
	~HttpConnect(void);
	std::string socketHttp(std::string host, std::string request);
	void postData(std::string host, std::string path, std::string post_content);
	CString getData(std::string host, std::string path, std::string get_content);
	char* UnicodeToUtf8(const wchar_t* unicode);
	std::string string_To_UTF8(char* str);  
	//const wchar_t *GetWC(const char *c);
};

