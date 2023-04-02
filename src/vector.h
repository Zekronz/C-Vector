#ifndef __VECTOR_H
#define __VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void* vec_ptr;

typedef struct __vector {
    size_t cap;
    size_t len;
    char data[];
} __vector;

vec_ptr __vector_create(size_t _data_size, size_t _cap, size_t _len);
void __vector_free(vec_ptr _vec);
__vector* __vector_struct(vec_ptr _vec);
size_t __vector_length(vec_ptr _vec);
size_t __vector_capacity(vec_ptr _vec);
__vector* __vector_realloc(__vector* _vec, size_t _data_size);
int __vector_inc(vec_ptr* _vec, size_t _num_elements, size_t _element_size);
int __vector_insert(vec_ptr* _vec, size_t _index, size_t _element_size);
int __vector_delete(vec_ptr* _vec, size_t _index, size_t _num_elements, size_t _element_size);
int __vector_set(vec_ptr _vec, size_t _index);
int __vector_get(vec_ptr _vec, size_t _index);

//@TODO: Error printing.
//@TODO: Documentation. Data does not initialize to 0.

#define vec_create(type, num_elements) (type*)(__vector_create(num_elements * sizeof(type), num_elements, num_elements))
#define vec_free(vec) __vector_free(vec)
#define vec_length(vec) __vector_length(vec)
#define vec_capacity(vec) __vector_capacity(vec)
#define vec_add(vec, value) if(__vector_inc((vec_ptr*)(&vec), 1, sizeof(value))) vec[__vector_length(vec) - 1] = value
#define vec_insert(vec, position, value) if(__vector_insert((vec_ptr*)(&vec), position, sizeof(value))) vec[position] = value
#define vec_delete(vec, position, num_elements) __vector_delete((vec_ptr*)(&vec), position, num_elements, sizeof(*vec))
#define vec_set(vec, position, value) if(__vector_set(vec, position)) vec[position] = value
#define vec_get(vec, position) (__vector_get(vec, position)) ? vec[position] : 0

#ifdef __cplusplus
}
#endif

#endif