/* #include "../include/hash.h"
#include "../include/huffman.h"
#include "../include/preArvore.h"

void printPrompt(ProductReview *vet, int n)
{
    char imp;
    std::cout << "Imprimir (s/n): ";
    std::cin >> imp;

    if(vet == NULL)
        std::cout << "ALERTA: ponteiro nulo, nada a imprimir!" << std::endl;
    else if(imp == 's')
    {
        for(int i = 0; i < n; i++)
            vet[i].print();
    }
}

void printPrompt(ArvoreVP *arv, int n)
{
    char imp;
    std::cout << "Imprimir (s/n): ";
    std::cin >> imp;

    if(arv == NULL)
        std::cout << "ALERTA: ponteiro nulo, nada a imprimir!" << std::endl;
    else if(imp == 's')
        arv->print();
}

void printPrompt(ArvoreB *arv, int n)
{
    char imp;
    std::cout << "Imprimir (s/n): ";
    std::cin >> imp;

    if(arv == NULL)
        std::cout << "ALERTA: ponteiro nulo, nada a imprimir!" << std::endl;
    else if(imp == 's')
        arv->print();
}

ProductReview* randomTest(int n)
{
    ProductReview *vet = new ProductReview[n];

    for(int i = 0; i < n; i++)
    {
        std::string u("STR");
        u += 'a'+rand()%('z'-'a');
        //vet[i].userId = u; // ou essa linha ou a de baixo pode ser usada, dependendo de como foi implementado (a de baixo é preferencial)
        vet[i].setUserId(u);
    }

    return vet;
}

template<typename T>
void treeTest(T arv, ProductReview *vet, int n)
{
    for(int i = 0; i < n; i++)
        arv->insere(&vet[i]);
    printPrompt(vet, n);

    std::string userId, productId;
    std::cout << "Digite um par (userId, productId) para busca: ";
    std::cin >> userId >> productId;
    while(userId != "quit")
    {
        ProductReview *p = arv->busca(userId, productId);
        if(p != NULL)
            p->print();
        else
            std::cout << "Produto nao encontrado!" << std::endl;
        
        std::cout << "Digite outro par (userId, productId) para busca: ";
        std::cin >> userId >> productId;
    }
}

void compressTest(int method)
{
    switch(method)
    {
        case 0: std::cout << "=== Teste Huffman ===" << std::endl << std::endl; break;
        case 1: std::cout << "=== Teste LZ77 ===" << std::endl << std::endl; break;
        case 2: std::cout << "=== Teste LZW ===" << std::endl << std::endl; break;
        default: std::cout << "Metodo de compressao nao suportado" << std::endl << std::endl; break;
    }
    
    std::cout << "Testando strings..." << std::endl;

    std::string str = "std::string qualquer";
    std::string comp = ope->comprime(str, method);
    std::string orig = ope->descomprime(comp, method);

    std::cout << "String comprimida: " << comp << std::endl;
    std::cout << "String descomprimida: " << orig << std::endl << std::endl;

    std::cout << "Testando arquivos..." << std::endl;

    comprime(method); // essa função deve comprimir um texto qualquer armazenado em '/diretorio/contendo/arquivos/reviewsOrig.txt'
    descomprime(method); // essa função deve descomprimir um texto qualquer armazenado em '/diretorio/contendo/arquivos/reviewsComp.bin'
}

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        // OBS.: TODOS OS ARQUIVOS USADOS NO PROGRAMA (TANTO DE ENTRADA QUANTO DE SAÍDA) DEVEM ESTAR LOCALIZADOS NO DIRETÓRIO FORNECIDO
        // PELO USUÁRIO COMO ARGUMENTO DA LINHA DE COMANDO
        std::string path(argv[1]);
        Reader reader(path , 41);

        reader.createBinary(path);
        
        int registerIdx;
        std::cout << "Digite um indice de registro (-1 para sair): ";
        std::cin >> registerIdx;
        while (registerIdx != -1)
        {
            reader.getReview(registerIdx);
            std::cout << "Digite outro indice de registro (-1 para sair): ";
            std::cin >> registerIdx;
        }

        ProductReview *vet = 0;
        ArvoreVP *arv_vp = 0;
        ArvoreB *arv_b = 0;
        int option, n;
        do{
            std::cout << "[1] Vetor de teste" << std::endl 
                << "[2] Importar registros" << std::endl
                << "[3] Arvore vermelho-preto" << std::endl
                << "[4] Arvore B" << std::endl
                << "[5] Huffman" << std::endl
                << "[6] LZ77" << std::endl
                << "[7] LZW" << std::endl
                << "[0] Sair" << std::endl;

            std::cout << "Digite uma opcao de menu: ";
            std::cin >> option;
            switch (option)
            {
                case 1:
                    n = 10;
                    delete [] vet;
                    vet = randomTest(n);
                    printPrompt(vet, n);
                    break;
                case 2:
                    std::cout << "Quantos registros deseja importar? ";
                    std::cin >> n;
                    delete [] vet;
                    vet = reader.import(n);
                    printPrompt(vet, n);
                    break;
                case 3:
                    delete arv_vp;
                    arv_vp = new ArvoreVP();
                    treeTest(arv_vp, vet, n);
                    break;
                case 4:
                    delete arv_b;
                    arv_b = new ArvoreB();
                    treeTest(arv_b, vet, n);
                    break;
                case 5:
                    compressTest(0);
                    break;
                case 6:
                    compressTest(1);
                    break;
                case 7:
                    compressTest(2);
                    break;
                default:
                    break;
            }
        } while(option != 0);

        delete [] vet;
        delete arv_vp;
        delete arv_b;
    }

    return 0;
}  */