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

    saida<<method<<" com "<<n<<" items:\ncomps "<<comparizons<<", moves"<<movimentations<<", tempo:"<<time<<"\n";

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

ProductReview* merge(ProductReview array[],int left, int mid, int right, double *comparizons, double *movements)
{
    //std::cout << "Dentro do merge\n";
    int arrayA= mid-left+1;
    int arrayB= right-mid;

    //std::cout << "Após definição de ArrayA e ArrayB\n";

    ProductReview* A = new ProductReview[arrayA];
    ProductReview* B = new ProductReview[arrayB];

    for(int i=left;i<=mid;i++)
        A[i-left]=array[i];
    for(int i=mid+1;i<right;i++)
        B[i-mid]=array[i]; // Foi retirado o +1 de B[i-mid+1], pois acessa memória indevida
    
    int indexA=0,indexB=0;
    int index=left;

    while(indexA<arrayA&&indexB<arrayB)
    {
        if(A[indexA].getUserId().compare(B[indexB].getUserId()) < 0)
        {   
            array[index]=A[indexA];
            indexA++;
        }
        else
        {
           array[index]=B[indexB];
            indexB++; 
        }
        index++;
    }

    while(indexA<arrayA)
    {
        array[index]=A[indexA];
        indexA++;
        index++;
    }
    while(indexB<arrayB)
    {
        array[index]=B[indexB];
        indexB++;
        index++;
    }

    delete[] A;
    delete[] B; 

    return array;
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
    saveData(2,n,comparizons,movement,time);
}

/* int* runDivider(ProductReview *array,int size)
{
    int const minrun = 64;
    int runsize=0;
    std::vector<int> divisions={0};
    for(int i=0;i<size;i++)
    {
        if(runsize<minrun)
            runsize++;
        else if(runsize>=minrun&&array[i-1]<)
    }
} */

// insertionSort para o uso do TimSort.
ProductReview* insertionSort(ProductReview *vet, int init, int end, double *comparizons, double *movement) {
    int j;
    ProductReview chave;
    for(int i=init+1; i<=end; i++) {
        std::cout << "Valor de i: " << i << "\n";
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
    std::cout << "Dentro do insertion\n\n";
    return vet;
}

// Função que compara 2 valores e retorna o menor.
int menor(int val1, int val2) {
    if(val1>val2)
        return val2;
    return val1;
}

/*ProductReview* merge(ProductReview *vet, int inicio, int meio, int fim, double *comparizons, double *movements) {
    int i = inicio;
    int j = meio;
    int k = 0;

    ProductReview aux[fim-meio+1];
    
    while(i<meio && j<fim) {
        if(vet[i].getUserId().compare(vet[j].getUserId())<0) {
            aux[k] = vet[i];
            i++;
        } else {
            aux[k] = vet[j];
            j++;
        }
        (*comparizons)++;
        k++;
    }

    while (i<meio) {
        aux[k] = vet[i];
        i++;
        k++;
        (*movements)++;
    }
    while (j<fim)
    {
        aux[k] = vet[j];
        j++;
        k++;
        (*movements);
    }
    
    for(i = inicio; i<fim; i++) {
        vet[i] = aux[i-inicio];
        (*movements)++;
    }

    return vet;
}*/

int minrun(int n) {
    int r=0;
    while(n>=64) {
        r |= n & 1;
        n>>=1;
    }
    return n + r;
}

void timsort(ProductReview *vet, int n)
{
    double comparizons=0,movement=0,time;
    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();
    
    //Coloque o algoritmo abaixo
    //--------------------------
    int MINRUN = minrun(n);

    for(int i=0; i<n; i+=MINRUN) {
        vet = insertionSort(vet,i,menor(i+MINRUN-1,n-1), &comparizons, &movement);
    }

    std::cout << "minrun: " << MINRUN << "\n";
    for(int size = MINRUN; size < n; size = 2*size) {
        for(int left = 0; left<n; left += 2*size) {
            int mid = left + size - 1;
            int right = menor(left + 2*size - 1, n-1);
            if(mid < right) {
                vet = merge(vet, left, mid, right, &comparizons, &movement);
            }
        }
    }
    //--------------------------

    std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    time=std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count();
    saveData(3,n,comparizons,movement,time);
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
    saveData(4,n,comparizons,movement,time);
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
        //quicksort(vet,n);
        break;
    case 2:
        //mergesort(vet,n);
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