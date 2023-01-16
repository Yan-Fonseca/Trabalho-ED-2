#include "../include/huffman.h"
#include <iostream>
#include <string>

namespace Node{
    node::node(char character, int frequency) {
        this->left = nullptr;
        this->right = nullptr;
        this->character = character;
        this->frequency = frequency;
    }

    node::node(int frequency, Node::node *left, Node::node *right) {
        this->left = left;
        this->right = right;
        this->frequency = frequency;
    }

    node::~node() { }

    char node::getCharacter() {
        return this->character;
    }

    int node::getFrequency() {
        return this->frequency;
    }

    node* node::getLeft() {
        return this->left;
    }

    node* node::getRight() {
        return this->right;
    }
}


namespace heap {
    void minHeap::generateSize(int *table) {
        int size = 0;
        for(int i=0; i<ASCII; i++) {
            if(table[i]!=0)
                size++;
        }
        this->size = size;
    }

    void minHeap::trocar(int index, int small) {
        Node::node *n;
        n = this->vet[index];
        this->vet[index] = this->vet[small];
        this->vet[small] = n;
    }

    minHeap::minHeap(int *table) {
        generateSize(table);
        this->vet = new Node::node*[ASCII];
        this->heapSize = 0;
        Node::node *aux;
        for(int i=0; i<ASCII; i++) {
            if(table[i]>0) {
                aux = new Node::node(i,table[i]);
                insert(aux);
            }
        }
    }
    minHeap::~minHeap() { }

    Node::node* minHeap::getMinimum() {
        return this->vet[0];
    }

    Node::node** minHeap::getVet() {
        return this->vet;
    }

    int minHeap::getHeapSize() {
        return this->heapSize;
    }

    int minHeap::getSize() {
        return this->size;
    }

    void minHeap::minHeapify(int index) {
        index++;
        int small;
        int left = 2*index - 1;
        int right = 2*index;

        if(left < this->heapSize && this->vet[left]->getFrequency() < this->vet[index-1]->getFrequency()) 
            small = left;
        else
            small = index-1;
        
        if(right < this->heapSize && this->vet[right]->getFrequency() < this->vet[small]->getFrequency()) 
            small = left;
        
        if(small!=index-1) {
            trocar(index-1,small);
            minHeapify(small);
        }
    }

    Node::node* minHeap::extractMin() {
        if(this->heapSize>=1) {
            Node::node* small = this->vet[0];
            this->vet[0] = this->vet[this->heapSize - 1];
            this->heapSize = this->heapSize - 1;
            minHeapify(0);

            return small;
        }

        std::cout << "Erro ao extrair elemento da Heap: Heap sem elementos!\n";
        return nullptr;
    }

    void minHeap::heapDecrease(int index) {
        if(this->vet[index]!=nullptr) {
            while(index>0 && this->vet[index/2]->getFrequency() > this->vet[index]->getFrequency()) {
                trocar(index/2, index);
                index = index/2;
            }
        }
        else
            std::cout << "Erro! índice inválido!\n";
    }
    void minHeap::insert(Node::node *n) {
        this->heapSize++;
        this->vet[this->heapSize - 1] = n;
        heapDecrease(this->heapSize - 1);
    }
}

namespace huffman {
    int huffmanTree::treeHeight(Node::node* n) {
        int left;
        int right;

        if(n == nullptr)
            return -1;
        else {
            left = treeHeight(n->getLeft()) + 1;
            right = treeHeight(n->getRight()) + 1;

            if(right>left)
                return right;
            else
                return left;
        }
    }

    void huffmanTree::generateDictionaryAux(std::string *dict, Node::node *n, std::string path) {
        std::string left;
        std::string right;

        if(n->getLeft()==nullptr && n->getRight()==nullptr) {
            dict[n->getCharacter()] = path; // Pode ocorrer erro aqui!
        }                    
        else {
            left = path;
            right = path;

            left += "0";
            right += "1";

            generateDictionaryAux(dict, n->getLeft(), left);
            generateDictionaryAux(dict, n->getRight(), right);
        }
    }

    huffmanTree::huffmanTree(heap::minHeap *priority_queue) {
        this->heap_vet = priority_queue;
        int n = priority_queue->getHeapSize();
        Node::node *left;
        Node::node *right;
        int frequency;

        for(int i=0; i<n-1; i++) {
            left = priority_queue->extractMin();
            right = priority_queue->extractMin();
            frequency = left->getFrequency() + right->getFrequency();

            Node::node *no = new Node::node(frequency,left,right);
            priority_queue->insert(no);
        }

        this->root = priority_queue->extractMin();
        this->height = this->treeHeight(this->root);
    }

