#ifndef TESTOVANIE_ZADANIE2_H
#define TESTOVANIE_ZADANIE2_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//moj AVL

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
		return 1;
	}

	while (root) {
		if (root->cislo == data) {
			return 1;
		}
		else if (root->cislo > data) root = root->vlavo;
		else if (root->cislo < data) root = root->vpravo;
	}

	return 0;
}



//moj hash
typedef struct hashTableNode {
	int key;	//na ukladanie cisiel normalnych
	int volny;		//ak je size 1, vtedy je index prazdny
	int pocet_obsadenych;
	int velkost_pola;
	struct hashTableNode* next;
	struct hashTableNode* last;
}HASHTABLENODE;

HASHTABLENODE* init(int size, HASHTABLENODE** t);
HASHTABLENODE* zvacsi_pole(HASHTABLENODE** t, int nova_velkost);
int hash(int key, int velkost_pola);
HASHTABLENODE* insert(HASHTABLENODE** t, int cislo, int velkost_pola);
HASHTABLENODE* reinsert(HASHTABLENODE** t, int cislo, int velkost_pola);
int najdi(HASHTABLENODE* t, int cislo, int velkost_pola);


HASHTABLENODE* init(int size, HASHTABLENODE** t) {
	HASHTABLENODE* ht;
	ht = (HASHTABLENODE*)malloc(size * sizeof(HASHTABLENODE));
	ht->pocet_obsadenych = 0;
	ht->velkost_pola = size;
	int i;
	for (i = 0; i < size; i++) {
		(ht + i)->volny = 1;
		(ht + i)->next = NULL;
		(ht + i)->key = NULL;
		(ht + i)->last = (ht + i);
	}

	*t = ht;
	return *t;
}

HASHTABLENODE* zvacsi_pole(HASHTABLENODE** t, int nova_velkost) {
	//HASHTABLENODE* stara = (HASHTABLENODE*)malloc(sizeof(HASHTABLENODE));
	HASHTABLENODE* nova; //(HASHTABLENODE*)malloc(sizeof(HASHTABLENODE));
	int stara_velkost = (*t)->velkost_pola;
	HASHTABLENODE* stara = *t;
	int novy_index, i;
	init(nova_velkost, &nova);

	for (i = 0; i < stara_velkost; i++) {
		if ((stara + i)->key) {
			//HASHTABLENODE* temp = (HASHTABLENODE*)malloc(sizeof(HASHTABLENODE));
			HASHTABLENODE* temp = (stara + i);
			while (temp) {
				reinsert(&nova, temp->key, nova_velkost);
				temp = temp->next;
			}

		}

	}
	free(stara);
	*t = nova;
	return *t;
}

int hash(int key, int velkost_pola) {
	int vysledok;
	vysledok = key  % velkost_pola;
	return vysledok;
}

HASHTABLENODE* reinsert(HASHTABLENODE** t, int cislo, int velkost_pola) {
	int index = hash(cislo, velkost_pola);		//index 30
	//HASHTABLENODE* temp = (HASHTABLENODE*)malloc(sizeof(HASHTABLENODE));
	if ((*t + index)->volny == 1) {
		(*t)->pocet_obsadenych++;
		(*t + index)->volny = 0;
		(*t + index)->key = cislo;
		(*t + index)->next = NULL;
		(*t + index)->last = (*t + index);
	}

	else if ((*t + index)->volny != 1) {
		HASHTABLENODE* temp = (HASHTABLENODE*)malloc(sizeof(HASHTABLENODE));
		HASHTABLENODE* aktualny = (*t + index);

		//HASHTABLENODE* temporary = (HASHTABLENODE*)malloc(sizeof(HASHTABLENODE));
		HASHTABLENODE* temporary = temp;
		while (aktualny) {
			if (aktualny->key == cislo)
			{
				return NULL;
			}

			else if (aktualny->next == NULL)
			{
				aktualny->next = temp;
				break;
			}
			else {
				aktualny = aktualny->next;
			}
		}
		temp->key = cislo;
		temp->volny = 0;
		temp->next = NULL;
	}
	return *t;
}

