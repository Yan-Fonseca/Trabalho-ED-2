#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <string>

class Reader
{
private:
    std::string path;
    std::unordered_map<int, int> offsetMap;
    int mediumLineSize;
    int nLines;
public:
    Reader(std::string& p,int m_size);

    void setPath(std::string& p);
    std::string getPath();
    void setOffsetMap(std::unordered_map<int, int>& o);
    std::unordered_map<int, int> getOffsetMap();

    int getnLines();

    std::string getReview(int i);
    void createBinary();
    void readBinary();
};