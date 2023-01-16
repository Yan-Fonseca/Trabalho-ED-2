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
            Operator() { this->reader = nullptr; }
            ~Operator() { }

            Reader* getReader() { return this->reader;}

            void createFrequencyTable(std::string str, int *table); //Tabela de frequência de caracteres
            huffmanTree* makeHuffmanTree(std::string str);          // Função que cria a árvore de huffman
            std::string *encode(std::string *dict, std::string text); // Codifica a mensagem usando o dicionário

            std::string encodeFrequencyTable(int *table); // Transforma a tabela de frequência em um código para ser usado na compressão da string
            std::string compressStr(std::string text); // Comprime a string dada e retorna o código
            std::string decompress(std::string cipher, huffmanTree *tree, int final_bits); // descomprimi o código isolado(somente o código codificado pela árvore de Huffman) do arquivo binário

            std::string decompressStr(std::string code); // Descomprimi string e retorna o resultado
            std::string compress(std::string str, huffmanTree* tree); // Comprime um texto passado como parâmetro. É usado pela função de compressão abaixo.
            void compress(); // Comprime o arquivo

            int bit(char byte, int shift);
            std::string decode(std::string text);
            int getFinalBits(std::string text);

            void descompress(); //descomprime o binário
            float compressionTax(std::string text, std::string code); // Função que gera as taxas de compressão
            void performanceMetrics(int n, int m); // Função que realiza as métricas de performance. 
            // n é a quantidade de registros a serem importados
            // m é a quantidade de iterações/compressões a serem testadas
    };
}

#endif