    void huffmanTree::deleteTree(Node::node* n) {
        if(n != nullptr) {
            deleteTree(n->getLeft());
            deleteTree(n->getRight());
            delete n;
        }
    }

    huffmanTree::~huffmanTree() {
        //Node::node *n = this->getRoot();
        //deleteTree(n);
    }

    Node::node* huffmanTree::getRoot() {
        return this->root;
    }

    int huffmanTree::getHeight() {
        return this->height;
    }

    void huffmanTree::print(Node::node* n) {
        if(n!=nullptr) {
            if(n->getRight()==nullptr && n->getLeft()==nullptr)
                std::cout << n->getCharacter() << ": " << n->getFrequency() << "\n";
            else {
                print(n->getLeft());
                print(n->getRight());
            }
        }
    }

    std::string* huffmanTree::generateDictionary() {
        std::string* dict = new std::string[ASCII];
        std::string path = "";
        generateDictionaryAux(dict, this->root, path);

        return dict;
    }
    heap::minHeap* huffmanTree::getPriorityQueue() {
        return this->heap_vet;
    }

    // FUNÇÕES DE MANIPULAÇÃO E COMPRESSÃO GERAIS DE HUFFMAN:
    
    // Função responsável por criar a tabela de frequências dos caracteres na string
    void Operator::createFrequencyTable(std::string str, int *table) {
        int i=0;
        while(str[i]!='\0') {
            table[str[i]]++;
            i++;
        }
    }

    // Função responsável por construir a árvore de Huffman em todos os casos
    huffmanTree* Operator::makeHuffmanTree(std::string str) {
        int frequencyTable[ASCII] = {0};
        createFrequencyTable(str, frequencyTable);
        heap::minHeap *priority_queue = new heap::minHeap(frequencyTable);

        /* std::cout << "---------------------------------------\n";
        std::cout << "Fila de prioridade minima:\n"; 
        for(int i=0; i<priority_queue->getHeapSize(); i++) {
            std::cout << priority_queue->getVet()[i]->getCharacter() << ": " << priority_queue->getVet()[i]->getFrequency() << "\n";
        }
         std::cout << "---------------------------------------\n";*/

        huffmanTree *tree = new huffmanTree(priority_queue);

        /*std::cout << "Arvore de Huffman:\n"; 
        tree->print(tree->getRoot());*/

        return tree;
    }


    // Função responsável por codificar a string usando o dicionário
    std::string* Operator::encode(std::string *dict, std::string text) {
        std::string *code = new std::string;
        *code = "";
        for(int i=0; text[i]!='\0'; i++) {
            *code += dict[text[i]];
        }
        return code;
    }

    std::string Operator::encodeFrequencyTable(int *table) {
        std::string encodedTable = "";
        char aux;
        
        for(int i=0; i<ASCII; i++) {
            if(table[i]>0) {
                aux = i;
                encodedTable += "|";
                encodedTable += aux;
                encodedTable += std::to_string(table[i]);
            }
        }

        //std::cout << encodedTable << std::endl;

        return encodedTable;
    }

    std::string Operator::compressStr(std::string text) {
        int table[ASCII] = {0};
        createFrequencyTable(text, table);

        huffmanTree *tree = makeHuffmanTree(text);
        std::string *dict = tree->generateDictionary();
        std::string *code = encode(dict, text);

        std::string tableEncoded = encodeFrequencyTable(table);

        std::string finalString = "";

        finalString += *code;
        finalString += "&";
        finalString += tableEncoded;

        //std::cout << finalString << "\n";

        return finalString;
    }

    // Função de descompressão/decodificação usada para o arquivo binário
    std::string Operator::decompress(std::string cipher, huffmanTree *tree, int final_bits) {
        Node::node *no = tree->getRoot();
        int i=0;
        std::string text = "";
        int size = cipher.size();

        while(i < size - final_bits && cipher[i]!='\0') {
            if(cipher[i]=='0')
                no = no->getLeft();
            else if(cipher[i]=='1')
                no = no->getRight();
            else {
                std::cout << "[ERRO] Código não binário!\n";
                exit(0);
            }
            
            if(no->getLeft()==nullptr && no->getRight()==nullptr) {
                text += no->getCharacter();
                no = tree->getRoot();
            }

            i++;
        }

        return text;
    }

