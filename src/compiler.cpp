#include <iostream>
#include <cstdio>
#include <fstream>
#include "scanner.hpp"

int main(int argc, char** argv) {

    FILE *fp;
    if (argc != 2) {
        std::cout << "argc\n";
        return 0;
    }
    fp = fopen(argv[1], "r+");


    token_t token;
    ScanOneToken(fp,token);
    std::cout<<token.type<<','<<token.val<<','<<token.id;
    /*
    while (ScanOneToken(fp, token_t))
        std::cout << token_t->type << std::endl;
    */

    return 0;
}
