#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct endereco {
  char estado[30], cidade[30], bairro[30], cep[30];
};

struct cadastro{
  char nome[30], email[30], sexo[15];
  double altura;
  int id;
  _Bool vacina;
  struct endereco end;
};

struct no{
  struct cadastro cad;
  struct no *prox;
};

void Menu();
void incluir(struct no **lista, struct no *novo);
void imprimir (struct no *imprimir);
struct no *editar(struct no *lista);
struct no *editar2(struct no *edicao);
void buscarID (struct no *imprimir);
void excluir(struct no **lista, struct no *vitima);
void fazerBackup_e_Restaurar (struct no *lista, struct no **backup, struct no *novo);
char* validarEmail(char*emailValido);
char* validarSexo(char*sexoValido);
_Bool vacinaValidado(_Bool vacina);
double alturaValidada(double altura);

int main(void) {
  int opcao, qtdBackup=0;
  struct no *novo, *edicao, *exclusao, *lista=NULL, *backup=NULL;

  do {
    Menu();
    fflush(stdin);
    scanf("%d", &opcao);
    system("cls");
    switch (opcao) {
      case 1:
        incluir(&lista, novo);
      break;
      case 2:
        edicao=editar(lista);
        if(edicao != NULL)
          edicao=editar2(edicao);
      break;
      case 3:
        exclusao=editar(lista);
        if(exclusao != NULL){
          excluir(&lista, exclusao);
        }
      break;
      case 4:
        buscarID(lista);
        break;
      case 5:
        imprimir(lista);
      break;
      case 6:
        while(backup != NULL){
          exclusao=backup;
          backup = backup->prox;
          free(exclusao);
        }
        fazerBackup_e_Restaurar(lista, &backup, novo);
        qtdBackup++;
      break;
      case 7:
        if (qtdBackup > 0) {
          while(lista != NULL){
            exclusao=lista;
            lista = lista->prox;
            free(exclusao);
          }
          fazerBackup_e_Restaurar(backup, &lista, novo);
        }
        else{
          printf("Nao ha backup! \n\n");
          system("pause"); system("cls");
        }
      break;
    }
  } while(opcao != 8);

  return 0;
}

void Menu(){
  printf(" ______________________________________\n");
  printf("|________|CADASTRO DE USUARIOS|________|\n");
  printf("|                                      |\n");
  printf("|     1-Incluir usuario;               |\n");
  printf("|                                      |\n");
  printf("|     2-Editar usuario;                |\n");
  printf("|                                      |\n");
  printf("|     3-Excluir usuario;               |\n");
  printf("|                                      |\n");
  printf("|     4-Buscar usuario pelo ID;        |\n");
  printf("|                                      |\n");
  printf("|     5-Imprimir usuarios;             |\n");
  printf("|                                      |\n");
  printf("|     6-Fazer backup;                  |\n");
  printf("|                                      |\n");
  printf("|     7-Restaurar dados;               |\n");
  printf("|                                      |\n");
  printf("|     8-Sair                           |\n");
  printf("|______________________________________|\n");
  printf("  Escolha uma opcao: ");
}

void incluir(struct no **lista, struct no *novo){

  novo = malloc (sizeof (struct no));
  novo->cad.id = rand() % 1000;
  printf("Usuario: %i\n", novo->cad.id);
  printf("Digite o nome:\n");
  fflush(stdin);
  gets(novo->cad.nome);
  strcpy(novo->cad.email,validarEmail(novo->cad.email));
  strcpy(novo->cad.sexo,validarSexo(novo->cad.sexo));
  printf("Digite o estado:\n");
  fflush(stdin);
  gets(novo->cad.end.estado);
  printf("Digite a cidade:\n");
  fflush(stdin);
  gets(novo->cad.end.cidade);
  printf("Digite a bairro:\n");
  fflush(stdin);
  gets(novo->cad.end.bairro);
  printf("Digite o cep:\n");
  fflush(stdin);
  gets(novo->cad.end.cep);
  novo->cad.altura=alturaValidada(novo->cad.altura);
  novo->cad.vacina=vacinaValidado(novo->cad.vacina);

  novo->prox = *lista;
  *lista = novo;
  system("pause"); system ("cls");
}

