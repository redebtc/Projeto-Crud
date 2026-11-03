#include <iostream>
#include "Portfolio.h"

using namespace std;

int main() {
    Portfolio sis;
    int op = 0;

    while (op != 7) {
        cout << "\n=== MENU PORTFOLIO CRYPTO ===" << endl;
        cout << "1. Inserir" << endl;
        cout << "2. Listar todos" << endl;
        cout << "3. Exibir um (pesquisar por nome)" << endl;
        cout << "4. Alterar (pesquisar por nome)" << endl;
        cout << "5. Remover (pesquisar por nome)" << endl;
        cout << "6. Exibir Relatorio" << endl;
        cout << "7. Sair" << endl;
        cout << "Opcao: ";
        cin >> op;
        cin.ignore();

        switch (op) {
            case 1:
                sis.inserir();
                break;
            case 2:
                sis.listarTodos();
                break;
            case 3:
                sis.exibirUm();
                break;
            case 4:
                sis.alterar();
                break;
            case 5:
                sis.remover();
                break;
            case 6:
                sis.relatorio();
                break;
            case 7:
                sis.salvarDados();
                cout << "Dados salvos! Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
                break;
        }
    }

    return 0;
}