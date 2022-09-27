#include <iostream>
#include <vector>
#include <string.h>

class Review{

    private:

    std::string userId;
    double productId;
    float rating;
    std::string timestamp;

    Review* next;

    std::vector<std::string> splitString(std::string str);

    public:

    Review(std::string info);
    ~Review();

    //Getters
    std::string getUserId(){return userId;};
    double getProductId(){return productId;};
    float getRating(){return rating;};
    std::string getTime(){return timestamp;};
    Review* getNext(){return next;};

    //Setters
    void setUserId(std::string id){userId=id;};
    void setProductId(double id){productId=id;};
    void setRating(float rating){this->rating=rating;};
    void setTime(double time){timestamp=time;};
    void setNext(Review* next){this->next=next;};

};