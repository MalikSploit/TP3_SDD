/**
 * @file arbres_construct.c
 * @brief fichier d'implementation du programme pour la construction d'une arborescence
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    FILE *file = fopen(fileName, "r");
    int  nbRacines;
    char val;
    int  nbFils;

    if (file != NULL)
    {
        fscanf(file, "%d", &nbRacines); // Lire le nombre de racines

        *nbEltsPref = 0; // Initialiser le nombre d'éléments à 0

        while (fscanf(file, " %c %d", &val, &nbFils) == 2)
        { // Lire chaque paire de caractère et nombre
            tabEltPref[*nbEltsPref].val = val;
            tabEltPref[*nbEltsPref].nbFils = nbFils;
            (*nbEltsPref)++;
        }

        fclose(file); // Fermer le fichier
    }

    else
    {
        printf("Erreur d'ouverture du fichier %s\n", fileName);
        nbRacines = -1;
    }

    return nbRacines;
}


/**
 * @brief afficher les elements de la representation prefixee sur un flux de sortie
 * @param file : le flux de sortie
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref le nombre des elements du tabEltPref
 */
void printTabEltPref(FILE *file, eltPrefPostFixee_t *tabEltPref, int nbEltsPref)
{
    for(int i = 0; i < nbEltsPref; i++)
    {
        if (i == nbEltsPref-1)
        {
            fprintf(file, "(%c,%d)", tabEltPref[i].val, tabEltPref[i].nbFils);
        }
        else
        {
            fprintf(file, "(%c,%d) ", tabEltPref[i].val, tabEltPref[i].nbFils);
        }
    }
    fprintf(file, "\n"); // Ajouter une nouvelle ligne à la fin
}

/**
 * @brief creer et initialiser un nouveau point de l'arborescence
 * @param [in] val la valeur du point
 * @return l'adresse du nouveau point 
 */
cell_lvlh_t* allocPoint(char val)
{
    cell_lvlh_t* point = (cell_lvlh_t*)malloc(sizeof(cell_lvlh_t));

    if (point != NULL)
    {
        point->val = val;
        point->lv = NULL;
        point->lh = NULL;
    }

    return point;
}

/**
 * @brief construire un arbre avec lvlh a partir de representation prefixee
 * @param [in] tabEltPref tableau des elements de la representation prefixee
 * @param [in] nbRacines nombre de racines de l'arborescence
 * @return : 
 *     - NULL si l'arbre resultatnt est vide
 *     - l'adresse de la racine de l'arbre sinon
*/
cell_lvlh_t * pref2lvlh(eltPrefPostFixee_t *tabEltPref, int nbRacines)
{
    if (nbRacines <= 0)
    {
        return NULL;
    }

    cell_lvlh_t  *racine = NULL;   // contient l'adresse de la racine de l'arbre renvoyé
    cell_lvlh_t **pprec = &racine; // contient l'adresse à laquelle on doit stocker le prochain noeud visité
    //afin de créer les liens dans l'arbre
    cell_lvlh_t  *nouv; //contient l'adresse du nouveau noeud créé à chaque visite d'un élément de tabEltPref

    int     nbFils_ou_Freres = nbRacines; //contient soit le nombre de fils ou de frères
    eltPrefPostFixee_t   *courLco = tabEltPref; // pointeur courant pour le parcours de tabEltPref

    pile_t      *pile = initPile(PILE_SZ); //pile pour stocker les noeuds à visiter prochainement
    eltType_pile eltPile; //variable qui contient l'élément ajouté à la pile
    int          code;

    while ( nbFils_ou_Freres>0 || !estVidePile(pile) )
    {
        if (nbFils_ou_Freres>0)
        {
            nouv = allocPoint(courLco->val);//créer un nouveau noeud de l'arbre de valeur val
            // stocker le nouveau noeud à la bonne adresse pour créer les liens de l'arbre
            *pprec = nouv;

            //ajouter à la pile le lien vertical du noeud courant pour le traiter plus tard (plusieurs lignes)
            eltPile.adrCell = nouv;
            eltPile.adrPrec = &nouv->lv;
            eltPile.nbFils_ou_Freres = courLco->nbFils-1;
            empiler(pile, &eltPile, &code);

            //mettre à jour pprec pour dire à quelle adresse on va stocker le prochain noeud visité
            //mettre à jour nbFils_ou_Freres
            pprec = &nouv->lh;
            nbFils_ou_Freres = 0;

            // passer a l'element suivant dans la liste contigue
            courLco++;
        }
        else // le point courant n'a pas de fils, on remonte
        {
            if (!estVidePile(pile))
            {
                depiler(pile, &eltPile, &code);
                pprec = eltPile.adrPrec;
                nbFils_ou_Freres = eltPile.nbFils_ou_Freres;
            }
        }
    }

    //libérer la pile et renvoyer le résultat
    libererPile(&pile);
    return racine;
}


/**
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
