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



int main(int argc, char * argv[])
{
	pstate_t pstate = {"Unknown", 1, false};
	List itemlist = {NULL, NULL};
	ShoppingCart cart = {NULL, NULL};
	
//	printf("Pstate->name: %s, Pstate->amount: %d\n", pstate.itemname, pstate.amount);
	if (argc > 1) {
		get_args(argc, argv, &pstate);
        printf("\nCalculations for %d %s\n\n", pstate.amount, pstate.itemname);

		if (loadAllItems(&itemlist) == EL_FAIL) {
			printf("Could not read the items.\n");
			exit(EXIT_FAILURE);
		}
		if (pstate.lookup) {
			printItems(&itemlist);
			exit(EXIT_SUCCESS);
		}
		
		printf("Filling shoppin cart.\n\n");

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


