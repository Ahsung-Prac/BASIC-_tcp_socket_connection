#include<iostream>
#include<cstdlib>
#include<winSock2.h>
using namespace std;

void erromessage(const char * message) {
	cerr << message << endl;
	exit(1);
}
void setSOCKIN(SOCKADDR_IN &sock,int ip , uint16_t port) {
	memset(&sock, 0, sizeof(sock));
	sock.sin_family = AF_INET;
	sock.sin_addr.s_addr = htonl(ip);
	sock.sin_port = htons(port);
}


int main(int argc, char * argv[]) {
	WSADATA wsadata;	//���̺귯�� ������ ���� �ּҰ� ���� �Ű�ü
	SOCKET hserveSock, hClntSock; //server ���ϰ� client ����
	SOCKADDR_IN servAddr, clntaddr; // ���� ������ ���� ��ü
	
	int szClntAddr;
	char message[] = "asung Hello world";
	
	if (argc != 2) {
		cout << "Usage: ���μ���name port ������ �Է�" << endl;
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		erromessage("WSAStartup�� �߸���");
	}
	//���� ����
	hserveSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hserveSock == INVALID_SOCKET) {
		erromessage("server ������ ���� ����");
	}
	//servAddr ����
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	//�ּ������� ���� ���ε�
	if (bind(hserveSock, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		erromessage("���� ���ε忡�� ����");
	}
	//���� ������ ����
	if (listen(hserveSock, 5) == SOCKET_ERROR) erromessage("listen���� ����");
	
	szClntAddr = sizeof(clntaddr);
	cout <<"port: " << argv[1] <<" accept ����!" << endl;
	//Ŭ���̾�Ʈ ������ ���������� accept�ؿ� �������� ����, ����� ���Ҽ��� �־ �����ͷ� �ִ°ǰ�?
	hClntSock = accept(hserveSock, (SOCKADDR *)&clntaddr, &szClntAddr);
	
	if (hClntSock == INVALID_SOCKET) erromessage("accep�� �ȵ�");
	
	//Ŭ���̾�Ʈ���� �޼��� ����
	if(send(hClntSock, message, sizeof(message), 0) == SOCKET_ERROR) erromessage("���� ����");
	cout << "message���� !" << endl;
	closesocket(hserveSock);
	closesocket(hClntSock);
	WSACleanup();
	return 0;
}

