#include<stdio.h>

int main() {
    int i, voto, cand, st, nd, rd, vv1=0, vv2=0, x1, x2;
    int p1=0, p2=0;
    double porcento = 0, res, result1 = 0, result2 = 0;
    
    scanf("%d %d", &voto, &cand);
    
    if(voto < 1 || voto > 10000 || cand < 1 || cand > 100){
        return 0;
    }
    
    int turno1[cand+1];
    int primeiro[voto], segundo[voto], terceiro[voto];
    
    for(i=0; i<=cand; i++){
        turno1[i] = 0;
    }
    
    for(i=0; i<voto; i++){
        scanf("%d %d %d", &st, &nd, &rd);
        
        if(st > 0 && st <= cand){
            turno1[st] += 1;
            vv1++;
            printf("voto valido %d - validos %d\n", st, vv1);
        }
            
        primeiro[i] = st;
        segundo[i] = nd;
        terceiro[i] = rd;
    }
    
    
    
    for(i=1; i<=cand; i++){
        if(turno1[i] > 0 && vv1 != 0){
            porcento = turno1[i] * (100.0 / vv1);
            if(result1 < porcento){
                result1 = porcento;
                x1 = i;
            } else {
                if(result2 < result1 && result2 < porcento){
                    result2 = porcento;
                    x2 = i;
                }
            }
        }
    }
    
    if(vv1 > 0){
        if(result1 > result2){
            printf("%d %.2f\n", x1, result1);
        } else { 
            if(result2 > result1) {
                printf("%d %.2f\n", x2, result2);
            }
          }
        if(result1 == result2 && x1 < x2){
            printf("%d %.2f\n", x1, result1);
        } else {
            if(result1 == result2 && x1 > x2){
                printf("%d %.2f\n", x2, result2);
            }
        }
    } else {
        printf("%d\n", 0);
        return 0;
    }
    
    if(result1 < 50.00 && result2 < 50.00){
        for(i=1; i<=voto; i++){
            
            if(x1 == primeiro[i]){
                p1 += 1;
                vv2+=1;
            } else {
                if(x2 == primeiro[i]){
                    p2 += 1;
                    vv2+=1;
                } else {
                    
                    if(x1 == segundo[i]){
                        p1 += 1;
                        vv2+=1;
                    } else {
                        if(x2 == segundo[i]){
                            p2 += 1;
                            vv2+=1;
                        } else {
                            
                            if(x1 == terceiro[i]){
                                p1 += 1;
                                vv2+=1;
                            } else {
                                if(x2 == terceiro[i]){
                                    p2 += 1;
                                    vv2+=1;
                                }
                            }
                        }
                    }
                }
            }
        }
    
        if(p1 > p2 && vv2 > 0 || p1 == p2 && x1 > x2){
            res = p1 * (100.0 / vv2);
            printf("%d %.2f\n", x1, res);
        } else {
            if(p1 < p2 && vv2 > 0 || p1 == p2 && x1 < x2){
                res = p2 * (100.0 / vv2);
                printf("%d %.2f\n", x2, res);
            }
        } 
    }       
           
   return 0;
}



