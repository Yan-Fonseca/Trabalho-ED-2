#ifndef PRODUCTREVIEW
#define PRODUCTREVIEW

#include <iostream>
#include <vector>
#include <string>

class ProductReview {

    private:

    std::string userId;
    std::string productId;
    std::string rating;
    std::string timestamp;

    long int binary_position;

    std::vector<std::string> splitString(std::string str);

    public:

    ProductReview(std::string info);
    ProductReview(ProductReview* pr);
    ProductReview(){};
    ~ProductReview();

    //Getters
    std::string getUserId(){return userId;};
    std::string getProductId(){return productId;};
    std::string getRating(){return rating;};
    std::string getTime(){return timestamp;};
    void print();

    long int getBinaryPosition(){return binary_position;};

    //Setters
    void setUserId(std::string id){userId=id;};
    void setProductId(std::string id){productId=id;};
    void setRating(std::string rate){rating=rate;};
    void setTime(std::string time){timestamp=time;};

    void setBinaryPosition(long int bp){binary_position=bp;};

    void setData(std::string info);
    void setNull();
};

#endif