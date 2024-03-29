/**
 * @file eltPile.h
 * @brief fichier d'entete pour la gestion du type des elements de pile
 */
#ifndef __ELTPILE_H__
#define __ELTPILE_H__

#include "eltsArbre.h"

/** TO DO
 * @struct eltType_pile
 * @brief definir la SDD des elements de pile
 * 3 champs :
 *   - adrCell : l'adresse d'un point/cellule d'une arborescence
 *   - adrPrec : l'adresse du pointeur prec du point
 *   - nbFils_ou_Freres : le nombre de fils ou freres d'un point
 */
typedef struct
{
    cell_lvlh_t *adrCell; // l'adresse d'un point/cellule d'une arborescence
    cell_lvlh_t **adrPrec; // l'adresse du pointeur prec du point
    int nbFils_ou_Freres; // le nombre de fils ou freres d'un point
} eltType_pile;


/**
 * @brief Copier la valeur d'un element dans un autre emplacement
 * @param [in] src l'adresse de l'element a copier
 * @param [in] dest l'adresse de la destination
 */
void copyElt(eltType_pile *src, eltType_pile *dest);

#endif