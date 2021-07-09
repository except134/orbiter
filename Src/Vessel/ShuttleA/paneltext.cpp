// ==============================================================
//                 ORBITER MODULE: ShuttleA
//                  Part of the ORBITER SDK
//          Copyright (C) 2001-2016 Martin Schweiger
//                   All rights reserved
//
// paneltext.cpp
// Text output into panel elements
// ==============================================================

#define STRICT 1
#define __PANELTEXT_CPP
#include "paneltext.h"

int small_font_xpos[256] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0/*(*/,0/*)*/,0/***/,0/*+*/,0/*,*/,0/*-*/,70/*.*/,0/*/*/,
	78/*0*/,83/*1*/,88/*2*/,94/*3*/,100/*4*/,105/*5*/,111/*6*/,117/*7*/,123/*8*/,129/*9*/,0/*:*/,0/*;*/,0/*<*/,0/*=*/,0/*>*/,0/*?*/,
	0/*@*/,178/*A*/,185/*B*/,191/*C*/,199/*D*/,206/*E*/,212/*F*/,218/*G*/,226/*H*/,233/*I*/,237/*J*/,243/*K*/,250/*L*/,256/*M*/,264/*N*/,271/*O*/,
	279/*P*/,285/*Q*/,293/*R*/,300/*S*/,306/*T*/,313/*U*/,320/*V*/,326/*W*/,335/*X*/,341/*Y*/,348/*Z*/,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

int small_font_width[256] = {   // character widths in texture
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,6/*(*/,0/*)*/,0/***/,0/*+*/,0/*,*/,0/*-*/,2/*.*/,0/*/*/,
	5/*0*/,5/*1*/,5/*2*/,5/*3*/,5/*4*/,5/*5*/,5/*6*/,5/*7*/,5/*8*/,5/*9*/,0/*:*/,0/*;*/,0/*<*/,0/*=*/,0/*>*/,0/*?*/,
	0/*@*/,5/*A*/,5/*B*/,5/*C*/,5/*D*/,5/*E*/,5/*F*/,6/*G*/,5/*H*/,2/*I*/,4/*J*/,5/*K*/,4/*L*/,6/*M*/,5/*N*/,6/*O*/,
	5/*P*/,6/*Q*/,5/*R*/,5/*S*/,6/*T*/,5/*U*/,5/*V*/,8/*W*/,5/*X*/,6/*Y*/,5/*Z*/,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

int small_font_ypos[2] = {35,43};
int small_font_height = 8;

void BltStr (SURFHANDLE tgt, SURFHANDLE src, int x, int y, const char *newstr, char *oldstr, DWORD style)
{
	if (newstr && oldstr && !strcmp (newstr, oldstr)) return; // nothing to do
	int w;
	bool align_right = ((style & ALIGN_RIGHT) > 0);

	if (oldstr) { // erase the old string
		w = 0;
		for (char *c = oldstr; *c; c++) w += small_font_width[*c];
		if (w) oapiColourFill (tgt, 0, (align_right ? x-w:x), y, w, small_font_height);
	}
	if (newstr) { // write new string
		if (align_right)
			for (const char *c = newstr; *c; c++) x -= small_font_width[*c];
		for (const char *c = newstr; *c; c++) {
			w = small_font_width[*c];
			oapiBlt (tgt, src, x, y, small_font_xpos[*c], small_font_ypos[*c <= 90 ? 0:1], w, small_font_height);
			x += w;
		}
	}
	strcpy (oldstr, newstr);
}