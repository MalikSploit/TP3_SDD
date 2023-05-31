/**
 * program for general linked list testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "../Seance1/arbres_construct.h"
#include "arbres_insert.h"
#include "../../teZZt.h"


BEGIN_TEST_GROUP(ARBRE_INSERT)

TEST(nouvCell) {
	cell_lvlh_t *new;

	new = allocPoint('A');
	REQUIRE( NULL != new ); 
	CHECK( 'A' == new->val );
	CHECK( NULL == new->lv );
	CHECK( NULL == new->lh );

	free(new);
}


TEST(rechercher_v) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	cell_lvlh_t *pere = NULL;

	printf("\033[35m\nrechercher_v :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	pere = rechercher_v(racine, 'X');   // valeur inexistante
	CHECK( NULL == pere );

	pere = rechercher_v(racine, 'A');   // valeur a la racine
	REQUIRE( NULL != pere );
	CHECK( 'A' == pere->val );

    // Test avec toutes les valeurs existantes dans l'arborescence
    pere = rechercher_v(racine, 'B');
    REQUIRE(NULL != pere);
    CHECK('B' == pere->val);

    pere = rechercher_v(racine, 'C');
    REQUIRE(NULL != pere);
    CHECK('C' == pere->val);

    pere = rechercher_v(racine, 'D');
    REQUIRE(NULL != pere);
    CHECK('D' == pere->val);

    pere = rechercher_v(racine, 'E');
    REQUIRE(NULL != pere);
    CHECK('E' == pere->val);

    pere = rechercher_v(racine, 'F');
    REQUIRE(NULL != pere);
    CHECK('F' == pere->val);

    pere = rechercher_v(racine, 'G');
    REQUIRE(NULL != pere);
    CHECK('G' == pere->val);

    pere = rechercher_v(racine, 'H');
    REQUIRE(NULL != pere);
    CHECK('H' == pere->val);

    pere = rechercher_v(racine, 'I');
    REQUIRE(NULL != pere);
    CHECK('I' == pere->val);

    pere = rechercher_v(racine, 'J');
    REQUIRE(NULL != pere);
    CHECK('J' == pere->val);

    pere = rechercher_v(racine, 'K');
    REQUIRE(NULL != pere);
    CHECK('K' == pere->val);

    pere = rechercher_v(racine, 'M');
    REQUIRE(NULL != pere);
    CHECK('M' == pere->val);

    pere = rechercher_v(racine, 'T');
    REQUIRE(NULL != pere);
    CHECK('T' == pere->val);

    libererArbre(&racine);
}


TEST(rechercherPrecFilsTries) {
    int nbRacines = 0;
    int nbEltsPref = 0;
    eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
    cell_lvlh_t *racine = NULL;
    cell_lvlh_t *pere = NULL;
    cell_lvlh_t **pprec = NULL;

    printf("\033[34m\nrechercherPrecFilsTries :\033[0m\n");

    nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
    racine = pref2lvlh(tabEltPref, nbRacines);

    // Recherche pour les lettres de A à T
    pere = rechercher_v(racine, 'F');
    REQUIRE(NULL != pere);
    CHECK('F' == pere->val);

    pprec = rechercherPrecFilsTries(pere, 'A');
    REQUIRE(NULL != *pprec);
    CHECK('K' == (*pprec)->val);

    pprec = rechercherPrecFilsTries(pere, 'H');
    REQUIRE(NULL != *pprec);
    CHECK('K' == (*pprec)->val);

    pere = rechercher_v(racine, 'B');
    REQUIRE(NULL != pere);
    CHECK('B' == pere->val);

    pprec = rechercherPrecFilsTries(pere, 'C');
    REQUIRE(NULL != *pprec);
    CHECK('E' == (*pprec)->val);

    pere = rechercher_v(racine, 'C');
    REQUIRE(NULL != pere);
    CHECK('C' == pere->val);

    pprec = rechercherPrecFilsTries(pere, 'D');
    REQUIRE(NULL != *pprec);
    CHECK('F' == (*pprec)->val);

    pere = rechercher_v(racine, 'A');
    REQUIRE(NULL != pere);
    CHECK('A' == pere->val);

    pprec = rechercherPrecFilsTries(pere, 'E');
    REQUIRE(NULL != *pprec);
    CHECK('H' == (*pprec)->val);

    pere = rechercher_v(racine, 'C');
    REQUIRE(NULL != pere);
    CHECK('C' == pere->val);

    pprec = rechercherPrecFilsTries(pere, 'F');
    REQUIRE(NULL != *pprec);
    CHECK('F' == (*pprec)->val);

    pere = rechercher_v(racine, 'F');
    REQUIRE(NULL != pere);
    CHECK('F' == pere->val);

    pprec = rechercherPrecFilsTries(pere, 'G');
    REQUIRE(NULL != *pprec);
    CHECK('K' == (*pprec)->val);

    pere = rechercher_v(racine, 'F');
    REQUIRE(NULL != pere);
    CHECK('F' == pere->val);

    pprec = rechercherPrecFilsTries(pere, 'H');
    REQUIRE(NULL != *pprec);
    CHECK('K' == (*pprec)->val);

    pere = rechercher_v(racine, 'C');
    REQUIRE(NULL != pere);
    CHECK('C' == pere->val);

    pprec = rechercherPrecFilsTries(pere, 'I');
    REQUIRE(NULL != *pprec);
    CHECK('I' == (*pprec)->val);

    pere = rechercher_v(racine, 'B');
    REQUIRE(NULL != pere);
    CHECK('B' == pere->val);

    pprec = rechercherPrecFilsTries(pere, 'J');
    REQUIRE(NULL != *pprec);
    CHECK('J' == (*pprec)->val);

    pere = rechercher_v(racine, 'F');
    REQUIRE(NULL != pere);
    CHECK('F' == pere->val);

    pprec = rechercherPrecFilsTries(pere, 'K');
    REQUIRE(NULL != *pprec);
    CHECK('K' == (*pprec)->val);

    pprec = rechercherPrecFilsTries(pere, 'L');
    REQUIRE(NULL != *pprec);
    CHECK('M' == (*pprec)->val);

    pprec = rechercherPrecFilsTries(pere, 'M');
    REQUIRE(NULL != *pprec);
    CHECK('M' == (*pprec)->val);

    pprec = rechercherPrecFilsTries(pere, 'N');
    REQUIRE(NULL != *pprec);
    CHECK('T' == (*pprec)->val);

    pprec = rechercherPrecFilsTries(pere, 'O');
    REQUIRE(NULL != *pprec);
    CHECK('T' == (*pprec)->val);

    pprec = rechercherPrecFilsTries(pere, 'P');
    REQUIRE(NULL != *pprec);
    CHECK('T' == (*pprec)->val);

    pprec = rechercherPrecFilsTries(pere, 'Q');
    REQUIRE(NULL != *pprec);
    CHECK('T' == (*pprec)->val);

    pprec = rechercherPrecFilsTries(pere, 'R');
    REQUIRE(NULL != *pprec);
    CHECK('T' == (*pprec)->val);

    pprec = rechercherPrecFilsTries(pere, 'S');
    REQUIRE(NULL != *pprec);
    CHECK('T' == (*pprec)->val);

    pprec = rechercherPrecFilsTries(pere, 'T');
    REQUIRE(NULL != *pprec);
    CHECK('T' == (*pprec)->val);


    // Recherche pour les lettres de U à Z (doivent tous êtres NULL)
    pprec = rechercherPrecFilsTries(pere, 'U');
    REQUIRE(NULL == *pprec);

    pprec = rechercherPrecFilsTries(pere, 'V');
    REQUIRE(NULL == *pprec);

    pprec = rechercherPrecFilsTries(pere, 'W');
    REQUIRE(NULL == *pprec);

    pprec = rechercherPrecFilsTries(pere, 'X');
    REQUIRE(NULL == *pprec);

    pprec = rechercherPrecFilsTries(pere, 'Y');
    REQUIRE(NULL == *pprec);

    pprec = rechercherPrecFilsTries(pere, 'Z');
    REQUIRE(NULL == *pprec);

    libererArbre(&racine);
}


TEST(insererTrie) {
    int nbRacines = 0;
    int nbEltsPref = 0;
    eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
    cell_lvlh_t *racine = NULL;

    printf("\033[34m\ninsererTrie :\033[0m\n");
    nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
    racine = pref2lvlh(tabEltPref, nbRacines);

        // Insérer une valeur en doublon
        int resultat1 = insererTrie(racine, 'C', 'F');
        CHECK(0 == resultat1);

        // Insérer une nouvelle valeur
        int resultat2 = insererTrie(racine, 'F', 'N');
        CHECK(1 == resultat2);
        cell_lvlh_t* nouv = rechercher_v(racine, 'N');
        REQUIRE(NULL != nouv);
        CHECK('N' == nouv->val);
        cell_lvlh_t* frere_gauche = nouv->lh;
        //printf("nouv->lh->val = %c\n", nouv->lh->val);
        REQUIRE(NULL != frere_gauche);
        CHECK(frere_gauche->val == 'T');
        cell_lvlh_t *fils = nouv->lv;
        CHECK(NULL == fils);

        // Insérer une valeur dans une cellule inexistante
        int resultat3 = insererTrie(racine, 'X', 'Y');
        CHECK(0 == resultat3);

        libererArbre(&racine);
}


END_TEST_GROUP(ARBRE_INSERT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_INSERT);
	return EXIT_SUCCESS;
}
