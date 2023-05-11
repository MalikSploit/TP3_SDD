/**
 * @file arbres_construct.c
 * @brief fichier d'implementation du programme pour la construction d'une arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_construct.h"

/**
 * @brief lire le fichier contenant la representation prefixee de l'arborescence
 * @param [in] fileName le nom du fichier contenant la representation prefixee
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref l'adresse memoire contenant le nombre des elements du tabEltPref
 * @return le nombre de racines
 */
int lirePref_fromFileName(const char* fileName, eltPrefPostFixee_t* tabEltPref, int* nbEltsPref)
{
    FILE* file = fopen(fileName, "r");
    int nbRacines = 0;
    int nbElems = 0;

    if (file == NULL)
    {
        printf("Error opening file.\n");
        nbRacines = -1;
    }
    else
    {
        char c;
        int i = 0;
        int nbFils = 0;

        while ((c = fgetc(file)) != EOF)
        {
            if (c == '\n')
            {
                nbRacines++;
                continue;
            }
            if (c == '(')
            {
                if (fscanf(file, "%c", &c) == EOF)
                {
                    printf("Error reading file.\n");
                    nbRacines = -1;
                }
                tabEltPref[i].val = c;
                if (fscanf(file, "%d", &nbFils) == EOF)
                {
                    printf("Error reading file.\n");
                    nbRacines = -1;
                }
                tabEltPref[i].nbFils = nbFils;
                i++;
                nbElems++;
            }
            else if (c == ')')
            {
                continue;
            }
            else
            {
                printf("Invalid character in file.\n");
                nbRacines = -1;
            }
        }
    }

    fclose(file);
    *nbEltsPref = nbElems;
    return nbRacines;
}

/** TO DO
 * @brief afficher les elements de la representation prefixee sur un flux de sortie
 * @param file : le flux de sortie
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref le nombre des elements du tabEltPref
 */
void printTabEltPref(FILE *file, eltPrefPostFixee_t *tabEltPref, int nbEltsPref)
{
    for (int i = 0; i < nbEltsPref; i++)
    {
        fprintf(file, "(%c,%d)", tabEltPref[i].val, tabEltPref[i].nbFils);
    }
    fprintf(file, "\n");
}

/** TO DO
 * @brief creer et initialiser un nouveau point de l'arborescence
 * @param [in] val la valeur du point
 * @return l'adresse du nouveau point 
 */
cell_lvlh_t* allocPoint(char val)
{
    cell_lvlh_t* point = (cell_lvlh_t*)malloc(sizeof(cell_lvlh_t));

    if (point == NULL) {
        return NULL;
    }

    point->val = val;
    point->lv = NULL;
    point->lh = NULL;

    return point;
}

/** TO DO
 * @brief construire un arbre avec lvlh a partir de representation prefixee
 * @param [in] tabEltPref tableau des elements de la representation prefixee
 * @param [in] nbRacines nombre de racines de l'arborescence
 * @return : 
 *     - NULL si l'arbre resultatnt est vide
 *     - l'adresse de la racine de l'arbre sinon
*/
//cell_lvlh_t *pref2lvlh(eltPrefPostFixee_t *tabEltPref, int nbRacines)
//{
//
//}


/** TO DO
 * @brief liberer les blocs memoire d'un arbre
 * @param [in] adrPtRacine l'adresse du pointeur de la racine d'un arbre
 */
void libererArbre(cell_lvlh_t **adrPtRacine)
{
    if (*adrPtRacine != NULL) {
        libererArbre(&((*adrPtRacine)->lv));
        libererArbre(&((*adrPtRacine)->lh));
        free(*adrPtRacine);
        *adrPtRacine = NULL;
    }
}
