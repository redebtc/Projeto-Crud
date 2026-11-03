#ifndef CRIPTO_H
#define CRIPTO_H

#include <iostream>
#include <string>
#include <fstream>
#include "Data.h"

using namespace std;

class Cripto {
private:
    string nome;
    string sigla;
    double qtd;
    double preco;
    Data data; 

public:
    Cripto() {
        nome = "";
        sigla = "";
        qtd = 0;
        preco = 0;
    }

    Cripto(string n, string s, double q, double p, Data d) {
        nome = n;
        sigla = s;
        qtd = q;
        preco = p;
        data = d;
    }

    virtual ~Cripto() {}

    string getNome() { return nome; }
    void setNome(string n) { nome = n; }

    string getSigla() { return sigla; }
    void setSigla(string s) { sigla = s; }

    double getQtd() { return qtd; }
    void setQtd(double q) { qtd = q; }

    double getPreco() { return preco; }
    void setPreco(double p) { preco = p; }

    Data getData() { return data; }
    void setData(Data d) { data = d; }

    double calcInvestido() {
        return qtd * preco;
    }

    virtual void exibir() {
        cout << "Nome: " << nome << " (" << sigla << ")" << endl;
        cout << "Data da compra: " << data.formatar() << endl;
        cout << "Quantidade: " << qtd << endl;
        cout << "Preco de compra: R$ " << preco << endl;
        cout << "Valor investido: R$ " << calcInvestido() << endl;
    }

    
    virtual double calcTotal() = 0;
    virtual void alterarExtra() = 0;
    virtual int getTipo() = 0;

    virtual void salvar(ofstream &arq) {
        arq << getTipo() << endl;
        arq << nome << endl;
        arq << sigla << endl;
        arq << qtd << endl;
        arq << preco << endl;
        arq << data.getDia() << " " << data.getMes() << " " << data.getAno() << endl;
    }
};

#endif