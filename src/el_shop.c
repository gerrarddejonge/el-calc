/*
 * File:       el_shop.c
 * Copyright:  (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:    GPLv2 (see file COPYING)
 *
 */


#include <stdio.h>
#include <stdlib.h>

#include "el_defs.h"
#include "el_shop.h"
#include "el_items.h"
#include "el_string.h"

enum elState buildShoppingList(struct List * list, struct ShoppingCart * cart, char itemname[], int amount)
{
	struct Item * found;
	struct Item * part;
	
	found = findItemName(list->head, itemname);
	if ( !found ) {
		printf("Unknown item: %s\n", itemname);
		return EL_FAIL;
	}
	
	if ( !found->compound ) {
		addToShoppingList(cart, found, amount);
		return EL_SUCCESS;
	} else {
//		addTONeededList(NeededItems, found);
		for (int i = 0; i < MAXITEMS && found->element[i].id != 0; i++) {
			part = findItemId(list->head, found->element[i].id);
			if (part) {
				buildShoppingList(list, cart, part->name, amount * found->element[i].amount);
			} else {
				printf("Unknown item: %d\n", found->element[i].id);
			}
		}			
	}
	return EL_SUCCESS;
}

/*
NeededItems * isInNeeded(NeededItems * item, int id)
{
	for ( ; item && item->id != id; item = item->next)
		;
	return item;
}


elState addToNeededList(NeededItems * list, NeededItems * item)
{
	return EL_SUCCESS;
}
*/

struct ShoppingList * isInCart(struct ShoppingList * item, int id)
{
	for ( ; item && item->id != id; item = item->next)
		;
	return item;
}


enum elState addToShoppingList(struct ShoppingCart * cart, struct Item * item, int amount)
{
	struct ShoppingList * shopitem;
	struct ShoppingList * temp;
	
	printf("Adding %d %s to shoppinglist.\n", amount, item->name);
	
	shopitem = xCalloc(1, sizeof ( *shopitem));
	
	strcpy(shopitem->name, item->name);
	shopitem->id = item->id;
	shopitem->amount = amount;
	
	if (cart->head == NULL) {
		cart->head = shopitem;
		cart->tail = cart->head;
	} else {
		if ((temp = isInCart(cart->head, shopitem->id)) == NULL) {
			cart->tail->next = shopitem;
			cart->tail = shopitem;
		} else {
			temp->amount += shopitem->amount;
		}
	}
	
	return EL_SUCCESS;
}


void printShoppingItem(struct ShoppingList * item)
{
	printf("%d %s\n", item->amount, item->name);
}

void    printShoppingList(struct ShoppingList * shop)
{
	for ( ; shop; shop = shop->next) {
		printShoppingItem(shop);
	}
}

void freeCart(struct ShoppingCart * cart)
{
	struct ShoppingList * temp;
	struct ShoppingList * head = cart->head;

	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
	cart->head = NULL;
	cart->tail = NULL;
}
	
// end of file el_shop.c
