/*
 * File:      el_items.c
 * Copyright: (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:   GPLv2 (see file COPYING)
 *
 */


#include <stdio.h>
#include <stdlib.h>

#include "el_defs.h"
#include "el_items.h"
#include "el_parse.h"
#include "el_string.h"

#define COMMENTCHAR '#'


enum elState getValidLine(char * line, FILE * stream, int * linenumber)
{
	char * result;
	int    valid = 0;
	
	while (!valid) {
		if ((result = fgets(line, LINESIZE, stream)) != NULL) {
			// Ok we got a line, lets clean it up by  removing all comments 
			// indicated by COMMENTCHAR and trimming all leading and trailing spaces.
			clearMarker(line, COMMENTCHAR);
			trim(line);

			(*linenumber)++;
			if (line[0] != '\0') {
				valid = 1;
			}
		} else {
			return EL_FAIL;
		} 
	}
	return EL_SUCCESS;
}


enum elState loadAllItems(struct List * list, char filepath[]) 
{
	FILE * itemfile;
	struct Item * item = NULL;
	struct Item   temp;
	int    linenumber = 0;
	
	if ((itemfile = fopen(filepath, "r")) != NULL) {
		printf("Loading item list.\n\n");

		initItem(&temp);
		while ((loadSingleItem(itemfile, &temp, &linenumber)) != EL_EOF) {
			if ((item = cloneItem(&temp)) != NULL) {
				addItem(list, item);
				initItem(&temp);
			} else {
				printf("ERROR: Could not create a new item\n");
				break;
			}
		}

		fclose(itemfile);
		return EL_SUCCESS;
	} else {
		return EL_FAIL;
	}
}


enum elState loadSingleItem(FILE * stream, struct Item * item, int * linenumber)
{
	char line[LINESIZE];
	enum elState res = EL_SUCCESS;
	int elementcount = 0;
	enum elState state;
	
	while ( ((state = getValidLine(line, stream, linenumber)) == EL_SUCCESS) ) {
		
		switch (getHead(line)) {
			case 'N':
				res = parseName(&line[2], item);
				break;
			case 'I':
				res = parseID(&line[2], item, *linenumber);
				break;
			case 'C':
				res = parseCompound(&line[2], item, *linenumber);
				break;
			case 'E':
				res = parseElement(&line[2], item, *linenumber, elementcount);
				elementcount++;
				break;
			case '0':
				res = EL_CMPLTD;
				break;
			case 'X':
				printf("Unknown line type: %s\nOn line: %d.\n", line, *linenumber);
				break;
			default:
				break;
		}
		if (res == EL_CMPLTD) {
			return EL_SUCCESS;
		}
	}
	return EL_EOF;
}




void initItem(struct Item * item)
{
	item->marker = 0;
	item->id = 0;
	item->compound = 0;
	strcpy(item->name, "");
	item->right = NULL;
	for (int i = 0; i < MAXITEMS; i++) {
		item->element[i].id = 0;
		item->element[i].amount = 0;
	}
}
	
	
struct Item * cloneItem(const struct Item * item)
{
	struct Item * clone = NULL;
	
	if (item != NULL) {
		if ((clone = calloc(1, sizeof(*clone))) != NULL) {
			memcpy(clone, item, sizeof(*clone));
		}
	}
	return clone;
}


struct Item * addItem(struct List * list, struct Item * item)
{
	struct Item * found = NULL;
	
	if ((found = findItemId(list->head, item->id)) == NULL) {
		if (list->head == NULL) {
			list->head = item;
			list->tail = item;
		} else {
			list->tail->right = item;
			list->tail = item;
		}
		return item;
	}
	return NULL;
}


struct Item * findItemId(struct Item * head, int id)
{
	for ( ; head && (head->id != id); head = head->right) 
		;
	return head;
}


struct Item * findItemName(struct Item * head, char name[])
{
	for( ; head && strcmp(head->name, name) != 0; head = head->right)
		;
	return head;	
}


void showItem(struct Item * item)
{
	if (item) {
		printf("\n");
		printf("Id:       %d\n", item->id);
		printf("name:     %s\n", item->name);
		printf("compound: %d\n", item->compound);
		if (item->compound) {
			for (int i = 0; i < MAXITEMS; i++) {
				if (item->element[i].id != 0) {
					printf("part %d:   %d  %d\n", i + 1, item->element[i].id, item->element[i].amount);
				}
			}
		}
	}
}


void printItems(struct List * list)
{
	struct Item * item;
	
	for (item = list->head; item; item = item->right) {
		showItem(item);
	}
}


char getHead(char * line) 
{    
    if (line[0] == '0' || (line[1] == ':' && (line[0] == 'N' || line[0] == 'I' || line[0] == 'C' || line[0] == 'E'))) {
        return line[0];
    } else {
		return 'X';
	}
}
    

void lookup(struct List * list, char name[])
{
	struct Item * item;
	
	if (strcmp("Unknown", name) != 0) {
		item = findItemName(list->head, name);
		if ( item != NULL ) {
			showItem(item);
		} else {
			printf("Can't find item: %s\n", name);
		}
	} else {
		printItems(list);
	}
}

void searchItem(struct List * list, char name[])
{
	struct Item * scan;
	
	if (strcmp("Unknown", name) != 0) {
		for ( scan = list->head; scan; scan = scan->right) {
			if ( strstr(scan->name, name ) != NULL ) {
				showItem(scan);
			} 
		}
	} else {
		printItems(list);
	}
}

void freeItemList(struct List * list)
{
	struct Item * temp;
	struct Item * head = list->head;
	
	while (head != NULL) {
		temp = head;
		head = head->right;
		free(temp);
	}
	list->head = NULL;
	list->tail = NULL;
}
   
        
// end of el_items.c        
