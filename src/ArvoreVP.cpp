#include "../include/ArvoreVP.h"
#include <stack>
#include <algorithm>
// construtor
ArvoreVP::ArvoreVP() {
    vazio = new NoVP(); 
    vazio->setCor(COR::BLACK); // Define a cor de "vazio" para BLACK
    raiz = vazio; // Define a raiz da árvore como "vazio"
}
// destrutor
ArvoreVP::~ArvoreVP() {
    // desalocar memoria
}
void ArvoreVP::LeftRotate(NoVP* novp) {
    NoVP* aux = novp->getRight();  //ponteiro "aux" para o filho direito do nó recebido
    novp->setRight(aux->getLeft()); //Define o filho direito do nó recebido para ser o filho esquerdo de "aux"
    if (aux->getLeft() != vazio) { // Se o filho esquerdo de "aux" não for um ponteiro nulo, define o pai desse nó para ser o nó recebido
        aux->getLeft()->setPai(novp);
    }
    aux->setPai(novp->getPai()); // Define o pai de "aux" para ser o pai do nó recebido
    if (novp->getPai() == vazio) { // Se o pai do nó recebido for um ponteiro nulo, define a raiz da árvore como "aux"
        raiz = aux;
    } else if (novp == novp->getPai()->getLeft()) { // Caso contrário, se o nó recebido for um filho esquerdo, define o filho esquerdo do pai do nó recebido como "aux"
        novp->getPai()->setLeft(aux); 
    } else {  // caso contrário, define o filho direito como "aux"
        novp->getPai()->setRight(aux);
    }
    aux->setLeft(novp); // Define o filho esquerdo de "aux" para ser o nó recebido
    novp->setPai(aux);  // Define o pai do nó recebido como "aux"
}

void ArvoreVP::RightRotate(NoVP* novp) {
    NoVP* aux = novp->getLeft(); // ponteiro "aux" e para o filho esquerdo do nó recebido
    novp->setLeft(aux->getRight());  // Define o filho esquerdo do nó recebido para ser o filho direito de "aux"
    if (aux->getRight() != vazio) { // Se o filho direito de "aux" não for um ponteiro nulo, define o pai desse nó para ser o nó recebido
        aux->getRight()->setPai(novp);
    }
    aux->setPai(novp->getPai()); // Define o pai de "aux" para ser o pai do nó recebido
    if (novp->getPai() == vazio) { // Se o pai do nó recebido for um ponteiro nulo, defina a raiz da árvore como "aux"
        raiz = aux;
    } else if (novp == novp->getPai()->getRight()) { //Caso contrário, se o nó recebido for um filho direito, define o filho direito do pai do nó recebido como "aux"
        novp->getPai()->setRight(aux);
    } else {  //caso contrário, define o filho esquerdo como "aux".
        novp->getPai()->setLeft(aux);
    }
    aux->setRight(novp); // Define o filho direito de "aux" para ser o nó recebido
    novp->setPai(aux); // Define o pai do nó recebido como "aux"
}

void ArvoreVP::Balanceamento_Insere(NoVP*& novp) {
    NoVP* tio;
    while (novp != raiz && novp->getPai()->getCor() == COR::RED) {
        if (novp->getPai() == novp->getPai()->getPai()->getLeft()) {
            tio = novp->getPai()->getPai()->getRight();
            if (tio->getCor() == COR::RED) {
                novp->getPai()->setCor(COR::BLACK);
                tio->setCor(COR::BLACK);
                novp->getPai()->getPai()->setCor(COR::RED);
                novp = novp->getPai()->getPai();
            } else {
                if (novp == novp->getPai()->getRight()) {
                    novp = novp->getPai();
                    LeftRotate(novp);
                }
                novp->getPai()->setCor(COR::BLACK);
                novp->getPai()->getPai()->setCor(COR::RED);
                RightRotate(novp->getPai()->getPai());
            }
        } else {
            tio = novp->getPai()->getPai()->getLeft();
            if (tio->getCor() == COR::RED) {
                novp->getPai()->setCor(COR::BLACK);
                tio->setCor(COR::BLACK);
                novp->getPai()->getPai()->setCor(COR::RED);
                novp = novp->getPai()->getPai();
            } else {
                if (novp == novp->getPai()->getLeft()) {
                    novp = novp->getPai();
                    RightRotate(novp);
                }
                novp->getPai()->setCor(COR::BLACK);
                novp->getPai()->getPai()->setCor(COR::RED);
                LeftRotate(novp->getPai()->getPai());
            }
        }
    }
    raiz->setCor(COR::BLACK);
}


