#include "../include/Reviews.h"

int main(int argc, char **argv)
{
    int n=0;

    std::cout << "Caminho do arquivo especificado:"<<argv[1]<<"\n";

    std::cout<<"\n"<<"Quantas reviews devem ser analizadas?"<<"\n";
    std::cin>>n;
  
    Reviews* a = new Reviews(argv,n);

    return 0;
}
    
