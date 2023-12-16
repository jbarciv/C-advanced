/*************************************************************
                     MASTER IN ROBOTICS
                         ETSII - UPM
                     Advanced Programming
                 --> Practice 7: Trees <--

    - Professor: Claudio Rossi - DISAM (ETSII - UPM)
    - Student: Josep Maria Barbera Civera
    - NMat: 17048
    - Description: function that sorts a given vector by 
    recursively constructing a dynamic sorted tree and then 
    vectorizing it again.
**************************************************************/

#include "common.h"

int main(void)
{
    int my_Array[SIZE];
    array_init_or_print(my_Array, 1);
    sort(my_Array, SIZE);
    array_init_or_print(my_Array, 0);
    return 0;
}