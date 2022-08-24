//
//  Partie_2.c
//  Projet Algo
//
//  Created by Mikail Yilmaz on 13/11/2021.
//

#include "Partie_2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************************************************************/
/*                                               */
/*                Sucre syntaxique               */
/*                                               */
/*************************************************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { false, true} bool;

/*************************************************************************************/
/*                                               */
/*          Definition type liste                */
/*                                               */
/*************************************************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************************************************/
/*                                               */
/*                Predeclarations                */
/*                                               */
/*************************************************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************************************************/
/*                                               */
/*                Briques de base                */
/*                                               */
/*************************************************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ;
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ;
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    printf("[ ");
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("]");
    printf("\n");
}

/*************************************************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************************************************/
/*                                               */
/*              Libere la memoire                */
/*                                               */
/*************************************************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
      
}



/*************************************************************************************/
/*                                               */
/*                  Questions                    */
/*                                               */
/*************************************************************************************/


void reverse (Liste *l){
    Liste temp;
    initVide(&temp);
    while(!estVide(*l)){
        empile(premier(*l), &temp);
        *l = suite(*l);
    }
    *l = temp;
}

bool ZeroEnDeuxiemePosition (Liste l){
    if(estVide(l) || estVide(suite(l))){
        return false;
    }
    return premier(suite(l)) == 0;
    
}

bool QueDesZeros (Liste l){
    if (estVide(l)){
        return true;
    } else {
        if(premier(l) = 0){
            QueDesZeros(suite(l))
        } else {
            return false;
        }
    }
}

int Compte0InitiauxIterative (Liste l){
    int k = 0;
    while(!estVide(l) && premier(l)==0){
        k++;
        l = suite(l);
    }
    return k;
}

int Compte0InitiauxRecursive (Liste l){
    if (estVide(l) || premier(l) != 0){
        return 0;
    } else {
        return 1 + Compte0InitiauxRecursive(suite(l));
    }
}
 
int auxIn(Liste l , int in){
    if (estVide(l) || premier(l) != 0){
        return in;
    } else {
        return auxIn(suite(l), in+1);
    }
}

int Compte0InitiauxRecursiveIn (Liste l){
    return auxIn(l, 0);
}

void auxInout (Liste l , int *inout){
    if (!estVide(l) && premier(l) == 0){
        (*inout)++;
        auxInout(suite(l), inout);
    }
}

int Compte0InitiauxRecursiveInout (Liste l){
    int k = 0;
    auxInout(l, &k);
    return k;
}



int minimum (int a , int b){
    if(a>b){
        return b;
    } else {
        return a;
    }
}


int occurencenombre (Liste l , int a){
    int k = 0;
    while(!estVide(l) && premier(l) == a){
        k++;
        l = suite(l);
    }
    return k;
}

Liste supprimeval (Liste l1 , int a){
    
    while(!estVide(l1) && premier(l1) == a){
        supprimeval(suite(l1),a);
    }
    return l1;
}


void comparerliste (Liste l1 , Liste l2 , Liste *l3){
    if(!estVide(l1) && !estVide(l2)){
        if(premier(l1) == premier(l2)){
            int k = minimum(occurencenombre(l1, premier(l1)),occurencenombre(l2, premier(l2)));
            for (int i = 0 ; i < k ; i++){
                empile(premier(l1), l3);
            }
            comparerliste((supprimeval(l1, premier(l1))),supprimeval(l2,premier(l2)),l3);
        } else if(premier(l1) < premier(l2)){
            comparerliste((supprimeval(l1, premier(l1))),l2,l3);
        } else {
            comparerliste(l1,supprimeval(l2,premier(l2)),l3);
        }
    }
}


Liste IntersectionTriee (Liste l1 , Liste l2){
    Liste res;
    initVide(&res);
    comparerliste(l1, l2, &res);
    reverse(&res);
    return res;
}

void ElimineKpremiersX (Liste *l1 , int k , int x){
    if(!estVide(*l1) && k != 0){
        if(premier(*l1)==x){
            depile(l1);
            ElimineKpremiersX(l1, k-1, x);
        } else {
            ElimineKpremiersX( & ( (**l1).suivant ), k, x);
        }
    }
}

