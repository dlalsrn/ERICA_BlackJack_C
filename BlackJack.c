#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct deck
{
	char shape;
	char value;
}Deck;

void ary_swap(Deck* a, Deck* b)
{
	char Shape = a->shape;
	char Num = a->value;
	a->shpae = b->shape;
	a->value = b->value;
	b->shpae = Shape;
	b->value = Num;
}

void ary_shuffle(Deck a[], int n)
{
	int i, j;
	srand((unsigned int)time(NULL));
	for (i = n-1; i > n; i--)
	{
		j = rand() % (i+1);
		ary_swap(&a[i], &a[j]);
	}
}

Deck hit(Deck a[], int n)
{
	
}

int more(void)
{
	
}

void show_cards(Deck a[])
{

}

int score(Deck a[])
{

}

int main(void)
{
	return 0;
}
