#ifndef SORT_H
#define SORT_H

#include "func.h"
#include "hash.h"

int nSorts = 3;

void saveData(int methodId,int n,long int comparizons,long int movimentations,double time) 
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
    default:
        method = "method "+ methodId;
        break;
    }

    saida<<method<<" com "<<n<<" items:\ncomps "<<comparizons<<", moves "<<movimentations<<", tempo: "<<time<<"\n";
} 

void methodsSeparator() {
    std::ofstream saida("../files/saida.txt",std::ios::app);
    saida<<"\n==============================================\n\n";
}

int median_of_3(ProductReview array[], int lo, int hi, long int *comparizons, long int *movements)
{
    int mid = lo + (hi - lo) / 2;

    if (array[hi].getUserId().compare(array[lo].getUserId()) < 0) {
        std::swap(array[lo], array[hi]);
        *movements += 1;
    }

    if (array[mid].getUserId().compare(array[lo].getUserId()) < 0) {
        std::swap(array[lo], array[mid]);
        *movements += 1;
    }

    if (array[hi].getUserId().compare(array[mid].getUserId()) < 0) {
        std::swap(array[mid], array[hi]);
        *movements += 1;
    }
    
    *comparizons += 3;

    return mid;
}


int partition(ProductReview array[], int lo, int hi, long int *comparizons, long int *movements) {
    int i = lo;
    int j = hi + 1;
    ProductReview v = array[lo];

    while(1) {
        while(array[++i].getUserId().compare(v.getUserId()) < 0) {
            *comparizons += 1;
            if(i == hi) break;
        }
        while(v.getUserId().compare(array[--j].getUserId()) < 0) {
            *comparizons += 1;
            if(j == lo) break;
        }
        if(i >= j) break;
        std::swap(array[i], array[j]);
        *movements += 1;
    }

    std::swap(array[lo], array[j]);
    *movements += 1;

    return j;
}



void StartQuickSort(ProductReview array[], int lo, int hi, long int *comparizons, long int *movements)
{
    if(lo < hi) {
       
        int median = median_of_3(array, lo, hi, comparizons, movements);
        std::swap(array[lo], array[median]);
       
        int j = partition(array, lo, hi, comparizons, movements);
       
        StartQuickSort(array, lo, j-1, comparizons, movements);
        StartQuickSort(array, j+1, hi, comparizons, movements);
    }
}



void quicksort(ProductReview *vet, int n)
{
    double time;
    long int comparizons=0,movement=0;
    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();
    

    StartQuickSort(vet , 0, n-1, &comparizons, &movement);


    std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    time=std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count();
    saveData(1,n,comparizons,movement,time);
}


void merge(ProductReview array[],int left, int mid, int right, long int *comparizons, long int *movements)
{
    int arrayA= mid-left+1; //cria o array temporario A com tamanho do intervalo do merge
    int arrayB= right-mid; //cria o array temporario B com tamanho do intervalo do merge

    ProductReview* A = new ProductReview[arrayA]; 
    ProductReview* B = new ProductReview[arrayB];

    for(int i=0;i<arrayA;i++)
        A[i]=array[left+i]; //próximo elemento a considerar no primeiro intervalo
    for(int j= 0;j< arrayB;j++) //próximo elemento a considerar no segundo intervalo
        B[j]=array[mid+1+j]; // Foi retirado o +1 de B[i-mid+1], pois acessa memória indevida
    
    int indexA=0,indexB=0; //declara os contadores do Array A,B 
    int index=left;

    //adiciona a menor string no array e aumenta o contador
    while(indexA<arrayA && indexB<arrayB){
        if(A[indexA].getUserId().compare(B[indexB].getUserId()) <= 0){   
            array[index]=A[indexA];
            indexA++;
        }else{
            array[index]=B[indexB];
            indexB++;
        }
        (*comparizons)++; 
        index++;
    }
    // só vai executar um dos dois while abaixo 
    //copia qualquer entrada restante da primeira metade do array
    while(indexA<arrayA){
        array[index]=A[indexA];
        indexA++;
        index++;
        (*movements)++;
    }
    //copia qualquer entrada restante da segunda metade do array
    while(indexB<arrayB){
        array[index]=B[indexB];
        indexB++;
        index++;
        (*movements)++;
    }
    //deleta arrays temporarios
    delete[] A;
    delete[] B; 
    //retorna o array principal
    //return array;
}

