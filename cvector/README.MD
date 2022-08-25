Work with cvector.
That connect lib need to insert `#include "cvector/cvector.h"` in your code. This header had `defines`, `macros`, `declare types`, `functions` for correcting work lib.

```C
// That the define type
cvector_init_type(TYPE) name (cvector_TYPE) = NULL; // replace TYPE ont your type
// simple example
cvector_init_type(int) my_vector = NULL;    // create vector of the int type
// for init vector can to use macro cvector_init(TYPE, size), 
// default size = 1 => usage two form
my_vector = cvector_init(int);              // init vector of int, size = 1
my_vector = cvector_init(int, 10);          // init vector of int, size = 10
// usually write:
cvector_init_type(int) my_vector = cvector_init(int, 10);   // good form

// typical typedef before the function main()
typedef cvector_init_type(int) cvector_int_t; 
// can declare vector
cvector_int_t new_vector_int = NULL;

```