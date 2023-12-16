//////////////////////////////////////////////////////////////////////////////////////
// MASTER IN ROBOTICS
//   ETSII - UPM
//
// Dynamic Structures (Practice 7)
// Advanced Programming
// First version: Professor Claudio Rossi - 2022
//
// Student: Josep Maria Barbera Civera (December 2023)
// ID: 17048
//////////////////////////////////////////////////////////////////////////////////////

#include "common.h"

void array_init_or_print(int *v, int flag)
{
    int i = 0;

    if(flag)
    {
        srand(time(NULL));
        printf("New random vector:\n");
    }
    else printf("\nSorted vector:\n");

    printf("[");

    for(i=0; i < SIZE; i++)
    {   
        if (flag)
            v[i] =  1 + (int)(100*(random()/(float)RAND_MAX));
        if (i == SIZE-1) 
            printf("%d]\n",v[i]);
        else 
            printf("%d,",v[i]);
    }
    return;
}

ptree insorder(ptree t, int x)
{
    ptree tmp;
    
    if(!t)
    {
        tmp = (node*)malloc(sizeof(node));
        if (tmp != NULL)
        {
            tmp->info = x;
            tmp->left = NULL;
            tmp->right = NULL;
        }
        return tmp;
    }

    if (x > (t->info))
    {
        t->right = insorder(t->right, x);
        return t;
    }
    else
    {
        t->left = insorder(t->left, x);
        return t;
    }
}

ptree vec2tree(ptree t, int *v, int n)
{
    int i;
    for(i=0; i<n; i++)
        t = insorder(t, v[i]);

    return t;
}

void tree2vect(ptree t, int *v, int *pos)
{
    if(!t) return;

    if(t->left) 
        tree2vect(t->left, v, pos);

    v[*pos] = t->info;
    (*pos)++;

    if(t->right)
        tree2vect(t->right, v, pos);
    return;
}

void destroy(ptree t)
{
    if (!t) return;
    if (t->left != NULL)
    {
        destroy(t->left);
    }
    if (t->right != NULL)
    {
        destroy(t->right);
    }
    printf("destroying: %d ", t->info);
    free(t);
    return;

}

void sort(int *v, int n)
{
    ptree t = NULL;
    int pos = 0;

    t = vec2tree(t, v, n);
    tree2vect(t, v, &pos);

    destroy(t);
    return;
}