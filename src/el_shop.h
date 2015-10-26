/*
 * File:       el_shop.h
 * Copyright:  (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:    GPLv2 (see file COPYING)
 *
 */

#ifndef _EL_SHOP_H
#define _EL_SHOP_H

#include "el_defs.h"

elState buildShoppingList(List * list, ShoppingCart * cart, char itemname[], int amount);
elState addToShoppingList(ShoppingCart * cart, Item * item, int amount);
void    printShoppingList(ShoppingList * shop);





#endif // _EL_SHOP_H
