#include <stdio.h>
#include "lib\data_structures\Matrix.h"
#include <stdlib.h>
#include <assert.h>
#include "lib\data_structures\String_lib.h"
#include "lib\data_structures\Void_Vector_lib.h"
#include <stdbool.h>
#include "lib\data_structures\Words.h"
#include <math.h>

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
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_4_test_1.txt";

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
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_4_test_2.txt";

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
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_4_test_3.txt";

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

void generate_text_file(const char* filename, int lines, int word, int max_word_size) {

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < word; j++) {
            for (int k = 0; k < rand() % max_word_size + 1; k++) {
                fprintf(file, "%c", 'a' + rand() % 26);
            }
            fprintf(file, " ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void leave_longest_word(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }


    char buff[MAX_STRING_SIZE] = "";
    char* rec_ptr = _stringBuffer;

    fgets(buff, sizeof(buff), file);

    size_t length = strlen_(buff);
    length = length == 0 ? 1 : length;

    rec_ptr = copy(buff, buff + length - 1, rec_ptr);
    *rec_ptr++ = ' ';


    size_t amount_word_in_line = 0;
    char* begin_search = _stringBuffer;
    while (getWord(begin_search, &_bag.words[_bag.size])) {
        begin_search = _bag.words[_bag.size].end + 1;
        amount_word_in_line++;
        _bag.size++;
    }


    while (fgets(buff, sizeof(buff), file)) {
        rec_ptr = copy(buff, buff + strlen_(buff) - 1, rec_ptr);
        *rec_ptr++ = ' ';

        while (getWord(begin_search, &_bag.words[_bag.size])) {
            begin_search = _bag.words[_bag.size].end + 1;
            _bag.size++;
        }
    }

    fclose(file);


    file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (size_t i = 0; i < _bag.size; i += amount_word_in_line) {
        WordDescriptor word_max_length = _bag.words[i];
        size_t max_length = word_max_length.end - word_max_length.begin + 1;

        for (size_t j = i + 1; j < i + amount_word_in_line; j++) {
            size_t current_length = _bag.words[j].end - _bag.words[j].begin + 1;

            if (current_length > max_length) {
                word_max_length = _bag.words[j];
                max_length = current_length;
            }
        }

        char* write_ptr = word_max_length.begin;
        while (write_ptr <= word_max_length.end) {
            fprintf(file, "%c", *write_ptr);
            write_ptr++;
        }

        fprintf(file, "\n");
    }

    free_bag(&_bag);
    fclose(file);
}


void test_leave_longest_word_1_empty_file() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\task_5_test_1.txt";

    FILE* file = fopen(filename, "w");
    fclose(file);

    leave_longest_word(filename);

    file = fopen(filename, "r");

    char data[100] = "";
    fprintf(file, "%s", data);

    fclose(file);

    assert(strcmp(data, "") == 0);
}


void test_leave_longest_word_2_one_element_in_line() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_5_test_2.txt";

    char line1[] = "rty";
    char line2[] = "jkl";

    FILE* file = fopen(filename, "w");

    fprintf(file, "%s \n", line1);
    fprintf(file, "%s \n", line2);

    fclose(file);

    leave_longest_word(filename);

    file = fopen(filename, "r");

    char res_line1[4] = "";
    fscanf(file, "%s\n", res_line1);

    char res_line2[10] = "";
    fscanf(file, "%s\n", res_line2);

    char res_line3[4] = "";
    fscanf(file, "%s\n", res_line3);

    fclose(file);

    assert(strcmp(line1, res_line1) == 0);
    assert(strcmp(line2, res_line2) == 0);
}


