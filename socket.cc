#include<iostream>
#include<cstdlib>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<cstdio>
#include"socket.h"
/*
using namespace std;
class Socket {
  int fd;
  struct sockaddr_in server;
public:
  Socket();
  Socket(int port,char *ip);
  int create_socket(int family,int type);
  void init_sockaddr(int port,char *ip);
  void Bind();
  void Listen(int no);
  int Accept(struct sockaddr *client);
};*/

Socket:: Socket(int port,char *ip) 
{
    fd = create_socket(AF_INET,SOCK_STREAM);
    init_sockaddr(port,ip);
    Bind();
    Listen(5);
}

Socket:: Socket()
{
  cout << "creating socket...." << endl;
  fd = create_socket(AF_INET,SOCK_STREAM);
  cout << "initialising the sock addr.... " << endl;
  init_sockaddr(5000,(char *) "127.0.0.1");
  cout << "Binding the socket to localhost:5000....." << endl;
  Bind();
  cout << "listening up to five clients in the queue......" << endl;
  Listen(5);
}

int Socket:: create_socket(int family,int type)
{
  int sock_fd;
  if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
    perror("Socket");
    exit(errno);
  }
  return sock_fd;
}

void Socket:: init_sockaddr(int port,char *ip)
{
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = inet_addr(ip);
}

void Socket:: Bind()
{
  if(bind(fd,(struct sockaddr *) &server,sizeof(struct sockaddr))) {
    perror("Bind");
    exit(errno);
  }
}

void Socket:: Listen(int no) 
{
  if(listen(fd,no)) {
    perror("Liseten");
    exit(errno);
  }
}

int Socket:: Accept(struct sockaddr *client) 
{
  int c;
  socklen_t len = sizeof(struct sockaddr);
  cout << "in accept" << endl;
  if((c = accept(fd,client,&len)) < 0) {
    perror("Accept");
    exit(errno);
  }
  cout << "after accept" << endl;
  return c;
}
