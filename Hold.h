#ifndef HOLD_H
#define HOLD_H

#include "Cripto.h"

using namespace std;

class Hold : public Cripto {
private:
    string carteira; 
    double taxa;     

public:
    Hold() : Cripto() {
        carteira = "";
        taxa = 0;
    }

    Hold(string n, string s, double q, double p, Data d, string c, double t)
        : Cripto(n, s, q, p, d) {
        carteira = c;
        taxa = t;
    }

    void exibir() override {
        cout << "[Tipo: Hold / Carteira]" << endl;
        Cripto::exibir();
        cout << "Carteira: " << carteira << endl;
        cout << "Taxa de rede: R$ " << taxa << endl;
        cout << "Valor liquido (descontando taxa): R$ " << calcTotal() << endl;
    }

    double calcTotal() override {
        double total = calcInvestido() - taxa;
        if (total < 0) return 0;
        return total;
    }

    void alterarExtra() override {
        cout << "Nova carteira (atual: " << carteira << "): ";
        getline(cin, carteira);
        cout << "Nova taxa em R$ (atual: " << taxa << "): ";
        cin >> taxa;
        cin.ignore();
    }

    int getTipo() override {
        return 1;
    }

    void salvar(ofstream &arq) override {
        Cripto::salvar(arq);
        arq << carteira << endl;
        arq << taxa << endl;
    }
};

#endif