#include "../include/ProductReview.h"

ProductReview::ProductReview(std::string info)
{
    std::vector<std::string> inf = splitString(info);

    setUserId(inf[0]);
    setProductId(inf[1]);
    setRating(std::stof(inf[2]));
    setTime(inf[3]);

    print();
}

std::vector<std::string> ProductReview::splitString(std::string str){
    std::vector<std::string> result;
    std::string current = ""; 
    for(int i = 0; i < str.size(); i++){
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
    std::cout<<"\n";
    std::cout<<getUserId()<<"\n";
    std::cout<<getProductId()<<"\n";
    std::cout<<getRating()<<"\n";
    std::cout<<getTime()<<"\n";
}