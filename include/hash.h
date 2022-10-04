#include "sort.h"

ProductReview* createTable(int n);

double valueString(std::string s)
{
    const char* c = s.c_str();
    float p = 2;
    double value=0;
    for(int i=0;i<s.length();i++)
    {
        value+=(((int)c[i])-48)*pow(p,i);
    }
    return value;
}