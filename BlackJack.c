#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct deck // 카드의 모양과 값을 저장해줄 구조체 선언 자료형을 Deck이라고 지정
{
	char shape;
	char value;
}Deck;

void ary_swap(Deck* a, Deck* b) // n번째 와 0~n-1 사이의 임의의 수번째 카드를 바꿔주는 함수
{
	char Shape = a->shape;
	char Num = a->value;
	a->shpae = b->shape;
	a->value = b->value;
	b->shpae = Shape;
	b->value = Num;
}

void ary_shuffle(Deck a[], int n) // 52장의 카드 덱을 무작위 섞어주는 함수
{
	int i, j;
	srand((unsigned int)time(NULL)); // 난수 시드 생성
	for (i = n-1; i > n; i--)
	{
		j = rand() % (i+1); // 0~n-1 사이의 임의의 수를 뽑아냄
		ary_swap(&a[i], &a[j]); // swap 함수에 i, j번째 카드를 주어 서로 바꿔줌
	}
}

Deck hit(Deck a[], int n) // 덱에서 카드 한장을 반환해주는 함수
{
	Deck temp;
	temp.shape = a[n].shpae; // 메인덱의 n번째 카드의 모양
	temp.value = a[n].value; // 메인덱의 n번째 카드의 숫자
	return temp;
}

int more(void) // hit을 할때 더 hit할건지 물어보는 함수
{
	char ch;
	printf("hit? (y/n) : ");
	scanf(" %c", &ch);
	(ch == 'y') ? return 1 : return 0; // y를 입력했으면 1을 반환, 아니면 0 반환
}

void show_cards(Deck a[])
{
	
}

int score(Deck a[])
{
	
}

int main(void)
{
	char Shape[] = {'S', 'D', 'H', 'C'};
	char Number[] = {'A', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
	// 숫자 10을 영어 Ten의 T로 지정
	Deck deck[52]; // 카드 52장을 넣을 덱 배열 선언;
	Deck Player[10] = {0}; // 10장의 카드 덱을 선언함과 동시에 모두 0으로 초기화
	                       // 현재는 10개의 배열을 고정으로 선언 (나중에 동적 할당으로 변환할 것)
	Deck Dealer[10] = {0}; // 딜러의 카드 덱도 동일 (후에 동적 할당으로 변환)
	int Player_score = 0; // 플레이어의 카드 덱 숫자의 합
	int Dealer_score = 0; // 딜러의 카드 덱 숫자의 합
	return 0;
}
