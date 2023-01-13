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
    NoVP* aux = novp->getRight();  //ponteiro auxiliar para o filho direito do nó recebido
    novp->setRight(aux->getLeft()); //Define o filho direito do nó recebido para ser o filho esquerdo de auxiliar
    if (aux->getLeft() != vazio) { // Se o filho esquerdo de auxiliar não for um ponteiro nulo, define o pai desse nó para ser o nó recebido
        aux->getLeft()->setPai(novp);
    }
    aux->setPai(novp->getPai()); // Define o pai de auxiliar para ser o pai do nó recebido
    if (novp->getPai() == vazio) { // Se o pai do nó recebido for um ponteiro nulo, define a raiz da árvore como auxiliar
        raiz = aux;
    } else if (novp == novp->getPai()->getLeft()) { // Caso contrário, se o nó recebido for um filho esquerdo, define o filho esquerdo do pai do nó recebido como auxiliar
        novp->getPai()->setLeft(aux); 
    } else {  // caso contrário, define o filho direito como auxiliar
        novp->getPai()->setRight(aux);
    }
    aux->setLeft(novp); // Define o filho esquerdo de auxiliar para ser o nó recebido
    novp->setPai(aux);  // Define o pai do nó recebido como auxiliar
}

void ArvoreVP::RightRotate(NoVP* novp) {
    NoVP* aux = novp->getLeft(); // ponteiro auxiliar e para o filho esquerdo do nó recebido
    novp->setLeft(aux->getRight());  // Define o filho esquerdo do nó recebido para ser o filho direito de auxiliar
    if (aux->getRight() != vazio) { // Se o filho direito de auxiliar não for um ponteiro nulo, define o pai desse nó para ser o nó recebido
        aux->getRight()->setPai(novp);
    }
    aux->setPai(novp->getPai()); // Define o pai de auxiliar para ser o pai do nó recebido
    if (novp->getPai() == vazio) { // Se o pai do nó recebido for um ponteiro nulo, defina a raiz da árvore como auxiliar
        raiz = aux;
    } else if (novp == novp->getPai()->getRight()) { //Caso contrário, se o nó recebido for um filho direito, define o filho direito do pai do nó recebido como auxiliar
        novp->getPai()->setRight(aux);
    } else {  //caso contrário, define o filho esquerdo como auxiliar.
        novp->getPai()->setLeft(aux);
    }
    aux->setRight(novp); // Define o filho direito de auxiliar para ser o nó recebido
    novp->setPai(aux); // Define o pai do nó recebido como auxiliar
}

void ArvoreVP::Balanceamento_Insere(NoVP*& novp) {
    NoVP* tio;
    while (novp != raiz && novp->getPai()->getCor() == COR::RED) { // verifica se o novp não é a raiz e se seu pai é vermelho
        if (novp->getPai() == novp->getPai()->getPai()->getLeft()) {//verifica se o pai do novp é um filho esquerdo 
            tio = novp->getPai()->getPai()->getRight(); // atribui o filho direito do avô como tio
            if (tio->getCor() == COR::RED) { //se tio é vermelho
                novp->getPai()->setCor(COR::BLACK); // colore o pai de preto
                tio->setCor(COR::BLACK); // colore o tio de preto
                novp->getPai()->getPai()->setCor(COR::RED);// colore o avô de vermelho
                novp = novp->getPai()->getPai(); //move o novp para o avô
            } else {
                if (novp == novp->getPai()->getRight()) { //se o tio é preto e o novp é o filho direito
                    novp = novp->getPai(); // move o novp para o pai
                    LeftRotate(novp); // realiza rotação à esquerda passando o novp 
                }
                //se o novp for filho esquerdo do pai
                novp->getPai()->setCor(COR::BLACK); //colore o pai de preto
                novp->getPai()->getPai()->setCor(COR::RED); //colore o avô de vermelho
                RightRotate(novp->getPai()->getPai()); //realiza rotação à direita passando o avô de novp
            }
        } else { //se o pai do novp é um filho direito
            tio = novp->getPai()->getPai()->getLeft(); //filho esquerdo do avô é o novo tio
            if (tio->getCor() == COR::RED) { //se tio é vermelho
                novp->getPai()->setCor(COR::BLACK); //colore o pai de preto
                tio->setCor(COR::BLACK); //colore o tio de vermelho
                novp->getPai()->getPai()->setCor(COR::RED); // colore o avô de vermelho
                novp = novp->getPai()->getPai(); // move o novp para o avô
            } else {
                if (novp == novp->getPai()->getLeft()) { //se o novp for filho esquerdo do pai
                    novp = novp->getPai(); // move o novp para o pai
                    RightRotate(novp); // realiza rotação à direita passando o novp 
                }
                
                novp->getPai()->setCor(COR::BLACK);//colore o pai de preto
                novp->getPai()->getPai()->setCor(COR::RED);// colore o avô de vermelho
                LeftRotate(novp->getPai()->getPai()); //realiza rotação à esquerda passando o avô de novp
            }
        }
    }
    raiz->setCor(COR::BLACK);
}


void ArvoreVP::insere(ProductReview* pr) {
    std::string valorid2 = pr->getUserId()+pr->getProductId(); //string para concatenar o userId e o productId do ProductReview
    valorid2.erase(std::remove_if(valorid2.begin(), valorid2.end(), ' '), valorid2.end()); //remove todos os espaços em branco
    NoVP* new_novp = new NoVP(valorid2, COR::RED, pr); // nó com o valorid2 sendo ele o id, de cor RED e um ponteiro para o objeto ProductReview recebido
    NoVP* novp = raiz; // Define o nó novp para a raiz da árvore
    NoVP* anterior = vazio; // Define um ponteiro anterior como nulo
    while (novp != vazio) { // cria um Loop até que o nó novp seja um ponteiro nulo
        anterior = novp; // Define o anterior para o nó novp
        if (new_novp->getId() < novp->getId()) { // Verifica se o id do novo nó (new_novp) é menor que o id do nó novp
            novp = novp->getLeft(); //caso seja, vai pra esquerda
        } else { //se não ele vai pra direita, pois o id dele é maior
            novp = novp->getRight(); 
        }
    }
    new_novp->setPai(anterior); // Define o pai do novo nó (new_novp) como o nó anterior
    if (anterior == vazio) { // Se o nó anterior for nulo, define a raiz da árvore como o novo nó (new_novp)
        raiz = new_novp;
    } else if (new_novp->getId() < anterior->getId()) { // Verifica se o id do novo nó é menor que o id do nó anterior
        anterior->setLeft(new_novp); // caso seja, ele define o filho esquerdo do nó anterior para ser o novo nó (new_novp)
    } else {
        anterior->setRight(new_novp); //se n ele, define o filho direito do nó anterior para ser o novo nó (new_novp), pois seu id é maior
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
