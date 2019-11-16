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
	WSADATA wsadata;	//라이브러리 연결을 위한 주소값 전달 매개체
	SOCKET hserveSock, hClntSock; //server 소켓과 client 소켓
	SOCKADDR_IN servAddr, clntaddr; // 소켓 정보를 담을 객체
	
	int szClntAddr;
	char message[] = "asung Hello world";
	
	if (argc != 2) {
		cout << "Usage: 프로세스name port 순서로 입력" << endl;
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		erromessage("WSAStartup이 잘못됨");
	}
	//소켓 생성
	hserveSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hserveSock == INVALID_SOCKET) {
		erromessage("server 소켓이 생성 실패");
	}
	//servAddr 셋팅
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	//주소정보로 소켓 바인딩
	if (bind(hserveSock, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		erromessage("서버 바인드에서 에러");
	}
	//소켓 리스닝 시작
	if (listen(hserveSock, 5) == SOCKET_ERROR) erromessage("listen에서 오류");
	
	szClntAddr = sizeof(clntaddr);
	cout <<"port: " << argv[1] <<" accept 구동!" << endl;
	//클라이언트 소켓은 서버소켓이 accept해온 소켓정보 저장, 사이즈가 변할수도 있어서 포인터로 주는건가?
	hClntSock = accept(hserveSock, (SOCKADDR *)&clntaddr, &szClntAddr);
	
	if (hClntSock == INVALID_SOCKET) erromessage("accep가 안됨");
	
	//클라이언트에게 메세지 전달
	if(send(hClntSock, message, sizeof(message), 0) == SOCKET_ERROR) erromessage("전달 실패");
	cout << "message전달 !" << endl;
	closesocket(hserveSock);
	closesocket(hClntSock);
	WSACleanup();
	return 0;
}

