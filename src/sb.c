#include "sb.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

StringBuilder *sb_create(void) {
    StringBuilder *sb = malloc(sizeof(StringBuilder));
    if (!sb)
        return NULL;

    sb->capacity = 64;
    sb->length = 0;
    sb->data = malloc(sb->capacity);
    if (!sb->data) {
        free(sb);
        return NULL;
    }

    sb->data[0] = '\0';
    return sb;
}

void sb_append(StringBuilder *sb, const char *str) {
    size_t str_len = strlen(str);
    if (sb->length + str_len + 1 > sb->capacity) {
        sb->capacity = (sb->length + str_len + 1) * 2;
        sb->data = realloc(sb->data, sb->capacity);
    }
    memcpy(sb->data + sb->length, str, str_len);
    sb->length += str_len;
    sb->data[sb->length] = '\0';
}

void sb_appendf(StringBuilder *sb, const char *fmt, ...) {
    if (!sb || !fmt) return;

    va_list args;
    
    va_start(args, fmt);
    int required = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    if (required <= 0) return;

    if (sb->length + required + 1 > sb->capacity) {
        size_t new_capacity = (sb->length + required + 1) * 2;
        char *new_data = realloc(sb->data, new_capacity);
        if (!new_data) return;
        sb->data = new_data;
        sb->capacity = new_capacity;
    }

    va_start(args, fmt);
    int written = vsnprintf(sb->data + sb->length, sb->capacity - sb->length, fmt, args);
    va_end(args);

    if (written > 0) {
        sb->length += written;
    }
}

void sb_free(StringBuilder *sb) {
    free(sb->data);
    free(sb);
}

void sb_clear(StringBuilder *sb) {
    sb->length = 0;
    sb->data[0] = '\0';
}
