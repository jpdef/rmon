#ifndef __NSCREEN_H_INCLUDED__
#define __NSCREEN_H_INCLUDED__

#define MAXCHAR 256


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <typeinfo>
#include "nscreen.h"
#include "nwindow.h"
extern "C"
{
   #include <ncurses.h>
}

using namespace std;


class Nscreen{
    public:
	int MAX_X ;
    int MAX_Y ;
    int numwindows;
  SCREEN* scrptr;
  vector<Nwindow> nwindows;
  int cw;

	public:

    Nscreen();
		Nscreen(int numwindows);
    ~Nscreen();
    void init_windows();
		void switch_window(int numwin);
    void clear();
    void next_win();

    template<typename P, typename Q>void print(P& obj, Q c){
        nwindows[cw].print_color(obj,c);
    }

    template<typename T,typename U> void move(T y, U x){
      nwindows[cw].move(y,x);
    }
};

#endif
