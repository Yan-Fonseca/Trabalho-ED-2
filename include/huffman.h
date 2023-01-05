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
            node(char character, int frequency);
            node(int frequency, Node::node *left, Node::node *right);
            ~node();

            char getCharacter();
            int getFrequency();
            node* getLeft();
            node* getRight();
    };
}


namespace heap {
    const int ASCII = 256;
    
    class minHeap {
        private:
            Node::node **vet;
            int heapSize;

            int generateHeapSize(int *table);
            void trocar(int index, int small);
        public:
            minHeap(int *table);
            ~minHeap() { }

            Node::node* getMinimum();
            Node::node** getVet();
            int getSize();
            void minHeapify(int index);
            Node::node* extractMin();
            void heapDecrease(int index);
            void insert(Node::node *n);
    };
}


namespace huffman {
    const int ASCII = 256;

    class huffmanTree {
        private:
            Node::node *root;
            int height;
            heap::minHeap *heap_vet;

            int treeHeight(Node::node* n);
            void generateDictionaryAux(std::string *dict, Node::node *n, std::string path);
        public:
            huffmanTree(heap::minHeap *priority_queue);
            ~huffmanTree();

            Node::node* getRoot();
            int getHeight();
            void print(Node::node* n);
            std::string* generateDictionary();
            heap::minHeap *getPriorityQueue();
    };


    void saveHuffmanTree_frequencyTable(int *table);
    huffmanTree *loadHuffmanTree_file();

    // Função responsável por criar a tabela de frequências dos caracteres na string
    void createFrequencyTable(std::string str, int *table);
    std::string *encode(std::string *dict, std::string text);

    std::string compress(std::string str, huffmanTree* tree);
    std::string decompress(std::string cipher, huffmanTree *tree);

    huffmanTree* makeHuffmanTree(std::string str);

    // Irá comprimir o conteúdo do arquivo reviewsOrig.txt
    void compress();
    void descompress();
}

#endif