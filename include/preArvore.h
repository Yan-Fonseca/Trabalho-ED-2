#ifndef PRE_ARVORE_H
#define PRE_ARVORE_H

#include "ArvoreB.h"

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

#endif 