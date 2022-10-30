#include "sort.h"

std::vector<int> twopowers(int n)
{
    std::cout<<"\npower array:2,";
    int numero=2;
    std::vector<int> array;
    for(int j=0;numero<n;j++){
        array.push_back(numero);
        numero=numero*2;
        std::cout<<numero<<",";
    }
    return array;
}

int setSize(int n)
{
    std::vector<int> powers = twopowers(n);
    bool end=false;
    int index=powers.size();

    while(!end){
        if(powers[index-1]<n && powers[index]>=n)
            end=true;
        else if(powers[index]<n)
            index= index+((powers.size() - index)/2);
        else if(powers[index-1]>n)
            index= index-((powers.size() - index)/2);
    }
    std::cout<<"\nsize:"<<powers[index];
    return powers[index];
}


int hash(int n, int colisions,int size)
{
    int h1= size;
    int h2 = (h1*9/10)+1;
    int hash = n%h1+ (colisions*n%h2);
    hash = hash%h1;
    return hash;
}

ProductReview* createTable(int n)
{
    int size= setSize(n);

    ProductReview* table = new ProductReview[size];
        for(int j=0;j<n;j++){
            table[j].setUserId("-1");
            table[j].setProductId("-1");
            table[j].setRating("-1");
            table[j].setTime("-1");
        }
    ProductReview* imports;
    int colisions=0;
    bool finished;
    int index;
    imports=import(n);
    for(int i=0;i<n;i++)
    {
        finished=false;
        for(int c=0;!finished;c++)
        {
            index=hash(stoi(imports[i].getProductId()),c,size);

            if(table[index].getProductId()=="-1"){
                table[index]=imports[i];
                finished=true;
                continue;
            }
            colisions++;
        }
    }
    return table;
}

void preHash()
{
    int n;
    std::cout<<"Quantas review devem ser importadas para a tabela?\n";
    std::cin>>n;
    ProductReview* table = createTable(n);
}

/* double valueString(std::string s)
{
    const char* c = s.c_str();
    float p = 2;
    double value=0;
    for(int i=0;i<s.length();i++)
    {
        value+=(((int)c[i])-48)*pow(p,i);
    }
    return value;
} */

