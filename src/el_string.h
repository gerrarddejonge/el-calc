/*
 * File:       el_string.h
 * Copyright:  (c)2015  Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:    GPLv2 (see file COPYING)
 *
 */

#ifndef EL_STRING_H
#define EL_STRING_H

void   clearMarker(char * s, char marker);
char * leftTrim(char * str);
char * rightTrim(char * str);
char * trim(char * str);
void * xMalloc(const size_t size);
void * xCalloc(const size_t count, const size_t eltsize);
void * xStrDup(const char * str);
char   upCase(const char c);
char   loCase(const char c);
void   upperCase(char * str);
void   lowerCase(char * str);


#endif  // EL_STRING_H
