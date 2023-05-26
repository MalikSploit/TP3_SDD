/**
 * program for general linked list testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_construct.h"
#include "../../teZZt.h"


BEGIN_TEST_GROUP(ARBRE_CONSTRUCT)

TEST(nouvCell) {
	cell_lvlh_t *new;

	new = allocPoint('A');
	REQUIRE( NULL != new ); 
	CHECK( 'A' == new->val );
	CHECK( NULL == new->lv );
	CHECK( NULL == new->lh );

	free(new);
}


TEST(lirePref_fromFileName_exTP) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
    printf("nbRacines = %d\n", nbRacines);
    printf("nbEltsPref = %d\n", nbEltsPref);

	printf("\033[34m\nlirePref_fromFileName_exTP :");
	printf("\033[0m\n");

	CHECK( 2 == nbRacines ); 
	CHECK( 13 == nbEltsPref );
	CHECK( 'A' == tabEltPref[0].val );
	CHECK( 3 == tabEltPref[0].nbFils );

	CHECK( 'B' == tabEltPref[1].val );
	CHECK( 2 == tabEltPref[1].nbFils );

	CHECK( 'C' == tabEltPref[7].val );
	CHECK( 2 == tabEltPref[7].nbFils );
	
	CHECK( 'I' == tabEltPref[nbEltsPref-1].val );
	CHECK( 0 == tabEltPref[nbEltsPref-1].nbFils );
}


TEST(printTabEltPref_exTP) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[34m\nprintPref_exTP :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	fprintf(file, "%d ", nbRacines);
	printTabEltPref(file, tabEltPref, nbEltsPref);
	fclose(file);
    printf("buffer = %s", buffer);
	CHECK( 0 == strcmp(buffer, "2 (A,3) (B,2) (E,0) (J,0) (D,0) (H,1) (G,0) (C,2) (F,3) (K,0) (M,0) (T,0) (I,0)\n") );
}

// 2  (A,3)  (B,2)  (E,0)  (J,0)  (D,0)  (H,1) (G,0)  (C,2)  (F,3)  (K,0)  (M,0)  (T,0)  (I,0)


TEST(pref2lvlh1_exTP) {
    //Test avec un fichier qui existe
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;

    //Inutile
	//char buffer[1024];
	//FILE * file = fmemopen(buffer, 1024, "w");
	//REQUIRE ( NULL != file);

	printf("\033[35m\npref2lvlh1_exTP :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
    racine = pref2lvlh(tabEltPref, nbRacines);
    REQUIRE( NULL != racine );
    REQUIRE(nbRacines == 2);

    // Test des valeurs des nœuds
    // Comparaison avec le contenu du fichier pref_exTP.txt
    REQUIRE('A' == racine->val);
    REQUIRE('C' == racine->lh->val);
    REQUIRE('B' == racine->lv->val);
    REQUIRE('D' == racine->lv->lh->val);
    REQUIRE('H' == racine->lv->lh->lh->val);
    REQUIRE('F' == racine->lh->lv->val);
    REQUIRE('I' == racine->lh->lv->lh->val);
    REQUIRE('E' == racine->lv->lv->val);
    REQUIRE('J' == racine->lv->lv->lh->val);
    REQUIRE('G' == racine->lv->lh->lh->lv->val);
    REQUIRE('K' == racine->lh->lv->lv->val);
    REQUIRE('M' == racine->lh->lv->lv->lh->val);
    REQUIRE('T' == racine->lh->lv->lv->lh->lh->val);

    libererArbre(&racine);
    REQUIRE(racine == NULL);


    //Test avec un fichier vide :
    int nbRacines2 = 0;
    int nbEltsPref2 = 0;
    eltPrefPostFixee_t tabEltPref2[NB_ELTPREF_MAX];
    cell_lvlh_t *racine2 = NULL;
    printf("\033[35m\npref2lvlhFichier_Vide :");
    printf("\033[0m\n");

    nbRacines = lirePref_fromFileName("../Fichier_Vide.txt", tabEltPref2, &nbEltsPref2);
    racine = pref2lvlh(tabEltPref2, nbRacines2);
    REQUIRE( NULL == racine2 );
    REQUIRE(racine2->lv == NULL);
    REQUIRE(racine2->lh == NULL);
    REQUIRE(nbRacines2 == 0);
}


END_TEST_GROUP(ARBRE_CONSTRUCT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_CONSTRUCT);
	return EXIT_SUCCESS;
}
