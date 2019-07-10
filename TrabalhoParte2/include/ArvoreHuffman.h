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
        string codigo; //C�digo gerado
        NoHuffman* raiz; //N� raiz

        NoHuffman** alfabeto; //N�s da �rvore (alfabeto)
        int* frequencia; //Vetor de frequ�ncias
        int tamAlfabeto; //Vari�vel que guarda o tamanho do alfabeto
        string * tabela; //Tabela
        char* tabelaChar;

        //M�todos
        void auxDelete(NoHuffman* p); //Fun��o para deletar n�

        int montarAlfabeto(string chave); //Fun��o que monta o alfabeto
        int contem(char c, int tam); //Fun��o que checa a exist�ncia de um caractere no alfabeto
        void montarArvore(); //Fun��o que monta a �rvore

        void insertionSortFrequencias(int n);//Calcula as frequ�ncias do alfabeto

        //Fun��es para criar a tabela
        void criarTabela();
        void auxCriarTabela(NoHuffman* p, string s, int* posicao);

        string criarCodigo(string s); //Fun��o para criar o c�digo

        //Fun��es para decodificar
        void decodificar(string s);
        void auxDecodificar(NoHuffman* p, string s, unsigned int posicao);

        void salvarArquivo(); //salva c�digo comprimido

};

#endif // ARVOREHUFFMAN_H
