#ifndef SCANNER.HPP_
#define SCANNER.HPP_

#include <stdlib.h>

// operators
#define T-COLON         ':'
#define T_SEMICOLON     ';'
#define T_COMA          ','
#define T_LPAREN        '('
#define T_RPAREN        ')'
#define T_LSQRBRE       '['
#define T-RSQRBRE       ']'
#define T_EQUAL         '='
#define T_DIVIED        '/'
#define T_MULTI         '*'
#define T_ADD           '+'
#define T_SUB           '-'
#define T_AND           '&'
#define T_OR            '|'
#define T_LESSER        '<'
#define T_GREATER       '>'
#define T_EXP           '!'
#define T_DQUOT         '"'
#define T_SQUOT         '''


// reserved words 
#define T_PROGRAM       257
#define T_BEGIN         258
#define T_END           259
#define T_IS            260
#define T_GLOBAL        261
#define T_PROCEDURE     262
#define T_IN            263
#define T_out           264
#define T_INOUT         265
#define T_IF            266
#define T_THEN          267
#define T_ELSE          268
#define T_FOR           269
#define T_RETURN        270
#define T_NOT           271
#define T_TRUE          272
#define T_FALSE         273

// identifiers, constants, etc.
#define T_IDENTIFIER    274
#define T_INT           275
#define T_DOUBLE        276
#define T_STRING        277

// unknow type
#define T_UNKNOWN       278


FILE myfile(*file)

struct token_t {
    int type;
    union {
        char    stringVal[256];
        int     intVal;
        double  doubleVal;
    } val;
    int line;
    int column;
} token;

static int ScanOneToken( FILE *fp, token_t *token) {
    
    int i, ch, nextch;
    
    do
        ch = getc(ch);
    while (isspace(ch));

    switch ch {
        // comment or divied
        case '/':
            nextch = getc(fp);
            // single line comment
            if (nextch == '/')
                while (getc(fp) != '\n');
            // multi line comment
            else if (nextch == '*') {
                for (;;) {
                    ch = getc(fp);
                    if (ch == '*') {
                        nextch = getc(fp);
                        if (nextch == '/')
                            break;
                    }
                }
            }
            // divied operator
            else if (isspach(nextch)) {
                token->type = ch;
                return ch;
            }
            // divied equal operator
            else if (nextch == '=') {
                token->type = "/=";
                return "/=";
            }
            break;

        case ';': case ',': case '[': case ']': case '(': case ')': case '&': case '|':
            token->type = ch;
            return ch;
            break;

        case ':':
            nextch = get(fp);
            // assign operator for identifier
            if (nextch == '=') {
                token->type = ":=";
                return ":=";
            } else { // unknow 
                ungetc(nextch,fp);
                token->type = T_UNKNOWN;
                token->val.intVal = ch;
                return T_UNKNOWN;
            }
            break;

            // TODO 
        case '<':
            nextch = get(fp);
            if (nextch = '=') {
                token->type = "<=";
            }

        case EOF:
            return T_END;
            break;
            
        default:
            token->val.intVal = ch;
            token->type = T_UNKNOWN;
            return T_UNKNOWN;
    }


}


#endif