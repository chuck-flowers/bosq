#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "tree.h"
#include "treenode.h"

Tree *treeNew(void) {
  Tree *tree = malloc(sizeof(Tree));
  treeInit(tree);
  return tree;
}

void treeInit(Tree *tree) { treeNodeInit(&tree->root); }

Tree *treeDelete(Tree *tree) {
  treeNodeDelete(&tree->root);
  free(tree);
  return NULL;
}

void treeAdd(Tree *tree, char *key, char *delimiter) {
  treeNodeAdd(&tree->root, key, delimiter);
}

size_t treeDepth(Tree *tree) { return treeNodeDepth(&tree->root); }

void treePrint(Tree *tree) {

  // Initialize an array for tracking when an element is the last child
  bool *depthArray = calloc(treeDepth(tree), sizeof(bool));
  depthArray[0] = true;

  treeNodePrint(&tree->root, depthArray, 0);
}

void treePrintDebug(Tree *tree, FILE *fp) {
  treeNodePrintDebug(&tree->root, fp, 0);
}
