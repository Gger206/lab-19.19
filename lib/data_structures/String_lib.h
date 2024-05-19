#ifndef STRING_LIB_H_INCLUDED
#define STRING_LIB_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

size_t strlen_(const char* begin){

    char *end = begin;
    while (*end != '\0'){
        end++;
    }
    return end - begin;
}

char* find(char *begin, char *end, int ch){

    while (begin != end && *begin != ch){
        begin++;
    }
    return begin;
}

char* findNonSpace(char *begin){

    while (*begin != '\0' && isspace(*begin)){
        begin++;
    }
    return begin;
}

char* findSpace(char* begin){

    while(*begin != '\0' && !isspace(*begin)){
        begin++;
    }
    return begin;
}

char* findNonSpaceReverse(char *rbegin, const char *rend){

    while (rbegin >= rend && isspace(*rbegin )){
        rbegin--;
    }
    return rbegin;
}

char* findSpaceReverse(char *rbegin, const char *rend){

    while(rbegin >= rend && !isspace(*(rbegin))){
        rbegin--;
    }
    return rbegin;
}

int strcmp(const char *lhs, const char *rhs){

    while (*lhs == *rhs && *lhs != '\0'){
        lhs++;
        rhs++;
    }
    return *lhs - *rhs;
}

char* copy(const char *beginSource, const char *endSource, char *beginDestination){

    size_t size = endSource - beginSource;

    memcpy(beginDestination, beginSource, size);

    *(beginDestination + size) = '\0';

    return beginDestination + size;
}

char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)){

    while (beginSource != endSource){
        if (f(*beginSource)){
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }

    return beginDestination;
}

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)){

    while (rbeginSource != rendSource){
        if (f(*(rbeginSource - 1))){
            *beginDestination = *(rbeginSource - 1);
            beginDestination++;
        }
        rbeginSource--;
    }

    return beginDestination;
}

#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20
#define English_Alphabet 26

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

BagOfWords _bag;
BagOfWords _bag2;

char _stringBuffer[MAX_STRING_SIZE + 1];

#endif