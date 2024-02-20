#include "s21_calc.h"

struct elem element[MAX] = {
    {0, 0, 0, 0},
    {2, 0, 1, 2},  // Сложение
    {2, 0, 2, 2},  // Вычитание
    {2, 0, 3, 3},  // Умножение
    {2, 0, 4, 3},  // Деление
    {2, 0, 5, 5},  // Возведение в степень
    {2, 0, 6, 3},  // Остаток от деления
    {2, 0, 7, 4},  // Унарный плюс
    {2, 0, 8, 4},  // Унарный минус
    {2, 0, 9, 6},  // Косинус
    {2, 0, 10, 6},  // Синус
    {2, 0, 11, 6},  // Тангенс
    {2, 0, 12, 6},  // Арккосинус
    {2, 0, 13, 6},  // Арксинус
    {2, 0, 14, 6},  // Арктангенс
    {2, 0, 15, 5},  // Квадратный корень
    {2, 0, 16, 6},  // Натуральный логарифм
    {2, 0, 17, 6},  // Десятичный логарифм
    {2, 0, 18, 6},  // Унарный плюс степени
    {2, 0, 19, 6},  // Унарный минус степени
    {4, 0, 20, 0},  // Скобка открывающая, значение функции
    {4, 0, 21, 0},  // Скобка открывающая
    {4, 0, 22, 0}  // Скобка закрывающая
};

elem_t input[MAX];  // Перевод элементов строки в элементы структуры input
elem_t stack[MAX];  // Для обратная польская нотация
elem_t output[MAX];  // Для обратная польская нотация
elem_t result[MAX];  // Для получения результата
elem_t x[MAX];  // Для хранения Икс