void StartmergeSort(ProductReview array[], int const begin, int const end, long int *comparizons, long int *movements)
{
    if (begin >= end)
        return; // Returns recursively
 
    auto mid = begin + (end - begin) / 2;
    StartmergeSort(array, begin, mid ,comparizons,movements);
    StartmergeSort(array, mid + 1, end,comparizons, movements);
    merge( array, begin, mid, end,comparizons,movements);
}

//long int *comparizons, long int *movements
void mergesort(ProductReview *vet, int n)
{
    double time;
    long int comparizons=0,movement=0;
    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();
    
    StartmergeSort( vet , 0, n-1, &comparizons, &movement);

    std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    time=std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count();
    saveData(2,n,comparizons,movement,time);
}

// insertionSort para o uso do TimSort.
ProductReview* insertionSort(ProductReview *vet, int init, int end, long int *comparizons, long int *movement) {
    int j;
    ProductReview chave;
    for(int i=init+1; i<=end; i++) {
        chave = vet[i];
        j = i - 1;
        while(j>=init && vet[j].getUserId().compare(chave.getUserId())>0) {
            vet[j+1] = vet[j];
            --j;
            (*movement)++;
            (*comparizons)++;
        }
        vet[j+1] = chave;
        (*movement)++;
    }
    return vet;
}

// Função que compara 2 valores e retorna o menor.
// É usada para quando estiver na última minrun o vetor não ultrapassar o tamanho
// do vetor original, resultando dessa forma em Segmentation Fault.
int menor(int val1, int val2) {
    if(val1>val2)
        return val2;
    return val1;
}

// Função para calcular a minrun ideal para o uso do Timsort com base na quantidade de itens
// no vetor de entrada (tamanho n)
int minrun(int n) {
    int r=0;
    // A minrun ideal, segundo Tim Peters, é um valor entre 32 e 64 (considerando valores de n
    // grandes)
    while(n>=64) {
        r |= n & 1;
        n>>=1;
    }
    return n + r;
}

void timsort(ProductReview *vet, int n)
{
    double time;
    long int comparizons=0,movement=0;
    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();
    

    int MINRUN = minrun(n);

    for(int i=0; i<n; i+=MINRUN) {
        vet = insertionSort(vet,i,menor(i+MINRUN-1,n-1), &comparizons, &movement);
    }

    for(int size = MINRUN; size < n; size = 2*size) {
        for(int left = 0; left<n; left += 2*size) {
            int mid = left + size - 1;
            int right = menor(left + 2*size - 1, n-1);
            if(mid < right) {
                merge(vet, left, mid, right, &comparizons, &movement);
            }
        }
    }

    std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    time=std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count();
    saveData(3,n,comparizons,movement,time);
}


void sort(ProductReview *vet, int n, int methodId)
{
    //methodId:
    //1- Quicksort 
    //2- Mergesort 
    //3- Timsort

    switch (methodId)
    {
    case 1:
        break;
    case 2:
    std::cout<<"\nMerge\n";
    for(int i=0;i < n;i++){
        std::cout<<vet[i].getUserId()<< " ";
    }
        std::cout<<" \n\n";
    

        mergesort(vet ,n);
        for(int i=0;i<n;i++)
            std::cout<<vet[i].getUserId()<<" ";
        break;
    case 3:
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
    ProductReview* review;
    ProductReview* reviews = new ProductReview[6];

    std::ifstream file("../files/input.dat");
    for(i=0;file.good();i++)
    {
        getline(file,value);
        N.push_back(stoi(value));
    }
     review = import(6);
    for(int l=0;l<nSorts;l++) //itera entre os sorts
    { 
        
       /*  for(int k=0;k<i-1;k++)  //itera entre os valores de N
        { */

            for(int j=0;j<M;j++) //roda M vezes
            {
                for(int p=0;p<6;p++)
                    reviews[p]=review[p];
               
                sort(reviews,6,l+1);     
                
            }
        /* } */
        methodsSeparator();
    }
}

#endif