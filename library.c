#include <stdio.h>
#include "lib\data_structures\Matrix.h"
#include <stdlib.h>
#include <assert.h>
#include "lib\data_structures\String_lib.h"
#include "lib\data_structures\Void_Vector_lib.h"
#include <stdbool.h>
#include "lib\data_structures\Words.h"

void generate_random_matrix_file(const char* filename, size_t n) {

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    fprintf(file, "%lld\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", rand() % 10);
        }

        fprintf(file, "\n");
    }

    fclose(file);
}

void transpose_matrix_in_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    long long int n;
    fscanf(file, "%lld", &n);

    matrix matrix = getMemMatrix((int) n , (int) n);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &matrix.values[i][j]);

    fclose(file);

    transposeSquareMatrix(&matrix);

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", matrix.values[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);

    freeMemMatrix(&matrix);
}


void test_matrix_transpose_1_one_element_matrix() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_1_test_1.txt";

    int n = 1;
    int element = 10;

    FILE* file = fopen(filename, "w");

    fprintf(file, "%d\n", n);
    fprintf(file, "%d\n", element);

    fclose(file);

    transpose_matrix_in_file(filename);

    file = fopen(filename, "r");

    int n_res, element_res;
    fscanf(file, "%d\n", &n_res);
    fscanf(file, "%d\n", &element_res);

    assert(element == element_res);

    fclose(file);
}

void test_matrix_transpose_2_unit_symmetric_matrix() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_1_test_2.txt";
    int n = 3;
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0,
                                              0, 0, 1}, 3, 3);

    FILE* file = fopen(filename, "w");

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", m.values[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);

    transpose_matrix_in_file(filename);

    int n_res;
    matrix m_res_test = getMemMatrix(n, n);

    file = fopen(filename, "r");

    fscanf(file, "%d\n", &n_res);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &m_res_test.values[i][j]);

    fclose(file);

    assert(areTwoMatrixEqual(&m, &m_res_test));

    freeMemMatrix(&m);
    freeMemMatrix(&m_res_test);
}


void test_matrix_transpose_3_matrix() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_1_test_3.txt";
    int n = 3;
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    matrix m_res = createMatrixFromArray((int[]) {1, 4, 7,
                                                  2, 5, 8,
                                                  3, 6, 9}, 3, 3);

    FILE* file = fopen(filename, "w");

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", m.values[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);

    transpose_matrix_in_file(filename);

    int n_res;
    matrix m_res_test = getMemMatrix(n, n);

    file = fopen(filename, "r");

    fscanf(file, "%d\n", &n_res);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &m_res_test.values[i][j]);

    fclose(file);

    assert(areTwoMatrixEqual(&m_res, &m_res_test));

    freeMemMatrix(&m);
    freeMemMatrix(&m_res_test);
    freeMemMatrix(&m_res);
}

void test_matrix_transpose() {
    test_matrix_transpose_1_one_element_matrix();
    test_matrix_transpose_2_unit_symmetric_matrix();
    test_matrix_transpose_3_matrix();
}

void generate_float(const char* filename, int n) {

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (size_t i = 0; i < n; i++)
        fprintf(file, "%f ", 10.0 * rand() / RAND_MAX);

    fclose(file);
}

void convert_float(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    vectorVoid v = createVoidVector(0, sizeof(float));

    while (!feof(file)) {
        float x;
        fscanf(file, "%f", &x);

        pushBackVoid(&v, &x);
    }

    fclose(file);

    file = fopen(filename, "w");

    for (size_t i = 0; i < v.size; i++) {
        float x;
        getVoidVectorValue(&v, i, &x);
        fprintf(file, "%.2lf ", x);
    }

    deleteVoidVector(&v);
    fclose(file);
}


