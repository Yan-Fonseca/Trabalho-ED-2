# Trabalho-ED-2

## TO DO
Etapa 1: Criar TAD
- [x] void ProductReview::print(): imprime os dados de um registro do tipo ProductReview.
- [x] void createBinary(std::string& path): gera o arquivo binário correspondente ao arquivo CSV armazenado no caminho passado como parâmetro. O arquivo binário deve ser gerado no mesmo diretório do arquivo CSV.
- [x] void getReview(int i): acessa diretamente o i-ésimo registro do arquivo binário e o imprime na tela. O valor de i deve ser recebido via parâmetro. Considere i=0 como o índice do primeiro registro.
- [x] ProductReview* import(int n): importa n registros aleatórios do arquivo binário e retorna um vetor contendo esses registros.

Etapa 2: Criar os algoritmos de ordenação
- [ ] Quicksort
- [ ] Mergesort
- [ ] Indefinido

Etapa 3: Ler N registros aleatórios e contar quantas vezes um mesmo produto se repete
- [x] Armazenar os produtos em um hash
- [ ] Imprimir os produtos mais avaliados
- [x] ProductReview* createTable(int n): gera e retorna uma tabela hash contendo n registros aleatórios, utilizando o método de tratamento de colisão escolhido para a Etapa 3. A tabela retornada por esta função não deve estar ordenada.

Etapa 4: Programa principal
- [x] Ordenação
- [x] Hash