#ifndef FUNC_H
#define FUNC_H

#include "../include/ProductReview.h"
#include <fstream>
#include <math.h>
#include <time.h>
#include <iomanip>
#include <chrono>

int nReviews=0;

unsigned int userId_size=15,productId_size=11,rating_size=4,timestamp_size=11;

int nTotal = 7824482;

std::string path= "";

//No meio do arquivo temos pouquissimas instancias de userIds contendo +- 21 chars
//Essa struck é para não ser necessário armazenar 21 bytes para todos userIds em binário
typedef struct 
{
    int index=0;
    int extraSize=0;
} Irregular;

std::vector<Irregular> IrregUser;
std::vector<Irregular> IrregProduct; //Talvez tenham ProductIds irregulares??
std::vector<Irregular> IrregTime;

void getReview(int i)
{
    int size = userId_size+productId_size+rating_size+timestamp_size;
    std::ifstream bin(path+"ratings_Electronics.bin",std::ios::in|std::ios::binary);
    if(bin.is_open())
    {
        char str[4][30];
        unsigned int s[4]={userId_size,productId_size,rating_size,timestamp_size}; 
        int extra=0;

        bin.seekg(0, bin.beg);

        for(unsigned int q=0;q<IrregUser.size()||q<IrregProduct.size()||q<IrregTime.size();q++){ //Algoritmo para lidar com inputs nao usuais
            if(q<IrregUser.size()){
                if(i>IrregUser[q].index)
                    extra+=IrregUser[q].extraSize;
                else if(i==IrregUser[q].index)
                    s[0]+=IrregUser[q].extraSize;
            }
            if(q<IrregProduct.size()){
                if(i>IrregProduct[q].index)
                    extra+=IrregProduct[q].extraSize;
                else if(i==IrregProduct[q].index)
                    s[1]+=IrregProduct[q].extraSize;
            }
            if(q<IrregTime.size()){
                if(i>IrregTime[q].index)
                    extra+=IrregTime[q].extraSize;
                else if(i==IrregTime[q].index)
                    s[1]+=IrregTime[q].extraSize;
            }
        }

        bin.ignore((size*i + extra),EOF);

        for(int j=0;j<4;j++)
        {
            bin.read(str[j],s[j]);
            std::cout<<str[0]<<" ";
        }

        std::string user(str[0]);
        std::string product(str[1]);
        std::string rate(str[2]);   
        std::string time(str[3]);


        std::cout<<"-------------\nReview "<<i<<":\n";

        std::cout<<"\n UserId: "<<user<<"\n ProductId: "<<product<<"\n Rating: "<<rate<<"\n Timestamp: "<<time;

        std::cout<<"\n-------------\n";
    }
    
}   

std::string getReviewString(int i) //igual a funçao superior em todos os sentidos, menos o retorno
{
    std::string input;
    int size = userId_size+productId_size+rating_size+timestamp_size;
    std::ifstream bin(path+"ratings_Electronics.bin",std::ios::in|std::ios::binary);
    if(bin.is_open())
    {
        char str[4][30];
        unsigned int s[4]={userId_size,productId_size,rating_size,timestamp_size};
        int extra=0;

        bin.seekg(0, bin.beg);

        for(unsigned int q=0;q<IrregUser.size()||q<IrregProduct.size()||q<IrregTime.size();q++){ //Algoritmo para lidar com inputs nao usuais
            if(q<IrregUser.size()){
                if(i>IrregUser[q].index)
                    extra+=IrregUser[q].extraSize;
                else if(i==IrregUser[q].index)
                    s[0]+=IrregUser[q].extraSize;
            }
            if(q<IrregProduct.size()){
                if(i>IrregProduct[q].index)
                    extra+=IrregProduct[q].extraSize;
                else if(i==IrregProduct[q].index)
                    s[1]+=IrregProduct[q].extraSize;
            }      
            if(q<IrregTime.size()){
                if(i>IrregTime[q].index)
                    extra+=IrregTime[q].extraSize;
                else if(i==IrregTime[q].index)
                    s[1]+=IrregTime[q].extraSize;
            }
        }

        bin.ignore((size*i + extra),EOF);

        for(int j=0;j<4;j++)
        {
            bin.read(str[j],s[j]);
            //std::cout<<str[0]<<" ";
        }

        std::string user(str[0]);
        std::string product(str[1]);
        std::string rate(str[2]);   
        std::string time(str[3]);

        input=user+","+product+","+rate+","+time;
    }
    return input;
}   

