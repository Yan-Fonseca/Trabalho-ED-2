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

const long long MAX_SIZE = 1000001;

std::vector<int >isprime(MAX_SIZE , true);
std::vector<int >prime;
std::vector<int>SPF(MAX_SIZE);
 
// function generate all prime number less than N in O(n)
int manipulated_seive(int N)
{
    // 0 and 1 are not prime
    isprime[0] = isprime[1] = false ;

    N=N+5000;
 
    // Fill rest of the entries
    for (long long int i=2; i<N ; i++)
    {
        // If isPrime[i] == True then i is
        // prime number
        if (isprime[i])
        {
            // put i into prime[] vector
            prime.push_back(i);
 
            // A prime number is its own smallest
            // prime factor
            SPF[i] = i;
        }
 
        // Remove all multiples of  i*prime[j] which are
        // not prime by making isPrime[i*prime[j]] = false
        // and put smallest prime factor of i*Prime[j] as prime[j]
        // [ for exp :let  i = 5 , j = 0 , prime[j] = 2 [ i*prime[j] = 10 ]
        // so smallest prime factor of '10' is '2' that is prime[j] ]
        // this loop run only one time for number which are not prime
        for (long long int j=0;
             j < (int)prime.size() &&
             i*prime[j] < N && prime[j] <= SPF[i];
             j++)
        {
            isprime[i*prime[j]]=false;
 
            // put smallest prime factor of i*prime[j]
            SPF[i*prime[j]] = prime[j] ;
        }
    }
    for(int i=0;i<(int)prime.size();i++)
        if(prime[i]>(N-5000)*2)
            return prime[i];
    
    return -1;
}

 int median_of_3(RegistroHash array[], int lo, int hi)
 {
    int mid = lo + (hi - lo) / 2;

    if (array[hi].qtdReviews < array[lo].qtdReviews) {
         std::swap(array[lo], array[hi]);
    }

    if (array[mid].qtdReviews < array[lo].qtdReviews) {
        std::swap(array[lo], array[mid]);
    }

    if (array[hi].qtdReviews < array[mid].qtdReviews) {
        std::swap(array[mid], array[hi]);
    }
    return mid;
}

int partition(RegistroHash array[], int lo, int hi) {
    int i = lo;
    int j = hi + 1;
    RegistroHash v = array[lo];

    while(1) {
        while(array[++i].qtdReviews < v.qtdReviews) {
            if(i == hi) break;
        }
        while(v.qtdReviews < array[--j].qtdReviews) {
            if(j == lo) break;
        }
        if(i >= j) break;
        std::swap(array[i], array[j]);
    }

    std::swap(array[lo], array[j]);

    return j;
}

void StartQuickSort(RegistroHash array[], int lo, int hi)
{
    if(lo < hi) {
       
        int median = median_of_3(array, lo, hi);
        std::swap(array[lo], array[median]);
       
        int j = partition(array, lo, hi);
       
        StartQuickSort(array, lo, j-1);
        StartQuickSort(array, j+1, hi);
    }
}


//finds the smallest prime number larger than num
/* int eratostenes(int num)
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
} */

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
    int size= manipulated_seive(n);

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

    std::cout<<"\n\n====== Produtos mais recorrentes ======\n";
    std::cout<<"\nQuantas posicoes devem ser visualizadas? ";
    std::cin>>P;
    while(P<1 || P>n){
        std::cout<<"\nNumero invalido. Favor digitar numero maior que 0 e menor que "<<n<<"\n\n";
        std::cout<<"Quantas reviews devem ter no hash? ";
        std::cin>>P;
    }
    
    RegistroHash* copy = new RegistroHash[tablesize];

    for(int i = 0;i<tablesize;i++)
        copy[i]=table[i];

    std::cout<<"\nbefore:";
    for(int i=0;i<tablesize;i++)
        std::cout<<copy[i].productId<<" ";

    StartQuickSort(copy,0,tablesize);

    std::cout<<"\nafter:";
    for(int i=0;i<tablesize;i++)
        std::cout<<copy[i].productId<<" ";



    std::cout<<"\n Produtos com mais reviews:\n";
    for(int j=0;j<P;j++)
    {
        std::cout<<j+1<<" - "<<copy[j].productId<<"\n";
    }

}



#endif