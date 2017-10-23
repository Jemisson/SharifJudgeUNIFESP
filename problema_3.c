#include<stdio.h>
#include<stdlib.h>
 
typedef struct t_celula{
    struct t_celula *direita, *abaixo;
    int linha, coluna, valor;
}tipo_celula;
 
typedef struct{
    int m, n;
    tipo_celula *inicio, *fimLinha, *fimColuna;
}matriz_esparsa;
 
int insereCabecaColuna(matriz_esparsa *mat){
    tipo_celula *cabeca;
    cabeca = (tipo_celula*)malloc(sizeof(tipo_celula));
 
    if (!cabeca) return 0;
 
    cabeca->coluna = -1;
    cabeca->linha = 0;
 
    mat->fimColuna->direita = cabeca;
    mat->fimColuna = cabeca;
 
    cabeca->direita = mat->inicio;
    cabeca->abaixo = cabeca;
    return 1;
}
 
int insereCabecaLinha(matriz_esparsa *mat){
    tipo_celula *cabeca;
    cabeca = (tipo_celula*)malloc(sizeof(tipo_celula));
 
    if (!cabeca) return 0;
 
    cabeca->coluna = 0;
    cabeca->linha = -1;
 
    mat->fimLinha->abaixo = cabeca;
    mat->fimLinha = cabeca;
 
    cabeca->abaixo = mat->inicio;
    cabeca->direita = cabeca;
 
    return 1;
}
 
int iniciaCabecas(matriz_esparsa *mat){
    int i=0;
 
    tipo_celula *cabeca;
    cabeca = (tipo_celula*)malloc(sizeof(tipo_celula));
 
    if (!cabeca) return 0;
 
    cabeca->coluna = -1;
    cabeca->linha = -1;
 
    mat->inicio = cabeca;
    mat->fimLinha = cabeca;
    mat->fimColuna = cabeca;
 
    for (i = 1; i <= mat->n; i++){
        insereCabecaColuna(mat);
    }
    for (i = 1; i <= mat->m; i++){
        insereCabecaLinha(mat);
    }
    return 1;
}
 
matriz_esparsa *cria_matriz_esparsa(int m, int n){
    matriz_esparsa *mat;
    mat = (matriz_esparsa *)malloc(sizeof(matriz_esparsa));
 
    if (!mat || m<=0 || n<=0){
        return 0;
    }
 
    mat->inicio = NULL;
    mat->fimLinha = NULL;
    mat->fimColuna = NULL;
    mat->m = m;
    mat->n = n;
 
    iniciaCabecas(mat);
 
    return mat;
}
 
 
int obtemElementoPeloIndice(matriz_esparsa *mat, int linha, int coluna){
    tipo_celula *pCelula;
    int i = 0;
 
    pCelula = mat->inicio->direita;
 
    for (i = 0; i < coluna-1; i++){
        pCelula = pCelula->direita;
    }
 
    do{
        pCelula = pCelula->abaixo;
        if (pCelula->linha == linha){
            return pCelula->valor;
        }
    }while(pCelula->coluna != -1);
 
    return 0;
}

void multiplicaMatriz(matriz_esparsa *matA, matriz_esparsa *matB){
    int i=0, j=0, k=0, total;
 
    if (matA->n == matB->m){
        for (i = 1; i <= matA->m; i++){
            for (j = 1; j <= matB->n; j++){
                total = 0;
                for (k = 1; k <= matA->n; k++){
                    total += obtemElementoPeloIndice(matA,i,k) * obtemElementoPeloIndice(matB,k,j);
                }
                if (total){
                    printf("%d %d %d\n", i, j, total);
                }
            }
        }
    } else {
        printf("%d", -1);
    }
    
}

int insere(matriz_esparsa *mat, int linha, int coluna, int valor){
    int i;
 
    if (linha>mat->m || coluna>mat->n || !valor || linha < 1 || coluna < 1){
        return 0;
    }

    tipo_celula *pCelula;
    tipo_celula *pCelulaColuna;
    tipo_celula *pCelulaLinha;
 
    pCelula = (tipo_celula*)malloc(sizeof(tipo_celula));
 
    if (!pCelula) return 0;
 
    pCelula->linha = linha;
    pCelula->coluna = coluna;
    pCelula->valor = valor;
 
    pCelulaLinha = mat->inicio->abaixo;
    pCelulaColuna = mat->inicio->direita;
 
    for (i=0; i<linha-1; i++){
        pCelulaLinha = pCelulaLinha->abaixo;
    }
    i=0;
    while (i<coluna && pCelulaLinha->direita->linha != -1){
        if (pCelulaLinha->direita->coluna > pCelula->coluna){
            pCelula->direita = pCelulaLinha->direita;
            pCelulaLinha->direita = pCelula;
        }
        else{
            pCelulaLinha = pCelulaLinha->direita;
        }
        i++;
    }
    if (pCelulaLinha->direita->linha == -1){
        pCelula->direita = pCelulaLinha->direita;
        pCelulaLinha->direita = pCelula;
    }
 
    for (i = 0; i < coluna-1; i++){
        pCelulaColuna = pCelulaColuna->direita;
    }
    i=0;
    while (i<linha && pCelulaColuna->abaixo->coluna != -1){
        if (pCelulaColuna->abaixo->linha > pCelula->linha){
            pCelula->abaixo = pCelulaColuna->abaixo;
            pCelulaColuna->abaixo = pCelula;
        }
        else{
            pCelulaColuna = pCelulaColuna->abaixo;
        }
        i++;
    }
    if (pCelulaColuna->abaixo->coluna == -1){
        pCelula->abaixo = pCelulaColuna->abaixo;
        pCelulaColuna->abaixo = pCelula;
    }
    return 1;
}
 
int main() {
   
    int i, j, m, n, N, linha, coluna, valor, op;
    matriz_esparsa *matA;
    matriz_esparsa *matB;
    
    scanf("%d %d %d", &m, &n, &N);
    
    matA = cria_matriz_esparsa(m, n);
    
    for(i=0; i<N; i++){
        scanf("%d %d %d", &linha, &coluna, &valor);
        insere(matA, linha, coluna, valor);
    }
    
    scanf("%d %d %d", &m, &n, &N);
    
    matB = cria_matriz_esparsa(m, n);
    
    for(i=0; i<N; i++){
        scanf("%d %d %d", &linha, &coluna, &valor);
        insere(matB, linha, coluna, valor);
    }
   
   scanf("%d",&op);
   
   if(op == 1){
       multiplicaMatriz(matA, matB);
   } else {
       if(op == 2){
           multiplicaMatriz(matB, matA);
       } else {
           printf("%d", -1);
       }
   }
   
   return 0;
}
// matriz transposta para só andar pos linhas.
