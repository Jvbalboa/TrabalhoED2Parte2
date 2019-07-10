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
    //Vari�veis comuns
    LeituraDaBase leitor; //Inst�ncia da classe de leitura
    double *comparacoes = new double(); //Vari�vel que guarda o n�mero de compara��es
    double *copias = new double(); //Vari�vel que guarda o n�mero de c�pias de registro

    //Loop que executa 5 vezes, gerando bases diferentes para cada N definido pelo arquivo de texto
    for(int cont=1; cont<=totalSeeds; cont++)
    {
        cout << "Execucao: " << cont << "..." << endl;

        //Abrindo arquivo com valores para N
        fstream arq;
        arq.open("entrada.txt");
        if(arq)
        {
            //Criando arquivo para salvar estat�sticas de inser��o
            ofstream arqSaidaInsercao;
            string saidaInsercao = "saidaInsercaoSeed" + to_string(cont) + ".txt"; //Para cada execu��o, gera uma sa�da diferente com o n�mero desta
            arqSaidaInsercao.open(saidaInsercao);

            if(arqSaidaInsercao)
            {

                //Criando arquivo para salvar estat�sticas de busca
                ofstream arqSaidaBusca;
                string saidaBusca = "saidaBuscaSeed" + to_string(cont) + ".txt"; //Para cada execu��o, gera uma sa�da diferente com o n�mero desta
                arqSaidaBusca.open(saidaBusca);

                if(arqSaidaBusca)
                {
                    //Para cada N, l� a base no vetor, insere e busca nas �rvores
                    while(!arq.eof())
                    {
                        //Instanciando as �rvores
                        ArvoreB b2(2); //�rvore B de grau 2
                        ArvoreB b20(20); //�rvore B de grau 20
                        ArvoreVP vp;

                        //Lendo tamanho do vetor
                        string linha;
                        getline(arq, linha);
                        int n = stoi(linha);

                        //Aloca��o de mem�ria
                        Rating *base = new  Rating[n];

                        //Lendo n linhas da base
                        leitor.leBase(base, n);

                        //Embaralhando a base
                        //embaralha(base, n);

                        //Inser��o
                        arqSaidaInsercao << "N: " << n << endl; //Imprime o tamanho do vetor no arquivo de sa�da da inser��o

                        //Zerando os contadores
                        *comparacoes = 0;
                        *copias = 0;

                        //Inserindo na �rvore B de grau 2
                        auto inicio = high_resolution_clock::now();
                        for(int i=0; i<n; i++)
                            b2.insere(base[i], comparacoes, copias);
                        auto resultado = high_resolution_clock::now() - inicio;
                        double tempo = duration_cast<nanoseconds >(resultado).count();

                        arqSaidaInsercao << "Arvore-B(2): \n" << "Tempo: " << tempo/1000000000 << "\nCompara��es: " << *comparacoes << "\nC�pias: " << *copias << endl;

                        //Zerando os contadores
                        *comparacoes = 0;
                        *copias = 0;

                        //Inserindo na �rvore B de grau 20
                        inicio = high_resolution_clock::now();
                        for(int i=0; i<n; i++)
                            b20.insere(base[i], comparacoes, copias);
                        resultado = high_resolution_clock::now() - inicio;
                        tempo = duration_cast<nanoseconds >(resultado).count();

                        arqSaidaInsercao << "Arvore-B(20): \n" << "Tempo: " << tempo/1000000000 << "\nCompara��es: " << *comparacoes << "\nC�pias: " << *copias << endl;

                        //Zerando os contadores
                        *comparacoes = 0;

                        //Inserindo na �rvore Vermelha e Preta
                        inicio = high_resolution_clock::now();
                        for(int i=0; i<n; i++)
                            vp.insere(base[i], comparacoes);
                        resultado = high_resolution_clock::now() - inicio;
                        tempo = duration_cast<nanoseconds >(resultado).count();

                        arqSaidaInsercao << "Arvore-VP: \n" << "Tempo: " << tempo/1000000000 << "\nCompara��es: " << *comparacoes << endl;


                        //Busca
                        arqSaidaBusca << "N: " << n << endl; //Imprime o tamanho do vetor no arquivo de sa�da da busca

                        //Zerando os contadores
                        *comparacoes = 0;

                        //Buscando na �rvore B de grau 2
                        inicio = high_resolution_clock::now();
                        for(int i=0; i<n; i++)
                            b2.busca(base[i], comparacoes);
                        resultado = high_resolution_clock::now() - inicio;
                        tempo = duration_cast<nanoseconds >(resultado).count();

                        arqSaidaBusca << "Arvore-B(2): \n" << "Tempo: " << tempo/1000000000 << "\nCompara��es: " << *comparacoes << endl;

                        //Zerando os contadores
                        *comparacoes = 0;

                        //Buscando na �rvore B de grau 20
                        inicio = high_resolution_clock::now();
                        for(int i=0; i<n; i++)
                            b20.busca(base[i], comparacoes);
                        resultado = high_resolution_clock::now() - inicio;
                        tempo = duration_cast<nanoseconds >(resultado).count();

                        arqSaidaBusca << "Arvore-B(20): \n" << "Tempo: " << tempo/1000000000 << "\nCompara��es: " << *comparacoes << endl;

                        //Zerando os contadores
                        *comparacoes = 0;

                        //Buscando na �rvore Vermelha e Preta
                        inicio = high_resolution_clock::now();
                        for(int i=0; i<n; i++)
                            vp.busca(base[i], comparacoes);
                        resultado = high_resolution_clock::now() - inicio;
                        tempo = duration_cast<nanoseconds >(resultado).count();

                        arqSaidaBusca << "Arvore-VP: \n" << "Tempo: " << tempo/1000000000 << "\nCompara��es: " << *comparacoes << endl;


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
