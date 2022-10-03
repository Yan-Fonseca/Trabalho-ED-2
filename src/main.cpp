#include "../include/func.h"

int main(int argc, char **argv)
{
    
    double i=0;
    double n=0;
    ProductReview* rreviews;
    std::string path;
    if(argc>1)
    {
        std::string pa(argv[1]);
        path = pa;
    }
    else path="../files/test.csv";

    std::cout << "Caminho do arquivo especificado:"<<path<<"\n";

    std::cout<<"\n"<<"Quantas reviews devem ser analizadas?"<<"\n";
    std::cin>>nReviews;
    /* if(nReviews<1)
        return 0; */
    
    createBinary(path,nReviews);
    nReviews = getSize();

    std::cout<<"\n"<<"Binario Carregado!"<<"\n";


    //GET REVIEW
    std::cout<<"\n"<<"Insira o indice da review desejada:"<<"\n";
    std::cin>>i;
    while(i>=0)
    {
        if(i>=nReviews){std::cout<<"Nao existem reviews com esse indice\n";std::cin>>i;continue;}
        getReview(i);
        std::cout<<"\n"<<"Insira o indice da review desejada:"<<"\n";
        std::cin>>i;
    }
    
    
    //IMPORT
    /* std::cout<<"\n\nPegador de reviews aleatorias\nQuantas reviews voce quer pegar?\n";
    std::cin>>n;
    std::cout<<"n: "<<n<<"\n";
    rreviews=import(n);

    std::cout<<"\n Resultados:\n";
    for(int j=0;j<n;j++)
    {
        rreviews[j].print();
    }
    return 0; */
}
    
