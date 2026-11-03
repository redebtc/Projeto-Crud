#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include "Cripto.h"
#include "Hold.h"
#include "Staking.h"

using namespace std;

class Portfolio {
private:
    vector<Cripto*> lista;

   
    string minusculo(string txt) {
        for (int i = 0; i < (int)txt.size(); i++) {
            txt[i] = tolower(txt[i]);
        }
        return txt;
    }

public:
    Portfolio() {
        carregarDados();
    }

    ~Portfolio() {
        for (int i = 0; i < (int)lista.size(); i++) {
            delete lista[i];
        }
        lista.clear();
    }


    int Pesquisar(string nome) {
        if (nome == "") return -1;

        string busca = minusculo(nome);
        vector<int> achados;

        for (int i = 0; i < (int)lista.size(); i++) {
            string nomeItem = minusculo(lista[i]->getNome());

            
            if (nomeItem.find(busca) == 0) {
                achados.push_back(i);
            }
        }

        if (achados.size() == 0) {
            return -1;
        }

       
        if (achados.size() == 1) {
            return achados[0];
        }

        
        cout << "\nMais de um ativo encontrado com esse nome:" << endl;
        for (int i = 0; i < (int)achados.size(); i++) {
            int ind = achados[i];
            cout << "Indice [" << ind << "] - " << lista[ind]->getNome()
                 << " (" << lista[ind]->getSigla() << ") | Qtd: " << lista[ind]->getQtd() << endl;
        }

        int esc;
        cout << "Digite o indice que deseja selecionar: ";
        cin >> esc;
        cin.ignore();

        for (int i = 0; i < (int)achados.size(); i++) {
            if (achados[i] == esc) {
                return esc;
            }
        }

        cout << "Indice invalido!" << endl;
        return -1;
    }

   
    void inserir() {
        int tipo;
        cout << "\n--- INSERIR CRIPTO ---" << endl;
        cout << "1 - Moeda em Hold (Carteira)" << endl;
        cout << "2 - Moeda em Staking (Rendendo)" << endl;
        cout << "Tipo: ";
        cin >> tipo;
        cin.ignore();

        if (tipo != 1 && tipo != 2) {
            cout << "Opcao invalida!" << endl;
            return;
        }

        string nome, sigla;
        double qtd, preco;
        int d, m, a;

        cout << "Nome da moeda (ex: Bitcoin): ";
        getline(cin, nome);
        cout << "Sigla (ex: BTC): ";
        getline(cin, sigla);
        cout << "Quantidade: ";
        cin >> qtd;
        cout << "Preco de compra (R$): ";
        cin >> preco;
        cout << "Data da compra (dia mes ano separados por espaco): ";
        cin >> d >> m >> a;
        cin.ignore();

        Data dt(d, m, a);

        if (tipo == 1) {
            string carteira;
            double taxa;
            cout << "Nome da carteira: ";
            getline(cin, carteira);
            cout << "Taxa de rede (R$): ";
            cin >> taxa;
            cin.ignore();

            lista.push_back(new Hold(nome, sigla, qtd, preco, dt, carteira, taxa));
        } else {
            string plat;
            double lucro;
            cout << "Plataforma de Staking: ";
            getline(cin, plat);
            cout << "Rendimento anual (%): ";
            cin >> lucro;
            cin.ignore();

            lista.push_back(new Staking(nome, sigla, qtd, preco, dt, plat, lucro));
        }

        cout << "Cadastrado com sucesso!" << endl;
    }

   
    void listarTodos() {
        cout << "\n--- LISTA DE CRIPTOS ---" << endl;
        if (lista.size() == 0) {
            cout << "Nenhuma cripto cadastrada." << endl;
            return;
        }

        for (int i = 0; i < (int)lista.size(); i++) {
            cout << "\n--- Item [" << i << "] ---" << endl;
            lista[i]->exibir();
        }
    }

    
    void exibirUm() {
        cout << "\n--- EXIBIR UM ---" << endl;
        string busca;
        cout << "Digite o nome para pesquisar: ";
        getline(cin, busca);

        int ind = Pesquisar(busca);
        if (ind == -1) {
            cout << "Nao encontrado!" << endl;
        } else {
            cout << endl;
            lista[ind]->exibir();
        }
    }

   
    void alterar() {
        cout << "\n--- ALTERAR CRIPTO ---" << endl;
        string busca;
        cout << "Digite o nome da cripto para alterar: ";
        getline(cin, busca);

        int ind = Pesquisar(busca);
        if (ind == -1) {
            cout << "Nao encontrado!" << endl;
            return;
        }

        string nome, sigla;
        double qtd, preco;
        int d, m, a;

        cout << "Novo nome (atual: " << lista[ind]->getNome() << "): ";
        getline(cin, nome);
        cout << "Nova sigla (atual: " << lista[ind]->getSigla() << "): ";
        getline(cin, sigla);
        cout << "Nova quantidade (atual: " << lista[ind]->getQtd() << "): ";
        cin >> qtd;
        cout << "Novo preco (atual: " << lista[ind]->getPreco() << "): ";
        cin >> preco;
        cout << "Nova data - dia mes ano (atual: " << lista[ind]->getData().formatar() << "): ";
        cin >> d >> m >> a;
        cin.ignore();

        lista[ind]->setNome(nome);
        lista[ind]->setSigla(sigla);
        lista[ind]->setQtd(qtd);
        lista[ind]->setPreco(preco);
        lista[ind]->setData(Data(d, m, a));

        lista[ind]->alterarExtra();

        cout << "Alterado com sucesso!" << endl;
    }

   
    void remover() {
        cout << "\n--- REMOVER CRIPTO ---" << endl;
        string busca;
        cout << "Digite o nome da cripto para remover: ";
        getline(cin, busca);

        int ind = Pesquisar(busca);
        if (ind == -1) {
            cout << "Nao encontrado!" << endl;
            return;
        }

        delete lista[ind];
        lista.erase(lista.begin() + ind);
        cout << "Removido com sucesso!" << endl;
    }

   
    void relatorio() {
        cout << "\n--- RELATORIO DO PORTFOLIO ---" << endl;
        if (lista.size() == 0) {
            cout << "Portfolio vazio." << endl;
            return;
        }

        int contHold = 0, contStaking = 0;
        double somaInvestido = 0, somaEstimado = 0;

        for (int i = 0; i < (int)lista.size(); i++) {
            if (lista[i]->getTipo() == 1) {
                contHold++;
            } else {
                contStaking++;
            }
            somaInvestido += lista[i]->calcInvestido();
            somaEstimado += lista[i]->calcTotal();
        }

        cout << "Quantidade total de ativos: " << lista.size() << endl;
        cout << " -> Em Hold: " << contHold << endl;
        cout << " -> Em Staking: " << contStaking << endl;
        cout << "Valor total investido: R$ " << somaInvestido << endl;
        cout << "Valor total estimado (com taxas/rendimentos): R$ " << somaEstimado << endl;
        cout << "Diferenca projetada: R$ " << (somaEstimado - somaInvestido) << endl;
    }

   
    void salvarDados() {
        ofstream arq("dados.txt");
        if (!arq.is_open()) return;

        for (int i = 0; i < (int)lista.size(); i++) {
            lista[i]->salvar(arq);
        }
        arq.close();
    }

   
    void carregarDados() {
        ifstream arq("dados.txt");
        if (!arq.is_open()) return;

        int tipo;
        while (arq >> tipo) {
            arq.ignore();
            string nome, sigla, extraTxt;
            double qtd, preco, extraNum;
            int d, m, a;

            getline(arq, nome);
            getline(arq, sigla);
            arq >> qtd >> preco >> d >> m >> a;
            arq.ignore();
            getline(arq, extraTxt);
            arq >> extraNum;
            arq.ignore();

            Data dt(d, m, a);

            if (tipo == 1) {
                lista.push_back(new Hold(nome, sigla, qtd, preco, dt, extraTxt, extraNum));
            } else if (tipo == 2) {
                lista.push_back(new Staking(nome, sigla, qtd, preco, dt, extraTxt, extraNum));
            }
        }
        arq.close();
    }
};

#endif