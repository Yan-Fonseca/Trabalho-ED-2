#include "../include/ProductReview.h"

ProductReview::ProductReview(char *argv){

    std::string path(argv);
    std::fstream file;
    file.open(path,ios::in);

    while (file.good())
    {
        std::string line;
        getline(file,line);
        Review(line);
    }
    

}