#ifndef LZW_H
#define LZW_H
#include<unordered_map>
#include <string>
#include <iostream>
#include <vector>


using namespace std;

class LZW
{
    private:
        string frase; //Frase a ser compactada
        vector<int> codigo; //C�digo gerado
        string codigoStr; //String do c�digo gerado

    public:
        LZW(string frase); //Construtor
        unordered_map<string, int> dicionario; //Dicion�rio

        void construirDicionarioASCII(); //Fun��o que constr�i dicion�rio com base na tabela ascii
        void codificar(); //Fun��o para codificar a string
        void decodificar(vector<int> codigos); //fun��o para decodificar

        void salvarArquivo();//Salva c�digo comprimido em disco

        //Gets
        string getCodigo();
        int getTamChave();
        int getTamCodigo();
        float getTaxaCompressao();

};

#endif // LZW_H
