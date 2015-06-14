<?php
// $br = (php_sapi_name() == "cli")? "":"<br>";

// if(!extension_loaded('myext')) {
// 	dl('myext.' . PHP_SHLIB_SUFFIX);
// }


//redirect("http://www.163.com");

$request = new My\Request();
print_r($request);

my_var_dump('string');
my_var_dump(0.5);
my_var_dump($request);
my_var_dump(['a']);

?>
