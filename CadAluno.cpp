#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Aluno {
  int ru;
  char nome[30];
  char email[30];
  struct Aluno *esq, *dir;
} *root;

void Inserir(Aluno **ElementoVarredura, Aluno alunoIns);
void InicializarListaAlunos();
int menu();
void ImprimirEmOrdem(Aluno *ElementoVarredura);
Aluno* Buscar(Aluno **ElementoVarredura, int RUBusca);

int main()
{

  setlocale(LC_ALL, "Portuguese");

  int RUBuscado, c, opcao;
  root = (Aluno *)malloc(sizeof(Aluno));
  root = NULL;
  Aluno *alunoBuscado;
  alunoBuscado = (Aluno *)malloc(sizeof(Aluno));
  InicializarListaAlunos();

  opcao = menu();

  switch (opcao)
  {
  case 1:
    ImprimirEmOrdem(root);
    break;
  case 2:

    printf("Digite o RU para pesquisa: ");
    scanf("%d", &RUBuscado);
    while ((c = getchar()) != '\n' && c != EOF){}
  
    alunoBuscado = Buscar(&root, RUBuscado);

    if(alunoBuscado)  //se a função Buscar encontrar o RU bsucado retorna o aluno
    {
      printf("\nRU: %d\n", alunoBuscado->ru);
      printf("Aluno: %s", alunoBuscado->nome);
      printf("E-mail: %s", alunoBuscado->email);
    }
    //caso a função não localize, imprime na tela a mensagem:
    else
    {
      printf("RU não localizado.");
    }
    break;

  default:
    break;
  }

  getchar();
  return 0;

}

int menu()
{

  int op, c;

  printf("\n#####################\n\n");
  printf("1. Imprimir em Ordem\n");
  printf("2. Buscar\n");
  printf("\n#####################\n\n");
  scanf("%d", &op);
  while ((c = getchar()) != '\n' && c != EOF){}

  return op;

}

//criação de uma lista de alunos e chamamento da função para inserir os valores
void InicializarListaAlunos() 
{
  struct Aluno lista[] = {
    {1094403,"Laize\n","laize@email.com\n",NULL, NULL},
    {2954709,"Lavinia\n","lavinia@email.com\n",NULL, NULL},
    {3997884,"Daniel\n","daniel@email.com\n",NULL, NULL},
    {5097307,"Ana\n","ana@email.com\n",NULL, NULL},
    {3097707,"Rodrigo\n","rodrigo@email.com\n",NULL, NULL},
    {4190790,"Pedro\n","pedro@email.com\n",NULL, NULL},
    {1093701,"Francisco\n","fran@email.com\n",NULL, NULL},
    {6394407,"Luiz\n","luiz@email.com\n",NULL, NULL},
    {3337703,"Adão\n","adao@email.com\n",NULL, NULL},
    {7003307,"Eva\n","eva@email.com\n",NULL, NULL},
  };

  unsigned int tamanhoLista = 10;
  //loop para rodar a função de inserir cada um dos alunos do Array
  for (int i = 0; i < tamanhoLista; i++)
  {
    Inserir(&root, lista[i]);
  }

}

//função inserir passando o elemento para varredura e os dados do Alunos a ser inserido
void Inserir(Aluno **ElementoVarredura ,Aluno alunoIns)
{

  if(*ElementoVarredura == NULL)
  {
    //start da variável que receberá os dados do aluno ser inserido
    Aluno *NovoAluno = NULL;  
    //alocação na memória da variavel com tamanho da struct de aluno
    NovoAluno = (struct Aluno *)malloc(sizeof(struct Aluno)); 
    *NovoAluno = alunoIns;
    *ElementoVarredura = NovoAluno;
    return;
  }
  
  if(alunoIns.ru < (*ElementoVarredura)->ru) 
  {
    //se o código RU do aluno inserido for menor que o ru do elemento de Varredura, este irá para a esquerda do elemento
    Inserir(&(*ElementoVarredura)->esq, alunoIns);
  }
  else if (alunoIns.ru > (*ElementoVarredura)->ru)
  {
    //se o RU for maior, irá para direita
    Inserir(&(*ElementoVarredura)->dir, alunoIns);
  }
}

//Função de busca passando um Elemento de Varredura e o RU a ser buscado
Aluno* Buscar(Aluno **ElementoVarredura, int RUBusca)
{

  //se o elemento de varredura for valor NULL, retorna NULL;
  if(*ElementoVarredura == NULL)
    return NULL;

  if(RUBusca < (*ElementoVarredura)->ru)
  {
    Buscar(&((*ElementoVarredura)->esq), RUBusca);
  }
  else 
  {
    if(RUBusca > (*ElementoVarredura)->ru)
    {
      Buscar(&((*ElementoVarredura)->dir), RUBusca);
    }
    else if (RUBusca == (*ElementoVarredura)->ru)
        return *ElementoVarredura;
  }
}

void ImprimirEmOrdem(Aluno *ElementoVarredura)
{
  if(ElementoVarredura)
  {
    ImprimirEmOrdem(ElementoVarredura->esq);
    printf("\n###########\n");
    printf("RU: %d\n", ElementoVarredura->ru);
    printf("Aluno: %s", ElementoVarredura->nome);
    printf("E-mail: %s", ElementoVarredura->email);
    ImprimirEmOrdem(ElementoVarredura->dir);
  }
}
