#include "ProductReview.h"
#include <fstream>

class Reviews{

    private:

    ProductReview* start;
    double nReviews;

    public:

   Reviews(char** argv,int nReviews);
    ~Reviews();
    
    
    void createBinary(std::string& path);
    void getReview(int i);
    ProductReview* import(int n);
};