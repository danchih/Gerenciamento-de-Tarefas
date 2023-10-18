#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>   //necessario para usar localtime() e struct tm
#include "BIBLIOTECAS.h"

int menu()
{
/*Funcao utilizada para imprimir menu de inicio
*/
    int indice;

    do{
    system("cls");
    printf("\n----------------------------------- GERENCIAMENTO DE TAREFAS ------------------------------------\n");
    printf("\n\n [1] Adicionar Novas Tarefas");
    printf("\n [2] Modificar Dados de uma Tarefa");
    printf("\n [3] Concluir uma Tarefa");
    printf("\n [4] Imprimir Tarefas");
    printf("\n [5] Sair");

    printf("\n\n\n Digite o Numero de uma das opcoes acima: ");
    scanf("%d", &indice);
    }while(indice<1 || indice>5);

    return indice;
}


void menuImpressao(Fila *F1, Fila *F2, Fila *F3, Lista *Pendente, Lista *Concluida)
{
/*Funcao utilizada para imprimir as Filas/Listas
  Parametro(s) recebido(s): F1, F2, F3, Pendente, Concluida
*/
    int n;

    printf("\n------------------------------------- IMPRESSAO DE TAREFAS --------------------------------------\n");
    printf("\n\n [1] Lista de Tarefas Pendentes");
    printf("\n [2] Lista de Tarefas Concluidas");
    printf("\n [3] Lista de Tarefas Concluidas (de acordo com o Status) \n");
    printf("\n [4] Fila com as Tarefas de Alta Prioridade");
    printf("\n [5] Fila com as Tarefas de Prioridade Normal");
    printf("\n [6] Fila com as Tarefas de Baixa Prioridade \n");
    do{
        printf("\nQual lista deseja imprimir? (Digite o Numero do Indice): ");
        scanf("%d", &n);
    }while(n<1 || n>6);

    switch(n){
        case 1:
            printf("\nLISTA DE TAREFAS PENDENTES ----------------------------------------------------------------------\n");
            imprimeLista(Pendente);
            break;
        case 2:
            printf("\nLISTA DE TAREFAS CONCLUIDAS ---------------------------------------------------------------------\n");
            imprimeLista(Concluida);
            break;
        case 3:
            printf("\nLISTA DE TAREFAS CONCLUIDAS (DE ACORDO COM SEU STATUS) ------------------------------------------\n");
            ImprimeAtraso(Concluida);
            break;
        case 4:
            printf("\nFILA DE TAREFAS DE ALTA PRIORIDADE --------------------------------------------------------------\n");
            imprimeFila(F1);
            break;
        case 5:
            printf("\nFILA DE TAREFAS DE PRIORIDADE NORMAL ------------------------------------------------------------\n");
            imprimeFila(F2);
            break;
        case 6:
            printf("\nFILA DE TAREFAS DE BAIXA PRIORIDADE -------------------------------------------------------------\n");
            imprimeFila(F3);
            break;
        }
}


void getStatus(int *status, int *dia, int *mes, int *ano, int *varC)
{
/*Funcao utilizada para setar o valor do Status de acordo com a Data de Termino
  Parametro(s) recebido(s): status, dia, mes, ano, varC
*/
    struct tm *data_atual;                  //struct que ira armazenar a data atual
    int diaAtual, mesAtual, anoAtual;
    int sAtual = 0, sFim = 0;

    time_t segundos;                        //time_t armazena o tempo em segundos
    time(&segundos);                        //obtem o tempo em segundos
    data_atual = localtime(&segundos);      //converte o valor de segundo para o tempo local

    diaAtual = data_atual->tm_mday;         //retorna a data atual
    mesAtual = data_atual->tm_mon +1;       //para retornar o mes corretamente devemos adicionar +1
    anoAtual = data_atual->tm_year + 1900;  //para retornar o ano corretamente devemos adicionar 1900

    sAtual = anoAtual*10000 + mesAtual*100 + diaAtual; //faz a soma das datas do dia atual (exemplo: 20231001)
    sFim = (*ano)*10000 + (*mes)*100 + (*dia);         //faz a soma da data de termino da tarefa (exemplo: 20241104)


    if(*varC == 1){                //caso a tarefa seja concluida, a data de termino muda para a data atual
        *dia = diaAtual;
        *mes = mesAtual;
        *ano = anoAtual;

    }else{                         //caso contrario,
        if(sAtual > sFim)          //caso o valor da soma da data atual seja maior que a soma de termino, a tarefa esta atrasada(1)
            *status = 1;
        else                       //caso contrario a tarefa esta em dia(0)
            *status = 0;
    }

}


