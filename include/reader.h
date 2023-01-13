#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

class Reader
{
private:
    std::string path;
    std::unordered_map<int, int> offsetMap;

public:
    Reader(std::string& p);

    void setPath(std::string& p);
    std::string getPath();
    void setOffsetMap(std::unordered_map<int, int>& o);
    std::unordered_map<int, int> getOffsetMap();


    void CreateOffsetFile();
    std::string getReview(int i);
    void ReadOffsetFile();
    void createBinary();
};