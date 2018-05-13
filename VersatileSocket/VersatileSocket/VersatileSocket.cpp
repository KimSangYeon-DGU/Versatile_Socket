#include "VersatileSocket.h"

TCPSocket::TCPSocket() 
{
	#ifndef _WIN
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "Winsock library initialization was failed" << endl;
		exit(1);
	}
	else 
	{
		cout << "Winsock library initialization succeeded" << endl;
	}
	
	if ((this->sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		cout << "Creating Socket was failed" << endl;
		exit(1);
	}
	else {
		cout << "Socket was created" << endl;
	}
	#endif // !_WIN
}

TCPSocket::TCPSocket(string ip, int port) : TCPSocket()
{
	this->server.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	this->server.sin_family = AF_INET;
	this->server.sin_port = htons(port);
}

bool TCPSocket::connect()
{
	if (::connect(sock_fd, (struct sockaddr *)&this->server, sizeof(this->server)) < 0)
	{
		// Connection fail
		return false;
	}
	else
	{
		// Connection success
		return true;
	}
}

bool TCPSocket::send(string message) {
	if (::send(this->sock_fd, message.c_str(), strlen(message.c_str()), 0) < 0)
	{
		// Send fail
		return false;
	}
	else {
		// Send success
		return true;
	}
}

string TCPSocket::receive() {
	int recv_size;
	char* buffer;
	if ((recv_size = ::recv(this->sock_fd, buffer, BUF_LEN, 0)) == SOCKET_ERROR)
	{
		// receive fail
		return NULL;
	}
	else {
		// receive success
		buffer[recv_size] = '\0';
		return buffer;
	}
}

void TCPSocket::close() {
	#ifdef _WIN32
	closesocket(this->sock_fd);
	WSACleanup();
	#elif

	#endif // !
}

bool TCPSocket::bind() 
{
	if (::bind(this->sock_fd, (struct sockaddr *)&this->server, sizeof(this->server)) == SOCKET_ERROR) 
	{	
		// bind fail
		return false;
	}
	else {
		// bind success
		return true;
	}
}

bool TCPSocket::listen() 
{
	::listen(this->sock_fd, MAX_CONN);
}

bool TCPSocket::accept() {
	c = sizeof(struct sockaddr_in);
	this->client_fd[this->clt_num] = ::accept(this->sock_fd, (struct sockaddr *)&this->client, &c);
	if (client_fd[this->clt_num] == INVALID_SOCKET) 
	{
		// accept fail
		return false;
	}
	else 
	{
		// accept success
		return true;
	}
}

UDPSocket::UDPSocket() 
{

}
