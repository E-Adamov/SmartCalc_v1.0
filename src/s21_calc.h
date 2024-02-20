#ifndef SRC_S21_CALC_H_
#define SRC_S21_CALC_H_

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256

typedef struct elem {
    int elemnts;
    double number;
    int operation;
    int priority;
} elem_t;

void initialization(elem_t *A);
void delet(elem_t *A);
void copy(elem_t *A, elem_t *B);
int check_string(char *str);
int calc(char *str, double str_x, double *result1);
void calc_cred_annu(double ost_kr, int srok, double pr_stav, int x,
double *plat_mes, double *plat_dolg, double *plat_proc, double *vse_dolg, double *vse_proc);
void calc_cred_diff(double ost_kr, int srok, double pr_stav, int x,
double *plat_mes, double *plat_dolg, double *plat_proc, double *vse_dolg, double *vse_proc);
int func1arg(double res_func, int num_arg);
int func2arg(double res_func, int num_arg);
int input1elem(int num_elem, int num_arg);
int input2elem(int num_elem, int num_arg);

#endif  // SRC_S21_CALC_H_
