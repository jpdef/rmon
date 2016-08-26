#ifndef RMONCLIENT_H
#define RMONCLIENT_H "rmonclient.h"
#include <map>
#include <string>
#include "rsocket.h"

static char* istr = "br0:";

static std::map<int,std::string> cmds = {
	{0,"cat /proc/net/dev\n"}
};

typedef struct _net_data{
	double tx;
	double rx;
} net_data;

static struct rsocket rs;

void  rmon_connect();
void  run_cmd(char** datastr, int cmd);
void  parse_nd(char* datastr, net_data* nd);
void  parse_net_data(char** datastr, net_data* nd);
void  get_net_data(net_data* nd);



#endif
