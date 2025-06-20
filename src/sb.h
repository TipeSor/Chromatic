#ifndef STRINGBUILDER_H
#define STRINGBUILDER_H

#include <stddef.h>

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} StringBuilder;

StringBuilder *sb_create(void);
void sb_append(StringBuilder *sb, const char *str);
void sb_appendf(StringBuilder *sb, const char *fmt, ...);
void sb_free(StringBuilder *sb);
void sb_clear(StringBuilder *sb);

#endif
