#ifndef __TREE_H
#define __TREE_H

#include <stdbool.h>

#include "treenode.h"

typedef struct Tree {
	TreeNode root;
} Tree;

Tree *treeNew();

void treeInit(Tree *tree);

Tree *treeDelete(Tree *tree);

void treeAdd(Tree *tree, char *key, char delimiter);

size_t treeDepth(Tree *tree);

void treePrint(Tree *tree);

void treePrintDebug(Tree *tree, FILE *fp);

#endif
