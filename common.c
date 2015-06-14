#include "common.h"
#include "php.h"



zval *my_get_class_instance(zend_class_entry *ce, const char *instance_name, int name_length){
	zval *instance;

	instance = zend_read_static_property(ce, instance_name, name_length, 0 TSRMLS_CC);//读取class的static属性
	if (IS_OBJECT == Z_TYPE_P(instance) && instance_function(Z_OBJCE_P(instance), ce TSRMLS_CC)) {//判断instance是否是object，并且是属于ce类型
		return instance;
	}

	MAKE_STD_ZVAL(instance);//初始化zval
	object_init_ex(instance, ce);//用instance初始化ce
	zend_update_static_property(ce, instance_name, name_length, instance TSRMLS_CC);//更新值

	return instance;
}


void my_var_dump(zval *val) {
	zval *function_name, *return_val;

	MAKE_STD_ZVAL(function_name);
	MAKE_STD_ZVAL(return_val);

	ZVAL_STRING(function_name, "var_dump", 1);
	zval *params = {val};

	call_user_function(CG(function_table), NULL, function_name, return_val, 1, &params TSRMLS_CC);

	my_dump_zval(return_val);

	zval_ptr_dtor(function_name);
	zval_ptr_dtor(return_val);
}


void my_dump_zval(zval *arg) {
	//php_printf("\ntype: %d \nis_ref__gc: %d\nrefcount__gc: %d\n\n", Z_TYPE_P(val), Z_ISREF_P(val), Z_REFCOUNT_P(val));
	switch(Z_TYPE_P(arg)) {
	        case IS_NULL://arg is null
	            php_printf("NULL\n");
	            break;
	        case IS_BOOL://arg is true, false
	            php_printf("bool(%s)\n", Z_BVAL_P(arg)?"true":"false");
	            break;
	        case IS_LONG:
	            php_printf("int(%d)\n", Z_LVAL_P(arg));
	            break;
	        case IS_DOUBLE:
	            php_printf("float(%f)\n", Z_DVAL_P(arg));
	            break;
	        case IS_STRING:
	            php_printf("string(%d)\n", Z_STRLEN_P(arg));
	            PHPWRITE(Z_STRVAL_P(arg), Z_STRLEN_P(arg));
	            php_printf("\n");
	            break;
	        case IS_ARRAY:
	            php_printf("array(%d){...}\n", zend_hash_num_elements(Z_ARRVAL_P(arg)));
	            break;
	        case IS_RESOURCE:{
	            const char *type_name = zend_rsrc_list_get_rsrc_type(Z_RESVAL_P(arg) TSRMLS_CC);
	            php_printf("resource#%ld(%s)\n", Z_RESVAL_P(arg), type_name?type_name:"Unknown");
	            break;
	        }
	        case IS_OBJECT:{
	            const zend_class_entry *ce = Z_OBJCE_P(arg);
	            php_printf("object#%u(%s)\n", Z_OBJ_HANDLE_P(arg), (ce && ce->name)?ce->name:"Unknown");
	            break;
	        }
	        default:
	            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unknown type: %d\n", Z_TYPE_P(arg));
	    }

}
