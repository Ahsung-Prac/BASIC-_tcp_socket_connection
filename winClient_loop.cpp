#include<iostream>
#include<cstdlib>
#include<winSock2.h>
#include<stdio.h>
#include<cstring>
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

	char message[100];
	int strLen = 0;
	if (argc != 3) {
		cout << "Usage: 프로세스name ip port 순서로 입력" << endl;
		exit(1);
	}
	cout << "ip: " << argv[1] << " port: " << argv[2] << " 연결시도!" << endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		erromessage("WSAStartup이 잘못됨");
	}
	//소켓 생성
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET) erromessage("클라이언트 소켓 안열림");
	//소켓에 주소할당.

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));
	if (connect(hSocket, (sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) erromessage("connect 실패");
	
	while (1) {
		cout << "전송 메세지: ";
		fgets(message,sizeof(message),stdin);
		if (message[0] == '0') break;

		strLen = send(hSocket, message, sizeof(message), 1);
		if (strLen < 0)
			erromessage("서버에 내용 전송 실패");

		cout << "waiting server msg"<<endl;
		strLen = recv(hSocket, message, sizeof(message) - 1, 0);
		if (strLen == SOCKET_ERROR) erromessage("서버에서 내용을 받지 못함");

		cout << "resv msg: "<< message << endl;
	}
	closesocket(hSocket);
	WSACleanup();
	return 0;
}
