/*
 * File:      el_parse.h
 * Copyright: (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:   GPLv2 (see file COPYING)
 *
 */


#ifndef EL_PARSE_H
#define EL_PARSE_H

#include "el_items.h"

enum elState parseName(char * line, struct Item * item);
enum elState parseID(char * line, struct Item * item, int ln);
enum elState parseCompound(char * line, struct Item * item, int ln);
enum elState parseElement(char * line, struct Item * item, int ln, int eltcount);




#endif  /*  EL_PARSE_H  */
