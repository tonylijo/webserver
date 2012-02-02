/*
 * Web server in cpp
 */
#include<stdio.h>
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<cstdlib>
#include<cstring>
#include<string>
#include<vector>
#include<map>
#include"socket.h"
#include<pthread.h>

using namespace std;

vector<string> split(char *buf,char *delim)
{
  vector<string> result;
  char *tock = strtok(buf,delim);
  while(tock != NULL) {
    result.push_back(tock);
    tock = strtok(NULL,delim);
  }
  return result;
}

map<string, vector<string> > split_to_map(vector<string> vectref)
{
  int i;
  map<string, vector<string> > map_lock;
  vector<string> newvect;
  for(i = 0; i < vectref.size(); i++) {
    //    cout << split((char *) vectref[i].c_str(),(char *) " ")[0] << endl;
    newvect = split((char *) vectref[i].c_str(),(char *)" ");
    string temp = newvect[0];
    newvect.erase(newvect.begin());
    map_lock[temp] = newvect;
  }
  return map_lock;
}

void *handle_request(void *connected)
{
    int count,i;
    char buf[1024];
    char read_buf[4096];
    count = recv((int )connected,buf,1024,0);
    buf[count] = '\0';
    vector<string> line_tock = split((char *) buf,(char *) "\n");
    for(i = 0; i < line_tock.size(); i++) {
	cout << line_tock[i] << endl;
    }
    map<string,vector<string> > parse_map = split_to_map(line_tock);
    string filename = "/var/www" + parse_map["GET"][0] + "index.html";
    int fd;
    if((fd = open(filename.c_str(),O_RDONLY)) < 0) {
      perror("open");
      exit(errno);
    }

    cout << " filename is " << filename << endl;
    while((count = read(fd,read_buf,4096))>0) {
      cout << count << endl;
      //      write(1,read_buf,count);
      cout << send((int) connected,read_buf,count,0) << endl ;
    }
    cout << "Hai" << endl;
    while(1);
}

int main(int argc,char *argv[])
{
  int i;
  pthread_t tid;
  Socket sock = Socket(80,(char *)"127.0.0.1");
  struct sockaddr_in client;
  int connected;
  while(1) {
    connected = sock.Accept((struct sockaddr *) &client);
    pthread_create(&tid,0,handle_request,(void *) connected);
  }
}
