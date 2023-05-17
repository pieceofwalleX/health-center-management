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

typedef struct nodeEspera{
    struct nodeEspera *end;   //Serve para saber a localizacao do ultimo nodo
    struct nodeEspera *prev;
    struct nodeEspera *next;
    struct Utente *UT;
}NodeEspera;

typedef struct medico{
    long codigoMedico;
    char nomeMedico[maxnome];
    NodeUtente *lista;
}Medico;

typedef struct nodeMedico{
    Medico medico;
    struct nodeMedico *next;
}NodeMed;

//Prototipo necessarios

void nomeMedico(long int codigo, NodeMed* lista, char* nome);

//Funcoes
//----------------------------------------------Utentes-----------------------------------------------
void resgistrarDadosUtente(NodeUtente **lista,Utente dados){
    NodeUtente *newNode = (NodeUtente*)malloc(sizeof(NodeUtente));
    newNode->utente = dados;
    newNode->next = *lista;
    *lista = newNode;
}

int adicionarUtente(NodeMed *listaMed,NodeUtente *listaUt,Utente *utente){
        
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
                    return 1;
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
                        return 1;          
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

    return 0;
}

void removerUtente(NodeUtente **lista){
    
    NodeUtente *aux = *lista;
    NodeUtente *ant = NULL;
    
    
    long int codigo;
    int encontrou = 0;
    system("cls");
    printf("--------------------------------------------------------\n");
    printf("|               Digite o numero do Utente              |\n");
    printf("--------------------------------------------------------\n");
    fflush(stdin);
    printf("|-> ");
    scanf("%li",&codigo);

    while (!encontrou && aux != NULL){
        if (aux->utente.codigoUtente == codigo){ 
            encontrou = 1;
        }
        else{
            ant = aux;
            aux=aux->next;
        }
    }
    if (encontrou){
        if (ant == NULL && aux == *lista)
        {
            *lista = NULL;
        }
        else
        {
            if (aux->next == NULL)
            {
                ant->next = NULL;
            }
            else{
                ant->next = aux->next;
            }
        }

        free(aux);
        aux = NULL;


        printf("--------------------------------------------------------\n");
        printf("|                   Utente removido!                   |\n");
        printf("--------------------------------------------------------\n");
        getchar();
        getchar();
    }
}

void listaUtentesVer(NodeUtente *dados,NodeMed *dadosMed){
        NodeUtente *aux = dados;    
        NodeMed *auxMed = dadosMed;  
        int i = 1;
        char nome[maxnome];


        system("cls");
        printf("---------------------------------------------------------\n");
        printf(" |               Lista de Utentes                      |\n");
        printf("---------------------------------------------------------\n");
        
        if(aux == NULL){
            printf(" | \t\t\b\b\bA Lista encontra-se .. VAZIA .. \t\t\b|\n");
        }
        while(aux != NULL){
            nomeMedico(aux->utente.codigoMedico, auxMed, nome);
            printf(" | [%d] %s\t->\t%s\t\t\t\t\b|\n",i,aux->utente.nomeUtente,nome);
            i++;
            aux = aux->next;
        }
        printf("---------------------------------------------------------\n");
    printf("\n\nClique 'ENTER' para continuar.. ");
    fflush(stdin);
    getchar();
}

void listaUtenteMenu(NodeMed **lista,NodeUtente **listaUtente){
    //Structs necessarias
    Utente utente;
    //Vars
    int opc = 1,check = 0;
   
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
                case 1: check = adicionarUtente(*lista,*listaUtente,&utente);if(check== 0)resgistrarDadosUtente(listaUtente,utente);break;
                case 2: removerUtente(listaUtente);break;  
                case 3: break;
                case 4: listaUtentesVer(*listaUtente,*lista);break;
                case 0: break;
                default: printf("[ERROR] Opcao Invalida!!");
            }
    }
}
//----------------------------------------------Lista de Espera-----------------------------------------------

void registrarEntrada(NodeEspera **listaEspera, Utente *dados) {
    NodeEspera *newNode = (NodeEspera*) malloc(sizeof(NodeEspera));
    newNode->UT = dados;
    newNode->prev = NULL;
    newNode->next = *listaEspera;
    if (*listaEspera != NULL) {

        (*listaEspera)->prev = newNode;
    }
    *listaEspera = newNode;

    if (newNode->next == NULL) {
        newNode->end = newNode;
    } else {

        newNode->end = (*listaEspera)->next->end;
    }

    printf("\n[ :D ] Sr.%s adicionado a lista de espera :D\n\n", dados->nomeUtente);

    printf("\nClique 'ENTER' para continuar.. ");
}