std::vector<ProductReview*> loadReviews(double nReviews){
    //std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();

    std::ifstream loader(path+"ratings_Electronics.csv");
    std::string line;
    std::vector<ProductReview*> reviews;
    reviews.reserve(nTotal);
    ProductReview *a;
    double counter=0;    

    if(nReviews<0)
        while(loader.good())
        {
            getline(loader,line);
            a= new ProductReview(line);
            reviews.push_back(a);
            counter++;
            //loading(counter,7824483);
        }
    else
        for(double i=0;i<nReviews&&loader.good();i++)
        {
            getline(loader,line);
            a= new ProductReview(line);
            reviews.push_back(a);
            //loading(i,nReviews);
        }
    /* std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    double time=std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count();
    std::cout<<time; */

    //std::cout<<"[&&&&&&&&&&] 100%\n";
    return reviews;
}

void createBinary(std::string p, double n)
{
    nReviews=n;
    path=p;
    std::vector<ProductReview*> reviews;
    reviews = loadReviews(nReviews);
    std::string line;

    std::string user,product,rate,time;

    std::ofstream eraser(path+"ratings_Electronics.bin"); eraser.close(); //apaga o conteudo do arquivo
    std::ofstream binaryfile(path+"ratings_Electronics.bin",std::ios::app|std::ios::binary);

    if(n<0)nReviews=reviews.size();

    for(int i=0;i<nReviews;i++)
    {
        user=reviews[i]->getUserId();
        product=reviews[i]->getProductId();
        rate=reviews[i]->getRating();
        time=reviews[i]->getTime();

        int UidSize = userId_size;
        int PidSize = productId_size;

        Irregular irreg;

        if(user.length()>userId_size-1){ //-1 e para sempre ter 1 byte extra
            irreg.index = i;
            UidSize=user.length()+1;
            irreg.extraSize = UidSize-userId_size;
            IrregUser.push_back(irreg);
        }
        if(product.length()>productId_size-1){
            irreg.index = i;
            PidSize=product.length()+1;
            irreg.extraSize = PidSize-productId_size;
            IrregProduct.push_back(irreg);
        }


        binaryfile.write(reinterpret_cast<const char*>(user.c_str()),UidSize);
        binaryfile.write(reinterpret_cast<const char*>(product.c_str()),PidSize);
        binaryfile.write(reinterpret_cast<const char*>(rate.c_str()),rating_size);
        binaryfile.write(reinterpret_cast<const char*>(time.c_str()),timestamp_size);
        
    }
}

int anti_duplicate(int arr[],int num,int filled,int max)
{
    if(filled==0)
    {
        arr[0]=num;
        return num;
    }
    else{
            
        int lo = 0, hi = filled;
        int mid;
        
        //binary search
        while (hi - lo > 1) {
            mid = (hi + lo) / 2;
            if (arr[mid] < num) {
                lo = mid + 1;
            }
            else {
                hi = mid;
            }
        }
        if (arr[lo] == num) 
        {
            int val=num+1;
            if(val==max)
                val=0;
            val=anti_duplicate(arr,val,filled,max);
            return val;
        }
        else if (arr[hi] == num) 
        {
            int val=num+1;
            if(val==max)
                val=0;
            val=anti_duplicate(arr,val,filled,max);
            return val;
        }
        else {
            for(int i=filled-1;i>=lo;i--)
            {
                arr[i+1]=arr[i];
            }
            if(num<arr[lo])
                arr[lo]=num;
            else
                arr[hi]=num;
            return num;
        }
    }
}



ProductReview* import(int n)
{
    int *arr = new int[n];
    int filled=0;
    int rnd=0;

    ProductReview *b = new ProductReview[n];
    
    for(int i=0;i<n;i++)
    {
        srand(i*time(0));
        rnd=rand()% nReviews;
        

        rnd=anti_duplicate(arr,rnd,filled,nReviews);
        filled++;

        std::string info = getReviewString(rnd);
        b[i].setData(info);
    }
    std::cout<<"\n";
    /* for(int i=0;i<filled;i++)
        std::cout<<arr[i]; */
    delete arr;
    return b;
}

double getSize()
{
    return nReviews;
}

#endif