#include "my_array_api.h"

#include "zend.h"
#include "zend_execute.h"
#include "zend_API.h"
#include "zend_operators.h"
#include "zend_hash.h"
#include "zend_list.h"


zval **paa_get_val_by_key(HashTable *ht, const char *key)
{
	HashPosition pos;
	zval **val;
	if (zend_hash_find(ht, key, sizeof(key), (void **)&val) == SUCCESS) {
		return val;
	}
	return NULL;
}


zval **paa_get_val_by_index(HashTable *ht, long index)
{
	return NULL;
}