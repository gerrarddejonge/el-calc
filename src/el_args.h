/*
 * File:      el_args.h
 * Copyright: (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:   GPLv2 (see file COPYING)
 *
 */


#ifndef EL_ARGS_H
#define EL_ARGS_H

#include <argp.h>

#include "el_defs.h"

int get_args(int argc, char ** argv, pstate_t * pstate);
error_t el_arg_parser(int key, char * arg, struct argp_state * state);
int parse_args(int argc, char ** argv);

#endif // EL_ARGS_H
