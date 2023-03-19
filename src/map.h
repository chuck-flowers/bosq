#include <stddef.h>

#ifndef __MAP_H
#define __MAP_H

typedef struct {
  char **keys;
  void **values;
  size_t length;
  size_t capacity;
} Map;

Map *mapCreate();

void mapInit(Map *map);

Map *mapDelete(Map *map);

void mapDestruct(Map *map);

void *mapGetKey(Map *map, char *key);

void *mapSetKey(Map *map, char *key, void *value);

#endif
