#ifndef __NWINDOW_H_INCLUDED__
#define __NWINDOW_H_INCLUDED__

#define MAXCHAR 256


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>

extern "C"
{
   #include <ncurses.h>
}

using namespace std;

enum COLOR{red, white, blue};


class Nwindow{
	int pos_x, pos_y, MAX_X = 0;
	int prev_x,prev_y, MAX_Y =0 ;
  WINDOW* winptr;

    public:
       
       Nwindow();
       Nwindow(int len_y, int len_x, int x, int y);

       //template<typename T,typename U>void move(T y, U x);
       //template<typename T>void move_over(T x, T y);

       template<typename T, typename U> void move(T y, U x){
         pos_y = int(y)%MAX_Y; pos_x = int(x)%MAX_X;
         wmove(winptr,pos_y,pos_x);
         wrefresh(winptr);
       
       }
       
       template<typename T> void move_over(T dy,T dx){
         pos_y += int(dy); pos_x += int(dx);
         wmove(winptr,pos_y,pos_x);
       }
      /*
       template<typename T> void print_color(T x, COLOR c ) {
           cout <<"Variable " <<typeid(T).name() << " is not supported" << endl;
       }*/
       void print_color(ifstream& file, COLOR c);
       void print_color(string str, COLOR c);
       void print_color(double* da, COLOR c, int startp);
       void clear();

    private: 
    	 
       void print_line(string line, COLOR c);
       void initialize_colors();
       void set_bkg_color(COLOR c);
       void reset_color(COLOR c);
       void set_color(COLOR c);
       int get_start(string str);
       int get_end(string str);

        
};

#endif
 
