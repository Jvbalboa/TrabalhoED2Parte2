#include "ArvoreHuffman.h"
#include "NoHuffman.h"
#include <iostream>
#include <fstream>

using namespace std;

//O constutor incializa a chave com o valor recebido, cria o alfabeto, calcula a frequ�cia, monta a �rvore e codifica a chave
ArvoreHuffman::ArvoreHuffman(string frase)
{
    chave = frase;
    alfabeto = new NoHuffman*[chave.size()](); //Aloca mem�ria para o alfabeto
    frequencia = new int[chave.size()](); //Aloca mem�ria para as frequ�ncias
    tamAlfabeto = montarAlfabeto(chave); //Monta o alfabeto
    tabelaChar = new char[tamAlfabeto](); //Aloca mem�ria para a tabela
    tabela = new string[tamAlfabeto](); //Monta a tabela
    montarArvore(); //Monta a �rvore
    criarTabela();
    codigo = criarCodigo(frase); //Codifica
    //salvarArquivo();

    //decodificar(x);

}


//Destrutor que chama a fun��o recursiva auxiliar come�ando pela raiz e excluindo o alfabeto e a frequencia no final
ArvoreHuffman::~ArvoreHuffman()
{
    auxDelete(raiz);
    delete alfabeto;
    delete frequencia;
}
//Fun��o auxiliar do destrutor, deletando os n�s da arvore
void ArvoreHuffman::auxDelete(NoHuffman* p)
{
    if(p->getEsq()!=NULL)
        auxDelete(p->getEsq());
    if (p->getDir()!=NULL)
        auxDelete(p->getDir());
    delete p;
}

//verifica se contem char c na arvore, sen�o retorna -1
int ArvoreHuffman::contem(char c, int tam)
{
    for(int i = 0; i < tam; i++)
    {
        if(c == alfabeto[i]->getChave()) return i;
    }
    return -1;
}

//Constroi o alfabeto da arvore de Huffman
int ArvoreHuffman::montarAlfabeto(string chave)
{
    int verifica = 0;

    for(unsigned int i = 0; i < chave.size(); i++)
    {
        int posicao = contem(chave[i],verifica);
        //Se n�o existe no alfabeto, insere um novo NoHuffman
        if(posicao == -1)
        {
            alfabeto[verifica] = new NoHuffman(chave[i],1);
            frequencia[verifica] = 1;
            verifica++;
        }
        //Existe no alfabeto, atualiza a frequencia
        else
        {
            frequencia[posicao]++;
            alfabeto[posicao]->setFreq(alfabeto[posicao]->getFreq()+1);
        }
    }
    return verifica;
}


//Monta a Arvore de Huffman
void ArvoreHuffman::montarArvore()
{
    insertionSortFrequencias(tamAlfabeto);
    int tamanhoEx = tamAlfabeto;

    while(tamanhoEx != 0)
    {
        for( int i = 0; i < tamAlfabeto; i++)
        {
        //    cout << alfabeto[i]->getChave() << " " << alfabeto[i]->getFreq() << endl;
        }
        //Inicio do alfabeto, insere a raiz
        if(tamanhoEx == 1)
        {
          //  cout << "Inserindo raiz. Valor: " << alfabeto[0]->getChave() << "Frequencia: " << alfabeto[0]->getFreq() << endl;
            raiz = alfabeto[0];
            break;
        }
        //cout << "Menores frequencias : " << alfabeto[0]->getChave() << " e " << alfabeto[1]->getChave() << " => Frequencias " << alfabeto[0]->getFreq() << alfabeto[1]->getFreq() << endl;
        const char *c = "/0";
        NoHuffman* pai = new NoHuffman(*c ,alfabeto[0]->getFreq() + alfabeto[1]->getFreq()); //cria n� pai
        frequencia[0] = INT_MAX; //atualiza frequencia pro max

        pai->setEsq(alfabeto[0]); //filho esquerda
        pai->setDir(alfabeto[1]); //filho direta


        frequencia[1] = pai->getFreq(); //atualiza frequencia do pai
        alfabeto[1] = pai; //insere pai no alfabeto
        insertionSortFrequencias(tamanhoEx); //Aplica insertionSort nas frequencias
        tamanhoEx--;

    }

}