void ArvoreVP::insere(ProductReview* pr) {
    std::string valorid2 = pr->getUserId()+pr->getProductId(); //string para concatenar o userId e o productId do ProductReview
    valorid2.erase(std::remove_if(valorid2.begin(), valorid2.end(), ' '), valorid2.end()); //remove todos os espaços em branco
    NoVP* new_novp = new NoVP(valorid2, COR::RED, pr); // nó com o valorid2 sendo ele o id, de cor RED e um ponteiro para o objeto ProductReview recebido
    NoVP* novp_x = raiz; // Define o nó novp_x para a raiz da árvore
    NoVP* novp_y = vazio; // Define um ponteiro novp_y como nulo, para ser o nó anterior
    while (novp_x != vazio) { // cria um Loop até que o nó novp_x seja um ponteiro nulo
        novp_y = novp_x; // Define o novp_y para o nó novp_x
        if (new_novp->getId() < novp_x->getId()) { // Verifica se o id do novo nó (new_novp) é menor que o id do nó novp_x
            novp_x = novp_x->getLeft(); //caso seja, vai pra esquerda
        } else { //se não ele vai pra direita
            novp_x = novp_x->getRight(); 
        }
    }
    new_novp->setPai(novp_y); // Define o pai do novo nó (new_novp) como o nó novp_y
    if (novp_y == vazio) { // Se o nó novp_y for nulo, define a raiz da árvore como o novo nó (new_novp)
        raiz = new_novp;
    } else if (new_novp->getId() < novp_y->getId()) { // Verifica se o id do novo nó é menor que o id do nodo novp_y
        novp_y->setLeft(new_novp); // caso seja, ele define o filho esquerdo do nó novp_y para ser o novo nó (new_novp)
    } else {
        novp_y->setRight(new_novp); //se n ele, define o filho direito do nó novp_y para ser o novo nó (new_novp), pois seu id é maior
    }
    //Define os filhos esquerdo e direito do novo nó como nulos (vazio)
    new_novp->setLeft(vazio);
    new_novp->setRight(vazio);
    
    //Chama a função balanceamento para manter as propriedades da árvore VP
    Balanceamento_Insere(new_novp);
}


ProductReview* ArvoreVP::busca(std::string userId,std::string productId) {
    ProductReview* Prod; // ponteiro para ProductReview definido como nulo
    std::string valorid = userId + productId; //Concatena o userId e o productId
    valorid.erase(std::remove_if(valorid.begin(), valorid.end(), ' '), valorid.end()); //remove espaços em branco da string
    NoVP* novp = raiz; // Define o nó novp para a raiz da árvore
    while (novp != vazio) { //Enquanto o nó novp não for um ponteiro nulo
        if (novp->getId() == valorid) { // Se o id do nó novp for igual ao valorid
            Prod = new ProductReview(novp->getBase()); //faz uma copia do ponteiro ProductReview contido no novp 
            return Prod;
        } else if (valorid < novp->getId()) { //se o valorid for menor que o id do nó novp vai pra esquerda
            novp = novp->getLeft(); 
        } else { //se for maior vai para a direita 
            novp = novp->getRight(); 
        }
    }
    return nullptr; //retorna nulo caso não encontre o valorid na arvore 
}

void ArvoreVP::print() {
    In_Ordem(raiz); //chama função In_Ordem
}
void ArvoreVP::In_Ordem(NoVP* no_imprime) {
    if (no_imprime != vazio) { // Se o nó recebido não for nulo
        In_Ordem(no_imprime->getLeft()); // Chama recursivamente a função In_Ordem para o filho esquerdo do nó recebido
        std::cout << no_imprime->getId() << std::endl; // Imprime o id do nó recebido
        In_Ordem(no_imprime->getRight()); // Chama recursivamente a função In_Ordem para o filho direito do nó recebido
    }
}
