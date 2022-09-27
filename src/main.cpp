#include "../include/ProductReview.h"

int main(int argc, char **argv)
{
    int n=0;

    std::cout << "Caminho do arquivo especificado:"<<argv[1]<<"\n";

    std::cout<<"\n"<<"Quantas reviews devem ser analizadas?"<<"\n";
    std::cin>>n;
  
    ProductReview* a = new ProductReview(argv,n);

    return 0;
}
    
