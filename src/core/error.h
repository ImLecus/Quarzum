/**
 * \file            error.h
 * \brief           Quarzum compiler definitions for errors, warnings
 *                  logs and debug messages.
 * \copyright       2024 Marcos González GPL3
 */
#ifndef ERROR_H
#define ERROR_H
#include "core.h"
#include "file.h"

#define MAX_ERRORS 100

/**
 * \brief           Struct to store an element position
 *                  inside a file during the compilation
 */
typedef struct {
    int line, column;
    const char* file;
} pos_t;

typedef struct {
    uint32_t line;
    char message[256];
} error_t;

extern error_t ERROR_LIST[MAX_ERRORS];
extern int error_count;

extern error_t WARNING_LIST[MAX_ERRORS];
extern int warning_count;

// Throws a compilation error into ERROR_LIST. Only stores one
// error per line.
void throw_error(pos_t pos,const char* const message);
// Throws a warning into WARNING_LIST. Only stores one warning per line.
void throw_warning(pos_t pos,const char* const message);
// Prints all errors inside ERROR_LIST without modifying the list.
// Prints all the warnings inside WARNING_LIST too, eliminating them
// once they appear in console.
void print_errors();

// Prints all the errors and exits the program if error_count > 0
void check_errors();

// Throws a lexical error with the form "Unexpected token '[buffer]'"
void unexpected_token_err(pos_t pos,const char* const buffer);
// Throws a lexical error with the form "Too many decimal points on numeric literal"
void invalid_decimal_err(pos_t pos);

void unclosed_quotes_err(pos_t pos);

void expected_token_err(pos_t pos,const char* const expected);

void duplicated_type_err(pos_t pos,const char* const typename);

void undefined_type_err(pos_t pos,const char* const typename);

void duplicated_flag_warning(pos_t pos,const char* const flag);

void duplicated_symbol_err(pos_t pos,const char* const symbol);

void file_not_found_err(const char* const filename);

void invalid_expr_err(pos_t pos);

#endif
