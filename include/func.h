#include "../include/ProductReview.h"
#include <fstream>
#include <math.h>
#include <time.h>
#include <sstream>
#include <iomanip>

int nReviews=0;

int userId_size=15,ProductId_size=11,rating_size=4,timestamp_size=11;

void loading(double i, double n)
{
    int ratio = trunc(10*i/n);

    switch (ratio)
    {
    case 0 :std::cout<<"[          ] 0%\n";break;
    case 1 :std::cout<<"[&         ] 10%\n";break;
    case 2 :std::cout<<"[&&        ] 20%\n";break;
    case 3 :std::cout<<"[&&&       ] 30%\n";break;
    case 4 :std::cout<<"[&&&&      ] 40%\n";break;
    case 5 :std::cout<<"[&&&&&     ] 50%\n";break;
    case 6 :std::cout<<"[&&&&&&    ] 60%\n";break;
    case 7 :std::cout<<"[&&&&&&&   ] 70%\n";break;
    case 8 :std::cout<<"[&&&&&&&&  ] 80%\n";break;
    case 9 :std::cout<<"[&&&&&&&&& ] 90%\n";break;
    case 10:std::cout<<"[&&&&&&&&&&] 100%\n";break;
    default:
        break;
    }
    return;
}

void getReview(int i)
{
    int size = userId_size+ProductId_size+rating_size+timestamp_size;
    std::ifstream bin("ratings_Electronics.bin",std::ios::in|std::ios::binary);
    if(bin.is_open())
    {
        char str[4][16];
        int s[4]={userId_size,ProductId_size,rating_size,timestamp_size}; 

        bin.seekg(0, bin.beg);
        bin.ignore((size*i),EOF);

        for(int j=0;j<4;j++)
        {
            bin.read(str[j],s[j]);
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

std::string getreviewString(int i)
{
    std::string input;
    int size = userId_size+ProductId_size+rating_size+timestamp_size;
    std::ifstream bin("ratings_Electronics.bin",std::ios::in|std::ios::binary);
    if(bin.is_open())
    {
        char str[4][16];
        int s[4]={userId_size,ProductId_size,rating_size,timestamp_size};

        bin.seekg(0, bin.beg);
        bin.ignore((size*i),EOF);

        for(int j=0;j<4;j++)
        {
            bin.read(str[j],s[j]);
        }
        
        std::string user(str[0]);
        std::string product(str[1]);
        std::string rate(str[2]);
        std::string time(str[3]);

        std::stringstream stream;

        /* stream<<user<<","<<product<<","<<rate<<","<<time;
        input = stream.str(); */
        input=user+","+product+","+rate+","+time;
    }
    return input;
}   

std::vector<ProductReview*> loadReviews(std::string path, double nReviews){
 
    std::ifstream loader(path);
    std::string line;
    std::vector<ProductReview*> reviews;
    //reviews.reserve(8000000 /** sizeof(ProductReview)*/); //8 milhoes
    ProductReview *a;
    double counter=0;

    if(nReviews<0)
        while(loader.good())
        {
            getline(loader,line);
            a= new ProductReview(line);
            reviews.push_back(a);
            //reviews.back()->print();
            counter++;
            loading(counter,7900000);
        }
    else
        for(double i=0;i<nReviews&&loader.good();i++)
        {
            getline(loader,line);
            a= new ProductReview(line);
            reviews.push_back(a);
            //reviews.back()->print();
            loading(i,nReviews);
        }
    
    return reviews;
}

void createBinary(std::string path, double n)
{
    nReviews=n;
    std::vector<ProductReview*> reviews;
    reviews = loadReviews(path,n);
    std::string line;

    std::string user,product,rate,time;

    std::ofstream eraser("ratings_Electronics.bin"); eraser.close(); //apaga o conteudo do arquivo
    std::ofstream binaryfile("ratings_Electronics.bin",std::ios::app|std::ios::binary);

    if(n<0)
    {
        for(double i=0;i<reviews.size();i++)
        {
            user=reviews[i]->getUserId();
            product=reviews[i]->getProductId();
            rate=reviews[i]->getRating();
            time=reviews[i]->getTime();

            binaryfile.write(reinterpret_cast<const char*>(user.c_str()),userId_size);
            binaryfile.write(reinterpret_cast<const char*>(product.c_str()),ProductId_size);
            binaryfile.write(reinterpret_cast<const char*>(rate.c_str()),rating_size);
            binaryfile.write(reinterpret_cast<const char*>(time.c_str()),timestamp_size);
        }
    }
    else
    {
        for(int i=0;i<n;i++)
        {
            user=reviews[i]->getUserId();
            product=reviews[i]->getProductId();
            rate=reviews[i]->getRating();
            time=reviews[i]->getTime();

            binaryfile.write(reinterpret_cast<const char*>(user.c_str()),userId_size);
            binaryfile.write(reinterpret_cast<const char*>(product.c_str()),ProductId_size);
            binaryfile.write(reinterpret_cast<const char*>(rate.c_str()),rating_size);
            binaryfile.write(reinterpret_cast<const char*>(time.c_str()),timestamp_size);
            
        }
    }
}

ProductReview* import(int n)
{

    ProductReview *b = new ProductReview[n];
    
    for(int i=0;i<n;i++)
    {
        srand(i*time(0));
        std::string info = getreviewString(rand()% nReviews);
        //std::cout<<"\n\nInfo:"<<info<<"\n";
        b[i].setData(info);
        //b->print();
    }
    return b;
}