//Fun��o que aplica insertionSort nas frequencias
void ArvoreHuffman::insertionSortFrequencias(int n)
{
    for(int i=1; i<n; i++)
    {
        NoHuffman* pivoChar = alfabeto[i];
        int pivo = frequencia[i];
        int j = i-1;
        while(j >= 0 && frequencia[j] > pivo)
        {
            frequencia[j+1] = frequencia[j];
            alfabeto[j+1] = alfabeto[j];
            j = j-1;
        }
        frequencia[j+1] = pivo;
        alfabeto[j+1] = pivoChar;
    }
}


//Cria tabela chamando fun��o auxiliar recursiva
void ArvoreHuffman::criarTabela()
{

    int c=0;
    auxCriarTabela(raiz,"",&c);
}


//Fun��o auxiliar recursiva pra criar tabela
void ArvoreHuffman::auxCriarTabela(NoHuffman* p, string s, int* posicao)
{
  //  cout << p->getChave() << " " << p->getFreq() << " " << (p->getEsq() == NULL) << (p->getDir() == NULL) <<endl;
    if(p!=NULL)
    {
        //N� folha, tabela recebe o valor do n�
        if(p->ehFolha())
        {
           // cout << "este eh folha! " << *posicao <<endl;
            tabelaChar[*posicao] = p->getChave();
            tabela[*posicao]=s;
            *posicao = *posicao + 1;


        }
        //N� n�o � folha, continua caminhando
        else
        {
          //  cout << "No nao folha. Continuando a caminhar." << endl;
            auxCriarTabela(p->getEsq(),s+"0",posicao);
            auxCriarTabela(p->getDir(),s+"1", posicao);
        }
    }

}



string ArvoreHuffman::criarCodigo(string s)
{
    /*for(int i = 0; i < tamAlfabeto ; i++)
    {
        cout << tabelaChar[i] << " " << tabela[i] << endl;
    }
    */
    string codigo = "";
    //Gera codigo de acordo com a tabela
    for(unsigned int i = 0; i < s.size(); i++)
    {
        for(int j = 0 ; j < tamAlfabeto; j++)
        {
            if( s[i] == tabelaChar[j] )
            {
                codigo+=tabela[j];
                break;
            }
        }
    }

    return codigo;
}

//Fun��o para decodificar uma string, chama a fun��o auxiliar recursiva de decodificar
void ArvoreHuffman::decodificar(string s)
{

    if(raiz != NULL)
    {
        //cout << "Segue texto para o codigo: ";
        auxDecodificar(raiz,s,0);
    }
}

//Fun��o auxiliar recursiva de decodificar,
void ArvoreHuffman::auxDecodificar(NoHuffman* p, string s, unsigned int posicao)
{
    if(posicao <= s.size())
    {
        //N� folha, pega informa��o
        if(p->ehFolha())
        {
            //cout << p->getChave();
            auxDecodificar(raiz, s, posicao);
        }
        //Continua a caminhar
        else
        {
            if(s[posicao] == '0')
            {
                auxDecodificar(p->getEsq(),s,posicao+1);
            }
            else
            {
                auxDecodificar(p->getDir(),s,posicao+1);
            }
        }
    }

}

//Fun��o pra salvar em arquivo a saida comprimida
void ArvoreHuffman::salvarArquivo()
{
    ofstream arqc;
    arqc.open("saidaComprimidaHuffman.txt");
    if(arqc)
    {
        arqc << codigo;
        arqc.close();
    }
    else
        cout << "Nao foi possivel salvar arquivo" << endl;
}


//gets
string ArvoreHuffman::getCodigo()
{
    return codigo;
}

int ArvoreHuffman::getTamChave()
{
    return chave.size();
}

int ArvoreHuffman::getTamCodigo()
{
    return codigo.size();
}

//Calcula taxa de compress�o
float ArvoreHuffman::getTaxaCompressao()
{
    float aux = codigo.size()/8;
    aux = aux/chave.size();
    return aux;
}