void leituraData(int *d, int *m, int *a)
{
/*Funcao utilizada para fazer a leitura das Datas de forma organizada
  Parametro(s) recebido(s): d, m, a
*/
    int dia, mes, ano;
    do{
        printf("Dia(1 a 31).....: ");
        scanf("%d", &dia);
    }while(dia<1 || dia>31);        //faz a leitura do dia (entre 1 e 31)
    do{
        printf("Mes(1 a 12).....: ");
        scanf("%d", &mes);
    }while(mes<1 || mes>12);        //faz a leitura do mes de janeiro(1) ate dezembro(12)

    printf("Ano(aaaa).......: ");
    scanf("%d", &ano);              //faz a leitura do ano

    *d = dia;   // passa aos valores que foram lidos na funcao para os parametros chamados
    *m = mes;
    *a = ano;
}


void Adiciona(Fila *F1, Fila *F2, Fila *F3, int *varC)
{
/*Funcao utilizada para adicionar Tarefas em uma Fila de Tarefas
  Parametro(s) recebido(s): F1, F2, F3, varC
*/
    int inserir, count = 0;
    tarefa t;
    printf("\nQuantas tarefas deseja inserir? ");
    scanf("%d", &inserir);                       //quantidade de tarefas que serao inseridas na fila
    do{
        printf("\nTAREFA %d: ---------------------------------------------------------------------------------------", count+1);
        printf("\nCodigo da tarefa: ");
        scanf("%d", &t.codigo);

        printf("Nome da tarefa: ");
        fflush(stdin);
        gets(t.nome);

        printf("Nome do Projeto que pertence a tarefa: ");
        fflush(stdin);
        gets(t.projeto);

        printf("Data de Inicio da tarefa: \n");
        leituraData(&t.inicio.dia, &t.inicio.mes, &t.inicio.ano);

        printf("Data de Termino da tarefa: \n");
        leituraData(&t.fim.dia, &t.fim.mes, &t.fim.ano);                  //chama a funcao leituraData para ler a data

        getStatus(&t.status, &t.fim.dia, &t.fim.mes, &t.fim.ano, varC);   //chama a funcao getStatus para mudar o status

        do{
            printf("\nPrioridades da Tarefa: - [1] Alta Prioridade ---- [2] Prioridade Normal ---- [3] Baixa Prioridade");
            printf("\n\nDigite o Indice da Prioridade da Tarefa: ");
            scanf("%d", &t.prioridade);
        }while(t.prioridade!=1 && t.prioridade!=2 && t.prioridade!=3);

        switch(t.prioridade){       //utiliza-se o switch case para saber em qual fila deve-se inserir a tarefa
            case 1:
                InsereFila(F1, t);  //Alta Prioridade
                break;
            case 2:
                InsereFila(F2, t);  //Prioridade Normal
                break;
            case 3:
                InsereFila(F3, t);  //Baixa Prioridade
                break;
        }

        count ++;
    }while(inserir != count);   //faz a repeticao ate que a quantidade de tarefas solicitadas sejam criadas
}


