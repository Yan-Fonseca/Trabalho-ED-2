#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <string>
#include "../include/func.h"

namespace Node {
    class node {
        private:
            char character;
            int frequency;
            node *left;
            node *right;
        public:
            node(char character, int frequency) {
                this->left = nullptr;
                this->right = nullptr;
                this->character = character;
                this->frequency = frequency;
            }

            node(int frequency, Node::node *left, Node::node *right) {
                this->left = left;
                this->right = right;
                this->frequency = frequency;
            }

            ~node() { }

            char getCharacter() {
                return this->character;
            }

            int getFrequency() {
                return this->frequency;
            }

            node* getLeft() {
                return this->left;
            }

            node* getRight() {
                return this->right;
            }
    };
}


namespace heap {
    const int ASCII = 256;
    
    class minHeap {
        private:
            Node::node **vet;
            int heapSize;

            int generateHeapSize(int *table) {
                int size = 0;
                for(int i=0; i<ASCII; i++) {
                    if(table[i]!=0)
                        size++;
                }
                return size;
            }

            void trocar(int index, int small) {
                Node::node *n;
                n = this->vet[index];
                this->vet[index] = this->vet[small];
                this->vet[small] = n;
            }
        public:
            minHeap(int *table) {
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
            ~minHeap() { }

            Node::node* getMinimum() {
                return this->vet[0];
            }

            Node::node** getVet() {
                return this->vet;
            }

            int getSize() {
                return this->heapSize;
            }

            void minHeapify(int index) {
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

            Node::node* extractMin() {
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

            void heapDecrease(int index) {
                if(this->vet[index]!=nullptr) {
                    while(index>0 && this->vet[index/2]->getFrequency() > this->vet[index]->getFrequency()) {
                        trocar(index/2, index);
                        index = index/2;
                    }
                }
                else
                    std::cout << "Erro! índice inválido!\n";
            }
            void insert(Node::node *n) {
                this->heapSize++;
                this->vet[this->heapSize - 1] = n;
                heapDecrease(this->heapSize - 1);
            }
    };
}


namespace huffman {
    const int ASCII = 256;

    class huffmanTree {
        private:
            Node::node *root;
            int height;
            heap::minHeap *heap_vet;

            int treeHeight(Node::node* n) {
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

            void generateDictionaryAux(std::string *dict, Node::node *n, std::string path) {
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
        public:
            huffmanTree(heap::minHeap *priority_queue) {
                this->heap_vet = priority_queue;
                int n = priority_queue->getSize();
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
            ~huffmanTree() { }

            Node::node* getRoot() {
                return this->root;
            }

            int getHeight() {
                return this->height;
            }

            void print(Node::node* n) {
                if(n!=nullptr) {
                    if(n->getRight()==nullptr && n->getLeft()==nullptr)
                        std::cout << n->getCharacter() << ": " << n->getFrequency() << "\n";
                    else {
                        print(n->getLeft());
                        print(n->getRight());
                    }
                }
            }

            std::string* generateDictionary() {
                std::string* dict = new std::string[ASCII];
                std::string path = "";
                generateDictionaryAux(dict, this->root, path);

                return dict;
            }
            heap::minHeap *getPriorityQueue() {
                return this->heap_vet;
            }
    };


    // ======================ALGORITMOS DO NAMESPACE==========================


    void saveHuffmanTree_frequencyTable(int *table) {
        std::ofstream eraser(path+"huffman.bin",std::ios::out | std::ios::binary);
        eraser.close(); // Limpar conteúdo de huffman.bin
        std::ofstream file(path+"huffman.bin",std::ios::out | std::ios::binary);
        
        if(file) {
            for(int i=0; i<ASCII; i++) {
                if(table[i]>0) {
                    file.write(reinterpret_cast<const char*>(&i),sizeof(unsigned char));
                    file.write(reinterpret_cast<const char*>(&table[i]),sizeof(int));
                }
            }
        }
        file.close();
    }

    // Função responsável por criar a tabela de frequências dos caracteres na string
    void createFrequencyTable(std::string str, int *table) {
        int i=0;
        while(str[i]!='\0') {
            table[str[i]]++;
            i++;
        }
    }

    std::string *encode(std::string *dict, std::string text) {
        std::string *code = new std::string;
        *code = "";
        for(int i=0; text[i]!='\0'; i++) {
            *code += dict[text[i]];
        }
        return code;
    }

    std::string compress(std::string str, huffmanTree* tree) {
        std::string *dictionary = tree->generateDictionary();

        std::cout << "---------------------------------------\n";
        std::cout << "Dicionário de códigos para cada caractere:\n";
        for(int i=0; i<ASCII; i++) {
            if(dictionary[i].length()!=0)
                std::cout << i << ": " << dictionary[i] << "\n";
        }
        std::cout << "---------------------------------------\n";

        std::string *cipher = encode(dictionary, str);

        return *cipher;
    }

    std::string decompress(std::string cipher, huffmanTree *tree) {
        Node::node *no = tree->getRoot();
        int i=0;
        std::string text = "";

        while(cipher[i]!='\0') {
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

    huffmanTree* makeHuffmanTree(std::string str) {
        int frequencyTable[ASCII] = {0};
        createFrequencyTable(str, frequencyTable);
        heap::minHeap *priority_queue = new heap::minHeap(frequencyTable);

        std::cout << "---------------------------------------\n";
        std::cout << "Fila de prioridade mínima:\n";
        for(int i=0; i<priority_queue->getSize(); i++) {
            std::cout << priority_queue->getVet()[i]->getCharacter() << ": " << priority_queue->getVet()[i]->getFrequency() << "\n";
        }
        std::cout << "---------------------------------------\n";

        huffmanTree *tree = new huffmanTree(priority_queue);

        std::cout << "Árvore de Huffman:\n";
        tree->print(tree->getRoot());

        return tree;
    }

    // Irá comprimir o conteúdo do arquivo reviewsOrig.txt
    void compress() {
        //std::string path = getPath();
        std::ifstream textFile(path+"reviewsOrig.txt",std::ios::in);
        std::string text;
        std::string code;
        getline(textFile,text);
        textFile.close();

        huffmanTree *tree = makeHuffmanTree(text);
        int table[ASCII] = {0};
        createFrequencyTable(text, table);
        saveHuffmanTree_frequencyTable(table);
        code = compress(text,tree);

        std::ofstream eraser(path+"reviewsComp.bin",std::ios::in | std::ios::binary); eraser.close(); //apaga o conteudo do arquivo
        std::ofstream binary(path+"reviewsComp.bin",std::ios::in | std::ios::binary);
        int i=0;
        int shift = 7;

        unsigned char byte = 0;
        unsigned char mask;

        if(binary) {
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
                    binary.write(reinterpret_cast<const char*>(&byte),sizeof(unsigned char));
                    byte = 0;
                    shift = 7;
                }
                i++;
            }

            // Se o último byte do código gerado de huffman for "incompleto", preencher o resto da cadeia
            // com 0 e armazenar o valor.
            if(shift!=7) {
                binary.write(reinterpret_cast<const char*>(&byte),sizeof(unsigned char));
            }
        }

        binary.close();
    }

    int bit(char byte, int shift) {
        int mask = 1;
        byte >>= shift;
        return byte & mask;
    }

    void descompress() {
        // Parte 1:
        // Fazendo a leitura da árvore de huffman.
        std::ifstream file(path+"huffman.bin", std::ios::in | std::ios::binary);
        int table[ASCII] = {0};
        int i;

        if(file.is_open()) {
            file.seekg(0, file.beg);
            while(file.good()) {
                file.read(reinterpret_cast<char*>(&i), 1);
                file.read(reinterpret_cast<char*>(&table[i]),sizeof(int));
            }
        }
        else {
            std::cout << "Ocorreu um erro na abertura do arquivo binário de huffman!\n";
            exit(1);
        }
        file.close();

        // Parte 2:
        // Gerando a árvore de huffman
        heap::minHeap *priority_queue = new heap::minHeap(table);
        huffmanTree *tree = new huffmanTree(priority_queue);
        Node::node *n = tree->getRoot();

        // Parte 3:
        // descomprimindo o arquivo
        std::ifstream file_cipher(path+"reviewsComp.bin", std::ios::in | std::ios::binary);
        file_cipher.seekg(0,file_cipher.beg);
        char byte;
        int shift;
        std::string text = "";

        if(file_cipher) {
            while(file_cipher.good()) {
                shift = 7;
                file_cipher.read(&byte,sizeof(char));
                while (shift>=0)
                {
                    
                    if(bit(byte,shift)) {
                        n = n->getRight();
                    }
                    else {
                        n = n->getLeft();
                    }

                    if(n->getLeft()==nullptr && n->getRight()==nullptr) {
                        text += n->getCharacter();
                        n = tree->getRoot();
                    }

                    shift--;
                }
                
            }
        }

        // Parte 4:
        // Salvando resultado da descompressão no arquivo reviewsDesc.txt

        std::ofstream eraser(path+"reviewsDesc.txt", std::ios::out);
        eraser.close(); // Limpar arquivo
        std::ofstream descompressed(path+"reviewsDesc.txt", std::ios::out);

        descompressed << text;
    }
}

#endif