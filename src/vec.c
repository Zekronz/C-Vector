/*

    vec.c
    Copyright (c) 2023 Zekronz - MIT License

*/

#include <stdlib.h>
#include <string.h>
#include "vec.h"

#define __VECTOR_MAX_CAPACITY (size_t)-1

__vec_ptr __vector_create(size_t _data_size, size_t _cap, size_t _len){
    __vector* v = (__vector*)malloc(sizeof(__vector) + _data_size);
    if(v == NULL) return NULL;

    v->cap = _cap;
    v->len = _len;

    return (__vec_ptr)(&v->data);
}

int __vector_free(__vec_ptr _vec){
    if(_vec == NULL) return 0;
    free(__vector_struct(_vec));
    return 1;
}

__vector* __vector_struct(__vec_ptr _vec){
    if(_vec == NULL) return NULL;
    return ((__vector*)_vec) - 1;
}

size_t __vector_length(__vec_ptr _vec){
    if(_vec == NULL) return 0;
    return __vector_struct(_vec)->len;
}

size_t __vector_capacity(__vec_ptr _vec){
    if(_vec == NULL) return 0;
    return __vector_struct(_vec)->cap;
}

__vector* __vector_realloc(__vector* _vec, size_t _data_size){
    if(_vec == NULL) return NULL;

    __vector* new_vec = (__vector*)realloc(_vec, sizeof(__vector) + _data_size);
    if(new_vec == NULL) return NULL;

    return new_vec;
}

int __vector_calc_capacity(size_t* _cap, size_t _dest){    
    (*_cap) = 0;
    if(_dest == 0) return 1;

    size_t new_cap = 1;
    size_t prev_cap;
    while(new_cap < _dest){
        prev_cap = new_cap;
        new_cap *= 2;

        if(new_cap < prev_cap){
            new_cap = __VECTOR_MAX_CAPACITY;
            break;
        }
    }

    if(new_cap < _dest) return 0; //Overflow

    (*_cap) = new_cap;
    return 1;
}

int __vector_inc(__vec_ptr* _vec, size_t _num_elements, size_t _element_size){
    if(_vec == NULL || _num_elements == 0 || _element_size == 0) return 0;
    if((*_vec) == NULL) return 0;

    __vector* v = __vector_struct(*_vec);
    
    size_t new_len = v->len + _num_elements;
    if(new_len < v->len) return 0; //Overflow.

    if(new_len > v->cap){
        size_t new_cap = 0;
        if(!__vector_calc_capacity(&new_cap, new_len)) return 0; //Overflow.

        __vector* new_vec = __vector_realloc(v, _element_size * new_cap);
        if(new_vec == NULL) return 0;

        v = new_vec;
        v->cap = new_cap;
        *_vec = (__vec_ptr)(&v->data);
    }

    v->len = new_len;

    return 1;
}

int __vector_insert(__vec_ptr* _vec, size_t _index, size_t _element_size){
    if(_vec == NULL || _element_size == 0) return 0;
    if((*_vec) == NULL) return 0;

    __vector* v = __vector_struct(*_vec);

    size_t old_len = v->len;
    size_t new_len = (_index <= old_len) ? old_len + 1 : old_len + (_index - old_len) + 1;
    if(new_len < old_len) return 0; //Overflow.
    if(!__vector_inc(_vec, new_len - old_len, _element_size)) return 0;

    char* ptr = (char*)(*_vec);
    if(_index < old_len) memmove(ptr + (_index * _element_size) + _element_size, ptr + (_index * _element_size), (old_len - _index) * _element_size);

    return 1;
}

int __vector_delete(__vec_ptr* _vec, size_t _index, size_t _num_elements, size_t _element_size){
    if(_vec == NULL || _element_size == 0 || _num_elements == 0) return 0;
    if((*_vec) == NULL) return 0;

    __vector* v = __vector_struct(*_vec);

    if(_index >= v->len) return 1;
    if(_index + _num_elements - 1 < _index) return 0; //Overflow.
    if(_index + _num_elements - 1 >= v->len) _num_elements = (v->len - _index);

    size_t new_len = v->len - _num_elements;
    size_t old_cap = v->cap;
    size_t new_cap = 0;
    if(!__vector_calc_capacity(&new_cap, new_len)) return 0; //Overflow.

    if(_index + _num_elements - 1 < v->len - 1){
        char* ptr = (char*)(*_vec);
        memmove(ptr + (_index * _element_size), ptr + (_index + _num_elements) * _element_size, (v->len - (_index + _num_elements)) * _element_size);
    }

    if(old_cap != new_cap){
        __vector* new_vec = __vector_realloc(v, _element_size * new_cap);
        if(new_vec == NULL) return 0;
        
        v = new_vec;
        *_vec = (__vec_ptr)(&v->data);
    }

    v->len = new_len;
    v->cap = new_cap;

    return 1;
}