    std::string Operator::decompressStr(std::string code) {
        int i=0;
        std::string cipher = "";
        int table[ASCII] = {0};

        while(code[i]!='&') {
            cipher += code[i];
            i++;
        }
        i++;

        char index;
        std::string aux = "";

        while (code[i]!='\0')
        {
            if(code[i]=='|') {
                aux = "";
                i++;
                index = code[i];
                i++;
            }
            aux += code[i];
            if(code[i+1]=='|' || code[i+1]=='\0') {
                table[index] = atoi(aux.c_str());
            }
            i++;
        }
        
        heap::minHeap *priority_queue = new heap::minHeap(table);
        huffmanTree *tree = new huffmanTree(priority_queue);

        std::string text = decompress(cipher, tree, 0);

        return text;
    }


    // Compressão utilizada pela função de compressão do arquivo
    std::string Operator::compress(std::string str, huffmanTree* tree) {
        std::string *dictionary = tree->generateDictionary();

        /*std::cout << "---------------------------------------\n";
        std::cout << "Dicionário de códigos para cada caractere:\n";
        for(int i=0; i<ASCII; i++) {
            if(dictionary[i].length()!=0)
                std::cout << i << ": " << dictionary[i] << "\n";
        }
        std::cout << "---------------------------------------\n";*/

        std::string *cipher = encode(dictionary, str);

        return *cipher;
    }


    // Irá comprimir o conteúdo do arquivo reviewsOrig.txt
    void Operator::compress() {
        std::string path = getReader()->getPath();
        std::ifstream textFile(path+"reviewsOrig.txt",std::ios::in);
        std::string text;
        std::string code;
        getline(textFile,text);
        textFile.close();

        huffmanTree *tree = makeHuffmanTree(text);
        code = compress(text,tree);

        int size_of_table = tree->getPriorityQueue()->getSize();

        std::ofstream eraser(path+"reviewsComp.bin",std::ios::out | std::ios::binary); 
        eraser.close(); //apaga o conteudo do arquivo
        std::ofstream binary(path+"reviewsComp.bin",std::ios::binary | std::ios::out | std::ios::app);
        int i=0;
        int shift = 7;

        int table[ASCII] = {0}; 
        createFrequencyTable(text,table);

        unsigned char byte = 0;
        unsigned char mask;

        if(binary) {
            for(int i=0; i<ASCII; i++) {
                if(table[i]>0) {
                    //std::cout << i << ": " << table[i] << "\n";
                    binary.write(reinterpret_cast<const char*>(&i),1);
                    binary.write(reinterpret_cast<const char*>(&table[i]),sizeof(int));
                }
            }
            i = 0;
            binary.write(reinterpret_cast<const char*>(&i),1);
            while(code[i]!='\0') {
                mask = 1;

                // a variável mask é responsável por fazer os deslocamentos binários dados pelo shift
                // e aplicá-los na variável byte. Funciona da seguinte forma: Quando um char é lido o 
                // algoritmo verifica se é 1 ou 0. Caso seja 1, o valor 0000 0001 da máscara é deslocado 
                // para a posição em que o valor 1 estaria no byte atual e é aplicado na variável byte,
                // caso seja 0, somente o shift será mudado(nesse caso, decrementado).  
                if(code[i]=='1') {
                    mask <<= shift;
                    byte |= mask;
                }

                shift--;

                // Cada vez que shift fica menor que 0 significa que um byte foi completado, bastando agora 
                // armazená-lo no arquivo compactado.
                if(shift<0) {
                    binary.write(reinterpret_cast<const char*>(&byte),1);
                    byte = 0;
                    shift = 7;
                }
                i++;
            }

            // Se o último byte do código gerado de huffman for "incompleto", preencher o resto da cadeia
            // e armazenar o byte final.
            if(shift!=7) {
                binary.write(reinterpret_cast<const char*>(&byte),1);
            }
        }

        shift = shift-7;
        binary.write(reinterpret_cast<const char*>(&shift),1);

        binary.close();
    }


    // Verificar se um determinado bit de um byte é 0 ou 1
    int Operator::bit(char byte, int shift) {
        int mask = 1;
        byte >>= shift;
        return byte & mask;
    }


