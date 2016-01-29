#include "nscreen.h"

Nscreen::Nscreen(){
    //default constructor uses stdin and out
    this->numwindows = 1;
    scrptr = newterm("xterm",stdin,stdout);    
    set_term(scrptr);
    getmaxyx(stdscr,MAX_Y, MAX_X);

    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);

    init_windows();
    cw=0;
}

Nscreen::Nscreen(int numwindows){
    //default constructor uses stdin and out
    this->numwindows = numwindows;
    scrptr = newterm("xterm",stdin,stdout);    
    set_term(scrptr);
    getmaxyx(stdscr,MAX_Y, MAX_X);

    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);

    init_windows();
    cw=0;
}


Nscreen::~Nscreen(){
   delscreen(scrptr);
}


void Nscreen::init_windows(){
    nwindows = vector<Nwindow>(numwindows);
    for (int i = 0 ; i< numwindows;++i){
        nwindows[i] = Nwindow(MAX_Y/numwindows,MAX_X, 
        	                i*(MAX_Y/numwindows) , 0);
    }
}

void Nscreen::next_win(){
      cw =(cw + 1) % numwindows;
}

void Nscreen::clear(){
	nwindows[cw].clear();
}