void imprimir (struct no *imprimir){
  struct no *aux=imprimir;
  while (aux != NULL) {
    printf("         Usuario: %i\n", aux->cad.id);
    printf("         Nome: %s\n",aux->cad.nome);
    printf("         Email: %s\n", aux->cad.email);
    printf("         Sexo: %s\n", aux->cad.sexo);
    printf("         Estado: %s\n",aux->cad.end.estado);
    printf("         Cidade: %s\n",aux->cad.end.cidade);
    printf("         Bairro: %s\n",aux->cad.end.bairro);
    printf("         CEP: %s\n",aux->cad.end.cep);
    printf("         Altura: %.2f\n",aux->cad.altura);
    printf("         Vacinado: ");
    switch (aux->cad.vacina) {
     case 1:
      printf("Sim");
     break;
     case 0:
      printf("Nao");
     break;
    }
    printf("\n--------------------------------------------\n");
    aux = aux->prox;
  }
  system("pause");
  system("cls");
}

void buscarID (struct no *imprimir){
  struct no *aux=imprimir;
  int id;
  printf("Digite o id: ");
  scanf("%i", &id);
  while (aux != NULL) {
    if (aux->cad.id==id) {
      printf("         Usuario: %i\n", aux->cad.id);
      printf("         Nome: %s\n",aux->cad.nome);
      printf("         Email: %s\n", aux->cad.email);
      printf("         Sexo: %s\n", aux->cad.sexo);
      printf("         Estado: %s\n",aux->cad.end.estado);
      printf("         Cidade: %s\n",aux->cad.end.cidade);
      printf("         Bairro: %s\n",aux->cad.end.bairro);
      printf("         CEP: %s\n",aux->cad.end.cep);
      printf("         Altura: %.2f\n",aux->cad.altura);
      printf("         Vacinado: ");
      switch (aux->cad.vacina) {
       case 1:
        printf("Sim");
       break;
       case 0:
        printf("Nao");
       break;
     }
      printf("\n--------------------------------------------\n");
    }
    else{
      printf("ID nao encontrado! \n");
    }
    aux = aux->prox;
  }
  system("pause"); system("cls");
}

struct no *editar(struct no *lista){
  int id;
  struct no *aux = lista;
  printf("Digite o ID: ");
  scanf("%i", &id);
  while (aux != NULL) {
    if(aux->cad.id == id)
      return aux;
    aux = aux->prox;
  }
  printf("ID invalido! \n\n"); system("pause"); system("cls");
  return NULL;
}

struct no *editar2(struct no *edicao){
  int opcao, sair;

  do {
    printf("  Nome: %s\n",edicao->cad.nome);
    printf("  Email: %s\n", edicao->cad.email);
    printf("  Sexo: %s\n", edicao->cad.sexo);
    printf("  Estado: %s\n",edicao->cad.end.estado);
    printf("  Cidade: %s\n",edicao->cad.end.cidade);
    printf("  Bairro: %s\n",edicao->cad.end.bairro);
    printf("  CEP: %s\n",edicao->cad.end.cep);
    printf("  Altura: %.2f\n",edicao->cad.altura);
    printf("  Vacinado: ");
    switch (edicao->cad.vacina) {
     case 1:
        printf("Sim");
     break;
     case 0:
        printf("Nao");
     break;
    }
    printf("\n--------------------\n");
    printf(" ____________________\n");
    printf("|_|Usuario: %i       |\n",edicao->cad.id);
    printf("|                    |\n");
    printf("|     1-Nome         |\n");
    printf("|     2-Email        |\n");
    printf("|     3-Sexo         |\n");
    printf("|     4-Estado       |\n");
    printf("|     5-Cidade       |\n");
    printf("|     6-Bairro       |\n");
    printf("|     7-CEP          |\n");
    printf("|     8-Altura       |\n");
    printf("|     9-vacina       |\n");
    printf("|     0-todos        |\n");
    printf("|____________________|\n");
    printf("Escolha uma opcao para editar: ");
    scanf("%i", &opcao);
    switch (opcao) {
      case 1:
        printf("Digite o nome:\n");
        fflush(stdin);
        gets(edicao->cad.nome);
      break;
      case 2:
        strcpy(edicao->cad.email,validarEmail(edicao->cad.email));
      break;
      case 3:
        strcpy(edicao->cad.sexo,validarSexo(edicao->cad.sexo));
      break;
      case 4:
        printf("Digite o estado:\n");
        fflush(stdin);
        gets(edicao->cad.end.estado);
      break;
      case 5:
        printf("Digite a cidade:\n");
        fflush(stdin);
        gets(edicao->cad.end.cidade);
      break;
      case 6:
        printf("Digite o bairro:\n");
        fflush(stdin);
        gets(edicao->cad.end.bairro);
      break;
      case 7:
        printf("Digite o cep:\n");
        fflush(stdin);
        gets(edicao->cad.end.cep);
      break;
      case 8:
        edicao->cad.altura=alturaValidada(edicao->cad.altura);
      break;
      case 9:
        edicao->cad.vacina=vacinaValidado(edicao->cad.vacina);
      break;
      case 0:
        printf("Digite o nome:\n");
        fflush(stdin);
        gets(edicao->cad.nome);
        strcpy(edicao->cad.email,validarEmail(edicao->cad.email));
        strcpy(edicao->cad.sexo,validarSexo(edicao->cad.sexo));
        printf("Digite o estado:\n");
        fflush(stdin);
        gets(edicao->cad.end.estado);
        printf("Digite a cidade:\n");
        fflush(stdin);
        gets(edicao->cad.end.cidade);
        printf("Digite a bairro:\n");
        fflush(stdin);
        gets(edicao->cad.end.bairro);
        printf("Digite o cep:\n");
        fflush(stdin);
        gets(edicao->cad.end.cep);
        edicao->cad.altura=alturaValidada(edicao->cad.altura);
        edicao->cad.vacina=vacinaValidado(edicao->cad.vacina);
      break;
    }
    printf("\nDeseja continuar editando?\n1 para sim\n2 para nao\n");
    scanf("%i", &sair);
    system("cls");
  } while(sair==1);
}

