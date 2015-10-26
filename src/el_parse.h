/*
 * File:      el_parse.h
 * Copyright: (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:   GPLv2 (see file COPYING)
 *
 */


#ifndef EL_PARSE_H
#define EL_PARSE_H

#include "el_items.h"

elState parseName(char * line, Item * item);
elState parseID(char * line, Item * item, int ln);
elState parseCompound(char * line, Item * item, int ln);
elState parseElement(char * line, Item * item, int ln, int eltcount);




#endif  /*  EL_PARSE_H  */
