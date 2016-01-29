#ifndef NWINDOW_H
#define NWINDOW_H "nwindow.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define MAXCHAR 1024

extern const char pi_art_1[35];
extern const char pi_art_2[365];

typedef struct _nwindow{
	WINDOW* winptr;
	int MAX_X;
	int MAX_Y;
} nwindow;

typedef struct _nscreen{
     int numwindows;
     SCREEN* scrptr;
     nwindow** wins;

} nscreen;


nscreen* create_nscreen(int numwindows);
void init_nscreen(FILE* outputfp, nscreen* scr);
void clean_nscreen(nscreen* scr);


void piheader_to_win(nscreen* scr);
void string_to_win(nscreen* scr,int winnum,char* str);
void carray_to_win(nscreen* scr,int winnum, int p, int size,double* buf);
void file_to_win(nscreen* scr,int winnum, char* filename);

double buf_get_max(double* buffer,int length);

#endif
