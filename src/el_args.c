/*
 * File:      el_args.c
 * Copyright: (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:   GPLv2 (see file COPYING)
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argp.h>

#include "el_defs.h"
#include "el_args.h"
#include "el_string.h"


const char * argp_program_version = 
	"el-calc v0.2";

const char * argp_program_bug_address = 
	"<development.gdj@netvisit.nl>";

static char pdoc[] =
	"el-calc  Calculator for el recipies";

static struct argp_option options[] = {
// long option, short option, option argument, option flags, help info, group identifier
	
	{"item", 'i', "\"itemname\"", 0, "item name.", 0},
	{"amount", 'a', "value", 0, "amount of items; default = 1", 0},
	{"lookup", 'l', "\"itemname\"", 0, "lookup item", 0},
	{"directory", 'd', "\"directory/<filename>\"", 0, "path to item list; default = items.lst", 0},
	{"search", 's', "\"text\"", 0, "Search for items containing text", 0},
	{"number", 'n', "ID number", 0, "item ID", 0},
	{NULL, 0, NULL, 0, NULL, 0}
};

static struct argp argp = {options, el_arg_parser, NULL, pdoc, NULL, NULL, NULL};


error_t el_arg_parser(int key, char * arg, struct argp_state * state)
{
	PState * pstate = state->input;
	int size;
	
	switch (key) {
		case 'i':
			strncpy(pstate->itemname, arg, LINESIZE);
			pstate->itemname[LINESIZE - 1] = '\0';
			
			break;
		case 'a':
			pstate->amount = strtol(arg, NULL, 10);
			break;
		case 'l':
			pstate->lookup = true;
			size = strlen(arg);
			strncpy(pstate->itemname, arg, size);
			pstate->itemname[size] = '\0';
			break;
		case 'd':
			size = strlen(arg);
			strncpy(pstate->path, arg, size);
			pstate->path[size] = '\0';
			break;
		case 's':
			pstate->search = true;
			size = strlen(arg);
			strncpy(pstate->itemname, arg, size);
			pstate->itemname[size] = '\0';
			break;
		case 'n':
			pstate->itemid = strtol(arg, NULL, 10);
			break;
		default:
			break;
	}
	return 0;
}


int get_args(int argc, char ** argv, PState * pstate)
{
	argp_parse(&argp, argc, argv, 0, 0, pstate);
	return 0;
}



/*  end of el_args.c  */

