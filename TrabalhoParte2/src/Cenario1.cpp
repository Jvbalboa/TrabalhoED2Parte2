#include "Cenario1.h"

#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;
using namespace chrono;

Cenario1::Cenario1()
{
    //ctor
}

void Cenario1::execucao(int totalSeeds)
{
    //Variáveis comuns
    LeituraDaBase leitor; //Instância da classe de leitura
    double *comparacoes = new double(); //Variável que guarda o número de comparações
    double *copias = new double(); //Variável que guarda o número de cópias de registro

    //Loop que executa 5 vezes, gerando bases diferentes para cada N definido pelo arquivo de texto
    for(int cont=1; cont<=totalSeeds; cont++)
    {
        cout << "Execucao: " << cont << "..." << endl;

        //Abrindo arquivo com valores para N
        fstream arq;
        arq.open("entrada.txt");
        if(arq)
        {
            //Criando arquivo para salvar estatísticas de inserção
            ofstream arqSaidaInsercao;
            string saidaInsercao = "saidaInsercaoSeed" + to_string(cont) + ".txt"; //Para cada execução, gera uma saída diferente com o número desta
            arqSaidaInsercao.open(saidaInsercao);

            if(arqSaidaInsercao)
            {

                //Criando arquivo para salvar estatísticas de busca
                ofstream arqSaidaBusca;
                string saidaBusca = "saidaBuscaSeed" + to_string(cont) + ".txt"; //Para cada execução, gera uma saída diferente com o número desta
                arqSaidaBusca.open(saidaBusca);

                if(arqSaidaBusca)
                {
                    //Para cada N, lê a base no vetor, insere e busca nas árvores
                    while(!arq.eof())
                    {
                        //Instanciando as árvores
                        ArvoreB b2(2); //Árvore B de grau 2
                        ArvoreB b20(20); //Árvore B de grau 20
                        ArvoreVP vp;

                        //Lendo tamanho do vetor
                        string linha;
                        getline(arq, linha);
                        int n = stoi(linha);

                        //Alocação de memória
                        Rating *base = new  Rating[n];

                        //Lendo n linhas da base
                        leitor.leBase(base, n);

                        //Embaralhando a base
                        //embaralha(base, n);

                        //Inserção
                        arqSaidaInsercao << "N: " << n << endl; //Imprime o tamanho do vetor no arquivo de saída da inserção

                        //Zerando os contadores
                        *comparacoes = 0;
                        *copias = 0;

                        //Inserindo na Árvore B de grau 2
                        auto inicio = high_resolution_clock::now();
                        for(int i=0; i<n; i++)
                            b2.insere(base[i], comparacoes, copias);
                        auto resultado = high_resolution_clock::now() - inicio;
                        double tempo = duration_cast<nanoseconds >(resultado).count();

                        arqSaidaInsercao << "Arvore-B(2): \n" << "Tempo: " << tempo/1000000000 << "\nComparações: " << *comparacoes << "\nCópias: " << *copias << endl;

                        //Zerando os contadores
                        *comparacoes = 0;
                        *copias = 0;

                        //Inserindo na Árvore B de grau 20
                        inicio = high_resolution_clock::now();
                        for(int i=0; i<n; i++)
                            b20.insere(base[i], comparacoes, copias);
                        resultado = high_resolution_clock::now() - inicio;
                        tempo = duration_cast<nanoseconds >(resultado).count();

                        arqSaidaInsercao << "Arvore-B(20): \n" << "Tempo: " << tempo/1000000000 << "\nComparações: " << *comparacoes << "\nCópias: " << *copias << endl;

                        //Zerando os contadores
                        *comparacoes = 0;

                        //Inserindo na Árvore Vermelha e Preta
                        inicio = high_resolution_clock::now();
                        for(int i=0; i<n; i++)
                            vp.insere(base[i], comparacoes);
                        resultado = high_resolution_clock::now() - inicio;
                        tempo = duration_cast<nanoseconds >(resultado).count();

                        arqSaidaInsercao << "Arvore-VP: \n" << "Tempo: " << tempo/1000000000 << "\nComparações: " << *comparacoes << endl;


                        //Busca
                        arqSaidaBusca << "N: " << n << endl; //Imprime o tamanho do vetor no arquivo de saída da busca

                        //Zerando os contadores
                        *comparacoes = 0;

                        //Buscando na Árvore B de grau 2
                        inicio = high_resolution_clock::now();
                        for(int i=0; i<n; i++)
                            b2.busca(base[i], comparacoes);
                        resultado = high_resolution_clock::now() - inicio;
                        tempo = duration_cast<nanoseconds >(resultado).count();

                        arqSaidaBusca << "Arvore-B(2): \n" << "Tempo: " << tempo/1000000000 << "\nComparações: " << *comparacoes << endl;

                        //Zerando os contadores
                        *comparacoes = 0;

                        //Buscando na Árvore B de grau 20
                        inicio = high_resolution_clock::now();
                        for(int i=0; i<n; i++)
                            b20.busca(base[i], comparacoes);
                        resultado = high_resolution_clock::now() - inicio;
                        tempo = duration_cast<nanoseconds >(resultado).count();

                        arqSaidaBusca << "Arvore-B(20): \n" << "Tempo: " << tempo/1000000000 << "\nComparações: " << *comparacoes << endl;

                        //Zerando os contadores
                        *comparacoes = 0;

                        //Buscando na Árvore Vermelha e Preta
                        inicio = high_resolution_clock::now();
                        for(int i=0; i<n; i++)
                            vp.busca(base[i], comparacoes);
                        resultado = high_resolution_clock::now() - inicio;
                        tempo = duration_cast<nanoseconds >(resultado).count();

                        arqSaidaBusca << "Arvore-VP: \n" << "Tempo: " << tempo/1000000000 << "\nComparações: " << *comparacoes << endl;


                        delete []base;
                    }

                    arqSaidaBusca.close();
                }
                else
                    cout << "Nao foi possivel criar o arquivo de saida da busca" << endl;

                arqSaidaInsercao.close();
            }
            else
                cout << "Nao foi possivel criar o arquivo de saida da insercao" << endl;

            arq.close();
        }
        else
            cout << "Nao foi possivel abrir o arquivo de entrada" << endl;
    }

}
