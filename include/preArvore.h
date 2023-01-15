#ifndef PRE_ARVORE_H
#define PRE_ARVORE_H

#include "ArvoreVP.h"
#include "ArvoreB.h"

std::vector<long double > execArvoreB(int order, int n, int b, ProductReview* imports, ProductReview* search)
{
    std::vector<long double > stats;

    ArvoreB* arvoreb = new ArvoreB(order);

    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < n ; i++ ){
        arvoreb->insere(&(imports[i]));
    }        
    std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    long double timeN=std::chrono::duration_cast<std::chrono::duration<long double >>(fim - inicio).count(); 
    std::cout<<timeN<<"    ";
    stats.push_back(timeN);
    int comp = arvoreb->getComp();
    stats.push_back(comp);

    arvoreb->resetComp();

    inicio = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < b ; i++ ){
        arvoreb->busca(search[i].getUserId(),search[i].getProductId());
    } 
    fim = std::chrono::high_resolution_clock::now();
    long double timeB=std::chrono::duration_cast<std::chrono::duration<long double >>(fim - inicio).count();
    std::cout<<timeB;
    stats.push_back(timeB);
    int com = arvoreb->getComp();
    stats.push_back(com);

    delete arvoreb;

    std::cout<<"test delete\n";

    return stats;
}

std::vector<long double > execArvoreVP( int n, int b, ProductReview* imports, ProductReview* search)
{
    std::vector<long double > stats;

    ArvoreVP* arvorevp = new ArvoreVP();

    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < n ; i++ ){
        arvorevp->insere(&(imports[i]));
    }        
    std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    long double timeN=std::chrono::duration_cast<std::chrono::duration<long double >>(fim - inicio).count(); 

    stats.push_back(timeN);

    int comp = arvorevp->getComp();
    stats.push_back(comp);

    arvorevp->resetComp();

    inicio = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < b ; i++ ){
        arvorevp->busca(search[i].getUserId(),search[i].getProductId());
    } 
    fim = std::chrono::high_resolution_clock::now();
    long double timeB=std::chrono::duration_cast<std::chrono::duration<long double >>(fim - inicio).count();
    stats.push_back(timeB);
    int com = arvorevp->getComp();
    stats.push_back(com);

    //delete arvorevp;

    return stats;
}

void preArvore(Reader reader)
{
    reader.saveFile();
    std::cout<<"preArvore\n";
    int orders[3]={20,200};
    int n = 1000000;
    int b = 100;

    std::ofstream file("../files/saida.txt");
    if(file.fail()){
        std::cout<<"Não foi possivel abrir";
    }

    std::vector<std::string> tipos= {"\nArvore B: \n","\nArvore VP: \n"};
    for(std::string tipo : tipos){
        file<<tipo;
        for(int k = 0; k < 2 ; k++ ){ //itera orders
            if(tipo!="Arvore VP: \n")
                file<<"m = "<<orders[k]<<"\n";

            //std::vector<long> stats;
            //std::vector<std::vector<long>> stats;
            std::vector<std::vector<long double>> stats;
            for(int j = 0; j < 2; j++ ){ //tem que rodar 3 vezes

                ProductReview* imports = reader.import(n);
                ProductReview* search = reader.import(b);

                std::vector<long double > stat;
                if(tipo!="Arvore VP: \n")
                    stat = execArvoreB(orders[k],n,b,imports,search);
                else
                    stat = execArvoreVP(n,b,imports,search);
                stats.push_back(stat);

                std::cout<<"test 1\n";

                file<<j<<": ti - ";
                file<<stats[j][0];
                file<<" ci - ";
                file<<stats[j][1];
                file<<" tb - ";
                file<<stats[j][2];
                file<<" cb - ";
                file<<stats[j][3]<<"\n";

                std::cout<<"test 2\n";
            }
                /*
                if(tipo!="Arvore VP: \n")
                    stats.push_back(execArvoreB(orders[k],n,b,imports,search));
                else
                    stats.push_back(execArvoreVP(n,imports,search));
                    file<<j<<": t i - "<<stats[j][0]<<" c i - "<<stats[j][1]<<" t b - "<<stats[j][2]<<" c b - "<<stats[j][3]<<"\n";
                */
            
            
            std::vector<long double > medias = {0,0,0,0};

            for(std::vector<long double > stat : stats ){
                medias[0] += stat[0];
                medias[1] += stat[1];
                medias[2] += stat[2];
                medias[3] += stat[3];
            }
            medias[0]/=stats.size();
            medias[1]/=stats.size();
            medias[2]/=stats.size();
            medias[3]/=stats.size();

            file<<"Medias:\n";
            file<<"Time insert: " << medias[0] <<"\n";
            file<<"Comp insert: " << medias[1] <<"\n";
            file<<"Time busca: " << medias[2] <<"\n";
            file<<"Comp busca: " << medias[3] <<"\n";

            if(tipo=="Arvore VP: \n")
                break;
        }
    }
    file.close();
}

#endif 