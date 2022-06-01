#ifndef MOJ_HASH_H
#define MOJ_HASH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct hashTableNode {
	int key;
	int volny;
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

	HASHTABLENODE* nova; //(HASHTABLENODE*)malloc(sizeof(HASHTABLENODE));
	int stara_velkost = (*t)->velkost_pola;
	HASHTABLENODE* stara = *t;
	int novy_index, i;
	init(nova_velkost, &nova);

	for (i = 0; i < stara_velkost; i++) {
		if ((stara + i)->key) {
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
	vysledok = key % velkost_pola;
	return vysledok;
}

HASHTABLENODE* reinsert(HASHTABLENODE** t, int cislo, int velkost_pola) {
	int index = hash(cislo, velkost_pola);

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

#endif