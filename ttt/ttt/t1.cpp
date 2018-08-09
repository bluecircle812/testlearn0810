
//ͷ�ļ�
#include <iostream>
#include <string>
#include <Winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include "HttpConnect.h"
using namespace std;

//��������
int request(char* hostname, char* api, char* parameters);

//��������
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
    int nRetCode = 0;


    // initialize MFC and print and error on failure
    //if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
    //{
    //    // TODO: change error code to suit your needs
    //    _tprintf(_T("Fatal Error: MFC initialization failed\n"));
    //    return 1;
    //}
    
    request("reg.163.com", "http://reg.163.com/CheckUser.jsp", "test");

    return nRetCode;
}

//����ʵ��
int request(char* hostname, char* api, char* parameters)
{
    WSADATA WsaData;
    WSAStartup(0x0101, &WsaData);


    //��ʼ��socket
    struct hostent* host_addr = gethostbyname(hostname);
    if (host_addr == NULL)
    {
        cout<<"Unable to locate host"<<endl;
        return -103;
    }


    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons((unsigned short)80);
    sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list);


    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return -100;
    }


    //��������
    if (connect(sock, (const struct sockaddr *)&sin, sizeof(sockaddr_in) ) == -1)
    {
        cout<<"connect failed"<<endl;
        return -101;
    }


    //��ʼ��������Ϣ
    char send_str[2048] = {0};


    //ͷ��Ϣ
    strcat(send_str, "POST ");
    strcat(send_str, api);
    strcat(send_str, " HTTP/1.1\r\n");
    strcat(send_str, "Host: ");
    strcat(send_str, hostname);
    strcat(send_str, "\r\n");
    strcat(send_str, "Connection: keep-alive\r\n");


    char content_header[100];
    sprintf(content_header,"Content-Length: %d\r\n", strlen(parameters));


    strcat(send_str, content_header);
    strcat(send_str, "Cache-Control: max-age=0\r\n");
    strcat(send_str, "Origin: http://www.hao123.com\r\n");
    strcat(send_str, "User-Agent: Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/15.0.849.0 Safari/535.1\r\n");
    strcat(send_str, "Content-Type: application/x-www-form-urlencoded\r\n");
    strcat(send_str, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n");
    strcat(send_str, "Referer: http://www.hao123.com/\r\n");
    strcat(send_str, "Accept-Encoding: gzip,deflate,sdch\r\n");
    strcat(send_str, "Accept-Language: zh-CN,zh;q=0.8\r\n");


    //������Ϣ
    strcat(send_str, "\r\n");
    strcat(send_str, parameters);


    if (send(sock, send_str, strlen(send_str),0) == -1)
    {
        cout<<"send failed"<<endl;
        return -101;
    }


    //��ȡ������Ϣ
    char recv_str[4096] = {0};
    if (recv(sock, recv_str, sizeof(recv_str), 0) == -1)
    {
        cout<<"recv failed"<<endl;
        return -101;
    }


    cout<<recv_str<<endl;


    WSACleanup( );


    return 0;
}

