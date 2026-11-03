#ifndef STAKING_H
#define STAKING_H

#include "Cripto.h"

using namespace std;

class Staking : public Cripto {
private:
    string plataforma; 
    double lucroAnual; 

public:
    Staking() : Cripto() {
        plataforma = "";
        lucroAnual = 0;
    }

    Staking(string n, string s, double q, double p, Data d, string plat, double lucro)
        : Cripto(n, s, q, p, d) {
        plataforma = plat;
        lucroAnual = lucro;
    }

    void exibir() override {
        cout << "[Tipo: Staking / Renda Passiva]" << endl;
        Cripto::exibir();
        cout << "Plataforma: " << plataforma << endl;
        cout << "Rendimento anual: " << lucroAnual << "%" << endl;
        cout << "Valor estimado em 1 ano: R$ " << calcTotal() << endl;
    }

    double calcTotal() override {
        double inv = calcInvestido();
        return inv + (inv * (lucroAnual / 100.0));
    }

    void alterarExtra() override {
        cout << "Nova plataforma (atual: " << plataforma << "): ";
        getline(cin, plataforma);
        cout << "Novo rendimento anual % (atual: " << lucroAnual << "): ";
        cin >> lucroAnual;
        cin.ignore();
    }

    int getTipo() override {
        return 2;
    }

    void salvar(ofstream &arq) override {
        Cripto::salvar(arq);
        arq << plataforma << endl;
        arq << lucroAnual << endl;
    }
};

#endif