#include "map.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 100

void expandCapacity(Map *map, size_t target);

Map *mapCreate() {
  Map *toReturn = malloc(sizeof(Map));
  mapInit(toReturn);
  return toReturn;
}

void mapInit(Map *map) {
  map->keys = malloc(sizeof(char *) * DEFAULT_CAPACITY);
  map->values = malloc(sizeof(void *) * DEFAULT_CAPACITY);
  map->length = 0;
  map->capacity = DEFAULT_CAPACITY;

  for (size_t i = 0; i < DEFAULT_CAPACITY; i++) {
    map->keys[i] = NULL;
    map->values[i] = NULL;
  }
}

Map *mapDelete(Map *map) {
  mapDestruct(map);
  free(map);

  return NULL;
}

void mapDestruct(Map *map) {
  // Delete each owned key and value
  for (size_t i = 0; i < map->length; i++) {
    free(map->keys[i]);
    free(map->values[i]);
  }

  // Delete the fields and struct
  free(map->keys);
  free(map->values);
}


void *mapGetKey(Map *map, char *key) {
  for (int i = 0; i < map->length; i++) {
    char *k = map->keys[i];
    if (strcmp(k, key) == 0) {
      return map->values[i];
    }
  }

  return NULL;
}

void *mapSetKey(Map *map, char *key, void *value) {
  for (int i = 0; i < map->length; i++) {
    char *k = map->keys[i];
    if (strcmp(k, key) == 0) {
      void *old = map->values[i];
      map->values[i] = value;
      return old;
    }
  }

  if (map->length >= map->capacity) {
    expandCapacity(map, (map->capacity + 1) * 2);
  }

  // Append pair to end
  map->keys[map->length] = key;
  map->values[map->length] = value;
  map->length++;

  return NULL;
}

void expandCapacity(Map *map, size_t target) {
  assert(target > map->capacity);

  // Get current buffers
  char **oldKeys = map->keys;
  void **oldValues = map->values;

  // Allocate new buffers
  char **newKeys = malloc(sizeof(char *) * target);
  void **newValues = malloc(sizeof(void *) * target);

  // Copy existing data
  for (size_t i = 0; i < map->length; i++) {
    newKeys[i] = oldKeys[i];
    newValues[i] = oldValues[i];
  }

  // Free old buffers
  free(oldKeys);
  free(oldValues);

  // Update struct
  map->keys = newKeys;
  map->values = newValues;
  map->capacity = target;
}
