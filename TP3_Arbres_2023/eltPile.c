/**
 * @file eltPile.c
 * @brief fichier d'implementation pour la gestion du type des elements de pile
 */
#include <stdio.h>

#include "eltPile.h"

/*
 * @brief Copier la valeur d'un element dans un autre emplacement
 * @param [in] src l'adresse de l'element a copier
 * @param [in] dest l'adresse de la destination
 */
/* -------------------------------------------------------------------- */
/* copyElt Copie la valeur d'un element dans un autre                   */
/*                                                                      */
/* Cette fonction permet de copier la valeur d'un element dans un autre */
/* emplacement                                                          */
/*                                                                      */
/* En entree:   src adresse de l'element a copier                       */
/*              dest adresse de l'element de destination                */
/* -------------------------------------------------------------------- */
void copyElt(eltType_pile *src, eltType_pile *dest)
{
    if (src != NULL && dest != NULL)
    {
        dest->adrCell = src->adrCell;
        dest->adrPrec = src->adrPrec;
        dest->nbFils_ou_Freres = src->nbFils_ou_Freres;
    }
    else
    {
        printf("Erreur: un ou plusieurs pointeurs sont NULL dans copyElt()\n");
    }
}


