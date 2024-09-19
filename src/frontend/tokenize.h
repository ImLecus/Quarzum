/**
 * \file            lexer.h
 * \brief           Quarzum lexer include file
 * \copyright       2024 Marcos González, GPL3
 */
#ifndef LEXER_H
#define LEXER_H
#include "../core/string.h"
#include "../core/error.h"
#include "../core/file.h"
#include "../core/vector.h"

/**
 * \brief           Token type enum
 */
typedef enum {
    T_TOKEN_ERROR,
    T_LOGICAL_OP,
    T_SPECIFIER,
    T_UNARY,
    T_ACCESS,
    T_TYPE,
    T_BITWISE_OP,
    T_ARITHMETIC_OP,
    T_ASSIGN_OP,
    T_IDENTIFIER,
    T_EOF,
    T_SYMBOL,
    T_NUMERIC_LITERAL,
    T_STRING_LITERAL,
    T_CHAR_LITERAL,
    T_INT_LITERAL,
    T_NULL_LITERAL,
    T_KEYWORD_ALLOC,
    T_KEYWORD_BREAK,
    T_KEYWORD_CASE,
    T_KEYWORD_CLASS,
    T_KEYWORD_CONTINUE,
    T_KEYWORD_DEFAULT,
    T_KEYWORD_DELETE,
    T_KEYWORD_DO,
    T_KEYWORD_ELSE,
    T_KEYWORD_ENUM,
    T_KEYWORD_FALSE,
    T_KEYWORD_FOR,
    T_KEYWORD_FOREACH,
    T_KEYWORD_IF,
    T_KEYWORD_IMPORT,
    T_KEYWORD_IN,
    T_KEYWORD_MODULE,
    T_KEYWORD_NEW,
    T_KEYWORD_RETURN,
    T_KEYWORD_SIZEOF,
    T_KEYWORD_STRUCT,
    T_KEYWORD_SWITCH,
    T_KEYWORD_TRUE,
    T_KEYWORD_TYPEDEF,
    T_KEYWORD_WHILE,
    T_KEYWORD_CONSTRUCTOR,
    T_KEYWORD_DESTRUCTOR,
    T_LEFT_PAR,
    T_RIGHT_PAR,
    T_COMMA,
    T_DOT,
    T_COLON,
    T_SEMICOLON,
    T_COMPARATION_OP,
    T_TERNARY_OP,
    T_LEFT_SQUARE,
    T_RIGHT_SQUARE,
    T_LEFT_CURLY,
    T_RIGHT_CURLY,
    T_ARROW,
    T_EQUAL,
    T_KEYWORD_OPERATOR,
    T_TYPE_EXTENSION_OP
} token_type_t;

/**
 * Keywords and symbols
 * --------------------
 * 
 * Primitive types are not keywords. 
 * Both string arrays are sorted.
 */

#define KEYWORDS_SIZE 39
#define SYMBOLS_SIZE 41

static const char* keywords[KEYWORDS_SIZE] = {
    "alloc","and","break","case","class","const","constructor","continue","default",
    "delete","destructor","do","else","enum",
    "false","for","foreach","foreign",
    "if","import","in",
    "module","new","not","null",
    "operator", "or","private","protected","public",
    "return","sizeof","struct","switch",
    "true","typedef","while","xor"
};

static const int keyword_types[KEYWORDS_SIZE] = {
    T_KEYWORD_ALLOC ,T_LOGICAL_OP, T_KEYWORD_BREAK, T_KEYWORD_CASE, T_KEYWORD_CLASS, T_SPECIFIER, T_KEYWORD_CONSTRUCTOR, 
    T_KEYWORD_CONTINUE, T_KEYWORD_DEFAULT, T_KEYWORD_DELETE, T_KEYWORD_DESTRUCTOR, T_KEYWORD_DO, T_KEYWORD_ELSE,
    T_KEYWORD_ENUM, T_KEYWORD_FALSE, T_KEYWORD_FOR, T_KEYWORD_FOREACH, 
    T_SPECIFIER, T_KEYWORD_IF, T_KEYWORD_IMPORT, T_KEYWORD_IN, T_KEYWORD_MODULE, T_KEYWORD_NEW,
    T_UNARY, T_NULL_LITERAL, T_KEYWORD_OPERATOR, T_LOGICAL_OP, T_ACCESS, T_ACCESS, T_ACCESS, T_KEYWORD_RETURN,
    T_KEYWORD_SIZEOF, T_KEYWORD_STRUCT, T_KEYWORD_SWITCH, T_KEYWORD_TRUE,
    T_KEYWORD_TYPEDEF, T_KEYWORD_WHILE, T_LOGICAL_OP

};

static const char* symbols[SYMBOLS_SIZE] = {
    "!","!=","#","#=","%","%=","&","&=","(",")","*","*=","+","++","+=",",","-","--","-=",
    ".","/","/=",":","::",";","<","<=","=","==","=>",">",">=","?","[","]","^","^=","{","|","|=","}"
};

static const int symbol_types[SYMBOLS_SIZE] = {
    T_BITWISE_OP, T_ASSIGN_OP, T_BITWISE_OP, T_ASSIGN_OP, T_ARITHMETIC_OP,
    T_ASSIGN_OP, T_BITWISE_OP, T_ASSIGN_OP, T_LEFT_PAR, T_RIGHT_PAR, T_ARITHMETIC_OP,
    T_ASSIGN_OP, T_ARITHMETIC_OP, T_UNARY, T_ASSIGN_OP, T_COMMA, T_ARITHMETIC_OP,
    T_UNARY, T_ASSIGN_OP, T_DOT, T_ARITHMETIC_OP, T_ASSIGN_OP, T_COLON,T_TYPE_EXTENSION_OP, T_SEMICOLON,
    T_COMPARATION_OP, T_COMPARATION_OP, T_EQUAL, T_COMPARATION_OP,T_ARROW ,T_COMPARATION_OP,
    T_COMPARATION_OP, T_TERNARY_OP, T_LEFT_SQUARE, T_RIGHT_SQUARE, T_ARITHMETIC_OP,
    T_ASSIGN_OP, T_LEFT_CURLY, T_BITWISE_OP, T_ASSIGN_OP, T_RIGHT_CURLY

};

/**
 * \brief           Basic lexer result unit
 */
typedef struct {
    pos_t position;
    token_type_t type;
    char* value;
} token_t;

/**
 * \brief           Lexer struct. Contains the result of the
 *                  last iteration and its position
 */
typedef struct {
    pos_t position;
    token_t* tok;
    char* input;
    string_t* buffer;
    unsigned int pos;
} lexer_t;

/**
 * \brief           Returns 1 if the token type is an operator,
 *                  0 otherwise.
 */
int is_operator(token_type_t t);

/**
 * \brief           Allocates a `lexer_t` on the heap.
 * \returns         A pointer to the allocated `lexer_t`
 * \warning         The function will return `NULL` if the
 *                  input does not exist or if there is not
 *                  enough memory to allocate the lexer.
 */
lexer_t* init_lexer(char* filename, char* input);

/**
 * \brief           Analyzes the text to find the next token.
 * \returns         A pointer to `token_t`, the next found token.
 * \note            The function will ever return an EOF token once
 *                  the text has been arrived to the end.
 */
token_t* next_token(lexer_t* lexer);

/**
 * \brief           Tells the lexer to read the next token
 *                  and stores it in `lexer->tok`
 */
void read_next(lexer_t* lexer);


#define DEFAULT_TOKENIZER_BUFFER_SIZE 10

#endif /* LEXER_H */