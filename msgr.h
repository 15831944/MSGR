#ifndef MSGR_H
#define MSGR_H

#include <stdio.h>
#include <stdlib.h>

#define SECONDS_IN_MINUTE 60
#define LENGTH_OF_CURRENT_LINE 8192

typedef struct Entry
{
    char *str;
    double dVal;
} Entry;


#endif
