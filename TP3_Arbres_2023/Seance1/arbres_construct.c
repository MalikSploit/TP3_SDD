/**
 * @file arbres_construct.c
 * @brief fichier d'implementation du programme pour la construction d'une arborescence
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "arbres_construct.h"

/**
 * @brief lire le fichier contenant la representation prefixee de l'arborescence
 * @param [in] fileName le nom du fichier contenant la representation prefixee
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref l'adresse memoire contenant le nombre des elements du tabEltPref
 * @return le nombre de racines
 */
/* -------------------------------------------------------------------- */
/* lirePref_fromFileName    Lecture d'une liste prefixee à partir d'un  */
/*                          fichier                                     */
/*                                                                      */
/* Cette fonction lit une liste prefixee a partir d'un fichier et       */
/* renvoie une representation prefixee, ainsi que le nombre d'elements  */
/* et le nombre de racines.                                             */
/*                                                                      */
/* En entrée:   fileName le nom du fichier                              */
/*              tabEltPref tableau des elements de la representation    */
/*              prefixee                                                */
/*              nbEltsPref adresse contenant le nombre d'elements de    */
/*              tabEltPref                                              */
/* En sortie:   tabEltPref tableau des elements de la representation    */
/*              prefixee                                                */
/*              nbEltsPref adresse contenant le nombre d'elements de    */
/*              tabEltPref                                              */
/*              nbRacines le nombre de racines                          */
/* -------------------------------------------------------------------- */
int lirePref_fromFileName(const char* fileName, eltPrefPostFixee_t* tabEltPref, int* nbEltsPref)
{
    FILE *file = fopen(fileName, "r");
    int  nbRacines = 0;
    char val;
    int  nbFils = 0;

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

//Version recurisve de lirePref_fromFileName
void lirePref_recursive(FILE* file, eltPrefPostFixee_t* tabEltPref, int* nbEltsPref)
{
    char val;
    int  nbFils = 0;

    if(fscanf(file, " %c %d", &val, &nbFils) != 2)
    {
        return;
    }

    tabEltPref[*nbEltsPref].val = val;
    tabEltPref[*nbEltsPref].nbFils = nbFils;
    (*nbEltsPref)++;

    lirePref_recursive(file, tabEltPref, nbEltsPref);
}

int lirePref_fromFileName_recursive(const char* fileName, eltPrefPostFixee_t* tabEltPref, int* nbEltsPref)
{
    FILE *file = fopen(fileName, "r");
    int  nbRacines = 0;

    if (file != NULL)
    {
        fscanf(file, "%d", &nbRacines);

        *nbEltsPref = 0;

        // Start the recursion
        lirePref_recursive(file, tabEltPref, nbEltsPref);

        fclose(file);
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
/* -------------------------------------------------------------------- */
/* printTabEltPref Affiche une liste prefixee                           */
/*                                                                      */
/* Cette fonction affiche les elements d'une representation prefixee    */
/*                                                                      */
/* En entrée:   file le flux de sortie                                  */
/*              tabEltPref le tableau de la representation prefixee     */
/*              nbEltsPref le nombre d'elements de tabEltPref           */
/* En sortie:   tabEltPref le tableau de la representation prefixee     */
/*              nbEltsPref le nombre d'elements de tabEltPref           */
/* -------------------------------------------------------------------- */
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
    fprintf(file, "\n");
}

//Version recursive de printTabEltPref
void printTabEltPref_auxiliaire(FILE *file, eltPrefPostFixee_t *tabEltPref, int index, int nbEltsPref)
{
    if(index == nbEltsPref)
    {
        fprintf(file, "\n");
        return;
    }

    if(index == nbEltsPref-1)
    {
        fprintf(file, "(%c,%d)", tabEltPref[index].val, tabEltPref[index].nbFils);
    }
    else
    {
        fprintf(file, "(%c,%d) ", tabEltPref[index].val, tabEltPref[index].nbFils);
    }

    printTabEltPref_auxiliaire(file, tabEltPref, index + 1, nbEltsPref);
}

void printTabEltPref_recursive(FILE *file, eltPrefPostFixee_t *tabEltPref, int nbEltsPref)
{
    printTabEltPref_auxiliaire(file, tabEltPref, 0, nbEltsPref);
}


/**
 * @brief creer et initialiser un nouveau point de l'arborescence
 * @param [in] val la valeur du point
 * @return l'adresse du nouveau point 
 */
/* -------------------------------------------------------------------- */
/* allocPoint Creer et initialise un nouveau point de l'arborescence    */
/*                                                                      */
/* Cette fonction creee et initialise une nouvelle cellule dans la liste*/
/*                                                                      */
/* En entree: val la valeur a ajouter                                   */
/* En sortie: l'adresse du nouveau point                                */
/* -------------------------------------------------------------------- */
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
/* -------------------------------------------------------------------- */
/* pref2lvlh Construit un arbe a partir de la representation prefixee   */
/*                                                                      */
/* Cette fonction construit un arbre a partir de la representation      */
/* prefixee                                                             */
/*                                                                      */
/* En entrée:   tabEltPref l'adresse du tableau des elements de la      */
/*              representation prefixee                                 */
/*              nbRacines le nombre de racines de la representation     */
/*              prefixee                                                */
/* En sortie:   racine l'adresse de la racine de l'arborescence         */
/* -------------------------------------------------------------------- */
cell_lvlh_t *pref2lvlh(eltPrefPostFixee_t *tabEltPref, int nbRacines)
{
    cell_lvlh_t  *racine = NULL;   // contient l'adresse de la racine de l'arbre renvoyé

    if (nbRacines > 0 && tabEltPref != NULL)
    {
        cell_lvlh_t         **pprec           = &racine; // contient l'adresse à laquelle on doit stocker le prochain noeud visité
        cell_lvlh_t          *nouv; //contient l'adresse du nouveau noeud créé à chaque visite d'un élément de tabEltPref
        int                  nbFils_ou_Freres = nbRacines; //contient soit le nombre de fils ou de frères
        eltPrefPostFixee_t   *courLco         = tabEltPref; // pointeur courant pour le parcours de tabEltPref
        pile_t               *pile            = initPile(PILE_SZ); //pile pour stocker les noeuds à visiter prochainement
        eltType_pile         eltPile; //variable qui contient l'élément ajouté à la pile
        int                  code;

        while ( nbFils_ou_Freres > 0 || !estVidePile(pile) )
        {
            if (nbFils_ou_Freres > 0)
            {
                nouv = allocPoint(courLco->val);//créer un nouveau noeud de l'arbre de valeur val
                // stocker le nouveau noeud à la bonne adresse pour créer les liens de l'arbre
                *pprec = nouv;

                //ajouter à la pile le lien vertical du noeud courant pour le traiter plus tard
                eltPile.adrCell = nouv;
                eltPile.nbFils_ou_Freres = nbFils_ou_Freres-1;
                eltPile.adrPrec = &(nouv->lh);
                empiler(pile, &eltPile, &code);

                //mettre à jour pprec pour dire à quelle adresse on va stocker le prochain noeud visité
                //mettre à jour nbFils_ou_Freres
                pprec = &nouv->lv;
                nbFils_ou_Freres = courLco->nbFils;

                // passer a l'element suivant dans la liste contigue
                courLco++;
            }
            else // le point courant n'a pas de fils, on remonte
            {
                if (!estVidePile(pile))
                {
                    depiler(pile, &eltPile, &code);
                    pprec = &(eltPile.adrCell->lh);
                    nbFils_ou_Freres = eltPile.nbFils_ou_Freres;
                }
            }
        }

        //libérer la pile et renvoyer le résultat
        libererPile(&pile);
    }
    return racine;
}

/**
 * @brief liberer les blocs memoire d'un arbre
 * @param [in] adrPtRacine l'adresse du pointeur de la racine d'un arbre
 */
/* -------------------------------------------------------------------- */
/* libererArbre Libere une arborescence                                 */
/*                                                                      */
/* Cette fonction libere les blocs memoire d'un arbre                   */
/*                                                                      */
/* En entrée:   adrPtRacine l'adresse du pointeur de la racine de       */
/*              l'arbre                                                 */
/* -------------------------------------------------------------------- */
void libererArbre(cell_lvlh_t **adrPtRacine)
{
    if (*adrPtRacine != NULL)
    {

        pile_t      *pile = initPile(PILE_SZ);
        int          code;
        eltType_pile eltPile;

        // Initialisation de la pile avec la racine
        eltPile.adrCell          = *adrPtRacine;
        eltPile.adrPrec          = NULL;
        eltPile.nbFils_ou_Freres = 0;
        empiler(pile, &eltPile, &code);

        while (!estVidePile(pile))
        {
            depiler(pile, &eltPile, &code);

            if (eltPile.adrCell->lv != NULL)
            {
                // Si le noeud actuel a un fils, on l'ajoute à la pile
                eltType_pile eltFils;
                eltFils.adrCell = eltPile.adrCell->lv;
                eltFils.adrPrec = NULL;
                eltFils.nbFils_ou_Freres = 0;
                empiler(pile, &eltFils, &code);
            }

            if (eltPile.adrCell->lh != NULL)
            {
                // Si le noeud actuel a un frère, on l'ajoute à la pile
                eltType_pile eltFrere;
                eltFrere.adrCell = eltPile.adrCell->lh;
                eltFrere.adrPrec = NULL;
                eltFrere.nbFils_ou_Freres = 0;
                empiler(pile, &eltFrere, &code);
            }

            // Enfin, on libère le noeud actuel
            free(eltPile.adrCell);
        }

        libererPile(&pile);
        *adrPtRacine = NULL;
    }
}


//Version recursive de libererArbre
void libererArbre_auxiliaire(cell_lvlh_t *racine)
{
    if (racine != NULL)
    {
        // Libérer les fils
        libererArbre_auxiliaire(racine->lv);

        // Libérer les frères
        libererArbre_auxiliaire(racine->lh);

        // Libérer le noeud lui-même
        free(racine);
    }
}

void libererArbre_recursive(cell_lvlh_t **adrPtRacine)
{
    if (*adrPtRacine != NULL)
    {
        libererArbre_auxiliaire(*adrPtRacine);
        *adrPtRacine = NULL;
    }
}

