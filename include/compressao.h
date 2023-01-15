#ifdef COMPRESSAO_H
#define COMPRESSAO_H

#include <iostream>
#include "huffman.h"

std::string comprime(std::string str, int metodo) {
    switch(metodo) {
        case 0:
            huffman::Operator ope = new huffman::Operator();
            return ope->compressStr(str);
        default:
            return "";
    }
}

std::string descomprime(std::string str, int metodo) {
    switch(metodo) {
        case 0:
            huffman::Operator ope = new huffman::Operator();
            return ope->decompressStr(str);
        default:
            return "";
    }
}

void comprime(int metodo) {
    switch(metodo) {
        case 0:
            huffman::Operator ope = new huffman::Operator();
            ope->compress();
            break;
        default:
            std::cout << "Membro não implementou\n";
            break;
    }
}

void descomprime(int metodo) {
    switch(metodo) {
        case 0:
            huffman::Operator ope = new huffman::Operator();
            ope->descompress();
            break;
        default:
            std::cout << "Membro não implementou\n";
            break;
    }
}

#endif