    // Função responsável por pegar os bytes codificados e transformá-los em uma string
    std::string Operator::decode(std::string text) {
        std::string cipher = "";
        int textSize = text.size()-1;
        char byte;
        int index = 0, shift;
        int size = text[textSize];

        while(index < textSize) {
            shift=7;
            while (shift>=0) {
                if(bit(text[index],shift)) {
                    cipher += "1";
                }
                else {
                    cipher += "0";
                }
                shift--;
            }
            index++;
        }

        return cipher;
    }


    // função responsável por decodificar o último byte do binário (o qual contém a quantidade de bits utilizáveis no penúltimo byte do arquivo)
    int Operator::getFinalBits(std::string text) {
        int byte = 0;
        int mask = 1;
        int aux;
        std::string number = "";
        number += text[text.size()-4];
        number += text[text.size()-3];
        number += text[text.size()-2];
        number += text[text.size()-1];

        for(int i=0; i<4; i++) {
            if(number[i]=='1') {
                aux = mask << 3 - i;
                byte |= aux;
            }
        }

        return byte;
    }


    // Função geral para descomprimir o arquivo
    void Operator::descompress() {
        // Parte 1:
        // Fazendo a leitura da árvore de huffman.
        std::string path = this->getReader()->getPath();
        int table[ASCII] = {0};
        char i;
        int j=0;
        int final_bits;

        std::ifstream file_cipher(path+"reviewsComp.bin", std::ios::in | std::ios::binary);

        if(file_cipher.is_open()) {
            file_cipher.seekg(0,file_cipher.beg);
            do {
                file_cipher.read(reinterpret_cast<char*>(&i), 1);
                if(i==0)
                    break;
                file_cipher.read(reinterpret_cast<char*>(&table[i]),sizeof(int));
            } while(i!=0);
        }
        else {
            std::cout << "Ocorreu um erro na abertura do arquivo binário!\n";
            exit(1);
        }

        // Parte 2:
        // Gerando a árvore de huffman
        heap::minHeap *priority_queue = new heap::minHeap(table);
        huffmanTree *tree = new huffmanTree(priority_queue);
        Node::node *n = tree->getRoot();


        // Parte 3:
        // Lendo o arquivo e transformando o código em binário para string.
        char byte;
        int shift;
        std::string text = "";
        std::string cipher = "";

        if(file_cipher) {
            while(file_cipher.good()) {
                file_cipher.read(&byte,1);
                cipher += byte;
            }
        }

        cipher = decode(cipher);
        final_bits = getFinalBits(cipher);
        text = decompress(cipher,tree,final_bits);

        // Parte 4:
        // Salvando resultado da descompressão no arquivo reviewsDesc.txt
        std::ofstream eraser(path+"reviewsDesc.txt", std::ios::out);
        eraser.close(); // Limpar arquivo
        std::ofstream descompressed(path+"reviewsDesc.txt", std::ios::out);

        descompressed << text;
        descompressed.close();

        
    }

    float Operator::compressionTax(std::string text, std::string code) {
        float sizeText = text.size();
        float sizeCode = code.size()/8;

        return (sizeText - sizeCode)/sizeText;
    }

    void Operator::performanceMetrics(int n, int m) {
        std::string path = this->getReader()->getPath();
        std::ofstream eraser(path + "saida.txt", std::ios::out);
        eraser.close();
        std::ofstream saida(path + "saida.txt", std::ios::app);

        saida << "Taxas de compressão do Huffman: \n";
        saida << "Quantidade de registros a serem analisados: " << n << "\n";

        std::string text = "";
        std::string code;
        float compression[m];
        float media=0;

        ProductReview *vet;

        int table[ASCII] = {0};
        heap::minHeap *priority_queue;
        huffmanTree *tree;

        for(int i=0; i<m; i++) {
            vet = this->getReader()->import(n);
            for(int j=0; j<n; j++) {
                text += vet[j].getUserId();
                text += vet[j].getProductId();
                text += vet[j].getRating();
                text += vet[j].getTime();
            }

            createFrequencyTable(text, table);
            priority_queue = new heap::minHeap(table);
            tree = new huffmanTree(priority_queue);
            code = compress(text,tree);

            compression[i] = compressionTax(text,code);

            saida << "Taxa de compressão [" << i << "]: " << compression[i] << "\n";

            text = "";
            code = "";
            for(int f=0; f<ASCII; f++) {
                table[f] = 0;
            }
        }

        for(int i=0; i<m; i++) {
            media += compression[i];
        }
        media = media / m;

        saida << "Média de compressão para " << m << " execuções: " << media << "\n";

        saida.close();
    }
}