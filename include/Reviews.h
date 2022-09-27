#include "ProductReview.h"
#include <fstream>

class Reviews{

    private:

    std::vector<ProductReview*> reviews;
    double nReviews;

    public:

   Reviews(std::string path,int nReviews);
    ~Reviews();
    
    
    void createBinary(std::string& path);
    void getReview(int i);
    ProductReview* import(int n);
};