/*
 * File:      el_path.h
 * Copyright: (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:   GPLv2 (see file COPYING)
 *
 */


#ifndef EL_PATH_H
#define EL_PATH_H

#include <stdbool.h>

#include "el_defs.h"

bool getArgPath(char path[], PState * pstate);
bool getEnvPath(char path[]);
bool getLocalPath(char path[]);
void getFilePath(char path[], PState * pstate);



#endif  // EL_PATH_H
