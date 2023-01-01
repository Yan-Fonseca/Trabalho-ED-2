#include "func.h"

class Node
{
private:
    std::string id;
    long int binary_position;
public:
    Node();
    Node(ProductReview* pr);
    Node(std::string ID);
    ~Node();

    int getPosition();
    std::string getId(){return id;}
};

Node::Node(){
    id="null";
    binary_position=-1;
}

Node::Node(ProductReview* pr)
{
    id = pr->getUserId()+""+pr->getProductId();
}

Node::Node(std::string ID){
    id = ID;
}

Node::~Node()
{
}
