#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definir constantes

#define maxnome 50

//Structs 
typedef struct node{
    long numMedico;
    long numUtente;
    struct node *next;
}Node;

typedef struct medico{
    long codigoMedico;
    char nomeMedico[maxnome];
    Node *lista;
}Medico;

typedef struct utente{
    long codigoUtente;
    long codigoMedico;
    char nomeUtente[maxnome];
}Utente;

//Funcoes

void listaEsperaEntrada(Utente *utente,Node **lista){
        system("cls");
        printf("--------------------------------------------------------\n");
        printf("|               Digite os dados do utente              |\n");
        printf("--------------------------------------------------------\n");
        printf("[Nome] ");
        fflush(stdin);
        gets(utente->nomeUtente);
        printf("[Numero Utente] ");
        scanf("%l",&utente->codigoUtente);
        fflush(stdin);
        printf("[Numero Medico] ");
        scanf("%l",&utente->codigoMedico);
}

int main(){
    //Structs e pointers para Fila binaria
    Node *lista = NULL;
    Utente utente;
    Medico medico;

    //Criacao de variaveis
    int opc = 1;
    //Criacao do Menu Inicial

    while(opc != 0){
        system("cls");
        printf("--------------------------------------------------------\n");
        printf("|[1..]Gestao Medico                                    |\n");
        printf("|[2..]Gestao Utente                                    |\n");
        printf("|[3..]Lista De Espera                                  |\n");
        printf("|                                                      |\n");
        printf("|                                                      |\n");
        printf("|                                                      |\n");
        printf("|[0..]Sair                                             |\n");
        printf("--------------------------------------------------------\n");
        printf("[?] Digite a opcao desejada: \n");
        printf("[>] ");
        scanf("%d",&opc);

        switch(opc)
        {
        case 1: break;
        case 2: break;  
        case 3: listaEsperaEntrada(&utente,&lista);break;
        case 0: break;
        default: printf("[ERROR] Opcao Invalida!!");
        }
    }
    return 0;
}
