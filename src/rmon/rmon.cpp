#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <assert.h>

#include "rmonclient.h"
#include "../nwin/nwindow.h"
#include "../nwin/nscreen.h"

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

char* readfile(FILE* f){
    fseek(f,0,SEEK_END);
    long fsize = ftell(f);
    fseek(f,0, SEEK_SET);
    char* foo = (char*)  malloc(fsize+1);
    fread(foo,fsize,1,f);
    printf("%s\n",foo);
    fclose(f);
    return foo;
}

void file_to_char_array(char* fname, char* filearray){
     FILE* fp = fopen(fname,"r");
     int i =0;
     char c;
     assert(fp);
     while ((c=fgetc(fp)) != EOF){
         filearray[i++] = c;
     }
     fclose(fp);
}


int main(int argc, char **argv){
    //Initialize files
    outputfp = stdout;

    //Nscreen* nscreen = new Nscreen(1);
    

    //double* rx_buffer = (double*) calloc(nscreen->MAX_X,sizeof(double));
    //double* tx_buffer = (double*) calloc(nscreen->MAX_X,sizeof(double));
    
    char foo [200];
    //sprintf(foo, "%s %d\n","entering event loop", nscreen->MAX_X);
    //nscreen->print(foo,blue);
    //std::string str(readfile(inputfp)); 
    //nscreen->print(str,blue);
    int i = 0;
    char str[2048];
    file_to_char_array("/proc/net/dev",str);
    net_data* nd = (net_data*)malloc(sizeof(net_data));
    //printf("String = %s\n",str);
    parse_nd(str,nd);
    printf("Netdata %f , %f\n",nd->tx,nd->rx);
    for( ; ;){
       //push_data(inputfp,rx_buffer,tx_buffer,i);
       //write_net_data(scr->wins[0]->winptr,rx_buffer,i);
       //write_net_data(scr->wins[1]->winptr,tx_buffer,i);
       //i = (i+1) % MAX_X;
      
       //wmove(scr->wins[0]->winptr, 0,0);
       //wprintw(scr->wins[0]->winptr,"%s  %.2f kB","RX max:", get_data_max(rx_buffer)/1024);   
       //wmove(scr->wins[1]->winptr, 0,0);
       //wprintw(scr->wins[1]->winptr,"%s  %.2f kB","TX max:", get_data_max(tx_buffer)/1024);   
   //
       //wrefresh(scr->wins[0]->winptr);
       //wrefresh(scr->wins[1]->winptr);
    
    }
    
    /*clean up stuff*/
    /*
    clean_nscreen(scr);
    */
    return 0; 
}

