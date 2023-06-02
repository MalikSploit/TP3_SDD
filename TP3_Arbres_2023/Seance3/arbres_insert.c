/**
 * @file arbres_insert.c
 * @brief fichier d'implementation du module pour l'insertion de valeur dans une arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_insert.h"
#include "../Seance1/arbres_construct.h"


/**
 * @brief rechercher un point de valeur v
 * @param [in] racine pointeur vers la racine de l'arborescence
 * @param [in] v la valeur a rechercher
 * @return
 *   - l'adresse du point contenant v si v existe dans l'arborescence
 *   - NULL, sinon
 */
/* -------------------------------------------------------------------- */
/* rechercher_v Recherche un point de valeur v                          */
/*                                                                      */
/* Cette fonction recherche un point de valeur v                        */
/*                                                                      */
/* En entree:   racine pointeur de la racine de l'arborescence          */
/*              v valeur recherchee                                     */
/* En sortie:   resultat l'adresse du point contenant v si v existe     */
/*              NULL sinon                                              */
/* -------------------------------------------------------------------- */
cell_lvlh_t* rechercher_v(cell_lvlh_t* racine, char v)
{
    cell_lvlh_t* resultat = NULL;

    if (racine != NULL)
    {
        pile_t* pile = initPile(NB_ELTPREF_MAX);

        if (pile != NULL)
        {
            eltType_pile cour;
            cour.adrCell = racine;
            int code;

            // Parcours de l'arborescence tant que le pointeur courant n'est pas NULL et que la pile n'est pas vide
            while (cour.adrCell != NULL || !estVidePile(pile))
            {
                // Parcours en profondeur vers le bas (liens verticaux)
                while (cour.adrCell != NULL)
                {
                    // Si la valeur du point courant correspond à la valeur recherchée, on met à jour le résultat et on arrête le parcours
                    if (cour.adrCell->val == v)
                    {
                        resultat = cour.adrCell;
                        break;
                    }

                    // Empilement du point courant pour le parcours ultérieur vers le bas
                    empiler(pile, &cour, &code);
                    cour.adrCell = cour.adrCell->lv;
                }

                // Si le résultat a été trouvé, on arrête le parcours
                if (resultat != NULL)
                {
                    break;
                }

                // Si la pile n'est pas vide, on dépile un point et on se déplace vers la droite (liens horizontaux)
                if (!estVidePile(pile))
                {
                    depiler(pile, &cour, &code);
                    cour.adrCell = cour.adrCell->lh;
                }
            }

            libererPile(&pile);
        }
    }

    return resultat;
}


/**
 * @brief rechercher le double prec de w dans une liste de fils
 * @param [in] adrPere l'adresse du pere
 * @param [in] w la valeur a inserer
 * @return l'adresse du pointeur prec apres lequel w doit etre inseree
 */
/* -------------------------------------------------------------------- */
/* rechercherPrecFilsTries Recherche le pointeur précédent la cellule   */
/* dans laquelle inserer une nouvelle valeur                            */
/*                                                                      */
/* Cette fonction recherche le pointeur précédent la cellule dans       */
/* laquelle on insere w                                                 */
/*                                                                      */
/* En entree:   adrPere adresse de la cellule du pere                   */
/*              w valeur a inserer                                      */
/* En sortie:   pprec adresse du pointeur prec apres lequel w doit etre */
/*              inseree                                                 */
/* -------------------------------------------------------------------- */
cell_lvlh_t** rechercherPrecFilsTries(cell_lvlh_t* adrPere, char w)
{
    cell_lvlh_t** pprec = &(adrPere->lv);

    // Parcourir les fils jusqu'à trouver le pointeur précédant lequel insérer w
    while (*pprec != NULL && (*pprec)->val < w) 
    {
        pprec = &((*pprec)->lh);
    }

    return pprec;
}


/**
 * @brief inserer une valeur w dans les fils d'un point de valeur v
 * @param [in] racine la racine de l'arborescence
 * @param [in] v la valeur d'un point auquel on va inserer la valeur w en fils
 * @param [in] w la valeur a inserer
 * @return 1 - insertion realisee; 0 - insertion n'a pas ete realisee
 */
/* -------------------------------------------------------------------- */
/* rechercherPrecFilsTries Insere une valeur dans l'arborescence        */
/*                                                                      */
/* Cette fonction insere une valeur w dans les fils d'un point de       */
/* valeur v                                                             */
/*                                                                      */
/* En entree:   racine pointeur de la racine de l'arborescence          */
/*              v la valeur du point auquel on va inserer w en fils     */
/*              w valeur a inserer                                      */
/* En sortie:   resultat 1 si l'insertion a ete realisee, 0 sinon       */
/* -------------------------------------------------------------------- */
int insererTrie(cell_lvlh_t* racine, char v, char w)
{
    cell_lvlh_t* pere = rechercher_v(racine, v);
    int resultat = 0;

    if (pere != NULL)
    {
        cell_lvlh_t** pprec = rechercherPrecFilsTries(pere, w);
        if (*(pprec) != NULL)
        {
            printf("(*pprec)->val = %c\n", (*pprec)->val);
        }

        // Vérifier si la valeur w n'existe pas déjà dans les fils
        if (*pprec == NULL || (*pprec)->val != w)
        {
            // Allouer un nouveau point de valeur w
            cell_lvlh_t* nouv = allocPoint(w);

            if (nouv != NULL)
            {
                nouv->lh = *pprec;
                *pprec = nouv;
                resultat = 1;
            }
        }
    }

    return resultat;
}
