Target of the C11-containers-lib to do easier creation new project and also help to focus on more important things such as implementation hard parts int your project. This lib include different data structures with opportunity to create structure any type.

structure of vector:


```
+++++++++++++++++++++++++++++++++++++++++++++++----------+--------+------------------+
+@      constructor      ||      destructor   | capacity |  size  |  data[capacity]  |
+------------------------++-------------------+----------+--------+------------------+
+@ pointer of constructor/destructor function | size_t c | size_t |  pointer of vec  |
+=============================================+===================|==================+
|<--------+---------------------------------->|                   ^
          ^                                                       | user's pointer vector => that user can use vec[i]
          | this optional settings, if your type(struct) has malloc/free (default=NULL) 
```

Simple example use lib:
```C
#include "cvector/cvector.h"

#include <stdio.h>


int main(void) {
    cvector_init_type(int) vector_int = NULL; // simple init vector
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
        tmp = cvector_pop_back(vector_int);
        printf("%d: %d element\n", i, tmp);
    }

    // the vector is clear

    return 0;
}
```