#ifndef __ARGS_H
#define __ARGS_H

#include <stdio.h>

typedef struct {
  char *delimiter;
} CliArgs;

void parseArgs(CliArgs *args, int argc, char **argv);

#endif
