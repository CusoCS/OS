// utility.h
#ifndef UTILITY_H
#define UTILITY_H

#define MAX_BUFFER 1024 // Shared buffer size definition

// Function declarations
void clear();
void printEnvironmentVariables();
void listDirectory(const char *directory);
void pauseShell();
void echoCommand(char *args[], int argCount);
void quitShell();
void changeDirectory(const char *directory);

#endif
