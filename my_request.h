#ifndef MY_REQUEST_H
#define MY_REQUEST_H
#include "php.h"

extern zend_class_entry *my_request_ce;
//MY_MODULE_STARTUP_FUNCTION(request);
PHP_MINIT_FUNCTION(my_request);


#endif
