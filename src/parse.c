#include "quarzum.h"
static node* parse_statement(lexer* lexer);


node* init_node(unsigned int children, int type){
    node* n = (node*)malloc(sizeof(node));
    n->children = init_vector(children);
    n->type = type;
    return n;
}

void expect(token* t, int type, char* what){
    if(t->type != type){
        printf(RED "[ERROR]" RESET " Expected %s at line %d.\n", what, t->line);
    }
}

static void parse_import(lexer* lexer, node* ast){
    read_next(lexer);
    if(lexer->tok->type == T_STRING_LITERAL){
        char* path = resolve_path(delete_quotes(lexer->tok->value));
        char* as = NULL; 
        read_next(lexer);
        if(lexer->tok->type == T_KEYWORD_AS){
            read_next(lexer);
            expect(lexer->tok, T_IDENTIFIER, "identifier");
            as = lexer->tok->value;
        }
        struct process importing = start_process("File import");
        node* imported_file_ast = parse(path);
        if(!imported_file_ast){
            return;
        }

        if(as){
            // create a virtual module with name {as}
            // maybe transforming the root node?
        }
        for(unsigned int i = 0; i < imported_file_ast->children->len; ++i){
            vector_push(ast->children, imported_file_ast->children->value[i]);
        }
        end_process(&importing);

        return;
    }
}

static node* parse_return_statement(lexer* lexer){
    node* return_node = init_node(1,N_RETURN);
    read_next(lexer);
    if(lexer->tok->type == T_SEMICOLON){
        // add to return_node a null expr
        return return_node;
    }
    node* expr = parse_expr(lexer);
    expect(lexer->tok, T_SEMICOLON, "semicolon");
    vector_push(return_node->children, expr);
    return return_node;
}

static node* parse_function_call(lexer* lexer, char* id){
    node* call_node = init_node(1, N_CALL);
    vector_push(call_node->children, id);
    read_next(lexer);
    while(lexer->tok->type != T_RIGHT_PAR){
        node* argument = parse_expr(lexer);
        vector_push(call_node->children, argument);
        if(lexer->tok->type == T_COMMA){
            read_next(lexer);
        }
        else{
            expect(lexer->tok, T_RIGHT_PAR, "')'");
            break;
        }
    }
    read_next(lexer);
    expect(lexer->tok, T_SEMICOLON, "semicolon");
    return call_node;
}

static node* parse_if_statement(lexer* lexer){
    node* if_stmt = init_node(2,N_IF);
    read_next(lexer);
    expect(lexer->tok, T_LEFT_PAR, "'(");
    read_next(lexer);
    node* condition = parse_expr(lexer);
    if(condition){
        vector_push(if_stmt->children, condition);
    }
    expect(lexer->tok, T_RIGHT_PAR, "')");
    read_next(lexer);
    expect(lexer->tok, T_LEFT_CURLY, "'if' body");
    read_next(lexer);
    while(lexer->tok->type != T_RIGHT_CURLY){
        node* stmt = parse_statement(lexer);
        vector_push(if_stmt->children, stmt);
        read_next(lexer);
    }
    // skip '}' ?
    return if_stmt;
}

static node* parse_while_statement(lexer* lexer){
    node* while_stmt = init_node(2,N_WHILE);
    read_next(lexer);
    expect(lexer->tok, T_LEFT_PAR, "'(");
    read_next(lexer);
    node* condition = parse_expr(lexer);
    if(condition){
        vector_push(while_stmt->children, condition);
    }
    expect(lexer->tok, T_RIGHT_PAR, "')");
    read_next(lexer);
    expect(lexer->tok, T_LEFT_CURLY, "'while' body");
    read_next(lexer);
    while(lexer->tok->type != T_RIGHT_CURLY){
        node* stmt = parse_statement(lexer);
        vector_push(while_stmt->children, stmt);
        read_next(lexer);
    }
    // skip '}' ?
    return while_stmt;
}

static node* parse_statement(lexer* lexer){
    switch (lexer->tok->type)
    {
    case T_KEYWORD_RETURN:
        return parse_return_statement(lexer);

    case T_IDENTIFIER:
        char* id = lexer->tok->value;
        read_next(lexer);
        switch (lexer->tok->type)
        {
        case T_LEFT_PAR:
            return parse_function_call(lexer, id);
        
        default:
            break;
        }
    case T_KEYWORD_IF:
        return parse_if_statement(lexer);
    case T_KEYWORD_WHILE:
        return parse_while_statement(lexer);

    default:
        printf(ERROR_MSG("Invalid statement"));
        break;
    }
    return NULL;
}

