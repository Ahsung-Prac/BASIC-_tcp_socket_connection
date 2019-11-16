#include<iostream>
#include<cstdlib>
#include<cstring>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

using namespace std;

void erromessage(const char * message) {
	cerr << message << endl;
	exit(1);
}

void setSOCKIN(sockaddr_in &sock,const char* port) {
	memset(&sock, 0, sizeof(sock));
	sock.sin_family = AF_INET;
	sock.sin_addr.s_addr = htonl(INADDR_ANY);
	sock.sin_port = htons(atoi(port));
}


int main(int argc, char * argv[]) {
	
	int hserveSock, hClntSock; 
	sockaddr_in servAddr, clntaddr;
	socklen_t szClntAddr;
	
	char message[] = "asung Hello world";
	
	if (argc != 2) {
		cout << "Usage: filename portnum" << endl;
		exit(1);
	}
	
	//¼ÒÄÏ »ý¼º
	hserveSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hserveSock == -1) {
		erromessage("server can't open");
	}
	//server ¿¿¿¿ ¿¿
	/*memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));*/
	setSOCKIN(servAddr,argv[1]);

	// bind ¿¿ port ¿¿
	if (bind(hserveSock, (sockaddr *)&servAddr, sizeof(servAddr)) == -1) {
		erromessage("bind fail");
	}
	// listen ¿¿ 
	if (listen(hserveSock, 5) == -1) erromessage("listen fail");
	
	szClntAddr = sizeof(clntaddr);
	cout <<"port: " << argv[1] <<" accept excute!" << endl;
	
	//accept!!
	hClntSock = accept(hserveSock, (sockaddr *)&clntaddr, &szClntAddr);
	
	if (hClntSock == -1) erromessage("accep fail");
	
	// ¿¿¿ ¿¿ 
	write(hClntSock, message, sizeof(message));
	cout << "message send success !" << endl;
	close(hserveSock);
	close(hClntSock);
	exit(1);
	return 0;
}

