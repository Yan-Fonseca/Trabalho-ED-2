#ifndef HASH_H
#define HASH_H

#include "sort.h"
#include <cmath>

typedef struct 
{
    std::string productId="";
    int qtdReviews=0;

}RegistroHash;

//finds the smallest prime number larger than num
int erastotenes(int num)
{
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

/* int twopowers(int n)
{
    int numero=2;
    std::vector<int> array;
    for(int j=0;numero<n;j++){
        array.push_back(numero);
        numero=numero*2;
    }
    return numero;
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
    return value;
} 

//Hash function
int hash(std::string d, int colisions,int h1,int h2)
{
    double a=valueString(d);

    int n = fmod(a,100000);
    int hash = fmod(n,h1)+ (colisions*fmod(n,h2));
    hash = hash%h1;
    return hash;
}

RegistroHash* createTable(int n)
{
    int ccounter=0;
    int nproducts=0;
    int size= erastotenes(n);

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
    
    std::cout<<"import:";
    for(int j=0;j<n;j++)
        std::cout<<importsRH[j].productId<<" ";
    std::cout<<"\n";

    
    
    int h2 = (size/2)+1;

    for(int i=0;i<n;i++)
    {
        finished=false;
        
        for(int c=0;!finished;c++)
        {
            index=hash(importsRH[i].productId,c,size,h2);
            
            if(table[index].productId=="")
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
            }
            
        } 
    }

    /* std::cout<<"\n[";
    for(int i=0;i<size;i++){
        std::cout<<table[i].getProductId()<<" ";
    }
    std::cout<<"]\n"; */

    //std::cout<<"\n[";
    for(int i=0;i<size;i++){
        //std::cout<<counter[i]<<" ";
        if(table[i].qtdReviews!=0)
            nproducts++;
    }
    //std::cout<<"]\n";

    std::cout<<"\n|====== HASH DATA =======\n\n";
    std::cout<<"Hash Table Size: "<<size<<"\n";
    std::cout<<"Number of Colisions: "<<ccounter<<"\n";
    std::cout<<"Number of Products: "<<nproducts<<"\n";
    std::cout<<"\n=========================|\n\n";

    //delete counter;

    return table;
}

void preHash()
{
    int n;
    int P;
    std::cout<<"Quantas reviews devem ter no hash?\n";
    std::cin>>n;
    RegistroHash* table = createTable(n);
    //sorttable(table,counter);
   /*  std::cout<<"\n\n====== Produtos mais recorrentes ======\n";
    std::cout<<"\nQuantas posições devem ser visualizadas?";
    std::cin>>P;
    std::vector<RegistroHash> arr;
    for(int j=0;j<n;j++)
        arr[j]=table[j];

    RegistroHash* array = arr.data();
    //StartmergeSort(array,0,n);
    std::cout<<"\n Produtos com mais reviews:\n";
    for(int j=0;j<P;j++)
    {
        std::cout<<j+1<<" - "<<array[n-1-j].productId<<"\n";
    } */
    
}



#endif