#include <iostream>
#include <cstring>
#include <locale.h>
#include <fstream>
#define TAM 10
using namespace std;
struct hqs
{
    string titulo;
    int codigo;
    struct hqs *prox;
    struct hqs *ant;
    /* data */
};

hqs *criaNoHqs()
{
    hqs *novaHq;
    novaHq = new hqs;
    novaHq->ant = NULL;
    novaHq->prox = NULL;
    return novaHq;
}

hqs *inserirHqs(string titulo, hqs *banca)
{
    hqs *novo;

    hqs *auxBanca;

    hqs *ant = NULL;

    auxBanca = banca;

    novo = criaNoHqs();

    novo->titulo = titulo;

    if (auxBanca == NULL)
    {
        novo->codigo = 1;
        auxBanca = novo;
    }
    else
    {
        if (auxBanca->prox == NULL)
        {
            auxBanca->prox = novo;
            novo->ant = auxBanca;
            novo->codigo = auxBanca->codigo + 1;
        }
        else
        {
            while (auxBanca->prox != NULL)
            {
                ant = auxBanca;
                auxBanca = auxBanca->prox;
            }
            auxBanca->prox = novo;
            novo->ant = ant;
            novo->codigo = auxBanca->codigo + 1;
        }
    }
    while (auxBanca->ant != NULL)
    {
        auxBanca = auxBanca->ant;
    }
    return auxBanca;
}
struct No
{
    char *palavra;
    int qtdOcorrencia;
    int codHq[TAM];
    hqs *listaHqs;
    struct No *esq;
    struct No *dir;
};

No *criaNoArvore(char *palavra)
{
    No *novoNo;
    int i;
    novoNo = new No;

    novoNo->palavra = palavra;

    novoNo->dir = NULL;

    novoNo->esq = NULL;

    novoNo->listaHqs = NULL;

    novoNo->qtdOcorrencia = 1;

    for (i = 0; i < TAM; i++)
    {
        novoNo->codHq[i] = 0;
    }
    return novoNo;
}

char *convertePalavra(string palavra, int tam)
{
    char *palavraH;

    palavraH = new char[tam + 1];

    strcpy(palavraH, palavra.c_str());

    for (int i = 0; i <= tam; i++)
    {

        palavraH[i] = toupper(palavraH[i]);
    }

    return palavraH;
}
No *inserirPalavra(No *arvore, char *novaPalavra, int codigo)
{
    No *novoNo;
    if (arvore == NULL)
    {
        novoNo = criaNoArvore(novaPalavra);
        arvore = novoNo;
        arvore->codHq[codigo - 1] = codigo;
    }
    else
    {
        if (strcmp(arvore->palavra, novaPalavra) == 0)
        {
            arvore->qtdOcorrencia++;
            arvore->codHq[codigo - 1] = codigo;
        }
        else if (strcmp(arvore->palavra, novaPalavra) < 0)
        {
            arvore->dir = inserirPalavra(arvore->dir, novaPalavra, codigo);
        }
        else if (strcmp(arvore->palavra, novaPalavra) > 0)
        {
            arvore->esq = inserirPalavra(arvore->esq, novaPalavra, codigo);
        }
    }

    return arvore;
}
No *inserirInfoLista(No *palavra, hqs *banca)
{
    while (banca != NULL)
    {
        for (int i = 0; i < TAM; i++)
        {
            if (palavra->codHq[i] == banca->codigo)
            {
                palavra->listaHqs = inserirHqs(banca->titulo, palavra->listaHqs);
            }
        }
        banca = banca->prox;
    }
    while (palavra->listaHqs->prox != NULL)
    {
        palavra->listaHqs->codigo = -1;
        palavra->listaHqs = palavra->listaHqs->prox;
    }
    palavra->listaHqs->codigo = -1;
    while (palavra->listaHqs->ant != NULL)
    {
        palavra->listaHqs = palavra->listaHqs->ant;
    }
    return palavra;
}
No *buscarPalavra(No *arvore, string palavra, hqs *banca)
{
    char *palavraH;
    palavraH = convertePalavra(palavra, palavra.length());
    if (arvore == NULL)
    {
        return NULL;
    }
    else
    {
        if (strcmp(arvore->palavra, palavraH) == 0)
        {
            if (arvore->listaHqs == NULL)
            {
                arvore = inserirInfoLista(arvore, banca);
            }
            return arvore;
        }
        else if (strcmp(arvore->palavra, palavraH) < 0)
        {
            return buscarPalavra(arvore->dir, palavra, banca);
        }
        else if (strcmp(arvore->palavra, palavraH) > 0)
        {
            return buscarPalavra(arvore->esq, palavra, banca);
        }
    }
    return NULL;
}
No *lerArquivo(hqs *banca, No *arvore)
{
    setlocale(LC_ALL, "");
    ifstream arquivoEntrada;
    string palavraS;
    string dado;
    char *palavraH;
    while (banca != NULL)
    {
        arquivoEntrada.open(banca->titulo);
        if (arquivoEntrada.is_open())
        {
            while (getline(arquivoEntrada, palavraS, ' '))
            {
                
                if (palavraS == "")
                {
                    continue;
                }
                palavraH = convertePalavra(palavraS, palavraS.length());
                arvore = inserirPalavra(arvore, palavraH, banca->codigo);
            }

            arquivoEntrada.close();
        }
        else
        {
            cout << "Não foi possível abrir o arquivo" << endl;
        }
        cout << "--------------------------------------------------" << endl;
        banca = banca->prox;
    }
    return arvore;
}
