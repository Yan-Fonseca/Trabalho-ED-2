#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>

namespace heap {
    const int heapVectorSize = 256;

    class hNode {
        private:
            char value;
            int frequency;
            hNode *left;
            hNode *right;
        public:
            hNode() {
                this->left = nullptr;
                this->right = nullptr;
            }
            hNode(char key){
                this->value = key;
                this->frequency = 1;
                this->left = nullptr;
                this->right = nullptr;
            }
            ~hNode() { }

            int getFrequency() {
                return this->frequency;
            }

            char getValue() {
                return this->value;
            }

            void incrementFrequency() {
                this->frequency++;
            }
    };

    /*class Heap {
    private:
        hNode heapVector[256];
        int heapSize;
    public:
        Heap() {
            this->heapSize = 0;
            this->heapVector = new hNode[heapVectorSize];
        }
        ~Heap() {
            delete [] this->heapVector;
        }


        int getHeapSize() {
            return this->heapSize;
        }

        hNode heapMin() {
            return this->heapVector[0];
        }

        int left(int index) {
            return index*2;
        }

        int right(int index) {
            return index*2 + 1;
        }

        void trocar(int index, int small) {
            hNode aux = this->heapVector[index];
            this->heapVector[index] = this->heapVector[small];
            this->heapVector[small] = aux;
        }
        
        void minHeapify(int index) {
            int l = left(index);
            int r = right(index);
            int small;

            if(l <= this->heapSize && this->heapVector[l].getFrequency() < this->heapVector[index].getFrequency()) {
                small = l;
            }
            else {
                small = index;
            }

            if(r <= this->heapSize && this->heapVector[r].getFrequency() < this->heapVector[small].getFrequency()) {
                small = r;
            }

            if(small != index) {
                trocar(index, small);
                minHeapify(small);
            }
        }
    };*/
}

namespace huffman {
    const int ASCII = 256;

    // Função responsável por criar a tabela de frequências dos caracteres na string
    int *createFrequencyTable(std::string str) {
        int table[ASCII] = {0};

        for(int i=0; i<str.size(); i++)
            table[str[i]]++;

        return table;
    }

    std::string compress(std::string str) {
        int *frequencyTable = createFrequencyTable(str);
    }
}

#endif