HASHTABLENODE* insert(HASHTABLENODE** t, int cislo, int velkost_pola) {
	int index = hash(cislo, velkost_pola);		//index 30
	//HASHTABLENODE* temp = (HASHTABLENODE*)malloc(sizeof(HASHTABLENODE));
	if ((*t + index)->volny == 1) {
		(*t)->pocet_obsadenych++;
		(*t + index)->volny = 0;
		(*t + index)->key = cislo;
		(*t + index)->next = NULL;
		(*t + index)->last = (*t + index);
	}

	else if ((*t + index)->volny != 1) {
		HASHTABLENODE* temp = (HASHTABLENODE*)malloc(sizeof(HASHTABLENODE));
		HASHTABLENODE* aktualny = (*t + index);

		//HASHTABLENODE* temporary = (HASHTABLENODE*)malloc(sizeof(HASHTABLENODE));
		HASHTABLENODE* temporary = temp;
		while (aktualny) {
			if (aktualny->key == cislo)
			{
				return NULL;
			}

			else if (aktualny->next == NULL)
			{
				aktualny->next = temp;
				break;
			}
			else {
				aktualny = aktualny->next;
			}
		}
		temp->key = cislo;
		temp->volny = 0;
		temp->next = NULL;
	}

	int percento_obsadenosti = ((*t)->pocet_obsadenych * 100) / (*t)->velkost_pola;	//100/10=10
	if (percento_obsadenosti >= 90) {
		zvacsi_pole(t, 2 * velkost_pola);
	}

	return *t;
}

int najdi_v_ht(HASHTABLENODE* t, int cislo, int velkost_pola) {
	int index = hash(cislo, velkost_pola);

	if ((t + index)->key == cislo) {
		return 1;
	}

	else if ((t + index) == NULL) {
		return 0;
	}

	else if ((t + index)->next != NULL) {
		//HASHTABLENODE* temp = (HASHTABLENODE*)malloc(sizeof(HASHTABLENODE));
		HASHTABLENODE* temp;
		temp = (t + index)->next;
		if (temp == NULL) {
			return 0;
		}

		else {
			while (temp) {
				if ((temp) && temp->key == cislo) {
					return 1;
				}
				temp = temp->next;

			}
		}
	}

	return 0;
}


//prevzaty avl strom
struct node {
	int data;
	struct node* prev; 
	struct node* left;
	struct node* right;
};

struct node* alloc(int x, struct node* p)
{
	struct node* tmp;

	tmp = (struct node*)malloc(sizeof(struct node));
	tmp->data = x;
	tmp->prev = p;
	tmp->left = NULL;
	tmp->right = NULL;

	return tmp;
}

bool is_left(struct node* curr)
{
	if (curr == NULL) {

		return false;
	}

	if (curr->prev == NULL) {

		return false;
	}

	if (curr->prev->left == curr) {

		return true;
	}

	return false;
}

void zag(struct node* curr, struct node** root) // single left rotation
{
	struct node* tmp;

	tmp = NULL;

	if (curr->right != NULL) {
		tmp = curr->right->left;
	}

	if (curr->prev != NULL) {
		if (is_left(curr) == true) {
			curr->prev->left = curr->right;
			curr->prev->left->prev = curr->prev;
			curr->prev = curr->prev->left;
		}
		else {
			curr->prev->right = curr->right;
			curr->prev->right->prev = curr->prev;
			curr->prev = curr->prev->right;
		}
		curr->prev->left = curr;
	}
	else {
		*root = curr->right;
		curr->prev = curr->right;
		curr->prev->left = curr;
		curr->prev->prev = NULL;
	}

	curr->right = tmp;
	if (curr->right != NULL) {
		curr->right->prev = curr;
	}

	return;
}

void zig(struct node* curr, struct node** root) // single right rotation
{
	struct node* tmp;
	struct node* l;

	tmp = NULL;
	l = curr->left;

	if (l != NULL) {
		tmp = l->right;
	}

	l->prev = curr->prev;

	if (curr->prev != NULL) {
		if (is_left(curr) == true) {
			l->prev->left = l;
		}
		else {
			l->prev->right = l;
		}
	}
	else {
		*root = l;
	}

	l->right = curr;
	curr->prev = l;

	curr->left = tmp;
	if (tmp != NULL) {
		tmp->prev = curr;
	}

	return;
}

void zig_zig(struct node* curr, struct node** root)
{
	zig(curr->prev->prev, root);
	zig(curr->prev, root);

	return;
}

void zag_zag(struct node* curr, struct node** root)
{
	zag(curr->prev->prev, root);
	zag(curr->prev, root);

	return;
}

void zig_zag(struct node* curr, struct node** root)
{
	zig(curr->prev, root);
	zag(curr->prev, root);

	return;
}

void zag_zig(struct node* curr, struct node** root)
{
	zag(curr->prev, root);
	zig(curr->prev, root);

	return;
}

