/*
 * File:       el_main.c
 * Copyright:  (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:    GPLv2 (see file COPYING)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "el_defs.h"
#include "el_args.h"
#include "el_items.h"
#include "el_shop.h"
#include "el_path.h"


int main(int argc, char * argv[])
{
	PState       pstate = {"Unknown", 1, false, "", false, -1};
	List         itemlist = {NULL, NULL};
	ShoppingCart cart = {NULL, NULL};
	char         path[PATHSIZE];
	Item *       temp;
	
//	printf("Pstate->name: %s, Pstate->amount: %d\n", pstate.itemname, pstate.amount);
	if (argc > 1) {
		get_args(argc, argv, &pstate);
		getFilePath(path, &pstate);
		
		if (loadAllItems(&itemlist, path) == EL_FAIL) {
			printf("Could not read the items.\n");
			exit(EXIT_FAILURE);
		}
		
		if (pstate.itemid >= 0) {
			if (( temp = findItemId(itemlist.head, pstate.itemid)) != NULL) {
				strcpy(pstate.itemname, temp->name);
			}
		}

/// If we have a lookup or search request, execute it and exit program
		if (pstate.lookup) {
			printf("Looking for %s.\n", pstate.itemname);
			lookup(&itemlist, pstate.itemname);
			exit(EXIT_SUCCESS);
		} else if (pstate.search) {
			printf("Searching for %s.\n", pstate.itemname);
			searchItem(&itemlist, pstate.itemname);
			exit(EXIT_SUCCESS);
		}
		
		printf("\nCalculations for %d %s\n\n", pstate.amount, pstate.itemname);
		
		printf("Filling shopping cart.\n\n");
		
		if (buildShoppingList(&itemlist, &cart, pstate.itemname, pstate.amount) == EL_FAIL) {
			printf("Failure to build shopping list.\n");
			exit(EXIT_FAILURE);
		}
		
		printf("\n\nTotals for %d %s\n\n", pstate.amount, pstate.itemname);
		
		printShoppingList(cart.head);
		
		
	} else {
		printf("\nMissing parameters. \nUse: \n\t%s --help\nfor correct syntax\n\n", argv[0]);
	}
	
	return 0;
}



// end of el_main