void test_leave_longest_word_3_more_element_in_line() {
    const char filename[] = "DD:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_5_test_3.txt";

    char line1[] = "asdfghjkl rtg ";
    char line2[] = "ikmu qqe ";
    char line3[] = "cvb tyu ";

    FILE* file = fopen(filename, "w");

    fputs(line1, file);
    fprintf(file, "\n");
    fputs(line2, file);
    fprintf(file, "\n");
    fputs(line3, file);
    fprintf(file, "\n");

    fclose(file);

    leave_longest_word(filename);

    file = fopen(filename, "r");

    char res_line1[10] = "";
    fscanf(file, "%s\n", res_line1);

    char res_line2[10] = "";
    fscanf(file, "%s\n", res_line2);

    char res_line3[10] = "";
    fscanf(file, "%s\n", res_line3);

    fclose(file);

    char res1[] = "asdfghjkl";
    char res2[] = "ikmu";
    char res3[] = "cvb";

    assert(strcmp(res1, res_line1) == 0);
    assert(strcmp(res2, res_line2) == 0);
    assert(strcmp(res3, res_line3) == 0);
}


void test_leave_longest() {
    test_leave_longest_word_1_empty_file();
    test_leave_longest_word_2_one_element_in_line();
    test_leave_longest_word_3_more_element_in_line();
}

typedef struct monomial {
    size_t degree;
    double coefficient;
} monomial;

void generate_polynomial(const char* filename) {

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int amount_polynomial = rand() % 5 + 2;

    for (int k = 0; k < amount_polynomial; k++) {
        int amount_monomial = rand() % 5 + 1;

        monomial mono;
        for (int i = 0; i <= amount_monomial; i++) {
            mono.degree = amount_monomial - i;
            mono.coefficient = 2.0 * rand() / RAND_MAX - 1.0;

            fwrite(&mono, sizeof(monomial), 1, file);
        }
    }

    fclose(file);
}

double get_monomial_value(monomial mono, double x) {
    return pow(x, mono.degree) * mono.coefficient;
}

void remove_true_polynomial(const char* filename, double x) {
    vectorVoid v = createVoidVector(16, sizeof(monomial));

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    monomial mono;
    while (fread(&mono, sizeof(monomial), 1, file) == 1)
        pushBackVoid(&v, &mono);

    fclose(file);

    file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    monomial m;
    vectorVoid temp = createVoidVector(8, sizeof(monomial));
    double res = 0;
    for (size_t i = 0; i < v.size; i++) {
        getVoidVectorValue(&v, i, &m);
        pushBackVoid(&temp, &m);
        res += get_monomial_value(m, x);

        if (m.degree == 0) {
            if (fabs(res) >= 0.001) {
                monomial temp_mono;
                for (size_t j = 0; j < temp.size; j++) {
                    getVoidVectorValue(&temp, j, &temp_mono);
                    fwrite(&temp_mono, sizeof(monomial), 1, file);
                }
            }

            clearVoid(&temp);
            res = 0;
        }
    }

    deleteVoidVector(&v);
    deleteVoidVector(&temp);

    fclose(file);
}

void test_remove_true_polynomial_1_empty_file() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_6_test_1.txt";

    FILE* file = fopen(filename, "wb");
    fclose(file);

    remove_true_polynomial(filename, 1.0);

    file = fopen(filename, "rb");

    char data[10] = "";
    fscanf(file, "%s", data);

    fclose(file);

    assert(strcmp(data, "") == 0);
}

void test_remove_true_polynomial_2_not_true_expression() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_6_test_2.txt";

    double x = 2.0;
    monomial x_2 = {.coefficient = 5.0, .degree = 2};
    monomial x_1 = {.coefficient = 3.0, .degree = 1};
    monomial c = {.coefficient = 10.0, .degree = 0};

    FILE* file = fopen(filename, "wb");

    fwrite(&x_2, sizeof(monomial), 1, file);
    fwrite(&x_1, sizeof(monomial), 1, file);
    fwrite(&c, sizeof(monomial), 1, file);

    fclose(file);

    remove_true_polynomial(filename, x);

    file = fopen(filename, "rb");

    monomial res_x_2;
    fread(&res_x_2, sizeof(monomial), 1, file);

    monomial res_x_1;
    fread(&res_x_1, sizeof(monomial), 1, file);

    monomial res_c;
    fread(&res_c, sizeof(monomial), 1, file);

    fclose(file);

    assert(x_2.coefficient - res_x_2.coefficient <= 0.0001 && x_2.degree == res_x_2.degree);
    assert(x_1.coefficient - res_x_1.coefficient <= 0.0001 && x_1.degree == res_x_1.degree);
    assert(c.coefficient - res_c.coefficient <= 0.0001 && c.degree == res_c.degree);
}

