#ifndef HASH_H
#define HASH_H

#include "sort.h"
#include <cmath>

int tablesize;

typedef struct 
{
    std::string productId="-1";
    int qtdReviews=0;

}RegistroHash;


/* void merge(RegistroHash array[],int left, int mid, int right)
{
    int arrayA= mid-left+1; //cria o array temporario A com tamanho do intervalo do merge
    int arrayB= right-mid; //cria o array temporario B com tamanho do intervalo do merge

    RegistroHash* A = new RegistroHash[arrayA]; 
    RegistroHash* B = new RegistroHash[arrayB];

    for(int i=left;i<=mid;i++)
        A[i-left]=array[i]; //próximo elemento a considerar no primeiro intervalo
    for(int i=mid+1;i<right;i++) //próximo elemento a considerar no segundo intervalo
        B[i-mid]=array[i]; // Foi retirado o +1 de B[i-mid+1], pois acessa memória indevida
    
    int indexA=0,indexB=0; //declara os contadores do Array A,B 
    int index=left;

    //adiciona a menor string no array e aumenta o contador
    while(indexA<arrayA&&indexB<arrayB){
        if(A[indexA].qtdReviews < B[indexB].qtdReviews){   
            array[index]=A[indexA];
            indexA++;
        }else{array[index]=B[indexB];
            indexB++;
        }
        index++;
    }
    // só vai executar um dos dois while abaixo 
    //copia qualquer entrada restante da primeira metade do array
    while(indexA<arrayA){
        array[index]=A[indexA];
        indexA++;
        index++;
    }
    //copia qualquer entrada restante da segunda metade do array
    while(indexB<arrayB){
        array[index]=B[indexB];
        indexB++;
        index++;
    }
    //deleta arrays temporarios
    delete[] A;
    delete[] B; 
    //retorna o array principal
    //return array;
}

void StartmergeSort(RegistroHash array[], int left, int right) {
    if (left == right) {
        return;
    }
    int mid = (left + right) / 2;
    // pega a primeira e a segunda metade
    StartmergeSort (array, left, mid);
    StartmergeSort(array, mid + 1, right);
    merge(array , left, mid, right);
}   
 */

//finds the smallest prime number larger than num
int eratostenes(int num)
{
    if(num<3)  
        return 3;
    int n = num*2;
    std::vector<int> nat;
    for(int i=0;i<n+100;i++){
        nat.push_back(i);
    }
    nat[1]=0;

    int divisor=2;
    int trashed=0;
    int b=0;
    int trash=0;

    
    for(int a=0;a<(n/2);a++){
        
        for(int c=0;c<(n-trashed);c++){ 
            if(divisor!=0)
            if(nat[c]%divisor==0){
                nat[c]=0;
                trash++;
            }
        }
        trashed=trash;
        
        for(int d=0;d<n-trash;d++){ 
            for(int e=0;e<n;e++){
                
                if(nat[e]==0){
                    nat[e]=nat[e+1];
                    nat[e+1]=0;
                    if(nat[e]==0&&nat[e+1]==0&&nat[e+2]==0&&nat[e+3]==0)
                        break;
                }
            }
            
        }
        if(divisor>=num)
            return divisor;
        divisor=nat[0];
        b+=1;
        
        if(nat[0]==0&&nat[1]==0&&nat[2]==0)
            break;
    }
    return -1;
}

//Assigns a numerical value to a string
 double valueString(std::string s)
{
    const char* c = s.c_str();
    float p = 2;
    double value=0;
    for(int i=0;i<(int)s.length();i++)
    {
        value+=(((int)c[i])-48)*pow(p,i);
    }
    return abs(value);
} 

//Hash function
int hash(std::string d, int colisions,int h1,int h2)
{
    long int a=valueString(d);

    int n = fmod(a,100000);

    

    int hash = (n%h1) + (colisions*(1+(n%h2)));

    hash = hash%h1;

    return hash;
}

RegistroHash* createTable(int n)
{
    int ccounter=0;
    int nproducts=0;
    int size= eratostenes(n);

    RegistroHash* table = new RegistroHash[size];
    RegistroHash* importsRH = new RegistroHash[n];
    ProductReview* importsPR;
    
    bool finished;
    int index;
    importsPR=import(n);

    for(int q=0;q<n;q++)
    {
        importsRH[q].productId=importsPR[q].getProductId();
    }
    delete importsPR;
    
    /* std::cout<<"import:";
    for(int j=0;j<n;j++)
        std::cout<<importsRH[j].productId<<" "; */

    std::cout<<"\n";
    
    int h2 = 2*size/3;

    for(int i=0;i<n;i++)
    {
        finished=false;
        
        for(int c=0;!finished;c++)
        {
            index=hash(importsRH[i].productId,c,size,h2);
            
            if(table[index].productId=="-1")
            {
                table[index]=importsRH[i];
                table[index].qtdReviews++;

                finished=true;

                continue;
            }
            else if(table[index].productId==importsRH[i].productId)
            {           
                table[index].qtdReviews++;

                finished=true;
                
                continue;
            }
            else
            {
                ccounter++;
                
                //std::cout<<i<<" "<<importsRH[i].productId<<" "<<index<<" "<<c<<"\n";

                if(c>12){
                    std::cout<<"\nERROR\n";
                    //std::cout<<"size:"<<size<<" h2:"<<h2<<"\n";
                    return nullptr;
                }
                    
            }
            
        } 
    }

    for(int i=0;i<size;i++){
        if(table[i].qtdReviews!=0)
            nproducts++;
    }

    std::cout<<"\n|====== HASH DATA =======\n\n";
    std::cout<<"Hash Table Size: "<<size<<"\n";
    std::cout<<"Number of Colisions: "<<ccounter<<"\n";
    std::cout<<"Number of Products: "<<nproducts<<"\n";
    std::cout<<"\n=========================|\n\n";

    tablesize = size;

    delete importsRH;

    return table;
}

void preHash()
{
    int n;
    int P;
    std::cout<<"Quantas reviews devem ter no hash? ";
    std::cin>>n;
    while(n<1){
        std::cout<<"\nNumero invalido. Favor digitar número maior que 0\n\n";
        std::cout<<"Quantas reviews devem ter no hash? ";
        std::cin>>n;
    }
    RegistroHash* table = createTable(n);

    /* std::cout<<"\n\n====== Produtos mais recorrentes ======\n";
    std::cout<<"\nQuantas posicoes devem ser visualizadas? ";
    std::cin>>P;
    while(P<1 || P>n){
        std::cout<<"\nNumero invalido. Favor digitar numero maior que 0 e menor que "<<n<<"\n\n";
        std::cout<<"Quantas reviews devem ter no hash? ";
        std::cin>>P;
    }
    
    RegistroHash* copy = new RegistroHash[tablesize];

    for(int i = 0;i<tablesize;i++)
        copy[i]=table[i]; */
    
    

    /* std::cout<<"\nOG:";
    for(int i=0;i<tablesize;i++)
        std::cout<<table[i].productId<<" ";

    std::cout<<"\nbefore:";
    for(int i=0;i<tablesize;i++)
        std::cout<<copy[i].productId<<" ";

    StartmergeSort(copy,0,tablesize);

    std::cout<<"\nafter:";
    for(int i=0;i<tablesize;i++)
        std::cout<<copy[i].productId<<" "; */



    /* std::cout<<"\n Produtos com mais reviews:\n";
    for(int j=0;j<P;j++)
    {
        std::cout<<j+1<<" - "<<copy[j].productId<<"\n";
    } */
    
}



#endif