#include "Header1.h"

void test1() {
    clock_t start, end;
    double time_spent = 0;
    int i;

    //moj strom
    start = clock();
    struct binarny_strom* root = NULL;

    for (i = 1; i < 50000; i++) {
        vloz(i, &root);
    }
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Total cas mojho stromu %f\n", time_spent);


    //moj hash
    start = clock();
    HASHTABLENODE* t = NULL;			//int *a;	a = (int*) malloc (sizeof(int))
    int velkost_pola = 50000;
    init(velkost_pola, &t);

    for (i = 1; i < 50000; i++) {
        insert(&t, i, t->velkost_pola);
    }

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Celkovy cas mojej hash funkcie pri zaciatocnej velkosti pola 50000 je %f\n", time_spent);



    //prevzaty hash
    start = clock();
    for (i = 1; i < 50000; i++) {
        Insert(i);
    }

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Total cas pri prevzatom hasi %f\n", time_spent);

    //prevzaty strom
    start = clock();
    struct node* koren;

    koren = NULL;

    for (i = 1; i < 50000; i++) {
        insert_splay(&koren, i);
    }

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Total cas pri prevzatom strome %f\n", time_spent);
}

void test2() {
    printf("Vkadaju sa vsetky cisla od 1 po 1 000 000\n");
    clock_t start, end;
    double time_spent = 0;
    int i;

    start = clock();
    struct binarny_strom* root = NULL;

    for (i = 1; i < 1000000; i++) {
        vloz(i, &root);
    }

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Total cas %f\n", time_spent);


    start = clock();
    HASHTABLENODE* t = NULL;			//int *a;	a = (int*) malloc (sizeof(int))
    int velkost_pola = 1000000;
    init(velkost_pola, &t);

    for (i = 1; i < 1000000; i++) {
        insert(&t, i, t->velkost_pola);
    }

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Total cas pri mojom hasi %f\n", time_spent);


    start = clock();
    for (i = 1; i < 1000000; i++) {
        Insert(i);
    }

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Total cas pri prevzatom hasi %f\n", time_spent);


    start = clock();
    struct node* koren;

    koren = NULL;

    for (i = 1; i < 1000000; i++) {
        insert_splay(&koren, i);
    }
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Total cas pri prevzatom strome %f\n", time_spent);
}



