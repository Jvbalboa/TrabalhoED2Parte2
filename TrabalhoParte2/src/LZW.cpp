#include "LZW.h"
#include<unordered_map>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>


using namespace std;

LZW::LZW(string frase)
{
    construirDicionarioASCII();
    this->frase = frase;
    codificar();

    //decodificar(codigo);

    for(unsigned int i=0; i<codigo.size(); i++)
        codigoStr += to_string(codigo[i]);

}
//Constroi o dicionario utilizando os valores da tabela ASCII
void LZW::construirDicionarioASCII()
{
    string x;
    for(int i = 0; i <= 255; i++)
    {
        x = (char) i;
        dicionario.insert(make_pair(x,i));

    }
    for(auto z = dicionario.begin(); z != dicionario.end(); z++)
    {
       //cout << z->first << " ----- " << z->second << endl;
    }
}
//Função de codificação
void LZW::codificar()
{
    //cout << "Iniciando compressao de " << frase << endl << endl;
    int novoCod = 257;
    string seq;
    seq += frase[0];
    for(unsigned int i = 1; i <= frase.size(); i++)
    {
        char c = frase[i];
        //Existe no dicionario, adciona o c na sequencia
        if(dicionario.count(seq+c) > 0)
        {
            //cout << "\nSequencia " << seq + c << " contida no dicionario, prosseguindo na compressao.\n" << endl;
            seq += c;
        }
        //Não existe no dicionario, adciona a sequencia
        else
        {
            auto indice = dicionario.find(seq);
            //cout << "Adicionando a sequencia " << seq << " (" << indice->second << ")" << " para o vetor de codigos." << endl;
            codigo.push_back(indice->second); //Adciona no vetor de codigo
            //cout << "Adicionando no dicionario o codigo " << novoCod << " para o texto "<< seq+c << endl;;
            dicionario.insert(make_pair(seq+c, novoCod)); //Adciona no dicionario
            novoCod++;
            seq = c;

        }
    }
    //cout << "Segue sequencia de codigos: " << endl;
    //for(int i = 0; i < codigo.size(); i++)
        //cout << codigo[i] << endl;
}

/*void LZW::decodificar(vector<int> codigos)
{
    cout << "Iniciando decodificacao: \n\n";
    int novoCod = 257;
    string stringOld;
    string stringNew;
    stringOld = codigos[0];
    dicionario.insert(make_pair(novoCod, stringOld));
    cout << stringOld;

    for(int i = 1; i < codigos.size(); i++)
    {

        stringNew = dicionario[codigos[i]];
        dicionario[novoCod] += stringNew[0];
        novoCod++;
        dicionario.insert(make_pair(novoCod,stringNew));
        stringNew = dicionario[codigos[i]];
        cout << stringNew;

    }
    for (int i= 257; i <262; i++)
    {
        cout << endl<< i << " " << dicionario[i];
    }

}*/

//Função pra salvar em arquivo a saida comprimida
void LZW::salvarArquivo()
{
    ofstream arqc;
    arqc.open("saidaComprimidaLZW.txt");
    if(arqc)
    {
        arqc << codigoStr;
        arqc.close();
    }
    else
        cout << "Nao foi possivel salvar arquivo" << endl;
}

//gets
string LZW::getCodigo()
{
    return codigoStr;
}
int LZW::getTamChave()
{
    return frase.size();
}

int LZW::getTamCodigo()
{
    return codigoStr.size();
}

//Calcula taxa de compressao
float LZW::getTaxaCompressao()
{
    float aux = codigoStr.size();
    aux = aux/frase.size();
    return aux;
}
