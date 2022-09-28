#include "../include/ProductReview.h"
#include <fstream>
#include <math.h>

void Loading(double i, double n)
{
    int ratio = trunc(10*i/n);

    switch (ratio)
    {
    case 1 :std::cout<<"[&         ] 10%\n";break;
    case 2 :std::cout<<"[&&        ] 20%\n";break;
    case 3 :std::cout<<"[&&&       ] 30%\n";break;
    case 4 :std::cout<<"[&&&&      ] 40%\n";break;
    case 5 :std::cout<<"[&&&&&     ] 50%\n";break;
    case 6 :std::cout<<"[&&&&&&    ] 60%\n";break;
    case 7 :std::cout<<"[&&&&&&&   ] 70%\n";break;
    case 8 :std::cout<<"[&&&&&&&&  ] 80%\n";break;
    case 9 :std::cout<<"[&&&&&&&&& ] 90%\n";break;
    case 10:std::cout<<"[&&&&&&&&&&] 100%\n";break;
    default:
        break;
    }
    return;
}

std::vector<ProductReview*> loadReviews(std::string path, int nReviews){
 
    std::ifstream loader(path);
    std::string line;
    std::vector<ProductReview*> reviews;
    //reviews.reserve(8000000 /** sizeof(ProductReview)*/); //8 milhoes
    ProductReview *a;
    double counter=0;

    if(nReviews<0)
        while(loader.good())
        {
            getline(loader,line);
            a= new ProductReview(line);
            reviews.push_back(a);
            //reviews.back()->print();
            counter++;
            Loading(counter,7900000);
        }
    else
        for(double i=0;i<nReviews&&loader.good();i++)
        {
            getline(loader,line);
            a= new ProductReview(line);
            reviews.push_back(a);
            //reviews.back()->print();
            Loading(i,nReviews);
        }
    
    return reviews;
}

void createBinary(std::string path, int n)
{
    std::vector<ProductReview*> reviews;
    reviews = loadReviews(path,n);
    std::string line;
    std::ofstream eraser("ratings_Electronics.bin"); eraser.close(); //apaga o conteudo do arquivo
    std::ofstream binaryfile("ratings_Electronics.bin",std::ios::app|std::ios::binary);
    std::cout<<"\nn de reviews:"<<reviews.size()<<"\n";
    if(n<0)
    {
        for(double i=0;i<reviews.size();i++)
        {
            binaryfile.write((char*)&reviews[i],sizeof(ProductReview));
        }
    }
    else
    {
        for(int i=0;i<n;i++)
        {
            binaryfile.write((char*)&reviews[i],sizeof(ProductReview));
        }
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
    std::ifstream binaryRead("../ratings_Electronics.bin",std::ios::in|std::ios::binary);
    std::ofstream printer("../ratings_Electronics.bin");
    goToBinaryReview(binaryRead,i);
    
}

int main(int argc, char **argv)
{
    int n=0;
    std::string path(argv[1]);

    std::cout << "Caminho do arquivo especificado:"<<path<<"\n";

    std::cout<<"\n"<<"Quantas reviews devem ser analizadas?"<<"\n";
    std::cin>>n;
    
    //reviews=loadReviews(path,n);
    createBinary(path,n);
    //void getReview(int i);
    //ProductReview* import(int n);
    return 0;
}
    
