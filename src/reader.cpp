#include "../include/Reader.h"

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
    
    line = line + "$";
    line.append(std::to_string(position)) ;

    infile.close();

    //std::cout<<"pos:"<<position<<" os:"<<offset<<"\n";

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

 ProductReview* Reader::import(int n)
{
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
    
    for(int i=0;i<n;i++)
    {
        srand(i*time(0));
        rnd=rand()% nLines;
        if(HashList::insertInHash(table, rnd)) {
            std::string info = getReview(rnd);
            b[i].setData(info);
        } else {
            i--;
        }

        // Lógica para utilizar a chave: Um usuário, teoricamente, não vai avaliar o mesmo produto duas vezes
        // Portanto, julgamos ser suficiente que a chave para a função do hash seja uma combinação do id do
        // usuário e o id do produto.
        //key = b[i].getProductId() + b[i].getUserId();

        // A função de inserir na tabela retorna true se a chave foi inserida na tabela.
        // Caso retorne falso, significa que o ProductReview já foi importado e, portanto, o valor de i é
        // decrementado e o loop inicia novamente.
        //if(!HashList::insertInHash(table, key))
        //    i--;
        
    }
    
    return b;
} 