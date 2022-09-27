#include "Review.h"
#include <fstream>

class ProductReview{

    private:

    Review* start;
    double nReviews;

    public:

    ProductReview(char** argv,int nReviews);
    ~ProductReview();
    
    void print();
    void createBinary(std::string& path);
    void getReview(int i);
    ProductReview* import(int n);
};