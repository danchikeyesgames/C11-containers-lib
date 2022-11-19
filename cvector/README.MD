Work with cvector.
That connect lib need to insert `#include "cvector/cvector.h"` in your code. This header had `defines`, `macros`, `declare types`, `functions` for correct work lib.
Lib interface:

```C
// This the define type
cvector_t(TYPE) <name> = NULL; // replace TYPE to your type
// simple example
cvector_t(int) my_vector = NULL;    // create vector of the int type

// for init vector can to use macro cvector_init(TYPE, size), 
// default size = 1 => usage two form

my_vector = cvector_init(int);              // init vector of int, size = 1
my_vector = cvector_init(int, 10);          // init vector of int, size = 10
// usually write:
cvector_t(int) my_vector = cvector_init(int, 10);   // good form

// typical typedef before the function main() that easier declare variable
typedef cvector_init_type(int) cvector_int_t;

// that can be to declare new vector
cvector_int_t new_vector_int = NULL;


cvector_push_back(vector, object);              // add object at the end of the vector
cvector_push_back(new_vector_int, 20);          // if not enough memory then allocate x2 memory

cvector_insert(vec, object, index);             // insert object to vec in index
cvector_insert(new_vector_int, 23, 5);          // example, index must be less than capacity of the vector

cvector_pop_back(vector);                       // erase last element
cvector_pop_back(new_vector_int);               //-----------------------------------------

cvector_erase(vec, index);                      // erase element in index
cvector_erase(new_vector_int, 5);               // example

size_t size_vec = cvector_get_size(vector);     // gets the current size of the vector
size_t cap_vec = cvector_get_capacity(vector);  // gets the current capacity of the vector

// checks vector
cvector_empty(vector);                          // checks the vector is empty, return 1 if vectro is empty
cvector_full(vector);                           // checks the vector is full, return 1 if vectro is full

cvector_resize(vec, new_size, object_type);     // change size and capacity of vector
cvector_resize(new_vector_int, 5, int);         // example

// clear vector from all elements, vector can to use continue 
cvector_clear(vec);

// destroy vector and call destructor for all elements, cant be use continue
cvector_destroy(v);         // if v equal NULL get ERROR

// free vector, dont call destructor for elements, vector cant be use continue
cvector_free(v);            // if v equal NULL get ERROR

cvector_check_free(vector);                 // It is improvment for standart 'cvector_free()' function, checks that vector isnt NULL  
cvector_check_destroy(vector);              // It is improvment for standart 'cvector_destroy()' function, checks that vector isnt NULL 

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