static node* parse_module(lexer* lexer){
    node* module_node = init_node(3, N_MODULE);
    read_next(lexer);
    expect(lexer->tok, T_IDENTIFIER, "identifier");
    vector_push(module_node->children, lexer->tok->value);
    // symbol table check
    read_next(lexer);
    
    expect(lexer->tok, T_LEFT_CURLY, "'{'");

    while(lexer->tok->type != T_RIGHT_CURLY){
        read_next(lexer);
        vector_push(module_node->children, parse_statement(lexer) );
    }
    expect(lexer->tok, T_RIGHT_CURLY, "'}'");

    return module_node;
}

static type* parse_type(lexer* lexer){
    type* t = (type*)malloc(sizeof(type));
    if(lexer->tok->type != T_TYPE){
        // custom type
    }
    else{

        if(strcmp(lexer->tok->value, "string") == 0){
            t = ty_string;
        }
        if(strcmp(lexer->tok->value, "int") == 0){
            t = ty_int32;
        }
        else{
            // int8 as placeholder
            t = ty_int8;
        }
        
    }

    read_next(lexer);
    if(strcmp(lexer->tok->value, "*") == 0){
        t->flags |= POINTER_FLAG;
        read_next(lexer);
    }

    return t;
}


static node* parse_class(lexer* lexer){
    node* class_node = init_node(3, N_CLASS);
    read_next(lexer);
    expect(lexer->tok, T_IDENTIFIER, "identifier");
    // create a symbol
    vector_push(class_node->children, lexer->tok->value);
    // parse optional inheritance
    read_next(lexer);
    if(lexer->tok->type == T_ARROW){
        // parse type
    }

    expect(lexer->tok, T_LEFT_CURLY, "'{'");
    while(lexer->tok->type != T_RIGHT_CURLY){
        read_next(lexer);
        vector_push(class_node->children, parse_statement(lexer) );
    }
    expect(lexer->tok, T_RIGHT_CURLY, "'}'");

    return class_node;
}

static symbol* parse_symbol(lexer* lexer, bool global){
    // TO-DO: warn or error when a specifier is duplicated
    symbol* s = (symbol*)malloc(sizeof(symbol));
    int flags = 0;

    // placeholder
    if(global == true){
        s->scope = S_GLOBAL;
    }
    

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
    s->name = lexer->tok->value;
    return s;
}

static node* parse_global_decl(lexer* lexer){
    symbol* s = parse_symbol(lexer, true);
    // if s is a struct, return the struct
    read_next(lexer);
    switch (lexer->tok->value[0])
    {
    case '=':
        // if(s->type->flags &= FOREIGN_FLAG == FOREIGN_FLAG){
        //     printf(ERROR_MSG("'foreign' variables can't be initialized."));
        //     return NULL;
        // }
        read_next(lexer);
        node* expr = parse_expr(lexer);
        expect(lexer->tok, T_SEMICOLON, "semicolon");

        node* var_decl_node = init_node(2,N_VAR);
        vector_push(var_decl_node->children, s);
        vector_push(var_decl_node->children, expr);
        return var_decl_node;
    
    case ';':
        // var_decl (null value)
        break;

    case '(':
        read_next(lexer);
        while(lexer->tok->type != T_RIGHT_PAR){
            symbol* arg = parse_symbol(lexer, true);
            read_next(lexer);
            if(lexer->tok->type == T_COMMA){
                read_next(lexer);
            }
            else{
                expect(lexer->tok, T_RIGHT_PAR, "')'");
            }
        }
        read_next(lexer);
        node* func_decl_node = init_node(2,N_FUNCTION);
        vector_push(func_decl_node->children, s);
        if(lexer->tok->type == T_LEFT_CURLY){
            read_next(lexer);
            while(lexer->tok->type != T_RIGHT_CURLY){
                node* stmt = parse_statement(lexer);
                if(stmt){
                    vector_push(func_decl_node->children, stmt);
                }
                read_next(lexer);
            }
        }
        else{
            // only for function definitions
            expect(lexer->tok, T_SEMICOLON, "semicolon");
        }
        
        return func_decl_node;

    default:
        break;
    }
}

node* parse(char* file){
    string* input = read_file(file);
    if(!input){
        return NULL;
    }
    lexer* lexer = init_lexer(input->value);
    if(!lexer){
        return NULL;
    }
    read_next(lexer);
    node* ast = init_node(10, N_ROOT);
    while (lexer->tok->type != T_EOF)
    {
        switch(lexer->tok->type){
            case T_KEYWORD_IMPORT:
                parse_import(lexer, ast);
                break;
            case T_KEYWORD_MODULE:
                vector_push(ast->children, parse_module(lexer));  
                break;
            case T_KEYWORD_CLASS:
                vector_push(ast->children, parse_class(lexer));  
                break;
            case T_SPECIFIER:
            case T_TYPE:
                vector_push(ast->children, parse_global_decl(lexer));
                break;
            default:
                read_next(lexer);
                break;
        } 
 
    }
    
    free(lexer);
    return ast;
}