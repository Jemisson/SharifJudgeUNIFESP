#include<stdio.h>
#include<stdlib.h>

typedef struct _no{
    int cons;
    struct _no *prox;
}no;

void push(int v, no **ini, no **fim){
    
    no *aux;
    
    if((*ini)==NULL){
        *ini = (no *) malloc(sizeof(no));
        (*ini)->prox = NULL;
        (*ini)->cons = v;
        *fim=*ini;
    } else {
        aux = (no *) malloc(sizeof(no));
        aux->cons = v;
        aux->prox = NULL;
        (*fim)->prox = aux;
        *fim = aux;
    }
    
}

int pop(no **ini, no **fim){
    
    int ret;
    no *aux;
    
    if((*ini == NULL) && (*fim == NULL)){
        return -1;
    } else {
        if((*ini) == (*fim)){
            aux = *ini;
            *ini = (*ini)->prox;
            *fim = *ini;
            ret = aux->cons;
            free(aux);
            return ret;
        } else {
            aux =* ini;
            (*ini) = (*ini)->prox;
            ret = aux->cons;
            free(aux);
            return ret;
        }
    }
    
}

void print(no **ini){

    no *aux = NULL;
    aux = *ini;

    if(aux != NULL){
        while(aux != NULL){
            printf("%d\n", aux->cons);
            aux = aux->prox;
        }
    }

}

int main(){
    int qdt, i, v, ret;
    no *ini = NULL, *fim=NULL;
    
    
    scanf("%d",&qdt);
    
    for(i=0; i<qdt; i++){
        scanf("%d",&v);    
        push(v, &ini, &fim);
    }
    
    
    while (ini->prox != NULL){
        pop(&ini, &fim);
        ret = pop(&ini, &fim);
        push(ret, &ini, &fim);
    }
    
    print(&ini);
    
}
