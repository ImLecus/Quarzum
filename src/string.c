#include "quarzum.h"
inline string* init_string(const unsigned int size){
    string* s = (string*) malloc(sizeof(string));
    if(s == NULL){
        return NULL;
    }
    s->size = size;
    s->len = 0;
    s->value = (char*) malloc(size + 1);
    if(s->value == NULL){
        free(s);
        return NULL;
    }
    s->value[0] = '\0';
    return s;
}

inline void free_string(string* s){
    free(s->value);
    free(s);
}

inline void string_push(string* s, const char c){
    if(s->len >= s->size){
        char* newBuffer = (char*) realloc(s->value,s->size * 2);
        if(newBuffer == NULL){
            return;
        }
        s->size *= 2;
        s->value = newBuffer;
    }
    s->value[s->len++] = c;
    s->value[s->len] = '\0';
}

inline void string_pop(string* s){
    s->value[--s->len] = '\0';
}

inline void string_clear(string* s){
    for(unsigned int i = 0; s->value[i]; ++i){
        s->value[i] = '\0';
    }
    s->len = 0;
}

inline char* string_copy(string* s){
    char* result = (char *) malloc(s->len + 1);
    if(result == NULL){
        return NULL;
    }
    strcpy(result, s->value);
    return result;
}

void string_append(string* s, char* c){
    int len = strlen(c);
    for(unsigned int i = 0; i < len; ++i){
        string_push(s,c[i]);
    }
}

char* delete_quotes(char* c){
    int len = strlen(c);
    char* new_str = (char*)malloc(sizeof(char) * (len - 2));
    for(int i = 1; i < len - 1; ++i){
        new_str[i - 1] = c[i];
    }
    return new_str;
}