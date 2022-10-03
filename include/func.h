#include "sort.h"

int nReviews=0;

int userId_size=15,productId_size=11,rating_size=4,timestamp_size=11;

int nTotal = 7824482;

//No meio do arquivo temos pouquissimas instancias de userIds contendo +- 21 chars
//Essa struck é para não ser necessário armazenar 21 bytes para todos userIds em binário
typedef struct 
{
    int index=0;
    int extraSize=0;
} Irregular;

std::vector<Irregular> IrregUser;
std::vector<Irregular> IrregProduct; //Talvez tenham ProductIds irregulares??


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
    int size = userId_size+productId_size+rating_size+timestamp_size;
    std::ifstream bin("../files/ratings_Electronics.bin",std::ios::in|std::ios::binary);
    if(bin.is_open())
    {
        char str[4][16];
        int s[4]={userId_size,productId_size,rating_size,timestamp_size}; 
        int extra=0;

        bin.seekg(0, bin.beg);

        for(int q=0;q<IrregUser.size()||q<IrregProduct.size();q++){ //Algoritmo para lidar com inputs nao usuais
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
        }

        bin.ignore((size*i + extra),EOF);

        
        bin.read(str[0],s[0]);
        std::string user(str[0]);
        bin.read(str[1],s[1]);
        std::string product(str[1]);
        bin.read(str[2],s[2]);
        std::string rate(str[2]);
        bin.read(str[3],s[3]);     
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
    std::ifstream bin("../files/ratings_Electronics.bin",std::ios::in|std::ios::binary);
    if(bin.is_open())
    {
        char str[4][16];
        int s[4]={userId_size,productId_size,rating_size,timestamp_size};
        int extra=0;

        bin.seekg(0, bin.beg);

        for(int q=0;q<IrregUser.size()||q<IrregProduct.size();q++){
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
        }

        bin.ignore((size*i + extra),EOF);

        bin.read(str[0],s[0]);
        std::string user(str[0]);
        bin.read(str[1],s[1]);
        std::string product(str[1]);
        bin.read(str[2],s[2]);
        std::string rate(str[2]);
        bin.read(str[3],s[3]);     
        std::string time(str[3]);

        std::stringstream stream;

        input=user+","+product+","+rate+","+time;
    }
    return input;
}   

std::vector<ProductReview*> loadReviews(std::string path, double nReviews){
 
    std::ifstream loader(path);
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
            loading(counter,7824483);
        }
    else
        for(double i=0;i<nReviews&&loader.good();i++)
        {
            getline(loader,line);
            a= new ProductReview(line);
            reviews.push_back(a);
            loading(i,nReviews);
        }
    std::cout<<"[&&&&&&&&&&] 100%\n";
    return reviews;
}

void createBinary(std::string path, double n)
{
    nReviews=n;
    std::vector<ProductReview*> reviews;
    reviews = loadReviews(path,nReviews);
    std::string line;

    std::string user,product,rate,time;

    std::ofstream eraser("../files/ratings_Electronics.bin"); eraser.close(); //apaga o conteudo do arquivo
    std::ofstream binaryfile("../files/ratings_Electronics.bin",std::ios::app|std::ios::binary);

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

ProductReview* import(int n)
{

    ProductReview *b = new ProductReview[n];
    
    for(int i=0;i<n;i++)
    {
        srand(i*time(0));
        std::string info = getReviewString(rand()% nReviews);
        b[i].setData(info);
    }
    return b;
}

double getSize()
{
    return nReviews;
}