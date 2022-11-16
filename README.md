Para o projeto, utilizamos o CMake para facilitar o processo de compilação nos 
diferentes Sistemas Operacionais que utilizamos. Portanto, é necessário que se tenha o CMake
devidamente instalado e atualizado.

Instruções de compilação:
Para plataformas Linux desenvolvemos um script de shell, compiler.sh, que automatiza o
processo de compilação.
Para poder executar o script, o usuário deve dar a permissão para o mesmo
executar utilizando o comando:

chmod +x compiler.sh

Para executar o script:

./compiler.sh

Obs.: caso não execute, utilize o comando: sudo ./compiler.sh

- Após compilar, o CMake irá gerar o diretório build dentro da pasta raiz do projeto.
Nessa pasta estará o arquivo binário gerado.

Executar o programa:
1) Entrar no diretório build:
	cd build/

2) Executar:
	./EDII path

Em que "path" é o caminho para o arquivo csv.