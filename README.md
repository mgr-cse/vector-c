# STL-like Vectors for pure C

Well, not really. This implementation has a lot of pitfalls.
After all it is very easy to shoot yourself in the foot! Don't
forget you are using C.

## Why?

STL vector is a really useful template abstraction. For instance
the dynamic memory allocation of vector makes it so easy to
parse input of an arbitrary size. This is a headache in pure C.

## How to use it?

We wrap vector functions by using a couple of `#define`s. Use
the following to perform operations:

- `VEC_INIT(type, n)`: Takes in datatype `type` and returns a
`vector`.

- `VEC_PUSH_BACK(type, v, e)`: Takes in datatype `type`, a vector
`v` and an element `e` to push into `v`.
Amortized insertion time `O(n)`

- `VEC_POP_BACK(type, v)`: Takes in datatype `type`, a vector `v`.
Pops the last element. Make sure to manually store the element to be
popped before. This function should only be used for deallocating
memory if you want to shrink the size of vector.

- `VEC_CLEAR(v)`:Takes in a vector `v`. Deallocates all the memory
used by the vector.

- `VEC_SET(type v, i, e)`: Similar to `v[i] = e`.

- `VEC_GET(type v, i)`: similar to `v[i]`.

See `vec_test.c` file for a sample usage.

