PHP_ARG_WITH(myext, for myext support,
[  --with-myext             Include myext support])

if test "$PHP_MYEXT" != "no"; then
  ext_files="myext.c common.c my_array_api.c my_request.c"
  PHP_NEW_EXTENSION(myext, $ext_files, $ext_shared)
fi

if test -z "$PHP_DEBUG"; then 
AC_ARG_ENABLE(debug,
[ --enable-debug      compile with debugging symbols],[
    PHP_DEBUG=$enableval
],[ PHP_DEBUG=no
])
fi
