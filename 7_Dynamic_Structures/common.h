#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 5

typedef struct element
{
    int info;
    struct element *left;
    struct element *right;
} node;
typedef node* ptree;

int my_Array[SIZE];
void array_init_or_print(int*, int);
ptree insorder(ptree, int);
ptree vec2tree(ptree, int*, int);
void tree2vect(ptree, int*, int*);
void destroy(ptree);
void sort(int*, int n);