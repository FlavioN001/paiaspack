// Esse é meu primeiro código fonte que vai além de um testezinho. (Passei um bom tempo desenvolvendo)
// Tá longe de ser considerado bom ou consistente, mas quase sempre funciona e acredito que vai ser bem útil pro que eu quero.
#include <cstdlib>
#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>
#include <filesystem>

//Checar sistema operacional
int checkSystem(){
    int SO;
    #if defined (_WIN32)
    SO = 0;
    #elif defined (__APPLE__)
    SO = 2;
    #else
    SO = 1;
    #endif
    return SO;
}

//Transformar CMD para UTF-8
void codepage(){
    if (checkSystem()==0) {
        system("chcp 65001");
    }
}

//Checar internet
bool online(){
    bool online;
    if (checkSystem()==0) {
        if (system("ping -n 1 8.8.8.8 > NUL 2>&1")==0) {
            online = true;
        }
        else {
            online = false;
        }
    }
    else {
        if (system("ping -c 1 8.8.8.8 > /dev/null 2>&1")==0) {
            online = true;
        }
        else {
            online = false;
        }
    }
    return online;
}

//Definindo pasta do jogo:
std::filesystem::path gameDir(){
    std::string folder;
    //No windows
    if (checkSystem()==0) {
        folder = getenv("USERPROFILE");
        folder += "\\appdata\\roaming\\.minecraft";
    }
    //No linux e parecidos
    else if (checkSystem()==1){
        folder = getenv("HOME");
        folder += "/.minecraft";
    }
    //No MacOS
    else if (checkSystem()==2){
        folder = getenv("HOME");
        folder += "/Library/Application\\ Support/minecraft/config";
    }
    std::filesystem::path dir = folder;
    return dir;
}

//Determinar pasta de instalação
std::filesystem::path installPath(){
    std::filesystem::path dir = gameDir() / "paiaspack";
    return dir;
}

std::filesystem::path mpdir(){
    std::filesystem::path path = gameDir() / "instances" / "Paia\'s_pack";
    return path;
}

//Limpar cache
void cleanUp(){
    if (std::filesystem::exists(installPath())) {
        std::filesystem::remove_all(installPath());
    }
}

//pausar o console
void pause(){
    if (checkSystem()==0) {
        system("pause");
    }
    else {
        system("read -n1 -r -p \"Pressione qualquer tecla para continuar.\"  key");
    }
}

//Mensagens de erro
int error(std::string type, std::string motivo){
    //erros de desenvolvimento
    if (type=="dev") {
        if (checkSystem()==1) {
            std::cout << "  Há um erro no código fonte D:  Contate o desenvolvedor.\n";
        }
        else {
            std::cout << "  Tem um erro no codigo fonte D:  Contate o desenvolvedor.\n";
        }
        std::cout << "  Motivo: "<< motivo << ".\n";
        pause();
        exit(1);
    }
    //erros do usuário
    else if (type=="entry") {
        if (checkSystem()==1) {
            std::cout << "  Insira uma opção válida.\n" << std::endl;
        }
        else {
            std::cout << "  Insira uma opcao valida.\n" << std::endl;
        }
    }
    //erro no tar
    else if (type=="tar") {
        std::cout << "  Ocorreu um erro ao extrair o modpack.\n Tenha certeza que você tem o \"tar\" instalado" << std::endl;
        cleanUp();
        pause();
        exit(1);
    }
    //erro no curl
    else if (type=="curl") {
        std::cout << "  Erro ao baixar modpack, verifique sua conexão com a internet.\n" << std::endl;
        cleanUp();
        pause();
        exit(1);
    }
    //erro ao desinstalar
    else if (type=="rm"){
        std::cout << "  Ocorreu um erro ao desinstalar o modpack. \n Remova a pasta \"" + mpdir().string() + "\"\n" << std::endl;  
    }

    //erro desconhecido (genérico)
    else {
        std::cout << "  Ocorreu um erro desconhecido." << std::endl;
        std::cout << "  Contate o desenvolvedor" << std::endl;
        std::cout << "  Motivo: "<< motivo << ".\n" << std::endl;

        exit(1);
    }
    return 0;
}

