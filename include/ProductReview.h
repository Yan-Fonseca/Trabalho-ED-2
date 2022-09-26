#include <Review.h>
#include <fstream>

class ProductReview{

    private:

    

    public:

    ProductReview(char *argv);
    ~ProductReview();
    
    void print();
    void createBinary(std::string& path);
    void getReview(int i);
    ProductReview* import(int n);
};