char menuModifica(Fila *F1, Fila *F2, Fila *F3, Lista *pendente, int *varC, struct no *aux, int encontro, int *mF)
{
/*Funcao que faz o menu da funcao modifica
  Parametro(s) recebido(s): F1, F2, F3, pendente, varC, aux, encontro, mF
*/
    int n;
    char statusResp;

    printf("\n[1] Codigo: %d", aux->info.codigo);
    printf("\n[2] Nome da Tarefa: %s", aux->info.nome);
    printf("\n[3] Nome do Projeto: %s", aux->info.projeto);
    printf("\n[4] Data de Inicio: %d/%d/%d", aux->info.inicio.dia, aux->info.inicio.mes, aux->info.inicio.ano);
    printf("\n[5] Data de Termino: %d/%d/%d", aux->info.fim.dia, aux->info.fim.mes, aux->info.fim.ano);
    if(aux->info.status == 0)
        printf("\n[6] Status: Em Dia");
    else if(aux->info.status == 1)
        printf("\n[6] Status: Atrasada");
    else
        printf("\n[6] Status: Pendente");

    if(aux->info.prioridade == 1)
        printf("\n[7] Prioridade: Alta Prioridade \n");
    else if(aux->info.prioridade == 2)
        printf("\n[7] Prioridade: Prioridade Normal \n");
    else
        printf("\n[7] Prioridade: Baixa Prioridade \n");


    do{
        printf("\nQual dado voce deseja alterar? (Digite o Numero do Indice): ");
        scanf("%d", &n);
    }while(n<1 || n>7);

    switch(n){  //utiliza-se o switch case para saber qual dado o usuario deseja editar
        case 1:
            printf("\nNovo Codigo: ");              //altera o codigo
            scanf("%d", &aux->info.codigo);
            break;
        case 2:
            printf("\nNovo Nome: ");                //altera o nome
            fflush(stdin);
            gets(aux->info.nome);
            break;
        case 3:
            printf("\nNovo Nome do Projeto: ");     //altera o nome do projeto
            fflush(stdin);
            gets(aux->info.projeto);
            break;
        case 4:
            printf("\nNova Data de Inicio: \n");    //altera a data de inicio
            leituraData(&aux->info.inicio.dia, &aux->info.inicio.mes, &aux->info.inicio.ano);
            break;
        case 5:
            printf("\nNova Data de Termino: \n");   //altera a data de fim e dependendo dela altera o status automaticamente
            leituraData(&aux->info.fim.dia, &aux->info.fim.mes, &aux->info.fim.ano);
            getStatus(&aux->info.status, &aux->info.fim.dia, &aux->info.fim.mes, &aux->info.fim.ano, varC);
            break;
        case 6:
            if(encontro == 1){      //caso o valor de encontro recebido seja 1(esta na fila) da a opcao de colocar a tarefa na lista de pendentes
                do{
                    printf("\nDeseja alterar o Status da tarefa para PENDENTE? (s/n): ");
                    fflush(stdin);
                    scanf("%c", &statusResp);
                }while(toupper(statusResp)!='S' && toupper(statusResp)!='N');
            }

            if(encontro == 2){      //caso o valor do encontro recebido seja 2(esta na lista de pendentes)
                do{                 //da a opcao de remover a tarefa da lista pendente e retornar a tarefa ao final da fila
                    printf("\nDeseja REMOVER o Status PENDENTE da tarefa? (s/n): ");
                    fflush(stdin);
                    scanf("%c", &statusResp);
                }while(toupper(statusResp)!='S' && toupper(statusResp)!='N');
            }
            break;
        case 7:
            do{
                printf("\nPrioridades da Tarefa: - [1] Alta Prioridade ---- [2] Prioridade Normal ---- [3] Baixa Prioridade");
                printf("\n\nDigite o Indice da Prioridade da Tarefa: ");
                scanf("%d", &aux->info.prioridade);
            }while(aux->info.prioridade!=1 && aux->info.prioridade!=2 && aux->info.prioridade!=3);

            *mF=1;  //mF esta sendo utilizada para saber se houve mudanca na prioridade da Fila

            if(encontro == 1){
                switch(aux->info.prioridade){   //insere na Fila adequada de acordo com a prioridade
                    case 1:
                        InsereFila(F1, aux->info);
                        break;
                    case 2:
                        InsereFila(F2, aux->info);
                        break;
                    case 3:
                        InsereFila(F3, aux->info);
                        break;
                }
            }

            break;
    }
    return statusResp;  //retorna a resposta referente a mudanca de status
}