//Definir o comando de limpar terminal
void clear(){
    int so = checkSystem();
    if (so == 1) {
        system("clear");
    }
    else{
        system("cls");
    }
}

//Pegar o nome do usuário
std::string getUser(){
    std::string user;
    if (checkSystem()==0){
        user = std::getenv("USERNAME");
    }
    else if (checkSystem()==1||checkSystem()==2) {
        user = std::getenv("USER");
    }
    return user;
}

//Esperar dois segundos
void wait(){
    if (checkSystem()==0) {
        system("timeout /t 2 > NUL 2>&1");
    }
    else if (checkSystem()==1 || checkSystem()==2) {
        system("sleep 2 > /dev/null 2>&1");
    }
}

// Baixar modpack usando curl
int downloadMP(){
    std::filesystem::path zippath = installPath() / "latest.tar.gz";
    if (!std::filesystem::exists(installPath())) {
        std::filesystem::create_directory(installPath());
    }
    std::cout << "  Baixando modpack... \n" << std::endl;
    std::string command = "curl -L# https://github.com/FlavioN001/paiaspack/releases/download/modpack-latest/Paia.s_pack.tar.gz -o " + zippath.string();

    if (system((command).c_str())!=0){
        error("curl", "");
    }
    return 0;
}

//Extrair .tar baixado
int extractZip(std::filesystem::path file, std::filesystem::path destination){
    //Extrai o zip usando tar sem retornar nada
    //Eu tentei colocar uma barra de progresso, mas a única solução que achei foi com o
    // programa pv, que eu não quero adicionar como uma dependência no projeto.
    std::string extractcommand;
    if (!std::filesystem::exists(std::filesystem::path(destination))) {
        std::filesystem::create_directories(destination);
    }
    //No windows (por causa do NUL)
    if (checkSystem()==0) {
        extractcommand = "tar -xf \"" + file.string() + "\" -C \"" + destination.string() + "\" > NUL 2>&1";
    }
    else {
        extractcommand = "tar -xf \"" + file.string() + "\" -C \"" + destination.string() + "\"";
    }
    if (system((extractcommand).c_str())!=0) {
        error("tar", "");
    }
    return 0;
}

//Instalar o modpack, baixando, extraindo e movendo-o.
void installModPack(std::string texto){
    std::filesystem::path mpzip = installPath() / "latest.tar.gz";
    std::filesystem::path instdir = gameDir() / "instances";
    downloadMP();
    std::cout << texto << "... \n" << std::endl;
    extractZip(mpzip, mpdir() / "..");
}

//Desinstalar modpack
void uninstall(){
    if (std::filesystem::exists(mpdir())) {
        std::filesystem::remove_all(mpdir());
    }
    else {
        std::cout << "  O modpack não está instalado.\n" << std::endl;
    }
}

//Determina a versão do modpack mais recente
std::string latestMPVersion(){
    std::string downloadVerCommand;
    std::string version;
    if (!std::filesystem::exists(installPath())) {
        std::filesystem::create_directory(installPath());  
    }
    std::filesystem::path path = installPath() / "Version.txt";
    if (checkSystem()==0) {
        downloadVerCommand = "curl -L https://github.com/FlavioN001/paiaspack/releases/download/modpack-latest/Version.txt -o " + path.string() + " > NUL 2>&1" ;
    }
    else {
        downloadVerCommand = "curl -L https://github.com/FlavioN001/paiaspack/releases/download/modpack-latest/Version.txt -o " + path.string() + " > /dev/null 2>&1" ;
    }
    system(downloadVerCommand.c_str());
    std::ifstream file(path);
    std::getline(file, version);
    return version;
}

