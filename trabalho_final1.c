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
int  verificaNumMedico(long int codigo,NodeMed *lista,int type);
void resgistrarDadosMedico(NodeMed **lista,Medico dados);
void resgistrarDadosUtente(NodeUtente **lista,Utente dados);


//Funcoes
//----------------------------------------------Ficheiros-----------------------------------------------

void renameBackup(int type){

    FILE *backup, *original;

    if (type == 0) {
        backup = fopen("medicos_backup.txt", "r");
        original = fopen("medicos.txt", "w");
    } else {
        backup = fopen("utentes_backup.txt", "r");
        original = fopen("utentes.txt", "w");
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), backup) != NULL) {
        fputs(buffer, original);
    }

    if( original == NULL )
      printf( "\n\n[ERRO] Falha ao carregar o BACKUP");
    else
      printf( "\n\n[AVISO]Backup carregado com SUCESSO");

    getchar();
}


void procuraBackup(){

    FILE *fpMedicos = fopen("medicos_backup.txt","w");
    FILE *fpUtentes = fopen("utentes_backup.txt","w");

    char foundMed[3] = ":D";
    char foundUtente[3] = ":D";
    
    char c;
    int op,fMed = 0,fUt = 0; //fMed e fUt servem para saber se existe o ficheiros backups

    if(!fpMedicos){
        strcpy(foundMed,"X");
        fMed = 1;
    }
    if(!fpUtentes){
        strcpy(foundUtente,"X");
        fUt = 1;
    }
    system("cls");
    printf("\n--------------------------------------------------------\n ");
    printf("\n|                        Backup                        |");
    printf("\n-------------------------------------------------------- ");
    printf("\n|                        Backup                        |");
    printf("\n|[1..] Medicos  (%s)\t\t\t\t\t\b|",foundMed);
    printf("\n|[2..] Utentes  (%s)\t\t\t\t\t\b|",foundUtente);
    printf("\n|                                                      |");
    printf("\n|[0..] Sair                                            |");
    printf("\n--------------------------------------------------------\n|> ");
    fflush(stdin);
    scanf("%d",&op);

    switch (op)
    {
    case 1:
            if(fMed == 0){
                printf("\nDeseja carregar o ficheiro Backup-Medicos ?\n");
                printf("[AVISO] Ao executar esta funcao SE JA EXISTIREM ficheiros eles seram substituidos");
                printf("\n\nClique 'ENTER' para continuar / Clique 'ESC' para voltar atras");
                c = getch();

                    if(c == 13){
                        getchar();
                        renameBackup(0);
                    }else if(c == 27){
                        getchar();
                        return;          
                    }
                    else{
                        printf("[ERROR]Operacao Invalida");
                    }
            }
        
    break;

    case 2:
            if(fMed == 0){
                printf("\nDeseja carregar o ficheiro Backup-Utentes ?\n");
                printf("[AVISO] Ao executar esta funcao SE JA EXISTIREM ficheiros eles seram substituidos");
                printf("\n\nClique 'ENTER' para continuar / Clique 'ESC' para voltar atras");
                c = getch();

                    if(c == 13){
                        getchar();
                        renameBackup(1);
                    }else if(c == 27){
                        getchar();
                        return;          
                    }
                    else{
                        printf("[ERROR]Operacao Invalida");
                    }
            }
        
    break;
    default:
        break;
    }
    getchar();
    fclose(fpMedicos);
    fclose(fpUtentes);
}

