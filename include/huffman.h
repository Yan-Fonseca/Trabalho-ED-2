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
        public:
            huffmanTree(heap::minHeap *priority_queue);
            ~huffmanTree();

            Node::node* getRoot();
            int getHeight();
            void print(Node::node* n);
            std::string* generateDictionary();
            heap::minHeap *getPriorityQueue();
    };

}

#endif