//689
#ifndef SCANNER_HPP_
#define SCANNER_HPP_

#include <stdlib.h>
#include <string>
#include <queue>

// operators
//#define T-COLON         ':'
#define T_SEMICOLON     ';'
#define T_COMA          ','
#define T_LPAREN        '('
#define T_RPAREN        ')'
#define T_LSQRBRE       '['
#define T_RSQRBRE       ']'
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
#define T_SQUOT         '\''
#define T_EQUAL         280//":="
#define T_LESSEREQ      281//"<="
#define T_GREATEREQ     282//">="
#define T_DEQUAL        283//"=="
#define T_NOTEQUAL      284//"!="
#define T_DIVIEDEQ      285//"/="
#define T_MULTIEQ       286//"*="
#define T_SUBEQ         287//"-="
#define T_PLUSEQ        288//"+="

// reserved words 
#define T_PROGRAM       257
#define T_BEGIN         258
#define T_END           259
#define T_IS            260
#define T_GLOBAL        261
#define T_PROCEDURE     262
#define T_IN            263
#define T_OUT           264
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

#define T_NUM           275
#define T_CHAR          276
#define T_STRING        277

// unknow type
#define T_UNKNOWN       999


enum table_t{
    operators=1,
    reserved_words,
    identifiers,
    num,
    unknow
};




// TODO function isstringval(char ch);
bool isstringval(char ch){

    return 0;
}
// TODO function ischar(char ch);
bool ischar(char ch){

    return 0;
}

struct token_t {
    int type;
    std::string val;
    //int intVal;
    //double douVal;
    /*    
    union {
        std::string     stringVal;
        //int     intVal;
        //double  num;
    } val;
    */
    int line;
    int column;
    table_t id;
};

