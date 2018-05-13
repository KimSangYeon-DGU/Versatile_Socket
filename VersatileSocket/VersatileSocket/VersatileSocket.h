#include <string>
#include <cstdlib>
#include <iostream>

// Winsock Library
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#elif __linux__
// for linux
#endif
#define BUF_LEN 65535
#define MAX_CONN 10
using namespace std;

class TCPSocket {
	#ifdef _WIN32
	// For windows codex
	WSADATA wsa;
	SOCKET sock_fd, client_fd[MAX_CONN];
	#elif __linux__
	// For linux codes
	#endif // DEBUG

	struct sockaddr_in server, client;
	string buffer;
	int c;
	// the number of clients
	int clt_num = 0;
	// Constructor
	TCPSocket();

	// Constructor
	TCPSocket(string ip, int port);

	// send
	bool send(string message);

	// receive
	string receive();

	// close
	void close();

	// bind
	bool bind();

	// accept
	bool accept();

	// connector
	bool connect();

	// listener
	bool listen();
};

class UDPSocket {

	// TCP Socket Constructor
	UDPSocket();
};