void test_remove_true_polynomial_3_true_expression() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_6_test_3.txt";

    double x = -1.0;
    monomial x_2 = {.coefficient = 3.0, .degree = 2};
    monomial x_1 = {.coefficient = 6.0, .degree = 1};
    monomial c = {.coefficient = 3.0, .degree = 0};

    FILE* file = fopen(filename, "wb");

    fwrite(&x_2, sizeof(monomial), 1, file);
    fwrite(&x_1, sizeof(monomial), 1, file);
    fwrite(&c, sizeof(monomial), 1, file);

    fclose(file);

    remove_true_polynomial(filename, x);

    file = fopen(filename, "rb");

    char data[10] = "";
    fscanf(file, "%s", data);

    fclose(file);

    assert(strcmp(data, "") == 0);
}

void test_remove_true_polynomial() {
    test_remove_true_polynomial_1_empty_file();
    test_remove_true_polynomial_2_not_true_expression();
    test_remove_true_polynomial_3_true_expression();
}

void generate_numbers_array(const char* filename) {

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int amount_numbers = (int) rand() % 10 + 1;

    for (int i = 0; i < amount_numbers; i++) {
        int x = rand() % 200 - 100;
        fwrite(&x, sizeof(int), 1, file);
    }

    fclose(file);
}

void positive_first(const char* filename) {
    vector positive_numbers = createVector(2);
    vector negative_numbers = createVector(2);

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int current_number;
    while (fread(&current_number, sizeof(int), 1, file) == 1) {
        if (current_number >= 0)
            pushBack(&positive_numbers, current_number);
        else
            pushBack(&negative_numbers, current_number);
    }

    fclose(file);

    file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (int i = 0; i < positive_numbers.size; i++)
        fwrite(positive_numbers.data + i, sizeof(int), 1, file);

    for (int i = 0; i < negative_numbers.size; i++)
        fwrite(negative_numbers.data + i, sizeof(int), 1, file);

    deleteVector(&positive_numbers);
    deleteVector(&negative_numbers);
    fclose(file);
}

void test_positive_first_1_only_negative() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_7_test_1.txt";

    int x1 = -8;
    int x2 = -7;
    int x3 = -6;

    FILE* file = fopen(filename, "wb");

    fwrite(&x1, sizeof(int), 1, file);
    fwrite(&x2, sizeof(int), 1, file);
    fwrite(&x3, sizeof(int), 1, file);

    fclose(file);

    positive_first(filename);

    file = fopen(filename, "rb");

    int res_1, res_2, res_3;
    fread(&res_1, sizeof(int), 1, file);
    fread(&res_2, sizeof(int), 1, file);
    fread(&res_3, sizeof(int), 1, file);

    fclose(file);

    assert(x1 == res_1);
    assert(x2 == res_2);
    assert(x3 == res_3);
}

void test_positive_first_2_only_positive() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_7_test_2.txt";

    int x1 = 9;
    int x2 = 9;
    int x3 = 3;

    FILE* file = fopen(filename, "wb");

    fwrite(&x1, sizeof(int), 1, file);
    fwrite(&x2, sizeof(int), 1, file);
    fwrite(&x3, sizeof(int), 1, file);

    fclose(file);

    positive_first(filename);

    file = fopen(filename, "rb");

    int res_1, res_2, res_3;
    fread(&res_1, sizeof(int), 1, file);
    fread(&res_2, sizeof(int), 1, file);
    fread(&res_3, sizeof(int), 1, file);

    fclose(file);

    assert(x1 == res_1);
    assert(x2 == res_2);
    assert(x3 == res_3);
}

