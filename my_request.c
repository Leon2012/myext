#include "my_request.h"
#include "common.h"
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_myext.h"

zend_class_entry *my_request_ce;
static zend_object_handlers my_request_handlers;



typedef struct _my_request_object {
	zend_object obj;

}my_request_object;

#define REQUEST_FETCH_OBJECT(zobj) (my_request_object *)zend_object_store_get_object((zobj) TSRMLS_CC)


static void my_request_object_dtor(void *object TSRMLS_DC) {
	my_request_object *objval = (my_request_object *)object;
	zend_object_std_dtor(&(objval->obj) TSRMLS_CC);
    efree(objval);
}

static zend_object_value my_request_object_ctor(zend_class_entry *ce TSRMLS_DC) {
	my_request_object *objval = (my_request_object *)emalloc(sizeof(my_request_object));
	memset(objval, 0, sizeof(my_request_object));

	zend_object_value retval;
	zend_object_std_init(&(objval->obj), ce TSRMLS_CC);

	retval.handle = zend_objects_store_put(objval, 
		NULL, 
		(zend_objects_free_object_storage_t)my_request_object_dtor,
		NULL TSRMLS_CC);

	retval.handlers = &my_request_handlers;

	return retval;
}


ZEND_METHOD(Request, __construct) {
	//my_request_object *objval =  REQUEST_FETCH_OBJECT(getThis());
}



static zend_function_entry my_request_methods[] = {
	ZEND_ME(Request, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	{NULL, NULL, NULL}
};



PHP_MINIT_FUNCTION(my_request) {
	MY_REGISTER_INTERNAL_CLASS(my_request_ce, "Request", my_request_methods);

	my_request_ce->create_object = my_request_object_ctor;
	memcpy(&my_request_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	my_request_handlers.clone_obj = NULL;

	return SUCCESS;
}


