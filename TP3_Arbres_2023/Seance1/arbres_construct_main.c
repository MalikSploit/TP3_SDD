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
    //CHECK ( NULL != file);

    printf("\033[35m\npref2lvlh1_exTP :");
    printf("\033[0m\n");

    nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
    REQUIRE(nbRacines == 2);
    racine = pref2lvlh(tabEltPref, nbRacines);
    REQUIRE( NULL != racine );

    // Comparaison avec le contenu du fichier pref_exTP.txt
    CHECK('A' == racine->val);
    CHECK('C' == racine->lh->val);
    CHECK(racine->lh->lh == NULL);
    CHECK('B' == racine->lv->val);
    CHECK('D' == racine->lv->lh->val);
    CHECK(racine->lv->lh->lv == NULL);
    CHECK('H' == racine->lv->lh->lh->val);
    CHECK(racine->lv->lh->lh->lh == NULL);
    CHECK('F' == racine->lh->lv->val);
    CHECK('I' == racine->lh->lv->lh->val);
    CHECK(racine->lh->lv->lh->lh == NULL);
    CHECK(racine->lh->lv->lh->lv == NULL);
    CHECK('E' == racine->lv->lv->val);
    CHECK(racine->lv->lv->lv == NULL);
    CHECK('J' == racine->lv->lv->lh->val);
    CHECK(racine->lv->lv->lh->lh == NULL);
    CHECK(racine->lv->lv->lh->lv == NULL);
    CHECK('G' == racine->lv->lh->lh->lv->val);
    CHECK(racine->lv->lh->lh->lv->lv == NULL);
    CHECK(racine->lv->lh->lh->lv->lh == NULL);
    CHECK('K' == racine->lh->lv->lv->val);
    CHECK(racine->lh->lv->lv->lv == NULL);
    CHECK('M' == racine->lh->lv->lv->lh->val);
    CHECK('T' == racine->lh->lv->lv->lh->lh->val);
    CHECK(racine->lh->lv->lv->lh->lh->lv == NULL);
    CHECK(racine->lh->lv->lv->lh->lh->lh == NULL);

    libererArbre(&racine);
    REQUIRE(racine == NULL);


    //Test avec un fichier vide :
    int nbRacines2 = 0;
    int nbEltsPref2 = 0;
    eltPrefPostFixee_t tabEltPref2[NB_ELTPREF_MAX];
    printf("\033[35m\npref2lvlhFichier_Vide :");
    printf("\033[0m\n");

    nbRacines2 = lirePref_fromFileName("../Fichier_Vide.txt", tabEltPref2, &nbEltsPref2);
    REQUIRE(nbRacines2 == 0);
    racine = pref2lvlh(tabEltPref2, nbRacines2);
    REQUIRE( NULL == racine );


    //Test avec un arbre representé qu'avec des liens horizentaux
    int nbRacines3 = 0;
    int nbEltsPref3 = 0;
    eltPrefPostFixee_t tabEltPref3[NB_ELTPREF_MAX];
    printf("\033[35m\npref2lvlhFichier_avec_lh :");
    printf("\033[0m\n");

    nbRacines3 = lirePref_fromFileName("../Fichier_avec_lh.txt", tabEltPref3, &nbEltsPref3);
    REQUIRE(nbRacines3 == 10);
    racine = pref2lvlh(tabEltPref3, nbRacines3);
    REQUIRE(racine != NULL);

    // Comparaison avec le contenu du fichier pref2lvlhFichier_avec_lh.txt
    CHECK('A' == racine->val);
    CHECK(racine->lv == NULL);
    CHECK('B' == racine->lh->val);
    CHECK(racine->lh->lv == NULL);
    CHECK('C' == racine->lh->lh->val);
    CHECK(racine->lh->lh->lv == NULL);
    CHECK('D' == racine->lh->lh->lh->val);
    CHECK(racine->lh->lh->lh->lv == NULL);
    CHECK('E' == racine->lh->lh->lh->lh->val);
    CHECK(racine->lh->lh->lh->lh->lv == NULL);
    CHECK('F' == racine->lh->lh->lh->lh->lh->val);
    CHECK(racine->lh->lh->lh->lh->lh->lv == NULL);
    CHECK('G' == racine->lh->lh->lh->lh->lh->lh->val);
    CHECK(racine->lh->lh->lh->lh->lh->lh->lv == NULL);
    CHECK('H' == racine->lh->lh->lh->lh->lh->lh->lh->val);
    CHECK(racine->lh->lh->lh->lh->lh->lh->lh->lv == NULL);
    CHECK('I' == racine->lh->lh->lh->lh->lh->lh->lh->lh->val);
    CHECK(racine->lh->lh->lh->lh->lh->lh->lh->lh->lv == NULL);
    CHECK('J' == racine->lh->lh->lh->lh->lh->lh->lh->lh->lh->val);
    CHECK(racine->lh->lh->lh->lh->lh->lh->lh->lh->lh->lv == NULL);
    CHECK(racine->lh->lh->lh->lh->lh->lh->lh->lh->lh->lh == NULL);

    libererArbre(&racine);
    REQUIRE(racine == NULL);


    //Test avec un arbre representé qu'avec des liens verticaux
    int nbRacines4 = 0;
    int nbEltsPref4 = 0;
    eltPrefPostFixee_t tabEltPref4[NB_ELTPREF_MAX];
    printf("\033[35m\npref2lvlhFichier_avec_lv :");
    printf("\033[0m\n");

    nbRacines4 = lirePref_fromFileName("../Fichier_avec_lv.txt", tabEltPref4, &nbEltsPref4);
    REQUIRE(nbRacines4 == 1);
    racine = pref2lvlh(tabEltPref4, nbRacines4);
    REQUIRE(racine != NULL);

    // Comparaison avec le contenu du fichier Fichier_avec_lv.txt
    CHECK('A' == racine->val);
    CHECK(racine->lh == NULL);
    CHECK('B' == racine->lv->val);
    CHECK(racine->lv->lh == NULL);
    CHECK('C' == racine->lv->lv->val);
    CHECK(racine->lv->lv->lh == NULL);
    CHECK('D' == racine->lv->lv->lv->val);
    CHECK(racine->lv->lv->lv->lh == NULL);
    CHECK('E' == racine->lv->lv->lv->lv->val);
    CHECK(racine->lv->lv->lv->lv->lh == NULL);
    CHECK('F' == racine->lv->lv->lv->lv->lv->val);
    CHECK(racine->lv->lv->lv->lv->lv->lh == NULL);
    CHECK('G' == racine->lv->lv->lv->lv->lv->lv->val);
    CHECK(racine->lv->lv->lv->lv->lv->lv->lh == NULL);
    CHECK('H' == racine->lv->lv->lv->lv->lv->lv->lv->val);
    CHECK(racine->lv->lv->lv->lv->lv->lv->lv->lh == NULL);
    CHECK('I' == racine->lv->lv->lv->lv->lv->lv->lv->lv->val);
    CHECK(racine->lv->lv->lv->lv->lv->lv->lv->lv->lh == NULL);
    CHECK('J' == racine->lv->lv->lv->lv->lv->lv->lv->lv->lv->val);
    CHECK(racine->lv->lv->lv->lv->lv->lv->lv->lv->lv->lh == NULL);
    CHECK(racine->lv->lv->lv->lv->lv->lv->lv->lv->lv->lv == NULL);

    libererArbre(&racine);
    REQUIRE(racine == NULL);
}


END_TEST_GROUP(ARBRE_CONSTRUCT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_CONSTRUCT);
	return EXIT_SUCCESS;
}