void guardarDadosFicheiro(NodeMed *listaMed, NodeUtente *listaUtente, int type, int backup) { //Type indica se vamos guardar 0-utentes 1-medicos 2-ambos;
    NodeMed *auxMed = listaMed;                                                              //Backup e utilizado para criar um backup 0-NAO 1-SIM;
    NodeUtente *auxUtente = listaUtente;

    FILE *fpUtentes;
    FILE *fpMedicos;

    if (backup == 0) {
        fpUtentes = fopen("utentes.txt", "w");
        fpMedicos = fopen("medicos.txt", "w");
    } else {
        fpUtentes = fopen("utentes_backup.txt", "w");
        fpMedicos = fopen("medicos_backup.txt", "w");
    }

    if (fpUtentes == NULL || fpMedicos == NULL) {
        printf("[ERRO] Falha ao encontrar ficheiros");
        return;
    }

    if (type == 0) { // guardar utentes
        if (auxUtente == NULL) {
            printf("\n[ERROR] Lista de Utentes esta vazia");
            getchar();
            return;
        }
        while (auxUtente != NULL) {
            fprintf(fpUtentes, "%s,%li,%li\n", auxUtente->utente.nomeUtente, auxUtente->utente.codigoUtente, auxUtente->utente.codigoMedico);
            fflush(fpUtentes);
            auxUtente = auxUtente->next;
        }
    } else if (type == 1) { // guarda medicos
        if (auxMed == NULL) {
            printf("\n[ERROR] Lista de Medicos esta vazia");
            getchar();
            return;
        }
        while (auxMed != NULL) {
            fprintf(fpMedicos, "%s,%li\n", auxMed->medico.nomeMedico, auxMed->medico.codigoMedico);
            fflush(fpMedicos);
            auxMed = auxMed->next;
        }
    } else if (type == 2) { // guarda ambos
        // guarda os medicos
        if (auxMed == NULL) {
            printf("\n[ERROR] Lista de Medicos esta vazia");
            getchar();
        } else {
            while (auxMed != NULL) {
                fprintf(fpMedicos, "%s,%li\n", auxMed->medico.nomeMedico, auxMed->medico.codigoMedico);
                fflush(fpMedicos);
                auxMed = auxMed->next;
            }
        }
        // guarda os utentes
        if (auxUtente == NULL) {
            printf("\n[ERROR] Lista de Utentes esta vazia");
            getchar();
        } else {
            while (auxUtente != NULL) {
                fprintf(fpUtentes, "%s,%li,%li\n", auxUtente->utente.nomeUtente, auxUtente->utente.codigoUtente, auxUtente->utente.codigoMedico);
                fflush(fpUtentes);
                auxUtente = auxUtente->next;
            }
        }
    } else { // Caso acha algum erro ao chamar a função em outras..
        printf("\n[UNKNOWN ERRO] Type not matching any option");
    }

    fclose(fpUtentes);
    fclose(fpMedicos);
    printf("\n[AVISO] Dados Guardados com Sucesso ....");
    getchar();
    getchar();
}

void lerDadosFicheiros(NodeMed **listaMed, NodeUtente **listaUtente, int type) {
    Utente dadosUtente;
    Medico dadosMedico;

    FILE *fpUtentes = fopen("utentes.txt", "r");
    FILE *fpMedicos = fopen("medicos.txt", "r");

    if (fpUtentes == NULL && fpMedicos == NULL) {
        printf("[ERRO] Impossivel carregar os ficheiros\n");
        return;
    }else{
        printf("[AVISO] Dados Carregados com Sucesso ....");
    }

    if (type == 0) { // LE utentes
        while (fscanf(fpUtentes, "%[^,],%li,%li\n", dadosUtente.nomeUtente, &dadosUtente.codigoUtente, &dadosUtente.codigoMedico) == 3) {
            resgistrarDadosUtente(listaUtente, dadosUtente);
        }
    } else if (type == 1) { // LE medicos
        while (fscanf(fpMedicos, "%[^,],%li\n", dadosMedico.nomeMedico, &dadosMedico.codigoMedico) == 2) {
            resgistrarDadosMedico(listaMed, dadosMedico);
        }
    } else if (type == 2) { // LE ambos
        // LE os medicos
        while (fscanf(fpMedicos, "%[^,],%li\n", dadosMedico.nomeMedico, &dadosMedico.codigoMedico) == 2) {
            resgistrarDadosMedico(listaMed, dadosMedico);
        }

        // LE os utentes
        while (fscanf(fpUtentes, "%[^,],%li,%li\n", dadosUtente.nomeUtente, &dadosUtente.codigoUtente, &dadosUtente.codigoMedico) == 3) {
            resgistrarDadosUtente(listaUtente, dadosUtente);
        }
    } else {
        printf("[UNKNOWN ERRO] Type not matching any option");
        return;
    }

    getchar();

    fclose(fpUtentes);
    fclose(fpMedicos);
}