void splay(struct node* curr, struct node** root)
{
	while (curr->prev != NULL) { // when curr->prev is NULL, it is root
		if (curr->prev->prev != NULL) {
			if (is_left(curr) == true) {
				if (is_left(curr->prev) == true) {
					zig_zig(curr, root);
				}
				else {
					zig_zag(curr, root);
				}
			}
			else {
				if (is_left(curr->prev) == true) {
					zag_zig(curr, root);
				}
				else {
					zag_zag(curr, root);
				}
			}
		}
		else if (curr->prev != NULL) {
			if (is_left(curr) == true) {
				zig(curr->prev, root);
			}
			else {
				zag(curr->prev, root);
			}
		}
	}

	return;
}

void insert_splay(struct node** root, int x)
{
	if (*root == NULL) {
		*root = alloc(x, NULL);

		return;
	}

	struct node* curr;
	struct node* prev;

	curr = *root;
	prev = NULL;

	while (curr != NULL) {
		prev = curr;
		if (x == curr->data) {

			return;
		}
		if (x < curr->data) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
	}

	if (x < prev->data) {
		prev->left = alloc(x, prev);
		curr = prev->left;
	}
	else {
		prev->right = alloc(x, prev);
		curr = prev->right;
	}

	splay(curr, root);

	return;
}

void inorder_t(struct node* curr)
{
	if (curr == NULL) {
		return;
	}

	inorder_t(curr->left);
	printf("%d ", curr->data);
	inorder_t(curr->right);

	return;
}

void preorder_t(struct node* curr)
{
	if (curr == NULL) {
		return;
	}

	printf("%d ", curr->data);
	preorder_t(curr->left);
	preorder_t(curr->right);

	return;
}

bool find(struct node** root, int x) // finds and splays node(only if found)
{
	struct node* curr;

	curr = *root;

	while (curr != NULL) {
		if (curr->data == x) {
			splay(curr, root);

			return true;
		}
		else if (x < curr->data) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
	}

	return false;
}

struct node* inorder_pred(struct node* curr)
{
	if (curr->left == NULL) {

		return curr->prev;
	}

	struct node* t;

	t = curr->left;

	while (t->right != NULL) {
		t = t->right;
	}

	return t;
}

struct node* inorder_succ(struct node* curr)
{
	if (curr->right == NULL) {
		return NULL;
	}

	struct node* t;

	t = curr->right;

	while (t->left != NULL) {
		t = t->left;
	}

	return t;
}

int delete_root(struct node** root)
{
	int x;
	struct node* r; // replacement node

	if (((*root)->left == NULL) && ((*root)->right == NULL)) {
		x = (*root)->data;
		r = (*root);
		(*root) = NULL;
		free(r);

		return x;
	}

	r = inorder_succ(*root);

	if (r != NULL) {
		if (is_left(r) == true) {
			r->prev->left = NULL;
		}
		else {
			r->prev->right = NULL;
		}
	}
	else {
		r = inorder_pred(*root);
		if (r == (*root)->prev) {
			(*root)->prev = (*root)->right; // since there was no left child
		}
		else {
			if (is_left(r) == true) {
				r->prev->left = NULL;
			}
			else {
				r->prev->right = NULL;
			}
		}
	}

	x = (*root)->data;
	(*root)->data = r->data;

	free(r);

	return x;
}

//prevzaty hash
#define SIZE 1000000

int Search(int element);
int arr[SIZE] = {};
int count;

int CalculateHash(int key)
{
    return key % SIZE;
}

void Insert(int element)
{
    if (count == SIZE) {
        printf("Error.\nTable if FULL\n");
        exit(EXIT_FAILURE);
    }
    int probe = CalculateHash(element);
    while (arr[probe] != NULL && arr[probe] != -1)
    {
        probe = (probe + 1) % SIZE;
    }
    arr[probe] = element;
    count++;
}

void Delete(int element)
{
    if (count == 0) {
        printf("Error.\nTable if EMPTY\n");
        exit(EXIT_FAILURE);
    }
    int loc = Search(element);
    if (loc != -1)
    {
        arr[loc] = -1;
        count--;
    }
}

int Search(int element)
{
    if (count == 0) {
        printf("Error.\nTable if EMPTY\n");
        exit(EXIT_FAILURE);
    }
    int probe = CalculateHash(element);
    while (arr[probe] != 0)
    {
        if (arr[probe] == element)
            return probe;
        probe = (probe + 1) % SIZE;
    }
   // printf("\nElement %d not found.\n", element);
    return -1;
}

void PrintList()
{
    int i;
    for (i = 0; i < SIZE; i++)
        printf("%d%c", arr[i], ' ');
}
#endif