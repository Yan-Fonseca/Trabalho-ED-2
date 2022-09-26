#include <iostream>
#include <string.h>

class Review{

    private:

    std::string userId;
    double productId;
    float rating;
    double timestamp;

    public:

    Review();
    ~Review();

    //Getters
    std::string getUserId();
    double getProductId();
    float getRating();
    std::string getTime();

    //Setters
    void setUserId(std::string id);
    void setProductId(double id);
    void setRating(float rating);
    void setTime(double time);

}