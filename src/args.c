#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "args.h"

static struct option o[] = {{"delimiter", required_argument, 0, 'd'},
                            {0, 0, 0, 0}};

void parseArgs(CliArgs *args, int argc, char **argv) {
  // Provide initial values
  args->delimiter = "/";

  int c;
  int option_index;
  while (1) {
    c = getopt_long(argc, argv, "d:", o, &option_index);

    if (c == -1) {
      break;
    }

    switch (c) {
    case 'd':
      args->delimiter = optarg;
      break;
    }
  }
}

void printArgs(FILE *fp, CliArgs *args) {
  fprintf(fp, "CliArgs {\n\tdelimiter = '%s'\n}\n", args->delimiter);
  fflush(fp);
}
