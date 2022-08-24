//
//  Partie_3.c
//  Projet Algo
//
//  Created by Mikail Yilmaz on 05/12/2021.
//

#include "Partie_3.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>




typedef enum {false, true} bool;



/*****************************************************************************/
/*                                               */
/*            Définition type image              */
/*                                               */
/*****************************************************************************/

typedef struct bloc_image {
    bool toutnoir ;
    struct bloc_image * fils[4] ;
} bloc_image ;

typedef bloc_image *image ;




/*****************************************************************************/
/*                                                                           */
/*                                 Constructeurs                             */
/*                                                                           */
/*****************************************************************************/

image Construit_blanc(void){
    return NULL;
}

image Construit_noir(void){
    image N = (image) malloc(sizeof(bloc_image));
    N ->toutnoir = true;
    N ->fils[0]=NULL;
    N ->fils[1]=NULL;
    N ->fils[2]=NULL;
    N ->fils[3]=NULL;
    
    return N;
}

image Construit_composee(image x1,image x2,image x3,image x4){
    image C = (image) malloc(sizeof(bloc_image));
    C ->toutnoir = false;
    C ->fils[0] = x1;
    C ->fils[1] = x2;
    C ->fils[2] = x3;
    C ->fils[3] = x4;
    
    return C;
}


/*****************************************************************************/
/*                                                                           */
/*                                Affichage                                  */
/*                                                                           */
/*****************************************************************************/
bool EstBlanche(image A){
    return A == NULL;
}

bool EstNoir(image A){
    return A->toutnoir && A->fils[0] == NULL && A->fils[1] == NULL &&
    A->fils[2] == NULL && A->fils[3] == NULL;
}

/*
void affiche_normal_aux(image A){
    if(A == NULL){
        printf("B");
    }
    else if(EstNoir(A)){
            printf("N");
    }
    else {
        printf("+");
        for(int i = 0 ; i < 4 ; i++){
        affiche_normal_aux(A->fils[i]);
        }
    }
}
*/ 

void affiche_normal(image A){
    if(EstBlanche(A)){
        printf("B");
    }
    else if(EstNoir(A)){
            printf("N");
    }
    else {
        printf("+");
        for(int i = 0 ; i < 4 ; i++){
        affiche_normal(A->fils[i]);
        }
    }
}

void affiche_profondeur_aux(image A , int k){
    if(EstBlanche(A)){
        printf("B%d" , k);
    }
    else if(EstNoir(A)) {
        printf("N%d" , k);
    }
    else {
        printf(" +%d ",k);
        for(int i = 0 ; i < 4 ; i++){
            affiche_profondeur_aux(A->fils[i] , k+1);
        }
    }
}

void affiche_profondeur(image A){
    affiche_profondeur_aux(A , 0);
    printf("\n");
}

/*****************************************************************************/
/*                                                                           */
/*                               Méthode                                     */
/*                                                                           */
/*****************************************************************************/



image Copie(image A){
    if(EstBlanche(A)){
        return Construit_blanc();
    }
    else if(EstNoir(A)){
        return Construit_noir();
    }
    else {
        return Construit_composee(Copie(A->fils[0]), Copie(A->fils[1]), Copie(A->fils[2]), Copie(A->fils[3]));
    }
}

float Aire_aux(image A , double n){ 
    if (EstBlanche(A)){
        return 0;
    }
    else if(EstNoir(A)){
        return n;
    }
    else return Aire_aux(A ->fils[0], n/4) + Aire_aux(A ->fils[1], n/4) + Aire_aux(A ->fils[2], n/4) + Aire_aux(A ->fils[3], n/4);
}

float Aire(image A){
    return Aire_aux(A,1.);
}

void Rendmemoire (image *A){
    if(!EstBlanche(*A) && !EstNoir(*A)){
        for(int i = 0 ; i<4 ; i++){
            Rendmemoire(&((*A)->fils[i]));
        }
    }
    else {
        free(*A);
    }
}

int CompteSousImagesGrises (image A){
    if (EstBlanche(A)) {
        return 0;
    }
    else if(Aire(A) > (1./3.) && Aire(A)< (2./3.)){
        return  1 + CompteSousImagesGrises(A-> fils[0]) + CompteSousImagesGrises(A-> fils[1]) + CompteSousImagesGrises(A-> fils[2]) + CompteSousImagesGrises(A-> fils[3]);
    }
    else{
        return CompteSousImagesGrises(A-> fils[0]) + CompteSousImagesGrises(A-> fils[1]) + CompteSousImagesGrises(A-> fils[2]) + CompteSousImagesGrises(A-> fils[3]);
    }
}

void negatif (image *i){
    if(!(*i == NULL) && !(((*i)->toutnoir))){
        for(int j =0; j<4;j++)
            negatif(&((*i)->fils[j]));
    }
    else if(EstNoir(*i)){
        *i = Construit_blanc();
    }
    else if(EstBlanche(*i)){
        *i = Construit_noir();
    }
        
}

