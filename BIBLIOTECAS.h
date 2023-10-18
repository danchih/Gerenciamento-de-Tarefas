#ifndef BIBLIOTECAS_H_INCLUDED
#define BIBLIOTECAS_H_INCLUDED


/* FUNCOES DE MANIPULACAO DE FILA

Fila* CriaFila() CRIA A FILA

int VaziaFila (Fila* f) VERIFICA SE A FILA ESTA VAZIA

void InsereFila (Fila* f, tarefa v) INSERCAO NO FIM

tarefa RetiraFila (Fila* f) REMOCAO NO INICIO

void imprimeFila (Fila* f)IMPRIME A FILA

Fila* liberaFila (Fila* f) LIBERA A FILA
*/

/* FUNCOES DE MANIPULACAO DE LISTA

Lista* CriaLista() CRIA UMA LISTA VAZIA

int VaziaLista(Lista* L) VERIFICA SE A LISTA ESTA VAZIA

Lista* InsereListaOrdenada(Lista* l, tarefa t) INSERCAO ORDENADA NA LISTA DE ACORDO COM AS DATAS DE TERMINO DA TAREFA (CRESCENTE)

Lista* ListaPendente(Lista* l, tarefa t) INSERCAO ORDENADA NA LISTA DE ACORDO COM AS DATAS DE TERMINO DA TAREFA (CRESCENTE) E A PRIORIDADE

Lista* RetiraLista(Lista* L, int r) REMOCAO EM QUALQUER LUGAR DA LISTA

void imprimeLista(Lista* L) IMPRIME A LISTA

void liberaLista(Lista* L) LIBERA A LISTA

*/

typedef struct Data
{
    int dia;
    int mes;
    int ano;
}data;

typedef struct info_tarefas
{
    int codigo;
    char nome[30];
    char projeto[30];
    data inicio;
    data fim;
    int status;
    int prioridade;

}tarefa;

//FILA --------------------------------------------------------------------------------------------------------------------------
typedef struct nos
{
    tarefa info;
    struct nos *prox;
}No;

typedef struct fila
{
    No * ini;
    No * fim;
} Fila;


int VaziaFila (Fila* f)
{
    if (f->ini==NULL) return 1;
    return 0;

}

Fila* CriaFila ()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

No* ins_fim (No* fim, tarefa A)
{
    No* p = (No*) malloc(sizeof(No));
    p->info = A;
    p->prox = NULL;
    if (fim != NULL) /* verifica se lista nao estava vazia */
    fim->prox = p;
    return p;
}

