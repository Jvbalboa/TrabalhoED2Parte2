#include "Cenario2.h"

#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;
using namespace chrono;

Cenario2::Cenario2()
{
    //ctor
}

void Cenario2::execucao(int totalSeeds)
{
    //Vari�veis comuns
    LeituraDaBase leitor; //Inst�ncia da classe de leitura

    //Loop que executa 5 vezes, gerando bases diferentes para cada N definido pelo arquivo de texto
    for(int cont=1; cont<=totalSeeds; cont++)
    {
        cout << "Execucao: " << cont << "..." << endl;

        //Abrindo arquivo com valores para N
        fstream arq;
        arq.open("entrada2.txt");
        if(arq)
        {
            //Criando arquivo para salvar estat�sticas
            ofstream arqSaida;
            string saida = "saidaSeed" + to_string(cont) + ".txt"; //Para cada execu��o, gera uma sa�da diferente com o n�mero desta
            arqSaida.open(saida);

            if(arqSaida)
            {
                //Para cada N, l� a base no vetor, insere e busca nas �rvores
                while(!arq.eof())
                {
                    //Lendo tamanho do vetor
                    string linha;
                    getline(arq, linha);
                    int n = stoi(linha);

                    //Lendo a base
                    string *str = new string();
                    leitor.leArquivo(str, n);
                    string chave = *str;

                    //Compress�o
                    arqSaida << "N: " << n << endl; //Imprime o n�mero de linhas no arquivo de sa�da
                    arqSaida << "Tamanho da chave: " << chave.size() << endl;

                    //Comprimindo
                    //LZW
                    auto inicio = high_resolution_clock::now();
                    LZW *lzw = new LZW(chave);
                    auto resultado = high_resolution_clock::now() - inicio;
                    double tempo = duration_cast<nanoseconds >(resultado).count();
                    arqSaida << "LZW: \nTempo: " << tempo/1000000000 << "\nTamanho do c�digo: " << lzw->getTamCodigo() << "\nTaxa de Compress�o: " << lzw->getTaxaCompressao() << endl;

                    //Huffman
                    inicio = high_resolution_clock::now();
                    ArvoreHuffman *huffman = new ArvoreHuffman(chave);
                    resultado = high_resolution_clock::now() - inicio;
                    tempo = duration_cast<nanoseconds >(resultado).count();
                    arqSaida << "Huffman: \nTempo: " << tempo/1000000000 << "\nTamanho do c�digo: " << huffman->getTamCodigo() << "\nTaxa de Compress�o: " << huffman->getTaxaCompressao() << endl;

                    delete str;
                    delete lzw;
                    delete huffman;
                }

                arqSaida.close();
            }
            else
                cout << "Nao foi possivel criar o arquivo de saida" << endl;

        }
        else
            cout << "Nao foi possivel abrir o arquivo de entrada" << endl;

    }

}
