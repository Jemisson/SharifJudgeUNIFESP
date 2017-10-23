#include <stdio.h>
#include <stdlib.h>

typedef struct aux
{
    int linha;
    int coluna;
    int valor;
    struct aux *proxLinha;
    struct aux *proxColuna;
} ELEMENTO, *PONT;

typedef struct
{
    int numLinhas;
    int numColunas;
    PONT *ALinha;
    PONT *AColuna;
} MATRIZ;

void inicializar(MATRIZ *m, int numLinhas, int numColunas){
    m->numLinhas = numLinhas;
    m->numColunas = numColunas;
    m->ALinha = (PONT *)malloc(numLinhas * sizeof(ELEMENTO));
    m->AColuna = (PONT *)malloc(numColunas * sizeof(ELEMENTO));
    int c;
    for (c = 0; c < numLinhas; c++){
        m->ALinha[c] = NULL;
    }
    for (c = 0; c < numColunas; c++){
        m->AColuna[c] = NULL;
    }
}

void exibir(MATRIZ *m){
    int c;
    PONT aux;
    for (c = 0; c < m->numLinhas; c++){
        aux = m->ALinha[c];
        while (aux != NULL){
            printf("%d %d %d\n", aux->linha, aux->coluna, aux->valor);
            aux = aux->proxLinha;
        }
    }
}

int inserir(MATRIZ *m, int linha, int coluna, int valor){
    if (linha < 0 || linha >= m->numLinhas || coluna < 0 || coluna >= m->numColunas){
        return -1;
    }
    PONT atual = m->ALinha[linha];
    PONT anterior = NULL;
    while (atual != NULL && atual->coluna < coluna){
        anterior = atual;
        atual = atual->proxLinha;
    }
    if (atual != NULL && atual->coluna == coluna){
        if (valor != 0){
            atual->valor = valor;
            return 0;
        }
        else{
            if (anterior == NULL){
                m->ALinha[linha] = atual->proxLinha;
            }
            else{
                anterior->proxLinha = atual->proxLinha;
            }
            anterior = NULL;
            atual = m->AColuna[coluna];
            while (atual != NULL && atual->linha != linha){
                anterior = atual;
                atual = atual->proxColuna;
            }
            if (anterior == NULL){
                m->AColuna[coluna] = atual->proxColuna;
            }
            else{
                anterior->proxColuna = atual->proxColuna;
            }
            free(atual);
            return 0;
        }
    }
    if (valor == 0){
        return 0;
    }
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    novo->coluna = coluna;
    novo->linha = linha;
    novo->valor = valor;
    if (anterior == NULL){
        novo->proxLinha = m->ALinha[linha];
        m->ALinha[linha] = novo;
    }
    else{
        novo->proxLinha = anterior->proxLinha;
        anterior->proxLinha = novo;
    }
    atual = m->AColuna[coluna];
    anterior = NULL;
    while (atual != NULL && atual->linha < linha){
        anterior = atual;
        atual = atual->proxColuna;
    }
    if (anterior == NULL){
        novo->proxColuna = m->AColuna[coluna];
        m->AColuna[coluna] = novo;
    }
    else{
        novo->proxColuna = anterior->proxColuna;
        anterior->proxColuna = novo;
    }
    return 0;
}

int multiplicar(MATRIZ *m1, MATRIZ *m2, MATRIZ *result){
	
	//printf("%d %d", m1->numColunas, m2->numLinhas);
    if (m1->numColunas != m2->numLinhas){
    	printf("-1\n");
        return -1;
    }
    inicializar(result, m1->numLinhas, m2->numColunas);
    int c;
    for (c = 0; c < m1->numLinhas; c++){
    	
        int i;
        for (i = 0; i < m2->numColunas; i++){
            int valor = 0;
            PONT atual = m1->ALinha[c];
            PONT atualM2 = m2->AColuna[i];
            while (atual != NULL){
            	
                while (atualM2 != NULL && atualM2->linha < atual->coluna){
                    atualM2 = atualM2->proxColuna;
                }
                if (atualM2 != NULL && atualM2->linha == atual->coluna){
                    valor += atual->valor * atualM2->valor;
                }
                atual = atual->proxLinha;
                atualM2 = m2->AColuna[i];
            }
            if (valor != 0){
                inserir(result, c, i, valor);
            }
        }
    }
    return 0;
}

int main(){
	
	MATRIZ M1, M2, M3;
	int m, n, N, i, linha , coluna, valor, op, resp;
	inicializar(&M3, 1, 1);
	
	scanf("%d %d %d", &m, &n, &N);
	inicializar(&M1, m+1, n+1);
	
	for(i=0; i<N; i++){
	    scanf("%d %d %d", &linha, &coluna, &valor);
	    inserir(&M1, linha, coluna, valor);
	}
	
	scanf("%d %d %d", &m, &n, &N);
	inicializar(&M2, m+1, n+1);
	
	for(i=0; i<N; i++){
	    scanf("%d %d %d", &linha, &coluna, &valor);
	    inserir(&M2, linha, coluna, valor);
	}
	
	scanf("%d",&op);
	 //1 ab e 2 ba
	if(op == 1){
		resp = multiplicar(&M1, &M2, &M3);
	} 
	else{
	   if(op == 2){
	    	resp = multiplicar(&M2, &M1, &M3);
	   	} 
		else{
	    	return 0;
	    }
	}
	//exibirMatriz(&M1);
	//exibirMatriz(&M2);
	if(resp!=-1)
		exibir(&M3);
	
	return 0;
}