void test_positive_first_3_both() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_7_test_3.txt";

    int x5 = -7;
    int x1 = 1;
    int x2 = 0;
    int x3 = 0;
    int x4 = 0;

    FILE* file = fopen(filename, "wb");

    fwrite(&x5, sizeof(int), 1, file);
    fwrite(&x1, sizeof(int), 1, file);
    fwrite(&x2, sizeof(int), 1, file);
    fwrite(&x3, sizeof(int), 1, file);
    fwrite(&x4, sizeof(int), 1, file);

    fclose(file);

    positive_first(filename);

    file = fopen(filename, "rb");

    int res_1, res_2, res_3, res_4, res_5;
    fread(&res_1, sizeof(int), 1, file);
    fread(&res_2, sizeof(int), 1, file);
    fread(&res_3, sizeof(int), 1, file);
    fread(&res_4, sizeof(int), 1, file);
    fread(&res_5, sizeof(int), 1, file);

    fclose(file);

    assert(res_1 == x1);
    assert(res_2 == x2);
    assert(res_3 == x3);
    assert(res_4 == x4);
    assert(res_5 == x5);
}

void test_positive_first() {
    test_positive_first_1_only_negative();
    test_positive_first_2_only_positive();
    test_positive_first_3_both();
}

void generate_non_symmetric_matrix(const char* filename) {

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int n = rand() % 2 + 2;
    fwrite(&n, sizeof(int), 1, file);

    int amount_matrix = rand() % 3 + 1;

    for (int k = 0; k < amount_matrix; k++) {
        int matrix[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = rand() % 100;
            }
        }
        fwrite(matrix, sizeof(int), n * n, file);
    }

    fclose(file);
}

void transpose_non_symmetric_matrix(const char* filename) {
    FILE* file = fopen(filename, "r+b");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return;
    }

    int n;
    if (fread(&n, sizeof(int), 1, file) != 1) {
        printf("Ошибка при чтении порядка матрицы.\n");
        fclose(file);
        return;
    }

    while(1) {
        int matrix[n][n];
        size_t read_count = fread(matrix, sizeof(int), n * n, file);
        if (read_count != n * n) {
            if (feof(file)) {
                break;
            } else {
                printf("Ошибка при чтении матрицы.\n");
                break;
            }
        }

        if (!isSymmetricMatrix(matrix)) {
            transposeSquareMatrix(matrix);
            fseek(file, -(long int)read_count * sizeof(int), SEEK_CUR);
            fwrite(matrix, sizeof(int), read_count, file);
            fseek(file, (long int)read_count * sizeof(int), SEEK_CUR);
        }
    }

    fclose(file);
}

void test_transpose_non_symmetric_matrix_1_empty_matrix() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_8_test_1.txt";

    int n = 0;
    FILE* file = fopen(filename, "wb");

    fwrite(&n, sizeof(int), 1, file);

    fclose(file);

    file = fopen(filename, "rb");

    int res_n;
    fread(&res_n, sizeof(int), 1, file);

    fclose(file);

    assert(n == res_n);
}

void test_transpose_non_symmetric_matrix_2_symmetric_matrix() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_8_test_3.txt";

    FILE* file = fopen(filename, "wb");

    int n = 3;
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0,
                                              0, 0, 1}, 3, 3);

    fwrite(&n, sizeof(int), 1, file);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&m.values[i][j], sizeof(int), 1, file);

    fclose(file);

    transpose_non_symmetric_matrix(filename);

    file = fopen(filename, "rb");

    int res_n;
    fread(&res_n, sizeof(int), 1, file);
    matrix res_m = getMemMatrix(res_n, res_n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&res_m.values[i][j], sizeof(int), 1, file);

    fclose(file);

    assert(areTwoMatrixEqual(&res_m, &m));

    freeMemMatrix(&m);
    freeMemMatrix(&res_m);
}

