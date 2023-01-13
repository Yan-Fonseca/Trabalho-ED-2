#include "../include/reader.h"

Reader::Reader(std::string& p,int m_size) : path(p) , mediumLineSize(m_size) {}

void Reader::setPath(std::string& p) { path = p; }
std::string Reader::getPath() { return path; }

void Reader::setOffsetMap(std::unordered_map<int, int>& o) { offsetMap = o; }
std::unordered_map<int, int> Reader::getOffsetMap() { return offsetMap; }

int Reader::getnLines(){ return nLines; }

std::string Reader::getReview(int lineNumber)
{
    std::ifstream infile(path+"ratings_Electronics.bin", std::ios::binary);
    std::string line;
    int offset = 0;
    int lineSize = mediumLineSize;
    int position = lineSize * lineNumber;
    for(auto& [line, offsetValue] : offsetMap)
    {
        if(line < lineNumber)
        {
            offset += offsetValue;
        }
    }
    position += offset;
    infile.seekg(position);

    if (offsetMap.find(lineNumber) != offsetMap.end()) {
        lineSize+=offsetMap.at(lineNumber);
    }

    char c;
    while (infile.get(c) && c != '\n') {
    line += c;
    }

    infile.close();

    std::cout<<"pos:"<<position<<" os:"<<offset<<"\n";

    return line;
}

void Reader::readBinary() {

    std::ifstream file(path+"ratings_Electronics.bin", std::ios::binary);

    std::string line;

    while (std::getline(file, line)) {
        if (line[0] == '#') {
            // This line contains the key-value pairs
            int key = 0;
            int value = 0;
            bool readingKey = true;
            for (int i = 1; i < line.length(); i++) {
                if (line[i] == '!') {
                    // Switch from reading key to reading value
                    readingKey = false;
                } else if (line[i] == '?') {
                    // Save the key-value pair and reset for next pair
                    offsetMap[key] = value;
                    key = 0;
                    value = 0;
                    readingKey = true;
                } else if (line[i] == '#') {
                    offsetMap[key] = value;
                    readingKey = false;
                } else {
                    // Add the digit to the key or value
                    if (readingKey) {
                        key = key * 10 + (line[i] - '0');
                    } else {
                        value = value * 10 + (line[i] - '0');
                    }
                }
            }
            // Save the last key-value pair
            nLines=value;
        }
    }
}

void Reader::createBinary()
{
    std::ifstream file(path+"ratings_Electronics.csv");
    std::ofstream outfile(path+"ratings_Electronics.bin", std::ios::binary);

    std::string line;
    int lineCounter = 0;
    int offsetCounter = 0;

    while (std::getline(file, line)) {
        offsetCounter = line.size();
        if(offsetCounter < mediumLineSize){
            for(int j = offsetCounter; j < mediumLineSize - 1; j++){
                line.push_back('*');
            }
            offsetCounter = 0;
            line.push_back('\n');
        }
        else{
            offsetMap[lineCounter] = offsetCounter - mediumLineSize +1;
            offsetCounter = 0;
            line.push_back('\n');
        }
        outfile << line;
        lineCounter++;
    }
    char hashtag = '#';
    outfile << hashtag;
    for(auto& [line, offset] : offsetMap)
    {
        std::string lineString = std::to_string(line);
        std::string offsetString = std::to_string(offset);

        outfile << lineString << "!" << offsetString << "?";
    }
    outfile << hashtag;

    std::string lineCounterString = std::to_string(lineCounter);
    outfile << lineCounterString ;

    file.close();
    outfile.close();
}