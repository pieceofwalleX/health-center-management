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

typedef struct nodeutente{
    Utente utente;
    struct node *next;
}NodeUtente;

typedef struct medico{
    long codigoMedico;
    char nomeMedico[maxnome];
    NodeUtente *lista;
}Medico;

typedef struct nodeMedico{
    Medico medico;
    struct nodeMedico *next;
}NodeMed;

//Funcoes
//----------------------------------------------Utentes-----------------------------------------------
void resgistrarDadosUtente(NodeUtente ***lista,Utente dados){
    NodeUtente *newNode = (NodeUtente*)malloc(sizeof(NodeUtente) + 1);
    newNode->utente = dados;
    newNode->next = **lista;
    **lista = newNode;
}

void adicionarUtente(NodeMed *listaMed,NodeUtente *listaUt,Utente *utente){
        
        NodeMed *aux = listaMed;
        NodeUtente *aux2 = listaUt;
        int foundU = 0;
        int foundMed = 0;
        char c;

        skip:
        system("cls");
        printf("--------------------------------------------------------\n");
        printf("|               Digite os dados do utente              |\n");
        printf("--------------------------------------------------------\n");
        printf("[Nome] ");
        fflush(stdin);
        gets(utente->nomeUtente);
        printf("[Numero Utente] ");
        fflush(stdin);
        scanf("%li",&utente->codigoUtente);
        fflush(stdin);
        printf("[Numero Medico] ");
        scanf("%li",&utente->codigoMedico);

        while(aux2 != NULL &&foundU == 0){
            if(aux2->utente.codigoUtente == utente->codigoUtente){
                printf("\n[ERROR] Numero de utente ja existente");
                printf("\n\nClique 'ENTER' para reinserir os dados / Clique 'ESC' para voltar atras");
                foundU = 1;
                c = getch();

                if(c == 13){
                    fflush(stdin);memset(utente,0,sizeof(Utente));goto skip;
                }else if(c == 27){
                    fflush(stdin);
                    memset(utente,0,sizeof(Utente));
                    return;
                }
                else{
                    printf("[ERROR]Operacao Invalida");
                }
                getchar();
            }
            aux2 = aux2->next;
        }
        while(aux != NULL && foundMed == 0){
            if(aux->medico.codigoMedico == utente->codigoMedico){
                foundMed = 1;
            }
            aux = aux->next;
        }
            if(foundMed != 1){
                printf("\n[ERROR] Numero de Medico nao encontrado");
                printf("\n\nClique 'ENTER' para reinserir os dados / Clique 'ESC' para voltar atras");
                
                c = getch();

                    if(c == 13){
                        fflush(stdin);memset(utente,0,sizeof(Utente));goto skip;
                    }else if(c == 27){
                        fflush(stdin);
                        memset(utente,0,sizeof(Utente));
                        return;           
                    }
                    else{
                        printf("[ERROR]Operacao Invalida");
                    }
                    fflush(stdin);
            }else{
                printf("\n[ ] Sr.%s (u%li) adiconado ao Sistema",utente->nomeUtente,utente->codigoUtente);
                
            }
        getchar();
        getchar();

    return;
}

void listaUtentesVer(NodeUtente *dados){
        NodeUtente *aux = dados;      
        int i = 1;

        system("cls");
        printf("--------------------------------------------------------\n");
        printf("|               Lista de Utentes                       |\n");
        printf("--------------------------------------------------------\n");
        
        while(aux != NULL){
            printf("[%d] %s -> %li",i,aux->utente.nomeUtente,aux->utente.codigoMedico);
            i++;
            aux = aux->next;
        }
    printf("\n\nClique 'ENTER' para continuar.. ");
    fflush(stdin);
    getchar();
}

void listaUtenteMenu(NodeMed **lista,NodeUtente **listaUtente){
    //Structs necessarias
    Utente utente;
    //Vars
    int opc = 1;
   
    while(opc != 0){
            system("cls");
            printf("--------------------------------------------------------\n");
            printf("|[1..]Registrar novo Utente                              |\n");
            printf("|[2..]Remover Utente                                     |\n");
            printf("|[3..]Editar Perfil do Utente                            |\n");
            printf("|[4..]Consultar Lista de Utentes                         |\n");
            printf("|                                                        |\n");
            printf("|                                                        |\n");
            printf("|[0..]Sair                                               |\n");
            printf("--------------------------------------------------------\n");
            printf("[?] Digite a opcao desejada: \n");
            printf("[>] ");
            scanf("%d",&opc);

            switch(opc)
            {
                case 1: adicionarUtente(*lista,*listaUtente,&utente);resgistrarDadosUtente(&listaUtente,utente);break;
                case 2: break;  
                case 3: break;
                case 4: listaUtentesVer(*listaUtente);break;
                case 0: break;
                default: printf("[ERROR] Opcao Invalida!!");
            }
    }
}
//----------------------------------------------Lista de Espera-----------------------------------------------

