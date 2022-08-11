#ifndef __CVECTOR_H__
#define __CVECTOR_H__

/* macros declare new vector different type */
#define con_cvector_init_type(type) type *

typedef void (*cvector_constructor_elem_t) (void* adr);
typedef void (*cvector_destructor_elem_t)  (void* adr);



#endif  // __CVECTOR_H__