Fila* VerificaFila(Fila *F1, Fila *F2, Fila *F3, int cod)
{
/*Funcao que ira identificar em qual das filas existe o codigo pesquisado
  Parametro(s) recebido(s): F1, F2, F3, cod
*/
    No *aux1 = F1->ini, *aux2 = F2->ini, *aux3 = F3->ini;

     while(aux1 != NULL){               //percorre a Fila 1 para ver se a tarefa esta nela
        if(aux1->info.codigo == cod)
            return F1;                  //caso encontre, passa ela
        else
            aux1 = aux1->prox;
     }

     while(aux2 != NULL){               //percorre a Fila 2 para ver se a tarefa esta nela
        if(aux2->info.codigo == cod)
            return F2;                  //caso encontre, passa ela
        else
            aux2 = aux2->prox;
     }

     while(aux3 != NULL){               //percorre a Fila 3 para ver se a tarefa esta nela
        if(aux3->info.codigo == cod)
            return F3;                  //caso encontre, passa ela
        else
            aux3 = aux3->prox;
     }

     return NULL;                       //caso a tarefa nao exista em nenhuma das Filas, retorna NULL
}


Lista* ModificaFL(Fila *F1, Fila *F2, Fila *F3, Lista *pendente, int *varC)
{
/*Funcao que busca a tarefa (na fila e na lista de pendentes) e modifica os dados dela
  Parametro(s) recebido(s): F1, F2, F3, pendente, varC
*/
    int cod, encontro = 0;
    int mudancaF = 0;       //mudancaF sera utilizada pra identificar se houve mudanca na Fila de acordo com a prioridade
    char resp, statusResp;
    tarefa t;
    Lista *auxL = pendente;
    Fila *F;
    Fila *F_auxiliar=CriaFila();

    printf("\nDigite o Codigo da Tarefa que deseja editar: ");
    scanf("%d", &cod);

    F = VerificaFila(F1, F2, F3, cod);

    if(F != NULL){          //caso a Fila F seja NULL, ela nem tenta percorrer a mesma
        No *auxF = F->ini;

        while(auxF != NULL){    //percorre todos os elementos da Fila

            if(auxF->info.codigo == cod && encontro != 1){  //verifica se o codigo existe na fila e se ele ja foi encontrado anteriormente
                encontro = 1;
                do{
                    statusResp = menuModifica(F1, F2, F3, pendente, varC, auxF, encontro, &mudancaF);   //modifica a tarefa e recebe a resposta referente ao valor de status

                    if(mudancaF == 1){              //caso haja mudanca nas filas de prioridade
                        auxF = auxF->prox;
                        t = RetiraFila(F);          //retira da fila que o codigo da tarefa se encontra
                    }

                    if(toupper(statusResp)=='S'){   //caso seja S muda o estatos para -1(pendente)
                        auxF->info.status = -1;
                        auxF = auxF->prox;          //move o auxiliar para o proximo elemento

                        pendente = ListaPendente(pendente, RetiraFila(F));    //retira a tarefa da fila e coloca ela na lista de Pendentes
                    }                                                               //ordenada do acordo com a data de termino

                    printf("\nDeseja alterar mais algum dados (s/n)? ");
                    fflush(stdin);
                    scanf("%c", &resp);

                    if(toupper(resp)=='S' && (toupper(statusResp)=='S' || mudancaF == 1)){
                        printf("\nTAREFA ACABOU DE MUDAR DE LOCALIZACAO!!! TENTE PESQUISAR POR ELA NOVAMENTE PARA MODIFICA-LA.");
                    }

                }while(toupper(resp)!='N' && toupper(statusResp)!='S' && mudancaF != 1); //faz a repeticao enquanto resp for diferente de N e nao houver mudanca nas filas
            }
            else{
                auxF = auxF->prox;
                InsereFila(F_auxiliar,RetiraFila(F));   //fila auxiliar para poder rodar a fila original e retirar um valor do meio caso necessario
            }
        }

        //retorna os valores da fila auxiliar para a fila original
        No *aux1 = F_auxiliar->ini;
        while(aux1!=NULL){
            aux1=aux1->prox;
            InsereFila(F,RetiraFila(F_auxiliar));
        }
    }


    while(auxL != NULL && encontro != 1){       //percorre toda a lista de pendentes apenas se o codigo nao for achado na fila anterior (encontro != 1)

        if(auxL->info.codigo == cod && encontro != 2){  //caso encontre o codigo e que nao tenha sido achado anteriormente
            encontro = 2;
            do{
                statusResp = menuModifica(F1, F2, F3, pendente, varC, auxL, encontro, &mudancaF);   //modifica a tarefa e recebe a resposta do status

                if(toupper(statusResp)=='S'){   //caso a resposta seja S
                    getStatus(&auxL->info.status, &auxL->info.fim.dia, &auxL->info.fim.mes, &auxL->info.fim.ano, varC); //atualiza automaticamente o status

                    switch(auxL->info.prioridade){   //insere na Fila adequada de acordo com a prioridade
                        case 1:
                            InsereFila(F1, auxL->info);
                            break;
                        case 2:
                            InsereFila(F2, auxL->info);
                            break;
                        case 3:
                            InsereFila(F3, auxL->info);
                            break;
                    }
                    pendente = RetiraLista(pendente, auxL->info.codigo);    //retira a tarefa da lista de pendentes
                }

                printf("\nDeseja alterar mais algum dados (s/n)? ");
                fflush(stdin);
                scanf("%c", &resp);
                if(toupper(resp)=='S' && toupper(statusResp)=='S'){
                    printf("\nTAREFA ACABOU DE MUDAR DE LOCALIZACAO!!! TENTE PESQUISAR POR ELA NOVAMENTE PARA MODIFICA-LA.");
                }

            }while(toupper(resp)!='N' && toupper(statusResp)!='S'); //faz a repeticao enquanto resp for diferente de N
        }
        auxL =auxL->prox;
    }

    if(encontro == 0)    //verifica se a tarefa existe no sistema. Caso encontro for 0, ela nao foi encontrada
        printf("\nTarefa nao encontrada no Sistema!!!");

    return pendente;

}


