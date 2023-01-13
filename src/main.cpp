/* #include "../include/func.h"
#include "../include/sort.h"
#include "../include/hash.h"
#include "../include/huffman.h" */
#include "../include/ArvoreVP.h"

void menuArvores();

void menu()
{
    int input=-1;

    std::cout<<"OPTIONS:\n";
    std::cout<<"1 - Gerar Arvores \n";
    std::cout<<"\n2 - Comprimir \n";
    std::cout<<"\n\nPress 0 to quit\n";
    while (input != 1 && input != 2 && input != 0)
        std::cin>>input;
  switch (input)
  {
  case 1:
    menuArvores();
    break;
  case 2:
    //preHash();
    break;
  case 0:
    return;
  }

  menu();
}

void menuArvores()
{
    int input=-1;

    std::cout<<"OPTIONS:\n";
    std::cout<<"1 - Arvore Vermelho-Preto \n";
    std::cout<<"\n2 - Arvore B \n";
    std::cout<<"\n\nPress 0 to quit\n";
    while (input != 1 && input != 2 && input != 0)
        std::cin>>input;
  switch (input)
  {
  case 1:
    //preSort();
    break;
  case 2:
    //preArvoreB();
    break;
  case 0:
    return;
  }

  menu();
}


int main(int argc, char **argv)
{
  std::string id;
  int size;
  std::cin>>size;
  ArvoreVP arvoreb;
  std::vector<std::string> inserir = {"A" , "A-BE-CE" , "A-TOA" , "AB" , "ABA" , "ABACATE" , "ABACATEIRO" , "ABACAXI" , "ABACO" , "ABADE" , "ABADESSA" , "ABADIA" , "ABAFA" , "ABAFADO" , "ABAFAMENTO" , "ABAFAR" , "ABAFO" , "ABAIANADO" , "ABAIXADO" , "ABAIXAR" , "ABAIXAR-SE" , "ABAIXO" , "ABAIXO-ASSINADO" , "ABAJUR" , "ABALADO" , "ABALAMENTO" , "ABALAR" , "ABALAVEL" , "ABALO" , "ABALROAMENTO" , "ABALROAR" , "ABANADOR" , "ABANAR" , "ABANDONADO" , "ABANDONAR" , "ABANDONO" , "ABANO" , "ABARCAR" , "ABARROTADO" , "ABARROTAMENTO" , "ABARROTAR" , "ABASTADO" , "ABASTANCA" , "ABASTAR" , "ABASTECEDOR" , "ABASTECER" , "ABASTECIDO" , "ABASTECIMENTO" , "ABATE" , "ABATEDOURO" , "ABATER" , "ABATER-SE" , "ABATIDO" , "ABATIMENTO" , "ABAULADO" , "ABAULAMENTO" , "ABAULAR" , "ABDICACAO" , "ABDICAR" , "ABDICAVEL" , "ABDOME" , "ABDOMEN" , "ABDOMINAL" , "ABECEDARIO" , "ABELHA" , "ABELHUDO" , "ABELIANO" , "ABENCOAR" , "ABERRACAO" , "ABERTA" , "ABERTO" , "ABERTURA" , "ABESTALHADO" , "ABESTALHAR-SE" , "ABETO" , "ABILOLADO" , "ABILOLAR" , "ABISCOITAR" , "ABISMADO" , "ABISMAR" , "ABISMO" , "ABISSAL" , "ABISSINIO" , "ABJETO" , "ABLACAO" , "ABLATIVO" , "ABLAUT" , "ABLUCAO" , "ABNEGACAO" , "ABNEGADO" , "ABNEGAR" , "ABOBADA" , "ABOBADADO" , "ABOBADAR" , "ABOBADO" , "ABOBAR" , "ABOBORA" , "ABOBORAL" , "ABOBOREIRA" , "ABOBRINHA" , "ABOCANHAR" , "ABOLETAR-SE" , "ABOLICAO" , "ABOLICIONISMO" , "ABOLICIONISTA" , "ABOLIR" , "ABOMINACAO" , "ABOMINAR" , "ABOMINAVEL" , "ABONACAO" , "ABONADO" , "ABONAR" , "ABONO" , "ABORDAGEM" , "ABORDAR" , "ABORDAVEL" , "ABORIGINE" , "ABORRECER" , "ABORRECIMENTO" , "ABORTAR" , "ABORTO" , "ABOTOAR" , "ABRACADABRA" , "ABRACAR" , "ABRACO" , "ABRANDAMENTO" , "ABRANDAR" , "ABRANGENCIA" , "ABRANGENTE" , "ABRANGER" , "ABRASADOR" , "ABRASILEIRADO" , "ABRASILEIRAR" , "ABRASIVO" , "ABRE-ALAS" , "ABREUGRAFIA" , "ABREUGRAFICO" , "ABREVIACAO" , "ABREVIADO" , "ABREVIAMENTO" , "ABREVIAR" , "ABREVIATURA" , "ABRICO" , "ABRICOTEIRO" , "ABRIDOR" , "ABRIGAR" , "ABRIGAR-SE" , "ABRIGO" , "ABRIL" , "ABRILHANTAR" , "ABRIR" , "ABRUPTO" , "ABRUTALHADO" , "ABRUTALHAR" , "ABSCESSO" , "ABSCISSA" , "ABSENTEISMO" , "ABSENTEISTA" , "ABSENTIA" , "ABSINTO" , "ABSOLUTA" , "ABSOLUTAMENTE" , "ABSOLUTISMO" , "ABSOLUTISTA" , "ABSOLUTO" , "ABSOLVER" , "ABSOLVICAO" , "ABSORCAO" , "ABSORTO" , "ABSORVE" , "ABSORVENTE" , "ABSORVER" , "ABSTEMIO" , "ABSTENCAO" , "ABSTER" , "ABSTINENCIA" , "ABSTRACAO" , "ABSTRACIONISMO" , "ABSTRACIONISTA" , "ABSTRATA" , "ABSTRATO" , "ABSURDO" , "ABUNDANCIA" , "ABUNDANTE" , "ABURGUESADO" , "ABURGUESAMENTO" , "ABURGUESAR" , "ABUSADO" , "ABUSAR" , "ABUSIVO" , "ABUSO" , "ABUTRE" , "AC" , "ACABADO" , "ACABAMENTO" , "ACABAR" , "ACABAVEL" , "ACABRUNHADO" , "ACABRUNHAMENTO" , "ACABRUNHAR" , "ACACIA" , "ACADEMIA" , "ACADEMICISMO" , "ACADEMICO" , "ACADIANO" , "ACAFAJESTADO" , "ACAFAJESTAMENTO" , "ACAFAJESTAR-SE" , "ACAFRAO" , "ACAI" , "ACAJU" , "ACALCAR" , "ACALENTAR" , "ACALMADO" , "ACALMAR" , "ACALORADO" , "ACALORAR" , "ACAMADO" , "ACAMAR" , "ACAMBARCAR" , "ACAMPADO" , "ACAMPAMENTO" , "ACAMPAR" , "ACANALHADO" , "ACANALHAR" , "ACANHADO" , "ACANHAMENTO" , "ACANHAR" , "ACAO" , "ACARAJE" , "ACAREACAO" , "ACAREAR" , "ACARICIAR" , "ACARO" , "ACARPETADO" , "ACARPETAR" , "ACARRETAR" , "ACASALAMENTO" , "ACASALAR" , "ACASO" , "ACATAMENTO" , "ACATAR" , "ACATO" , "ACAUTELADO" , "ACAUTELAMENTO" , "ACAUTELAR" , "ACCESSORIOS" , "ACE" , "ACEBOLADO" , "ACEBOLAR" , "ACEDER" , "ACEFALO" , "ACEITACAO" , "ACEITAR" , "ACEITAVEL" , "ACEITO" , "ACELARACAO" , "ACELERACAO" , "ACELERADO" , "ACELERADOR" , "ACELERAR" , "ACELGA" , "ACEM" , "ACENAR" , "ACENDEDOR" , "ACENDER" , "ACENO" , "ACENTO" , "ACENTUACAO" , "ACENTUADO" , "ACENTUAR" , "ACEPCAO" , "ACEPIPE" , "ACERBAR" , "ACERCA" , "ACERCAR" , "ACEROLA" , "ACERTADO" , "ACERTAR" , "ACERTO" , "ACESO" , "ACESSADO" , "ACESSAR" , "ACESSIBILIDADE" , "ACESSIVEL" , "ACESSO" , "ACESSORIO" , "ACESSORIOS" , "ACETALDEIDO" , "ACETATO" , "ACETICO" , "ACETILCOLINA" , "ACETILENO" , "ACETILSALICILICO" , "ACETINADO" , "ACETINAR" , "ACETONA" , "ACHA" , "ACHADICO" , "ACHADO" , "ACHAR" , "ACHAR-SE" , "ACHATADO" , "ACHATAMENTO" , "ACHATAR" , "ACHAVA" , "ACHINCALHAMENTO" , "ACHINCALHANTE" , "ACHINCALHAR" , "ACHINCALHE" , "ACHOCOLATADO" , "ACIDA" , "ACIDENTADO" , "ACIDENTAL" , "ACIDENTAR" , "ACIDENTE" , "ACIDENTES" , "ACIDEZ" , "ACIDO" , "ACIDO-BASICO" , "ACIMA" , "ACINTE" , "ACINTOSO" , "ACINZENTADO" , "ACINZENTAR" , "ACIONADO" , "ACIONADOR" , "ACIONAMENTO" , "ACIONAR" , "ACIONARIO" , "ACIONISTA" , "ACIRRADO" , "ACIRRAMENTO" , "ACIRRAR" , "ACLAMACAO" , "ACLAMAR" , "ACLARADO" , "ACLARAMENTO" , "ACLARAR" , "ACLIMATACAO" , "ACLIMATADO" , "ACLIMATAR" , "ACLIVE" , "ACNE" , "ACO" , "ACOBERTADO" , "ACOBERTAR" , "ACOCORADO" , "ACOCORAR" , "ACOITAR" , "ACOITE" , "ACOLA" , "ACOLCHOADO" , "ACOLCHOAR" , "ACOLHEDOR" , "ACOLHER" , "ACOLHIDA" , "ACOLHIDO" , "ACOLHIMENTO" , "ACOMETER" , "ACOMODACAO" , "ACOMODADO" , "ACOMODAR" , "ACOMPANHA" , "ACOMPANHAMENTO" , "ACOMPANHAMENTOS" , "ACOMPANHANTE" , "ACOMPANHAR" , "ACONCHEGANTE" , "ACONCHEGAR" , "ACONCHEGO" , "ACONDICIONADO" , "ACONDICIONAR" , "ACONSELHA" , "ACONSELHADO" , "ACONSELHAMENTO" , "ACONSELHAR" , "ACONSELHAVEL" , "ACONTECER" , "ACONTECIDO" , "ACONTECIMENTO" , "ACONTECIMENTOS" , "ACOPLADO" , "ACOPLAGEM" , "ACOPLAMENTO" , "ACOPLAR" , "ACORDADO" , "ACORDAR" , "ACORDE" , "ACORDEAO" , "ACORDEOM" , "ACORDEONISTA" , "ACORDO" , "ACORIANO" , "ACORRENTADO" , "ACORRENTAR" , "ACORRER" , "ACOSSADO" , "ACOSSAR" , "ACOSTAMENTO" , "ACOSTAR" , "ACOSTUMADO" , "ACOSTUMAR" , "ACOTOVELAMENTO" , "ACOTOVELAR" , "ACOUGUE" , "ACOVARDADO" , "ACOVARDAR" , "ACRE" , "ACRE-DOCE" , "ACREDITADO" , "ACREDITAR" , "ACREDITAVEL" , "ACRESCENTAR" , "ACRESCER" , "ACRESCIMO" , "ACRIANO" , "ACRIDEZ" , "ACRILICO" , "ACRIMONIA" , "ACRIMONIOSO" , "ACROBACIA" , "ACROBATA" , "ACROBATICO" , "ACROFOBIA" , "ACROMATICO" , "ACRONIMO" , "ACROPOLE" , "ACROSTICO" , "ACTINIDEO" , "ACTINIO" , "ACTINOMICETE" , "ACUADO" , "ACUAR" , "ACUCAR" , "ACUCARADO" , "ACUCARAR" , "ACUCAREIRO" , "ACUCENA" , "ACUDE" , "ACUDIR" , "ACUIDADE" , "ACULTURACAO" , "ACULTURADO" , "ACULTURAR" , "ACUMULACAO" , "ACUMULADO" , "ACUMULADOR" , "ACUMULAR" , "ACUMULO" , "ACUPUNTURA" , "ACUSACAO" , "ACUSADO" , "ACUSAR" , "ACUSATIVO" , "ACUSTICA" , "ARITMETICO" , "ARLEQUIM" , "ARMA" , "ARMACAO" , "ARMADA" , "ARMADAS" , "ARMADILHA" , "ARMADO" , "ARMADOR" , "ARMADURA" , "ARMAGEDON" , "ARMAMENTISMO" , "ARMAMENTISTA" , "ARMAMENTO" , "ARMAMENTOS" , "ARMAR" , "ARMARINHO" , "ARMARIO" , "ARMAS" , "ARMAZEM" , "ARMAZENADO" , "ARMAZENAGEM" , "ARMAZENAMENTO" , "ARMAZENAR" , "ARMENIO" , "ARMINHO" , "ARMISTICIO" , "ARO" , "AROEIRA" , "AROMA" , "AROMATERAPIA" , "AROMATICO" , "AROMATIZACAO" , "AROMATIZADO" , "AROMATIZANTE" , "AROMATIZAR" , "ARPAO" , "ARPEJO" , "ARPOAR" , "ARQUEADO" , "ARQUEAMENTO" , "ARQUEAR" , "ARQUEIRO" , "ARQUEJANTE" , "ARQUEJAR" , "ARQUEJO" , "ARQUEOLOGIA" , "ARQUEOLOGICO" , "ARQUEOLOGO" , "ARQUEOPTERIX" , "ARQUETIPICO" , "ARQUETIPO" , "ARQUIBANCADA" , "ARQUIDIOCESANO" , "ARQUIDIOCESE" , "ARQUIDUCADO" , "ARQUIDUCAL" , "ARQUIDUQUE" , "ARQUIDUQUESA" , "ARQUIINIMIGO" , "ARQUIMEDIANO" , "ARQUIPELAGO" , "ARQUITETAR" , "ARQUITETO" , "ARQUITETONICO" , "ARQUITETURA" , "ARQUITETURAL" , "ARQUIVAMENT" , "ARQUIVAMENTO" , "ARQUIVAR" , "ARQUIVISTA" , "ARQUIVO" , "ARRABALDE" , "ARRAIA" , "ARRAIAL" , "ARRAIGADO" , "ARRAIGAR" , "ARRANCA-RABO" , "ARRANCA-TOCO" , "ARRANCADA" , "ARRANCADO" , "ARRANCAR" , "ARRANHA-CEU" , "ARRANHADO" , "ARRANHADURA" , "ARRANHAO" , "ARRANHAR" , "ARRANJADO" , "ARRANJAR" , "ARRANJO" , "ARRANQUE" , "ARRASADO" , "ARRASADOR" , "ARRASAMENTO" , "ARRASANTE" , "ARRASAR" , "ARRASTA-PE" , "ARRASTADO" , "ARRASTAO" , "ARRASTAR" , "ARRAZOADO" , "ARRAZOAMENTO" , "ARRAZOAR" , "ARRE" , "ARREBANHAR" , "ARREBATADO" , "ARREBATAMENTO" , "ARREBATAR" , "ARREBENTACAO" , "ARREBENTADO" , "ARREBENTAR" , "ARREBITADO" , "ARREBITAR" , "ARREBITE" , "ARRECADACAO" , "ARRECADAR" , "ARRECIFE" , "ARREDAR" , "ARREDAVEL" , "ARREDONDADO" , "ARREDONDAMENTO" , "ARREDONDAR" , "ARREDOR" , "ARREDORES" , "ARREFECER" , "ARREFECIMENTO" , "ARREGACAR" , "ARREGALADO" , "ARREGALAR" , "ARREGANHADO" , "ARREGANHAR" , "ARREMATAR" , "ARREMATE" , "ARREMESSAR" , "ARREMESSO" , "ARREMETER" , "ARREMETIDA" , "ARRENDADO" , "ARRENDAR" , "ARREPENDER-SE" , "ARREPENDIDO" , "ARREPENDIMENTO" , "ARREPIADO" , "ARREPIANTE" , "ARREPIAR" , "ARREPIO" , "ARRETADO" , "ARREVESADO" , "ARREVESAMENTO" , "ARREVESAR" , "ARRIADO" , "ARRIAR" , "ARRIMO" , "ARRISCADO" , "ARRISCAR" , "ARRISCAR-SE" , "ARRITMIA" , "ARRITMICO" , "ARROBA" , "ARROCHADO" , "ARROCHAR" , "ARROCHO" , "ARROGANCIA" , "ARROGANTE" , "ARROIO" , "ARROJADO" , "ARROJAMENTO" , "ARROJAR" , "ARROJAR-SE" , "ARROJO" , "ARROLAMENTO" , "ARROLAR" , "ARROMBA" , "ARROMBADOR" , "ARROMBAMENTO" , "ARROMBAR" , "ARROTAR" , "ARROTO" , "ARROUBO" , "ARROZ" , "ARROZ-DE-CARRETEIRO" , "ARROZ-DE-FESTA" , "ARROZ-DOCE" , "ARROZAL" , "ARRUACA" , "ARRUACEIRO" , "ARRUDA" , "ARRUELA" , "ARRUINADO" , "ARRUINAR" , "ARRULHAR" , "ARRULHO" , "ARRUMACAO" , "ARRUMADEIRA" , "ARRUMAR" , "ARSENAL" , "ARSENICO" , "ARSENIO" , "ART" , "ARTE" , "ARTE-FINAL" , "ARTEFATO" , "ARTEIRO" , "ARTELHO" , "ARTEMISIA" , "ARTERIA" , "ARTERIAL" , "ARTERIOSCLEROSE" , "ARTES" , "ARTESANAL" , "ARTESANATO" , "ARTESAO" , "ARTESIANO" , "ARTICO" , "ARTICULACAO" , "ARTICULADA" , "ARTICULADO" , "ARTICULADOR" , "ARTICULAR" , "ARTICULISTA" , "ARTIFICE" , "ARTIFICIAL" , "ARTIFICIO" , "ARTIGO" , "ARTILHARIA" , "ARTILHEIRO" , "ARTIMANHA" , "ARTISTA" , "ARTISTICA" , "ARTISTICAS" , "ARTISTICO" , "ARTRITE" , "ARTROPODE" , "ARTURIANO" , "ARUAQUE" , "ARVORE" , "ARVOREDO" , "ARVORES" , "AS" , "ASA" , "ASA-DELTA" , "ASBESTO" , "ASCENDENCIA" , "ASCENDENTE" , "ASCENDER" , "ASCENSAO" , "ASCENSORISTA" , "ASCETA" , "ASCETICO" , "ASCII" , "ASCO" , "ASCORBICO" , "ASFALTAR" , "ASFALTO" , "ASFIXIA" , "ASFIXIANTE" , "ASFIXIAR" , "ASIATICO" , "ASIATICOS" , "ASILADO" , "ASILAR" , "ASILO" , "ASMA" , "ASMATICO" , "ASNEIRA" , "ASNO" , "ASPARGO" , "ASPARTAME" , "ASPAS" , "ASPECTO" , "ASPEREZA" , "ASPERGIMENTO" , "ASPERGIR" , "ASPERO" , "ASPIRACAO" , "ASPIRADOR" , "ASPIRANTE" , "ASPIRAR" , "ASPIRINA" , "ASQUEROSO" , "ASSADEIRA" , "ASSADO" , "ASSALARIADO" , "ASSALARIAR" , "ASSALTANTE" , "ASSALTAR" , "ASSALTO" , "ASSANHAMENTO" , "ASSANHAR" , "ASSAR" , "ASSASSINAR" , "ASSASSINATO" , "ASSASSINIO" , "ASSASSINO" , "ASSAZ" , "ASSEADO" , "ASSEAR" , "ASSECLA" , "ASSEDIAR" , "ASSEDIO" , "ASSEGURADO" , "ASSEGURAR" , "ASSEIO" , "ASSEMBLEIA" , "ASSEMBLER" , "ASSEMELHAR" , "ASSENTADO" , "ASSENTAMENTO" , "ASSENTAR" , "ASSENTO" , "ASSEPSIA" , "ASSEPTICO" , "ASSERTIVO" , "ASSESSOR" , "ASSESSORAMENTO" , "ASSESSORAR" , "ASSESSORIA" , "ASSEVERAR" , "ASSEXUADO" , "ASSEXUAL" , "ASSIDUIDADE" , "ASSIDUO" , "ASSIM" , "ASSIMETRIA" , "ASSIMETRICO" , "ASSIMILACAO" , "ASSIMILAR" , "ASSIMILAVEL" , "ASSIMPTOTA" , "ASSIMPTOTICO" , "ASSINADO" , "ASSINALACAO" , "ASSINALADO" , "ASSINALAMENTO" , "ASSINALAR" , "ASSINANTE" , "ASSINAR" , "ASSINATURA" , "ASSINCRONO" , "ASSINDETICO" , "ASSINDETO" , "ASSIRIO" , "ASSIRIOLOGIA" , "ASSISTENCIA" , "ASSISTENCIAL" , "ASSISTENTE" , "ASSISTIR" , "ASSOALHO" , "ASSOAR" , "ASSOBERBADO" , "ASSOBERBAMENTO" , "ASSOBERBAR" , "ASSOBIAR" , "ASSOBIO" , "ASSOCIACAO" , "ASSOCIADO" , "ASSOCIAR" , "ASSOCIATIVIDADE" , "ASSOCIATIVO" , "ASSOLAR" , "ASSOMBRACAO" , "ASSOMBRADO" , "ASSOMBRAMENTO" , "ASSOMBRAR" , "ASSOMBRO" , "ASSOMBROSO" , "ASSOMPAR" , "ASSOPRAR" , "ASSOPRO" , "ASSUMIDO" , "ASSUMIR" , "ASSUNCAO" , "ASSUNTAR" , "ASSUNTO" , "ASSUNTOS" , "ASSUSTADICO" , "ASSUSTADO" , "ASSUSTADOR" , "ASSUSTAR" , "ASTATINIO" , "ASTECA" , "ASTERISCO" , "ASTEROIDAL" , "ASTEROIDE" , "ASTIGMATA" , "ASTIGMATICO" , "ASTIGMATISMO" , "ASTRAL" , "ASTRO" , "ASTROFISICA" , "ASTROFISICO" , "ASTROLABIO" , "ASTROLOGIA" , "ASTROLOGICO" , "ASTROLOGO" , "ASTRONAUTA" , "ASTRONAUTICA" , "ASTRONAUTICO" , "ASTRONAVE" , "ASTRONOMIA" , "ASTRONOMICA" , "ASTRONOMICO" , "ASTRONOMICOS" , "ASTRONOMO" , "ASTUCIA" , "ASTUCIOSO" , "ASTUTO" , "AT" , "ATA" , "ATABALHOADO" , "ATABALHOAMENTO" , "ATABALHOAR" , "ATABAQUE" , "ATACADISTA" , "ATACADO" , "ATACANTE" , "ATACAR" , "ATACAVEL" , "ATACHE" , "ATADAS" , "ATADO" , "ATADURA" , "ATALHAR" , "ATALHO" , "ATAPETADO" , "ATAPETAR" , "ATAQUE" , "ATAR" , "ATARANTADO" , "ATARANTAR" , "ATARDAR" , "ATAREFADO" , "ATAREFAMENTO" , "ATAREFAR" , "ATARRACADO" , "ATAUDE" , "ATAVIADO" , "ATAVIAR" , "ATAZANAR" , "ATE" , "ATEAR" , "ATEISMO" , "ATEISTA" , "ATELIE" , "ATELIER" , "ATEMORIZANTE" , "ATEMORIZAR" , "ATEMPORAL" , "ATENCAO" , "ATENCIOSO" , "ATENDENTE" , "ATENDER" , "ATENDIMENTO" , "ATENEU" , "ATENTADO" , "ATENTAR" , "ATENTO" , "ATENUACAO" , "ATENUADO" , "ATENUANTE" , "ATENUAR" , "ATER" , "ATERRADO" , "ATERRADOR" , "ATERRAR" , "ATERRISSAGEM" , "ATERRISSAR" , "ATERRO" , "ATERRORIZADO" , "ATERRORIZANTE" , "ATERRORIZAR" , "ATESTACAO" , "ATESTADO" , "ATESTAR" , "ATEU" , "ATICAR" , "ATIMO" , "ATINADO" , "ATINAR" , "ATINGIDO" , "ATINGIR" , "ATINGIVEL" , "ATIPICO" , "ATIRADEIRA" , "ATIRAR" , "ATITUDE" , "ATIVA" , "ATIVACAO" , "ATIVADO" , "ATIVAR" , "ATIVIDADE" , "ATIVIDADES" , "ATIVISMO" , "ATIVISTA" , "ATIVO" , "ATLANTICO" , "ATLAS" , "ATLETA" , "ATLETICA" , "ATLETICANO" , "ATLETICO" , "ATLETISMO" , "ATMOSFERA" , "ATMOSFERICA" , "ATMOSFERICO" , "ATO" , "ATOL" , "ATOLADO" , "ATOLAR" , "ATOLAR-SE" , "ATOMICA" , "ATOMICO" , "ATOMO" , "ATONA" , "ATONAL" , "ATONALIDADE" , "ATONITO" , "ATONO" , "ATOR" , "ATORDOADO" , "ATORDOAMENTO" , "ATORDOANTE" , "ATORDOAR" , "ATORMENTADO" , "ATORMENTAR" , "ATRACACAO" , "ATRACADOURO" , "ATRACAO" , "ATRACAR" , "ATRAENTE" , "ATRAICOADO" , "ATRAICOAR" , "ATRAIR" , "ATRAPALHACAO" , "ATRAPALHADO" , "ATRAPALHAR" , "ATRAS" , "ATRASADO" , "ATRASAR" , "ATRASO" , "ATRATIVO" , "ATRATIVOS" , "ATRAVANCA-LO" , "ATRAVANCAMENTO" , "ATRAVANCAR" , "ATRAVES" , "ATRAVESSADO" , "ATRAVESSADOR" , "ATRAVESSAR" , "ATRELAR"}; 
  

 // {"100","200","300","150","190","380","350","125"}; 
  //for(int i=0;i<inserir.size();i++){
    
    //std::cout<<"Inserindo: "<<inserir[i]<<"\n";
   // arvoreb.insere(inserir[i]);
    //arvoreb.print();
  //}
  
  while(id!="0"){
    arvoreb.print();
    std::cout<<"insert: ";
    std::cin>>id;
    std::cout<<"\n";
    ProductReview* prod = new ProductReview(id + ", , , ");
    arvoreb.insere(prod);
    
  }
    arvoreb.print();
    std::cout<<"seg: ";
    std::string str = "1" , str2 = "1" ;  
    ProductReview* prodtest = arvoreb.busca(str , str2);
    std::cout<<"ter: ";
    std::cout<<"\n user: " << prodtest->getUserId() << "  prod: " << prodtest->getProductId()<<"\n";
    std::cout<<"quar: ";
  
  
  
  
    /* std::string path;
    if(argc>1)
    {
        std::string pa(argv[1]);
        path = pa;
    }
    else path="../files/";

    std::cout << "Caminho do arquivo especificado:"<<path<<"\n";

    
    std::cout<<"\n|====== STARTING PRE PROCESSING ======|\n\n";

    std::cout<<"\n"<<"Quantas reviews devem ser analizadas?"<<"\n";
    std::cin>>nReviews;
    

    // Tempo para geração do arquivo binário
    double timeForCreateBinary;
    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();

    createBinary2(path,nReviews);
    nReviews = getSize();

    std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    timeForCreateBinary=std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count();

    
    std::cout<<"\n|====== PRE PROCESSING FINISHED ======|\n\n";
    std::cout << "Tempo para gerar o arquivo binário: " << timeForCreateBinary << "\n\n";

    //GET REVIEW
   
    double i=0;

    std::cout<<"\n"<<"Insira o indice da review desejada:"<<"\n";
    std::cin>>i;
    while(i>=0)
    {
        if(i>=nReviews){std::cout<<"Nao existem reviews com esse indice\n";std::cin>>i;continue;}
        getReview(i);
        std::cout<<"\n"<<"Insira o indice da review desejada:"<<"\n";
        std::cin>>i;
    }  */
    
    
    //IMPORT
    
    /* double n=0;
    ProductReview* rreviews;

    std::cout<<"\n\nPegador de reviews aleatorias\nQuantas reviews voce quer pegar?\n";
    std::cin>>n;
    std::cout<<"n: "<<n<<"\n";
    rreviews=import(n);

    std::cout<<"\n Resultados:\n";
    for(int j=0;j<n;j++)
    {
        rreviews[j].print();
    }  */
   

    menu();
    
    /*std::string text;

    std::cout << "Digite o texto a ser comprimido: ";
    std::getline(std::cin,text);

    std::string compressao;
    std::string descompressao;

    std::cout << "Palavra: " << text << "\n";
    huffman::huffmanTree *tree = huffman::makeHuffmanTree(text);

    compressao = huffman::compress(text, tree);

    std::cout << "Arquivo comprimido como: " << compressao << "\n";

    descompressao = huffman::decompress(compressao, tree);

    std::cout << "==========================\n";
    std::cout << "Código: " << compressao << "\n";
    std::cout << "Mensagem descomprimida: " << descompressao << "\n";
 */
    return 0;
}
    
