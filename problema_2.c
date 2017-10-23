#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _No{
    int id, esq, dir;
    struct _No *prox;
}No;

typedef struct _lista{
    No *inicio, *fim;
}Lista;

void inicializa(Lista *lista){
    lista->inicio = NULL;
    lista->fim = NULL;
}

int ehVazia(Lista *lista){
    if(lista->inicio == NULL)
        return 1;
    return 0;
}

int buscaPai(Lista *lista, int filho){
    No *aux = lista->inicio;
    
    while(aux){
        if(aux->dir == filho || aux->esq == filho){
            return aux->id;
        }
        aux = aux->prox;
    }
    return -1;
}

int buscaIrmao(Lista *lista, int bro){
    No *aux = lista->inicio;
    
    while(aux){
        if(aux->dir == bro){
            return aux->esq;
        } else {
            
            if(aux->esq == bro){
                return aux->dir;
            }
        }
        aux = aux->prox;
    }
    return -1;
}

int grau(Lista *lista, int no){
    No *aux = lista->inicio;
    int gr = 0;
    while(aux){
        if(aux->id == no){
            if(aux->esq >= 0){
                gr++;
            }
            if(aux->dir >= 0){
                gr++;
            }
            return gr;
        }
        aux = aux->prox;
    }
    return gr;
}

int nivel(Lista *lista, int no){
    No *aux = lista->inicio;
    int nv = -1;
    do{
        no = buscaPai(lista, no);
        nv++;
    } while(no != -1);
    return nv;
}

No *buscaNo(Lista *lista, int id){
    No *aux = lista->inicio;
    while(aux != NULL && aux->id != id){
        aux = aux->prox;
    }
    return aux;
}

int altura(Lista *lista, No *aux){
    int u, v;
    No *no = aux;
    
    if (no == NULL)return -1; 
    u = altura(lista, buscaNo(lista, no->esq));
    v = altura(lista, buscaNo(lista, no->dir));
    
    if (u > v){
        return u+1;  
    } else {
        return v+1;
    }
}

char * identificaNo(Lista *lista, No *no){
    
    if(buscaPai(lista, no->id) == -1){
        return "raiz";
    } else {
        if(no->esq == -1 && no->dir == -1){
            return "folha";
        }
    }
    return "interno";
}

void print(Lista *lista){
    No *aux = lista->inicio;
    int p, s, g, n, a;
    char tipo[8];
    
    while(aux){
        p = buscaPai(lista, aux->id);
        s = buscaIrmao(lista, aux->id);
        g = grau(lista, aux->id);
        n = nivel(lista, aux->id);
        a = altura(lista, aux);
        strcpy(tipo, identificaNo(lista, aux));
        
        printf("%d: pai = %d, irmao = %d, grau = %d, nivel = %d, altura = %d, %s\n", 
                aux->id, p, s, g, n, a, tipo);
        aux = aux->prox;
    }
}

int push(Lista *lista, No no){
    No *aux, *auxp, *auxs;
    
    if(ehVazia(lista)){
        lista->inicio = malloc(sizeof(No));
        *lista->inicio = no;
        lista->inicio->prox = NULL;
        lista->fim = lista->inicio;
        return 1;
    } else {
        
        aux = malloc(sizeof(No));
        *aux = no;
        
        if(aux->id < lista->inicio->id){
            aux->prox = lista->inicio;
            lista->inicio = aux;
            return 1;
        } else {
            if(aux->id > lista->fim->id){
                aux->prox = NULL;
                lista->fim->prox = aux;
                lista->fim = aux;
                return 1;
            } else { 
                auxs = lista->inicio->prox;
                auxp = lista->inicio;
                while(auxs != NULL){
                    if(auxs->id > aux->id){
                        aux->prox = auxs;
                        auxp->prox = aux;
                        return 1;
                    }
                    auxp = auxs;
                    auxs = auxs->prox;
                }
            }
        }
    }
    return 0;
}

int main() {
   int i, qtd;
   Lista lista;
   No no;
   inicializa(&lista);
   
   scanf("%d", &qtd);
   
   for(i=0; i<qtd; i++){
       scanf("%d %d %d", &no.id, &no.esq, &no.dir);
       push(&lista, no);
   }
   
   print(&lista);
   return 0;
}

