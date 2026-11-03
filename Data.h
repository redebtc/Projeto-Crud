#ifndef DATA_H
#define DATA_H

#include <string>

using namespace std;

class Data {
private:
    int dia;
    int mes;
    int ano;

public:
    Data() {
        dia = 1;
        mes = 1;
        ano = 2026;
    }

    Data(int d, int m, int a) {
        dia = d;
        mes = m;
        ano = a;
    }

    int getDia() { return dia; }
    int getMes() { return mes; }
    int getAno() { return ano; }

    void setData(int d, int m, int a) {
        dia = d;
        mes = m;
        ano = a;
    }

    string formatar() {
        return to_string(dia) + "/" + to_string(mes) + "/" + to_string(ano);
    }
};

#endif