void resgistrarEntrada(NodeMed **lista,Utente dados){
    NodeMed *newNode = (NodeMed*)malloc(sizeof(Medico) + 1);
    newNode->medico.lista->utente = dados;
    newNode->medico.lista->next = *lista;
    *lista = newNode;

    printf("\n[ :D ]Sr.%s adiconado a lista de espera",dados.nomeUtente);
    printf("\n\nClique 'ENTER' para continuar.. ");

    fflush(stdin);
    getchar();
}

void procuraMedico(NodeMed **listaMed,NodeUtente *dados,long codigo){
    NodeMed *aux = *listaMed;
    Utente dadosUtente;
    int found = 0;
    while(aux != NULL && found == 0){
        if(aux->medico.codigoMedico == codigo){
            dadosUtente = dados->utente;
            resgistrarEntrada(&aux,dadosUtente);
            *listaMed = aux;
        }
        aux = aux->next;
    }
    printf("\nERROR");
}

int verificaResposta(char ans[maxnome]){
    //Verificar se a resposta comeca por um Numero Ou Letra , assim podemos verificar se e um nome ou um numero
    //AVISO : com muitos lapsos ,pois ele pode colocar 1 numero e depois uma letra
    int found = 0,i = 0;
    char num[1];
    while(i != 10 && found == 0){
        itoa(i,num,10);
            if(ans[0] == num[0]){
                found = 1;
                return 0;
            }
        i++;
    }
    return 1;
}


void listaEsperaEntrada(NodeMed **lista,NodeUtente *dados){
        NodeMed *auxMed = *lista;
        NodeUtente *auxUt = dados;

        char ans[maxnome];
        int style,found = 0;
        system("cls");
        printf("--------------------------------------------------------\n");
        printf("|            Digite o numero/nome do Utente            |\n");
        printf("--------------------------------------------------------\n");
        printf("|                                                      |\n");
        printf("[>] ");  
        fflush(stdin);
        gets(ans);
        ans[strcspn(ans, "\n")] = 0;
        printf("|                                                      |\n");
        printf("--------------------------------------------------------\n");

        style = verificaResposta(ans);
        while(auxUt != NULL && found != 1){
            if(style == 1 && !strcmp(auxUt->utente.nomeUtente,ans)){
                found = 1;
                procuraMedico(&auxMed,auxUt,auxUt->utente.codigoMedico);
            }else if(style == 0 && auxUt->utente.codigoUtente == atoi(ans)){
                found = 1;
                procuraMedico(&auxMed,auxUt,auxUt->utente.codigoMedico);
            }
            auxUt = auxUt->next;
        }
        if(found != 1){
            printf("\n[ERRO] Dados introduzidos incorretamente / Utente nao existe na base de dados");
        }

        getchar();
    return;
}

void listaEsperaVer(NodeMed *medico){
        NodeMed *aux = medico;      
        int i = 1;

        system("cls");
        printf("--------------------------------------------------------\n");
        printf("|               Lista de Espera                        |\n");
        printf("--------------------------------------------------------\n");
        
        while(aux != NULL){
            printf("[%d] %s -> %s",i,aux->medico.nomeMedico,aux->medico.lista->utente.nomeUtente);
            aux = aux->next;
        }
    printf("\n\nClique 'ENTER' para continuar.. ");
    fflush(stdin);
    getchar();
}

void listaEsperaMenu(NodeMed **listaMed,NodeUtente **listaUt){
    //Structs necessarias   
    //Vars
    int opc = 1;
   
    while(opc != 0){
            system("cls");
            printf("--------------------------------------------------------\n");
            printf("|[1..]Check-in Utente                                  |\n");
            printf("|[2..]Remover Utente da Lista                          |\n");
            printf("|[3..]Ver Lista de Espera                              |\n");
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
            case 1: listaEsperaEntrada(listaMed,*listaUt);break;
            case 2: break;  
            case 3: listaEsperaVer(*listaMed);break;
            case 0: break;
            default: printf("[ERROR] Opcao Invalida!!");
            }
        }
    return;
}