//Determina a temporada do modpack mais recente
std::string getSeason(){
    std::string season;
    if (!std::filesystem::exists(installPath())) {
        std::filesystem::create_directory(installPath());  
    }
    std::filesystem::path path = installPath() / "Season.txt";
    if (!std::filesystem::exists(path)) {
        if (checkSystem()==0) {
            std::string downloadSeasonCommand = "curl -L https://github.com/FlavioN001/paiaspack/releases/download/modpack-latest/Season.txt -o " + path.string() + " > NUL 2>&1" ;
            system(downloadSeasonCommand.c_str());

        }
        else {
            std::string downloadSeasonCommand = "curl -L https://github.com/FlavioN001/paiaspack/releases/download/modpack-latest/Season.txt -o " + path.string() + " > /dev/null 2>&1" ;
            system(downloadSeasonCommand.c_str());

        }
    }
        
    std::ifstream file(path);
    std::getline(file, season);
    return season;
}

std::string getlocalSeason(){
    std::string season;
    std::filesystem::path seasonfile = mpdir() / "Season.txt";
    if (std::filesystem::exists(seasonfile)) {
        std::ifstream file(seasonfile);
        std::getline(file, season);
    }
    return season;
}

//Verificar se o modpack está instalado
bool isInstalled(){
    int result;
    if (std::filesystem::exists(mpdir() / "options.txt")) {
        result = 1;
    }
    else {
        result = 0;
    }
    return result;
}

//Mensagem de boas vindas
void greet(){
    std::string greet;
    if (getUser().empty()){
        greet = "  Bem vindo ao configurador do Paia\'s Pack!\n";
    }
    else {
        greet = "  Olá, " + getUser() + "!\n  Bem vindo ao configurador do Paia\'s Pack!\n";
    }
    std::cout << greet << std::endl;
    if (isInstalled()) {
        if (!getlocalSeason().empty()) {
            std::cout << "  Instalado: " << getlocalSeason() << std::endl;
        }
    }
}

//Verificar se a versão mais recente está instalada
bool upToDate(){
    bool result;
    std::string latestVersion = latestMPVersion();
    std::filesystem::path installedVersion = mpdir() / "Version.txt";
    
    if (std::filesystem::exists(installedVersion)) {
        std::ifstream file(installedVersion);
        std::string installed_str;
        std::getline(file, installed_str);
        if (installed_str == latestVersion) {
            result = 1;
        }
        else {
            result = 0;
        }
    }
    else {
        result = 0;
    }
    return result;
}

//Fazer backup dos dados de usuário
void backup() {
    std::cout << "  Fazendo backup dos dados de usuário..." << std::endl ;
    std::filesystem::path backupPath = installPath() / "updateBackup";
    
    //Pastas a fazer backup
    std::filesystem::path resourcePacks = mpdir() / "resourcepacks";
    std::filesystem::path shaderPacks = mpdir() / "shaderpacks";
    std::filesystem::path saves = mpdir() / "saves";
    std::filesystem::path configs = mpdir() / "config";
    std::filesystem::path screenshots = mpdir() / "screenshots";
    std::filesystem::path DHdata = mpdir() / "Distant_Horizons_server_data";
    std::filesystem::path miniMapData = mpdir() / "xaero";
    //Fazendo backup das pastas
    
    std::filesystem::create_directory(backupPath);
    if (std::filesystem::exists(resourcePacks)) {
        std::filesystem::path resourcebackupPath = backupPath / "resourcepacks";
        std::filesystem::copy(resourcePacks, resourcebackupPath);
        
    }
    if (std::filesystem::exists(shaderPacks)) {
        std::filesystem::path shaderbackupPath = backupPath / "shaderpacks";
        std::filesystem::copy(shaderPacks, shaderbackupPath);
    }
    if (std::filesystem::exists(saves)) {
        std::filesystem::path savebackupPath = backupPath / "saves";
        std::filesystem::copy(saves, savebackupPath);
    }
    if (std::filesystem::exists(configs)) {
        std::filesystem::path configbackupPath = backupPath / "config";
        std::filesystem::copy(configs, configbackupPath);
    }
    if (std::filesystem::exists(screenshots)) {
        std::filesystem::path screenshotbackupPath = backupPath / "screenshots";
        std::filesystem::copy(screenshots, screenshotbackupPath);
    }
    if (std::filesystem::exists(DHdata)) {
        std::filesystem::path DHdatabackupPath = backupPath / "Distant_Horizons_server_data";
        std::filesystem::copy(DHdata, DHdatabackupPath);
    }
    if (std::filesystem::exists(miniMapData)) {
        std::filesystem::path miniMapDataBackupPath = backupPath / "xaero";
        std::filesystem::copy(miniMapData, miniMapDataBackupPath);
    }


    std::cout << "  Backup concluído." << std::endl;
}

