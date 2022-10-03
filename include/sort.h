#include "../include/ProductReview.h"
#include <fstream>
#include <math.h>
#include <time.h>
#include <sstream>
#include <iomanip>

void quicksort(ProductReview *vet)
{

}

void mergesort(ProductReview *vet)
{

}

void Rsort(ProductReview *vet)
{

}


void sort(ProductReview *vet, int n, int methodId)
{
    //methodId:
    //1- Quicksort 
    //2- Mergesort 
    //3- ???

    switch (methodId)
    {
    case 1:
        quicksort(vet);
        break;
    case 2:
        mergesort(vet);
        break;
    case 3:
        Rsort(vet); //ainda nao esta definido
        break;
    default:
        std::cout<<"Sorting algorithm ID not valid\n";
        return;
    }
}