/*
 * File:       el_shop.c
 * Copyright:  (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:    GPLv2 (see file COPYING)
 *
 */


#include <stdio.h>

#include "el_defs.h"
#include "el_shop.h"
#include "el_items.h"
#include "el_string.h"

elState buildShoppingList(List * list, ShoppingCart * cart, char itemname[], int amount)
{
	Item * found;
	Item * part;
	
	found = findItemName(list->head, itemname);
	if ( !found ) {
		printf("Unknown item: %s\n", itemname);
		return EL_FAIL;
	}
	
//	printf("SL: Adding %d %s to shopping list.\n", amount, itemname);
	
	if ( !found->compound ) {
		addToShoppingList(cart, found, amount);
		return EL_SUCCESS;
	} else {
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


ShoppingList * isInCart(ShoppingList * item, int id)
{
	for ( ; item && item->id != id; item = item->next)
		;
	return item;
}

elState addToShoppingList(ShoppingCart * cart, Item * item, int amount)
{
	ShoppingList * shopitem;
	ShoppingList * temp;
	
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


void printShoppingItem(ShoppingList * item)
{
	printf("%d %s\n", item->amount, item->name);
}

void    printShoppingList(ShoppingList * shop)
{
	for ( ; shop; shop = shop->next) {
		printShoppingItem(shop);
	}
}



// end of file el_shop.c
