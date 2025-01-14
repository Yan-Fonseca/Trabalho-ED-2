#include "../include/ProductReview.h"

ProductReview::ProductReview(std::string info)
{
    if(info=="")
        return;
    std::vector<std::string> inf = splitString(info);

    setUserId(inf[0]);
    setProductId(inf[1]);
    setRating(inf[2]);
    setTime(inf[3]);
    setBinaryPosition(stol(inf[4]));
}

ProductReview::ProductReview(ProductReview* pr)
{
    if(pr==nullptr){
        std::cerr<<"Product Review Constructor Error: Null Pointer .\n";
        return;
    }
        

    setUserId(pr->getUserId());
    setProductId(pr->getProductId());
    setRating(pr->getRating());
    setTime(pr->getTime());
    setBinaryPosition(pr->getBinaryPosition());
}

ProductReview::ProductReview(){
    setBinaryPosition(-1);
    setUserId("");
    setProductId("");
    setTime("");
    setRating("");
}

ProductReview::~ProductReview()
{
    //delete(this);
}

std::vector<std::string> ProductReview::splitString(std::string str){
    std::vector<std::string> result;
    std::string current = ""; 
    for(unsigned int i = 0; i < str.size(); i++){
        if(str[i] == ','||str[i] == '$'){
            if(current != ""){
                result.push_back(current);
                current = "";
            } 
            continue;
        }
        else if(str[i] == '*')
            continue;
        current += str[i];
    }
    if(current.size() != 0)
        result.push_back(current);
    return result;
}

void ProductReview::print(){

    std::cout<<"-------------\nReview:\n";

    std::cout<<"\n UserId: "<<getUserId()<<"\n ProductId: "<<getProductId()<<"\n Rating: "<<getRating()<<"\n Timestamp: "<<getTime()<<"\n Bin.Position: "<<getBinaryPosition()   ;

    std::cout<<"\n-------------\n";
}

void ProductReview::setData(std::string info)
{

    if(info==""){
        std::cerr<<"Product Review setData Error: Empty string .\n";
        return;
    }
    std::vector<std::string> inf = splitString(info);

    setUserId(inf[0]);
    setProductId(inf[1]);
    setRating(inf[2]);
    setTime(inf[3]);
    setBinaryPosition(stol(inf[4]));
}

void ProductReview::setNull()
{
    setUserId("-1");
    setProductId("-1");
    setRating("-1");
    setTime("-1");
    setBinaryPosition(-1);
}