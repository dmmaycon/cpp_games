#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int main() {
    cout << "*********************************************************\n";
    cout << "* * * * *  * BEM-VINDO AO JOGO DE ADIVINHAÇÃO * * * * * *\n";
    cout << "*********************************************************\n";

    char nivel;
    cout << "Escolha o nível de dificuldade do jogo: Facíl (F), Médio (M), Dificil (D)\n";
    cin >> nivel;

    while (nivel != 'F' and nivel != 'M' and nivel != 'D') {
        cout << "Escolha o nível de dificuldade do jogo: Facíl (F), Médio (M), Dificil (D)\n";
        cin >> nivel;
    }

    int numero_tentativa = 0;
    switch (nivel)
    {
        case 'F':
            numero_tentativa = 15;
            cout << "Nível escolhido: Facíl, você tem 15 tentativas\n";
        break;
        case 'M':
            numero_tentativa = 10;
            cout << "Nível escolhido: Médio, você tem 10 tentativas\n";
        break;
        case 'D':
            numero_tentativa = 5;
            cout << "Nível escolhido: Facíl, você tem 5 tentativas\n";
        break;
    }
    
    srand(time(NULL));
    const int NUMERO_SECRETO    = rand() % 100;

    double pontuacao = 1000.0;
    
    bool ganhou = false;
    int controle = 1;
    while ( controle <= numero_tentativa ) {
        cout << "Tentativa número " << controle << " \n";
        controle++;
        int chute;
        cout << "Digite seu chute do número secreto: \n";
        cin >> chute;

        double ponto_perdido = abs(chute - NUMERO_SECRETO) / 2.0;
        pontuacao -= ponto_perdido;

        if (chute > NUMERO_SECRETO) {
            cout << "Número digitado foi maior que o número secreto \n";
        } else if (chute < NUMERO_SECRETO) {
            cout << "Número digitado foi menor que o número secreto \n";
        } else {
            cout << "Parabéns, o número digitado foi igual ao número secreto! \n";
            ganhou = true;
            break;
        }
    }

    if (!ganhou) {
        cout << "Suas chances acabaram, e você perdeu... \n";
        cout << "O número secreto era: " << NUMERO_SECRETO << "\n";
    }
    cout.precision(2);
    cout << fixed;
    cout << "Fim de jogo, sua pontuação final foi de: " << pontuacao << "\n";
}