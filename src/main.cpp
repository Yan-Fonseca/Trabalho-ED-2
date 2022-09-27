#include "../include/Reviews.h"

int main(int argc, char **argv)
{
    int n=0;
    std::string path(argv[1]);

    std::cout << "Caminho do arquivo especificado:"<<path<<"\n";

    std::cout<<"\n"<<"Quantas reviews devem ser analizadas?"<<"\n";
    std::cin>>n;
  
    Reviews* a = new Reviews(path,n);
    a->createBinary(path);
    return 0;
}
    
