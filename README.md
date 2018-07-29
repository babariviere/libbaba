# lib baba: A set of structures and functions for C to do things faster

## Buffer

The buffer is an array with dynamic size. It avoids reallocation and so performance loose.

An empty buffer will not allocate any memory.

Each allocation are directly made by `buf_push` or `buf_realloc`.

## Stack

The stack is a small stack on the stack. It will create a large array that behave like a stack.

## Fat pointer

A fat pointer is a pointer to a data with his knows size. It is usefull for array with dynamic size.

It avoids manual calculation.