int __vector_set(__vec_ptr _vec, size_t _index){
    if(_vec == NULL) return 0;
    __vector* v = __vector_struct(_vec);

    if(_index >= v->len) return 0;

    return 1;
}

int __vector_get(__vec_ptr _vec, size_t _index){
    if(_vec == NULL) return 0;
    __vector* v = __vector_struct(_vec);

    if(_index >= v->len) return 0;

    return 1;
}

int __vector_clear(__vec_ptr* _vec){
    if(_vec == NULL) return 0;
    if((*_vec) == NULL) return 0;
    __vector* v = __vector_struct(*_vec);

    if(v->cap == 0) return 1;

    __vector* new_vec = __vector_realloc(v, 0);
    if(new_vec == NULL) return 0;

    new_vec->len = 0;
    new_vec->cap = 0;
    *_vec = (__vec_ptr)(&new_vec->data);

    return 1;
}

int __vector_reverse(__vec_ptr _vec, size_t _element_size){
    if(_vec == NULL) return 0;
    __vector* v = __vector_struct(_vec);

    size_t middle = ((v->len / 2) + ((v->len & 0x1) == 1)) * _element_size;
    size_t ind;
    char temp;
    for(size_t i = 0; i < middle; i += _element_size){
        for(size_t j = 0; j < _element_size; ++j){
            temp = v->data[i + j];
            ind = ((v->len - 1) * _element_size) - i + j;
            v->data[i + j] = v->data[ind];
            v->data[ind] = temp;
        }
    }

    return 1;
}

__vec_ptr __vector_clone(__vec_ptr _vec, size_t _element_size){
    if(_vec == NULL) return NULL;

    __vector* v = __vector_struct(_vec);
    __vector* new_vec = (__vector*)malloc(sizeof(__vector) + (v->cap * _element_size));
    if(new_vec == NULL) return NULL;

    new_vec->cap = v->cap;
    new_vec->len = v->len;

    size_t len = new_vec->len * _element_size;
    for(size_t i = 0; i < len; ++i) new_vec->data[i] = v->data[i];

    return (__vec_ptr)(&new_vec->data);
}

int __vector_reserve(__vec_ptr* _vec, size_t _num_elements, size_t _element_size){
    if(_vec == NULL || _element_size == 0) return 0;
    if((*_vec) == NULL) return 0;
    __vector* v = __vector_struct(*_vec);

    if(v->cap >= _num_elements) return 1;

    __vector* new_vec = __vector_realloc(v, _num_elements * _element_size);
    if(new_vec == NULL) return 0;

    new_vec->cap = _num_elements;
    *_vec = (__vec_ptr)(&new_vec->data);

    return 1;
}

int __vector_resize(__vec_ptr* _vec, size_t _num_elements, size_t _element_size){
    if(_vec == NULL || _element_size == 0) return 0;
    if((*_vec) == NULL) return 0;
    __vector* v = __vector_struct(*_vec);

    if(v->len == _num_elements) return 1;

    size_t new_cap = 0;
    if(!__vector_calc_capacity(&new_cap, _num_elements)) return 0; //Overflow.

    if(new_cap != v->cap){
        __vector* new_vec = __vector_realloc(v, new_cap * _element_size);
        if(new_vec == NULL) return 0;

        v = new_vec;
        *_vec = (__vec_ptr)(&new_vec->data);
    }

    v->cap = new_cap;
    v->len = _num_elements;

    return 1;
}

int __vector_shrink(__vec_ptr* _vec, size_t _element_size){
    if(_vec == NULL || _element_size == 0) return 0;
    if((*_vec) == NULL) return 0;
    __vector* v = __vector_struct(*_vec);

    if(v->len == v->cap) return 1;

    __vector* new_vec = __vector_realloc(v, v->len * _element_size);
    if(new_vec == NULL) return 0;

    new_vec->cap = new_vec->len;
    *_vec = (__vec_ptr)(&new_vec->data);

    return 1;
}