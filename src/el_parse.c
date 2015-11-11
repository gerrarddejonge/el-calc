/*
 * File:      el_parse.c
 * Copyright: (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:   GPLv2 (see file COPYING)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "el_defs.h"
#include "el_string.h"
#include "el_parse.h"
#include "el_items.h"

const char undefline[] = "%s: Line %d. Item is undefined\n";

elState parseName(char * line, Item * item)
{
	strncpy(item->name, trim(line), LINESIZE);
	lowerCase(item->name);
	item->name[LINESIZE - 1] = '\0';
	item->marker |= NAMEMARKER;

	return EL_SUCCESS;
}


elState parseID(char * line, Item * item, int ln)
{
	if (sscanf( line, "%d", &item->id) < 1) {
		printf("Line: %d. Missing id. Setting to 0\n", ln);
		item->id = 0;
	}
	item->marker |= IDMARKER;
	
	return EL_SUCCESS;
}


elState parseCompound(char * line, Item * item, int ln)
{
	elState res = EL_SUCCESS;
	int compound = 0;

	if (sscanf(line, "%d", &compound) < 1) {
		printf("Line: %d. Missing compound value. Setting to false\n", ln);
		item->compound = false;
		res = EL_CMPLTD;
	} else {
		item->compound = (bool) compound;
		item->marker |= COMPOUNDMARKER;
		if (!item->compound) {
			res = EL_CMPLTD;
		}
	}
	return res;
}

elState parseElement(char * line, Item * item, int ln, int eltcount)
{
	elState res = EL_SUCCESS;
	int  id;
	int  amount;
	
	switch (sscanf(line, "%d %d", &id, &amount)) {
		case 0:
			printf("Line: %d. Missing item for recipe.\n", ln);
			break;
		case 1:
			if (id == 0) {
				res = EL_CMPLTD;
			}else {
				printf("Line: %d. Incomplete item for recipe\n", ln);
			}
			break;
		case 2:
			if (eltcount < MAXITEMS) {
				item->element[eltcount].id = id;
				item->element[eltcount].amount = amount;
			} else {
				printf("Line: %d. Maximum items for recipe reached.\n", ln);
				res = EL_CMPLTD;
			}	
			break;
		default:
			break;
	}

	return res;
}



// end of el_parse.c
