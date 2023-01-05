#include "../include/huffman.h"

namespace Node {
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
    int minHeap::generateHeapSize(int *table) {
        int size = 0;
        for(int i=0; i<ASCII; i++) {
            if(table[i]!=0)
                size++;
        }
        return size;
    }

    void minHeap::trocar(int index, int small) {
        Node::node *n;
        n = this->vet[index];
        this->vet[index] = this->vet[small];
        this->vet[small] = n;
    }

    minHeap::minHeap(int *table) {
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

    int minHeap::getSize() {
        return this->heapSize;
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
    huffmanTree::~huffmanTree() { }

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


    // ======================ALGORITMOS DO NAMESPACE==========================


    void saveHuffmanTree_frequencyTable(int *table) {
        std::ofstream eraser(path+"huffman.bin");
        eraser.close(); // Limpar conteúdo de huffman.bin
        std::ofstream file(path+"huffman.bin");
        
        if(file) {
            for(int i=0; i<ASCII; i++) {
                if(table[i]>0) {
                    file.write(reinterpret_cast<const char*>(&i),1);
                    file.write(reinterpret_cast<const char*>(&table[i]),1);
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

    void splitText(std::string line, int *table) {
        int i=0;
        std::string index = "";
        std::string frequency = "";

        for(i=0; line[i]!=':';i++) {
            index += line[i];
        }
        for(i++; line[i]!='\0';i++) {
            frequency += line[i];
        }

        table[stoi(index)] = stoi(frequency);
    }

    void descompress() {
        // Parte 1:
        // Gerando a árvore de huffman a partir do arquivo huffman.txt
        std::ifstream file(path+"huffman.txt");
        int table[ASCII] = {0};
        std::string line;

        while(file.good()) {
            getline(file,line);
            splitText(line,table);
        }
        file.close();

        heap::minHeap *priority_queue = new heap::minHeap(table);
        huffmanTree *tree = new huffmanTree(priority_queue);
    }
}