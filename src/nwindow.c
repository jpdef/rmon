#include "nwindow.h"

const char pi_art_1[35] = " \
  .~~.   .~~.\n\
  '. \\ ' ' / .'\n";

const char pi_art_2[365] = "\
   .~ .~~~..~.\n\
  : .~.'~'.~. :\n\
 ~ (   ) (   ) ~\n\
( : '~'.~.'~' : )\n\
 ~ .~ (   ) ~. ~\n\
  (  : '~' :  )\n\     
   '~ .~~~. ~'\n\      
       '~' \n";

nscreen* create_nscreen(int numwindows){
	nscreen* screen = (nscreen*) malloc(sizeof(nscreen));
	screen->wins = (nwindow**) malloc(numwindows*sizeof(nwindow*));
	screen->numwindows = numwindows;
    for (int i = 0 ; i< screen->numwindows;++i){    
         screen->wins[i] = (nwindow*) malloc(sizeof(nwindow));
    }

	return screen;
}
void init_nscreen(FILE* outputfp, nscreen* scr){
	int MAX_X, MAX_Y;
    scr->scrptr = newterm("xterm",stdin,stdout);    
    set_term(scr->scrptr);
    getmaxyx(stdscr,MAX_Y, MAX_X);
    for (int i = 0 ; i< scr->numwindows;++i){
        scr->wins[i]->winptr = newwin(MAX_Y/scr->numwindows,MAX_X, i*(MAX_Y/scr->numwindows) , 0);
    }
}

void clean_nscreen(nscreen* scr){
	for (int i = 0 ; i< scr->numwindows;++i){
         delwin(scr->wins[i]->winptr);
         free(scr->wins[i]);
    }
    endwin();
    delscreen(scr->scrptr);
    free(scr);
}

void piheader_to_win(nscreen* scr){
    
    start_color(); 
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    
    wattron(scr->wins[0]->winptr,COLOR_PAIR(0)); 
    wprintw(scr->wins[0]->winptr,"%s",pi_art_1); 

    wattron(scr->wins[0]->winptr,COLOR_PAIR(1)); 
    wprintw(scr->wins[0]->winptr,"%s",pi_art_2); 
    wmove(scr->wins[0]->winptr, 6, 20);
    wattroff(scr->wins[0]->winptr,COLOR_PAIR(1)); 
    wprintw(scr->wins[0]->winptr,"%s","Raspi");
    wmove(scr->wins[0]->winptr, 7, 20);
    wprintw(scr->wins[0]->winptr,"%s","Bandwidth Monitor");
    wrefresh(scr->wins[0]->winptr);

}

void string_to_win(nscreen* scr,int winnum,char* str){
    if(scr->wins[winnum] == NULL){
       //fprintf(stdout, "%s\n","print works" );
       wprintw(scr->wins[winnum]->winptr,"%s",str);
    }else{
        //fprintf(stdout, "%s\n","print failed" );
    }
           wprintw(scr->wins[winnum]->winptr,"%s",str);
           wrefresh(scr->wins[winnum]->winptr);

}


void carray_to_win(nscreen* scr,int winnum, int p, int size,double* buffer){
     int x_max =0; int y_max = 0; char c; double max =0;
     getmaxyx(scr->wins[winnum]->winptr,y_max,x_max);
     max = buf_get_max(buffer,x_max); 
     int i = 0;
     int limit = (p+1)%size;
     while (  p  != limit ){
         double val = (buffer[p] /  max)*(y_max -1);
         if (val > 10e6) val = (double)y_max -1;
         for (int j =y_max; j >=  0 ; --j){
             c = (val > j) ? 'X' : ' ';
             mvwaddch(scr->wins[winnum]->winptr,y_max-j,i,c);
         }
         --p;
         if (p <  0) p = size -1;
         ++i; 
     }
     wrefresh(scr->wins[winnum]->winptr);

}

void file_to_win(nscreen* scr,int winnum, char* filename){
   int c;
   FILE *file;
   file = fopen(filename, "r");
    if (file) {
    while ((c = getc(file)) != EOF)
      waddch(scr->wins[winnum]->winptr,c);
       fclose(file);
    }else{
      wprintw(scr->wins[winnum]->winptr,"%s","failure to read file");
    }
    wrefresh(scr->wins[winnum]->winptr);

}


double buf_get_max(double* buffer,int length){
   double max =0;
   for(int i = 0; i< length; ++i){
       if(buffer[i] > max) max = buffer[i]; 
   }
   return max;
}