void test_convert_float_1_zero_numbers() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_2_test_1.txt";

    FILE* file = fopen(filename, "w");
    fclose(file);

    convert_float(filename);

    file = fopen(filename, "r");

    char data[10] = "";
    fscanf(file, "%s", data);

    fclose(file);

    assert(strcmp(data, "0.00") == 0);
}

void test_convert_float_2_one_number() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_2_test_2.txt";

    float number = 404.7891462156415651;

    FILE* file = fopen(filename, "w");

    fprintf(file, "%f", number);

    fclose(file);

    convert_float(filename);

    file = fopen(filename, "r");

    char data[10] = "";
    fscanf_s(file, "%s", data);

    fclose(file);

    char res[10] = "404.78";

    assert(strcmp(data, res) == 0);
}

void test_convert_float_3_three_numbers() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_2_test_3.txt";

    float number1 = 7.143423;
    float number2 = 2.241518;
    float number3 = 9.353738;

    FILE* file = fopen(filename, "w");

    fprintf(file, "%f %f %f",number1, number2,number3);

    fclose(file);

    convert_float(filename);

    file = fopen(filename, "r");

    char data[100] = "";
    fgets(data, sizeof(data), file);

    fclose(file);

    char res[100] = "7.14 2.24 9.35 ";

    assert(strcmp(data, res) == 0);
}

void test_convert_float() {
    test_convert_float_1_zero_numbers();
    test_convert_float_2_one_number();
    test_convert_float_3_three_numbers();
}

void generate_expression(const char *file_name) {

    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int x1 = rand() % 10;
    int x2 = rand() % 10;
    int x3 = rand() % 10;

    char operators[] = "+-*/";
    char op1 = operators[rand() % 4];
    char op2 = operators[rand() % 4];

    bool one_operation = rand() % 2;

    if (one_operation)
        fprintf(file, "(%d %c %d)", x1, op1, x2);
    else
        fprintf(file, "(%d %c %d) %c %d", x1, op1, x2, op2, x3);

    fclose(file);
}

void calculate_expression(const char* filename) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int x1, x2, x3;
    char op1, op2;
    char open_bracket, close_bracket;
    float result;

    int amount_element = fscanf(file, "%c%d %c %d%c %c %d", &open_bracket, &x1, &op1, &x2, &close_bracket, &op2, &x3);

    bool two_operation = amount_element == 7 ? true : false;

    switch (op1) {
        case '+':
            result = x1 + x2;
            break;
        case '-':
            result = x1 -x2;
            break;
        case '*':
            result = x1 * x2;
            break;
        case '/':
            if (x2 == 0) {
                fprintf(stderr, "Zero division");
                exit(1);
            }
            result = x1 / x2;
            break;
        default:
            fprintf(stderr,"unknown operation");
            exit(1);
    }

    if (two_operation) {
        switch (op2) {
            case '+':
                result += x3;
                break;
            case '-':
                result -= x3;
                break;
            case '*':
                result *= x3;
                break;
            case '/':
                if (x3 == 0) {
                    fprintf(stderr, "Zero division");
                    exit(1);
                }
                result /= x3;
                break;
            default:
                fprintf(stderr,"unknown operation");
                exit(1);
        }
    }

    fseek(file, 0, SEEK_END);
    fprintf(file, " = %.2f", result);

    fclose(file);
}

void test_calculate_expression_2_operand() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_3_test_1.txt";

    char expression[] = "(2 * 4)";
    FILE* file = fopen(filename, "w");

    fputs(expression, file);

    fclose(file);

    calculate_expression("D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_3_test_1.txt");

    file = fopen(filename, "r");

    char data[100] = "";
    fgets(data, sizeof(data), file);

    fclose(file);

    char res[] = "(2 * 4) = 8.00 ";

    assert(strcmp(data, res));
}

