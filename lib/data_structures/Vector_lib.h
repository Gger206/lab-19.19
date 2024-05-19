#ifndef LAB_19_19_VECTOR_LIB_H
#define LAB_19_19_VECTOR_LIB_H

#include <stdbool.h>
#include <malloc.h>
#include <stdio.h>

typedef struct vector{
    int *data;
    size_t size;
    size_t capacity;
}vector;

vector createVector(size_t n){

    vector vector;

    vector.data = (int *) malloc(n * sizeof(int));
    vector.size = 0;
    vector.capacity = n;

    if (vector.data == NULL){
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    return vector;
}

void reserve(vector *v, size_t newCapacity){

    if (newCapacity == 0){
        v->data = NULL;
    }

    if (newCapacity < v->size){
        v->size = newCapacity;
    }

    v->capacity = newCapacity;
    v->data = (int *) realloc(v->data, newCapacity * sizeof(int));

    if (v->data == NULL){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

void clear(vector *v){

    v->data = NULL;

}

void shrinkToFit(vector *v){

    v->data = (int *) realloc(v->data, v->size);

}

void deleteVector(vector *v){

    free(v->data);
    v->size = 0;
    v->capacity = 0;

}

bool isEmpty(vector *v){

    return v->data == NULL;

}

bool isFull(vector *v){

    return v->size == v->capacity;

}

int getVectorValue(vector *v, size_t i){

    return v->data[i];

}

void pushBack(vector *v, int x){

    if (!v->capacity){
        reserve(v, 1);
    }

    if (v->size >= v->capacity){
        reserve(v, v->capacity * 2);
    }

    v->data[v->size++] = x;

}

void popBack(vector *v){

    if (!v->size){
        fprintf(stderr, "size = 0 error");
        exit(1);
    }

    v->data[v->size - 1] = NULL;
    v->size--;

}

int* atVector(vector *v, size_t index){

    if (v->size <= index){
        fprintf(stderr, "IndexError: a[index] is not exists");
        exit(1);
    }

    return &v->data[index];
}

int* back(vector *v){

    if (!v->size){
        return &v->data[v->size];
    }

    return &v->data[v->size - 1];
}

int* front(vector *v){

    return &v->data[0];
}

#endif
