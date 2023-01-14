//#include "../include/sort.h"
#include "../include/hash.h"
#include "../include/huffman.h"
#include "../include/preArvore.h"

void menuArvores(Reader r);

void menu(Reader r)
{
    int input=-1;

    std::cout<<"OPTIONS:\n";
    std::cout<<"1 - Gerar Arvores \n";
    std::cout<<"\n2 - Comprimir \n";
    std::cout<<"\n\nPress 0 to quit\n";
    while (input != 1 && input != 2 && input != 0)
        std::cin>>input;
  switch (input)
  {
  case 1:
    menuArvores(r);
    break;
  case 2:
    //preHash();
    break;
  case 0:
    return;
  }

  menu(r);
}

void menuArvores(Reader r)
{
    int input=-1;

    std::cout<<"OPTIONS:\n";
    std::cout<<"1 - Arvore Vermelho-Preto \n";
    std::cout<<"\n2 - Arvore B \n";
    std::cout<<"\n\nPress 0 to quit\n";
    while (input != 1 && input != 2 && input != 0)
        std::cin>>input;
  switch (input)
  {
  case 1:
    //preSort();
    break;
  case 2:
    preArvore(r);
    break;
  case 0:
    return;
  }

  menu(r);
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

  Reader reader(path,41);

  std::cout << "Caminho do arquivo especificado:"<<path<<"\n";


  std::cout<<"\n|====== STARTING PRE PROCESSING ======|\n\n";

  std::ifstream test(path+"ratings_Electronics.bin");

  if(test.good()){

  std::cout<<"Binario ja existe\n";
  test.close();

  reader.readBinary();
  }
  else{

  // Tempo para geração do arquivo binário
  double timeForCreateBinary;
  std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();

  reader.createBinary();

  std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
  timeForCreateBinary=std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count();

  std::cout<<"\n|====== PRE PROCESSING FINISHED ======|\n\n";
  std::cout << "Tempo para gerar o arquivo binário: " << timeForCreateBinary << "\n\n";

  }

  int nlines = reader.getnLines();

  //GET REVIEW
/* 
  double i=0;
  ProductReview* pr;

  std::cout<<"\n"<<"Insira o indice da review desejada:"<<"\n";
  std::cin>>i;
  while(i>=0)
  {
  if(i>=nlines){std::cout<<"Nao existem reviews com esse indice\n";std::cin>>i;continue;}
  //std::cout<<reader.getReview(i);
  pr = new ProductReview(reader.getReview(i));
  pr->print();
  delete pr;
  std::cout<<"\n"<<"Insira o indice da review desejada:"<<"\n";
  std::cin>>i;
  }   */


  //IMPORT
/* 
  double n=0;
  ProductReview* rreviews;

  std::cout<<"\n\nPegador de reviews aleatorias\nQuantas reviews voce quer pegar?\n";
  std::cin>>n;
  std::cout<<"n: "<<n<<"\n";
  rreviews=reader.import(n);

  std::cout<<"\n Resultados:\n";
  for(int j=0;j<n;j++)
  {
  rreviews[j].print();
  }  */


  menu(reader);

  return 0;
}
    
