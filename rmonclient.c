#include "rmonclient.h"

void  rmon_connect(){
    rs = create_default_rsocket();
    printf("%s\n",rs.servip );
    printf("%p\n",&rs );
    connect_to_socket(&rs);
    write_to_server(&rs,"Salutations\n");
    char* msg = read_from_server(&rs,MAXCHAR);
    printf("%s\n", msg);
}

void  run_cmd(char** datastr,int cmd){
      char* cmdstr = (char* ) malloc(MAXCHAR*sizeof(char));
      strcpy(cmdstr, (cmds.find(cmd)->second).c_str());
      write_to_server(&rs,cmdstr);
      read_from_server(&rs,MAXCHAR);
      printf("%p\n", &datastr);
      *(datastr) = read_from_server(&rs,MAXCHAR);
      printf("%p\n", &datastr);
}

void  parse_net_data(char** datastr, net_data* nd){
       int record_flag =1;  int i=0;
       char* tok;  

       tok = strtok(*datastr, " ");
       while(tok != NULL){
         //printf("%s \n",strdup(tok));
         if(record_flag == 0){
            if(i == 0) {nd->tx = atof(strdup(tok));printf("%s ,",strdup(tok));}
            if(i == 8) {nd->rx = atof(strdup(tok));printf("%s \n",strdup(tok));}
            ++i;
         } 
         if( strcmp(istr, tok) == 0  ) record_flag = 0;
         tok = strtok(NULL, " ");
        }
}

void get_net_data(net_data* nd){
       char* datastr = (char* ) malloc(MAXCHAR*sizeof(char));
       run_cmd(&datastr,0);
       parse_net_data(&datastr,nd);        
}

/*
int main(){
  //char* datastr = (char* ) malloc(MAXCHAR*sizeof(char));
  net_data* nd = (net_data*) malloc(sizeof(net_data));
  //printf(" string ->%p\n", &datastr);
  rmon_connect();
  //run_cmd(&datastr, 0);
  //parse_net_data(&datastr,nd);
  get_data(nd);
  return 0;
}
*/