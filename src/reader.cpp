#include "../include/reader.h"

Reader::Reader(std::string& p) : path(p) {}

void Reader::setPath(std::string& p) { path = p; }
std::string Reader::getPath() { return path; }

void Reader::setOffsetMap(std::unordered_map<int, int>& o) { offsetMap = o; }
std::unordered_map<int, int> Reader::getOffsetMap() { return offsetMap; }

std::string Reader::getReview(int i)
{
    std::ifstream binaryFile(path+"ratings_Electronics.bin", std::ios::binary);
    std::string line;
    binaryFile.seekg(offsetMap[i]);
    char c;
    while (binaryFile.get(c) && c != '#') {
        line += c;
    }
    binaryFile.close();
    return line;
}

void Reader::ReadOffsetFile()
{
    std::ifstream offsetFile(path+"offset.txt");
    std::string line;
    while(std::getline(offsetFile, line))
    {
        int lineNumber = std::stoi(line.substr(0, line.find(".")));
        int offset = std::stoi(line.substr(line.find(".") + 2));
        offsetMap[lineNumber] = offset;
    }
    offsetFile.close();
}

void Reader::CreateOffsetFile()
{
    static const auto BUFFER_SIZE = 16*1024;

    std::ifstream infile(path+"ratings_Electronics.bin", std::ios::binary);

    std::ofstream outfile(path+"offset.txt");

    std::string line;
    int lineCounter = 0;
    int offsetCounter = 0;
    char buffer[BUFFER_SIZE];

    while (infile) {
        // Read data from binary file into buffer
        infile.read(buffer, BUFFER_SIZE);
        // Get the number of bytes read
        std::streamsize bytesRead = infile.gcount();

        if (bytesRead > 0) {
            for(int i = 0; i < BUFFER_SIZE; i++)
            {
                if(buffer[i] != '#'){
                    line.push_back(buffer[i]);
                }
                else{
                    int lineSize = line.size();
                    offsetCounter += lineSize - 41;
                    outfile << lineCounter + 1 << " . " << offsetCounter << std::endl;
                    lineCounter++;
                    line.clear();
                }
            }
        }
    }
    infile.close();
    outfile.close();

    ReadOffsetFile();
}

void Reader::createBinary()
{
    static const auto BUFFER_SIZE = 16*1024;

    std::ifstream file(path+"aaa.txt");

    std::ofstream outfile(path+"ratings_Electronics.bin", std::ios::binary);

    char buffer[BUFFER_SIZE];

    while (file) {

        // Read data from file into buffer
        file.read(buffer, BUFFER_SIZE);
        // Get the number of bytes read
        std::streamsize bytesRead = file.gcount();

        int counter=0;
        if (bytesRead > 0) {
            for(int i = 0; i < BUFFER_SIZE; i++)
            {
                if(buffer[i]!='\n'){
                    outfile.write(&buffer[i], sizeof(char));
                }
                else{
                    if(counter<41){
                        for(int j = counter; j<41 ; j++){
                            char hashtag = '#';
                            outfile.write(&hashtag, sizeof(hashtag));
                        }
                        counter=0;
                        continue;
                    }
                    else{
                        offsetMap
                    }
                }
                counter++;
            }
        }
    }
    file.close();
    outfile.close();

    CreateOffsetFile();
}