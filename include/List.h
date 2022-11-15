#include "iostream"

namespace List {
    #ifndef LIST
    #define LIST
    
    class Node
    {
    private:
        std::string valor;
        Node* prox;
    public:
        Node(std::string valor)
        {
            this->valor = valor;
            this->prox = NULL;
        }
        ~Node();
    
        std::string getValor() {return valor;}
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

    void inserirNaLista(std::string value) {
        Node* new_node = new Node(value);

        if(empty())
        {
            new_node->setProx(this->first);
            this->first = new_node;
            this->tam++;
        }
    }

    std::string searchElement(std::string value) 
    {
        Node *tmp = this->first;

        while(tmp && tmp->getValor() != value) 
        {
            tmp = tmp->getProx();

            if (tmp) {return tmp->getValor();}
        }
        return 0;
    }

    };
    

    #endif
}