void procuraMedico(NodeMed **listaMed,NodeUtente *dados,long codigo,NodeEspera **listaEspera){
    NodeMed *aux = *listaMed;

    int found = 0;
    while(aux != NULL && found == 0){
        if(aux->medico.codigoMedico == codigo){
            registrarEntrada(listaEspera,&dados->utente);
            found = 1;
        }
        aux = aux->next;
    }
    if (found == 0) {
        printf("\nERROR: Médico não encontrado.\n");
    }
}

int verificaResposta(char ans[maxnome]){
    //Verificar se a resposta comeca por um Numero Ou Letra , assim podemos verificar se e um nome ou um numero
    //AVISO : com muitos lapsos ,pois ele pode colocar um numero e depois uma letra da erro
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

int numUtentesEspera(NodeEspera *lista,long int codigo){
    NodeEspera *lastNode = NULL;
    NodeEspera *aux = lista;  
    int i = 0;

    lastNode = aux->end;

    while (lastNode != NULL) {
        Utente *utente = lastNode->UT;  
        if(utente->codigoMedico == codigo){
                i++;
        }
        lastNode = lastNode->prev;      
    }
    return i;
}

void maiorListaEspera(NodeEspera *listaEspera, NodeMed *listaMed){
    NodeEspera *auxEspera = listaEspera;
    NodeMed *auxMed = listaMed;

    char nome[maxnome];

    int max = 0,temp;

    while(auxMed != NULL){
            temp = numUtentesEspera(auxEspera,auxMed->medico.codigoMedico);
            if(temp > max ){
                max = temp;
                strcpy(nome,auxMed->medico.nomeMedico);
            }
        auxMed = auxMed->next;
    }
    if(max == 0){
        printf("\nTodas as listas de Espera estao Vazias");
    }else{
        printf("\nO Medico %s tem mais pacientes a atender :( ",nome);
    }

    fflush(stdin);
    getchar();
}


void listaEsperaEntrada(NodeMed **lista,NodeUtente *dados,NodeEspera **listaEspera){
        NodeMed *auxMed = *lista;
        NodeUtente *auxUt = dados;
        NodeEspera *auxEspera = *listaEspera;

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

        while(auxEspera != NULL){
            Utente *utente = auxEspera->UT;
            if(style == 1 && !strcmp(utente->nomeUtente,ans)){
                found = 1;
            }else if(style == 0 && utente->codigoUtente == atoi(ans)){
                found = 1;
            }
           auxEspera = auxEspera->next;
        }
        if(found == 1){
            printf("[] Utente ja esta na lista de Espera\n\n");
            printf("\nClique 'ENTER' para continuar.. ");
            getchar();
            getchar();
            return;
        }
        while(auxUt != NULL && found != 1){
            if(style == 1 && !strcmp(auxUt->utente.nomeUtente,ans)){
                found = 1;
                procuraMedico(&auxMed,auxUt,auxUt->utente.codigoMedico,listaEspera);
            }else if(style == 0 && auxUt->utente.codigoUtente == atoi(ans)){
                found = 1;
                procuraMedico(&auxMed,auxUt,auxUt->utente.codigoMedico,listaEspera);
            }
            auxUt = auxUt->next;
        }
        if(found != 1){
            printf("\n[ERRO] Dados introduzidos incorretamente / Utente nao existe na base de dados");
        }

        getchar();
    return;
}

void listaEsperaVer(NodeEspera *listaEspera,NodeMed *listaMed){
    NodeEspera *lastNode = NULL;
    NodeEspera *aux = listaEspera;   
    //NodeMed *med = listaMed;
    int i = 1;
    long int codigo;
    char nome[maxnome];

    system("cls");
    printf("--------------------------------------------------------\n");
    printf("|               Digite o numero do Medico              |\n");
    printf("--------------------------------------------------------\n");
    printf("[Numero Medico] ");
    scanf("%li",&codigo);

    system("cls");
    printf("--------------------------------------------------------\n");
    printf("|                   Lista de Espera                    |\n");
    printf("--------------------------------------------------------\n");

    

    lastNode = aux->end;

    while (lastNode != NULL) {
        Utente *utente = lastNode->UT;  
        if(utente->codigoMedico == codigo){
                nomeMedico(codigo,listaMed,nome);
                printf("[%d] %s -> %s \n", i, utente->nomeUtente,nome);
                i++;
        }
        lastNode = lastNode->prev;      
    }
    if (i == 1) {
        printf("\n\n[ :D ] Lista de espera vazia\n");
    } else {
        printf("\n\nClique 'ENTER' para continuar.. ");
    }
    fflush(stdin);
    getchar();
}

void listaEsperaMenu(NodeMed **listaMed,NodeUtente **listaUt,NodeEspera **listaEspera){
    //Structs necessarias   
    //Vars
    int opc = 1;
   
    while(opc != 0){
            system("cls");
            printf("--------------------------------------------------------\n");
            printf("|[1..]Check-in Utente                                  |\n");
            printf("|[2..]Remover Utente da Lista                          |\n");
            printf("|[3..]Ver Lista de Espera                              |\n");
            printf("|[4..]Estatistica                                      |\n");
            printf("|                                                      |\n");
            printf("|                                                      |\n");
            printf("|[0..]Sair                                             |\n");
            printf("--------------------------------------------------------\n");
            printf("[?] Digite a opcao desejada: \n");
            printf("[>] ");
            scanf("%d",&opc);

            switch(opc)
            {
            case 1: listaEsperaEntrada(listaMed,*listaUt,listaEspera);break;
            case 2: break;  
            case 3: listaEsperaVer(*listaEspera,*listaMed);break;
            case 4: maiorListaEspera(*listaEspera,*listaMed);break;
            case 0: break;
            default: printf("[ERROR] Opcao Invalida!!");
            }
        }
    return;
}

//----------------------------------------------Medicos-----------------------------------------------
void resgistrarDadosMedico(NodeMed **lista,Medico dados){
    NodeMed *newNodeMed = (NodeMed*)malloc(sizeof(NodeMed));
    newNodeMed->medico = dados;
    newNodeMed->next = *lista;
    *lista = newNodeMed;
}

void nomeMedico(long int codigo, NodeMed* lista, char* nome) {
    NodeMed* aux = lista;

    while (aux != NULL) {
        if (codigo == aux->medico.codigoMedico) {
            strcpy(nome, aux->medico.nomeMedico);
            return;
        }
        aux = aux->next;
    }
    return;
}

int verificaNumMedico(long int codigo,NodeMed *lista){
    NodeMed *aux = lista;
    char c;

    while(aux != NULL){
            if(codigo == aux->medico.codigoMedico){
                printf("\n[ERROR] Numero de medico ja existente");
                printf("\n\nClique 'ENTER' para reinserir os dados / Clique 'ESC' para voltar atras ");
                c = getch();
                if(c == 13){
                    fflush(stdin);
                    return 1;
                }else if(c == 27){
                    fflush(stdin);
                    return -1;
                }
                else printf("[ERROR]Operacao Invalida");
                getchar();
            }
        aux = aux->next;
    }
    return 0;
}

void adicionarMedico(Medico *medico,NodeMed *lista){
        int vald;
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
        vald = verificaNumMedico(medico->codigoMedico,lista);
        if(vald == 1){
            goto skip;
        }else if (vald == -1){
            return;
        }
}

void removerMedicoListaEspera(NodeEspera **lista, long int codigo) {
    NodeEspera *aux = *lista;
    NodeEspera *ant = NULL;

    while (aux != NULL) {
        Utente *utente = aux->UT;
        if (utente->codigoMedico == codigo) {
            if (ant == NULL) {
                *lista = aux->next;
            } else {
                ant->next = aux->next;
            }

            if (*lista != NULL) {
                (*lista)->end = aux->end;
            }

            free(aux);
            aux = NULL;

            return;
        } else {
            ant = aux;
            aux = aux->next;
        }
    }
}

void removerMedico(NodeMed **lista,NodeEspera **listaEspera){
    
    NodeMed *aux = *lista;
    NodeMed *ant = NULL;
    
    
    long int codigo;
    int encontrou = 0;
    system("cls");
    printf("--------------------------------------------------------\n");
    printf("|               Digite o numero do Medico              |\n");
    printf("--------------------------------------------------------\n");
    fflush(stdin);
    printf("|-> ");
    scanf("%li",&codigo);

    while (!encontrou && aux != NULL){
        if (aux->medico.codigoMedico == codigo){ 
            encontrou = 1;
        }
        else{
            ant = aux;
            aux=aux->next;
        }
    }
    if (encontrou){
        if (ant == NULL && aux == *lista)
        {
            *lista = NULL;
        }
        else
        {
            if (aux->next == NULL)
            {
                ant->next = NULL;
            }
            else{
                ant->next = aux->next;
            }
        }

        free(aux);
        aux = NULL;

        if (*listaEspera != NULL) {
            removerMedicoListaEspera(listaEspera, codigo);
        }

        printf("--------------------------------------------------------\n");
        printf("|                   Medico removido!                   |\n");
        printf("--------------------------------------------------------\n");
        getchar();
        getchar();
    }
}

void editarDadosMedico(NodeMed **lista){
    int op;
    NodeMed *aux = *lista;

    int encontrou = 0,vald;
    long int codigoMed, newCode;

    system("cls");
    printf("----------------------------------------------------------\n");
    printf("|                Digite o numero do Medico               |\n");
    printf("----------------------------------------------------------\n|> ");
    fflush(stdin);
    scanf("%li",&codigoMed);


    while(aux != NULL && encontrou == 0){
        if(aux->medico.codigoMedico == codigoMed){
            system("cls"); 
            printf("--------------------------------------------------------\n");
            printf("|[1..] Nome                                            |");
            printf("\n|[2..] Numero Medico                                   |");
            printf("\n|                                                      |");
            printf("\n|[0..] Sair                                            |");
            printf("\n--------------------------------------------------------\n|> ");
            fflush(stdin);
            scanf("%d",&op);

            switch(op){
                case 1:
                    system("cls"); 
                    printf("--------------------------------------------------------\n");
                    printf("|                   Insira o novo nome                 |");
                    printf("\n--------------------------------------------------------\n|> ");
                    fflush(stdin);
                    gets(aux->medico.nomeMedico);
                    break;

                case 2:
                    skip:
                    system("cls");    
                    printf("--------------------------------------------------------\n");
                    printf("|           Insira o novo numero de medico             |  ");
                    printf("\n--------------------------------------------------------\n|> ");
                    fflush(stdin);
                    scanf("%li", &newCode);
                    vald = verificaNumMedico(newCode,*lista);
                    if (vald == 0){
                        aux->medico.codigoMedico = newCode;
                    }else if(vald == 1){
                        goto skip;
                    }
                    break;
                case 0: break;
                default: printf("Opção Inválida");
            }
            encontrou = 1;
        }
        aux = aux->next;
    }
    
    if(!encontrou) printf("\n[ERROR] Falha ao encontrar o Medico");

    printf("\n\nClique 'ENTER' para continuar.. ");
    fflush(stdin);
    getchar();
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

void consultarDadosMedico(NodeMed *lista,NodeEspera *listaEspera){

    NodeMed *aux = lista;
    int encontrou = 0, quant;
    long int codigo;

    system("cls");
    printf("----------------------------------------------------------\n");
    printf("|                Digite o numero do Medico               |\n");
    printf("----------------------------------------------------------\n|> ");
    fflush(stdin);
    scanf("%li",&codigo);


    quant = numUtentesEspera(&listaEspera,codigo);

    while(aux != NULL && encontrou == 0){
        if(aux->medico.codigoMedico == codigo){
            printf("----------------------------------------------------------\n");
            printf("|Nome: %s \t\t\t\t\t\t|",aux->medico.nomeMedico);
            printf("\n|Codigo: %li \t\t\t\t\t\t|",aux->medico.codigoMedico);
            printf("\n|Utentes em Espera: %i \t\t\t\t\t|",quant);
            printf("\n----------------------------------------------------------\n");
            encontrou = 1;
        }
        aux = aux->next;
    }
    if(!encontrou)
    printf("\n[ERROR] Falha ao encontrar o Medico");

    printf("\n\nClique 'ENTER' para continuar.. ");
    fflush(stdin);
    getchar();
}

void listaMedicoMenu(NodeMed **lista,NodeEspera **listaEspera){
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
            printf(" |[5..]Consultar Medico                                   |\n");
            printf(" |                                                        |\n");
            printf(" |[0..]Sair                                               |\n");
            printf("------------------------------------------------------------\n");
            printf("[?] Digite a opcao desejada: \n");
            printf("[>] ");
            scanf("%d",&opc);

            switch(opc)
            {
                case 1: adicionarMedico(&medico,*lista);resgistrarDadosMedico(lista,medico);break;
                case 2: removerMedico(lista,listaEspera);break;  
                case 3: editarDadosMedico(lista);break;
                case 4: listaMedicos(*lista);break;
                case 5: consultarDadosMedico(*lista,*listaEspera);break;
                case 0: break;
                default: printf("[ERROR] Opcao Invalida!!");
            }
    }
}



int main(){
    //Structs e pointers para Fila binaria
    NodeMed *lista = NULL;
    NodeUtente *listaUtente = NULL;
    NodeEspera *listaEspera = NULL;
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
        case 1: listaMedicoMenu(&lista,&listaEspera);break;
        case 2: listaUtenteMenu(&lista,&listaUtente);break;
        case 3: listaEsperaMenu(&lista,&listaUtente,&listaEspera);break;
        case 0: break;
        default: printf("[ERROR] Opcao Invalida!!");
        }
    }
    free(lista);free(listaUtente);free(listaEspera);

    return 0;
}