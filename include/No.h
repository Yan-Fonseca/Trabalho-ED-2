 #ifndef NO_H
#define NO_H

#include "func.h"

class No
{
private:
    std::string id;
    long int binary_position;
public:
    No(){id="null";binary_position=-1;};
    No(ProductReview* pr){id = pr->getUserId()+""+pr->getProductId();};
    No(std::string ID){ id = ID;};
    ~No(){};

    int getPosition();
    std::string getId(){return id;}
};

#endif