//Restaurar backup do usuário
void restoreBackup() {
    std::filesystem::path backupPath = installPath() / "updateBackup";

    //Pastas a restaurar backup
    std::filesystem::path resourcePacks = backupPath / "resourcepacks";
    std::filesystem::path shaderPacks = backupPath / "shaderpacks";
    std::filesystem::path saves = backupPath / "saves";
    std::filesystem::path configs = backupPath / "configs";
    std::filesystem::path screenshots = backupPath / "screenshots";
    std::filesystem::path DHdata = backupPath / "Distant_Horizons_server_data";
    std::filesystem::path miniMapData = backupPath / "xaero";

    //Restaurando backup
    if (std::filesystem::exists(resourcePacks)) {
        std::filesystem::copy(resourcePacks, mpdir() / "resourcepacks", std::filesystem::copy_options::overwrite_existing);
    }
    if (std::filesystem::exists(shaderPacks)) {
        std::filesystem::copy(shaderPacks, mpdir() / "shaderpacks", std::filesystem::copy_options::overwrite_existing);
    }
    if (std::filesystem::exists(saves)) {
        std::filesystem::copy(saves, mpdir() / "saves", std::filesystem::copy_options::overwrite_existing);
    }
    if (std::filesystem::exists(configs)) {
        std::filesystem::copy(configs, mpdir() / "configs", std::filesystem::copy_options::overwrite_existing);
    }
    if (std::filesystem::exists(screenshots)) {
        std::filesystem::copy(screenshots, mpdir() / "screenshots", std::filesystem::copy_options::overwrite_existing);
    }
    if (std::filesystem::exists(DHdata)) {
        std::filesystem::copy(DHdata, mpdir() / "Distant_Horizons_server_data", std::filesystem::copy_options::overwrite_existing);
    }
    if (std::filesystem::exists(miniMapData)) {
        std::filesystem::copy(miniMapData, mpdir() / "xaero", std::filesystem::copy_options::overwrite_existing);
    }
}

//Atualizar o modpack
void update(){
    clear();
    if (!isInstalled()) {
        std::cout << "  Não é possível atualizar. O modpack não está instalado." << std::endl;
    }
    else if (upToDate()) {
        std::cout << "  O modpack já está atualizado." << std::endl;
    }
    else {
        //Fazer backup, apagar a versão instalada e baixar a mais recente
        if (!std::filesystem::exists(installPath())) {
            std::filesystem::create_directory(installPath());  
        }
        backup();
        uninstall();
        std::filesystem::path zipdir = mpdir() / "latest.tar.gz";
        installModPack("Atualizando para " + getSeason());
        
        //Restaurando backup
        restoreBackup();

        //Apagando backup
        std::filesystem::remove_all((installPath() / "updateBackup"));
    }
}

//Reparar instalação do modpack
void restore(){
    //A fazer: apagar pasta do modpack e baixar a mais recente. Funciona como uma forma
    //de atualizar, mas perdendo dados.
    clear();
    std::cout << "  ATENÇÃO! Você pode acabar perdendo os dados do modpack. \n Tem certeza que quer continuar? (s/n) \n" << std::endl;
    std::string resposta;
    std::cout << "> ";
    std::cin >> resposta;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (resposta == "s") {
        clear();
        std::cout << "  Restaurando Paia\'s Pack...\n" << std::endl;
        backup();
        std::filesystem::remove_all(mpdir());
        installModPack("Restaurando");
        restoreBackup();
        cleanUp();
        std::cout << "\n  Instalação reparada com sucesso!\n" << std::endl;
        pause();
        clear();
    }
    else if (resposta != "s" && resposta != "n") {
        std::cout << "  Insira uma resposta válida\n" << std::endl;
        pause();
        restore();
    }
}

