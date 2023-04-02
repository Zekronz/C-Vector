# C Vector - Dynamic arrays in C.
Dynamic array implementation for C, inspired by C++ vectors.  
The library is designed to be as straight forward and easy-to-use as possible.  
It contains multiple functions for manipulating vectors, and elements can be accessed using the `[]` operator.  
Compatible with C++.

## Basic Usage
Creating vectors:
```c
float* a = vec_create(); // Creates an empty vector of floats.
int* b = vec_create_size(int, 16);  // Creates a vector with 16 elements of type int. Memory is uninitialized.
```

Freeing vectors:
```c
vec_free(v); // Frees the allocated memory of the vector.
```

Accessing elements:
```c
// Elements can be accessed using the [] operator. Note: This does not check if the index is within the vector's range.
float value = a[0];
b[0] = 32;

// You can also use vec_get/vec_set to read and write values. These functions contain boundary checks.
float value = vec_get(a, 0);
vec_set(b, 0, 32);
```

Adding/removing elements:
```c
vec_add(v, 32.0f); // Adds an element at the end of the vector.
vec_insert(v, 8, 16.0f); // Inserts an element into the vector at the specified index.
vec_delete(v, 0, 4); // Removes n elements from the vector at the specified index.
vec_clear(v); // Clears the entire vector and sets its length to 0.

// The vector will reallocate it's capacity if necessary.
```

Resizing vectors:
```c
vec_resize(v, 8); // Resizes the vector to the specified number of elements. Any new memory will be uninitialized.
vec_reserve(v, 16); // Reserves enough memory to contain the specified number of elements. Length will stay the same.
vec_shrink(v) // Shrinks the vector's capacity to its length.
```

Filling vectors:
```c
vec_fill(v, 4.0f); // Fills the entire vector with the specified value.
vec_fill_range(v, 16, 8, 4.0f); // Fills the vector at the specified position/length with the specified value.
```

Other functions:
```c
vec_length(v); // Returns the length of the vector.
vec_size(v); // Same as vec_length.
vec_capacity(v); // Returns the allocated capcity of the vector.
vec_empty(v); // Returns whether the vector is empty or not.
```

## Function List
```c
vec_create();
vec_create_size(type, num_elements);
vec_free(vec);
vec_get(vec, position);
vec_set(vec, position, value);
vec_add(vec, value);
vec_insert(vec, position, value);
vec_delete(vec, position, value);
vec_clear(vec);
vec_resize(vec, num_elements);
vec_reserve(vec, num_elements);
vec_shrink(vec);
vec_fill(vec, value);
vec_fill_range(vec, position, num_elements, value);
vec_length(vec);
vec_size(vec);
vec_capacity(vec);
vec_empty(vec);
```