void ScanOneToken(FILE *fp, token_t token) {
    
    int i, nextch;
    char ch;
    
    do
        ch = getc(fp);
    while (isspace(ch));

    std::cout<<ch<<std::endl;
    switch (ch) {
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
                            ScanOneToken(fp,token);
                    }
                }
            } else if (isspace(nextch)) {// divied operator
                putc(nextch,fp);
                token.type = T_DIVIED;
                token.id=operators;
            }
            break;
            /*
            // divied equal operator
            else if (nextch == '=') {
                token->type = T_DIVIEDEQ;
                return T_DIVIEDEQ;
            }
            */

        case ';': case ',': case '[': case ']': case '(': case ')': case '&': case '|':
        case '+': case '-': case '*':
            token.type = ch;
            token.id=operators;
            break;

        case ':':
            nextch = getc(fp);
            // assign operator for identifier
            if (nextch == '=') {
                token.type = T_EQUAL;//":=";
                token.id = operators;
            }
            // UNKNOWN type
            ungetc(nextch, fp);
            token.type = T_UNKNOWN;
            token.val = ch;
            token.id = unknow;
            break;

        case '<':
            nextch = getc(fp);
            // Greater or equal operator
            if (nextch = '=') {
                token.type = T_GREATEREQ;
                token.id = operators;
            }
            // greater than operator
            ungetc(nextch, fp);
            token.type = T_GREATER;
            token.id = operators;

        case '>':
            nextch = getc(fp);
            // lesser or equal operator
            if (nextch = '=') {
                token.type = T_GREATEREQ;
                token.id = operators;
            }
            // lesser than operator
            ungetc(nextch, fp);
            token.type = T_GREATER;
            token.id = operators;

        case '=':
            nextch = getc(fp);
            // double equal operator
            if (nextch = '=') {
                token.type = T_DEQUAL;
                token.id=operators;
            }
            // unknow operator
            ungetc(nextch, fp);
            token.type = T_UNKNOWN;
            token.val = ":";
            token.id = unknow;

        case '0': case '1': case '2': case '3': case '4': case '5': case '6':
        case '7': case '8': case '9':
            token.val = ch;
            i = 1;
            while (isdigit(ch = getc(fp)))
                token.val += ch;

            if (ch == '_') {
                if ( nextch=getc(fp) == '.') {
                    token.val += nextch;
                    while(isdigit(ch = getc(fp)))
                        token.val += ch;
                    if (ch=getc(fp) == '_') {
                        token.type = T_DOUBLE;
                        token.id = num;
                    }
                    ungetc(nextch,fp);
                    token.type = T_UNKNOWN;
                    token.id = unknow;
                }
                token.type = T_INT;
                token.id = num;
            }
            break;


        /*
        case 'B':
            if (ch = getc(fp) == 'E') {
                if (ch = getc(fp) == 'G') {
                    if (ch = getc(fp) == 'I') {
                        if (ch = getc(fp) == 'N') {
                            token.type = T_BEGIN;
                            token.id=reserved_words;
                        } else {
                            token.val="BEGI" + ch;
                            for(ch=getc(fp);;ch=get(fp))
                                if(isalph(ch) || isdigit(ch) || ch=='_')
                                    token.val+=ch;
                                else
                                    break;
                            ungetc(ch, fp);
                            token.type=T_IDENTIFIER;
                            token.id=identifiers;
                        }
                    } else {
                        token.val = "BEG"+ch;
                        for(ch=getc(fp);;ch=get(fp))
                            if(isalph(ch) || isdigit(ch) || ch=='_')
                                token.val+=ch;
                            else
                                break;
                        ungetc(ch,fp);
                        token.type=T_IDENTIFIER;
                        token.id=identifiers;
                    }
                } else {
                    token.val = "BE"+ch;
                    for(ch=getc(fp);;ch=get(fp))
                        if(isalph(ch) || isdigit(ch) || ch=='_')
                            token.val+=ch;
                        else
                            break;
                    ungetc(ch,fp);
                    token.type = T_IDENTIFIER;
                    token.id=identifiers;
                }
            } else {
                token.val = 'B'+ch;
                for(ch=getc(fp);;ch=get(fp))
                    if(isalph(ch) || isdigit(ch) || ch=='_')
                        token.val+=ch;
                    else
                        break;
                ungetc(ch, fp);
                token.type = T_IDENTIFIER;
                token.id=identifiers;

            }
            break;

        case 'C':
            if (ch = getc(fp) == 'H') {
                if (ch = getc(fp) == 'A') {
                    if (ch = getc(fp) == 'R') {
                        token->type = T_CHAR;
                        return T_CHAR;
                    } else {
                        ungetc(ch, fp);
                        token->stringVal = "CHA";
                        token->type = T_UNKNOWN;
                        return T_UNKNOWN;
                    }
                } else {
                    ungetc(ch, fp);
                    token->stringVal = "CH";
                    token->type = T_UNKNOWN;
                    return T_UNKNOWN;
                }
            }
            ungetc(ch, fp);
            token->stringVal = 'C';
            token->type = T_UNKNOWN;
            return T_UNKNOWN;

        case 'E':
            ch = getc(fp);
            if (ch == 'N') {
                if (ch = getc(fp) == 'D') {
                    token->type = T_END;
                    return T_END;
                } else {
                    ungetc(ch, fp);
                    token->stringVal = "EN";
                    token->type = T_UNKNOWN;
                    return T_UNKNOWN;
                }
            } else if (ch == 'L') {
                if (ch = getc(fp) == 'S') {
                    if( ch = getc(fp) == 'E') {
                        token->type = T_ELSE;
                        return T_ELSE;
                    } else {
                        ungetc(ch, fp);
                        token->stringVal = "ELS";
                        token->type = T_UNKNOWN;
                        return T_UNKNOWN;
                    }
                } else {
                    ungetc(ch, fp);
                    token->stringVal = "EL";
                    token->type = T_UNKNOWN;
                    return T_UNKNOWN;
                }
            }
            ungetc(ch, fp);
            token->stringVal = "E";
            token->type = T_UNKNOWN;
            return T_UNKNOWN;

        case 'F':
            ch = getc(fp);
            if (ch == 'O') {
                if (ch = getc(fp) == 'R') {
                    token->type = T_UNKNOWN;
                    return T_UNKNOWN;
                } else {
                    ungetc(ch, fp);
                    token->stringVal = "FO";
                    token->type = T_UNKNOWN;
                    return T_UNKNOWN;
                }
            } else if ( ch == 'A') {
                if (ch = getc(fp) == 'L') {
                    if (ch = getc(fp) == 'S') {
                        if (ch = getc(fp) =='E') {
                            token->type = T_UNKNOWN;
                            return T_UNKNOWN;
                        } else {
                            ungetc(ch, fp);
                            token->stringVal = "FALS";
                            token->type = T_UNKNOWN;
                            return T_UNKNOWN;
                        }
                    } else {
                        ungetc(ch, fp);
                        token->stringVal = "FAL";
                        token->type = T_UNKNOWN;
                        return T_UNKNOWN;
                    }
                } else {
                    ungetc(ch, fp);
                    token->stringVal = "FA";
                    token->type = T_UNKNOWN;
                    return T_UNKNOWN;
                }
            }
            ungetc(ch, fp);
            token->stringVal = "F";
            token->type = T_UNKNOWN;
            return T_UNKNOWN;

        case 'G':
            if (ch = getc(fp) == 'L') {
                if (ch = getc(fp) == 'O') {
                    if (ch = getc(fp) == 'B') {
                        if (ch = getc(fp) == 'A') {
                            if (ch = getc(fp) == 'L') {
                                token->type = T_GLOBAL;
                                return T_GLOBAL;
                            } else {
                                ungetc(ch, fp);
                                token->stringVal = "GLOBA";
                                token->type = T_UNKNOWN;
                                return T_UNKNOWN;
                            }
                        } else {
                            ungetc(ch, fp);
                            token->stringVal = "GLOB";
                            token->type = T_UNKNOWN;
                            return T_UNKNOWN;
                        }
                    } else {
                        ungetc(ch, fp);
                        token->stringVal = "GLO";
                        token->type = T_UNKNOWN;
                        return T_UNKNOWN;
                    }
                } else {
                    ungetc(ch, fp);
                    token->stringVal = "GL";
                    token->type = T_UNKNOWN;
                    return T_UNKNOWN;
                }
            }
            ungetc(ch, fp);
            token->stringVal = "G";
            token->type = T_UNKNOWN;
            return T_UNKNOWN;


        case 'I':
            ch = getc(fp);
            if (ch == 'F') { // if
                token->type = T_IF;
                return T_IF;
            } else if (ch == 'S') { // is
                token->type = T_IS;
                return T_IF;
            } else if (ch == 'N') { // in...
                ch = getc(fp);
                if (ch == 'O') {
                    if (ch = getc(fp) == 'U') {
                        if (ch = getc(fp) == 'T') {
                            token->type = T_INOUT;
                            return T_INOUT;
                        } else {
                            ungetc(ch, fp);
                            token->type = T_UNKNOWN;
                            token->stringVal = "INOU";
                            return T_UNKNOWN;
                        }
                    } else {
                        ungetc(ch, fp);
                        token->type = T_UNKNOWN;
                        token->stringVal = "INO";
                        return T_UNKNOWN;
                    }
                } else if (ch == 'T') {
                    token->type = T_INT;
                    return T_INT;
                } else {
                    ungetc(ch, fp);
                    token->type = T_IN;
                    return T_IN;
                }
            }
            ungetc(ch, fp);
            token->type = T_UNKNOWN;
            token->stringVal = "I";
            return T_UNKNOWN;

        case 'N':
            if (ch = getc(fp) == 'O') {
                if (ch = getc(fp) == 'T') {
                    token->type = T_NOT;
                    return T_NOT;
                } else {
                    ungetc(ch, fp);
                    token->stringVal = "NO";
                    token->type = T_UNKNOWN;
                    return T_UNKNOWN;
                }
            }
            ungetc(ch, fp);
            token->type = T_UNKNOWN;
            token->stringVal = "N";
            return T_UNKNOWN;


        case 'P':
            if (ch = getc(fp) == 'R') {
                if (ch = getc(fp) == 'O') {
                    ch = getc(fp);
                    if (ch == 'G') {
                        if (ch = getc(fp) == 'R') {
                            if (ch = getc(fp) == 'A') {
                                if (ch = getc(fp) == 'M') {
                                    token->type = T_PROGRAM;
                                    return T_PROGRAM;
                                } else {
                                    ungetc(ch, fp);
                                    token->type = T_UNKNOWN;
                                    token->stringVal = "PROGRA";
                                    return T_UNKNOWN;
                                }
                            } else {
                                ungetc(ch, fp);
                                token->type = T_UNKNOWN;
                                token->stringVal = "PROGR";
                                return T_UNKNOWN;
                            }
                        } else {
                            ungetc(ch, fp);
                            token->type = T_UNKNOWN;
                            token->stringVal = "PROG";
                            return T_UNKNOWN;
                        }
                    } else if (ch == 'C') {
                        if (ch = getc(fp) == 'E') {
                            if (ch = getc(fp) == 'D') {
                                if (ch = getc(fp) == 'U') {
                                    if (ch = getc(fp) == 'R') {
                                        if (ch = getc(fp) == 'E') {
                                            token->type = T_PROCEDURE;
                                            return T_PROCEDURE;
                                        } else {
                                            ungetc(ch, fp);
                                            token->stringVal = "PROCEDUR";
                                            token->type = T_UNKNOWN;
                                            return T_UNKNOWN;
                                        }
                                    } else {
                                        ungetc(ch, fp);
                                        token->stringVal = "PROCEDU";
                                        token->type = T_UNKNOWN;
                                        return T_UNKNOWN;
                                    }
                                } else {
                                    ungetc(ch, fp);
                                    token->stringVal = "PROCED";
                                    token->type = T_UNKNOWN;
                                    return T_UNKNOWN;
                                }
                            } else {
                                ungetc(ch, fp);
                                token->stringVal = "PROCE";
                                token->type = T_UNKNOWN;
                                return T_UNKNOWN;
                            }
                        } else {
                            ungetc(ch, fp);
                            token->stringVal = "PROC";
                            token->type = T_UNKNOWN;
                            return T_UNKNOWN;
                        }
                    } else {
                        ungetc(ch, fp);
                        token->stringVal = "PRO";
                        token->type = T_UNKNOWN;
                        return T_UNKNOWN;
                    }
                } else {
                    ungetc(ch, fp);
                    token->stringVal = "PR";
                    token->type = T_UNKNOWN;
                    return T_UNKNOWN;
                }
            }
            ungetc(ch, fp);
            token->stringVal = "P";
            token->type = T_UNKNOWN;
            return T_UNKNOWN;

        case 'R':
            if (ch = getc(fp) == 'E') {
                if (ch = getc(fp) == 'T') {
                    if (ch = getc(fp) == 'U') {
                        if (ch = getc(fp) == 'R') {
                            if (ch = getc(fp) == 'N') {
                                token->type = T_RETURN;
                                return T_RETURN;
                            } else {
                                ungetc(ch, fp);
                                token->stringVal = "RETUR";
                                token->type = T_UNKNOWN;
                                return T_UNKNOWN;
                            }
                        } else {
                            ungetc(ch, fp);
                            token->stringVal = "RETU";
                            token->type = T_UNKNOWN;
                            return T_UNKNOWN;
                        }
                    } else {
                        ungetc(ch, fp);
                        token->stringVal = "RET";
                        token->type = T_UNKNOWN;
                        return T_UNKNOWN;
                    }
                } else {
                    ungetc(ch, fp);
                    token->stringVal = "RE";
                    token->type = T_UNKNOWN;
                    return T_UNKNOWN;
                }
            }
            ungetc(ch, fp);
            token->stringVal = "R";
            token->type = T_UNKNOWN;
            return T_UNKNOWN;

        case 'S':
            if (ch = getc(fp) == 'T') {
                if (ch = getc(fp) == 'R') {
                    if (ch = getc(fp) == 'I') {
                        if (ch = getc(fp) == 'N') {
                            if (ch = getc(fp) == 'G') {
                                token->type = T_UNKNOWN;
                                return T_UNKNOWN;
                            } else {
                                ungetc(ch, fp);
                                token->stringVal = "STRIN";
                                token->type = T_UNKNOWN;
                                return T_UNKNOWN;
                            }
                        } else {
                            ungetc(ch, fp);
                            token->stringVal = "STRI";
                            token->type = T_UNKNOWN;
                            return T_UNKNOWN;
                        }
                    } else {
                        ungetc(ch, fp);
                        token->stringVal = "STR";
                        token->type = T_UNKNOWN;
                        return T_UNKNOWN;
                    }
                } else {
                    ungetc(ch, fp);
                    token->stringVal = "ST";
                    token->type = T_UNKNOWN;
                    return T_UNKNOWN;
                }
            }
            ungetc(ch, fp);
            token->stringVal = "S";
            token->type = T_UNKNOWN;
            return T_UNKNOWN;

        case 'T':
            ch = getc(fp);
            if (ch == 'H') {
                if (ch = getc(fp) == 'E') {
                    if (ch = getc(fp) == 'N') {
                        token->type = T_THEN;
                        return T_THEN;
                    } else {
                        ungetc(ch, fp);
                        token->stringVal = "THE";
                        token->type = T_UNKNOWN;
                        return T_UNKNOWN;
                    }
                } else {
                    ungetc(ch, fp);
                    token->stringVal = "TH";
                    token->type = T_UNKNOWN;
                    return T_UNKNOWN;
                }
            } else if (ch == 'R') {
                if (ch = getc(fp) == 'U') {
                    if (ch = getc(fp) == 'E') {
                        token->type = T_THEN;
                        return T_THEN;
                    } else {
                        ungetc(ch, fp);
                        token->stringVal = "TRU";
                        token->type = T_UNKNOWN;
                        return T_UNKNOWN;
                    }
                } else {
                    ungetc(ch, fp);
                    token->stringVal = "TR";
                    token->type = T_UNKNOWN;
                    return T_UNKNOWN;
                }
            }
            ungetc(ch, fp);
            token->stringVal = "T";
            token->type = T_UNKNOWN;
            return T_UNKNOWN;
            */

        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I':
        case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
        case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i':
        case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
        case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
            for (;;) {
                ch = getc(fp);
                if (isdigit(ch) || isalpha(ch) || ch == '_') {
                    token.val += ch;
                    continue;
                }
                break;
            }
            ungetc(ch,fp);
            token.type = T_IDENTIFIER;
            token.id=identifiers;



       case '"':
            token.type = T_STRING;
            token.val[0] = ch;
            // TODO function isstringval(char ch);
            /*
            for (i = 1; isstringval(ch = getc(fp)); i++)
                token->val.stringVal[i] = ch;
            if (ch == '"') {
                token->val.stringVal[i+1] = ch;
                token->val.stringVal[i+2] = '\0';
            }
            */

       case '\'':
            token.type = T_CHAR;
            token.val[0] = ch;
            /*
            // TODO function ischar(char ch);
            for (i = 1; ischar(ch = getc(fp)); i++)
                token->val.stringVal[i] = ch;
            if (ch == "'") {
                token->val.stringVal[i+1] = ch;
                token->val.stringVal[i+2] = '\0';
            }
            */

        case EOF:
            break;
        default:
            token.type = T_UNKNOWN;
            token.id = unknow;
    }


}


#endif
