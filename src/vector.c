#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"

vec_ptr __vector_create(size_t _data_size, size_t _cap, size_t _len){
    __vector* v = (__vector*)malloc(sizeof(__vector) + _data_size);
    if(v == NULL) return NULL;

    v->cap = _cap;
    v->len = _len;

    return (vec_ptr)(&v->data);
}

void __vector_free(vec_ptr _vec){
    if(_vec == NULL) return;
    free(__vector_struct(_vec));
}

__vector* __vector_struct(vec_ptr _vec){
    if(_vec == NULL) return NULL;
    return ((__vector*)_vec) - 1;
}

size_t __vector_length(vec_ptr _vec){
    if(_vec == NULL) return 0;
    return __vector_struct(_vec)->len;
}

size_t __vector_capacity(vec_ptr _vec){
    if(_vec == NULL) return 0;
    return __vector_struct(_vec)->cap;
}

__vector* __vector_realloc(__vector* _vec, size_t _data_size){
    if(_vec == NULL) return NULL;

    __vector* new_vec = (__vector*)realloc(_vec, sizeof(__vector) + _data_size);
    if(new_vec == NULL) return NULL;

    return new_vec;
}

int __vector_inc(vec_ptr* _vec, size_t _num_elements, size_t _element_size){
    if(_vec == NULL || _num_elements == 0 || _element_size == 0) return 0;
    __vector* v = __vector_struct(*_vec);
    
    size_t new_len = v->len + _num_elements;
    if(new_len < v->len) return 0; //Overflow.

    if(new_len > v->cap){
        size_t new_cap = (v->cap == 0) ? 1 : v->cap * 2;
        while(new_cap < new_len) new_cap *= 2;

        __vector* new_vec = __vector_realloc(v, _element_size * new_cap);
        if(new_vec == NULL) return 0;
        printf("Allocated %u\n", new_cap);
        v = new_vec;
        v->cap = new_cap;

        *_vec = (vec_ptr)(&v->data);
    }

    v->len = new_len;

    return 1;
}

int __vector_insert(vec_ptr* _vec, size_t _index, size_t _element_size){
    if(_vec == NULL || _element_size == 0) return 0;
    __vector* v = __vector_struct(*_vec);

    size_t old_len = v->len;
    size_t new_len = (_index <= old_len) ? old_len + 1 : old_len + (_index - old_len) + 1;
    if(!__vector_inc(_vec, new_len - old_len, _element_size)) return 0;

    vec_ptr ptr = *_vec;
    if(_index < old_len) memmove(ptr + (_index * _element_size) + _element_size, ptr + (_index * _element_size), (old_len - _index) * _element_size);

    return 1;
}

int __vector_delete(vec_ptr* _vec, size_t _index, size_t _num_elements, size_t _element_size){
    if(_vec == NULL || _element_size == 0 || _num_elements == 0) return 0;
    __vector* v = __vector_struct(*_vec);

    if(_index >= v->len) return 0;
    if(_index + _num_elements - 1 >= v->len) _num_elements = (v->len - _index);

    size_t new_len = v->len - _num_elements;
    size_t old_cap = v->cap;
    size_t new_cap = (new_len == 0) ? 0 : 1;
    while(new_cap < new_len) new_cap *= 2;

    //@TODO: Move memory if necessary.
    

    if(old_cap != new_cap){
        __vector* new_vec = __vector_realloc(v, _element_size * new_cap);
        if(new_vec == NULL) return 0;
        printf("Reallocated %u\n", new_cap);
        v = new_vec;
        *_vec = (vec_ptr)(&v->data);
    }

    v->len = new_len;
    v->cap = new_cap;

    return 1;
}

int __vector_set(vec_ptr _vec, size_t _index){
    if(_vec == NULL) return 0;
    __vector* v = __vector_struct(_vec);

    if(_index >= v->len){
        //@TODO: Error message.
        printf("Oh no.\n");
        return 0;
    }

    return 1;
}

int __vector_get(vec_ptr _vec, size_t _index){
    if(_vec == NULL) return 0;
    __vector* v = __vector_struct(_vec);

    if(_index >= v->len){
        //@TODO: Error message.
        printf("Oh no.\n");
        return 0;
    }

    return 1;
}