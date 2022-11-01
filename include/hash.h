#include "sort.h"
#include <cmath>

int* counter;

void startcounter(int n)
{
    counter = new int[n];
    for(int i=0;i<n;i++)
        counter[i]=0;
}

void deletecounter(){delete counter;}

void countUp(int index){counter[index]++;}

int twopowers(int n)
{
    int numero=2;
    std::vector<int> array;
    for(int j=0;numero<n;j++){
        array.push_back(numero);
        numero=numero*2;
    }
    return numero;
}

 double valueString(std::string s)
{
    const char* c = s.c_str();
    float p = 2;
    double value=0;
    for(int i=0;i<s.length();i++)
    {
        value+=(((int)c[i])-48)*pow(p,i);
    }
    return value;
} 

double tratamento(std::string s)
{
    std::stringstream ss;
    for(int i=0;i<(int)s.length();i++)
    {
        if((int)s[i]>='0'&&(int)s[i]<='9')
            ss<<s[i];
    }

    s=ss.str();

    return stod(s);

}

int hash(std::string d, int colisions,int size)
{
    double a=valueString(d);

    int n = fmod(a,100000);
    int h1= size;
    int h2 = (h1/2)+1;
    int hash = fmod(n,h1)+ (colisions*fmod(n,h2));
    //int hash = n%h1+ (colisions*n%h2);
    hash = hash%h1;
    return hash;
}

ProductReview* createTable(int n)
{
    int ccounter=0;
    int nproducts=0;
    int size= twopowers(n);
    startcounter(size);

    std::string null="-1";

    ProductReview* table = new ProductReview[size];
        for(int j=0;j<size;j++){
            table[j].setUserId(null);
            table[j].setProductId(null);
            table[j].setRating(null);
            table[j].setTime(null);
        }
    ProductReview* imports;
    int colisions=0;
    bool finished;
    int index;
    imports=import(n);



    std::cout<<"import:";
    for(int j=0;j<n;j++)
        std::cout<<imports[j].getProductId()<<" ";
    std::cout<<"\n";

    for(int i=0;i<n;i++)
    {
        finished=false;
        colisions=0;
        //std::cout<<"ID:"<< imports[i].getProductId()<<"\n";
        for(int c=0;!finished;c++)
        {
            index=hash(imports[i].getProductId(),c,size);
            
            //std::cout<<c+1<<" Index:"<<index<<"\n";
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
                //std::cout<<"Index:"<<index<<"   value :"<<table[index].getProductId()<<";";
                colisions++;
                ccounter++;
            }
            
        } 
    }

    std::cout<<"\n[";
    for(int i=0;i<size;i++){
        std::cout<<table[i].getProductId()<<" ";
    }
    std::cout<<"]\n";

    std::cout<<"\n[";
    for(int i=0;i<size;i++){
        std::cout<<counter[i]<<" ";
        if(counter[i]!=0)
            nproducts++;
    }
    std::cout<<"]\n";

    std::cout<<"\n|====== HASH DATA =======\n\n";
    std::cout<<"Hash Table Size: "<<size<<"\n";
    std::cout<<"Number of Colisions: "<<ccounter<<"\n";
    std::cout<<"Number of Products: "<<nproducts<<"\n";
    std::cout<<"\n=========================|\n";

    delete counter;

    return table;
}

void preHash()
{
    int n;
    std::cout<<"Quantas review devem ser importadas para a tabela?\n";
    std::cin>>n;
    ProductReview* table = createTable(n);
}



