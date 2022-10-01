#include <iostream>
#include <vector>
#include <string>

class ProductReview{

    private:

    std::string userId;
    std::string productId;
    std::string rating;
    std::string timestamp;

    std::vector<std::string> splitString(std::string str);

    public:

    ProductReview(std::string info);
    ProductReview(){};
    ~ProductReview();

    //Getters
    std::string getUserId(){return userId;};
    std::string getProductId(){return productId;};
    std::string getRating(){return rating;};
    std::string getTime(){return timestamp;};
    void print();

    //Setters
    void setUserId(std::string id){userId=id;};
    void setProductId(std::string id){productId=id;};
    void setRating(std::string rate){rating=rate;};
    void setTime(std::string time){timestamp=time;};

    void setData(std::string info);

    

};