void excluir(struct no **lista, struct no *excluir){
  struct no *aux = *lista;
  if (*lista==excluir){
    *lista= excluir->prox;
  }
  else{
    while(aux->prox !=excluir){
    aux = aux->prox;
  }
    aux->prox = excluir->prox;
  }
  free(excluir);
  system("pause");
  system("cls");
}

void fazerBackup_e_Restaurar (struct no *lista, struct no **backup, struct no *novo){
  struct no *aux=lista;

  while (aux != NULL) {
    novo = (struct no*) malloc (sizeof (struct no));
    *novo = *aux;
    novo->prox = *backup;
    *backup = novo;

    aux = aux->prox;
  }
  system("pause"); system("cls");
}

char* validarSexo(char*sexoValido){
  char repetir;
  do {
    printf("Digite o sexo (Feminino, Masculino, Nao declarar):\n");
    fflush(stdin);
    gets(sexoValido);
    if ((stricmp(sexoValido,"Feminino")==0) || (stricmp(sexoValido,"Masculino")==0) || (stricmp(sexoValido,"Nao declarar")==0))
      break;
    else{
      printf("Sexo Incorreto!!\n");
        repetir='S';
    }
  } while(repetir=='S');
  return sexoValido;
}

char* validarEmail(char*emailValido){
  int tamanhoEmail, i, encontrou;
  do {
      printf("Digite o email:\n");
      gets(emailValido);
      encontrou = 0;
      tamanhoEmail=strlen(emailValido);
      for (i = 0; i < tamanhoEmail; i++) {
        switch (emailValido[i]) {
          case '@':
            encontrou++;
          break;
        }
      }
      if (encontrou != 1)
        printf("Email deve conter @!!\n");
  } while(encontrou != 1);
  return emailValido;
}

_Bool vacinaValidado(_Bool vacina){
  char vacinado[5], repetir;
  do {
    printf("Ja vacinou? (Sim ou Nao)\n");
    fflush(stdin);
    gets(vacinado);
    if ((stricmp(vacinado,"Sim")==0)||(stricmp(vacinado,"Nao")==0))
      repetir='n';
    else
      printf("Digite Sim ou Nao!\n");
  } while (repetir!='n');
  vacina=(stricmp(vacinado,"Sim")==0);
  return vacina;
}

double alturaValidada(double altura){
  char repetir;
  do {
    printf("Digite a altura:\n");
    scanf("%lf", &altura);
    if ((altura>1)&&(altura<2)) {
      break;
    }
    else{
      printf("Altura Incorreta\n");
      repetir='S';
    }
  } while(repetir=='S');
  return altura;
}
