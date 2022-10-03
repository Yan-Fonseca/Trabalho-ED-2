#include "hash.h"

int nSorts = 3;

void saveData(int methodId,int n,double comparizons,double movimentations,double time) 
{
    //escreve os dados de cada sorteamento no arquivo saida.txt
    std::ofstream saida("../files/saida.txt",std::ios::app);
    std::string method;
    switch (methodId)
    {
    case 1:
        method = "quicksort";
        break;
    case 2:
        method = "mergesort";
        break;
    case 3:
        method = "rsort";
        break;
    default:
        method = "method "+ methodId;
        break;
    }

    saida<<method<<" com "<<n<<" items:"<<comparizons<<","<<movimentations<<","<<time<<"\n";

} 

void quicksort(ProductReview *vet, int n)
{
    double comparizons,movement,time;
    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();
    
    //Coloque o algoritmo abaixo
    //--------------------------





    //--------------------------

    std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    time=std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count();
    saveData(1,n,comparizons,movement,time);
}

void mergesort(ProductReview *vet, int n)
{
    double comparizons,movement,time;
    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();
    
    //Coloque o algoritmo abaixo
    //--------------------------





    //--------------------------

    std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    time=std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count();
    saveData(1,n,comparizons,movement,time);
}

void Rsort(ProductReview *vet, int n)
{
    double comparizons,movement,time;
    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();
    
    //Coloque o algoritmo abaixo
    //--------------------------





    //--------------------------

    std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    time=std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count();
    saveData(1,n,comparizons,movement,time);
}


void sort(ProductReview *vet, int n, int methodId)
{
    //methodId:
    //1- Quicksort 
    //2- Mergesort 
    //3- ???

    switch (methodId)
    {
    case 1:
        quicksort(vet,n);
        break;
    case 2:
        mergesort(vet,n);
        break;
    case 3:
        Rsort(vet,n); //ainda nao esta definido
        break;
    default:
        std::cout<<"Sorting algorithm ID not valid\n";
        return;
    }
}

void preSort()
{
    std::ofstream eraser("../files/saida.txt"); eraser.close(); //apaga o arquivo

    std::vector<int> N;
    int M = 3;
    int i;
    std::string value;
    ProductReview* reviews;

    std::ifstream file("../files/input.dat");
    for(i=0;file.good();i++)
    {
        getline(file,value);
        N.push_back(stoi(value));
    }

    for(int l=0;l<nSorts;l++) //itera entre os sorts
    {
        for(int k=0;k<i-1;k++)  //itera entre os valores de N
        {
            for(int j=0;j<M;j++) //roda M vezes
            {
                reviews = import(N[k]);
                sort(reviews,N[k],l+1);       
            }
        }
    } 
        
    
}