void test_calculate_expression_3_operand() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_3_test_2.txt";

    char expression[] = "(2 * 8) + 3";
    FILE* file = fopen(filename, "w");

    fputs(expression, file);

    fclose(file);

    calculate_expression("D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_3_test_2.txt");

    file = fopen(filename, "r");

    char data[100] = "";
    fgets(data, sizeof(data), file);

    fclose(file);

    char res[] = "(2 * 3) + 3 = 19.00 ";

    assert(strcmp(data, res));
}

void test_calculate() {
    test_calculate_expression_2_operand();
    test_calculate_expression_3_operand();
}

void generate_string(const char* filename, char* source_string) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    size_t string_length = strlen_(source_string);

    for (size_t i = 0; i <= string_length; i++)
        fprintf(file, "%c", source_string[i]);

    fclose(file);
}

int compare_letters(const void* s1, const void* s2) {
        return *(const unsigned char*) s1 - *(const unsigned char*) s2;
}

void sort_word_letters(WordDescriptor* word) {
    qsort(word->begin, word->end - word->begin + 1, sizeof(char), compare_letters);
}

bool is_letters_in_word(WordDescriptor sub_word, WordDescriptor word) {
    bool include[English_Alphabet] = {0};

    char* start = word.begin;
    char* end = word.end + 1;

    while (start != end) {
        if (isalpha(*start))
            include[*start - 97] = true;

        start++;
    }

    while (sub_word.begin + 1 <= sub_word.end) {
        if (!include[*(sub_word.begin + 1) - 97])
            return false;

        sub_word.begin++;
    }

    return true;
}

void filter_word(const char* filename, char* source_word) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (length == 0){
        return;
        }

    fread(_stringBuffer, sizeof(char), length, file);
    _stringBuffer[length] = '\0';

    fclose(file);

    WordDescriptor word;
    getWord(source_word, &word);
    sort_word_letters(&word);

    BagOfWords words = {.size = 0};
    char* begin_search = _stringBuffer;
    while (getWord(begin_search, &words.words[words.size])) {
        begin_search = words.words[words.size].end + 1;
        words.size++;
    }

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (size_t i = 0; i < words.size; i++) {
        if (is_letters_in_word(word, words.words[i])) {
            while (words.words[i].begin <= words.words[i].end) {
                fprintf(file, "%c", *words.words[i].begin);
                words.words[i].begin++;
            }
            fprintf(file, " ");
        }
    }

    fprintf(file, "%c", '\0');

    fclose(file);
}


void test_filter_word_1_empty_file() {
    const char filename[] = "D:\\GitHub\\OP\\Lab19\\task_4_test_1.txt";

    generate_string(filename, "");
    char source_word[] = "word";
    filter_word(filename, source_word);

    FILE* file = fopen(filename, "r");
    char data[10] = "";
    fscanf(file, "%s", data);
    fclose(file);

    assert(strcmp(data, "") == 0);
}


void test_filter_word_2_sequence_not_in() {
    const char filename[] = "D:\\GitHub\\OP\\Lab19\\task_4_test_2.txt";

    generate_string(filename, "qwe rtg ngfm");
    char source_word[] = "bgmk";
    filter_word(filename, source_word);

    FILE* file = fopen(filename, "r");
    char data[10] = "";
    fscanf(file, "%s", data);
    fclose(file);

    assert(strcmp(data, "") == 0);
}

void test_filter_word_3_sequence_in() {
    const char filename[] = "D:\\GitHub\\OP\\Lab19\\task_4_test_3.txt";

    generate_string(filename, "bvgh vhv jaef kfk");
    char source_word[] = "v";
    filter_word(filename, source_word);

    FILE* file = fopen(filename, "r");
    char data[40] = "";
    fgets(data, sizeof(data), file);
    fclose(file);

    assert(strcmp(data, "bvgh  vhv   ") == 0);
}

void test_filter_word() {
    test_filter_word_1_empty_file();
    test_filter_word_2_sequence_not_in();
    test_filter_word_3_sequence_in();
}

int main(){

    test_matrix_transpose();
    test_convert_float();
    test_calculate();
    test_filter_word();
}