//Não me orgulho em dizer que essa função foi completamente vibe-coded.
//A esse ponto do projeto, eu só queria fazer isso funcionar logo, mas ainda pretendo aprender json
//pra entender como isso funciona de fato.
void setProfile(){
    std::filesystem::path raw_gamedir = gameDir() / "instances" / "Paia's_pack";
    std::filesystem::path raw_configPath = gameDir() / "launcher_profiles.json";
    std::string configPath = raw_configPath.string();
    std::string gamedir = raw_gamedir.string();
    using json = nlohmann::json;
    std::string profileId = "279237ef738849d299b251aefded2f45";
     json newProfile = {
        {"name", "Paia's pack"},
        {"gameDir", gamedir},
        {"lastVersionId", "fabric-loader-0.17.3-1.21.1"},
        {"javaArgs", "-XX:+UnlockExperimentalVMOptions -XX:+UseG1GC -XX:G1NewSizePercent=20 -XX:G1ReservePercent=20 -XX:MaxGCPauseMillis=50 -XX:G1HeapRegionSize=16M -Djava.net.preferIPv4Stack=false"},
        {"resolution", {
            {"width", 854},
            {"height", 480},
            {"fullscreen", false}
        }},
        {"type", "custom"},
        {"created", "2025-11-01T22:05:49-03:00"},
        {"lastUsed", "2025-11-01T22:05:49-03:00"},
        {"icon", "data:image/png;base64,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"}
    };
    json data;
    try {
        std::ifstream inputFile(configPath);
        if (inputFile.is_open()) {
             inputFile >> data;
        }
    }
    catch (json::parse_error& e) {
        std::cout << "  Tem algo de errado com o seu arquivo launcher_profiles.json\n" << std::endl;
        cleanUp();
        pause();
        exit(1);
    }

    data["profiles"][profileId] = newProfile;
    std::ofstream outputFile(configPath);
    if (!outputFile.is_open()) {
        std::cerr << "  Não foi possivel alterar o launcher_profiles.json\n" << std::endl;
        cleanUp();
        pause();
        exit(1);
    }

    outputFile << data.dump(4);
    outputFile.close();
}

