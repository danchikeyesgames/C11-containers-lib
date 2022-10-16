Work with cvector.
That connect lib need to insert `#include "cvector/cvector.h"` in your code. This header had `defines`, `macros`, `declare types`, `functions` for correcting work lib.
Lib interface:

```C
// That the define type
cvector_t(TYPE) <name> = NULL; // replace TYPE ont your type
// simple example
cvector_t(int) my_vector = NULL;    // create vector of the int type

// for init vector can to use macro cvector_init(TYPE, size), 
// default size = 1 => usage two form

my_vector = cvector_init(int);              // init vector of int, size = 1
my_vector = cvector_init(int, 10);          // init vector of int, size = 10
// usually write:
cvector_t(int) my_vector = cvector_init(int, 10);   // good form

// typical typedef before the function main()
typedef cvector_init_type(int) cvector_int_t; 
// can declare vector
cvector_int_t new_vector_int = NULL;

cvector_push_back(vector, object);              // add object at the end of the vector
cvector_push_back(new_vector_int, 20);          // if not enough memory then allocate x2 mem

cvector_pop_back(vector);                       // erase last element
cvector_pop_back(new_vector_int);               // -----------------------------------------

cvector_get_size(vector);                       // gets the current size of the vector
cvector_get_capacity(vector);                   // gets the current capacity of the vector

// checks vector
cvector_empty(vector);                          // checks the vector is empty
cvector_full(vector);                           // checks the vector is full

```

structure of vector:


```
+------------------------++-------------------+----------+--------+------------------+
+@      constructor      ||      destructor   | capacity |  size  |  data[capacity]  |
+------------------------++-------------------+----------+--------+------------------+
+@ pointer of constructor/destructor function | size_t c | size_t |  pointer of vec  |
+=============================================+===================|==================+
|<--------+---------------------------------->|                   ^
          ^                                                       | user's pointer vector => that user can use vec[i]
          | this optional settings, if your type(struct) has malloc/free (default=NULL) 
```

Simple example to use lib:
```C
#include "cvector/cvector.h"

#include <stdio.h>


int main(void) {
    cvector_t(int) vector_int = NULL; // simple init vector
    int tmp;
    size_t size;

    cvector_push_back(vector_int, 10);        // macros push value (=10) in the end of vector_int
    cvector_push_back(vector_int, 20);        // macros push value (=20) in the end of vector_int
    cvector_push_back(vector_int, 30);        // macros push value (=30) in the end of vector_int
    cvector_push_back(vector_int, 40);        // macros push value (=40) in the end of vector_int
    cvector_push_back(vector_int, 50);        // macros push value (=50) in the end of vector_int

    size = (cvector_get_size(vector_int));
    
    for (int i = 0; i < size; ++i)            // can to use the vector as usual array in C lib
        printf("%d ", vector_int[i]);
    putchar('\n');

    for (int i = 0; i < size; ++i) {          // output the vector in stdout + clear node
        tmp = vector_int[size - i - 1];
        printf("%d: %d element\n", i, tmp);
        cvector_pop_back(vector_int);
    }

    // the vector is clear

    return 0;
}
```