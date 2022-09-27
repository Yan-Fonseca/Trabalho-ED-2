#include "../include/ProductReview.h"
#include <iostream>

ProductReview::ProductReview(char** argv, int nReviews){

    std::string path(argv[1]); 
    std::ifstream file;
    file.open(path);
    Review* address;
    Review* next;
    std::string line;

    if(file.good())
    {
        getline(file,line);
        start= new Review(line);
        address=start;
    }
    for(int i=1;i<nReviews-1&&file.good();i++)
    {
        getline(file,line);
        next= new Review(line);
        address->setNext(next);
        address=next;
    }
    

}