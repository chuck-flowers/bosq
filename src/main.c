#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "tree.h"
#include "treenode.h"

#define MAX_LINE_SIZE 1024

int main() {
  Tree *tree = treeNew();
  if (tree == NULL) {
    fprintf(stderr, "Failed to allocate the Tree struct\n");
    return 1;
  }

  // Add each line of input to the tree
  char line[MAX_LINE_SIZE];
  while (fgets(line, MAX_LINE_SIZE, stdin) == line) {
    // Remove the new line character
    size_t line_length = strlen(line);
    line[line_length - 1] = '\0';

	treeAdd(tree, line, '/');
  }

  // Traverse and print tree
  treePrint(tree);

  tree = treeDelete(tree);
}
