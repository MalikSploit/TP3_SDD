/**
 * @file arbres_parcours.c
 * @brief fichier d'implementation du module pour le parcours d'arborescence
 */
#include <stdio.h>
#include <stdlib.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_parcours.h"


/**
 * @brief calculer le nombre de fils ou freres d'un point a partir du pointeur du debut de la liste
 * @param [in] ptCell pointeur vers le 1er frere
 * @return le nombre de fils ou freres
 */
/* -------------------------------------------------------------------- */
/* getNbFils_ou_Freres Calcule le nombre de fils ou freres d'un point   */
/*                                                                      */
/* Cette fonction calcule le nombre de fils ou freres d'un point        */
/*                                                                      */
/* En entree:   ptCell le pointeur du premier frere                     */
/* En sortie:   compteur le nombre de fils ou freres                    */
/* -------------------------------------------------------------------- */
int getNbFils_ou_Freres(cell_lvlh_t *ptCell)
{
    int compteur = 0;
    cell_lvlh_t* cour = ptCell;

    while(cour != NULL)
    {
        compteur++;
        cour = cour->lh;
    }

    return compteur;
}

//Version recursive de getNbFils_ou_Freres
int getNbFils_ou_Freres_recursive(cell_lvlh_t *ptCell)
{
    if (ptCell == NULL)
    {
        return 0;
    }

    return 1 + getNbFils_ou_Freres(ptCell->lh);
}


/**
 * @brief parcours en profondeur postfixee
 * @param [in] file le flux de sortie
 * @param [in] racine la racine de l'arborescence
 */
/* -------------------------------------------------------------------- */
/* printPostfixee Parcours une arborescence postfixee                   */
/*                                                                      */
/* Cette fonction affiche une arborescence en effectuant un parcours en */
/* profondeur                                                           */
/*                                                                      */
/* En entree:   file le flux de sortie                                  */
/*              racine le pointeur de la racine de l'arborescence       */
/* -------------------------------------------------------------------- */
void printPostfixee(FILE *file, cell_lvlh_t * racine)
{
    // initialisation
    cell_lvlh_t * curr = racine;
    int code = 0;               /* code de retour de la pile */
    pile_t *pile = initPile(NB_ELTPREF_MAX); /* pile d'éléments */
    if (NULL == pile) /* gestion erreur d'allocation de la pile */
    {
        printf("Erreur du malloc. Dans la fonction printPostfixee\n");
        code = 1;
    }
    eltType_pile elp; /* élément de la pile à empiler/dépiler */

    while (curr != NULL && !code) // verifie qu'il n'y a pas d'erreur, tant
        // TQ on n'est pas sur une feuille
    {
        elp.adrCell = curr;
        empiler(pile, &elp, &code); // empile "le futur parent"
        if (1 == code) // si erreur empiler
        {
            printf("Erreur lors de l'insertion dans la pile. Dans la fonction printPostfixee\n");
        }
        else
        {
            curr = curr->lv; // passe au fils
        }
        while(curr == NULL && !estVidePile(pile) && !code) // si pas d'erreur d'empiler ou depiler + on est sur une feuille

        {
            depiler(pile, &elp, &code);
            if (1 == code) // verifie si depiler a reussi
            {
                printf("Erreur lors de l'insertion dans la pile. Dans la fonction printPostfixee\n");
            }
            else
            {
                curr = elp.adrCell;
                fprintf(file, "(%c,%d) ", curr->val, getNbFils_ou_Freres(curr->lv));
                curr = curr->lh; // passage au frere de la feuille
            }
        }
    }
    fprintf(file, "%d\n", getNbFils_ou_Freres(racine)); // affiche le nombre de racines
    libererPile(&pile); // libere pile
}

//Version recursive de printPostfixee
void printPostfixee_auxiliaire(FILE *file, cell_lvlh_t *racine)
{
    if (racine == NULL)
    {
        return;
    }

    printPostfixee_auxiliaire(file, racine->lv); // Parcours récursif des fils
    fprintf(file, "(%c,%d) ", racine->val, getNbFils_ou_Freres(racine->lv));
    printPostfixee_auxiliaire(file, racine->lh); // Parcours récursif des frères
}

void printPostfixee_recursive(FILE *file, cell_lvlh_t *racine)
{
    printPostfixee_auxiliaire(file, racine);
    fprintf(file, "%d\n", getNbFils_ou_Freres(racine)); // affiche le nombre de racines
}