void test3() {
    printf("Vklada prvky od 1 po 200 000 a potom ich vyhladava, znova od 1 do 200 000\n");
    clock_t start, koniec;
    double celkovy_cas = 0;
    int i;

    start = clock();
    struct binarny_strom* root = NULL;

    for (i = 1; i < 200000; i++) {
        vloz(i, &root);
    }

    //hladanie
    for (i = 1; i < 200000; i++) {
        najdi(i, root);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas mojho stromu %f\n", celkovy_cas);

    HASHTABLENODE* t = NULL;			//int *a;	a = (int*) malloc (sizeof(int))
    int velkost_pola = 200000;
    init(velkost_pola, &t);

    start = clock();
    for (i = 1; i < 200000; i++) {
        insert(&t, i, t->velkost_pola);
    }

    for (i = 1; i < 200000; i++) {
        najdi_v_ht(t, i, t->velkost_pola);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas pri mojom hasi %f\n", celkovy_cas);


    start = clock();
    struct node* koren;

    koren = NULL;

    for (i = 1; i < 200000; i++) {
        insert_splay(&koren, i);
    }


    for (i = 1; i < 200000; i++) {
        find(&koren, i);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas pri prevzatom strome %f\n", celkovy_cas);



    start = clock();
    for (i = 1; i < 200000; i++) {
        Insert(i);
    }

    for (i = 1; i < 200000; i++) {
        Search(i);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas pri prevzatom hasi %f\n", celkovy_cas);
}

void test4() {
    int nahodne, i;
    clock_t start, koniec;
    double celkovy_cas = 0;
   
    start = clock();
    struct binarny_strom* root = NULL;
    for (i = 0; i < 10000; i++) {
        nahodne = rand();
        vloz(nahodne, &root);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas pri mojom strome %f\n", celkovy_cas);

   /* start = clock();
    HASHTABLENODE* t = NULL;			//int *a;	a = (int*) malloc (sizeof(int))
    int velkost_pola = 2000;
    init(velkost_pola, &t);
    
    for (i = 0; i < 10000; i++) {
        nahodne = rand();
        insert(&t, nahodne, t->velkost_pola);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas pri mojom hasi %f\n", celkovy_cas); */

    
 /*  start = clock();
    struct node* koren;

    koren = NULL;

    for (i = 0; i < 10000; i++) {
        nahodne = rand();
        insert_splay(&koren, nahodne);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas pri prevzatom strome %f\n", celkovy_cas);*/

   /* start = clock();
    for (i = 1; i < 10000; i++) {
        nahodne = rand();
        Insert(nahodne);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas pri prevzatom hasi %f\n", celkovy_cas);*/
}



void test5() {
    printf("Vkladam 10 000 nahodnych cisel a potom vyhladavam 3 000 nahodnych cisel\n");
    int nahodne, i;
    clock_t start, koniec;
    double celkovy_cas = 0;

    /*start = clock();
    struct binarny_strom* root = NULL;

    for (i = 0; i < 10000; i++) {
        vloz(i, &root);
    }

    //hladanie
    for (i = 0; i < 3000; i++) {
        najdi(i, root);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas mojho stromu %f\n", celkovy_cas);*/


    start = clock();
    HASHTABLENODE* t = NULL;			//int *a;	a = (int*) malloc (sizeof(int))
    int velkost_pola = 10000;
    init(velkost_pola, &t);

    for (i = 0; i < 10000; i++) {
        nahodne = rand();
        insert(&t, nahodne, t->velkost_pola);
    }

    for (i = 0; i < 3000; i++) {
        nahodne = rand();
        najdi_v_ht(t, nahodne, t->velkost_pola);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas pri mojom hasi %f\n", celkovy_cas);

 /*   start = clock();
    struct node* koren;

    koren = NULL;

    for (i = 0; i < 10000; i++) {
        insert_splay(&koren, i);
    }


    for (i = 0; i < 3000; i++) {
        find(&koren, i);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas pri prevzatom strome %f\n", celkovy_cas);*/

    /*start = clock();
    for (i = 0; i < 10000; i++) {
        Insert(i);
    }

    for (i = 0; i < 3000; i++) {
        Search(i);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas pri prevzatom hasi %f\n", celkovy_cas);*/

}

void test6() {
    printf("Vklada prvky od 1 po 1 000 000 a potom vyhladava cisla od 1 do 200 000\n");
    clock_t start, koniec;
    double celkovy_cas = 0;
    int i;

    
    struct binarny_strom* root = NULL;

    for (i = 1; i < 1000000; i++) {
        vloz(i, &root);
    }

    start = clock();
    //hladanie
    for (i = 1; i < 200000; i++) {
        najdi(i, root);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas mojho stromu %f\n", celkovy_cas);

    HASHTABLENODE* t = NULL;			//int *a;	a = (int*) malloc (sizeof(int))
    int velkost_pola = 200000;
    init(velkost_pola, &t);

    
    for (i = 1; i < 1000000; i++) {
        insert(&t, i, t->velkost_pola);
    }

    start = clock();
    for (i = 1; i < 200000; i++) {
        najdi_v_ht(t, i, t->velkost_pola);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas pri mojom hasi %f\n", celkovy_cas);


    
    struct node* koren;

    koren = NULL;

    for (i = 1; i < 1000000; i++) {
        insert_splay(&koren, i);
    }

    start = clock();
    for (i = 1; i < 200000; i++) {
        find(&koren, i);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas pri prevzatom strome %f\n", celkovy_cas);



    //prevzaty hash
    for (i = 1; i < 1000000; i++) {
        Insert(i);
    }

    start = clock();
    for (i = 1; i < 200000; i++) {
        Search(i);
    }

    koniec = clock();
    celkovy_cas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Total cas pri prevzatom hasi %f\n", celkovy_cas);
}


int main() {
   // test1();
   // test2();
 //  test3();
  // test4();
  // test5();
    test6();
}