//----------------------------------------------Medicos-----------------------------------------------
void resgistrarDadosMedico(NodeMed **lista,Medico dados){
    NodeMed *newNodeMed = (NodeMed*)malloc(sizeof(NodeMed) + 1);
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

        //Vereficar se ja existe o codigoMedico na base de dados
        while(aux != NULL){
            if(medico->codigoMedico == aux->medico.codigoMedico){
                printf("\n[ERROR] Numero de medico ja existente");
                printf("\n\nClique 'ENTER' para reinserir os dados / Clique 'ESC' para voltar atras ");
                c = getch();
                if(c == 13){
                    fflush(stdin); goto skip;
                }else if(c == 27){
                    fflush(stdin);
                    return 0;
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
                   

        printf("\n----------------------------------------------------------\n");
        printf(" |               Lista de Medicos                       | \n");
        printf("----------------------------------------------------------\n");
        printf(" |                                                      | \n");
        while(aux != NULL){
            printf(" | [%d] %s\t->\t%li\t\t\t\t|\n",i,aux->medico.nomeMedico,aux->medico.codigoMedico);
            aux = aux->next;
            i++;
        }
        printf(" |                                                      | \n");
        printf("----------------------------------------------------------\n");
        printf(" |                                                      | \n");
        printf("----------------------------------------------------------\n");
    printf("\n\nClique 'ENTER' para continuar.. ");
    fflush(stdin);
    getchar();
}

void listaMedicoMenu(NodeMed **lista){
    //Structs necessarias
    //NodeMed *aux = *lista;

    Medico medico;
    //Vars
    int opc = 1;
   
    while(opc != 0){
            system("cls");
            printf("------------------------------------------------------------\n");
            printf(" |[1..]Adicionar Medico                                   |\n");
            printf(" |[2..]Remover Medico                                     |\n");
            printf(" |[3..]Editar Perfil do Medico                            |\n");
            printf(" |[4..]Consultar Lista de Medicos                         |\n");
            printf(" |                                                        |\n");
            printf(" |                                                        |\n");
            printf(" |[0..]Sair                                               |\n");
            printf("------------------------------------------------------------\n");
            printf("[?] Digite a opcao desejada: \n");
            printf("[>] ");
            scanf("%d",&opc);

            switch(opc)
            {
                case 1: adicionarMedico(&medico,*lista);resgistrarDadosMedico(lista,medico);break;
                case 2: break;  
                case 3: break;
                case 4: listaMedicos(*lista);break;
                case 0: break;
                default: printf("[ERROR] Opcao Invalida!!");
            }
    }
}

int main(){
    //Structs e pointers para Fila binaria
    NodeMed *lista = NULL;
    NodeUtente *listaUtente = NULL;
    //Criacao de variaveis
    int opc = 1;
    //Criacao do Menu Inicial

    while(opc != 0){
        system("cls");

        printf("\n \t     ____    _     __  ____  _____    \t  ");
        printf("\n \t    / ___|  / \\  _/_/_|  _ \\| ____|   \t   " );
        printf("\n \t    \\___ \\ / _ \\| | | | | | |  _|       \t   " );
        printf("\n \t     ___) / ___ \\ |_| | |_| | |___    \t   " );
        printf("\n \t    |____/_/   \\_\\___/|____/|_____|   \t   " );

        printf("\n///////////////////////////////////////////////////////////");
        printf("\n-----------------------------------------------------------\n");
        printf("  |[1..]Gestao Medico                                    |\n");
        printf("  |[2..]Gestao Utente                                    |\n");
        printf("  |[3..]Lista De Espera                                  |\n");
        printf("  |                                                      |\n");
        printf("  |                                                      |\n");
        printf("  |                                                      |\n");
        printf("  |[0..]Sair                                             |\n");
        printf("------------------------------------------------------------\n");
        printf("[?] Digite a opcao desejada: \n");
        printf("[>] ");
        scanf("%d",&opc);

        switch(opc)
        {
        case 1: listaMedicoMenu(&lista);break;
        case 2: listaUtenteMenu(&lista,&listaUtente);break;
        case 3: listaEsperaMenu(&lista,&listaUtente);break;
        case 0: break;
        default: printf("[ERROR] Opcao Invalida!!");
        }
    }
    return 0;
}
