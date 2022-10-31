#ifndef SORT_H
#define SORT_H

#include "func.h"

int nSorts = 4;

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
        method = "timsort";
        break;
    case 4:
        method = "radixsort";
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

// insertionSort para o uso do TimSort.
void insertionSort(ProductReview *vet, int init, int end) {
    int j;
    ProductReview chave;
    for(int i=init+1; i<end; i++) {
        chave = vet[i];
        j = i - 1;
        while(j>init && vet[j].getUserId().compare(chave.getUserId())>0) {
            vet[j+1] = vet[j];
            j--;
        }
        vet[i+1] = chave;
    }
}

void timsort(ProductReview *vet, int n)
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

void radixsort(ProductReview *vet, int n)
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
    //3- Timsort
    //4- Radixsort

    switch (methodId)
    {
    case 1:
        quicksort(vet,n);
        break;
    case 2:
        mergesort(vet,n);
        break;
    case 3:
        timsort(vet,n);
        break;
    case 4:
        radixsort(vet,n);
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

#endif