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
/// Returns pointer to string, which should be 
/// the same as the original
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
/// Returns pointer to string, which should be 
/// the same as the original
///
char * rightTrim(char * str)
{
	int pos;
	
	pos = strlen(str) - 1;
	while (isspace(str[pos]) && pos >= 0) {
		str[pos] = '\0';
		pos--;
	}
	return str;
}


/// 
/// Remove all leading and trailing spaces of string str
/// Returns pointer to string, which should be 
/// the same as the original
///
char * trim(char * str)
{
	return leftTrim(rightTrim(str));
}


/// 
/// Alloc memory for size chars
/// Return pointer to allocated memory or 
/// exits on failure
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
/// exits on failure
///
void * xCalloc(const size_t count, const size_t eltsize)
{
	void * temp = xMalloc(count * eltsize);
	memset (temp, 0, count * eltsize);
  	return temp;
}


/// 
/// Allocates new string and copies string str to it
/// Return pointer to allocated memory or exit 
/// if allocation went wrong
///
void * xStrDup(const char * str)
{
	char * temp;

	if ((temp = calloc(strlen(str)+1, 1)) == NULL) {
		printf("Out of memory\n");
		exit(EXIT_FAILURE);
	} else {
		strcpy(temp, str);
	}
	return temp;
}


/// 
/// 
///
///
char loCase(const char c)
{
	return ('A' <= c && c <= 'Z') ? c -'A' + 'a' : c;
}


/// 
///
///
///
char upCase(const char c)
{
	return ('a' <= c && c <= 'z') ? c - 'a' + 'A' : c;
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


///
/// Remove all spaces from a given string
///
///
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

/// Check if a line is isEmpty
/// Return true if empty otherwise return false
bool isEmpty(const char const * line)
{
	return *line == '\0' ? true : false;
}

// end of el_string.c
