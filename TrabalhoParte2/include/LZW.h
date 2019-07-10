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
        vector<int> codigo; //Código gerado
        string codigoStr; //String do código gerado

    public:
        LZW(string frase); //Construtor
        unordered_map<string, int> dicionario; //Dicionário

        void construirDicionarioASCII(); //Função que constrói dicionário com base na tabela ascii
        void codificar(); //Função para codificar a string
        void decodificar(vector<int> codigos); //função para decodificar

        void salvarArquivo();//Salva código comprimido em disco

        //Gets
        string getCodigo();
        int getTamChave();
        int getTamCodigo();
        float getTaxaCompressao();

};

#endif // LZW_H
