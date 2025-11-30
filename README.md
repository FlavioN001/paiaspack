# paiaspack - INDEV
## Um modpack que eu fiz para eu e meus amigos jogarem, com um instalador multiplataforma. Aproveitei para praticar minhas habilidades de programação em c++.

### Eu tentei ao máximo simplificar o lado do usuário, deve ser tão fácil quanto baixar e executar o instalador certo e seguir as instruções.

- Dependência: [git](https://git-scm.com/install/)

É, bem simples. Só tenha o [git](https://git-scm.com/install/) instalado e tudo deve funcionar bem. O programa tentará instalar automaticamente se não tiver instalado. Se houver qualquer problema, entre em contato comigo que eu tentarei te ajudar com ele.

- Nota: 
Teoricamente, o software deve funcionar no MacOS se o homebrew estiver instalado, mas não foi testado. Então se for o caso, apenas siga o processo de instalação do Linux e descubra o que acontece. Também há a opção de instalar manualmente, então na verdade tem salvação sim.

### Passo 1 - Tenha um launcher de minecraft instalado.

Todos os testes realizados foram com o [SK Launcher](https://skmedix.pl/), então ele é altamente recomendado. Eu não garanto que o instalador funcionará corretamente com outros launchers.

### Passo 2 - Baixe o instalador do modpack

Na aba [releases](https://github.com/FlavioN001/paiaspack/releases), selecione a versão mais recente disponível para o seu sistema operacional (Windows ou Linux).
- **Execução**

WINDOWS

Execute o instalador e ignore possíveis notificações do windows defender, o windows não deve gostar muito de mim.

LINUX

Abra uma janela de terminal, e acesse o diretório no qual você baixou o instalador (provavelmente `~/Downloads`), permita que o arquivo execute como programa, e abra ele, desta forma: 
```
cd ~/Downloads/
sudo chmod +x Paias_Pack_Installer-LINUX
./Paias_Pack_Installer-LINUX
```

### Passo 3 - Instalação

Ao abrir o instalador, ele tentará baixar o git se não estiver instalado.

Se der tudo certo, você se deparará com uma tela parecida com esta:
![Prévia do instalador em sua tela incial](/assets/preview1.png)

Aqui está o que cada ação faz, tecnicamente:

- 1- Instalar\
Essa opção baixará o modpack com todos os recursos, criará uma instância do modpack exclusiva para ele no seu launcher (para evitar conflito de recursos) e apagará o cache da instalação.

- 2- Desinstalar\
Essa opção deletará a pasta da instância dentro de .minecraft/instances que contém todos os dados do modpack.

- 3- Atualizar modpack\
Essa opção apagará a pasta mods do modpack e baixará a versão mais nova disponível no repositório git.

- 4- Sair\
Essa opção fecha o programa. (duh)

### Passo 4 - Pós-Instalação

Agora que o modpack foi instalado corretamente, ao abrir o sklauncher, ele deve se parecer com isso:
![prévia do launcher após a instalação](/assets/preview2.png)

- Não se esqueça de alocar memória o suficiente para o modpack!\
é recomendado entre 3gb e 4gb de ram.\
![prévia do botão de editar instância](/assets/preview3.png)
![prévia da alocação de memória](/assets/preview4.png)

### Resolução de erros

Se tudo der errado e a vida parecer triste, ainda existe a opção de instalar o modpack manualmente

- Baixe esse repositório pela interface do github:
![prévia da interface do github](/assets/preview5.png)

Em seguida, extraia o arquivo, encontre a pasta `instances` e mova-a para dentro da [sua pasta .minecraft](https://minecraft.fandom.com/pt/wiki/.minecraft).

- Depois, no [SK Launcher](https://skmedix.pl/), crie uma instância seguindo os seguintes passos:

1- Crie uma instância\
![troubleshooting step 1](/assets/preview6.png)


2- Mude o nome da instância para `Paia's pack`\
![troubleshooting step 2](/assets/preview7.png)


3- Crie uma pasta separada para a instância\
![troubleshooting step 3](/assets/preview8.png)


4- Mude a versão para Fabric 1.21.1\
![troubleshooting passo 4](/assets/preview9.png)
![troubleshooting passo 5](/assets/preview10.png)


5- Troque o último argumento da JVM para false\
![troubleshooting passo 6](/assets/preview11.png)
![troubleshooting passo 7](/assets/preview12.png)
![troubleshooting passo 8](/assets/preview13.png)


- Agora salve as opções e seja feliz!

### Isso me deu muito trabalho e eu estou contente com o resultado, apesar da demora.

### Créditos: 
Flero - Programação, modpack, documentação e servidor\
Fox - Todos os ícones/logos do modpack
