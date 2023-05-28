/**
 * program for general linked list testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "../Seance1/arbres_construct.h"
#include "arbres_parcours.h"
#include "../../teZZt.h"


BEGIN_TEST_GROUP(ARBRE_PARCOURS)

TEST(nouvCell)
{
	cell_lvlh_t *new;

	new = allocPoint('A');
	REQUIRE( NULL != new ); 
	CHECK( 'A' == new->val );
	CHECK( NULL == new->lv );
	CHECK( NULL == new->lh );

	free(new);
}


TEST(getNbFils_ou_Freres)
{
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[35m\ngetNbFils_ou_Freres :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	REQUIRE( NULL != racine );
//	printf("A = %c\n", racine->val);
	CHECK( 2 == getNbFils_ou_Freres(racine) );     // 2 freres y compris lui-meme
	CHECK( 3 == getNbFils_ou_Freres(racine->lv) ); // 3 fils

	REQUIRE( NULL != racine->lv );
//	printf("B = %c\n", racine->lv->val);
	CHECK( 3 == getNbFils_ou_Freres(racine->lv) );     // 3 freres y compris lui-meme
	CHECK( 2 == getNbFils_ou_Freres(racine->lv->lv) ); // 2 fils

	REQUIRE( NULL != racine->lv->lh );
//	printf("D = %c\n", racine->lv->lh->val);
	CHECK( 0 == getNbFils_ou_Freres(racine->lv->lh->lv) ); // 0 fils

	REQUIRE( NULL != racine->lv->lh->lh );
//	printf("H = %c\n", racine->lv->lh->lh->val);
	CHECK( 1 == getNbFils_ou_Freres(racine->lv->lh->lh->lv) ); // 1 fils

    fclose(file);
	libererArbre(&racine);
}


//Test avec l'arbre du TP
TEST(printPostfixee_pref_exTP)
{
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[35m\nprintPostFixee :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	printPostfixee(stdout, racine);
	printPostfixee(file, racine);
	fclose(file);
	CHECK( 0 == strcmp(buffer,"(E,0) (J,0) (B,2) (D,0) (G,0) (H,1) (A,3) (K,0) (M,0) (T,0) (F,3) (I,0) (C,2) 2\n") );
	
	libererArbre(&racine);
}


//Test avec un arbre contenant uniquement des liens verticaux
TEST(printPostfixee_Fichier_avec_lv)
{
    int nbRacines = 0;
    int nbEltsPref = 0;
    eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
    cell_lvlh_t *racine = NULL;

    char buffer[1024];
    FILE *file = fmemopen(buffer, 1024, "w");
    REQUIRE(NULL != file);

    printf("\033[35m\nprintPostfixee_Fichier_avec_lv :");
    printf("\033[0m\n");

    nbRacines = lirePref_fromFileName("../Fichier_avec_lv.txt", tabEltPref, &nbEltsPref);
    racine = pref2lvlh(tabEltPref, nbRacines);

    printPostfixee(stdout, racine);
    printPostfixee(file, racine);
    fclose(file);
    CHECK(0 == strcmp(buffer, "(J,0) (I,1) (H,1) (G,1) (F,1) (E,1) (D,1) (C,1) (B,1) (A,1) 1\n"));

    libererArbre(&racine);
    CHECK(racine == NULL);
}


//Test avec un arbre contenant uniquement des liens horizentaux
TEST(printPostfixee_Fichier_avec_lh)
{
    int nbRacines = 0;
    int nbEltsPref = 0;
    eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
    cell_lvlh_t *racine = NULL;

    char buffer[1024];
    FILE *file = fmemopen(buffer, 1024, "w");
    REQUIRE(NULL != file);

    printf("\033[35m\nprintPostfixee_Fichier_avec_lh :");
    printf("\033[0m\n");

    nbRacines = lirePref_fromFileName("../Fichier_avec_lh.txt", tabEltPref, &nbEltsPref);
    racine = pref2lvlh(tabEltPref, nbRacines);

    printPostfixee(stdout, racine);
    printPostfixee(file, racine);
    fclose(file);
    CHECK(0 == strcmp(buffer, "(A,0) (B,0) (C,0) (D,0) (E,0) (F,0) (G,0) (H,0) (I,0) (J,0) 10\n"));

    libererArbre(&racine);
    CHECK(racine == NULL);
}


//Test avec un arbre vide
TEST(printPostfixee_Fichier_Vide)
{
    int nbRacines = 0;
    int nbEltsPref = 0;
    eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
    cell_lvlh_t *racine = NULL;

    char buffer[1024];
    FILE *file = fmemopen(buffer, 1024, "w");
    REQUIRE(NULL != file);

    printf("\033[35m\nprintPostfixee_Fichier_Vide :");
    printf("\033[0m\n");

    nbRacines = lirePref_fromFileName("../Fichier_Vide.txt", tabEltPref, &nbEltsPref);
    racine = pref2lvlh(tabEltPref, nbRacines);

    printPostfixee(stdout, racine);
    printPostfixee(file, racine);
    fclose(file);
    CHECK(0 == strcmp(buffer, "0\n"));

    libererArbre(&racine);
    CHECK(racine == NULL);
}


END_TEST_GROUP(ARBRE_PARCOURS)

int main(void) {
	RUN_TEST_GROUP(ARBRE_PARCOURS);
	return EXIT_SUCCESS;
}