void ElimineKderniersX (Liste *l1 , int *k , int x){
    if(!estVide(*l1)) {
        ElimineKderniersX(& ( (**l1).suivant ), k, x);
        if(*k!=0 && premier(*l1)== x ){
            depile(l1);
            
            *k = *k-1;
            
        }
    }
}



/*************************************************************************************/
/*                                               */
/*                 Fonction Test                 */
/*                                               */
/*************************************************************************************/


void testZeroEnDeuxiemePosition(Liste l1){
    ZeroEnDeuxiemePosition(l1);
    printf("La liste : ");
    affiche_iter(l1);
    printf("testZeroEnDeuxiemePosition : ");
    if(ZeroEnDeuxiemePosition(l1)){
        printf("True\n");
    } else {
        printf("False \n");
    }
}







/*************************************************************************************/
/*                                               */
/*                    Main                       */
/*                                               */
/*************************************************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n",
                           longueur_rec(l),
                           longueur_iter(l)
               ) ;
}

int main(int argc, char** argv){
    
    //Création et initialisation
    int k =2;
    Liste l,val0,val1,val2,val2f,test, test2,test3;
    initVide (&l);
    initVide (&val1);
    initVide (&val2);
    initVide (&val2f);
    initVide (&test);
    initVide (&test2);
    initVide (&test3);
    
    //Remplissage des Listes
    empile(0, &val0);
    empile(0, &val0);
    
    empile(1, &val1);
    
    empile(0, &val2);
    empile(2, &val2);
    
    empile(2, &val2f);
    empile(2, &val2f);
    
    empile(9, &test);
    empile(8, &test);
    empile(6, &test);
    empile(4, &test);
    empile(4, &test);
    empile(2, &test);
    empile(2, &test);
    empile(2, &test);
    
    empile(8, &test2);
    empile(8, &test2);
    empile(4, &test2);
    empile(4, &test2);
    empile(3, &test2);
    empile(3, &test2);
    empile(2, &test2);
    empile(2, &test2);
    empile(1, &test2);
    empile(1, &test2);
    
    empile(8, &test3);
    empile(8, &test3);
    empile(3, &test3);
    empile(4, &test3);
    empile(4, &test3);
    empile(3, &test3);
    empile(3, &test3);
    empile(3, &test3);
    empile(2, &test3);
    empile(2, &test3);
    empile(1, &test3);
    empile(2, &test3);
    
    
  
    printf("Test des fonctions ZeroEnDeuxiemePosition : \n");
    printf("\n");
    
    affiche_iter(l);
    if(ZeroEnDeuxiemePosition(l)){
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    printf("\n");
    
    affiche_iter(val1);
    if(ZeroEnDeuxiemePosition(val1)){
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    printf("\n");
    
    affiche_iter(val2);
    if(ZeroEnDeuxiemePosition(val2)){
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    printf("\n");
    
    affiche_iter(val2f);
    if(ZeroEnDeuxiemePosition(val2f)){
        printf("true\n");
    } else {
        printf("false\n");
    }

  
    printf("\n\n\nTest des fonctions QueDesZeros : \n\n");
    
    affiche_iter(l);
    if(QueDesZeros(l)){
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    
    printf("\n");
    affiche_iter(val0);
    if(QueDesZeros(val0)){
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    
    printf("\n");
    affiche_iter(val1);
    if(QueDesZeros(val1)){
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    printf("\n");
    affiche_iter(val2);
    if(QueDesZeros(val2)){
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    
    printf("\n");
    affiche_iter(val2f);
    if(QueDesZeros(val2f)){
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    
    
    
    
    printf("\n\n\nTest des fonctions Compte0InitiauxIterative : \n\n");
    
    
    affiche_iter(l);
    printf("Le nombre de 0 : %i \n" , Compte0InitiauxIterative(l));
    
    printf("\n");
    affiche_iter(val0);
    printf("Le nombre de 0 : %i \n" , Compte0InitiauxIterative(val0));
    
    printf("\n");
    affiche_iter(val1);
    printf("Le nombre de 0 : %i \n" , Compte0InitiauxIterative(val1));
    
    printf("\n");
    affiche_iter(val2);
    printf("Le nombre de 0 : %i \n" , Compte0InitiauxIterative(val2));
    
    printf("\n");
    affiche_iter(val2f);
    printf("Le nombre de 0 : %i \n" , Compte0InitiauxIterative(val2f));
    
    
    
    printf("\n\n\nTest des fonctions Compte0InitiauxRecursive : \n");
    
    printf("\nAfichage de la liste : \n");
    affiche_iter(l);
    printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursive(l));
    
    printf("\nAfichage de la liste : \n");
    affiche_iter(val0);
    printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursive(val0));
    
    printf("\nAfichage de la liste : \n");
    affiche_iter(val1);
    printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursive(val1));
    
    printf("\nAfichage de la liste : \n");
    affiche_iter(val2);
    printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursive(val2));
    
    printf("\nAfichage de la liste : \n");
    affiche_iter(val2f);
    printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursive(val2f));
    
    
    
     printf("\n\n\nTest des fonctions Compte0InitiauxRecursiveIn : \n");
     
     printf("\nAfichage de la liste : \n");
     affiche_iter(l);
     printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursiveIn(l));
     
     printf("\nAfichage de la liste : \n");
     affiche_iter(val0);
     printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursiveIn(val0));
     
     printf("\nAfichage de la liste : \n");
     affiche_iter(val1);
     printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursiveIn(val1));
     
     printf("\nAfichage de la liste : \n");
     affiche_iter(val2);
     printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursiveIn(val2));
     
     printf("\nAfichage de la liste : \n");
     affiche_iter(val2f);
     printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursiveIn(val2f));
    
    
     printf("\n\n\nTest des fonctions Compte0InitiauxRecursiveInout : \n");
    
     
     printf("\nAfichage de la liste : \n");
     affiche_iter(l);
     printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursiveInout(l));
     
     printf("\nAfichage de la liste : \n");
     affiche_iter(val0);
     printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursiveInout(val0));
     
     printf("\nAfichage de la liste : \n");
     affiche_iter(val1);
     printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursiveInout(val1));
     
     printf("\nAfichage de la liste : \n");
     affiche_iter(val2);
     printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursiveInout(val2));
     
     printf("\nAfichage de la liste : \n");
     affiche_iter(val2f);
     printf("Le nombre de 0 en début : %i \n" , Compte0InitiauxRecursiveInout(val2f));
    
    
    
    
    printf("\n\n\nTest de la fonction IntersectionTriee : \n");
    
    printf("\nAfichage des deux listes : \n");
    
    affiche_iter(l);
    affiche_iter(test2);
    printf("Résultat de l'intersection des 2 listes : \n");
    affiche_iter(IntersectionTriee(l, test2));
    
    printf("\nAfichage des deux listes : \n");
    affiche_iter(test);
    affiche_iter(test2);
    printf("Résultat de l'intersection des 2 listes : \n");
    affiche_iter(IntersectionTriee(test, test2));
    
    
    
    printf("\n\n\nTest de la fonction ElimineKpremiersX : \n");
    
    printf("\nListe avant suppression des 2 premieres valeur de 2 : \n");
    affiche_iter(test2);
    ElimineKpremiersX(&test2, 2, 2);
    
    printf("Liste après suppression des 2 premieres valeur de 2 : \n");
    affiche_iter(test2);
    
    
    printf("\nListe avant suppression de la premiere valeur de 2 : \n");
    affiche_iter(test3);
    ElimineKpremiersX(&test3, 1, 2);
    printf("Liste après suppression des 2 premieres valeur de 2 : \n");
    affiche_iter(test3);
     
    
    printf("\n\n\nTest de la fonction ElimineKderniersX : \n");
    printf("\nListe avant suppression des 2 dernieres valeur de 3 : \n");
    affiche_iter(test3);
    ElimineKderniersX(&test3, &k, 3);
    printf("Liste après suppression des 2 dernierss valeurs de 3 : \n");
    affiche_iter(test3);
    return 0;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
    poup(l) ;
    
    poup(l) ;
     
    
     
    poup(l) ;
    VireDernier_rec  (&l) ;
    VireDernier_iter (&l) ;
    depile(& l) ;
    poup(l) ;
    VideListe(&l);
    */
    
}




