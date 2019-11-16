#include<iostream>
#include<cstdlib>
#include<winSock2.h>
using namespace std;

void erromessage(const char * message) {
	cerr << message << endl;
	exit(1);
}
void setSOCKIN(SOCKADDR_IN &sock, char * ip, uint16_t port) {
	memset(&sock, 0, sizeof(sock));
	sock.sin_family = AF_INET;
	sock.sin_addr.s_addr = htonl(inet_addr(ip));
	sock.sin_port = htons(port);
}


int main(int argc, char * argv[]) {
	WSADATA wsadata;	
	SOCKET hSocket; 
	SOCKADDR_IN servAddr; 

	char message[30];
	int strLen = 0;
	if (argc != 3) {
		cout << "Usage: ���μ���name ip port ������ �Է�" << endl;
		exit(1);
	}
	cout << "ip: " << argv[1] << " port: " << argv[2] <<" ����õ�!"<< endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		erromessage("WSAStartup�� �߸���");
	}
	//���� ����
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET) erromessage("Ŭ���̾�Ʈ ���� �ȿ���");
	//���Ͽ� �ּ��Ҵ�.

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));
	
	if (connect(hSocket, (sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) erromessage("connect ����");
	
	strLen = recv(hSocket, message, sizeof(message)-1, 0);
	if (strLen == SOCKET_ERROR) erromessage("�������� ������ ���� ����");

	cout << message << endl;

	//Ŭ���̾�Ʈ���� �޼��� ����;
	closesocket(hSocket);
	WSACleanup();
	return 0;
}

