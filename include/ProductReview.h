#include <iostream>
#include <vector>
#include <string.h>

class ProductReview{

    private:

    std::string userId;
    std::string productId;
    float rating;
    std::string timestamp;

    ProductReview* next;

    std::vector<std::string> splitString(std::string str);

    public:

    ProductReview(std::string info);
    ~ProductReview();

    //Getters
    std::string getUserId(){return userId;};
    std::string getProductId(){return productId;};
    float getRating(){return rating;};
    std::string getTime(){return timestamp;};
    ProductReview* getNext(){return next;};
    void print();

    //Setters
    void setUserId(std::string id){userId=id;};
    void setProductId(std::string id){productId=id;};
    void setRating(float rating){this->rating=rating;};
    void setTime(std::string time){timestamp=time;};
    void setNext(ProductReview* next){this->next=next;};

    

};