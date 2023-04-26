#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definir constantes
#define maxnome 50
//Structs 
typedef struct utente{
    long codigoUtente;
    long codigoMedico;
    char nomeUtente[maxnome];
}Utente;

typedef struct node{
    Utente utente;
    struct node *next;
}Node;

typedef struct medico{
    long codigoMedico;
    char nomeMedico[maxnome];
    Node *lista;
}Medico;

typedef struct nodeMedico{
    Medico medico;
    struct nodeMedico *next;
}NodeMed;

//Funcoes
void resgistrarDadosUtente(Medico *medico,Utente dados){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->utente = dados;
    newNode->next = medico->lista->next;
    medico->lista = newNode;
}


void listaEsperaEntrada(Utente *utente){
        system("cls");
        printf("--------------------------------------------------------\n");
        printf("|               Digite os dados do utente              |\n");
        printf("--------------------------------------------------------\n");
        printf("[Nome] ");
        fflush(stdin);
        gets(utente->nomeUtente);
        printf("[Numero Utente] ");
        scanf("%li",&utente->codigoUtente);
        fflush(stdin);
        printf("[Numero Medico] ");
        scanf("%li",&utente->codigoMedico);
        fflush(stdin);
    return;
}

void listaEsperaVer(Medico medico){
        Node *aux = medico.lista;      
        int i = 1;

        system("cls");
        printf("--------------------------------------------------------\n");
        printf("|               Lista de Espera                        |\n");
        printf("--------------------------------------------------------\n");
        
        while(aux != NULL){
            printf("[%d]%s",i,aux->utente.nomeUtente);
        }
    printf("\n\nClique 'ENTER' para continuar.. ");
    fflush(stdin);
    getchar();
}

void listaEsperaMenu(){
    //Structs necessarias
    Node *lista = NULL;
    Utente utente;
    Medico medico;   
    //Vars
    int opc = 1;
   
    while(opc != 0){
            system("cls");
            printf("--------------------------------------------------------\n");
            printf("|[1..]Check-in Utente                                    |\n");
            printf("|[2..]Remover Utente da Lista                            |\n");
            printf("|[3..]Ver Lista de Espera                                |\n");
            printf("|                                                        |\n");
            printf("|                                                        |\n");
            printf("|                                                        |\n");
            printf("|[0..]Sair                                               |\n");
            printf("--------------------------------------------------------\n");
            printf("[?] Digite a opcao desejada: \n");
            printf("[>] ");
            scanf("%d",&opc);

            switch(opc)
            {
            case 1: listaEsperaEntrada(&utente);resgistrarDadosUtente(&medico,utente);break;
            case 2: break;  
            case 3: listaEsperaVer(medico);break;
            case 0: break;
            default: printf("[ERROR] Opcao Invalida!!");
            }
        }
    free(lista);
    return;
}

//----------------------------------------------Medicos-----------------------------------------------
void resgistrarDadosMedico(NodeMed **lista,Medico dados){
    NodeMed *newNodeMed = (NodeMed*)malloc(sizeof(NodeMed));
    newNodeMed->medico = dados;
    newNodeMed->next = *lista;
    *lista = newNodeMed;
}

void adicionarMedico(Medico *medico,NodeMed *lista){
        NodeMed *aux = lista;
        char c;
        skip:
        system("cls");
        printf("--------------------------------------------------------\n");
        printf("|               Digite os dados do Medico              |\n");
        printf("--------------------------------------------------------\n");
        printf("[Nome] ");
        fflush(stdin);
        gets(medico->nomeMedico);
        fflush(stdin);
        printf("[Numero Medico] ");
        scanf("%li",&medico->codigoMedico);
        fflush(stdin);
        
        while(aux != NULL){
            if(medico->codigoMedico == aux->medico.codigoMedico){
                printf("\n[ERROR] Numero de medico ja existente");
                printf("\n\nClique 'ENTER' para reinserir os dados / Clique 'ESC' para voltar atras ");
                c = getch();
                if(c == 13){
                    fflush(stdin); goto skip;
                }else if(c == 27){
                    fflush(stdin);
                    listaMedicoMenu();
                }
                else printf("[ERROR]Operacao Invalida");
                getchar();
            }
            aux = aux->next;
        }
    return;
}

void listaMedicos(NodeMed *node){
        NodeMed *aux = node;          
        int i = 1;

        system("cls");
        printf("--------------------------------------------------------\n");
        printf("|               Lista de Espera                        |\n");
        printf("--------------------------------------------------------\n");
        
        while(aux != NULL){
            printf("| [%d] %s\t->\t%li\t\t\t\t\b|\n",i,aux->medico.nomeMedico,aux->medico.codigoMedico);
            aux = aux->next;
            i++;
        }
        printf("--------------------------------------------------------\n");
        printf("|                                                      |\n");
        printf("--------------------------------------------------------\n");
    printf("\n\nClique 'ENTER' para continuar.. ");
    fflush(stdin);
    getchar();
}

void listaMedicoMenu(){
    //Structs necessarias
    NodeMed *lista = NULL;
    Medico medico;   
    //Vars
    int opc = 1;
   
    while(opc != 0){
            system("cls");
            printf("--------------------------------------------------------\n");
            printf("|[1..]Adicionar Medico                                   |\n");
            printf("|[2..]Remover Medico                                     |\n");
            printf("|[3..]Editar Perfil do Medico                            |\n");
            printf("|[4..]Consultar Lista de Medicos                         |\n");
            printf("|                                                        |\n");
            printf("|                                                        |\n");
            printf("|[0..]Sair                                               |\n");
            printf("--------------------------------------------------------\n");
            printf("[?] Digite a opcao desejada: \n");
            printf("[>] ");
            scanf("%d",&opc);

            switch(opc)
            {
            case 1: adicionarMedico(&medico,lista);resgistrarDadosMedico(&lista,medico);break;
            case 2: break;  
            case 3: break;
            case 4: listaMedicos(lista);break;
            case 0: break;
            default: printf("[ERROR] Opcao Invalida!!");
            }
        }
    free(lista);
    return;
}

int main(){
    //Structs e pointers para Fila binaria

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
        case 1: listaMedicoMenu();break;
        case 2: break;  
        case 3: /*listaEsperaEntrada(&utente,&lista)*/listaEsperaMenu();break;
        case 0: break;
        default: printf("[ERROR] Opcao Invalida!!");
        }
    }
    return 0;
}

