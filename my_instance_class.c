#include "my_instance_class.h"
#include "common.h"
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_myext.h"


zend_class_entry *my_instance_class_ce;


PHP_METHOD(InstanceClass, __construct) {

}

PHP_METHOD(InstanceClass, getInstance) {
	zval *instance = MY_CLASS_INSTANCE(my_instance_class_ce, DEFAULT_CLASS_INSTANCE_NAME);
	RETURN_ZVAL(instance, 1, 0);
	zval_ptr_dtor(instance);
}



static zend_function_entry my_instance_class_methods[] = {
	PHP_ME(InstanceClass, __construct, NULL, ZEND_ACC_PRIVATE | ZEND_ACC_CTOR)
	PHP_ME(InstanceClass, getInstance, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};


PHP_MINIT_FUNCTION(my_instance_class) {
	MY_REGISTER_INTERNAL_CLASS(my_instance_class_ce, "InstanceClass", my_instance_class_methods);

	zend_declare_property_null(my_instance_class_ce, ZEND_STRL(DEFAULT_CLASS_INSTANCE_NAME),  ZEND_ACC_PRIVATE|ZEND_ACC_STATIC TSRMLS_CC);

	return SUCCESS;
}