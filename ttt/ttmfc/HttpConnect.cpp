
#include "stdafx.h"
#include "HttpConnect.h"
#include <comdef.h>  // you will need this
#include <sstream>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

#ifdef WIN32
#pragma comment(lib,"ws2_32.lib")
#endif

HttpConnect::HttpConnect()
{
#ifdef WIN32
	//此处一定要初始化一下，否则gethostbyname返回一直为空
	WSADATA wsa = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsa);
#endif
}

string  UrlUTF8(char * str);
void GB2312ToUTF_8(string& pOut,char *pText, int pLen);
void Gb2312ToUnicode(WCHAR* pOut,char *gbBuffer);
void  UnicodeToUTF_8(char* pOut,WCHAR* pText);
void UTF8toANSI(CString &strUTF8);

//UTF8转ANSI
void UTF8toANSI(CString &strUTF8)
{
	//获取转换为多字节后需要的缓冲区大小，创建多字节缓冲区
	UINT nLen = MultiByteToWideChar(CP_UTF8,NULL,strUTF8,-1,NULL,NULL);
	WCHAR *wszBuffer = new WCHAR[nLen+1];
	nLen = MultiByteToWideChar(CP_UTF8,NULL,strUTF8,-1,wszBuffer,nLen);
	wszBuffer[nLen] = 0;

	nLen = WideCharToMultiByte(936,NULL,wszBuffer,-1,NULL,NULL,NULL,NULL);
	CHAR *szBuffer = new CHAR[nLen+1];
	nLen = WideCharToMultiByte(936,NULL,wszBuffer,-1,szBuffer,nLen,NULL,NULL);
	szBuffer[nLen] = 0;
	
	strUTF8 = szBuffer;
	//清理内存
	delete []szBuffer;
	delete []wszBuffer;
}

string  UrlUTF8(char * str)
{
    string tt;
    string dd;
    GB2312ToUTF_8(tt,str,strlen(str));
    int len=tt.length();
    for (int i=0;i<len;i++)
    {
        if(isalnum((BYTE)tt.at(i)) || tt.at(i) == '='||tt.at(i) == '&') //判断字符中是否有数组或者英文
        {
            char tempbuff[2]={0};
            sprintf_s(tempbuff,"%c",(BYTE)tt.at(i));
            dd.append(tempbuff);
        }
        else if (isspace((BYTE)tt.at(i)))
        {
            dd.append("+");
        }
        else
        {
            char tempbuff[4];
            sprintf_s(tempbuff,"%%%X%X",((BYTE)tt.at(i)) >>4,((BYTE)tt.at(i)) %16);
            dd.append(tempbuff);
        }

    }
    return dd;
}
void GB2312ToUTF_8(string& pOut,char *pText, int pLen)
{
    char buf[4];
    memset(buf,0,4);

    pOut.clear();

    int i = 0;
    while(i < pLen)
    {
        //如果是英文直接复制就可以
        if( pText[i] >= 0)
        {
            char asciistr[2]={0};
            asciistr[0] = (pText[i++]);
            pOut.append(asciistr);
        }
        else
        {
            WCHAR pbuffer;
            Gb2312ToUnicode(&pbuffer,pText+i);

            UnicodeToUTF_8(buf,&pbuffer);

            pOut.append(buf);

            i += 2;
        }
    }

    return;
}
void Gb2312ToUnicode(WCHAR* pOut,char *gbBuffer)
{
    ::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
    return;
}
void UTF_8ToUnicode(WCHAR* pOut,char *pText)
{
    char* uchar = (char *)pOut;

    uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
    uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);

    return;
}
void  UnicodeToUTF_8(char* pOut,WCHAR* pText)
{
    // 注意 WCHAR高低字的顺序,低字节在前，高字节在后
    char* pchar = (char *)pText;

    pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
    pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
    pOut[2] = (0x80 | (pchar[0] & 0x3F));

    return;
}

