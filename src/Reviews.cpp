#include "../include/Reviews.h"
#include <iostream>

Reviews::Reviews(std::string path, int nReviews){
 
    std::ifstream file;
    file.open(path);
    std::string line;
    reviews.reserve(8000000); //8 milhoes
    ProductReview *a;

    for(int i=0;i<nReviews&&file.good();i++)
    {
        getline(file,line);
        a= new ProductReview(line);
        reviews.push_back(a);
    }
    

}

void Reviews::createBinary(std::string& path)
{
    std::ofstream eraser("ratings_Electronics.bin"); eraser.close(); //apaga o conteudo do arquivo
    std::ofstream binaryfile("ratings_Electronics.bin",std::ios::app|std::ios::binary);

    for(double i=0;i<reviews.size();i++)
    {
        binaryfile.write((char*)reviews[i],sizeof(ProductReview));
    }
}