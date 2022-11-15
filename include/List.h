#include "iostream"

namespace List {
    #ifndef LIST
    #define LIST
    
    class Node
    {
    private:
        std::string key;
        Node* prox;
    public:
        Node(std::string key)
        {
            this->key = key;
            this->prox = NULL;
        }
        ~Node();
    
        std::string getkey() {return key;}
        Node* getProx() {return this->prox;}
        void setProx(Node *p) {this->prox = p;}
    };

    class List
    {
    private:
        Node *first;
        int tam;
    public:
        List() 
        {
            this->first = NULL;
            this->tam = 0;
        }
        ~List(){this->first = NULL;}
    
    bool empty()
    {
        return (this->first == NULL);
    }

    void inserirNaLista(std::string key) {
        Node* new_node = new Node(key);

        if(new_node != NULL)
        {
            new_node->setProx(this->first);
            this->first = new_node;
            this->tam++;
        }
    }

    std::string searchElement(std::string key) 
    {
        Node *tmp = this->first;

        while(tmp && tmp->getkey() != key) 
        {
            tmp = tmp->getProx();

            if (tmp) {return tmp->getkey();}
        }
        return 0;
    }

    };
    

    int hashFunction(std::string key) {
        const int p = 53;
        const int m = 7919;
        int h = 0;
        long long p_power = 1;
        for(int i=0; i<key.size(); i++) {
            h = (h + key[i]*p_power) % m;
            p_power = (p_power * p) % m;
        }

        return h;
    }

    #endif
}