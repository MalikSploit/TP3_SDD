/**
 * @file arbres_parcours.c
 * @brief fichier d'implementation du module pour le parcours d'arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_parcours.h"


/** TO DO
 * @brief calculer le nombre de fils ou freres d'un point a partir du pointeur du debut de la liste
 * @param [in] ptCell pointeur vers le 1er frere
 * @return le nombre de fils ou freres
 */
int getNbFils_ou_Freres(cell_lvlh_t* ptCell)
{
    int count = 0;

    // Comptez le nombre de frères en parcourant la liste horizontale.
    cell_lvlh_t* temp = ptCell;
    while(temp != NULL)
    {
        count++;
        temp = temp->lh;
    }

    // Réinitialisez le compteur pour compter les fils.
    count = 0;
    temp = ptCell;
    while(temp != NULL)
    {
        count++;
        temp = temp->lv;
    }

    return count;
}


/** TO DO
 * @brief parcours en profondeur postfixee
 * @param [in] file le flux de sortie
 * @param [in] racine la racine de l'arborescence
 */
void printPostfixee(FILE* file, cell_lvlh_t* racine)
{
    if (racine == NULL)
    {
        // Arbre vide, rien à faire.
        return;
    }

    // Visitez d'abord le sous-arbre vertical (enfants).
    printPostfixee(file, racine->lv);

    // Puis le sous-arbre horizontal (frères).
    printPostfixee(file, racine->lh);

    // Enfin, écrivez la valeur du nœud lui-même.
    fprintf(file, "%c ", racine->val);
}
