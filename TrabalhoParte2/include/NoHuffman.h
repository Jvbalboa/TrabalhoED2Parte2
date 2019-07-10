#ifndef NOHUFFMAN_H
#define NOHUFFMAN_H
#include <iostream>


using namespace std;

class NoHuffman
{
    private:
        char ch; //Caractere
        int freq; //Frequência
        NoHuffman* esq; //Filho a esquerda
        NoHuffman* dir; //Filho a direita

    public:
        NoHuffman(char chave, int frequencia); //Construtor
        bool ehFolha(); //Retorna true se é folha e false caso contrário

        //Gets e Sets
        char getChave();
        void setChave(char c);
        int getFreq();
        void setFreq(int f);
        NoHuffman* getEsq();
        void setEsq(NoHuffman* p);
        NoHuffman* getDir();
        void setDir(NoHuffman* p);

};

#endif // NOHUFFMAN_H
