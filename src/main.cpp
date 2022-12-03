#include "../include/func.h"
#include "../include/sort.h"
#include "../include/hash.h"

void menu()
{
    int input=-1;

    std::cout<<"OPTIONS:\n";
    std::cout<<"1 - Sorting \n";
    std::cout<<"\n2 - Hash \n";
    std::cout<<"\n\nPress 0 to quit\n";
    while (input != 1 && input != 2 && input != 0)
        std::cin>>input;
  switch (input)
  {
  case 1:
    preSort();
    break;
  case 2:
    preHash();
    break;
  case 0:
    return;
  }

  menu();
}

int main(int argc, char **argv)
{
    std::string path;
    if(argc>1)
    {
        std::string pa(argv[1]);
        path = pa;
    }
    else path="../files/";

    std::cout << "Caminho do arquivo especificado:"<<path<<"\n";

    std::cout<<"\n|====== STARTING PRE PROCESSING ======|\n\n";

    std::cout<<"\n"<<"Quantas reviews devem ser analizadas?"<<"\n";
    std::cin>>nReviews;
    

    // Tempo para geração do arquivo binário
    double timeForCreateBinary;
    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();

    createBinary2(path,nReviews);
    nReviews = getSize();

    std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    timeForCreateBinary=std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count();

    
    std::cout<<"\n|====== PRE PROCESSING FINISHED ======|\n\n";
    std::cout << "Tempo para gerar o arquivo binário: " << timeForCreateBinary << "\n\n";

    //GET REVIEW
    /* 
    double i=0;

    std::cout<<"\n"<<"Insira o indice da review desejada:"<<"\n";
    std::cin>>i;
    while(i>=0)
    {
        if(i>=nReviews){std::cout<<"Nao existem reviews com esse indice\n";std::cin>>i;continue;}
        getReview(i);
        std::cout<<"\n"<<"Insira o indice da review desejada:"<<"\n";
        std::cin>>i;
    } */
    
    
    //IMPORT
    /* 
    double n=0;
    ProductReview* rreviews;

    std::cout<<"\n\nPegador de reviews aleatorias\nQuantas reviews voce quer pegar?\n";
    std::cin>>n;
    std::cout<<"n: "<<n<<"\n";
    rreviews=import(n);

    std::cout<<"\n Resultados:\n";
    for(int j=0;j<n;j++)
    {
        rreviews[j].print();
    } 
   */

    menu();

    return 0;
}
    