void test_transpose_non_symmetric_matrix_3_non_symmetric_matrix() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_8_test_4.txt";

    FILE* file = fopen(filename, "wb");

    int n = 3;
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    fwrite(&n, sizeof(int), 1, file);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&m.values[i][j], sizeof(int), 1, file);

    fclose(file);

    transpose_non_symmetric_matrix(filename);

    file = fopen(filename, "rb");

    int res_n;
    fread(&res_n, sizeof(int), 1, file);
    matrix res_m = getMemMatrix(res_n, res_n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&res_m.values[i][j], sizeof(int), 1, file);

    fclose(file);

    matrix check = createMatrixFromArray((int[]) {1, 4, 7,
                                                  2, 5, 8,
                                                  3, 6, 9}, 3, 3);

    assert(res_n == n);
    assert(areTwoMatrixEqual(&res_m, &check));

    freeMemMatrix(&m);
    freeMemMatrix(&res_m);
    freeMemMatrix(&res_m);
}

void test_transpose_non_symmetric_matrix() {
    test_transpose_non_symmetric_matrix_1_empty_matrix();
    test_transpose_non_symmetric_matrix_2_symmetric_matrix();
    test_transpose_non_symmetric_matrix_3_non_symmetric_matrix();
}

#define MAX_AMOUNT_SPORTSMAN 20

typedef struct sportsman {
    char name[MAX_STRING_SIZE];
    double best_result;
} sportsman;

void generate_name(char* s) {
    int name_length = rand() % 30 + 5;

    char* rec_ptr = s;
    for (int i = 0; i < name_length; i++) {
        *rec_ptr = rand() % 26 + 97;
        rec_ptr++;
    }
    *rec_ptr = '\0';
}

void generate_team(const char* filename, const int n) {

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        sportsman s;
        generate_name(s.name);

        s.best_result = (double) rand() / 100;

        fwrite(&s, sizeof(sportsman),1, file);
    }

    fclose(file);
}

void sort_sportsman(sportsman sm[], const int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (sm[j].best_result < sm[j + 1].best_result) {
                sportsman temp = sm[j];
                sm[j] = sm[j + 1];
                sm[j + 1] = temp;
            }
}

void get_best_team(const char* filename, const int n) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    sportsman* team = (sportsman*) malloc(MAX_AMOUNT_SPORTSMAN * sizeof(sportsman));

    sportsman* rec_ptr = team;
    int amount_sportsman = 0;
    while (fread(rec_ptr, sizeof(sportsman), 1, file) == 1) {
        rec_ptr ++;
        amount_sportsman++;
    }

    fclose(file);

    file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    sort_sportsman(team, amount_sportsman);

    int amount_in_team = amount_sportsman >= n ? n : amount_sportsman;

    for (int i = 0; i < amount_in_team; i++) {
        fwrite(team + i, sizeof(sportsman), 1, file);
    }

    free(team);
    fclose(file);
}

void test_get_best_team_1_empty_file() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_9_test_1.txt";

    FILE* file = fopen(filename, "wb");
    fclose(file);

    get_best_team(filename, 0);

    file = fopen(filename, "rb");

    char res[100] = "";
    fread(res, sizeof(res), 1, file);

    fclose(file);

    assert(strcmp(res, "") == 0);
}