Lista* Conclui(Fila *F1, Fila *F2, Fila *F3, Lista *C, int *varC)
{
/*Funcao utilizada para Concluir uma Tarefa
  Parametro(s) recebido(s): F1, F2, F3, C, varC
*/
    char feita;
    int cod, encontrado = 0;
    Fila *F;
    Fila *Fauxiliar = CriaFila();

    printf("\nDigite o Codigo da Tarefa que deseja concluir: ");
    scanf("%d", &cod);

    F = VerificaFila(F1, F2, F3, cod);

    if(F != NULL){      //caso a Fila F seja NULL, ela nem tenta percorrer a mesma
        No *aux = F->ini;

        while(aux!=NULL){       //percorre a lista em busca da tarefa desejada
           if(aux->info.codigo == cod && encontrado != 1){  //caso encontre
                encontrado = 1;

                printf("\nCodigo: %d", aux->info.codigo);
                printf("\nNome da Tarefa: %s", aux->info.nome);
                printf("\nNome do Projeto: %s", aux->info.projeto);
                printf("\nData de Inicio: %d/%d/%d", aux->info.inicio.dia, aux->info.inicio.mes, aux->info.inicio.ano);
                printf("\nData de Termino: %d/%d/%d", aux->info.fim.dia, aux->info.fim.mes, aux->info.fim.ano);
                if(aux->info.status == 0)
                    printf("\nStatus: Em Dia");
                else if(aux->info.status == 1)
                    printf("\nStatus: Atrasada");
                else
                    printf("\nStatus: Pendente");

                if(aux->info.prioridade == 1)
                    printf("\nPrioridade: Alta Prioridade \n");
                else if(aux->info.prioridade == 2)
                    printf("\nPrioridade: Prioridade Normal \n");
                else
                    printf("\nPrioridade: Baixa Prioridade \n");

                do{
                   printf("\nDeseja marcar como Tarefa Concluida? (s/n): "); //verifica se a pessoa deseja concluir a tarefa
                    fflush(stdin);
                    scanf("%c", &feita);
                }while(toupper(feita)!='S' && toupper(feita)!='N');

                if(toupper(feita)=='S'){        //caso queira
                    *varC = 1;                  //seta a variavel varC = 1 para poder alterar a data de termino para atual sem mudar o status da tarefa
                    getStatus(&aux->info.status, &aux->info.fim.dia, &aux->info.fim.mes, &aux->info.fim.ano, varC);
                    aux = aux->prox;
                    C = InsereListaOrdenada(C,RetiraFila(F));   //retira tarefa da fila e coloca ela na lista de concluidas
                }
           }
           else{
                aux = aux->prox;
                InsereFila(Fauxiliar,RetiraFila(F));
           }
        }
    }

    if (encontrado == 0){
        printf("\nTarefa nao encontrada no Sistema!!!");
    }

    //retorna os valores da fila auxiliar para a fila original
    No *aux1 = Fauxiliar->ini;
    while(aux1!=NULL){
        aux1=aux1->prox;
        InsereFila(F,RetiraFila(Fauxiliar));
    }

    *varC = 0;  //seta a variavel varC = 0 para retornar o seu valor original apos selecionar a tarefa que queria concluir
    return C;
}


