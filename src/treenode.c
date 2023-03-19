#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treenode.h"

const char *PREFIX = u8"├── ";
const char *SPAN = u8"│   ";
const char *FINAL_PREFIX = u8"└── ";
const char *D = u8"    ";

TreeNode *treeNodeNew() {
  TreeNode *node = malloc(sizeof(TreeNode));
  treeNodeInit(node);
  return node;
}

void treeNodeInit(TreeNode *node) {
  mapInit(&node->map);
}

TreeNode *treeNodeDelete(TreeNode *node) {
  mapDestruct(&node->map);
  return NULL;
}

void treeNodeAdd(TreeNode *node, char *key, char delimiter) {
  size_t totalKeyLength = strlen(key);

  // If the key is empty, mark the current node and exit
  if (totalKeyLength == 0) {
    node->exists = true;
    return;
  }

  // Find length of "root" segment
  size_t rootSegLength;
  for (rootSegLength = 0; rootSegLength < totalKeyLength; rootSegLength++) {
    char c = key[rootSegLength];
    if (c == delimiter) {
      break;
    }
  }

  // Allocate a dedicated, "root" segment
  char *rootSeg = malloc(sizeof(char) * rootSegLength + 1);
  char *remaining = key + rootSegLength + 1;
  memcpy(rootSeg, key, rootSegLength);
  rootSeg[rootSegLength] = '\0';

  // If no node exists yet, create one
  TreeNode *nextNode = mapGetKey(&node->map, rootSeg);
  if (nextNode == NULL) {
    nextNode = treeNodeNew();
    mapSetKey(&node->map, rootSeg, nextNode);
  }

  // Move to the next segment
  treeNodeAdd(nextNode, remaining, delimiter);
}

size_t treeNodeDepth(TreeNode *node) {
  size_t maxSubDepth = 0;
  for (size_t i = 0; i < node->map.length; i++) {
    TreeNode *subNode = node->map.values[i];
    size_t subDepth = treeNodeDepth(subNode);
    if (subDepth > maxSubDepth) {
      maxSubDepth = subDepth;
    }
  }

  return 1 + maxSubDepth;
}

void treeNodePrint(TreeNode *node, bool *isLastOfSiblings, size_t depth) {


  size_t childCount = node->map.length;
  for (size_t i = 0; i < childCount; i++) {
    char *name = node->map.keys[i];
    TreeNode *subNode = node->map.values[i];

    // Print the prefix of the element
    for (size_t d = 0; d < depth; d++) {
      if (d == depth - 1) {
        if (i == childCount - 1) {
          printf("%s", FINAL_PREFIX);
        } else {
          printf("%s", PREFIX);
        }
      } else if (isLastOfSiblings[d + 2]) {
		printf("    ");
	  } else {
        printf("%s", SPAN);
      }
    }

    // Print the current element
    printf("%s\n", name);

    // Print the elements of the element
    isLastOfSiblings[depth + 1] = i == childCount - 1;
    treeNodePrint(subNode, isLastOfSiblings, depth + 1);
  }
}

void treeNodePrintDebug(TreeNode *node, FILE *fp, size_t depth) {

  for (size_t i = 0; i < node->map.length; i++) {
    char *nodeName = node->map.keys[i];
    TreeNode *subNode = node->map.values[i];

    // Print the relevant prefix
    for (size_t i = 0; i < depth; i++) {
      printf("    ");
    }

    printf("%s\n", nodeName);
    treeNodePrintDebug(subNode, stderr, depth + 1);
  }
}
