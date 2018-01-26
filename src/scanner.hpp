#ifndef SCANNER.HPP_
#define SCANNER.HPP_

#include <stdlib.h>

// operators
//#define T-COLON         ':'
#define T_SEMICOLON     ';'
#define T_COMA          ','
#define T_LPAREN        '('
#define T_RPAREN        ')'
#define T_LSQRBRE       '['
#define T-RSQRBRE       ']'
//#define T_EQUAL         '='
#define T_DIVIED        '/'
#define T_MULTI         '*'
#define T_PLUS          '+'
#define T_SUB           '-'
#define T_AND           '&'
#define T_OR            '|'
#define T_LESSER        '<'
#define T_GREATER       '>'
#define T_EXP           '!'
#define T_DQUOT         '"'
#define T_SQUOT         '''
#define T_EQUAL         ":="
#define T_LESSEREQ      "<="
#define T_GREATEREQ     ">="
#define T_DEQUAL        "=="
#define T_NOTEQUAL      "!="
#define T_DIVIEDEQ      "/="
#define T_MULTIEQ       "*="
#define T_SUBEQ         "-="
#define T_PLUSEQ        "+="


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
/*
#define T_INT           275
#define T_DOUBLE        276
*/
#define T_NUM           275
#define T_CHAR          276
#define T_STRING        277

// unknow type
#define T_UNKNOWN       278


// TODO function isstringval(char ch);
// TODO function ischar(char ch);

FILE myfile(*file)

struct token_t {
    int type;
    union {
        char    stringVal[256];
        //int     intVal;
        //double  num;
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
                ungetc(nextch,fp);
                token->type = ch;
                return ch;
            }
            /*
            // divied equal operator
            else if (nextch == '=') {
                token->type = T_DIVIEDEQ;
                return T_DIVIEDEQ;
            }
            */

        case ';': case ',': case '[': case ']': case '(': case ')': case '&': case '|':
        case '+': case '-': case '*':
            token->type = ch;
            return ch;

        case ':':
            nextch = get(fp);
            // assign operator for identifier
            if (nextch == '=') {
                token->type = ":=";
                return ":=";
            }
            // UNKNOWN type
            ungetc(nextch, fp);
            token->type = T_UNKNOWN;
            token->val.intVal = ch;
            return T_UNKNOWN;

        case '<':
            nextch = get(fp);
            // Greater or equal operator
            if (nextch = '=') {
                token->type = T_GREATEREQ;
                return T_GREATEREQ;
            }
            // greater than operator
            ungetc(nextch, fp);
            token->type = T_GREATER;
            return T_GREATER;

        case '>':
            nextch = get(fp);
            // lesser or equal operator
            if (nextch = '=') {
                token->type = T_GREATEREQ;
                return T_GREATEREQ;
            }
            // lesser than operator
            ungetc(nextch, fp);
            token->type = T_GREATER;
            return T_LESSER;

        case '=':
            nextch = get(fp);
            // double equal operator
            if (nextch = '=') {
                token->type = T_DEQUAL;
                return T_DEQUAL;
            }
            // unknow operator
            ungetc(nextch, fp);
            token->type = T_UNKNOWN;
            return T_UNKNOWN;

        case '0': case '1': case '2': case '3': case '4': case '5': case '6':
        case '7': case '8': case '9':
            token->val.stringVal[0] = ch;
            i = 1;
            while (isdigit(ch = getc(fp))) {
                token->val.stringVal[i] = ch;
                i++;
            if (ch == '_') {
                if ( nextch=getc(fp) == '.') {
                    token->val.stringVal[i] = ch;
                    token->val.stringVal[i++] = nextch;
                    i++
                    while(isdigit(ch = getc(fp)))
                    {
                        token->val.stringVal[i] = ch;
                        i++;
                    }
                    if (ch=getc(fp) == '_')
                        token->val.stringVal[i] = ch;
                    ungetc(ch,fp);
                    token->type = T_UNKNOWN;
                    return T_UNKNOWN;
                }
                else {
                    ungetc(nextch,fp);
            }
            ungetc(ch,fp);
            token->type = T_NUM;
            return T_NUM;

        case 'I': case 'i':
            ch = getc(ch);
            if (ch == 'f' || ch == 'F') { // if
                token->type = T_IF;
                return T_IF;
            } else if (ch == 's' || ch = 'S') { // is
                token->type = T_IS;
                return T_IF;
            } else if (ch == 'n' || ch == 'N') { // in...
                ch = getc(ch);
                if () 
            }

        /*    
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I':
        case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case "R':
        case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i':
        case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
        case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
        */
       case '"':
            token->type = T_STRING;
            token->val.stringVal[0] = ch;
            // TODO function isstringval(char ch);
            for (i = 1; isstringval(ch = getc(fp)); i++)
                token->val.stringVal[i] = ch;
            if (ch == '"') {
                token->val.stringVal[i+1] = ch;
                token->val.stringVal[i+2] = '\0';
            }
            return T_STRING;

       case ''':
            token->type = T_CHAR;
            token->val.stringVal[0] = ch;
            // TODO function ischar(char ch);
            for (i = 1; ischar(ch = getc(fp)); i++)
                token->val.stringVal[i] = ch;
            if (ch == ''') {
                token->val.stringVal[i+1] = ch;
                token->val.stringVal[i+2] = '\0';
            }
            return T_CHAR;

        case EOF:
            return T_END;
            
        default:
            token->val.intVal = ch;
            token->type = T_UNKNOWN;
            return T_UNKNOWN;
    }


}


#endif
