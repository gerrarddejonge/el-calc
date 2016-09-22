/*
 * File:      el_defs.h
 * Copyright: (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:   GPLv2 (see file COPYING)
 *
 */

#ifndef EL_DEFS_H
#define EL_DEFS_H

#include <stdbool.h>

#ifdef DEBUG
	#define __DEBUGPRINT__	printf("%s:%d %s\n", __FILE__, __LINE__, __FUNCTION__)
#endif

#ifdef DEBUG
	#define __DEBUGP__(s1, p1) { printf(s1, p1); }
#else
	#define __DEBUGP__(s1, p1) { }
#endif
	
#define MAXITEMS 6
#define LINESIZE 256
#define PATHSIZE 1024
#define LINKSIZE 4092
#define ITEMFILENAME "items.lst"
#define ENVNAME "ELCALC"


#define IDMARKER       0x01
#define NAMEMARKER     0x02
#define COMPOUNDMARKER 0x04


// structure is filled with CLI parameters
struct PState {
	char  itemname[LINESIZE];
	int   amount;
	bool  lookup;
	char  path[PATHSIZE];
	bool  search;
	int   itemid;
};


struct Recipe {
	int    id;
	int    amount;
};


struct NeededItems {
	struct NeededItems * next;
	int  id;
	char name[LINESIZE];
	int  amount;
};

	
struct ShoppingList {
	struct ShoppingList * next;	
	int  id;
	char name[LINESIZE];
	int  amount;
};

struct ShoppingCart {
	struct ShoppingList * head;
	struct ShoppingList * tail;
};


struct Item {
	struct Item * right;
	int  marker;				// Keeps flags about which information has` been read from file id: 0x01, name: 0x02, compound: 0x04
	int  id;
	char name[LINESIZE];
	bool compound;
	struct Recipe   element[MAXITEMS];
};


struct List {
	struct Item * head;
	struct Item * tail;
};


enum elState {
	EL_SUCCESS,
	EL_FAIL,
	EL_IOERR,
	EL_EOF,
	EL_CMPLTD
};


#endif  /*  EL_DEFS_H  */
