#include "../include/reader.h"

Reader::Reader(std::string& p,int m_size)
    {path=p;
    mediumLineSize=m_size;

    std::ifstream test(path+"ratings_Electronics.bin");

    if(test.good()){

        std::cout<<"Binario ja existe\n\n";
        test.close();

        readBinary();
    }
    else{
        std::cout<<"Binario nao encontrado\n\nCriando Binario...";
        createBinary(path);
        std::cout<<"Criação concluida\n";
    }

}

void Reader::setPath(std::string& p) {path = p;}
std::string Reader::getPath() {return path;}

void Reader::setOffsetMap(std::unordered_map<int, int>& o) {offsetMap = o;}
std::unordered_map<int, int> Reader::getOffsetMap() {return offsetMap;}

int Reader::getnLines(){return nLines;}

//printa o que esta presente na lineNumber ° linha do arquivo binário
void Reader::getReview(int lineNumber)
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
    
    line = line + "$";
    line.append(std::to_string(position)) ;

    infile.close();

    //std::cout<<"pos:"<<position<<" os:"<<offset<<"\n";

    ProductReview* pr = new ProductReview(line);

    pr->print();
}

//Retorna ua string que possui os conteusdos da lineNumber ° linha do arquivo binário
std::string Reader::getReviewString(int lineNumber)
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
    
    line = line + "$";
    line.append(std::to_string(position)) ;

    infile.close();

    //std::cout<<"pos:"<<position<<" os:"<<offset<<"\n";

    return line;
}

//usa o arquivo binário salvo na memória e retorna a lineNumber ° reviews presente nele
std::string Reader::getBinReview(int lineNumber)
{
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
    char *p = bin_data + position;
    while (*p != '\n' && p < bin_data + bin_size) {
        line += *p++;
    }
    line = line + "$";
    line.append(std::to_string(position));
    return line;
}

//Lê o arquivo binário e constroi o offsetMap
void Reader::readBinary() {

    std::ifstream file(path+"ratings_Electronics.bin", std::ios::binary);

    std::string line;

    while (std::getline(file, line)) {
        if (line[0] == '#') {
            int key = 0;
            int value = 0;
            bool readingKey = true;
            for (unsigned int i = 1; i < line.length(); i++) {
                if (line[i] == '!') {
                    // Troca entre ler chave para ler valor
                    readingKey = false;
                } else if (line[i] == '?') {
                    // Sava o par e reseta 
                    offsetMap[key] = value;
                    key = 0;
                    value = 0;
                    readingKey = true;
                } else if (line[i] == '#') {
                    offsetMap[key] = value;
                    readingKey = false;
                } else {
                    if (readingKey) {
                        key = key * 10 + (line[i] - '0');
                    } else {
                        value = value * 10 + (line[i] - '0');
                    }
                }
            }
            nLines=value;
        }
    }
}

//Le o arquivo csv, e o armazena em binário, assim como salva as informações do offsetMap no fi do arquivo 
void Reader::createBinary(std::string path)
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

//Recebe um inteiro n e retorna um vetro de ProductReviews contendo n elementos aleatórios não repetidos
 ProductReview* Reader::import(int n)
{
    bool save = false;
    if(n>10000){
        saveFile();
        save= true;
    }

    // É criada uma tabela Hash para armazenar os os dados gerados aleatoriamente
    // Optou-se por utilizar uma lista de listas encadeadas.
    HashList::List table[HashList::getTAM()]; 
    // TAM é o número primo 7919, um número suficientemente grande
    // para comportar os dados.

    // A tabela inicia todas as suas posições com um ponteiro para um nó encadeado.
    HashList::initializeTable(table);

    int rnd=0;
    std::string key; // Chave para ser usada no hash.

    ProductReview *b = new ProductReview[n];
    if(save)
        for(int i=0;i<n;i++)
        {
            srand(i*time(0));
            rnd=rand()% nLines;
            if(HashList::insertInHash(table, rnd)) {
                std::string info = getBinReview(rnd);
                b[i].setData(info);
            } else {
                i--;
            }
            
        }
    else
        for(int i=0;i<n;i++)
        {
            srand(i*time(0));
            rnd=rand()% nLines;
            if(HashList::insertInHash(table, rnd)) {
                std::string info = getReviewString(rnd);
                b[i].setData(info);
            } else {
                i--;
            }
            
        }

    return b;
} 

//Salva o arquivo binário na memória
void Reader::saveFile()
{
    std::ifstream file(path+"ratings_Electronics.bin", std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file " + path + "ratings_Electronics.bin");
    }
    // Get the size of the file
    file.seekg(0, file.end);  
    int size = file.tellg();
    file.seekg(0, file.beg);

    // Allocate memory to store the contents of the file
    bin_data = new char[size];

    bin_size = size;

    // Read the entire contents of the file into memory
    file.read(bin_data, size);
    file.close();
}