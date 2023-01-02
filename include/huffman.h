#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
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
            // Algoritmo de Huffman:
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

    void saveHuffmanTree_frequencyTable(int *table) {
        std::ofstream eraser(path+"huffman.txt");
        eraser.close(); // Limpar conteúdo de huffman.bin

        std::ofstream file(path+"huffman.txt");
        
        std::string frequency;
        std::string ascii;
        std::string line;
        
        if(file) {
            for(int i=0; i<ASCII; i++) {
                if(table[i]>0) {
                    ascii = std::to_string(i);
                    frequency = std::to_string(table[i]);
                    file << ascii << ":" << frequency << std::endl;
                }
            }
        }

        file.close();
    }

    huffmanTree *loadHuffmanTree_file() {
        std::ifstream binary(path+"huffman.bin",std::ios::in|std::ios::binary);
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
        std::string path = getPath();
        std::ifstream textFile(path+"reviewsOrig.txt");
        std::string text;
        std::string code;
        getline(textFile,text);
        textFile.close();

        huffmanTree *tree = makeHuffmanTree(text);
        int table[ASCII] = {0};
        createFrequencyTable(text, table);
        saveHuffmanTree_frequencyTable(table);
        code = compress(text,tree);

        std::ofstream eraser(path+"reviewsComp.bin"); eraser.close(); //apaga o conteudo do arquivo
        std::ofstream binary(path+"reviewsComp.bin");
        int i=0;
        int shift = 7;

        unsigned char byte = 0;
        unsigned char mask;

        if(binary) {
            while(code[i]!='\n') {
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
                    binary.write(reinterpret_cast<const char*>(byte),1);
                    byte = 0;
                    shift = 7;
                }
                i++;
            }

            // Se o último byte do código gerado de huffman for "incompleto", preencher o resto da cadeia
            // com 0 e armazenar o valor.
            if(shift!=7) {
                binary.write(reinterpret_cast<const char*>(byte),1);
            }
        }

        binary.close();
    }
}

#endif