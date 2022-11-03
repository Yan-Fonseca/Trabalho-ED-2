#include "sort.h"
#include <cmath>

//Counts the number of repetitions of each product ID
int* counter;

void startcounter(int n)
{
    counter = new int[n];
    for(int i=0;i<n;i++)
        counter[i]=0;
}

void deletecounter(){delete counter;}

void countUp(int index){counter[index]++;}

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
        if(divisor>num)
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

ProductReview* createTable(int n)
{
    int ccounter=0;
    int nproducts=0;
    int size= erastotenes(n);
    startcounter(size);

    std::string null="-1";

    ProductReview* table = new ProductReview[size];
        for(int j=0;j<size;j++){
            table[j].setNull();
        }
    ProductReview* imports;
    int colisions=0;
    bool finished;
    int index;
    imports=import(n);



    /* std::cout<<"import:";
    for(int j=0;j<n;j++)
        std::cout<<imports[j].getProductId()<<" ";
    std::cout<<"\n"; */

    
    
    int h2 = (size/2)+1;

    for(int i=0;i<n;i++)
    {
        finished=false;
        colisions=0;
        for(int c=0;!finished;c++)
        {
            index=hash(imports[i].getProductId(),c,size,h2);
            
            if(table[index].getProductId()=="-1"){
                table[index]=imports[i];
                finished=true;

                countUp(index);

                continue;
            }
            else if(table[index].getProductId()==imports[i].getProductId()){
                countUp(index);
                finished=true;
                continue;
            }
            else{
                colisions++;
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
        if(counter[i]!=0)
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
    std::cout<<"Quantas reviews devem ter no hash?";
    std::cin>>n;
    ProductReview* table = createTable(n);
    //sorttable(table,counter);
    std::cout<<"\n\n====== Produtos mais recorrentes ======\n";
    std::cout<<"\nQuantas posições devem ser visualizadas?";
    std::cin>>P;
    
}



