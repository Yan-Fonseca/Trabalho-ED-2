#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <string>
#include "../include/reader.h"

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
    const int ASCII = 128;
    
    class minHeap {
        private:
            Node::node **vet;
            int heapSize;
            int size;

            void generateSize(int *table);
            void trocar(int index, int small);
        public:
            minHeap(int *table);
            ~minHeap();

            Node::node* getMinimum();
            Node::node** getVet();
            int getHeapSize();
            int getSize();
            void minHeapify(int index);
            Node::node* extractMin();
            void heapDecrease(int index);
            void insert(Node::node *n);
    };
}


namespace huffman {
    const int ASCII = 128;

    class huffmanTree {
        private:
            Node::node *root;
            int height; // Altura da árvore de huffman
            int size;
            heap::minHeap *heap_vet;

            int treeHeight(Node::node* n);
            void generateDictionaryAux(std::string *dict, Node::node *n, std::string path);
            void deleteTree(Node::node* n);
        public:
            huffmanTree(heap::minHeap *priority_queue);
            ~huffmanTree();

            Node::node* getRoot();
            int getHeight();
            void print(Node::node* n);
            std::string* generateDictionary();
            heap::minHeap *getPriorityQueue();
    };

    class Operator {
        private:
            Reader *reader;
        public:
            Operator(Reader *r) { this->reader = r; }
            ~Operator() { }

            Reader* getReader() { return this->reader;}

            void createFrequencyTable(std::string str, int *table);
            huffmanTree* makeHuffmanTree(std::string str);
            std::string *encode(std::string *dict, std::string text);

            std::string encodeFrequencyTable(int *table);
            std::string compressStr(std::string text);
            std::string decompress(std::string cipher, huffmanTree *tree, int final_bits);

            std::string decompressStr(std::string code);
            std::string compress(std::string str, huffmanTree* tree);
            void compress(); // Comprime o arquivo

            int bit(char byte, int shift);
            std::string decode(std::string text);
            int getFinalBits(std::string text);

            void descompress(); //descomprime o binário
            float compressionTax(std::string text, std::string code);
            void performanceMetrics(int n, int m);
    };
}

#endif