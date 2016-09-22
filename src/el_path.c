/*
 * File:      el_path.c
 * Copyright: (c) 2015 Gerrard de Jonge <development.gdj@netvisit.nl>
 * License:   GPLv2 (see file COPYING)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
//#include <libgen.h>

#include "el_defs.h"
#include "el_string.h"
#include "el_path.h"



// if the path to the data file is to long pathToLong will be called.
void pathToLong(void)
{
	printf("File path is to long. Closing application.\n");
	exit(EXIT_FAILURE);
}

bool testPath(char path[])
{
	FILE * testfile = fopen(path, "r");
	
	if (testfile != NULL) {
		fclose(testfile);
		return true;
	}
	return false;
}
	

// getArgPath will look for a filepath in commandline argument list
// and return the filepath in variable path and true if a valid file 
// is found
bool getArgPath(char path[], struct PState * pstate)
{
	char temp[PATHSIZE];
	int  len = strlen(pstate->path); 
	
	if (isEmpty(pstate->path)) {
		return false;
	}
	
	strcpy(temp, pstate->path);
	
	if (temp[len - 1] == '/') {
		if ( strlen(ITEMFILENAME) + len > PATHSIZE) {
			pathToLong();
		}
		strcat(temp, ITEMFILENAME);
	}
	strcpy(path, temp);

	return true;
}


// getEnvPath will look for a file path in an environment variable
// called ELCALC and return the filepath in variable path and true 
// if a valid file is found
bool getEnvPath(char path[])
{
	char   temp[PATHSIZE] = {'\0'};
	int    len;
	char * envv;
	
	if ((envv = getenv(ENVNAME)) != NULL) {
		strcat(temp, envv);
		len = strlen(temp);
		
		if (temp[len - 1] == '/') {
			if ( strlen(ITEMFILENAME) + len >= PATHSIZE) {
				pathToLong();
			}
			strcat(temp, ITEMFILENAME);
		}

	} else {
		return false;
	}
	
	strcpy(path, temp);
	return true;
}

/*
 * The code for the getExePath is based on code written by 
 * Nicolai Haehnle <prefect_@gmx.net>
 */
 bool getExePath(char path[])
{
	char linkname[PATHSIZE]; /* /proc/<pid>/exe */
	pid_t pid;
	int ret;
	
	/* Get our PID and build the name of the link in /proc */
	pid = getpid();
	
	if (snprintf(linkname, sizeof(linkname), "/proc/%d/exe", pid) == 0) {
		printf("Failure to find executable path.\n");
		exit(EXIT_FAILURE);
	}
	
	/* Now read the symbolic link */
	ret = readlink(linkname, path, PATHSIZE);
	
	/* In case of an error, leave the handling up to the caller */
	if (ret == -1) {
		path[0] = '\0';	
		return false;
	}
	/* Report insufficient buffer size */
	if (ret >= PATHSIZE) {
		errno = ERANGE;
		path[0] = '\0';
		return false;
	}
	
	/* Ensure proper NUL termination */
	path[ret] = '\0';
	
	/* removing program name */
	for ( ; path[ret] != '/'; ret--) {
		path[ret] = '\0';
	}

	return true;
}


// getLocalPath will try looking for a file in the same directory as where
// the executable is located and return the filepath in variable path and 
// true if a valid file is found
bool getLocalPath(char path[])
{
	if (getExePath(path)) {
		if (strlen(path) + strlen(ITEMFILENAME) < PATHSIZE) {
			strcat(path, ITEMFILENAME);
			return true;
		} else {
			pathToLong();
		}
	}

	return false;
}


//getFilePath will look for a valid data file in several places
void getFilePath(char path[], struct PState * pstate)
{
	if (!getArgPath(path, pstate)) {
		if ( ! getEnvPath(path)) {
			if ( ! getLocalPath(path)) {
				strcat(path, ITEMFILENAME);
			}
		}
	}
	if (! testPath(path)) {
		printf("Could not find a valid data file at %s\n", path);
		exit(EXIT_FAILURE);
	}
}





// end of el_path.c
