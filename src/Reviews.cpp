#include "../include/Reviews.h"
#include <iostream>

Reviews::Reviews(char** argv, int nReviews){

    std::string path(argv[1]); 
    std::ifstream file;
    file.open(path);
    ProductReview* address;
    ProductReview* next;
    std::string line;

    if(file.good())
    {
        getline(file,line);
        start= new ProductReview(line);
        address=start;
    }
    for(int i=1;i<nReviews-1&&file.good();i++)
    {
        getline(file,line);
        next= new ProductReview(line);
        address->setNext(next);
        address=next;
    }
    

}