#ifndef MOJ_STROM_H
#define MOJ_STROM_H

#include <stdio.h>
#include <stdlib.h>

struct binarny_strom {
    int cislo;
    int vyska;
    struct binarny_strom* vlavo;
    struct binarny_strom* vpravo;
    struct binarny_strom* rodic;
};

void vloz_prvy(int data, binarny_strom** root) {
    struct binarny_strom* uzol = (struct binarny_strom*) malloc(sizeof(struct binarny_strom));
    uzol->vlavo = NULL;
    uzol->vpravo = NULL;
    uzol->cislo = data;
    uzol->vyska = 1;
    uzol->rodic = NULL;
    *root = uzol;
}

struct binarny_strom* vytvor_prvok(int data, binarny_strom* rodic) {
    struct binarny_strom* uzol = (struct binarny_strom*) malloc(sizeof(struct binarny_strom));
    uzol->cislo = data;
    uzol->vpravo = NULL;
    uzol->vlavo = NULL;
    uzol->vyska = 1;
    return uzol;
}

int maximum(int lavy, int pravy) {
    if (lavy >= pravy) return lavy;
    else return pravy;
}

int vrat_vysku(struct binarny_strom* uzol) {
    if (uzol == NULL) return 0;
    else return uzol->vyska;
}

int zisti_balans(struct binarny_strom* uzol) {
    int balans;
    balans = vrat_vysku(uzol->vlavo) - vrat_vysku(uzol->vpravo);
    return balans;
}

struct binarny_strom* rotacia_dolava(struct binarny_strom* root) {
    struct binarny_strom* temp;
    struct binarny_strom* temp2;

    if (root->rodic == NULL) {
        temp = root->vpravo;
        temp2 = temp->vlavo;

        root->vpravo = temp2;
        temp->vlavo = root;
        if (temp2)  temp2->rodic = root;
        temp->rodic = NULL;
        root->rodic = temp;

    }

    else {
        temp = root->vpravo;
        temp2 = root->rodic;
        struct binarny_strom* temp3;
        temp3 = temp->vlavo;
        temp->vlavo = root;

        root->vpravo = temp3;
        if (temp3) temp3->rodic = root;
        root->rodic = temp;
        temp->rodic = temp2;
    }

    int vyska_laveho_potomka = vrat_vysku(root->vlavo);
    int vyska_praveho_potomka = vrat_vysku(root->vpravo);

    root->vyska = 1 + maximum(vyska_laveho_potomka, vyska_praveho_potomka);

    vyska_laveho_potomka = vrat_vysku(temp->vlavo);
    vyska_praveho_potomka = vrat_vysku(temp->vpravo);

    temp->vyska = 1 + maximum(vyska_laveho_potomka, vyska_praveho_potomka);
    return temp;
}

struct binarny_strom* rotacia_doprava(struct binarny_strom* root) {
    struct binarny_strom* temp;
    struct binarny_strom* temp2;

    if (root->rodic == NULL) {
        temp = root->vlavo;
        temp2 = temp->vpravo;

        root->vlavo = temp2;
        temp->vpravo = root;
        if (temp2)  temp2->rodic = root;
        temp->rodic = NULL;
        root->rodic = temp;
    }

    else {
        temp = root->vlavo;
        temp2 = root->rodic;
        struct binarny_strom* temp3;
        temp3 = temp->vpravo;
        temp->vpravo = root;

        root->vlavo = temp3;
        if (temp3) temp3->rodic = root;
        root->rodic = temp;
        temp->rodic = temp2;
    }


    int vyska_laveho_potomka = vrat_vysku(root->vlavo);
    int vyska_praveho_potomka = vrat_vysku(root->vpravo);

    root->vyska = 1 + maximum(vyska_laveho_potomka, vyska_praveho_potomka);

    vyska_laveho_potomka = vrat_vysku(temp->vlavo);
    vyska_praveho_potomka = vrat_vysku(temp->vpravo);

    temp->vyska = 1 + maximum(vyska_laveho_potomka, vyska_praveho_potomka);

    return temp;
}

struct binarny_strom* vloz(int data, struct binarny_strom** root) {
    struct binarny_strom* aktualny;
    struct binarny_strom* rodic;
    struct binarny_strom* novy_prvok = vytvor_prvok(data, NULL);

    aktualny = *root;
    rodic = *root;

    if ((*root) == NULL) {
        vloz_prvy(data, root);
        return *root;
    }

    while (aktualny != NULL) {
        rodic = aktualny;
        if (data > aktualny->cislo)   aktualny = aktualny->vpravo;
        else if (data < aktualny->cislo)   aktualny = aktualny->vlavo;
        else return *root;
    }

    if (novy_prvok->cislo > rodic->cislo) {
        rodic->vpravo = novy_prvok;
        novy_prvok->rodic = rodic;
    }

    else {
        rodic->vlavo = novy_prvok;
        novy_prvok->rodic = rodic;
    }

    aktualny = rodic;
    int vyska_laveho_potomka = 0;
    int vyska_praveho_potomka = 0;

    while (aktualny != NULL) {
        vyska_laveho_potomka = vrat_vysku(aktualny->vlavo);
        vyska_praveho_potomka = vrat_vysku(aktualny->vpravo);
        aktualny->vyska = 1 + maximum(vyska_laveho_potomka, vyska_praveho_potomka);
        int balans = 0;
        balans = zisti_balans(aktualny);

        if (balans < -1 && data > aktualny->vpravo->cislo) {
            aktualny = rotacia_dolava(aktualny);
            if (aktualny->rodic && aktualny->cislo < aktualny->rodic->cislo)   aktualny->rodic->vlavo = aktualny;
            else if (aktualny->rodic) aktualny->rodic->vpravo = aktualny;
        }

        else if (balans < -1 && data < aktualny->vpravo->cislo)
        {
            aktualny->vpravo = rotacia_doprava(aktualny->vpravo);
            aktualny = rotacia_dolava(aktualny);
            if (aktualny->rodic && aktualny->rodic->cislo < aktualny->cislo)   aktualny->rodic->vpravo = aktualny;
            else if (aktualny->rodic)    aktualny->rodic->vlavo = aktualny;
        }

        else if (balans > 1 && data < aktualny->vlavo->cislo) {
            aktualny = rotacia_doprava(aktualny);
            if (aktualny->rodic && aktualny->cislo < aktualny->rodic->cislo)   aktualny->rodic->vlavo = aktualny;
            else if (aktualny->rodic) aktualny->rodic->vpravo = aktualny;
        }

        else if (balans > 1 && data > aktualny->vlavo->cislo) {
            aktualny->vlavo = rotacia_dolava(aktualny->vlavo);
            aktualny = rotacia_doprava(aktualny);
            if (aktualny->rodic && aktualny->rodic->cislo < aktualny->cislo) aktualny->rodic->vpravo = aktualny;
            else if (aktualny->rodic) aktualny->rodic->vlavo = aktualny;
        }

        if (aktualny->rodic == NULL && aktualny != NULL) *root = aktualny;
        aktualny = aktualny->rodic;
    }

    return *root;
}

int najdi(int data, struct binarny_strom* root) {
    if (data == root->cislo) {
        printf("Cislo sa naslo\n");
        return 1;
    }

    while (root) {
        if (root->cislo == data) {
            printf("Cislo sa naslo\n");
            return 1;
        }
        else if (root->cislo > data) root = root->vlavo;
        else if (root->cislo < data) root = root->vpravo;
    }

    printf("Cislo sa nenaslo\n");
    return 0;
}

#endif