void ImprimeAtraso(Lista *L)
{
/*Funcao para imprimir tarefas concluidas de acordo com o status
  Parametro(s) recebido(s): L
*/
    Lista *L1 = CriaLista();
    Lista *L2 = CriaLista();
    Lista *p = L;


    while(p!=NULL)  //percorre a lista concluida original
    {
        if(p->info.status == 0){
            L1=InsereListaOrdenada(L1,p->info); //caso o status seja 0(em dia), L1 recebe o valor da tarefa
        }else{
            L2=InsereListaOrdenada(L2,p->info); //caso seja 1(atrasado), L2 recebe o valor da tarefa
        }
        p=p->prox;
    }

    printf("\nTAREFAS SEM ATRASO: \n");
    imprimeLista(L1);                   //imprime todas as tarefas sem atraso

    printf("\nTAREFAS COM ATRASO: \n");
    imprimeLista(L2);                   //imprime todas as tarefas com atraso
}


int main()
{
    Fila *F1, *F2, *F3;          //filas do sistema
    Lista *Pendente, *Concluida; //listas do sistema
    F1 = CriaFila();
    F2 = CriaFila();
    F3 = CriaFila();
    Pendente = CriaLista();
    Concluida = CriaLista();
    int variavelConcluida = 0;   //variavel utilizada para mudar a data das tarefas concluidas sem alterar o status
    int indice;

    do{
        indice = menu();
        system("cls");

        switch(indice){
            case 1:
                printf("\n------------------------------------- ADICIONA NOVA TAREFA --------------------------------------\n");
                Adiciona(F1, F2, F3, &variavelConcluida);
                break;
            case 2:
                printf("\n----------------------------------- MODIFICA TAREFA EXISTENTE -----------------------------------\n");
                Pendente = ModificaFL(F1, F2, F3, Pendente, &variavelConcluida);
                break;
            case 3:
                printf("\n--------------------------------------- CONCLUI DE TAREFA ---------------------------------------\n");
                Concluida = Conclui(F1, F2, F3, Concluida, &variavelConcluida);
                break;
            case 4:
                menuImpressao(F1, F2, F3, Pendente, Concluida);
                break;
            case 5:
                liberaFila(F1);
                liberaFila(F2);
                liberaFila(F3);
                liberaLista(Pendente);
                liberaLista(Concluida);
                printf("\n\nFIM DO PROGRAMA...\n");
                break;
        }

        getchar();
        printf("\n\nDigite a tecla ENTER para continuar...");   //utilizado para manter na tela ate que o usuario deseje proseguir para a proxima tela
        getchar();

    }while(indice != 5);


    return 0;
}