bool UnionNoir (image A1 , image A2){
    if(EstNoir(A1) || EstNoir(A2)){
        return true;
    }
    else if (EstBlanche(A1) && EstBlanche(A2)){
        return false;
    }
    else return UnionNoir(A1 -> fils[0], A2->fils[0]) && UnionNoir(A1 -> fils[1], A2->fils[1]) && UnionNoir(A1 -> fils[2], A2->fils[2]) && UnionNoir(A1 -> fils[3], A2->fils[3]);
}


void Intersection (image *A1, image A2) {
    if( !EstBlanche(*A1) && EstBlanche(A2)){
        (*A1) = Construit_blanc();
    }
    else if(!EstNoir(A2) && !EstBlanche(*A1)) {
        Intersection(&((*A1)->fils[0]), A2->fils[0]);
        Intersection(&((*A1)->fils[1]), A2->fils[1]);
        Intersection(&((*A1)->fils[2]), A2->fils[2]);
        Intersection(&((*A1)->fils[3]), A2->fils[3]);
    }
}



int main(){
    
    image blanc = Construit_blanc();
    image noir = Construit_noir();
    image AB , AN , A3 , A4 , A5 , A6 , A7 , A8;
    image F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,F14,F15;
    AB = Construit_blanc();
    AN = Construit_noir();
    
    F1 = Construit_composee(blanc, blanc, noir, blanc);
    F2 = Construit_composee(noir,blanc, noir, noir);
    F3 = Construit_composee(noir, noir, blanc, F2);
    F4 = Construit_composee(noir, F3, blanc, noir);
    F5 = Construit_composee(noir, blanc, noir, blanc);
    F6 = Construit_composee(noir, noir, blanc, blanc);
    F7 = Construit_composee(blanc, noir, blanc, blanc);
    F8 = Construit_composee(noir, F7, blanc, F6);
    F9 = Construit_composee(noir, blanc, blanc, blanc);
    F10 = Construit_composee(blanc, noir, blanc, blanc);
    F11 = Construit_composee(noir, F10, blanc, F9);
    F12 = Construit_composee(noir, blanc, noir, blanc);
    F13 = Construit_composee(blanc, noir, noir, blanc);
    F14 = Construit_composee(noir, noir, blanc, blanc);
    F15 = Construit_composee(noir, blanc, noir, noir);
    
    A3 = Construit_composee(noir, F1, blanc, F4);
    
    
    
    
    /*****************************************************************************/
    /*                                               */
    /*                Test    Affichage              */
    /*                                               */
    /*****************************************************************************/
    
    
    printf("L'image A1 est Blanche et son affichage normal est : ");
    affiche_normal(AB);
    printf("\n");
    printf("L'image A1 est Blanche et son affichage en profondeur est : ");
    affiche_profondeur(AB);
    printf("\n");
    printf("Test si l'image A1 est blanche :");
    if(EstBlanche(AB)){
        printf("True");
    }
    
    printf("\n\nL'image A2 est Noire et son affichage normal est : ");
    affiche_normal(AN);
    printf("\n");
    printf("L'image A2 est Noire et son affichage en profondeur est : ");
    affiche_profondeur(AN);
    printf("Test si l'image A2 est noire :");
    if(EstNoir(AN)){
        printf("True");
    }
    
    printf("\n\nL'image A3 est un carré Blanc/Noir/Blanc/Noir et son affichage normal est : ");
    affiche_normal(A3);
    printf("\n");
    printf("L'image A3 est un carré Blanc/Noir/Blanc/Noir et son affichage en profondeur est : ");
    affiche_profondeur(A3);
    
    
    /*****************************************************************************/
    /*                                               */
    /*                Test   Méthode                 */
    /*                                               */
    /*****************************************************************************/
    
    
    printf("\nA3 est copié sur A4 : ");
    A4 = Copie(A3);
    printf("\nL'image A3 copié est d'affichage : ");
    affiche_profondeur(A3);
    printf("L'image A4 copié est d'affichage : ");
    affiche_profondeur(A4);
    
    
    A5 = Construit_composee(noir, blanc, noir, F5);
    printf("\nLe taux de noir de A5 est de : %f",Aire(A5));
    

    printf("\n\nL'image A5 affichage normal est : ");
    affiche_normal(A5);

    printf("\n\nLe nombre de sous image grise de A5 est : %i", CompteSousImagesGrises(A5));
    
    
    printf("Représentation de son négatif de A5 :");
    negatif(&A5);
    affiche_normal(A5);
    
    
    printf("\nRend tous les blocs de l'image A5 à la mémoire");
    Rendmemoire(&A5);
    
         
    A7 = Construit_composee(F12, F13, blanc, F14);
    A8 = Construit_composee(noir, F15,noir, F12);
    printf("\n\nAffichage normal de A7 : ");
    affiche_normal(A7);
    printf("Affichage normal de A8 : ");
    affiche_normal(A8);
    if(!UnionNoir(A7, A8)){
        printf("L'union de A7 et A8 ne donne pas un carré tout noir.");
    }
    printf("\n\n");
    
    
    printf("\n\nAffichage normal de A7 : ");
    affiche_normal(A7);
    printf("Application de l'intersection de A7 et A8");
    Intersection(&A7, A8);
    printf("\nAffichage normal de A7 après intersection : ");
    affiche_normal(A7);
    


}
