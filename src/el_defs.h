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
#define LINESIZE 100


#define IDMARKER       0x01
#define NAMEMARKER     0x02
#define COMPOUNDMARKER 0x04

// structure is filled with CLI parameters
struct pstate {
	char  itemname[LINESIZE];
	int   amount;
	bool  lookup;
};
typedef struct pstate pstate_t;


struct recipe {
	int    id;
	int    amount;
};

typedef struct recipe Recipe;


struct shoppinglist {
	struct shoppinglist * next;	
	int  id;
	char name[LINESIZE];
	int  amount;
};

typedef struct shoppinglist ShoppingList;

struct shoppingcart {
	ShoppingList * head;
	ShoppingList * tail;
};

typedef struct shoppingcart ShoppingCart;


struct item {
	struct item * left;
	struct item * right;
	int      marker;				// Keeps flags about which information has` been read from file id: 0x01, name: 0x02, compound: 0x04
	int      id;
	char     name[LINESIZE];
	bool     compound;
	Recipe   element[MAXITEMS];
};

typedef struct item   Item;



struct list {
	Item * head;
	Item * tail;
};

typedef struct list List;



enum elstate {
	EL_SUCCESS,
	EL_FAIL,
	EL_IOERR,
	EL_EOF,
	EL_CMPLTD
};

typedef enum elstate elState;



#endif  /*  EL_DEFS_H  */