int input2elem(int num_elem, int num_arg) {
            input[num_arg] = element[num_elem];
            num_arg++;
            input[num_arg] = element[20];
            num_arg++;
    return num_arg;
}
int input1elem(int num_elem, int num_arg) {
    input[num_arg] = element[num_elem];
    num_arg++;
    return num_arg;
}
int func2arg(double res_func, int num_arg) {
    delet(&result[num_arg - 2]);
    delet(&result[num_arg - 1]);
    num_arg--;
    num_arg--;
    result[num_arg].number = res_func;
    num_arg++;
    return num_arg;
}
int func1arg(double res_func, int num_arg) {
    delet(&result[num_arg - 1]);
    num_arg--;
    result[num_arg].number = res_func;
    num_arg++;
    return num_arg;
}
void initialization(elem_t *A) {
    for (int t = 0; t < MAX; t++) {
        A[t].elemnts = 0;
        A[t].number = 0;
        A[t].operation = 0;
        A[t].priority = 0;
    }
}
void delet(elem_t *A) {
    A->elemnts = 0;
    A->number = 0;
    A->operation = 0;
    A->priority = 0;
}
void copy(elem_t *A, elem_t *B) {
    B->elemnts = A->elemnts;
    B->number = A->number;
    B->operation = A->operation;
    B->priority = A->priority;
}
int check_string(char *str) {
    int FlagError = 0;
    for (int i = 0; i < (int)strlen(str); i++) {
        // один символ
        if ((str[i] == '0') ||(str[i] == '1') ||(str[i] == '2') ||(str[i] == '3') ||(str[i] == '4')
            ||(str[i] == '5') ||(str[i] == '6') ||(str[i] == '7') ||(str[i] == '8') ||(str[i] == '9')
            ||(str[i] == '.') ||(str[i] == '+') ||(str[i] == '-') ||(str[i] == '*') ||(str[i] == '/')
            ||(str[i] == '^') ||(str[i] == '(') ||(str[i] == ')') ||(str[i] == 'x')) {
        } else {
            // три символ
            if (((str[i] == 'l')&&(str[i+1] == 'n')&&(str[i+2] == '('))
                ||((str[i] == 'm')&&(str[i+1] == 'o')&&(str[i+2] == 'd'))) {
                i = i+2;
            } else {
                // четыре символ
                if (((str[i] == 'c')&&(str[i+1] == 'o')&&(str[i+2] == 's')&&(str[i+3] == '('))
                ||((str[i] == 's')&&(str[i+1] == 'i')&&(str[i+2] == 'n')&&(str[i+3] == '('))
                ||((str[i] == 't')&&(str[i+1] == 'a')&&(str[i+2] == 'n')&&(str[i+3] == '('))
                ||((str[i] == 'l')&&(str[i+1] == 'o')&&(str[i+2] == 'g')&&(str[i+3] == '('))) {
                    i = i+3;
                } else {
                    // пять символ
                    if (((str[i] == 'a')&&(str[i+1] == 'c')&&(str[i+2] == 'o')&&(str[i+3] == 's')
                        &&(str[i+4] == '('))
                        ||((str[i] == 'a')&&(str[i+1] == 's')&&(str[i+2] == 'i')&&(str[i+3] == 'n')
                        &&(str[i+4] == '('))
                        ||((str[i] == 'a')&&(str[i+1] == 't')&&(str[i+2] == 'a')&&(str[i+3] == 'n')
                        &&(str[i+4] == '('))
                        ||((str[i] == 's')&&(str[i+1] == 'q')&&(str[i+2] == 'r')&&(str[i+3] == 't')
                        &&(str[i+4] == '('))) {
                        i = i+4;
                    } else {
                        FlagError = 1;
                    }
                }
            }
        }
        if ((i == 0)
            &&((str[i] == '*') ||(str[i] == '/') ||(str[i] == '^') ||(str[i-1] == 'm'))) {
            FlagError = 1;
        }
        if ((str[i] == '*') ||(str[i] == '/') ||(str[i] == '^')) {
            if ((str[i-1] == 'x') ||(str[i-1] == ')') ||(('0' <= str[i-1])&&(str[i-1] <= '9'))) {
                if ((str[i+1] == 'x') ||(str[i+1]== 's') ||(str[i+1]== 'c') ||(str[i+1]== 't')
                    ||(str[i+1]== 'a') ||(str[i+1]== 'l') ||(str[i+1]== '(') ||(str[i+1]== '+')
                    ||(str[i+1]== '-') ||(('0' <= str[i+1])&&(str[i+1] <= '9'))) {
                } else {
                    FlagError = 1;
                }
            } else {
                FlagError = 1;
            }
        }
        if (str[i] == 'x') {
            if (('0' <= str[i-1])&&(str[i-1] <= '9')) FlagError = 1;
            if (('0' <= str[i+1])&&(str[i+1] <= '9')) FlagError = 1;
        }
        if ((str[i] == 'm') ||(str[i+1] == 'o') ||(str[i+2] == 'd')) {
            if ((str[i-1] == 'x') ||(str[i-1] == ')') ||(('0' <= str[i-1])&&(str[i-1] <= '9'))) {
            } else {
                FlagError = 1;
            }
        }
        if (((str[i] == '-') ||(str[i] == '+'))
            &&((str[i+1] == '-') ||(str[i+1] == '+'))
            &&((str[i+2]== '+') ||(str[i+2]== '-'))) {
            FlagError = 1;
        }
        if (str[i] == ')') {
            if ((str[i+1]== 'c') ||(str[i+1]== 's') ||(str[i+1]== 't')
                ||(str[i+1]== 'a') ||(str[i+1]== 'l') ||(str[i+1]== '(')
                ||(str[i+1]== 'x') ||(('0' <= str[i+1])&&(str[i+1] <= '9'))) {
                FlagError = 1;
            }
        }
    }
    return FlagError;
}
int calc(char *str, double str_x, double *result1) {
    initialization(input);
    initialization(stack);
    initialization(output);
    initialization(result);
    initialization(x);
    *result1 = 0.0;

    int num_input = 0;
    int FlagError = 0;
    int bracket_open = 0;
    int bracket_close = 0;

    // Обработка значения Икс
    x[0].elemnts = 1;
    x[0].number = str_x;
    x[0].operation = 0;
    x[0].priority = 0;

    // Проверка на корректность ввода
    FlagError = check_string(str);
    // Перевод элементов строки в элементы структуры input
    for (int i = 0; i < (int)strlen(str)+1; i++) {
        if (bracket_close > bracket_open) FlagError = 1;
        if ((('0' <= str[i])&&(str[i] <= '9')) || (str[i] == '.')) {
            int k = 0;
            char temp_num[MAX];
            memset(temp_num, '\0', MAX);
            int point = 0;
            while ((('0' <= str[i+k])&&(str[i+k] <= '9')) || (str[i+k] == '.')) {
                if (str[i+k] == '.') point++;
                if (point > 1) FlagError = 1;
                temp_num[k] = str[i+k];
                k++;
            }
            input[num_input].elemnts = 1;
            input[num_input].number = atof(temp_num);
            input[num_input].operation = 0;
            input[num_input].priority = 0;
            i = i+k;
            num_input++;
        }
        if (str[i] == 'x') {
            input[num_input] = x[0];
            num_input++;
        }
        if (str[i] == '(') {
            input[num_input] = element[21];
            bracket_open++;
            num_input++;
        }
        if (str[i] == ')') {
            input[num_input] = element[22];
            bracket_close++;
            num_input++;
        }
        // плюс
        if (str[i] == '+') {
            if ((i == 0) || (str[i-1] == '(' || str[i-1] == '+' || str[i-1] == '-'
                || str[i-1] == '*' || str[i-1] == '/' || str[i-1] == 'd')) {
                num_input = input1elem(7, num_input);
            } else {
                if (str[i-1] == '^') {
                    num_input = input1elem(18, num_input);
                } else {
                    num_input = input1elem(1, num_input);
                }
            }
        }
        if (str[i] == '-') {
            // унарный минус
            if ((i == 0) || (str[i-1] == '(' || str[i-1] == '+' || str[i-1] == '-'
                || str[i-1] == '*' || str[i-1] == '/' || str[i-1] == 'd')) {
                input[num_input] = element[8];
                num_input++;
            } else {
                // унарный минус степень
                if (str[i-1] == '^') {
                    input[num_input] = element[19];
                    num_input++;
                } else {
                // бинарный минус (вычитание)
                input[num_input] = element[2];
                num_input++;
                }
            }
        }
        if (str[i] == '*') num_input = input1elem(3, num_input);
        if (str[i] == '/') num_input = input1elem(4, num_input);
        if (str[i] == '^') num_input = input1elem(5, num_input);
        if ((str[i] == 'm') && (str[i+1] == 'o') && (str[i+2] == 'd')) {
            num_input = input1elem(6, num_input);
            i = i + 2;
        }
        if ((str[i] == 'c') && (str[i+1] == 'o') && (str[i+2] == 's') && (str[i+3] == '(')) {
            num_input = input2elem(9, num_input);
            bracket_open++;
            i = i + 3;
        }
        if ((str[i] == 's') && (str[i+1] == 'i') && (str[i+2] == 'n') && (str[i+3] == '(')) {
            num_input = input2elem(10, num_input);
            bracket_open++;
            i = i + 3;
        }
        if ((str[i] == 't') && (str[i+1] == 'a') && (str[i+2] == 'n') && (str[i+3] == '(')) {
            num_input = input2elem(11, num_input);
            bracket_open++;
            i = i + 3;
        }
        if (((str[i] == 'a') && str[i+1] == 'c') && (str[i+2] == 'o') && (str[i+3] == 's')
            && (str[i+4] == '(')) {
            num_input = input2elem(12, num_input);
            bracket_open++;
            i = i + 4;
        }
        if (((str[i] == 'a') && str[i+1] == 's') && (str[i+2] == 'i') && (str[i+3] == 'n')
            && (str[i+4] == '(')) {
            num_input = input2elem(13, num_input);
            bracket_open++;
            i = i + 4;
        }
        if ((str[i] == 'a') && (str[i+1] == 't') && (str[i+2] == 'a') && (str[i+3] == 'n')
            && (str[i+4] == '(')) {
            num_input = input2elem(14, num_input);
            bracket_open++;
            i = i + 4;
        }
        if ((str[i] == 's') && (str[i+1] == 'q') && (str[i+2] == 'r') && (str[i+3] == 't')
            && (str[i+4] == '(')) {
            num_input = input2elem(15, num_input);
            bracket_open++;
            i = i + 4;
        }
        if ((str[i] == 'l') && (str[i+1] == 'n') && (str[i+2] == '(')) {
            num_input = input2elem(16, num_input);
            bracket_open++;
            i = i + 2;
        }
        if ((str[i] == 'l') && (str[i+1] == 'o') && (str[i+2] == 'g') && (str[i+3] == '(')) {
            num_input = input2elem(17, num_input);
            bracket_open++;
            i = i + 3;
        }
    }
    if (bracket_close != bracket_open) FlagError = 1;
    if (FlagError == 0) {
        // Алгоритм преобразования из инфиксного в постфиксное выражение (обратная польская нотация)
        int num_stack = 0;
        int num_output = 0;
        for (int i = 0; i < num_input+1; i++) {
            if (input[i].elemnts == 1) {
                copy(&input[i], &output[num_output]);
                num_output++;
            }
            if (input[i].elemnts == 2) {
                if (stack[0].elemnts == 0) {
                    copy(&input[i], &stack[0]);
                } else {
                    while (stack[num_stack].priority >= input[i].priority) {
                        copy(&stack[num_stack], &output[num_output]);
                        delet(&stack[num_stack]);

                        num_output++;
                        if (num_stack > 0) num_stack--;
                    }
                    // if (stack[num_stack].priority < input[i].priority) {
                        if (stack[0].elemnts == 0) {
                            copy(&input[i], &stack[0]);
                        } else {
                            copy(&input[i], &stack[num_stack+1]);
                            num_stack++;
                        }
                    // }
                }
            }
            if (input[i].elemnts == 4) {
                // скобка открывания тригонометрической функции
                if (input[i].operation == 20) {
                        copy(&input[i], &stack[num_stack+1]);
                        num_stack++;
                    // }
                }
                // скобка открывания
                if (input[i].operation == 21) {
                    if (stack[0].elemnts == 0) {
                        copy(&input[i], &stack[0]);
                    } else {
                        copy(&input[i], &stack[num_stack+1]);
                        num_stack++;
                    }
                }
                // скобка закрытия
                if (input[i].operation == 22) {
                    while ((stack[num_stack].operation != 21) && (stack[num_stack].operation != 20)) {
                        copy(&stack[num_stack], &output[num_output]);
                        delet(&stack[num_stack]);
                        num_output++;
                        if (num_stack > 0) num_stack--;
                    }
                    switch (stack[num_stack].operation) {
                        case 20:
                            delet(&stack[num_stack]);
                            if (num_stack > 0) num_stack--;
                            copy(&stack[num_stack], &output[num_output]);
                            delet(&stack[num_stack]);
                            if (num_stack > 0) num_stack--;
                            num_output++;
                            break;
                        case 21:
                            delet(&stack[num_stack]);
                            if (num_stack > 0) num_stack--;
                            break;
                    }
                }
            }
            if (input[i].elemnts == 0) {
                while (stack[num_stack].operation) {
                    copy(&stack[num_stack], &output[num_output]);
                    delet(&stack[num_stack]);
                    num_output++;
                    if (num_stack > 0) num_stack--;
                }
            }
        }
        // Алгоритм получение результата из постфиксного выражения
        int num_result = 0;
        for (int i = 0; i < num_output+1; i++) {
            if (output[i].elemnts == 1) {
                copy(&output[i], &result[num_result]);
                num_result++;
            }
            if (output[i].elemnts == 2) {
                if (output[i].operation == 1) num_result = func2arg(result[num_result - 2].number
                + result[num_result - 1].number, num_result);
                if (output[i].operation == 2) num_result = func2arg(result[num_result - 2].number
                - result[num_result - 1].number, num_result);
                if (output[i].operation == 3) num_result = func2arg(result[num_result - 2].number
                * result[num_result - 1].number, num_result);
                if (output[i].operation == 4) num_result = func2arg(result[num_result - 2].number
                    / result[num_result - 1].number, num_result);
                if (output[i].operation == 5) num_result = func2arg(pow(result[num_result - 2].number,
                result[num_result - 1].number), num_result);
                if (output[i].operation == 6) num_result = func2arg(fmod(result[num_result - 2].number,
                result[num_result - 1].number), num_result);
                if (output[i].operation == 7)
                    num_result = func1arg(result[num_result - 1].number, num_result);
                if (output[i].operation == 8)
                    num_result = func1arg(-1*(result[num_result - 1].number), num_result);
                if (output[i].operation == 9)
                    num_result = func1arg(cos(result[num_result - 1].number), num_result);
                if (output[i].operation == 10)
                    num_result = func1arg(sin(result[num_result - 1].number), num_result);
                if (output[i].operation == 11)
                    num_result = func1arg(tan(result[num_result - 1].number), num_result);
                if (output[i].operation == 12)
                    num_result = func1arg(acos(result[num_result - 1].number), num_result);
                if (output[i].operation == 13)
                    num_result = func1arg(asin(result[num_result - 1].number), num_result);
                if (output[i].operation == 14)
                    num_result = func1arg(atan(result[num_result - 1].number), num_result);
                if (output[i].operation == 15)
                    num_result = func1arg(sqrt(result[num_result - 1].number), num_result);
                if (output[i].operation == 16)
                    num_result = func1arg(log(result[num_result - 1].number), num_result);
                if (output[i].operation == 17)
                    num_result = func1arg(log10(result[num_result - 1].number), num_result);
                if (output[i].operation == 18)
                    num_result = func1arg(result[num_result - 1].number, num_result);
                if (output[i].operation == 19)
                    num_result = func1arg(-1*(result[num_result - 1].number), num_result);
            }
        }
    }
    *result1 = result[0].number;
    return FlagError;
}
void calc_cred_annu(double ost_kr, int srok, double pr_stav, int x,
double *plat_mes, double *plat_dolg, double *plat_proc, double *vse_dolg, double *vse_proc) {
    *vse_proc = 0;
    *vse_dolg = ost_kr;
    double dol_proc = pr_stav/1200.0;

    *plat_mes = ost_kr*(dol_proc+(dol_proc/(pow((1.0+dol_proc), srok)-1.0)));
    *plat_mes = round(*plat_mes*100)/100;

    for (int i = 0; i < x; i++) {
        *plat_proc = ost_kr*dol_proc;
        *plat_proc = round(*plat_proc*100)/100;
        *plat_dolg = *plat_mes - *plat_proc;
        ost_kr = ost_kr - *plat_dolg;
        *vse_proc += *plat_proc;
    }
    *vse_dolg += *vse_proc;
}
void calc_cred_diff(double ost_kr, int srok, double pr_stav, int x,
double *plat_mes, double *plat_dolg, double *plat_proc, double *vse_dolg, double *vse_proc) {
    *vse_proc = 0;
    *vse_dolg = ost_kr;
    double dol_proc = pr_stav/1200.0;

    *plat_dolg = ost_kr/srok;
    *plat_dolg = round(*plat_dolg*100)/100;

    for (int i = 0; i < x; i++) {
        *plat_proc = ost_kr*dol_proc;
        *plat_proc = round(*plat_proc*100)/100;
        *plat_mes = *plat_dolg + *plat_proc;
        ost_kr = ost_kr - *plat_dolg;
        *vse_proc += *plat_proc;
    }
    *vse_dolg += *vse_proc;
}
