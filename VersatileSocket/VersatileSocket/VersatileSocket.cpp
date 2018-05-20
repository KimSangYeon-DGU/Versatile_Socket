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

	memset(client_fd, 0, sizeof(client_fd));
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
		cout << "Connection failed" << endl;
		return false;
	}
	else
	{
		// Connection success
		cout << "Socket connected" << endl;
		return true;
	}
}

bool TCPSocket::send(int to, string message) {
	if (::send(to, message.c_str(), (int)strlen(message.c_str()), 0) < 0)
	{
		// Send fail
		return false;
	}
	else {
		// Send success
		return true;
	}
}

bool TCPSocket::sendToAll(int from, string message)
{
	for (int client = 0; client < this->clt_num; client++) 
	{
		if (this->client_fd[client] == from)
			continue;
		if (::send(this->client_fd[client], message.c_str(), (int)strlen(message.c_str()), 0) < 0)
		{
			// Send fail
			return false;
		}
	}
	return true;
}

string TCPSocket::receive(int from) {
	int recv_size;
	if ((recv_size = ::recv(from, this->buffer, BUF_LEN, 0)) == SOCKET_ERROR)
	{
		// receive fail
		return "FAIL";
	}
	else {
		// receive success
		buffer[recv_size] = '\0';
		return string(buffer);
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
	if (::listen(this->sock_fd, MAX_CONN) == 0) 
	{
		return true;
	}
	else {
		return false;
	}
}

int TCPSocket::accept() 
{
	c = sizeof(struct sockaddr_in);
	this->client_fd[this->clt_num] = ::accept(this->sock_fd, (struct sockaddr *)&this->client, &c);
	if (client_fd[this->clt_num] == INVALID_SOCKET) 
	{
		// accept fail
		return -1;
	}
	else 
	{
		// accept success
		this->clt_num++;
		char addr_buf[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &this->client.sin_addr, addr_buf, INET_ADDRSTRLEN);
		cout << "Connected IP Address: " << addr_buf << ", Port: " << ntohs(this->client.sin_port)<<endl;
		return this->client_fd[this->clt_num-1];
	}
}

SOCKET TCPSocket::getSockfd() 
{
	return this->sock_fd;
}

int TCPSocket::getClientNumber() 
{
	return this->clt_num;
}

bool TCPSocket::removeClient(int client){
	for (int i = 0; i < this->clt_num; i++) {
		if (this->client_fd[i] == client) {
			for (int j = i; j < this->clt_num - 1; j++) {
				this->client_fd[j] = this->client_fd[j + 1];
			}
			this->clt_num--;
			return true;
		}
	}
	return false;
}

void TCPSocket::showClient() {
	for (auto c : this->client_fd)
		cout << c << " ";
	cout << endl;
}
UDPSocket::UDPSocket() 
{

}
