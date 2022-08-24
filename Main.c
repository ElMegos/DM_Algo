//
//  Main.c
//  Projet Algo
//
//  Created by Mikail Yilmaz on 19/10/2021.
//

#include "Main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Question 1
float factorielle(int n) {
    if (n == 0){
        return 1;
    } else {
        return (n * factorielle(n-1));
    }
}


float expo(int n){
    if(n>=0){
        return 1./factorielle(n) + expo(n-1);
    }
}

//Question 2
float powerFloat(float x , int n){
    if(n == 0){
        return 1.;
    }
    if(n == 1){
        return x;
    }
    if(n < 0){
        return 1./(x*powerFloat(x, -(n+1)));
    } 
    else return x*powerFloat(x, n-1);
}

double powerDouble(double x , int n){
    if(n == 0){
        return 1.;
    } 
    if(n == 1){
        return x;
    } 
    if(n < 0){
        return 1./(x*powerDouble(x, -(n+1)));
    } 
    else return x*powerDouble(x, n-1);
}
void tpscalculFloat (float x, int n){
    float res;
    clock_t start, end;
    start = clock();
    powerFloat(x, n);
    end = clock();
    res = (float)(end - start)/ CLOCKS_PER_SEC;
    printf("Temps de calcul PowerFloat : %f\n",powerFloat(x, n));

}

void tpscalculDouble (double x, int n){
    float res;
    clock_t start, end;
    start = clock();
    powerDouble(x, n);
    end = clock();
    res = (float)(end - start)/ CLOCKS_PER_SEC;
    printf("Temps de calcul PowerDouble : %f\n",powerDouble(x, n));

}

int etatmemoireFloat(float x , int n){
    return sizeof(powerFloat((float)x, n));
    
}

int etatmemoireDouble(double x , int n){
    return sizeof(powerDouble(x, n));
    
}

void precisionresFloat(float x , int n){
    printf("Precision : %f\n " , powerFloat(x, n));
}


void precisionresDouble(double x , int n){
    printf("Precision : %f\n " , powerDouble(x, n));
}


void testFloat(float x,int n){
    printf("Puissance float : \n");
    tpscalculFloat(x, n);
    printf("Memoire Float : %i octets\n", etatmemoireFloat(x, n));
    precisionresFloat(x,n);
}

void testDouble(double x,int n){
    printf("\nPuissance Double : \n");
    tpscalculDouble(x, n);
    printf("Memoire Double : %i octets\n", etatmemoireDouble(x, n));
    precisionresDouble(x,n);
}

void testpuissance(int k){
    printf("\nPour k = %i\n", k);
    for (int i = 1; i <= k; i++) {
        double x =1. + powerDouble(10, -i);
        int n = powerDouble(10, i);
        printf("\nPour %f^%i : \n", x , n);
        testFloat(x, n);
        testDouble(x, n);
    }
}

//Question 3

int AckermannRecursive(int m,int n) {
    if(m == 0){
        return n+1;
    }
    else {
        if(n == 0){
            return AckermannRecursive(m-1,1);
        }
        else {
            return AckermannRecursive(m-1,(AckermannRecursive(m,n-1)));
        }
    }
}

int Ackermann(int m , int n){
    int r=1;
    if (m == 0){
        return n+1;
    }
    else{
        for(int i = 1 ; i<=n+1 ; i++){
            r = Ackermann(m -1, r);
        }
    }
    return r;
}

//Question 4

/*
 Pseudo code de la fonction X
 on prends n en argument
 si n = 0 return 1
 sinon boucle de 1 à n avec
 résultat = résultat + 1/résultat
 
 */

float SuiteRecursive(int n){
    //float res;
    if (n == 0){
        return 1;
    }
    else {
        float x = SuiteRecursive(n-1);
        return x + 1. / x;
    }
}

float SuiteIterative (int n){
    float x1 = 1;
    
    if(n==0){
        return 1;
    }
    else {
        for(int i = 1 ; i<=n ; i++){
            x1 = x1 + 1./x1;
        }
    }
    return x1;
}

int main(){
    //PARTIE 1
    
    //Question 1
    printf("la somme de 1/n! pour n vaux 5 est égale à : %f\n" , expo(7));
    
    //Question 2
    testpuissance(4);
    
    
    //Question 3
    for (int i= 0 ; i<5 ; i++){
        printf("\nRésultat de Ackermann Récursive de %i et 1 donne %i\n" ,i, AckermannRecursive(i, 0));
        printf("Résultat de Ackermann  de %i et 1 donne %i\n" ,i, Ackermann(i, 0));
    }
    
   
    //Question 4
    printf("\nPour x = 100 en Récursive on a : %f\n" , SuiteRecursive(100));
    printf("Pour x = 100 en Itérative on a : %f\n" , SuiteIterative(100));
    
    return 0;
}
