#ifndef READER_H
#define READER_H

#include <fstream>
#include <unordered_map>
#include <map>
#include <string>
#include <math.h>
#include <time.h>
#include <chrono>

#include "huffman.h"
#include "ProductReview.h"
#include "List.h"

class Reader
{
private:
    std::string path;
    std::unordered_map<int, int> offsetMap;
    int mediumLineSize;
    int nLines;
    char* bin_data;
    long bin_size;
public:
    Reader(std::string& p,int m_size);

    void setPath(std::string& p);
    std::string getPath();
    void setOffsetMap(std::unordered_map<int, int>& o);
    std::unordered_map<int, int> getOffsetMap();

    int getnLines();

    void getReview(int i);
    std::string getReviewString(int i);
    std::string getBinReview(int i);
    void createBinary(std::string path);
    void readBinary();
    ProductReview* import(int n);

    void saveFile();
    void deleteBinFile(){delete[] bin_data;};

    void comprime(std::string str, int metodo);
    void descomprime(std::string str, int metodo);

    std::string comprime(int metodo);
    std::string descomprime(int metodo);
};

#endif