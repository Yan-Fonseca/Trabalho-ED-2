#ifndef PRE_ARVORE_H
#define PRE_ARVORE_H

#include <iomanip>
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
    
    stats.push_back(timeB);
    int com = arvoreb->getComp();
    stats.push_back(com);

    //delete arvoreb;

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

    delete arvorevp;

    std::cout<<"test delete vp\n";

    return stats;
}

void preArvore(Reader reader)
{

    int orders[3]={20,200};
    int n = 1000000;
    int b = 100;

    ProductReview* imports = reader.import(n);
    ProductReview* search = reader.import(b);

    std::ofstream file("../files/saida.txt");
    if(file.fail()){
        std::cout<<"Não foi possivel abrir";
    }

    int reps = 3;

    file<<"\nArvore B: \n";
    for(int k = 0 ; k<2 ; k++){//itera orders

        std::vector<std::vector<long double>> stats;

        for(int i = 0; i < reps ; i++ ){ 
            file<<"\nm = "<<orders[k]<<"\n";

            

            std::vector<long double > stat;

            stat = execArvoreB(orders[k],n,b,imports,search);
            stats.push_back(stat);



            file<<i<<": ti - ";
            file<<stats[i][0];
            file<<" ci - ";
            file << std::setprecision(std::numeric_limits<long double>::digits10 + 1) <<stats[i][1];
            file<<" tb - ";
            file<<stats[i][2];
            file<<" cb - ";
            file<<std::setprecision(std::numeric_limits<long double>::digits10 + 1) <<stats[i][3]<<"\n";


        }   

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
        file<<"Comp insert: " <<std::setprecision(std::numeric_limits<long double>::digits10 + 1) << medias[1] <<"\n";
        file<<"Time busca: " << medias[2] <<"\n";
        file<<"Comp busca: " <<std::setprecision(std::numeric_limits<long double>::digits10 + 1) << medias[3] <<"\n";
    }
//------

    file<<"\nArvore VP: \n";
    for(int q = 0; q<1; q++){ //só para organização do código

    std::vector<std::vector<long double>> stats;

        for(int i = 0; i < reps ; i++ ){ 

            std::vector<long double > stat;

            stat = execArvoreVP(n,b,imports,search);
            stats.push_back(stat);



            file<<i<<": ti - ";
            file<<stats[i][0];
            file<<" ci - ";
            file<<std::setprecision(std::numeric_limits<long double>::digits10 + 1) <<stats[i][1];
            file<<" tb - ";
            file<<stats[i][2];
            file<<" cb - ";
            file<<std::setprecision(std::numeric_limits<long double>::digits10 + 1) <<stats[i][3]<<"\n";


        }

        std::vector<long double > medias = {0,0,0,0};

        for(auto stat : stats ){
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
        file<<"Comp insert: " <<std::setprecision(std::numeric_limits<long double>::digits10 + 1) << medias[1] <<"\n";
        file<<"Time busca: " << medias[2] <<"\n";
        file<<"Comp busca: " <<std::setprecision(std::numeric_limits<long double>::digits10 + 1) << medias[3] <<"\n";

    }

    file.close();
}

#endif 