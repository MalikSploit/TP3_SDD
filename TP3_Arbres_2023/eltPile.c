/**
 * @file eltPile.c
 * @brief fichier d'implementation pour la gestion du type des elements de pile
 */
#include <stdio.h>

#include "eltPile.h"


/* ------------------------- Gestion des elements de type 'int' ------------------------- */
/**
 * @brief Ecrire une fonction de comparaison de 2 elements 'int'
 * @param [in] elt1 l'adresse du 1er element du type 'eltType'
 * @param [in] elt2 l'adresse du 2eme element du type 'eltType'
 * @return 1 si les 2 elements sont egaux; 0 s'ils sont differents
 */
//int compareElt(const eltType *elt1, const eltType *elt2)
//{
//    return *elt1 == *elt2;
//}


/**
 * @brief Copier la valeur d'un element a un autre emplacement
 * @param [in] source l'adresse de l'element a copier
 * @param [in] destination l'adresse de la destination
 */
//void copyElt(const eltType *source, eltType *destination)
//{
//    *destination = *source;
//}


/* ---------- Gestion des elements de type struct contenant un 'char' et un 'int' ---------- */
/**
 * @brief Ecrire une fonction de comparaison de 2 elements
 * @param [in] elt1 l'adresse du 1er element
 * @param [in] elt2 l'adresse du 2eme element
 * @return 1 si les 2 elements sont egaux; 0 s'ils sont differents
 */
int compareElt(const eltType *elt1, const eltType *elt2)
{
    return (elt1->lettre == elt2->lettre && elt1->num == elt2->num);
}


/**
 * @brief Copier la valeur d'un element dans un autre emplacement
 * @param [in] source l'adresse de l'element a copier
 * @param [in] destination l'adresse de la destination
 */
void copyElt(const eltType *source, eltType *destination)
{
    destination->lettre = source->lettre;
    destination->num = source->num;
}