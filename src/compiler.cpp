#include "scanner.hpp"

int main(int argc, char** argv) {

    FILE *fp;
    if (argc != 2) {
        std::cout << "argc\n";
        return 0;
    }
    fp = argv[1];
    while (ScanOneToken(fp, token))
        std::cout << token->type << std::endl;

    return 0;
}
