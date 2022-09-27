#include "../include/ProductReview.h"
#include <fstream>

std::vector<ProductReview> loadReviews(std::string path, int nReviews){
 
    std::ifstream loader(path);
    std::string line;
    std::vector<ProductReview> reviews;
    reviews.reserve(8000000 * sizeof(ProductReview)); //8 milhoes
    ProductReview *a;

    if(nReviews<0)
        for(int i=0;i<loader.good();i++)
        {
            getline(loader,line);
            a= new ProductReview(line);
            reviews.push_back(*a);
        }
    else
        for(int i=0;i<nReviews&&loader.good();i++)
        {
            getline(loader,line);
            a= new ProductReview(line);
            reviews.push_back(*a);
        }
    
    return reviews;
}

void createBinary(std::string path)
{
    std::vector<ProductReview> reviews = loadReviews(path,-1);
    std::ofstream eraser("ratings_Electronics.bin"); eraser.close(); //apaga o conteudo do arquivo
    std::ofstream binaryfile("ratings_Electronics.bin",std::ios::app|std::ios::binary);

    for(double i=0;i<reviews.size();i++)
    {
        binaryfile.write((char*)&reviews[i],sizeof(ProductReview));
        //reviews[i].~ProductReview();
    }


}

void goToBinaryReview(std::ifstream& file, unsigned int num)
{
    double size = sizeof(ProductReview);
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; i++){
            file.ignore(size);
    }
}

void getReview(int i)
{
    std::ifstream binaryRead("ratings_Electronics.bin",std::ios::in|std::ios::binary);
    std::ofstream printer("ratings_Electronics.bin");
    goToBinaryReview(binaryRead,i);
    
}

int main(int argc, char **argv)
{
    int n=0;
    std::vector<ProductReview> reviews;
    std::string path(argv[1]);

    std::cout << "Caminho do arquivo especificado:"<<path<<"\n";

    std::cout<<"\n"<<"Quantas reviews devem ser analizadas?"<<"\n";
    std::cin>>n;
    
    reviews=loadReviews(path,n);
    createBinary(path);
    //void getReview(int i);
    //ProductReview* import(int n);
    return 0;
}
    
