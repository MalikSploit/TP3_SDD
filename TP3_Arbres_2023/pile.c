/**
 * @file pile.c
 * @brief fichier d'implementation pour la gestion de pile
 */

#include <stdlib.h>
#include "pile.h"

/**
 * @brief Initialiser une pile du type pile_t
 *   - allocation de memoire pour une structure pile_t et un tableau de taille elements
 * @param [in] taille taille de la pile
 * @return l'adresse de la structure
 */

/* -------------------------------------------------------------------- */
/* initPile Initialise une pile                                         */
/*                                                                      */
/* Cette fonction initialise une pile                                   */
/*                                                                      */
/* En entree: taille la taille maximale de la pile                      */
/* En sortie: adresse de la pile                                        */
/* -------------------------------------------------------------------- */
pile_t* initPile(int taille)
{
    pile_t *pile = NULL;

    if (taille > 0)
    {
        // Allocation de mémoire pour la structure pile_t
        pile = malloc(sizeof(pile_t));

        if (pile)
        {
            pile->taille = taille;
            pile->sommet = -1;

            // Allocation de mémoire pour le tableau de taille éléments
            pile->base = malloc(taille * sizeof(eltType_pile));
            if (!pile->base)
            {
                free(pile);
                pile = NULL;
            }
        }
    }
    // Retourne l'adresse de la structure nouvellement allouée
    return pile;
}


/**
 * @brief Liberer les memoires occupees par la pile
 * @param [in, out] adrPtPile l'adresse du pointeur de la structure pile_t
 */
/* -------------------------------------------------------------------- */
/* libererPile Libere la pile                                           */
/*                                                                      */
/* Cette fonction libere la memoire occupee par la pile                 */
/*                                                                      */
/* En entree: adrPtPile adresse du pointeur de la pile                  */
/* -------------------------------------------------------------------- */
void libererPile(pile_t** adrPtPile)
{
    if (*adrPtPile != NULL)
    {
        // Libération de la mémoire allouée pour le tableau
        free((*adrPtPile)->base);
        // Libération de la mémoire allouée pour la structure
        free(*adrPtPile);
        // Réinitialisation du pointeur à NULL
        *adrPtPile = NULL;
    }
}


/**
 * @brief Verifier si la pile est vide (aucun element dans la "base")
 * @param [in] ptPile l'adresse de la structure pile_t
 * @return 1 - vide, ou 0 - non vide
 */
/* -------------------------------------------------------------------- */
/* estVidePile Verifie si la pile est vide                              */
/*                                                                      */
/* Cette fonction verifie si la pile est vide                           */
/*                                                                      */
/* En entree:   ptPile l'adresse de la pile                             */
/* En sortie:   retourne 1 si la pile est vide et 0 si la vide n'est    */
/*              pas vide                                                */
/* -------------------------------------------------------------------- */
int estVidePile(pile_t *ptPile)
{
    return ptPile->sommet == -1;
}


/**
 * @brief Entrer un element dans la pile
 * @param [in, out] ptPile l'adresse de la structure pile_t
 * @param [in] ptVal l'adresse de la valeur a empiler
 * @param [in, out] code : l'adresse du code de sortie
 *                     *code = 0 si reussi
 *                           = 1 si echec
 */
/* -------------------------------------------------------------------- */
/* empiler Ajouter un element dans la pile                              */
/*                                                                      */
/* Cette fonction ajoute un element dans la pile                        */
/*                                                                      */
/* En entree:   ptPile l'adresse de la pile                             */
/*              ptVal l'adresse de la valeur a empiler                  */
/*              code l'adresse du code de sortie                        */
/* En sortie:   code le code de sortie : *code = 0 si reussi            */
/*              *code = 1 si echec                                      */
/* -------------------------------------------------------------------- */
void empiler(pile_t * ptPile, eltType_pile * ptVal, int * code)
{
    *code = 1;
    if (ptPile != NULL)
    {
        if (ptPile->taille-1 > ptPile->sommet)
        {
            *code = 0;
            ptPile->sommet++;
            ptPile->base[ptPile->sommet] = *ptVal;
        }
    }
}



/**
 * @brief Sortir un element de la pile
 * @param [in, out] ptPile l'adresse de la structure pile_t
 * @param [out] ptRes l'adresse de l'element sorti
 * @param [in, out] code : l'adresse du code de sortie
 *                     *code = 0 si reussi
 *                           = 1 si echec
 */
/* -------------------------------------------------------------------- */
/* depiler Depiler un element de la pile                                */
/*                                                                      */
/* Cette fonction depile un element de la pile                          */
/*                                                                      */
/* En entree:   ptPile l'adresse de la pile                             */
/*              code l'adresse du code de sortie                        */
/* En sortie:   ptRes l'adresse de l'element sorti                      */
/*              code le code de sortie : *code = 0 si reussi            */
/*              *code = 1 si echec                                      */
/* -------------------------------------------------------------------- */
void depiler(pile_t * ptPile, eltType_pile * ptRes, int * code)
{
    *code = 1;
    if (ptPile != NULL)
    {
        if (-1 != ptPile->sommet)
        {
            *code = 0;
            *ptRes = ptPile->base[ptPile->sommet];
            ptPile->sommet--;
        }
    }
}
