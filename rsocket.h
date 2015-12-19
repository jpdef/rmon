#ifndef RSOCKET_H
#define RSOCKET_H "rsocket.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BACKLOG  10    //how many pending24 connections
#define PORTNUM  "23" //port of the client (telnet)
#define SERVIP   "192.168.168.1"
#define MAXCHAR  1024


struct rsocket {
	int sockfd;
	char* servip;
	char* portnum;
	struct addrinfo* servinf;
};


struct rsocket create_rsocket(char* portnum, char* servip);
struct rsocket create_default_rsocket();
void destroy_socket(struct rsocket* rs);
void connect_to_socket(struct rsocket* rs);

//void router_read_net_data(char* filebuffer, net_data* nd);
void   initialize_socket(struct addrinfo* ai, struct rsocket* rs);
char*  read_from_server(struct rsocket* rs, int len);
void   write_to_server(struct rsocket* rs, char* msg);

#endif
