

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
