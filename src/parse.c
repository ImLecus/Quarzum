#include "quarzum.h"

node* init_node(unsigned int children, int type){
    node* n = (node*)malloc(sizeof(node));
    n->children = init_vector(children);
    n->type = type;
    return n;
}

static void expect(token* t, int type, char* what){
    if(t->type != type){
        printf(RED "[ERROR]" RESET " Expected %s at line %d.\n", what, t->line);
    }
}

static void parse_import(lexer* lexer){
    read_next(lexer);
    if(lexer->tok->type == T_STRING_LITERAL){
        // path
    }
}

static node* parse_statement(lexer* lexer){
    return NULL;
}

static node* parse_module(lexer* lexer){
    node* module_node = init_node(3, N_MODULE);
    token* next;

    next = next_token(lexer);
    expect(next, T_IDENTIFIER, "identifier");
    vector_push(module_node->children, next->value);
    // symbol table check
    expect(next_token(lexer), T_LEFT_CURLY, "'{'");

    while(next->type != T_RIGHT_CURLY){
        next = next_token(lexer);
        vector_push(module_node->children, parse_statement(lexer) );
    }
    expect(next, T_RIGHT_CURLY, "'}'");

    return module_node;
}

static type* parse_type(lexer* lexer){
    type* t = (type*)malloc(sizeof(type));
    if(lexer->tok->type != T_TYPE){
        // custom type
    }
    else{
        // int8 as placeholder
        t = &(type){TY_INT, 1, 1};;
    }

    read_next(lexer);
    if(strcmp(lexer->tok->value, "*") == 0){
        t->flags |= POINTER_FLAG;
    }

    return t;
}

static node* parse_function_decl(lexer* lexer, type* t){
    return NULL;
}

static node* parse_class(lexer* lexer){
    node* class_node = init_node(3, N_CLASS);
    token* next;
    next = next_token(lexer);
    expect(next, T_IDENTIFIER, "identifier");
    vector_push(class_node->children, next->value);
    // parse optional inheritance
    next = next_token(lexer);
    if(next->type == T_ARROW){
        // parse type
    }

    expect(next, T_LEFT_CURLY, "'{'");
    while(next->type != T_RIGHT_CURLY){
        next = next_token(lexer);
        vector_push(class_node->children, parse_statement(lexer) );
    }
    expect(next, T_RIGHT_CURLY, "'}'");

    return class_node;
}

static symbol* parse_symbol(lexer* lexer){
    // TO-DO: warn or error when a specifier is duplicated
    symbol* s = (symbol*)malloc(sizeof(symbol));
    int flags = 0;
    while(lexer->tok->type == T_SPECIFIER){
        // specifiers can be differentiated by the first char
        switch (lexer->tok->value[0])
        {
        case 'c':
            flags |= CONST_FLAG;
            break;
        case 'f':
            flags |= FOREIGN_FLAG;
        default:
            // err
            break;
        }
        read_next(lexer);
    }
    if(lexer->tok->type == T_KEYWORD_STRUCT){
        // parse_struct_decl
        return NULL;
    }
    s->type = parse_type(lexer);
    s->type->flags |= flags;
    expect(lexer->tok, T_IDENTIFIER, "identifier");
    // TO-DO: mangle name
    s->name = "";//string_copy(lexer->tok->value);
    return s;
}

node* parse(){
    lexer* lexer = init_lexer(read_file("code.qz")->value);
    read_next(lexer);
    node* ast = init_node(10, N_ROOT);
    while (lexer->tok->type != T_EOF)
    {
        switch(lexer->tok->type){
            case T_KEYWORD_IMPORT:
                parse_import(lexer);
                printf(LOG_MSG("IMPORT "));
                break;
            case T_KEYWORD_MODULE:
                vector_push(ast->children, parse_module(lexer));  
                printf(LOG_MSG("MODULE "));
                break;
            case T_KEYWORD_CLASS:
                vector_push(ast->children, parse_class(lexer));  
                printf(LOG_MSG("CLASS "));
                break;

            case T_SPECIFIER:
            case T_TYPE:
                symbol* s = parse_symbol(lexer);
                printf(LOG_MSG("SYMBOL"));
                break;

            default:
                break;
        } 
        read_next(lexer);
    }
    
    free(lexer);
    return NULL;
}