void menuBackup(NodeMed *listaMed,NodeUtente *listaUtente){
        int opc = 1;

    while(opc != 0){
                system("cls");
                printf("------------------------------------------------------------\n");
                printf(" |[1..]Criar Backup                                       |\n");
                printf(" |[2..]Carregar Backup                                    |\n");
                printf(" |                                                        |\n");
                printf(" |                                                        |\n");
                printf(" |                                                        |\n");
                printf(" |                                                        |\n");
                printf(" |                                                        |\n");
                printf(" |                                                        |\n");
                printf(" |[0..]Sair                                               |\n");
                printf("------------------------------------------------------------\n");
                printf("[?] Digite a opcao desejada: \n");
                printf("[>] ");
                scanf("%d",&opc);

                switch(opc)
                {
                    case 1: guardarDadosFicheiro(listaMed,listaUtente,2,1);break;
                    case 2: procuraBackup();break;
                    case 0: break;
                    default: printf("[ERROR] Opcao Invalida!!");
                }
        }
}



void ficheirosMenu(NodeMed **listaMed,NodeUtente **listaUtente){

    int opc = 1;

    while(opc != 0){
                system("cls");
                printf("------------------------------------------------------------\n");
                printf(" |[1..]Salvar Dados Utentes                               |\n");
                printf(" |[2..]Salvar Dados Medicos                               |\n");
                printf(" |[3..]Carregar Dados Utentes                             |\n");
                printf(" |[4..]Carregar Dados Medicos                             |\n");
                printf(" |[5..]Backup                                             |\n");
                printf(" |                                                        |\n");
                printf(" |                                                        |\n");
                printf(" |                                                        |\n");
                printf(" |[0..]Sair                                               |\n");
                printf("------------------------------------------------------------\n");
                printf("[?] Digite a opcao desejada: \n");
                printf("[>] ");
                scanf("%d",&opc);

                switch(opc)
                {
                    case 1: guardarDadosFicheiro(*listaMed,*listaUtente,0,0);break;
                    case 2: guardarDadosFicheiro(*listaMed,*listaUtente,1,1);break;
                    case 3: lerDadosFicheiros(listaMed,listaUtente,0);;break;
                    case 4: lerDadosFicheiros(listaMed,listaUtente,1);;break;
                    case 5: menuBackup(*listaMed,*listaUtente);break;
                    case 0: break;
                    default: printf("[ERROR] Opcao Invalida!!");
                }
        }
}

//----------------------------------------------Utentes-----------------------------------------------
void resgistrarDadosUtente(NodeUtente **lista,Utente dados){
    NodeUtente *newNode = (NodeUtente*)malloc(sizeof(NodeUtente));
    newNode->utente = dados;
    newNode->next = *lista;
    *lista = newNode;
}

