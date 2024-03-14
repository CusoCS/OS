#include "myshell.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>                             // for chdir(), getcwd()
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators

// Declare the external environ variable and utility functions
extern char **environ;
void clear();
void printEnvironmentVariables();
void listDirectory(const char *directory);
void pauseShell();
void echoCommand(char *args[], int argCount);
void quitShell();
void changeDirectory(const char *directory);

int main (int argc, char ** argv) {
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args
    char * prompt = "==> " ;                   // shell prompt
    char cwd[MAX_BUFFER];                      // current working directory

    while (!feof(stdin)) {
        fputs(prompt, stdout); // write prompt

        if (fgets(buf, MAX_BUFFER, stdin)) { // read a line
            arg = args;
            *arg++ = strtok(buf, SEPARATORS); // tokenize input

            while ((*arg++ = strtok(NULL, SEPARATORS)));

            if (args[0]) { // if there's anything there
                if (!strcmp(args[0], "clr")) { // "clr" command
                    clear();
                    continue;
                }

                if (!strcmp(args[0], "quit")) { // "quit" command
                    quitShell(); // Call the quitShell function instead of exit(0)
                }

                if (!strcmp(args[0], "dir")) { // "dir" command
                    listDirectory(args[1]); // Pass the directory argument to listDirectory
                    continue;
                }

                if (!strcmp(args[0], "environ")) {
                    printEnvironmentVariables();
                    continue;
                }

                if (!strcmp(args[0], "cd")) { // "cd" command
                    changeDirectory(args[1]); // Pass the directory argument to changeDirectory
                    continue;
                }

                if (!strcmp(args[0], "echo")) { // "echo" command
                    int argCount = 0;
                    for (argCount = 0; args[argCount] != NULL; argCount++); // Count arguments
                    echoCommand(args, argCount);
                    continue;
                }

                if (!strcmp(args[0], "help")) { // "help" command
                    // Assuming user_manual.txt is in the current working directory or a specified path
                    system("more user_manual.txt"); // Execute the command to display the manual with 'more'
                    continue;
                }

                if (!strcmp(args[0], "pause")) { // "pause" command
                    pauseShell();
                    continue;
                }

                // If command is not recognized, it's passed here as external command or printed out
                arg = args;
                while (*arg) {
                    fprintf(stdout, "%s ", *arg++);
                }
                fputs("\n", stdout);
            }
        }
    }
    return 0; 
}