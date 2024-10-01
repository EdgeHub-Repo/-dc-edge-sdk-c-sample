#ifndef __STRING_H__
#define __STRING_H__

#include <unistd.h>

struct string {
    char *ptr;
    size_t len;
};

#endif
