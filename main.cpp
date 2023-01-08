#include <iostream>
#include <string.h>
#include <iomanip>
#include <locale.h>
#include <fstream>

#include "AVL.hpp"

using namespace std;
int main()
{
    No *arvore;
    No *palavraBuscada;
    hqs *banca;
    string nomeHq;
    string palavra;
    int qtd;
    ofstream arquivo;
    /*arquivo.open("Palavras01(1).txt", ios::app);

   arquivo.close();*/
    banca = NULL;
    palavraBuscada = NULL;
    arvore = NULL;
    cout<<"Quantas histórias de quadrinhos você deseja pesquisar";
    cin>>qtd;   
    for (int i = 0; i < qtd; i++)
    {
        
        cout << "Digite o nome da HQ: ";

        cin >> nomeHq;

        banca = inserirHqs(nomeHq, banca);
    }
    arvore = lerArquivo(banca, arvore);
    for (;;)
    {
        cout << "Digite a palavra que deseja buscar: ";
        cin >> palavra;

        palavraBuscada = buscarPalavra(arvore, palavra, banca);
        if (palavraBuscada == NULL)
        {
            cout << "Palavra não encontrada" << endl;
        }
        else
        {
            cout << "--------------------------------------------------" << endl;

            cout << "A palavra encontrada foi: " << palavraBuscada->palavra << endl;
            cout << "Quantidade de vezes foi:" << palavraBuscada->qtdOcorrencia << endl;
            cout << "Encontrada nos arquivos:";
            while (palavraBuscada->listaHqs != NULL)
            {
                cout << palavraBuscada->listaHqs->titulo << " ";
                palavraBuscada->listaHqs = palavraBuscada->listaHqs->prox;
            }
            cout << palavraBuscada->listaHqs->titulo << endl;
            cout << "--------------------------------------------------" << endl;
                

            while (palavraBuscada->listaHqs->ant != NULL)
            {
                palavraBuscada->listaHqs = palavraBuscada->listaHqs->ant;
            }
        }
    }

    return 0;
}