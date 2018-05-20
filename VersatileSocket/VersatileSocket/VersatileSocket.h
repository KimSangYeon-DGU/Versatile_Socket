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

class TCPSocket 
{
private:
	#ifdef _WIN32
	// For windows codex
	WSADATA wsa;
	SOCKET sock_fd, client_fd[MAX_CONN];
	#elif __linux__
	// For linux codes
	#endif // DEBUG

	struct sockaddr_in server, client;
	char* buffer = new char[BUF_LEN];
	int c;
	// the number of clients
	int clt_num = 0;
	// Constructor

public:
	TCPSocket();

	// Constructor
	TCPSocket(std::string ip, int port);

	// send
	bool send(int to, std::string message);

	// sendToAll
	bool sendToAll(int from, std::string message);

	// receive
	std::string receive(int from);

	// close
	void close();

	// bind
	bool bind();

	// accept
	int accept();

	// connector
	bool connect();

	// listener
	bool listen();

	int getClientNumber();

	SOCKET getSockfd();

	void showClient();

	bool removeClient(int client);
};

class UDPSocket 
{

	// TCP Socket Constructor
	UDPSocket();
};