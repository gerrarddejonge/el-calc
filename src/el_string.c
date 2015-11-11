/*
 * File:       el_string.c
 * Copyright:  (c)2015  Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:    GPLv2 (see file COPYING)
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "el_defs.h"
#include "el_string.h"


/// 
///
///
///
void clearMarker(char * s, char marker)
{
	char * pos;
	
	if ((pos = strchr(s, marker)) != NULL) {
		*pos = '\0';
	}
}


///  
/// Remove all leading spaces of string
/// Returns pointer to string
///
char * leftTrim(char * str)
{
	char * t;
	int i = 0;

	while (isspace(str[i]))
		i++;
	t = xStrDup(&str[i]);
	strcpy(str, t);
	if (t) {
		free(t);
	}
	return str;
}


/// 
/// Remove all trailing spaces of string str
/// Returns pointer to string
///
char * rightTrim(char * str)
{
	int len = strlen(str) - 1;

	while (isspace(str[len]) && len >= 0)
		str[len--] = '\0';
	return str;
}


/// 
/// Remove all leading and trailing spaces of string str
/// Returns pointer to string
///
char * trim(char * str)
{
	return leftTrim(rightTrim(str));
}


/// 
/// Alloc memory for size chars
/// Return pointer to allocated memory or
/// quit if allocation went wrong
///
void * xMalloc(const size_t size)
{
	void * temp;

	if ((temp = malloc(size)) == NULL) {
		printf("Out of memory\n");
		exit(EXIT_FAILURE);
	}
	return temp;
}
///
/// Allocate memory for count elements of size chars and set them to 0
/// Return pointer to allocated memory or 
/// quit if allocation went wrong
///
void * xCalloc(const size_t count, const size_t eltsize)
{
	void * temp = xMalloc(count* eltsize);
    memset (temp, 0, count * eltsize);
  	return temp;
}


/// 
/// Allocates new string and copies string str to it
/// Return pointer to allocated memory or quit 
/// if allocation went wrong
///
void * xStrDup(const char * str)
{
	char * temp;

	if ((temp = (char *) malloc(strlen(str)+1)) == NULL) {
		printf("Out of memory\n");
		exit(EXIT_FAILURE);
	}
	strcpy(temp, str);
	return temp;
}


/// 
/// 
///
///
char loCase(const char c)
{
	if ('A' <= c && c <= 'Z') {
		return c -'A' + 'a';
	}
	return c;
}


/// 
///
///
///
char upCase(const char c)
{
	if ('a' <= c && c <= 'z') {
		return c - 'a' + 'A';
	}
	return c;
}


/// 
///
///
///
void upperCase(char * str)
{
	if (str) {
		for ( ; *str != '\0'; str++) {
			*str = upCase(*str);
		}
	}
}


/// 
///
///
///
void lowerCase(char * str)
{
	if (str) {
		for ( ; *str != '\0'; str++) {
			*str = loCase(*str);
		}
	}
}

void strTransform(char * line)
{
	char * str;
	char   newstr[LINESIZE] = {""};
	
	while ((str = strtok(line, " ")) != NULL) {
		strcat(newstr, str);
	}
	
	strcpy(line, newstr);
	lowerCase(line);
}


bool isEmpty(const char line[])
{
	return line[0] == '\0' ? true : false;
}

// end of el_string.c
