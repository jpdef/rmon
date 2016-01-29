#include "rsocket.h"

struct rsocket create_rsocket(char* portnum, char* servip){
    //implicitly allocates memory
    struct rsocket new_socket;
    //memset does not allocate memory only initializes values
    memset(&new_socket, 0, sizeof new_socket); 
 
    struct addrinfo ai;
    memset(&ai, 0, sizeof ai);

    ai.ai_family   = AF_UNSPEC;
    ai.ai_socktype = SOCK_STREAM;

    if(portnum == NULL || servip == NULL ){
        //printf(stderr, "config failed, null parameters\n" );
    }else {
       new_socket.portnum = portnum;
       new_socket.servip  = servip;
       initialize_socket(&ai,&new_socket);
    }
    
    return new_socket;
    
}

struct rsocket create_default_rsocket(){
    struct rsocket new_socket;
    memset(&new_socket, 0, sizeof new_socket);
     
    
    struct addrinfo ai;
    memset(&ai, 0, sizeof ai);

    //printf("memory set \n" );

    ai.ai_family   = AF_UNSPEC;
    ai.ai_socktype = SOCK_STREAM;
    
    new_socket.portnum = PORTNUM;
    new_socket.servip  = SERVIP;


    initialize_socket(&ai,&new_socket);
    //printf("initialized \n" );

    return new_socket;
} 

void initialize_socket(struct addrinfo* ai,struct rsocket* rs){
    //have kernel give you setting for socket
    struct addrinfo* servinf;
    int status = getaddrinfo(rs->servip,rs->portnum,ai,&servinf);
    if ( status < 0 ){
         //printf(stderr,"getaddrinfo failed");
    }


    //construct a socket
    rs->sockfd  = socket(servinf->ai_family,servinf->ai_socktype, servinf->ai_protocol);
    rs->servinf = servinf;
}

void connect_to_socket(struct rsocket* rs){
    int rc = 0;
    rc = connect(rs->sockfd,rs->servinf->ai_addr,rs->servinf->ai_addrlen);
    if (rc < 0 ){
        //printf(stderr, "failed to connect \n");
    }
}




char* read_from_server(struct rsocket* rs,int len){
    //read from sever
    char* msg; 
    msg = (char*) malloc(len*(sizeof(char)));
    int numbytes = recv(rs->sockfd,msg,len-1,0);
    if (numbytes == -1){
       //printf(stderr,"recv failed");
    }
    //*(&msg + numbytes) = '\0';
    msg[numbytes] = '\0';
    //printf("client: recieved '%s'\n", msg);
    return msg;
}


void write_to_server(struct rsocket* rs,char* msg){
    int rc = 0;
    int len = strlen(msg);
    rc = send(rs->sockfd,msg,len,0);    
    if (rc == -1){
        //printf(stderr,"send fail");
    }
}


//for tests
/*
int main(int argc, char *argv[]){


    rs = create_default_rsocket();
    //printf("%s\n",rs.servip );
    //printf("%p\n",&rs );
    connect_to_socket(&rs);
    write_to_server(&rs,"Salutations");
    char* msg = read_from_server(&rs,MAXCHAR);
    //printf("%s\n", msg);
}
  */            
