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


//Version iterative
TEST(rechercher_v_iterative) {
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
    CHECK(racine == NULL);
}


//Version recursive
TEST(rechercher_v_iterative) {
    int nbRacines = 0;
    int nbEltsPref = 0;
    eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
    cell_lvlh_t *racine = NULL;
    cell_lvlh_t *pere = NULL;

    printf("\033[35m\nrechercher_v_recursif :");
    printf("\033[0m\n");

    nbRacines = lirePref_fromFileName_recursive("../pref_exTP.txt", tabEltPref, &nbEltsPref);
    racine = pref2lvlh(tabEltPref, nbRacines);

    pere = rechercher_v_recursive(racine, 'X');   // valeur inexistante
    CHECK( NULL == pere );

    pere = rechercher_v_recursive(racine, 'A');   // valeur a la racine
    REQUIRE( NULL != pere );
    CHECK( 'A' == pere->val );

    // Test avec toutes les valeurs existantes dans l'arborescence
    pere = rechercher_v_recursive(racine, 'B');
    REQUIRE(NULL != pere);
    CHECK('B' == pere->val);

    pere = rechercher_v_recursive(racine, 'C');
    REQUIRE(NULL != pere);
    CHECK('C' == pere->val);

    pere = rechercher_v_recursive(racine, 'D');
    REQUIRE(NULL != pere);
    CHECK('D' == pere->val);

    pere = rechercher_v_recursive(racine, 'E');
    REQUIRE(NULL != pere);
    CHECK('E' == pere->val);

    pere = rechercher_v_recursive(racine, 'F');
    REQUIRE(NULL != pere);
    CHECK('F' == pere->val);

    pere = rechercher_v_recursive(racine, 'G');
    REQUIRE(NULL != pere);
    CHECK('G' == pere->val);

    pere = rechercher_v_recursive(racine, 'H');
    REQUIRE(NULL != pere);
    CHECK('H' == pere->val);

    pere = rechercher_v_recursive(racine, 'I');
    REQUIRE(NULL != pere);
    CHECK('I' == pere->val);

    pere = rechercher_v_recursive(racine, 'J');
    REQUIRE(NULL != pere);
    CHECK('J' == pere->val);

    pere = rechercher_v_recursive(racine, 'K');
    REQUIRE(NULL != pere);
    CHECK('K' == pere->val);

    pere = rechercher_v_recursive(racine, 'M');
    REQUIRE(NULL != pere);
    CHECK('M' == pere->val);

    pere = rechercher_v_recursive(racine, 'T');
    REQUIRE(NULL != pere);
    CHECK('T' == pere->val);

    libererArbre_recursive(&racine);
    CHECK(racine == NULL);
}


//Version iterative
TEST(rechercherPrecFilsTries_iterative)
{
    int nbRacines = 0;
    int nbEltsPref = 0;
    eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
    cell_lvlh_t *racine = NULL;
    cell_lvlh_t *pere = NULL;
    cell_lvlh_t **pprec = NULL;

    printf("\033[34m\nrechercherPrecFilsTries_iterative :\033[0m\n");

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
    CHECK(racine == NULL);
}


//Version recursive
TEST(rechercherPrecFilsTries_recursive)
{
    int nbRacines = 0;
    int nbEltsPref = 0;
    eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
    cell_lvlh_t *racine = NULL;
    cell_lvlh_t *pere = NULL;
    cell_lvlh_t **pprec = NULL;

    printf("\033[34m\nrechercherPrecFilsTries_recursive :\033[0m\n");

    nbRacines = lirePref_fromFileName_recursive("../pref_exTP.txt", tabEltPref, &nbEltsPref);
    racine = pref2lvlh(tabEltPref, nbRacines);

    // Recherche pour les lettres de A à T
    pere = rechercher_v_recursive(racine, 'F');
    REQUIRE(NULL != pere);
    CHECK('F' == pere->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'A');
    REQUIRE(NULL != *pprec);
    CHECK('K' == (*pprec)->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'H');
    REQUIRE(NULL != *pprec);
    CHECK('K' == (*pprec)->val);

    pere = rechercher_v_recursive(racine, 'B');
    REQUIRE(NULL != pere);
    CHECK('B' == pere->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'C');
    REQUIRE(NULL != *pprec);
    CHECK('E' == (*pprec)->val);

    pere = rechercher_v_recursive(racine, 'C');
    REQUIRE(NULL != pere);
    CHECK('C' == pere->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'D');
    REQUIRE(NULL != *pprec);
    CHECK('F' == (*pprec)->val);

    pere = rechercher_v_recursive(racine, 'A');
    REQUIRE(NULL != pere);
    CHECK('A' == pere->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'E');
    REQUIRE(NULL != *pprec);
    CHECK('H' == (*pprec)->val);

    pere = rechercher_v_recursive(racine, 'C');
    REQUIRE(NULL != pere);
    CHECK('C' == pere->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'F');
    REQUIRE(NULL != *pprec);
    CHECK('F' == (*pprec)->val);

    pere = rechercher_v(racine, 'F');
    REQUIRE(NULL != pere);
    CHECK('F' == pere->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'G');
    REQUIRE(NULL != *pprec);
    CHECK('K' == (*pprec)->val);

    pere = rechercher_v_recursive(racine, 'F');
    REQUIRE(NULL != pere);
    CHECK('F' == pere->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'H');
    REQUIRE(NULL != *pprec);
    CHECK('K' == (*pprec)->val);

    pere = rechercher_v_recursive(racine, 'C');
    REQUIRE(NULL != pere);
    CHECK('C' == pere->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'I');
    REQUIRE(NULL != *pprec);
    CHECK('I' == (*pprec)->val);

    pere = rechercher_v_recursive(racine, 'B');
    REQUIRE(NULL != pere);
    CHECK('B' == pere->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'J');
    REQUIRE(NULL != *pprec);
    CHECK('J' == (*pprec)->val);

    pere = rechercher_v_recursive(racine, 'F');
    REQUIRE(NULL != pere);
    CHECK('F' == pere->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'K');
    REQUIRE(NULL != *pprec);
    CHECK('K' == (*pprec)->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'L');
    REQUIRE(NULL != *pprec);
    CHECK('M' == (*pprec)->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'M');
    REQUIRE(NULL != *pprec);
    CHECK('M' == (*pprec)->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'N');
    REQUIRE(NULL != *pprec);
    CHECK('T' == (*pprec)->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'O');
    REQUIRE(NULL != *pprec);
    CHECK('T' == (*pprec)->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'P');
    REQUIRE(NULL != *pprec);
    CHECK('T' == (*pprec)->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'Q');
    REQUIRE(NULL != *pprec);
    CHECK('T' == (*pprec)->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'R');
    REQUIRE(NULL != *pprec);
    CHECK('T' == (*pprec)->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'S');
    REQUIRE(NULL != *pprec);
    CHECK('T' == (*pprec)->val);

    pprec = rechercherPrecFilsTries_recursive(pere, 'T');
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
    CHECK(racine == NULL);
}


