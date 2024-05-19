#ifndef LAB_19_19_WORD_H
#define LAB_19_19_WORD_H

#include "String_lib.h"
#include <stdbool.h>

char *getEndOfString(char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;

    return end;
}

void removeNonLetters(char *s){
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void removeAdjacentEqualLetters(char *s) {

    if (strlen_(s) == 0){
        return;
    }

    int i, j;

    for (i = 0, j = 0; s[i] != '\0'; i++) {
        if ( *(s + i) != *(s + (i + 1))){
            s[j] = *(s + i);
            j++;
        }
    }

    s[j] = '\0';
}

void removeExtraSpaces(char *s){

    if (strlen_(s) == 0){
        return;
    }

    int i, j;

    for (i = 0, j = 0; s[i] != '\0'; i++) {
        if ( (*(s + i) != ' ') || (i > 0 && (*(s + (i - 1)) != ' '))){
            s[j] = *(s + i);
            j++;
        }
    }

    s[j] = '\0';
}

int getWord(char *beginSearch, WordDescriptor *word){
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}

void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1,
                                      _stringBuffer - 1,
                                      word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

void digitsToStart(char *s){

    char *beginSearch = s;
    WordDescriptor word;

    while (getWord(beginSearch, &word)){
        digitToStart(word);
        beginSearch = word.end;
    }
}

void digitsToSpaces(char *s){

    copy(s, getEndOfString(s), _stringBuffer);

    char *recPtr = s;
    char *readPtr = _stringBuffer;

    for (int i = 0; i < strlen(_stringBuffer); i++){

        if (strlen(s) >= MAX_STRING_SIZE){
            fprintf(stderr, "Out of MAX_STRING_SIZE");
            return;(1);
        }

        if (!isdigit(_stringBuffer[i])){
            *recPtr = *readPtr;
            recPtr++;
            readPtr++;
        }else{
            int amount = _stringBuffer[i] - '0';
            for (int j = 0; j < amount; j++){
                *recPtr = ' ';
                recPtr++;
            }
            readPtr++;
        }
    }
    *(_stringBuffer + 0) = '\0';
    *recPtr = '\0';
}

void replace(char *source, char *w1, char *w2) {


    size_t size_w1 = strlen(w1);
    size_t size_w2 = strlen(w2);
    WordDescriptor word1 = {w1, w1 + size_w1};
    WordDescriptor word2 = {w2, w2 + size_w2};
    char *readPtr, *recPtr;

    if (size_w1 >= size_w2){
        readPtr = source;
        recPtr = source;
    }else{
        copy(source, getEndOfString(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }

    while (*readPtr != '\0'){
        if (memcmp(readPtr, w1, size_w1) == 0){
            for (int i = 0; i < size_w2; i++){
                *recPtr = w2[i];
                recPtr++;
            }
            readPtr += size_w1;

        }else{
            *recPtr = *readPtr;
            readPtr++;
            recPtr++;
        }
    }
    *recPtr = '\0';
}

bool isWordsEqual(WordDescriptor w1, WordDescriptor w2){

    char *ptr1 = w1.begin;
    char *ptr2 = w2.begin;

    while (ptr1 <= w1.end && ptr2 <= w2.end) {
        if (*ptr1 != *ptr2){
            return 0;
        }

        ptr1++;
        ptr2++;
    }

    return ptr1 > w1.end && ptr2 > w2.end;

}

bool isWordsOrdered(char *s){

    WordDescriptor word1;
    WordDescriptor word2;

    if (getWord(s, &word1)){
        word2 = word1;
        while (getWord(s, &word1)){
            if (!isWordsEqual(word1, word2)){
                return false;
            }
            word2 = word1;
            s = word1.end;
        }

        return true;

    }else{
        return true;
    }
}

void getBagOfWords(BagOfWords *bag, char *s){

    WordDescriptor word;
    bag->size = 0;

    while (getWord(s, &word)){
        bag->words[bag->size] = word;
        bag->size++;
        s = word.end;
    }
}

char *Copy_Reverse(char *rbeginSource, const char *rendSource, char *beginDestination){
    while (rbeginSource != rendSource)
        (*beginDestination++) = *rbeginSource--;

    return beginDestination;
}

void reverseWordsBag(char *s){

    *copy(s, getEndOfString(s), _stringBuffer) = '\0';

    getBagOfWords(&_bag, _stringBuffer);

    char *copy_str = s;

    for (int i = 0; i < _bag.size; i++){
        copy_str = Copy_Reverse(_bag.words[i].end - 1, _bag.words[i].begin - 1, copy_str);
        *copy_str++ = ' ';
    }
    if (copy_str != s){
        copy_str--;
    }

    *copy_str = '\0';
}

bool isWordPalindrome(char *begin, char *end){

    while (begin < end){

        if (!isalpha(*begin)){
            begin++;
        }else if (!isalpha(*end)){
            end--;
        }else{

            if (tolower(*begin) != tolower(*end)) {
                return false;
            }
            begin++;
            end--;
        }
    }

    return true;
}

size_t WordsPalindromesAmount(char *s){

    char *end_str = getEndOfString(s);
    char *beginSearch = findNonSpace(s);

    int countPalindromes = 0;

    char *position_first_comma = find(beginSearch, end_str, ',');
    int last_comma = *position_first_comma == '\0' && end_str - beginSearch != 0;

    while (*position_first_comma != '\0' || last_comma){

        beginSearch = findNonSpace(beginSearch);
        countPalindromes += isWordPalindrome(beginSearch, position_first_comma);

        beginSearch = position_first_comma + 1;
        if (last_comma){
            break;
        }

        position_first_comma = find(beginSearch, end_str, ',');
        last_comma = *position_first_comma == '\0';
    }

    return countPalindromes;
}

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *w){
    if (s == NULL || strlen(s) == 0)
        return EMPTY_STRING;

    char *wordBegin = NULL;
    char *wordEnd = NULL;
    char *s_copy = strtok(s, " ");

    while (s_copy != NULL){
        bool found_a = false;
        for (int i = 0; s_copy[i] != '\0'; i++){
            if (tolower(s_copy[i]) == 'a'){
                found_a = true;
                break;
            }
        }

        if (found_a){

            if (wordBegin != NULL){
                w->begin = wordBegin;
                w->end = wordEnd;
                return WORD_FOUND;

            }else{
                return FIRST_WORD_WITH_A;
            }

        }else{
            wordBegin = s_copy;
            wordEnd = s_copy + strlen(s_copy);
        }

        s_copy = strtok(NULL, " ");
    }

    return NOT_FOUND_A_WORD_WITH_A;
}

WordDescriptor lastWordInFirstStringFindInSecondString(char *s1, char *s2){

    BagOfWords bag1, bag2;
    getBagOfWords(&bag1, s1);
    getBagOfWords(&bag2, s2);

    for (int i = bag1.size - 1; i >= 0; i--){
        WordDescriptor word = bag1.words[i];
        for (int j = 0; j < bag2.size; j++){
            if (isWordsEqual(word, bag2.words[j])){
                return word;
            }
        }
    }

    WordDescriptor emptyWord = {"", ""};
    return emptyWord;
}

void wordDescriptorToString(WordDescriptor word, char *destination){

    char *wordPtr = word.begin;
    while (wordPtr != word.end){
        *destination++ = *wordPtr++;
    }
    *destination = '\0';
}

bool isHasEqualWords(char *s) {

    BagOfWords bag;
    getBagOfWords(&bag, s);

    for (int i = 0; i < bag.size - 1; i++){
        for (int j = i + 1; j < bag.size; j++){
            if (isWordsEqual(bag.words[i], bag.words[j])){
                return true;
            }
        }
    }
    return false;
}

void wordToIntLetters(WordDescriptor *w, int res[]){

    int len = (w->end - w->begin);
    for (int i = 0; i < len; i++){
        int j = *(w->begin + i);
        res[j - 'a'] = 1;
    }
}

bool hasWordWithSameLetters(char *s){

    int word1_letters[27] = {0};
    int word2_letters[27] = {0};

    WordDescriptor word1, word2;
    word1.end = s;


    for (int i = 0; i < strlen(s); i++){
        getWord(word1.end, &word1);
        wordToIntLetters(&word1, &word1_letters);
        word2.end = word1.end;

        for (int j = i + 1; j < strlen(s); j++){
            getWord(word2.end, &word2);
            wordToIntLetters(&word2, &word2_letters);

            int amount = 0;
            for (int q = 0; q < 27; q++){
                if (word1_letters[q] == word2_letters[q]){
                    amount++;
                }
            }
            if (amount == 27){
                return  true;
            }
        }
    }
    return false;
}

char *srtingWithWordsNoLastWord(char *s){

    char *last_space = strrchr(s, ' ');
    if (last_space != NULL)
        *last_space = '\0';

    return s;
}

bool isWordInBag(BagOfWords bag, WordDescriptor word){
    for (int i = 0; i < bag.size; i++){
        if (strncmp(word.begin, bag.words[i].begin, word.end - word.begin) == 0){
            return true;
        }
    }
    return false;
}

WordDescriptor beforeEqualWordInStrings(char *s1, char *s2){

    BagOfWords bag, bag2;

    getBagOfWords(&bag, s1);
    getBagOfWords(&bag2, s2);

    for (int i = 0; i < bag.size; i++){
        if (isWordInBag(bag2, bag.words[i])){

            if (i != 0){
                return  bag.words[i - 1];

            }else{
                break;
            }
        }
    }

    WordDescriptor NULL_word = {NULL, NULL};

    return NULL_word;
}

void removePalindromes(char *s){

    BagOfWords bag;
    getBagOfWords(&bag, s);

    for (int i = 0; i < bag.size; i++) {
        WordDescriptor word = bag.words[i];

        if (isWordPalindrome(word.begin, word.end)){

            char *ptr = word.begin;
            while (ptr != word.end) {
                *ptr = ' ';
                ptr++;
            }
        }
    }

    removeExtraSpaces(s);
}

void addWordsToLowest(char *s1, char *s2){

    BagOfWords bag1, bag2;
    getBagOfWords(&bag1, s1);
    getBagOfWords(&bag2, s2);

    if (bag1.size < bag2.size){
        char *ptr1 = s1 + strlen_(s1);

        for (int i = bag1.size; i < bag2.size; i++){
            if (ptr1 != s1){
                *ptr1++ = ' ';
            }

            WordDescriptor word = bag2.words[i];
            char *wordPtr = word.begin;

            while (wordPtr != word.end){
                *ptr1++ = *wordPtr++;
            }
        }

        *ptr1 = '\0';
    }

    if (bag1.size > bag2.size){
        char *ptr2 = s2 + strlen_(s2);

        for (int i = bag2.size; i < bag1.size; i++){
            if (ptr2 != s1){
                *ptr2++ = ' ';
            }

            WordDescriptor word = bag2.words[i];
            char *wordPtr = word.begin;

            while (wordPtr != word.end){
                *ptr2++ = *wordPtr++;
            }
        }

        *ptr2 = '\0';
    }
}

bool hasStringWithWordLetters(char *s, char *word){

    int word1_letters[27] = {0};
    int word2_letters[27] = {0};

    WordDescriptor word1, w;
    word1.end = s;
    getWord(word, &w);
    wordToIntLetters(&w, &word1_letters);

    int letters_amount = 0;
    for (int i = 0; i < 27; i++){
        letters_amount += word1_letters[i];
    }

    int amount = 0;

    for (int i = 0; i < strlen(s); i++){
        getWord(word1.end, &word1);
        wordToIntLetters(&word1, &word2_letters);

        for (int q = 0; q < 27; q++){
            if (word1_letters[q] == 1 && word2_letters[q] == 1){
                amount++;
                word1_letters[q]++;
            }
        }
    }
    if (amount == letters_amount){
        return  true;
    }

    return false;
}

void free_bag(BagOfWords *b){
    for (int i = 0; i < b->size; i++){
        b->words[i].begin = NULL;
        b->words[i].end = NULL;
    }
    b->size = 0;
}

#endif //LAB_19_19_WORD_H
