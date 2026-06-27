# Paia's Pack
### Um modpack em fabric que eu fiz para eu e meus amigos jogarem, com um instalador multiplataforma. Aproveitei para praticar minha programação em c++.
#
# A SEASON 2 CHEGOU! 
# ![Banner da season 2 - arte por FOX](/assets/banner.png)

### Novo Instalador!




### Eu tentei ao máximo simplificar o lado do usuário, deve ser tão fácil quanto baixar e executar o configurador e seguir as instruções.

### Passo 1 - Tenha um launcher de minecraft instalado.

Todos os testes realizados foram com o [SK Launcher](https://skmedix.pl/), então ele é altamente recomendado. Eu não garanto que o instalador funcionará corretamente com outros launchers.

### Passo 2 - Baixe e execute o configurador do Paia's

  Na aba [releases](https://github.com/FlavioN001/paiaspack/releases/tag/publish), selecione a versão certa para o seu sistema operacional (Windows ou baseado em Linux).

- WINDOWS:
  
  Após o download, ignore qualquer aviso do windows defender .Qualquer suspeita pode ser um falso positivo, [o código fonte está aberto para público, verifique você mesmo.](https://github.com/FlavioN001/paiaspack/blob/main/source/PaiasSourceCode.cpp)
  
  Execute o arquivo .exe e instale o modpack.

- LINUX - SIMPLIFICADO
  
  Ao invés de baixar o arquivo, apenas rode esse comando no terminal:
  ```
  clear && echo "Baixando instalador..." && curl -L# https://github.com/FlavioN001/paiaspack/releases/download/publish/Paias_Setup-LINUX -o ~/.cache/Paias_Setup-LINUX && echo "Insira sua senha para deixar o instalador executável." && sudo chmod +x ~/.cache/Paias_Setup-LINUX && ~/.cache/Paias_Setup-LINUX && rm ~/.cache/Paias_Setup-LINUX
  ```
  
- LINUX

  Abra uma janela de terminal, e acesse o diretório no qual você baixou o instalador (provavelmente `~/Downloads`). Em seguida, permita que o arquivo execute como programa e rode-o, desta forma: 

  ```
  cd ~/Downloads/
  sudo chmod +x Paias_Setup-LINUX
  ./Paias_Setup-LINUX
  ```


### Passo 3 - Instalação

Se der tudo certo, você se deparará com uma tela parecida com esta:
![Prévia do instalador em sua tela incial](/assets/preview1.png)

Estas são todas as funções contidas no configurador:

- 1- Instalar\
Baixa o modpack com todos os recursos e cria uma instância exclusiva do modpack no seu launcher (para evitar conflito de recursos).

- 2- Atualizar\
Faz backup dos dados do jogador, apaga a versão instalada, baixa a mais recente e restaura o backup.

- 3- Restaurar\
Tenta fazer backup dos dados do jogador, apaga a versão instalada, baixa a mais recente e restaura o backup. (é como atualizar sem precisar de uma versão mais nova)

- 4- Desinstalar\
Deleta a pasta da instância dentro de .minecraft/instances que contém todos os dados do modpack.

- 5- Sair\
Fecha o programa. (duh)

### Passo 4 - Pós-Instalação

Agora que o modpack foi instalado com sucesso, ao abrir o sklauncher ele deve se parecer com isso:
![prévia do launcher após a instalação](/assets/preview2.png)

- Não se esqueça de alocar memória o suficiente para o modpack!\
é recomendado entre 3gb e 4gb de ram.\
![prévia do botão de editar instância](/assets/preview3.png)
![prévia da alocação de memória](/assets/preview4.png)


### Isso me deu muito trabalho e eu estou contente com o resultado, apesar da demora.

### Créditos: 
Flero - Programação, ModPack, documentação e servidor\
Fox - Toda a arte do ModPack
