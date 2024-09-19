// File: error.c
// Description: Quarzum error handling implementation
#include "error.h"

error_t ERROR_LIST[MAX_ERRORS];
int error_count;
error_t WARNING_LIST[MAX_ERRORS];
int warning_count;



void throw_error(pos_t pos, char* message){
    if(error_count >= MAX_ERRORS){
        return;
    }
    if(ERROR_LIST[error_count - 1].line == pos.line){
        return;
    }
    ERROR_LIST[error_count].line = pos.line;
    if(pos.line >= 0){
        sprintf(ERROR_LIST[error_count++].message, "\e[1;31m[ERROR] \e[0m(%s) %s at line %d\n",pos.file, message, pos.line);
        return;
    }
    sprintf(ERROR_LIST[error_count++].message, "\e[1;31m[ERROR] \e[0m(%s) %s\n",pos.file, message);

}

void throw_warning(pos_t pos, char* message){
    if(warning_count >= MAX_ERRORS){
        return;
    }
    if(WARNING_LIST[warning_count - 1].line == pos.line){
        return;
    }
    WARNING_LIST[warning_count].line = pos.line;
    sprintf(WARNING_LIST[warning_count++].message, "\e[1;38;5;214m[WARNING] \e[0m(%s) %s at line %d\n",pos.file, message, pos.line);
}

void print_errors(){
    for(unsigned int i = 0; i < error_count; ++i){
        if(i < warning_count){
            printf(WARNING_LIST[i].message);
        }
        printf(ERROR_LIST[i].message);
    }
    warning_count = 0;
}

inline void check_errors(){
    print_errors();
    if(error_count > 0){
        printf("Process failed with %d errors\n", error_count);
        exit(-1);
    }
}

inline void unexpected_token_err(pos_t pos, char* buffer){
    char* message;
    sprintf(message, "Unexpected token '%s'", buffer);
    throw_error(pos, message);   
}

inline void invalid_decimal_err(pos_t pos){
    throw_error(pos, "Too many decimal points on numeric literal");
}

inline void expected_token_err(pos_t pos, char* expected){
    char* message;
    sprintf(message, "Expected %s", expected);
    throw_error(pos, message);   
}

inline void duplicated_type_err(pos_t pos, char* typename){
    char* message;
    sprintf(message, "Type '%s' has been already defined", typename);
    throw_error(pos, message);   
}

inline void undefined_type_err(pos_t pos, char* typename){
    char* message;
    sprintf(message, "Undefined type '%s'", typename);
    throw_error(pos, message);  
}

void duplicated_flag_warning(pos_t pos, char* flag){
    char* message;
    sprintf(message, "Duplicated flag '%s'", flag);
    throw_error(pos, message); 
}

void duplicated_symbol_err(pos_t pos, char* symbol){
    char* message;
    sprintf(message, "Symbol '%s' already exists", symbol);
    throw_error(pos, message); 
}

void file_not_found_err(char* filename){
    throw_error((pos_t){-1, 0, filename}, "File not found");
}