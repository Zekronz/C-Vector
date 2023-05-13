/*

    vec.h
    Copyright (c) 2023 Zekronz - MIT License

    https://github.com/Zekronz/C-Vector

*/

#ifndef __ZEKRONZ_VECTOR_H
#define __ZEKRONZ_VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void* __vec_ptr;

typedef struct __vector {
    size_t cap;
    size_t len;
    char data[];
} __vector;

__vec_ptr __vector_create(size_t _data_size, size_t _cap, size_t _len);
int __vector_free(__vec_ptr _vec);
__vector* __vector_struct(__vec_ptr _vec);
size_t __vector_length(__vec_ptr _vec);
size_t __vector_capacity(__vec_ptr _vec);
__vector* __vector_realloc(__vector* _vec, size_t _data_size);
int __vector_calc_capacity(size_t* _cap, size_t _dest);
int __vector_inc(__vec_ptr* _vec, size_t _num_elements, size_t _element_size);
int __vector_insert(__vec_ptr* _vec, size_t _index, size_t _element_size);
int __vector_delete(__vec_ptr* _vec, size_t _index, size_t _num_elements, size_t _element_size);
int __vector_set(__vec_ptr _vec, size_t _index);
int __vector_get(__vec_ptr _vec, size_t _index);
int __vector_clear(__vec_ptr* _vec);
int __vector_reverse(__vec_ptr _vec, size_t _element_size);
__vec_ptr __vector_clone(__vec_ptr _vec, size_t _element_size);
int __vector_reserve(__vec_ptr* _vec, size_t _num_elements, size_t _element_size);
int __vector_resize(__vec_ptr* _vec, size_t _num_elements, size_t _element_size);
int __vector_shrink(__vec_ptr* _vec, size_t _element_size);

#define vec_create() __vector_create(0, 0, 0)
#define vec_create_size(type, num_elements) (type*)(__vector_create(num_elements * sizeof(type), num_elements, num_elements))
#define vec_free(vec) __vector_free(vec)
#define vec_length(vec) __vector_length(vec)
#define vec_size(vec) __vector_length(vec)
#define vec_capacity(vec) __vector_capacity(vec)
#define vec_add(vec, value) if(__vector_inc((__vec_ptr*)(&vec), 1, sizeof(*vec))) vec[__vector_length(vec) - 1] = value
#define vec_insert(vec, index, value) if(__vector_insert((__vec_ptr*)(&vec), index, sizeof(*vec))) vec[index] = value
#define vec_delete(vec, index, num_elements) __vector_delete((__vec_ptr*)(&vec), index, num_elements, sizeof(*vec))
#define vec_set(vec, index, value) if(__vector_set(vec, index)) vec[index] = value
#define vec_get(vec, index) (__vector_get(vec, index)) ? vec[index] : 0
#define vec_clear(vec) __vector_clear((__vec_ptr*)(&vec))
#define vec_reverse(vec) __vector_reverse(vec, sizeof(*vec))
#define vec_fill(vec, value) for(size_t __vec_len = vec_length(v), i = 0; i < __vec_len; ++i) vec[i] = value
#define vec_fill_range(vec, index, num_elements, value) for(size_t __vec_len = vec_length(v), __vec_start = (index < 0) ? 0 : index, __vec_end = (__vec_start + num_elements > __vec_len) ? __vec_len : __vec_start + num_elements, i = __vec_start; i < __vec_end; ++i) vec[i] = value
#define vec_clone(vec) __vector_clone(vec, sizeof(*vec))
#define vec_reserve(vec, num_elements) __vector_reserve((__vec_ptr*)(&vec), num_elements, sizeof(*vec))
#define vec_resize(vec, num_elements) __vector_resize((__vec_ptr*)(&vec), num_elements, sizeof(*vec))
#define vec_shrink(vec) __vector_shrink((__vec_ptr*)(&vec), sizeof(*vec))
#define vec_empty(vec) (vec_length(vec) == 0)

#ifdef __cplusplus
}
#endif

#endif