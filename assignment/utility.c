#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>                             // for chdir(), getcwd()

#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"

//Defining cunctions
void clear(){
	system("clear");
}