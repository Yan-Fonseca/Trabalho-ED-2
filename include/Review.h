#include <iostream>
#include <string.h>

class Review{

    private:

    std::string userId;
    double productId;
    float rating;
    std::string timestamp;

    public:

    Review();
    ~Review();

    //Getters
    std::string getUserId(){return userId;};
    double getProductId(){return productId;};
    float getRating(){return rating;};
    std::string getTime(){return timestamp;};

    //Setters
    void setUserId(std::string id);
    void setProductId(double id);
    void setRating(float rating);
    void setTime(double time);

};