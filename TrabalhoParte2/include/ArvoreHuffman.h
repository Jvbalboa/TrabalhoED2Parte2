#ifndef ARVOREHUFFMAN_H
#define ARVOREHUFFMAN_H
#include "NoHuffman.h"
#include <iostream>


using namespace std;


class ArvoreHuffman
{
    public:
        ArvoreHuffman(string frase); //Constutor
        ~ArvoreHuffman(); //Destrutor

        //Gets
        string getCodigo();
        int getTamChave();
        int getTamCodigo();
        float getTaxaCompressao();

    private:
        string chave; //Chave a ser codificada
        string codigo; //Código gerado
        NoHuffman* raiz; //Nó raiz

        NoHuffman** alfabeto; //Nós da árvore (alfabeto)
        int* frequencia; //Vetor de frequências
        int tamAlfabeto; //Variável que guarda o tamanho do alfabeto
        string * tabela; //Tabela
        char* tabelaChar;

        //Métodos
        void auxDelete(NoHuffman* p); //Função para deletar nó

        int montarAlfabeto(string chave); //Função que monta o alfabeto
        int contem(char c, int tam); //Função que checa a existência de um caractere no alfabeto
        void montarArvore(); //Função que monta a árvore

        void insertionSortFrequencias(int n);//Calcula as frequências do alfabeto

        //Funções para criar a tabela
        void criarTabela();
        void auxCriarTabela(NoHuffman* p, string s, int* posicao);

        string criarCodigo(string s); //Função para criar o código

        //Funções para decodificar
        void decodificar(string s);
        void auxDecodificar(NoHuffman* p, string s, unsigned int posicao);

        void salvarArquivo(); //salva código comprimido

};

#endif // ARVOREHUFFMAN_H
