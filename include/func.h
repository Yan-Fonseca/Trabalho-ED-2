#ifndef FUNC_H
#define FUNC_H

#include "ArvoreB.h"
//#include "../include/ProductReview.h"
#include "../include/List.h"
#include <fstream>
#include <math.h>
#include <time.h>
#include <iomanip>
#include <chrono>
#include <map>


int nReviews=0;

unsigned int userId_size=15,productId_size=11,rating_size=4,timestamp_size=11;

int nTotal = 7824482; // Quantidade total de registros no arquivo csv

std::string path= "";

//No meio do arquivo temos pouquissimas instancias de userIds contendo +- 21 chars
//Essa struct é para não ser necessário armazenar 21 bytes para todos userIds em binário
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

void createBinary2(std::string p, double n) {
    nReviews=n;
    path=p;
    int i;
    int buffer_tam = 100000;

    if(n<0)nReviews=nTotal;

    std::ifstream loader(path+"ratings_Electronics.csv");
    std::string line;

    auto *reviews = new ProductReview*[buffer_tam];
    ProductReview *a;
    long counter=0; 

    std::string user,product,rate,time;

    std::ofstream eraser(path+"ratings_Electronics.bin"); eraser.close(); //apaga o conteudo do arquivo
    std::ofstream binaryfile(path+"ratings_Electronics.bin",std::ios::app|std::ios::binary);

    while(counter < nReviews) {
        for(i=0;i<buffer_tam&&loader.good();i++)
        {
            getline(loader,line);
            a= new ProductReview(line);
            reviews[i] = a;
            counter++;
        }

        buffer_tam = i;

        for(i=0;i<buffer_tam;i++)
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
        for(i=0; i<buffer_tam; i++) {
            delete reviews[i];
        }
    }
    
    delete [] reviews;
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

//pega n reviews aleatórias do binário
ProductReview* import(int n)
{
    // É criada uma tabela Hash para armazenar os os dados gerados aleatoriamente
    // Optou-se por utilizar uma lista de listas encadeadas.
    HashList::List table[HashList::getTAM()]; 
    // TAM é o número primo 7919, um número suficientemente grande
    // para comportar os dados.

    // A tabela inicia todas as suas posições com um ponteiro para um nó encadeado.
    HashList::initializeTable(table);

    int rnd=0;
    std::string key; // Chave para ser usada no hash.

    ProductReview *b = new ProductReview[n];
    
    for(int i=0;i<n;i++)
    {
        srand(i*time(0));
        rnd=rand()% nReviews;
        std::string info = getReviewString(rnd);
        b[i].setData(info);

        // Lógica para utilizar a chave: Um usuário, teoricamente, não vai avaliar o mesmo produto duas vezes
        // Portanto, julgamos ser suficiente que a chave para a função do hash seja uma combinação do id do
        // usuário e o id do produto.
        key = b[i].getProductId() + b[i].getUserId();

        // A função de inserir na tabela retorna true se a chave foi inserida na tabela.
        // Caso retorne falso, significa que o ProductReview já foi importado e, portanto, o valor de i é
        // decrementado e o loop inicia novamente.
        if(!HashList::insertInHash(table, key))
            i--;
        
    }
    
    return b;
}

double getSize()
{
    return nReviews;
}

void preArvoreB()
{
    int orders[2]={20,200};

    int n = 1000000;

    int b = 100;
    for(int k = 0; k<2;k++){
        for(int j = 0; j < 3; j++ ){

            ArvoreB* arvoreb = new ArvoreB(orders[k]);

            ProductReview* imports = import(n);

            std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();
            for(int i = 0; i < n ; i++ ){
                arvoreb->insere(&(imports[i]));
            }        
            std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
            long int timeN=std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count(); 

            delete imports;

            imports = import(b);

            inicio = std::chrono::high_resolution_clock::now();
            for(int i = 0; i < b ; i++ ){
                arvoreb->busca(imports[i].getUserId(),imports[i].getProductId());
            } 
            fim = std::chrono::high_resolution_clock::now();
            long int timeB=std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count(); 

            delete arvoreb;
        }   
    }
}

void handle_error(const char* msg) {
    perror(msg); 
    exit(255);
}


void CreateBinary1000(std::string& path)
{
    static const auto BUFFER_SIZE = 16*1024;
    
    std::ifstream file(path+"ratings_Electronics.csv");

    std::ofstream outfile(path+"ratings_Electronics.bin", std::ios::binary);

    std::vector<std::string> irregularidades;

    std::vector<std::string> lines;
    std::string line;

    char buffer[BUFFER_SIZE];

    while (file) {
        // Read data from file into buffer
        file.read(buffer, BUFFER_SIZE);
        // Get the number of bytes read
        std::streamsize bytesRead = file.gcount();

        if (bytesRead > 0) {
            
            int lastline = 0;
            int linesize = 0;
            int linenumber = 0;
            std::string irreg;
            for(int i = 0; i < BUFFER_SIZE; i++)
            {
                if(buffer[i]!='\n'){
                    line.push_back(buffer[i]);
                }
                else{
                    linesize=i-lastline;
                    lastline=i;
                    if(linesize>41){
                        irreg= linenumber + "#" + (linesize-41);
                        irreg = irreg+"#";
                        irregularidades.push_back(irreg);
                        irreg="";
                    }
                    lines.push_back(line);
                    line="";
                    linenumber++;
                }
            }

            // Write the vector of strings to the binary file
            for (const auto& lin : lines) {
                if(lin.size()>41)
                    outfile.write(lin.c_str(), lin.size());
                else   
                    outfile.write(lin.c_str(), 41);
            }

            // Clear the vectors
            lines.clear();
            irregularidades.clear();
        }
    }
    char hashtag = '#';
    outfile.write(&hashtag, sizeof(hashtag));

    for (const auto& irr : irregularidades) {
        outfile.write(irr.c_str(), irr.size());
    }
    file.close();
    outfile.close();
}

std::string ReadBinaryLine(std::string& path, int n)
{
    std::ifstream binFile(path+"ratings_Electronics.bin", std::ios::binary);
    std::string line;
    int offset = 0;

    // Move the read pointer to the end of the file
    binFile.seekg(-1, binFile.end);

    // Initialize a variable to store the current character
    char current = binFile.get();

    // Initialize an empty string to store the irregularity information
    std::string irregularInfo;
    
    // Keep reading characters until the '#' character is found
    while(current != '#')
    {
        // Add the current character to the irregularity information string
        irregularInfo = current + irregularInfo;
        
        // Move the read pointer one position back in the file
        binFile.seekg(-2, binFile.cur);
        
        // Read the next character
        current = binFile.get();
    }

    // Initialize a map to store the irregular lines information
    std::map<int,int> irregularLines;
    std::string token;
    std::istringstream tokenStream(irregularInfo);
    while (std::getline(tokenStream, token, '#')) {
        if(token.empty() || !std::isdigit(token[0])) continue;
        int lineNum = std::stoi(token);
        std::getline(tokenStream, token, '#');
        int sizeDiff = std::stoi(token);
        irregularLines[lineNum] = sizeDiff;
    }

    // Check if the requested line is an irregular line
    if (irregularLines.find(n) != irregularLines.end()) {
        // If it is, set the offset to the appropriate value
        offset = irregularLines[n];
    }
    binFile.seekg(n*41 + offset, binFile.beg);
    std::getline(binFile, line, '\0');
    binFile.close();
    return line;
}












#endif 