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
                        aux = new Node::node(i+1,table[i]); // Aqui pode dar Erro!!
                        insert(aux);
                    }
                }
            }

            ~minHeap() { }

            Node::node* getMinimum() {
                return this->vet[0];
            }

            int getSize() {
                return this->heapSize;
            }

            void minHeapify(int index) {
                int small;
                int left = 2*index;
                int right = 2*index + 1;
                if(left < this->heapSize && this->vet[left]->getFrequency() < this->vet[index]->getFrequency()) 
                    small = left;
                else
                    small = index;
                
                if(right < this->heapSize && this->vet[right]->getFrequency() < this->vet[small]->getFrequency()) 
                    small = left;
                
                if(small!=index) {
                    trocar(index,small);
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
        public:
            huffmanTree(heap::minHeap *priority_queue) {
                int n = priority_queue->getSize();
                for(int i=0; i<n-2; i++) {
                    Node::node *left = priority_queue->extractMin();
                    Node::node *right = priority_queue->extractMin();
                    int frequency = left->getFrequency() + right->getFrequency();

                    Node::node *no = new Node::node(frequency,left,right);
                    priority_queue->insert(no);
                }

                this->root = priority_queue->extractMin();
            }
            ~huffmanTree() { }
    };

    // Função responsável por criar a tabela de frequências dos caracteres na string
    int *createFrequencyTable(std::string str) {
        int table[ASCII] = {0};

        for(int i=0; i<str.size(); i++)
            table[str[i]]++;

        return table;
    }

    std::string compress(std::string str) {
        int *frequencyTable = createFrequencyTable(str);
        heap::minHeap *priority_queue = new heap::minHeap(frequencyTable);
    }
}

#endif