#ifndef MY_ARRAY_API_H
#define MY_ARRAY_API_H

#include "php.h"


zval **paa_get_val_by_key(HashTable *ht, const char *key);

zval **paa_get_val_by_index(HashTable *ht, long index);
	

#endif