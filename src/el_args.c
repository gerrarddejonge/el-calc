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
	"el-calc v0.1";

const char * argp_program_bug_address = 
	"<development.gdj@netvisit.nl>";

static char pdoc[] =
	"el-calc  Calculator for el recipies";

static struct argp_option options[] = {
// long option, short option, option argument, option flags, help info, group idenifier
	
	{"item", 'i', "\"itemname\"", 0, "item name or id.", 0},
	{"amount", 'a', "value", 0, "amount of items; default = 1", 0},
	{"lookup", 'l', NULL, 0, "lookup item", 0},
	{NULL, 0, NULL, 0, NULL, 0}
};

static struct argp argp = {options, el_arg_parser, NULL, pdoc, NULL, NULL, NULL};


error_t el_arg_parser(int key, char * arg, struct argp_state * state)
{
	pstate_t * pstate = state->input;

	switch (key) {
		case 'i':
//			printf("arg is %s\n", arg);
			strcpy(pstate->itemname, arg);
//			upperCase(pstate->itemname);
			break;
		case 'a':
//			printf("arg is %s\n", arg);
			pstate->amount = strtol(arg, NULL, 10);
			break;
		case 'l':
			pstate->lookup = true;
			break;
		default:
			break;
	}
	return 0;
}


int get_args(int argc, char ** argv, pstate_t * pstate)
{
	argp_parse(&argp, argc, argv, 0, 0, pstate);
	return 0;
}









/*  end of a65_args.c  */

