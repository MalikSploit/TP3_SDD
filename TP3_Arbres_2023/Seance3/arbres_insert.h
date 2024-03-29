/**
 * @file arbres_insertion.h
 * @brief fichier d'entete du module pour l'insertion de valeur dans une arborescence
 */

#ifndef __ARBRE_INSERTION_H__
#define __ARBRE_INSERTION_H__

#include "../eltsArbre.h"

/**
 * @brief rechercher un point de valeur v
 * @param [in] racine pointeur vers la racine de l'arborescence
 * @param [in] v la valeur a rechercher
 * @return
 *   - l'adresse du point contenant v si v existe dans l'arborescence
 *   - NULL, sinon
 */
cell_lvlh_t* rechercher_v(cell_lvlh_t* racine, char v);
cell_lvlh_t* rechercher_v_recursive(cell_lvlh_t* racine, char v);


/**
 * @brief rechercher le double prec de w dans une liste de fils
 * @param [in] adrPere l'adresse du pere
 * @param [in] w la valeur a inserer
 * @return l'adresse du pointeur prec apres lequel w doit etre inseree
 */
cell_lvlh_t** rechercherPrecFilsTries(cell_lvlh_t* adrPere, char w);
cell_lvlh_t** rechercherPrecFilsTries_recursive(cell_lvlh_t* adrPere, char w);


/**
 * @brief inserer une valeur w dans les fils d'un point de valeur v
 * @param [in] racine la racine de l'arborescence
 * @param [in] v la valeur d'un point auquel on va inserer la valeur w en fils
 * @param [in] w la valeur a inserer
 * @return 1 - insertion realisee; 0 - insertion n'a pas ete realisee
 */
int insererTrie(cell_lvlh_t *racine, char v, char w);

#endif