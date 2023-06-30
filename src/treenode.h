#ifndef __TREE_NODE_H
#define __TREE_NODE_H

#include <stdbool.h>
#include <stdio.h>

#include "map.h"

typedef struct TreeNode {
  bool exists;
  Map map;
} TreeNode;

TreeNode *treeNodeNew(void);

void treeNodeInit(TreeNode *node);

TreeNode *treeNodeDelete(TreeNode *node);

void treeNodeAdd(TreeNode *node, char *key, char *delimiter);

size_t treeNodeDepth(TreeNode *node);

void treeNodePrint(TreeNode *node, bool *parentsAreLast, size_t depth);

void treeNodePrintDebug(TreeNode *node, FILE *fp, size_t depth);

#endif
