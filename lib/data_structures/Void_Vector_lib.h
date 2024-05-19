#ifndef VOID_VECTOR_lib_H_INCLUDED
#define VOID_VECTOR_lib_H_INCLUDED

#include <limits.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct vectorVoid{
    void *data;
    size_t size;
    size_t capacity;
    size_t baseTypeSize;// размер базового типа:
    // например, если вектор хранит int -
    // то поле baseTypeSize = sizeof(int)
    // если вектор хранит float -
    // то поле baseTypeSize = sizeof(float)
}vectorVoid;

vectorVoid createVoidVector(size_t n, size_t baseTypeSize){

    vectorVoid vector;

    vector.data = malloc(n * baseTypeSize);
    vector.size = 0;
    vector.capacity = n;

    if (vector.data == NULL){
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    vector.baseTypeSize = baseTypeSize;

    return vector;
}

void reserveVoid(vectorVoid *v, size_t newCapacity){

    if (newCapacity == 0){
        v->data = NULL;
    }

    if (newCapacity < v->size){
        v->size = newCapacity;
    }

    v->capacity = newCapacity;
    v->data = (void *) realloc(v->data, newCapacity * v->baseTypeSize);

    if (v->data == NULL){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

void shrinkToFitVoid(vectorVoid *v){

    v->data = (void *) realloc(v->data, v->size);

}

void clearVoid(vectorVoid *v){

    v->data = NULL;
}

void deleteVoidVector(vectorVoid *v){

    free(v->data);
    v->size = 0;
    v->capacity = 0;
    v->baseTypeSize = 0;
}

bool isEmptyVoid(vectorVoid *v){

    return v->data == NULL ? true : false;
}

bool isFullVoid(vectorVoid *v){

    return v->size == v->capacity ? true : false;
}

void getVoidVectorValue(vectorVoid *v, size_t index, void *destination){

    char *source = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);

}

void setVoidVectorValue(vectorVoid *v, size_t index, void *source){

    char *destination = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);

}

void popBackVoid(vectorVoid *v){

    if (!v->size){
        fprintf(stderr, "size = 0 error");
        exit(1);
    }

    (v->size)--;

}

void pushBackVoid(vectorVoid *v, void *source){

    if (v->size >= v->capacity){
        size_t newCapacity = (v->capacity == 0) ? 1: v->capacity * 2;
        reserveVoid(v,newCapacity);
    }

    char *destination = (char *) v->data + v->size * v->baseTypeSize;

    memcpy(destination, source, v->baseTypeSize);
    (v->size)++;
}

#endif
