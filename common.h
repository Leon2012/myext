#ifndef COMMON_H
#define COMMON_H

#include "php.h"
	
#define PHP_MYEXT_NS_NAME "My"

ZEND_BEGIN_ARG_INFO(arg_info_void, 0)
ZEND_END_ARG_INFO()


#define MY_REGISTER_INTERNAL_CLASS(class_ce, class_name, functions) \
		zend_class_entry ce; \
		INIT_CLASS_ENTRY(ce, ZEND_NS_NAME(PHP_MYEXT_NS_NAME, class_name), functions); \
		class_ce = zend_register_internal_class(&ce);


#define MY_REGISTER_INTERNAL_CLASS_EX(class_ce, class_name, functions, parent_class_ce, parent_class_name) \
		zend_class_entry ce; \
		INIT_CLASS_ENTRY(ce, ZEND_NS_NAME(PHP_MYEXT_NS_NAME, class_name), functions); \
		class_ce = zend_register_internal_class_ex(&ce, parent_class_ce,  parent_class_name TSRMLS_CC);


#define MY_MODULE_STARTUP(module) \
		ZEND_MODULE_STARTUP_N(my_##module)(INIT_FUNC_ARGS_PASSTHRU);

#define MY_MODULE_STARTUP_FUNCTION(module) \
		PHP_MINIT_FUNCTION(my_##module)
        


/*
 *ZEND_API int call_user_function(HashTable *function_table, 
 									zval **object_pp, 
 									zval *function_name, 
 									zval *retval_ptr, 
 									zend_uint param_count, 
 									zval *params[] TSRMLS_DC)
*/
#define MY_CALL_USER_FUNCTION(function_name, retval_ptr, params) \
		call_user_function(CG(funcion_table), NULL, function_name, retval_ptr, sizeof(params) / sizeof(zval *), &params TSRMLS_CC);


#define MY_CALL_CLASS_FUNCTION(function_name, retval_ptr, params) \
		call_user_function(NULL, &getThis(), function_name, retval_ptr, sizeof(params) / sizeof(zval *), params TSRMLS_CC)


void my_dump_zval(zval *val);
void my_var_dump(zval *val);

#endif