HttpConnect::~HttpConnect()
{

}
std::string HttpConnect::socketHttp(std::string host, std::string request)
{
	int sockfd;
	struct sockaddr_in address;
	struct hostent *server;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	address.sin_family = AF_INET;
	address.sin_port = htons(9012);
	server = gethostbyname(host.c_str());
	memcpy((char *)&address.sin_addr.s_addr,(char*)server->h_addr, server->h_length);

	if(-1 == connect(sockfd,(struct sockaddr *)&address,sizeof(address))){
		// DBG <<"connection error!"<<std::endl;
		return 0;
	}

	//const WCHAR* wc = L"Hello World" ;
	//_bstr_t b(wc);
	//const char* c = b;
	////USES_CONVERSION;  
	//////char* test1 = W2A(L"我是宽字节");//转化成默认  
	////wchar_t* test12 = A2W(request.c_str());  
	//CString cs;
	//cs=request.c_str();

	//const char* crequest;
	//// UnicodeToUtf8方法将Unicode编码转为UTF-8格式。
	//crequest = UnicodeToUtf8(cs);
	//char *cs = "GET /zadd?server=sdddfs阿道夫撒的 HTTP/1.0\r\nHost: 127.0.0.1\r\nUser-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\nConnection:close\r\n\r\n";
	//std::string ss=string_To_UTF8(cs);
	//DBG << request << std::endl;
#ifdef WIN32
	send(sockfd, request.c_str(),request.size(),0);
	//send(sockfd, ss.c_str(),request.size(),0);
#else
	write(sockfd,request.c_str(),request.size());
	//write(sockfd,ss.c_str(),request.size());

#endif
	//char buf[1024*1024] = {0};
	//char buf[1024 * 1024] = { 0 }; 
	char *buf = (char *)malloc(10 *10); 
	/* 其他代码 */ 
	//free(buf);

	int offset = 0;
	int rc;

#ifdef WIN32
	while(rc = recv(sockfd, buf+offset, 1,0))
#else
	while(rc = read(sockfd, buf+offset, 1024))
#endif
	{
		offset += rc;
	}

#ifdef WIN32
	closesocket(sockfd);
#else
	close(sockfd);
#endif
	//string as="a";
	//char *pp="abc";
	//char *ppp=(char*)malloc(20*20);
	//*ppp='abc';
	//int ppl = strlen(pp);
	//
	//int pppl=strlen(ppp);
	//int aaa=strlen(buf);
	std::string recStr=buf;
	//recStr.length();
	
	buf[offset] = 0;
	// DBG << buf << std::endl;
	free(buf);
	return recStr;
}

void HttpConnect::postData(std::string host, std::string path, std::string post_content)
{
	//POST请求方式
	std::stringstream stream;
	stream << "POST " << path;
	stream << " HTTP/1.0\r\n";
	stream << "Host: "<< host << "\r\n";
	stream << "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
	stream << "Content-Type:application/x-www-form-urlencoded\r\n";
	stream << "Content-Length:" << post_content.length()<<"\r\n";
	stream << "Connection:close\r\n\r\n";
	stream << post_content.c_str();

	socketHttp(host, stream.str());
}

CString HttpConnect::getData(std::string host, std::string path, std::string get_content)
{
	//GET请求方式
	std::stringstream stream;
	CString cs;
	//cs=get_content.c_str();

	//// UnicodeToUtf8方法将Unicode编码转为UTF-8格式。
	//crequest = UnicodeToUtf8(cs);
	//UnicodeToUtf8(wCharUnicode);

	//std::string ss=string_To_UTF8(get_content);

	char * p=(char*)get_content.data();
	std::string sss=string_To_UTF8(p);

	stream << "GET " << path << "?" << sss<<"\r\n";	


	//stream << " HTTP/1.0\r\n";
 //   stream << "Host: " << host << "\r\n";
 //   stream <<"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
 //   stream <<"Connection:close\r\n\r\n";




	//stream << " HTTP/1.0\r\n";
	//stream << "Host: " << host << "\r\n";
 //   stream<<"Accept-Encoding:gzip, deflate\r\n";
 //   stream<< "Accept-Language:zh-CN,en,*\r\n";
 //   stream<<"Content-Length:114\r\n";
 //   stream<< "Content-Type:application/x-www-form-urlencoded; charset=UTF-8\r\n";
 //   stream<< "User-Agent:Mozilla/5.0\r\n\r\n";
	//stream<<"Connection:Keep-Alive\r\n";


	stream<<"HTTP/1.1\r\n";
	stream << "Host: " << host << "\r\n";
	stream<<"Connection: close\r\n";
	stream<<"User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.139 Safari/537.36\r\n";
	stream<<"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n";
	stream<<"Accept-Encoding: gzip, deflate, br\r\n";
	stream<<"Accept-Language: zh-CN,zh;q=0.9\r\n";
	stream<< "Content-Type:application/x-www-form-urlencoded; charset=UTF-8\r\n\r\n";

	std::string recStr=socketHttp(host, stream.str());
	CString CrecStr;
	CrecStr.Format("%s", recStr.c_str());
	UTF8toANSI(CrecStr);
	return CrecStr;
}

char* HttpConnect::UnicodeToUtf8(const wchar_t* unicode)
{
	int len;
	len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = (char*)malloc(len + 1);
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
	return szUtf8;
}


std::string HttpConnect::string_To_UTF8(char* str)  
{
	string retStr=UrlUTF8(str);
	//int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);  

	//wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴  
	//ZeroMemory(pwBuf, nwLen * 2 + 2);  

	//::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);  

	//int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);  

	//char * pBuf = new char[nLen + 1];  
	//ZeroMemory(pBuf, nLen + 1);  

	//::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);  

	//std::string retStr(pBuf);  

	//delete []pwBuf;  
	//delete []pBuf;  

	//pwBuf = NULL;  
	//pBuf = NULL;  

	return retStr;  
}


//const wchar_t* HttpConnect::GetWC(const char *c)
//{
//    const size_t cSize = strlen(c)+1;
//    wchar_t* wc = new wchar_t[cSize];
//    mbstowcs(wc, c, cSize);
//
//    return wc;
//}