//Onde o programa inteiro executa
int exec(){
    clear();
    greet();
    if (!isInstalled()) {
        if (!online()) {
            std::cout << "  ------  Modo offline  ------- \n" << std::endl;
            std::cout
            << "Opções: " << "\n\n"
            << "  1 - Tentar novamente" << "\n\n"
            << "  2 - Sair" << "\n \n \n \n";
            int escolha;
            std::cout << "> ";
            std::cin >> escolha;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (escolha == 1) {
                exec();
            }
            else if (escolha == 2) {
                cleanUp();
                exit(0);
            }
            else {
            std::cout << "  Opção invalida.\n";
                pause();
                exec();
            }
        }
        std::cout
        << "Opções: " << "\n\n"
        << "  1 - Instalar Paia\'s Pack" << "\n\n"
        << "  2 - Sair" << "\n \n \n \n";
        int escolha;
        std::cout << "> ";
        std::cin >> escolha;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (escolha == 1) {
            clear();
            installModPack("Instalando Paia\'s Pack");
            cleanUp();
            setProfile();
            clear();
            std::cout << "\n\n  O Paia\'s Pack foi instalado com sucesso!\n" << std::endl;
            pause();
            exec();
        }
        else if (escolha == 2) {
            cleanUp();
            exit(0);
        }
        else {
            std::cout << "  Opção invalida.\n";
            pause();
            exec();
        }

    }
    else{
        if (!online()) {
            std::cout
            << "\n  ------  Modo offline  ------- \n" << std::endl
            << "Opções: " << "\n\n"
            << "  1 - Tentar novamente" << "\n\n"
            << "  2 - Desinstalar Paia\'s Pack" << "\n\n"
            << "  3 - Sair" << "\n \n \n \n";
            int escolha;
            std::cout << "> ";
            std::cin >> escolha;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (escolha==1) {
                exec();
            }
            else if (escolha==2) {
                std::cout << "\n\n  Tem certeza que quer perder todos os dados do modpack? (s/n) \n" << std::endl;
                std::string resposta;
                std::cout << "> ";
                std::cin >> resposta;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (resposta == "s") {
                    clear();
                    std::cout << "\n\n  Desinstalando Paia\'s Pack...\n" << std::endl;
                    uninstall();
                    cleanUp();
                    clear();
                    std::cout << "\n\n  O Paia\'s Pack foi desinstalado com sucesso!\n" << std::endl;
                    pause();
                }
                else if (resposta != "s" && resposta != "n") {
                    std::cout << "  Insira uma resposta válida\n" << std::endl;
                    pause();
                    uninstall();
                }
            }
            else if (escolha==3) {
                cleanUp();
                exit(0);
            }
            exec();    
        }
        else if (!upToDate()) {
            std::cout
            << "Opções: " << "\n\n"
            << "  1 - Atualizar Paia\'s Pack para " << getSeason() << "!" << "\n\n"
            << "  2 - Restaurar Paia\'s Pack" << "\n"
            << "  3 - Desinstalar Paia\'s Pack" << "\n\n"
            << "  4 - Sair" << "\n \n \n \n";
            int escolha;
            std::cout << "> ";
            std::cin >> escolha;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');            
            if (escolha==1) {
                update();
                cleanUp();
                exec();
            }
            else if (escolha==2) {
                restore();
                setProfile();
                exec();
            }
            else if (escolha==3) {
                std::cout << "\n\n  Tem certeza que quer perder todos os dados do modpack? (s/n) \n" << std::endl;
                std::string resposta;
                std::cout << "> ";
                std::cin >> resposta;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (resposta == "s") {
                    clear();
                    std::cout << "\n\n  Desinstalando Paia\'s Pack...\n" << std::endl;
                    uninstall();
                    cleanUp();
                    clear();
                    std::cout << "\n\n  O Paia\'s Pack foi desinstalado com sucesso!\n" << std::endl;
                    pause();
                }
                else if (resposta != "s" && resposta != "n") {
                    std::cout << "  Insira uma resposta válida\n" << std::endl;
                    pause();
                    uninstall();
                }
                exec();
            }
            else if (escolha==4) {
                cleanUp();
                exit(0);
            }
            else {
                std::cout << "  Opção invalida.\n" << std::endl;
                pause();
                exec();
            }
        }
        else {
            std::cout
            << "  Opções: " << "\n\n"
            << "  1 - Restaurar Paia\'s Pack" << "\n"
            << "  2 - Desinstalar Paia\'s Pack" << "\n\n"
            << "  3 - Sair" << "\n \n \n \n";
            int escolha;
            std::cout << "> ";
            std::cin >> escolha;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (escolha==1) {
                restore();
                setProfile();
                exec();
            }
            else if (escolha==2) {
                std::cout << "\n\n  Tem certeza que quer perder todos os dados do modpack? (s/n) \n" << std::endl;
                std::string resposta;
                std::cout << "> ";
                std::cin >> resposta;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (resposta == "s") {
                    clear();
                    std::cout << "\n\n  Desinstalando Paia\'s Pack...\n" << std::endl;
                    uninstall();
                    cleanUp();
                    clear();
                    std::cout << "\n\n  O Paia\'s Pack foi desinstalado com sucesso!\n" << std::endl;
                    pause();
                }
                else if (resposta != "s" && resposta != "n") {
                    std::cout << "  Insira uma resposta válida\n" << std::endl;
                    pause();
                    uninstall();
                }
                exec();
            }
            else if (escolha==3) {
                cleanUp();
                exit(0);
            }
            else {
                std::cout << "  Opção invalida.\n";
                pause();
                exec();
            }
        }
    }
    return 0;
}

//Inicia o programa
int main(){
    cleanUp();
    codepage();
    exec();
    return 0;
}