void InsereFila (Fila* f, tarefa v)
{
    f->fim = ins_fim(f->fim,v);
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

No* retira_ini (No* ini)
{
    No* p = ini->prox;
    free(ini);
    return p;
}

tarefa RetiraFila (Fila* f)
{
    tarefa v;
    if (VaziaFila(f))
    {
        printf("Fila vazia.\n");
        exit(0); /* aborta programa */
    }
    v = f->ini->info;
    f->ini = retira_ini(f->ini);
    if (f->ini == NULL) /* fila ficou vazia? */
    f->fim = NULL;
    return v;
}

void imprimeFila (Fila* f)
{
    No* q;

    if(!VaziaFila(f)){
        for(q=f->ini; q!=NULL; q=q->prox){
            printf("\nCodigo: %d", q->info.codigo);
            printf("\nNome da Tarefa: %s", q->info.nome);
            printf("\nNome do Projeto: %s", q->info.projeto);
            printf("\nData de Inicio: %d/%d/%d", q->info.inicio.dia, q->info.inicio.mes, q->info.inicio.ano);
            printf("\nData de Termino: %d/%d/%d", q->info.fim.dia, q->info.fim.mes, q->info.fim.ano);
            if(q->info.status == 0)
                printf("\nStatus: Em Dia");
            else if(q->info.status == 1)
                printf("\nStatus: Atrasada");
            else
                printf("\nStatus: Pendente");

            if(q->info.prioridade == 1)
                printf("\nPrioridade: Alta Prioridade \n");
            else if(q->info.prioridade == 2)
                printf("\nPrioridade: Prioridade Normal \n");
            else
                printf("\nPrioridade: Baixa Prioridade \n");
        }

    }else
        printf("\nA Fila esta vazia no momento...\n");

}

void liberaFila (Fila* f)
{
    No* q = f->ini;
    while (q!=NULL) {
        No* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
}

//LISTA -------------------------------------------------------------------------------------------------------------------------
typedef struct no
{
    tarefa info;
    struct no *prox;
}Lista;


int VaziaLista(Lista* L)
{
    if(L == NULL){
        return 1;
    }
    return 0;
}

Lista* CriaLista()
{
    return NULL;
}

Lista* InsereListaOrdenada(Lista* l, tarefa t)
{
    Lista* novo = (Lista*) malloc(sizeof(Lista));   //cria o novo elemento da lista
    novo->info = t;
    int dataT = 0;

    Lista* ant = NULL;  //aponta para elemento anterior
    Lista* p = l;       //ponteiro para percorrer a lista

    dataT = t.fim.ano * 10000 + t.fim.mes * 100 + t.fim.dia;    //faz a soma do ano, mes e dia da tarefa para poder comparar com as datas da lista (exemplo: 20231010)


    //procura posicao de insercao de acordo com a data de termino
    while (p != NULL && (p->info.fim.ano * 10000 + p->info.fim.mes * 100 + p->info.fim.dia) < dataT) { //percorre a lista enquanto a data da tarefa for maior que a data do elemento da lista
        ant = p;
        p = p->prox;
    }

    if (ant == NULL) {  //insere elemento no inicio
        novo->prox = l;
        l = novo;
    }
    else {  //caso contrario, insere elemento no meio/final da lista
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return l;
}


Lista* ListaPendente(Lista* l, tarefa t)
{
    Lista* novo = (Lista*) malloc(sizeof(Lista));   //cria o novo elemento da lista
    novo->info = t;
    int dataT = 0;
    int prioridadeT = t.prioridade;
    Lista* ant = NULL;  //aponta para elemento anterior
    Lista* p = l;       //ponteiro para percorrer a lista

    dataT = t.fim.ano * 10000 + t.fim.mes * 100 + t.fim.dia;    //faz a soma do ano, mes e dia da tarefa para poder comparar com as datas da lista (exemplo: 20231010)

    //procura posicao de insercao de acordo com a data de termino
    while (p != NULL && (p->info.prioridade < prioridadeT || (p->info.prioridade == prioridadeT && (p->info.fim.ano * 10000 + p->info.fim.mes * 100 + p->info.fim.dia) < dataT))) { //percorre a lista enquanto a data da tarefa for maior que a data do elemento da lista
        ant = p;
        p = p->prox;
    }

    if (ant == NULL) {  //insere elemento no inicio
        novo->prox = l;
        l = novo;
    }
    else {  //caso contrario, insere elemento no meio/final da lista
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return l;
}


Lista* RetiraLista(Lista* L, int r)
{
    Lista *ant=NULL;
    Lista *p = L;

    while(p!=NULL && p->info.codigo!= r){
        ant=p;
        p = p->prox;
    }
    if(p == NULL)
        return L;


    if(ant == NULL)
        L = p->prox;
    else
        ant->prox = p->prox;

    free(p);
    return L;
}

void imprimeLista(Lista* L)
{
    Lista* aux;

    if(!VaziaLista(L)){
        for(aux = L; aux != NULL; aux = aux->prox){
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
        }

    }else
        printf("\nA Lista esta vazia no momento...\n");

}

void liberaLista(Lista* l)
{
    Lista* p = l;
    while(p != NULL){
        Lista* t = p->prox; // guarda a referencia do proximo elemento
        free(p);            // libera a memoria apontada por p
        p = t;              // faz p apontar para o proximo
    }
}


#endif // BIBLIOTECAS_H_INCLUDED
