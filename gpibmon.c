#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "rmonclient.h"

#define MAX_CHAR 256

//Input vars
FILE* inputfp;
FILE* outputfp;
//char* istr = "eth0:";
//Output vars
int ttyfp;

SCREEN* s;
WINDOW* rx_win;
WINDOW* tx_win;
WINDOW* hd_win;
int MAX_X;
int MAX_Y;
double bmax[2] = {0,0};

char pi_art_1[35] = " \
  .~~.   .~~.\n\
  '. \\ ' ' / .'\n";

char pi_art_2[365] = "\
   .~ .~~~..~.\n\
  : .~.'~'.~. :\n\
 ~ (   ) (   ) ~\n\
( : '~'.~.'~' : )\n\
 ~ .~ (   ) ~. ~\n\
  (  : '~' :  )\n\     
   '~ .~~~. ~'\n\      
       '~' ";


/*
void  read_net_data(FILE* inputfp, net_data* nd){
       int record_flag =1;  int i=0;
       char filebuffer[MAX_CHAR];
       char* tok; char* end; 

       while (! feof(inputfp)) {
         fgets(filebuffer, MAX_CHAR, inputfp);
         tok = strtok(filebuffer, " ");
         while(tok != NULL){
           if(record_flag == 0){
              if(i == 0) {nd->tx = atof(strdup(tok));printf("%s ,",strdup(tok));}
              if(i == 8) {nd->rx = atof(strdup(tok));printf("%s \n",strdup(tok));}
              ++i;
           } 
           if( strcmp(istr, tok) == 0  ) record_flag = 0;
           tok = strtok(NULL, " ");
          }
       }
       rewind(inputfp);    
} */

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

double get_data_max(double* buffer){
   double max =0;
   for(int i = 0; i< MAX_X; ++i){
       if(buffer[i] > max) max = buffer[i]; 
   }
   return max;
}

void write_net_data(WINDOW* w, double* buffer, int p){
     int x_max =0; int y_max = 0; char c; double max =0;
     getmaxyx(w,y_max,x_max);
     max = get_data_max(buffer);
     int i = 0;
     int limit = (p+1)%40;
     while (  p  != limit ){
         double val = (buffer[p] /  max)*(y_max -1);
         printf("%f ,", val);
         if (val > 10e6) val = (double)y_max -1;
         for (int j =y_max; j >=  0 ; --j){
             c = (val > j) ? 'X' : ' ';
             mvwaddch(w,y_max-j,i,c);
         }
         --p;
         if (p <  0) p = 39;
         ++i; 
     }
     printf("\n %f \n \n ",max);
}

void initialize_windows(){
   hd_win = newwin(MAX_Y/3.0, MAX_X, 0 , 0);
   rx_win = newwin(MAX_Y/3.0, MAX_X, MAX_Y/3 ,0);
   tx_win = newwin(MAX_Y/3.0, MAX_X, 2*MAX_Y/3,0);
} 

void initialize_tty(){
    outputfp = fopen("/dev/tty1","w+");
    s = newterm("xterm",outputfp,outputfp);
    set_term(s);
    getmaxyx(stdscr,MAX_Y, MAX_X);
}

void clean_window(){
   delwin(hd_win);
   delwin(rx_win);
   delwin(tx_win);
}

void clean_tty(SCREEN *s){
    endwin();
    delscreen(s);
}

int main(int argc, char **argv){
    //Initialize file
    inputfp  = fopen("/proc/net/dev","r");
  
    initialize_tty();
    initialize_windows(); 
    rmon_connect();

    double* rx_buffer = (double*) calloc(MAX_X,sizeof(double));
    double* tx_buffer = (double*) calloc(MAX_X,sizeof(double));
  
    start_color(); 
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    
    wattron(hd_win,COLOR_PAIR(2)); 
    wprintw(hd_win,"%s",pi_art_1); 

    wattron(hd_win,COLOR_PAIR(1)); 
    wprintw(hd_win,"%s",pi_art_2); 
    wmove(hd_win, 6, 20);
    wattroff(hd_win,COLOR_PAIR(1)); 
    wprintw(hd_win,"%s","Raspi");
    wmove(hd_win, 7, 20);
    wprintw(hd_win,"%s","Bandwidth Monitor");
    wrefresh(hd_win);
    

    int i = 0;
    for( ; ;){ 

       push_data(inputfp,rx_buffer,tx_buffer,i);
       write_net_data(rx_win,rx_buffer,i);
       write_net_data(tx_win,tx_buffer,i);
       i = (i+1) % MAX_X;
      
       wmove(rx_win, 0,0);
       wprintw(rx_win,"%s  %.2f kB","RX max:", get_data_max(rx_buffer)/1024);   
       wmove(tx_win, 0,0);
       wprintw(tx_win,"%s  %.2f kB","TX max:", get_data_max(tx_buffer)/1024);   
   
       wrefresh(rx_win);
       wrefresh(tx_win);
    
    }
    
    clean_window(); 
    clean_tty(s);
    return 0; 
}

