#include "../include/ProductReview.h"

ProductReview::ProductReview(std::string info)
{
    std::vector<std::string> inf = splitString(info);

    setUserId(inf[0]);
    setProductId(inf[1]);
    setRating(inf[2]);
    setTime(inf[3]);
}

ProductReview::~ProductReview()
{
    delete(this);
}

std::vector<std::string> ProductReview::splitString(std::string str){
    std::vector<std::string> result;
    std::string current = ""; 
    for(unsigned int i = 0; i < str.size(); i++){
        if(str[i] == ','){
            if(current != ""){
                result.push_back(current);
                current = "";
            } 
            continue;
        }
        current += str[i];
    }
    if(current.size() != 0)
        result.push_back(current);
    return result;
}

void ProductReview::print(){

    std::cout<<"-------------\nReview:\n";

    std::cout<<"\n UserId: "<<getUserId()<<"\n ProductId: "<<getProductId()<<"\n Rating: "<<getRating()<<"\n Timestamp: "<<getTime();

    std::cout<<"\n-------------\n";
}

void ProductReview::setData(std::string info)
{
    std::vector<std::string> inf = splitString(info);

    setUserId(inf[0]);
    setProductId(inf[1]);
    setRating(inf[2]);
    setTime(inf[3]);
}