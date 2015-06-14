/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "SAPI.h"
#include "ext/standard/info.h"
#include "ext/standard/head.h"
#include "php_myext.h"

#include "common.h"
#include "my_array_api.h"

/* If you declare any globals in php_myext.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(myext)
*/

/* True global resources - no need for thread safety here */
static int le_myext;



/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("myext.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_myext_globals, myext_globals)
    STD_PHP_INI_ENTRY("myext.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_myext_globals, myext_globals)
PHP_INI_END()
*/
/* }}} */



/* {{{ php_myext_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_myext_init_globals(zend_myext_globals *myext_globals)
{
	myext_globals->global_value = 0;
	myext_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(myext)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/

	MY_MODULE_STARTUP(request);


	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(myext)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(myext)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(myext)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(myext)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "myext support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

ZEND_BEGIN_ARG_INFO(function_redirect_arg, 0)
	ZEND_ARG_INFO(0, url)
	ZEND_ARG_INFO(0, code)
ZEND_END_ARG_INFO()

PHP_FUNCTION(redirect) {
	char *url = NULL;
	int url_len;
	int code = 0;

	sapi_header_line redirect = {0};
	redirect.response_code = 301;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &url, &url_len, &code) == FAILURE) {
		return;
	}

	if (code != 0) {
		redirect.response_code = code;
	}

	asprintf(&redirect.line , "Location: %s", url);
	redirect.line_len = strlen(redirect.line);

	sapi_header_op(SAPI_HEADER_REPLACE, &redirect TSRMLS_CC);
	php_header(TSRMLS_C);
	free(redirect.line);
}

ZEND_BEGIN_ARG_INFO(function_myvardump_arg, 0)
	ZEND_ARG_INFO(0, param)
ZEND_END_ARG_INFO()
PHP_FUNCTION(my_var_dump) {
	zval *param;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &param) == FAILURE) {
		return;
	}
	my_dump_zval(param);
}

/* {{{ myext_functions[]
 *
 * Every user visible function must have an entry in myext_functions[].
 */
const zend_function_entry myext_functions[] = {
	PHP_FE(redirect,	function_redirect_arg)		
	PHP_FE(my_var_dump, function_myvardump_arg)
	PHP_FE_END	/* Must be the last line in myext_functions[] */
};
/* }}} */

/* {{{ myext_module_entry
 */
zend_module_entry myext_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"myext",
	myext_functions,
	PHP_MINIT(myext),
	PHP_MSHUTDOWN(myext),
	PHP_RINIT(myext),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(myext),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(myext),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_MYEXT_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MYEXT
ZEND_GET_MODULE(myext)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
