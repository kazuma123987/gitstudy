#include <stdint.h> 
#include <stdlib.h>
#ifndef _STUDENT_h_
#define _STUDENT_h_
#define NAME_SIZE 20
typedef struct{
    char name[NAME_SIZE];
    int8_t gendar;
    int8_t age;
}student; 
#endif