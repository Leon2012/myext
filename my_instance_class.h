#ifndef MY_INSTANCE_CLASS_H
#define MY_INSTANCE_CLASS_H
#include "php.h"

#define DEFAULT_CLASS_INSTANCE_NAME "instance"

extern zend_class_entry *my_instance_class_ce;
//MY_MODULE_STARTUP_FUNCTION(instance_class);
PHP_MINIT_FUNCTION(my_instance_class);


#endif