int verificaNumUtente(long int codigo,NodeUtente *lista){
    NodeUtente *aux = lista;
    int foundU = 0;
    char c;
    fflush(stdin);
    while(aux != NULL && foundU == 0){
            if(aux->utente.codigoUtente == codigo){
                printf("\n[ERROR] Numero de utente ja existente");
                printf("\n\nClique 'ENTER' para reinserir os dados / Clique 'ESC' para voltar atras");
                foundU = 1;
                c = getch();

                if(c == 13){
                    return -1;
                }else if(c == 27){
                    return 1;
                }
                else{
                    printf("[ERROR]Operacao Invalida");
                }
                getchar();
            }
            aux = aux->next;
        }
    return 0;
}
int adicionarUtente(NodeMed *listaMed,NodeUtente *listaUt,Utente *utente){
        
        NodeMed *aux = listaMed;
        int foundMed = 0,valid;

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

        valid = verificaNumUtente(utente->codigoUtente,listaUt);
        
        if(valid == -1){
            memset(utente,0,sizeof(Utente));
            goto skip;
        }else if (valid == 1){
            getchar();memset(utente,0,sizeof(Utente));
            return 1;
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
                
                c = getchar();

                    if(c == 13){
                        getchar();
                        memset(utente,0,sizeof(Utente));goto skip;
                    }else if(c == 27){
                        getchar();
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

void editarDadosUtente(NodeUtente **lista,NodeMed *listaMed){
    int op;
    NodeUtente *aux = *lista;
    NodeMed *auxMed = listaMed;
    char nomeMed[maxnome],c;

    int encontrou = 0,vald;
    long int codigo, newCode;

    system("cls");
    printf("----------------------------------------------------------\n");
    printf("|                Digite o numero do Utente               |\n");
    printf("----------------------------------------------------------\n|> ");
    fflush(stdin);
    scanf("%li",&codigo);

    while(aux != NULL && encontrou == 0){
        if(aux->utente.codigoUtente == codigo){
            system("cls");
            printf("-------------------------------------------------------\n");
            printf("| Deseja alterar os dados do Utente %s\t\t\b|\n",aux->utente.nomeUtente,aux->utente.codigoUtente);
            printf("-------------------------------------------------------\n");

            printf("\n\nClique 'ENTER' para continuar / Clique 'ESC' para voltar atras");
                
                c = getch();

                    if(c == 13){
                        getchar();
                    }else if(c == 27){
                        getchar();
                        return;          
                    }
                    else{
                        printf("[ERROR]Operacao Invalida");
                    }

            system("cls");
            printf("--------------------------------------------------------\n");
            printf("| Alterando os dados do Utente %s (%li) \t\t\b|\n",aux->utente.nomeUtente,aux->utente.codigoUtente);
            printf("--------------------------------------------------------");
            printf("\n|[1..] Nome                                            |");
            printf("\n|[2..] Numero                                          |");
            printf("\n|[3..] Medico                                          |");
            printf("\n|                                                      |");
            printf("\n|[0..] Sair                                            |");
            printf("\n--------------------------------------------------------\n|> ");
            fflush(stdin);
            scanf("%d",&op);

            switch(op){
                case 1:
                    system("cls"); 
                    printf("--------------------------------------------------------\n");
                    printf("|                   Insira o novo nome                 |\n");
                    printf("\n--------------------------------------------------------\n|> ");
                    fflush(stdin);
                    gets(aux->utente.nomeUtente);
                    break;

                case 2:
                    skip_numUtente:
                    system("cls");    
                    printf("--------------------------------------------------------\n");
                    printf("|           Insira o novo numero de Utente             |  ");
                    printf("\n--------------------------------------------------------\n|> ");
                    fflush(stdin);
                    scanf("%li", &newCode);
                    vald = verificaNumUtente(newCode,aux);
                    if (vald == 0){
                        aux->utente.codigoUtente = newCode;
                        printf("|                                                        |\n");
                        printf("| Alterado com sucesso !! Novo codigo : %li            |\n",aux->utente.codigoUtente);
                        printf("\n--------------------------------------------------------\n|> ");
                    }else if(vald == 1){
                        goto skip_numUtente;
                    }
                    break;
                case 3:
                    skip_numMedico:
                    system("cls");    
                    printf("--------------------------------------------------------\n");
                    printf("|           Insira o numero do novo Medico             |\n");
                    printf("\n--------------------------------------------------------\n|> ");
                    fflush(stdin);
                    scanf("%li", &newCode);
                    vald = verificaNumMedico(newCode,auxMed,0);
                    if (vald == 1){
                        aux->utente.codigoMedico = newCode;
                        nomeMedico(aux->utente.codigoMedico,auxMed,nomeMed);
                        printf("|                                                      |\n");
                        printf("| Alterado com sucesso !! Novo Medico : %s\t\t\b|\n",nomeMed);
                        printf("\n--------------------------------------------------------\n|> ");

                    }else if(vald == 0){
                        goto skip_numMedico;
                    }
                break;

                case 0: break;

                default: printf("Opção Inválida");
            }
            encontrou = 1;
        }
        aux = aux->next;
    }
    
    if(encontrou == 0) 
    printf("\n[ERROR] Falha ao encontrar o Utente");

    printf("\n\nClique 'ENTER' para continuar.. ");
    fflush(stdin);
    getchar();
}

void consultarDadosUtente(NodeUtente *listaUtente,NodeEspera *listaEspera){
    NodeUtente *auxUtente = listaUtente;
    NodeEspera *lastNode = NULL;
    NodeEspera *auxEspera = listaEspera;

    long int codigo;
    int i = 0,encontrou = 0;

    system("cls");
    printf("----------------------------------------------------------\n");
    printf("|                Digite o numero do Utente               |\n");
    printf("----------------------------------------------------------\n|> ");
    fflush(stdin);
    scanf("%li",&codigo);

    if(auxEspera == NULL){
        lastNode = NULL;
    }else{
        lastNode = auxEspera->end;
    }
    if(auxUtente == NULL){
        printf("[ERROR] Lista de Utentes vazia");
        return;
    }



    while(auxUtente != NULL && !encontrou){
        if(auxUtente->utente.codigoUtente == codigo){  
            if(lastNode != NULL){
                while(lastNode != NULL && !encontrou){
                    Utente *dados = lastNode->UT;
                    if( auxUtente->utente.codigoUtente == dados->codigoUtente){
                        encontrou = 1;
                        i++;
                        break;
                    }
                    i++;
                    lastNode = lastNode->prev;
                }
            }
            printf("----------------------------------------------------------\n");
            printf("|Nome: %s \t\t\t\t\t\t|",auxUtente->utente.nomeUtente);
            printf("\n|Codigo: %li \t\t\t\t\t\t|",auxUtente->utente.codigoUtente);
            if(i != 0){
                printf("\n|Lugar na Fila de Espera: %d \t\t\t\t|",i);
            }else{
                printf("\n|Utente nao se encontra em Espera \t\t\t|");
            }
            printf("\n----------------------------------------------------------\n");
            encontrou = 1;
        }
        auxUtente = auxUtente->next;
    }
    getchar();
    getchar();
}

void listaUtentesVer(NodeUtente *dados,NodeMed *dadosMed){
        NodeUtente *aux = dados;    
        NodeMed *auxMed = dadosMed;  
        char nome[maxnome];


        system("cls");
        printf("---------------------------------------------------------\n");
        printf(" |               Lista de Utentes                      |\n");
        printf("---------------------------------------------------------\n");
        
        if(aux == NULL){
            printf(" | \t\t\b\b\bA Lista encontra-se .. VAZIA .. \t\t\b|\n");
        }
        while (auxMed != NULL) {
            nomeMedico(aux->utente.codigoMedico, auxMed, nome);
            while (aux != NULL) {
                printf(" | [%li] %s ->\t%s\t\t\t\t\b|\n", aux->utente.codigoUtente, aux->utente.nomeUtente, nome);
                aux = aux->next;
            }

            auxMed = auxMed->next;
        }
            
        printf("---------------------------------------------------------\n");
    printf("\n\nClique 'ENTER' para continuar.. ");
    fflush(stdin);
    getchar();
}

void listaUtenteMenu(NodeMed **lista,NodeUtente **listaUtente,NodeEspera *listaEspera){
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
            printf("|[4..]Consultar Utente                                   |\n");
            printf("|[5..]Consultar Lista de Utentes                         |\n");
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
                case 3: editarDadosUtente(listaUtente,*lista);break;
                case 4: consultarDadosUtente(*listaUtente,listaEspera);break;
                case 5: listaUtentesVer(*listaUtente,*lista);break;
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
    // AVISO : com muitos lapsos ,pois ele pode colocar um numero e depois uma letra da erro , so foi feito para uma confirmacao rapida
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

    if(listaEspera == NULL){
        printf("\n[ERRO] Lista de Espera esta ....VAZIA....");
        getchar();
        getchar();
        return;
    }

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

void removerDaListaEspera(NodeEspera **listaEspera,NodeMed *listaMed){
    NodeEspera *lastNode = NULL; 
    NodeEspera *auxEspera = *listaEspera;
    NodeMed *auxMed = listaMed;

    lastNode = auxEspera->end; 

    long int codigo;
    int encontrou = 0;

    system("cls");
    printf("--------------------------------------------------------\n");
    printf("|               Digite o numero do Medico              |\n");
    printf("--------------------------------------------------------\n");
    printf("[Numero Medico] ");
    scanf("%li",&codigo);

    while(auxMed != NULL && !encontrou){
        if(auxMed->medico.codigoMedico == codigo){
            encontrou = 1;
        }
    }
    if (encontrou != 1){
        printf("\n[ERRO] Dados introduzidos incorretamente / Medico nao encontrado");
        return;
    }

    if(lastNode == NULL){
        printf("[ERRO] Lista de Espera vazia ");
        return;
    }

    if (lastNode->prev != NULL) {
        auxEspera->end = lastNode->prev;
        lastNode = NULL;
    } else {
        *listaEspera = NULL;
    }
    return;
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

    
    if(aux == NULL){
        printf("\n\n[ :D ] Lista de espera vazia\n");
        getchar();
        getchar();
        return;
    }
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
        printf("\n\nClique 'ENTER' para continuar.. ");
    
    fflush(stdin);
    getchar();
}

void listaEsperaMenu(NodeMed **listaMed,NodeUtente **listaUt,NodeEspera **listaEspera){
    //Vars
    int opc = 1;
   
    while(opc != 0){
            system("cls");
            printf("--------------------------------------------------------\n");
            printf("|[1..]Check-in Utente                                  |\n");
            printf("|[2..]Atender Utente da Lista                          |\n");
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
            case 2: removerDaListaEspera(listaEspera,*listaMed);break;  
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

int verificaNumMedico(long int codigo,NodeMed *lista,int type){
    NodeMed *aux = lista;
    char c;

    while(aux != NULL){
            if(codigo == aux->medico.codigoMedico){
                if(type == 1){
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
                }else{
                    return 1;
                }
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
        vald = verificaNumMedico(medico->codigoMedico,lista,1);
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
                    vald = verificaNumMedico(newCode,*lista,1);
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

        system("cls");
                   

        printf("\n----------------------------------------------------------\n");
        printf(" |               Lista de Medicos                       | \n");
        printf("----------------------------------------------------------\n");
        printf(" |                                                      | \n");
        while(aux != NULL){
            printf(" | [%li] %s \t\t\t\t\t\t|\n",aux->medico.codigoMedico,aux->medico.nomeMedico);
            printf(" |                                                      | \n");
            aux = aux->next;
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
    //Leitura dos ficheiros
    lerDadosFicheiros(&lista,&listaUtente,2);
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
        printf("  |[4..]Ficheiros                                        |\n");
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
        case 2: listaUtenteMenu(&lista,&listaUtente,listaEspera);break;
        case 3: listaEsperaMenu(&lista,&listaUtente,&listaEspera);break;
        case 4: ficheirosMenu(&lista,&listaUtente);break;
        case 0: guardarDadosFicheiro(lista,listaUtente,2,0);break;
        default: printf("[ERROR] Opcao Invalida!!");
        }
    }
    free(lista);free(listaUtente);free(listaEspera);

    return 0;
}