#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>                             // for chdir(), getcwd()
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators

extern char **environ; // Declare the external environ variable

int main (int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args
    char * prompt = "==> " ;                   // shell prompt
    char command[MAX_BUFFER];                  // command to be executed
    char cwd[MAX_BUFFER];                      // current working directory

    while (!feof(stdin)) { 
        fputs(prompt, stdout); // write prompt

        if (fgets(buf, MAX_BUFFER, stdin)) { // read a line
            arg = args;
            *arg++ = strtok(buf, SEPARATORS); // tokenize input

            while ((*arg++ = strtok(NULL, SEPARATORS)));

            if (args[0]) { // if there's anything there
                if (!strcmp(args[0], "clr")) { // "clear" or "clr" command
                    system("clear");
                    continue;
                }

                if (!strcmp(args[0], "quit")) { // "quit" command
                    exit(0); // exit program with a zero return value
                }

                if (!strcmp(args[0], "dir")) { // "dir" command
                    strcpy(command, "ls -al "); // Start with base command
                    if (args[1]) {
                        strcat(command, args[1]); // Append the directory to command
                    } else {
                        strcat(command, "."); // Default to current directory
                    }
                    system(command); // Execute the command
                    continue;
                }

                if (!strcmp(args[0], "environ")) { // "environ" command
                    for (char **env = environ; *env; ++env) {
                        printf("%s\n", *env); // Print each environment string
                    }
                    continue;
                }

                if (!strcmp(args[0], "cd")) { // "cd" command
                    if (args[1]) {
                        if (chdir(args[1]) == 0) {
                            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                                setenv("PWD", cwd, 1); // update PWD environment variable
                            }
                        } else {
                            perror("Error changing directory"); // report error
                        }
                    } else {
                        if (getcwd(cwd, sizeof(cwd)) != NULL) {
                            printf("%s\n", cwd); // print current working directory
                        } else {
                            perror("Error getting current directory"); // report error
                        }
                    }
                    continue;
                }

                if (!strcmp(args[0], "echo")) { // "echo" command
                    for (int i = 1; args[i] != NULL; i++) {
                        if (i > 1) printf(" "); // Print a space between words
                        printf("%s", args[i]);
                    }
                    printf("\n");
                    continue;
                }

                if (!strcmp(args[0], "help")) { // "help" command
                    // Assuming user_manual.txt is in the current working directory or a specified path
                    strcpy(command, "more user_manual.txt"); 
                    system(command); // Execute the command to display the manual with 'more'
                    continue;
                }

                if (!strcmp(args[0], "pause")) { // "pause" command
                    printf("Press 'Enter' to continue...");
                    while (getchar() != '\n'); // Wait for 'Enter'
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