TEST(insererTrie)
{
    int nbRacines = 0;
    int nbEltsPref = 0;
    eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
    cell_lvlh_t *racine = NULL;

    printf("\033[34m\ninsererTrie :\033[0m\n");
    nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
    racine = pref2lvlh(tabEltPref, nbRacines);

    // Insérer une nouvelle valeur
    int resultat2 = insererTrie(racine, 'F', 'N');
    CHECK(1 == resultat2);
    cell_lvlh_t* nouv = rechercher_v(racine, 'N');
    REQUIRE(NULL != nouv);
    CHECK('N' == nouv->val);
    cell_lvlh_t* frere = nouv->lh;
    REQUIRE(NULL != frere);
    CHECK(frere->val == 'T');
    cell_lvlh_t *fils = nouv->lv;
    CHECK(NULL == fils);

    // Insérer une valeur dans une cellule inexistante
    int resultat3 = insererTrie(racine, 'X', 'Y');
    CHECK(0 == resultat3);

    //Insérer une nouvelle valeur apres l'ancienne valeur inserée
    int resultat4 = insererTrie(racine, 'F', 'O');
    CHECK(1 == resultat4);
    nouv = rechercher_v(racine, 'O');
    REQUIRE(NULL != nouv);
    CHECK('O' == nouv->val);
    frere = nouv->lh;
    REQUIRE(NULL != frere);
    CHECK(frere->val == 'T');
    fils = nouv->lv;
    CHECK(NULL == fils);

    //Insérer une nouvelle valeur dans la deuxième branche de l'arbre
    int resultat5 = insererTrie(racine, 'C', 'Z');
    CHECK(1 == resultat5);
    nouv = rechercher_v(racine, 'Z');
    REQUIRE(NULL != nouv);
    CHECK('Z' == nouv->val);
    frere = nouv->lh;
    REQUIRE(NULL == frere);
    fils = nouv->lv;
    CHECK(NULL == fils);

    //Insérer une valeur existante mais pas dans la meme cellule de l'arbre
    int resultat6 = insererTrie(racine, 'A', 'J');
    CHECK(1 == resultat6);
    nouv = rechercher_v(racine, 'J');
    REQUIRE(NULL != nouv);
    CHECK('J' == nouv->val);
    frere = nouv->lh;
    REQUIRE(NULL == frere);
    fils = nouv->lv;
    CHECK(NULL == fils);

    //Insérer une valeur en premier fils (plus petit que tous les existants)
    int resultat7 = insererTrie(racine, 'B', 'C');
    CHECK(1 == resultat7);
    nouv = racine->lv->lv;
    REQUIRE(NULL != nouv);
    CHECK('C' == nouv->val);
    frere = nouv->lh;
    REQUIRE(NULL != frere);
    CHECK(frere->val == 'E');
    fils = nouv->lv;
    CHECK(NULL == fils);

    //Insérer une valeur sous une feuille
    int resultat8 = insererTrie(racine, 'E', 'V');
    CHECK(1 == resultat8);
    nouv = racine->lv->lv->lh->lv;
    REQUIRE(NULL != nouv);
    CHECK('V' == nouv->val);
    frere = nouv->lh;
    REQUIRE(NULL == frere);
    fils = nouv->lv;
    CHECK(NULL == fils);

    //Insérer une valeur en doublon
    int resultat9 = insererTrie(racine, 'A', 'B');
    CHECK(1 == resultat9);
    nouv = racine->lv->lh;
    REQUIRE(NULL != nouv);
    CHECK('B' == nouv->val);
    frere = nouv->lh;
    REQUIRE(frere != NULL);
    CHECK('D' == frere->val);
    fils = nouv->lv;
    CHECK(NULL != fils);
    CHECK('C' == fils->val);

    libererArbre(&racine);
    CHECK(racine == NULL);
}


END_TEST_GROUP(ARBRE_INSERT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_INSERT);
	return EXIT_SUCCESS;
}
