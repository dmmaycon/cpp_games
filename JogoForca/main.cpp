#include<iostream>
#include<string>
#include<map> 
#include<vector>
#include<fstream>
#include<ctime>
#include<cstdlib>

using namespace std;

const int NUMERO_TENTATIVAS = 5;
string palavra_secreta;

map<char, bool> palavra_chute;
vector<char> letras_erradas;

bool existe_letra(char letraDigitada) {
    for (char letra : palavra_secreta) {
        if (letra == letraDigitada) {
            palavra_chute[letra] = true;
            return true;            
        }
    }
    return false;
}

string desenha_palavra() {
    string desenho = "";
    for (char letra : palavra_secreta) {
        if (palavra_chute[letra]) {
            desenho += letra;
            desenho += " ";       
        } else {
            desenho += "_ ";
        }
    }
    return desenho;
}

char perguntaLetra() {
    char letra;
    cout << "Informe uma letra: ";
    cin >> letra;
    return letra;
}

bool verifica_ganhou() {
    for (char letra : palavra_secreta) {
        if (!palavra_chute[letra]) {
            return false;
        }
    }
    return true;
}

bool verifica_forca() {
    return letras_erradas.size() < NUMERO_TENTATIVAS;
}

string letras_erradas_digitadas() {
    string letras = "";
    for (char letra :  letras_erradas) {
        letras += letra;
        letras += " ";
    }
    return letras;
}

vector<string> le_arquivo() {
    ifstream arquivo;
    arquivo.open("banco_palavras.txt");
    if (arquivo.is_open()) {
        vector<string> palavras_banco;
        int qtd_palavras;
        arquivo >> qtd_palavras;

        for (int i = 0; i < qtd_palavras; i++) {
            string palavra;
            arquivo >> palavra;
            palavras_banco.push_back(palavra);
        }
        arquivo.close();
        return palavras_banco;
    } else {
        cout << "Não foi possível abrir o arquivo!";
        exit(0);
    }
}

void sorteia_palavra() {
    vector<string> palavras_banco = le_arquivo();
    srand(time(0));
    int index = rand() % palavras_banco.size();
    palavra_secreta = palavras_banco[index];
}


void insere_palavra() {
    cout << "Digite a nova palavra para inserir no jogo: ";
    string palavra;
    cin >> palavra;

    vector<string> palavras_banco = le_arquivo();
    palavras_banco.push_back(palavra);

    ofstream arquivo;
    arquivo.open("banco_palavras.txt");
    if (arquivo.is_open()) {
        
        arquivo << palavras_banco.size() << "\n";

        for (string palavra : palavras_banco) {
            arquivo << palavra << "\n";            
        }
        arquivo.close();
    } else {
        cout << "Não foi possível abrir o arquivo!";
        exit(0);
    }
}

int main() {
    cout << "***************************************************\n";
    cout << "* * * * * *  BEM-VINDO AO JOGO DA FORCA * * * * * * \n";
    cout << "***************************************************\n";

    sorteia_palavra();
    cout << "Palavra a ser descoberta: " << desenha_palavra() << "\n";
    
    do {
        char letra = perguntaLetra();
        if (existe_letra(letra)) {
            cout << desenha_palavra() << "\n";
        } else {
            cout << "Letra não existe \n";
            cout << desenha_palavra() << "\n";
            letras_erradas.push_back(letra);
        }
        cout << "\n";
        cout << "Letras erradas: " << letras_erradas_digitadas() << "\n";
        cout << "\n";
    } while(!verifica_ganhou() && verifica_forca());
    
    cout << "FIM DE JOGO \n";
    cout << "A palavra era: " << palavra_secreta << "\n";

    if (verifica_ganhou()) {
        cout << "Parabéns você acertou a palavra e ganhou!\n";
        cout << "Você deseja cadastrar uma nova palavra no banco do jogo? (S/N)\n";
        char letra;
        cin >> letra;
        if (letra == 'S') {
            insere_palavra();
        }
    } else {
        cout << "Você foi enforcado e perdeu! Tenta novamente...\n";
    }
}