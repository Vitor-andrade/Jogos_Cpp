#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

int i,j;

string palavra_secreta = "MELANCIA"; 
map <char, bool> chutou;
vector<char> chutes_errados;

bool letra_existe(char chute){
    
    for(i = 0; i < palavra_secreta.size(); i++){
        if(chute == palavra_secreta[i]){
            return true;
        }
    }
    return false;
}

bool nao_acertou(){
    for(i = 0; i < palavra_secreta.size(); i++){
        if(!chutou[palavra_secreta[i]]){
            return true;
        }
    }
    return false;
}

void imprime_cabecalho(){
    cout << "**************************"<< endl;
    cout << "*     Jogo da Forca      *"<< endl;
    cout << "**************************"<< endl;
}

bool nao_enforcou(){
    return chutes_errados.size() < 5;
}

void imprime_erros(){
        for(i = 0; i < chutes_errados[i]; i++){
        cout << chutes_errados[i] << " ";
        }
        cout << endl;
}

void imprime_palavra(){
    for(i = 0; i < palavra_secreta.size(); i++){
            if(chutou[palavra_secreta[i]]){
                cout << palavra_secreta[i] << " ";
            }
            else{
                cout << "_ ";
            }
        }
        cout << endl;
}

void chuta(){
    cout << "Digite um chute: " << endl;
        char chute;
        cin >> chute;

        chutou[chute] = true;

        if(letra_existe(chute)){
            cout << "Voce acertou! Seu chute esta na palavra." << endl;
        }
        else{
            cout << "Voce errou! Seu chute nao esta na palavra." << endl;
            chutes_errados.push_back(chute);
            cout << "Chutes errados: ";
            imprime_erros();
        }
        cout << endl;
}

vector<string> le_arquivo(){
    ifstream arquivo;
    arquivo.open("palavras.txt");

    if(arquivo.is_open()){
        int quantidade_palavras;
        arquivo >> quantidade_palavras;

        vector<string> palavras_do_arquivo;

        for(i = 0; i < quantidade_palavras; i++){
            string palavra_lida;
            arquivo >> palavra_lida;
            palavras_do_arquivo.push_back(palavra_lida);
        }
        arquivo.close();
        return palavras_do_arquivo;
    }
    else{
        cout << "Nao foi possivel acessar o banco de palavras" << endl;
        exit(0);
    }
}

void sorteia_palavra(){
    vector<string> palavras = le_arquivo();

    srand(time(0));
    int indice_sorteado = rand() % palavras.size();

    palavra_secreta = palavras[indice_sorteado];
}

void salva_arquivo(vector<string> nova_lista){
    ofstream arquivo;
    arquivo.open("palavras.txt");
    if(arquivo.is_open()){
        arquivo << nova_lista.size() << endl;

        for(j = 0; j < nova_lista.size(); j++){
            arquivo << nova_lista[j] << endl;
        }
        arquivo.close();
    }
    else{
        cout << "Nao foi possivel acessar o banco de palavras" << endl;
        exit(0);
    }
    
}

void adiciona_palavra(){
    cout << "Digite a nova palavra com letras maiusculas: " << endl;
    string nova_palavra;
    cin >> nova_palavra;

    vector<string> lista_palavras = le_arquivo();
    lista_palavras.push_back(nova_palavra);

    salva_arquivo(lista_palavras);
}

int main () {

    imprime_cabecalho();

    le_arquivo();
    sorteia_palavra();

    while(nao_acertou() && nao_enforcou()){
        imprime_palavra();
        chuta();
    }

    cout << "Fim de jogo!" << endl;
    cout << "A palavra secreta era: " << palavra_secreta << endl;
    if(nao_acertou()){
        cout << "Voce perdeu! Tente novamente" << endl;
    }
    else{
        cout << "Parabens! Voce acertou!" << endl;

        cout << "Voce deseja adicionar uma nova palavra ao jogo? (S ou N)" << endl;
        char resposta;
        cin >> resposta;
        if(resposta == 'S'){
            adiciona_palavra();
        }
        else{

        }
    }
}