void test_get_best_team_2_n_more() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_9_test_2.txt";

    FILE* file = fopen(filename, "wb");

    sportsman s1 = {.best_result = 15.8, .name="first"};
    sportsman s2 = {.best_result = 8.51,  .name="second"};

    fwrite(&s1, sizeof(sportsman), 1, file);
    fwrite(&s2, sizeof(sportsman), 1, file);

    fclose(file);

    get_best_team(filename, 3);

    file = fopen(filename, "rb");

    sportsman res_1, res_2;
    fread(&res_1, sizeof(sportsman), 1, file);
    fread(&res_2, sizeof(sportsman), 1, file);

    fclose(file);

    assert(strcmp(s1.name, res_1.name) == 0 && fabs(s1.best_result - res_1.best_result) <= 0.001);
    assert(strcmp(s2.name, res_2.name) == 0 && fabs(s2.best_result - res_2.best_result) <= 0.001);
}

void test_get_best_team_3_n_less() {
    const char filename[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\task_9_test_3.txt";

    FILE* file = fopen(filename, "wb");

    sportsman s1 = {.best_result = 22.7, .name="first"};
    sportsman s2 = {.best_result = 16.65,  .name="second"};

    fwrite(&s1, sizeof(sportsman), 1, file);
    fwrite(&s2, sizeof(sportsman), 1, file);

    fclose(file);

    get_best_team(filename, 1);

    file = fopen(filename, "rb");

    sportsman res_1;
    fread(&res_1, sizeof(sportsman), 1, file);

    fclose(file);

    assert(strcmp(s1.name, res_1.name) == 0 && fabs(s1.best_result - res_1.best_result) <= 0.001);
}

void test_get_best_team() {
    test_get_best_team_1_empty_file();
    test_get_best_team_2_n_more();
    test_get_best_team_3_n_less();
}

typedef struct product {
    char product_name[MAX_STRING_SIZE];
    int unit_price;
    int total_cost;
    int quantity;
} product;

typedef struct order {
    char order_name[MAX_STRING_SIZE];
    int quantity;
} order;

void update_product(const char* filename1, const char* filename2) {
    vectorVoid v1 = createVoidVector(16, sizeof(product));
    vectorVoid v2 = createVoidVector(16, sizeof(order));

    FILE* file1 = fopen(filename1, "rb");
    if (file1 == NULL) {
        printf("reading error\n");
        exit(1);
    }

    product pr;
    while (fread(&pr, sizeof(product), 1, file1) == 1)
        pushBackVoid(&v1, &pr);

    fclose(file1);


    FILE* file2 = fopen(filename2, "rb");
    if (file2 == NULL) {
        printf("reading error\n");
        exit(1);
    }

    order od;
    while (fread(&od, sizeof(order), 1, file2) == 1)
        pushBackVoid(&v2, &od);

    for (size_t i = 0; i < v1.size; i++) {
        product curr_pr;
        getVoidVectorValue(&v1, i, &curr_pr);
        for (size_t j = 0; j < v2.size; j++) {
            order curr_od;
            getVoidVectorValue(&v2, j, &curr_od);

            if (strcmp(curr_pr.product_name, curr_od.order_name) == 0) {
                curr_pr.quantity = pr.quantity > od.quantity ? pr.quantity - od.quantity : 0;
                curr_pr.total_cost = pr.unit_price * curr_pr.quantity;
                setVoidVectorValue(&v1, i, &curr_pr);
            }
        }
    }

    file1 = fopen(filename1, "wb");

    for (size_t i = 0; i < v1.size; i++) {
        product read_pr;
        getVoidVectorValue(&v1, i, &read_pr);
        if (read_pr.quantity != 0)
            fwrite(&read_pr, sizeof(product), 1, file1);
    }

    deleteVoidVector(&v1);
    deleteVoidVector(&v2);

    fclose(file1);
}

void test_update_product_1_empty_files() {
    const char filename1[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_10_test_1.txt";
    const char filename2[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_10_test_1a.txt";

    FILE* file = fopen(filename1, "wb");
    fclose(file);

    file = fopen(filename2, "wb");
    fclose(file);

    update_product(filename1, filename2);

    char data1[10] = "";
    file = fopen(filename1, "rb");
    fread(data1, sizeof(data1), 1, file);
    fclose(file);

    char data2[10] = "";
    file = fopen(filename1, "rb");
    fread(data2, sizeof(data2), 1, file);
    fclose(file);

    assert(strcmp(data1, "") == 0);
    assert(strcmp(data2, "") == 0);
}

void test_update_product_2_order_more_product() {
    const char filename1[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_10_test_2.txt";
    const char filename2[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_10_test_2a.txt";

    product pr1 = {.product_name="name1", .unit_price=10, .total_cost=30, .quantity=3};
    product pr2 = {.product_name="name2", .unit_price=20, .total_cost=40, .quantity=2};
    order od = {.order_name="name2", .quantity=10};

    FILE* file = fopen(filename1, "wb");
    fwrite(&pr1, sizeof(product), 1, file);
    fwrite(&pr2, sizeof(product), 1, file);
    fclose(file);

    file = fopen(filename2, "wb");
    fwrite(&od, sizeof(order), 1, file);
    fclose(file);

    update_product(filename1, filename2);

    product res_pr;
    order res_od;

    file = fopen(filename1, "rb");
    fread(&res_pr, sizeof(product), 1, file);
    fclose(file);

    file = fopen(filename2, "rb");
    fread(&res_od, sizeof(order), 1, file);
    fclose(file);

    assert(strcmp(pr1.product_name, res_pr.product_name) == 0);
    assert(pr1.unit_price == res_pr.unit_price);
    assert(pr1.total_cost == res_pr.total_cost);
    assert(pr1.quantity == res_pr.quantity);
    assert(strcmp(od.order_name, res_od.order_name) == 0 && od.quantity == res_od.quantity);

}

void test_update_product_3_order_less_product() {
    const char filename1[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_10_test_3.txt";
    const char filename2[] = "D:\\BSTU Shukhov\\LionProjects\\lab_19_19\\task_10_test_3a.txt";

    product pr1 = {.product_name="name1", .unit_price=10, .total_cost=30, .quantity=3};
    product pr2 = {.product_name="name2", .unit_price=20, .total_cost=240, .quantity=12};
    order od = {.order_name="name2", .quantity=10};

    FILE* file = fopen(filename1, "wb");
    fwrite(&pr1, sizeof(product), 1, file);
    fwrite(&pr2, sizeof(product), 1, file);
    fclose(file);

    file = fopen(filename2, "wb");
    fwrite(&od, sizeof(order), 1, file);
    fclose(file);

    update_product(filename1, filename2);

    product res_pr1, res_pr2;
    order res_od;

    file = fopen(filename1, "rb");
    fread(&res_pr1, sizeof(product), 1, file);
    fread(&res_pr2, sizeof(product), 1, file);
    fclose(file);

    file = fopen(filename2, "rb");
    fread(&res_od, sizeof(order), 1, file);
    fclose(file);

    assert(strcmp(pr1.product_name, res_pr1.product_name) == 0);
    assert(pr1.unit_price == res_pr1.unit_price);
    assert(pr1.total_cost == res_pr1.total_cost);
    assert(pr1.quantity == res_pr1.quantity);

    assert(strcmp(pr2.product_name, res_pr2.product_name) == 0);
    assert(pr2.unit_price == res_pr2.unit_price);
    assert(res_pr2.total_cost == 40);
    assert(res_pr2.quantity == 2);

    assert(strcmp(od.order_name, res_od.order_name) == 0 && od.quantity == res_od.quantity);
}

void test_update_product() {
    test_update_product_1_empty_files();
    test_update_product_2_order_more_product();
    test_update_product_3_order_less_product();
}

int main(){

    test_matrix_transpose();
    test_convert_float();
    test_calculate();
    test_filter_word();
    test_leave_longest();
    test_remove_true_polynomial();
    test_positive_first();
    test_transpose_non_symmetric_matrix();
    test_get_best_team();
    test_update_product();
}