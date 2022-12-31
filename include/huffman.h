#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>

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

            std::string* generateDictionary() {
                std::string* dict = new std::string[ASCII];
                std::string path = "";
                generateDictionaryAux(dict, this->root, path);

                return dict;
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
    };

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

    std::string compress(std::string str) {
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
}

#endif