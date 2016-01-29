#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "rmonclient.h"
#include "../nwin/nwindow.h"

#define MAX_CHAR 256

//Input vars
FILE* inputfp;
FILE* outputfp;
//char* istr = "eth0:";
//Output vars
int ttyfp;

int MAX_X;
int MAX_Y;
double bmax[2] = {0,0};



void push_data(FILE* input_fp,double* tx_buffer,double* rx_buffer,int index){
     net_data* nd_1 = (net_data*)malloc(sizeof(net_data));
     net_data* nd_2 = (net_data*) malloc(sizeof(net_data));
     //read_net_data(input_fp,nd_1);
     get_net_data(nd_1);
     sleep(2); 
     //read_net_data(input_fp,nd_2);
     get_net_data(nd_2);
     tx_buffer[index] = (nd_2->tx - nd_1->tx);  
     rx_buffer[index] = (nd_2->rx - nd_1->rx);
     free(nd_1); free(nd_2);  
}

int main(int argc, char **argv){
   /*
    //Initialize files
    inputfp  = fopen("/proc/net/dev","r");
    outputfp = stdout;//fopen("/dev/tty1","w+");//stdout;

    //Create and initialize screen
    nscreen* scr;
    scr = create_nscreen(2);
    init_nscreen(outputfp,scr); 
    file_to_win(scr,0,"/home/jpdef/test.txt");
    //piheader_to_win(scr);
    for(;;){

    }

    //print_to_window(scr,0,"hello world\n");
    
        //Connect to router
    fprintf(stdout, "%s\n","try to connect" );
    rmon_connect();

    double* rx_buffer = (double*) calloc(MAX_X,sizeof(double));
    double* tx_buffer = (double*) calloc(MAX_X,sizeof(double));
  
    fprintf(stdout, "%s\n","entering event loop" );
    int i = 0;
    for( ; ;){ 

       push_data(inputfp,rx_buffer,tx_buffer,i);
       write_net_data(scr->wins[0]->winptr,rx_buffer,i);
       write_net_data(scr->wins[1]->winptr,tx_buffer,i);
       i = (i+1) % MAX_X;
      
       wmove(scr->wins[0]->winptr, 0,0);
       wprintw(scr->wins[0]->winptr,"%s  %.2f kB","RX max:", get_data_max(rx_buffer)/1024);   
       wmove(scr->wins[1]->winptr, 0,0);
       wprintw(scr->wins[1]->winptr,"%s  %.2f kB","TX max:", get_data_max(tx_buffer)/1024);   
   
       wrefresh(scr->wins[0]->winptr);
       wrefresh(scr->wins[1]->winptr);
    
    }
    
    /*clean up stuff*/
    /*
    clean_nscreen(scr);
    */
    return 0; 
}

