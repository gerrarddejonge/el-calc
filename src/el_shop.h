/*
 * File:       el_shop.h
 * Copyright:  (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:    GPLv2 (see file COPYING)
 *
 */

#ifndef _EL_SHOP_H
#define _EL_SHOP_H

#include "el_defs.h"

enum elState buildShoppingList(struct List * list, struct ShoppingCart * cart, char itemname[], int amount);
enum elState addToShoppingList(struct ShoppingCart * cart, struct Item * item, int amount);
void    printShoppingList(struct ShoppingList * shop);
//elState addToNeededList(NeededItems * list, NeededItems * item);
void freeCart(struct ShoppingCart * cart);


#endif // _EL_SHOP_H
