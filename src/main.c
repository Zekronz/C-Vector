#include <stdio.h>
#include "vector.h"

int main(){
    
    float* v = vec_create(float, 0);
    /*v[0] = 5.0f;
    v[1] = 2.0f;
    v[2] = 3.0f;
    v[3] = 2.0f;
    v[4] = 2.0f;
    v[5] = 2.0f;
    v[6] = 2.0f;
    v[7] = 3.0f;

    printf("%u\n", vec_capacity(v));*/

    //@TODO: Clear vector, and fill vector (range?).

    vec_insert(v, 16, 5.0f);
    for(size_t i = 0; i < vec_length(v); ++i) vec_set(v, i, (float)(i * 2));
    vec_set(v, 0, 1.0f);
    vec_set(v, 1, 2.0f);
    vec_set(v, 2, 4.0f);
    vec_set(v, 3, 8.0f);

    vec_delete(v, vec_length(v) - 1, 1);

    for(size_t i = 0; i < vec_length(v); ++i) printf("%f\n", vec_get(v, i));

    vec_free(v);

    return 0;

}