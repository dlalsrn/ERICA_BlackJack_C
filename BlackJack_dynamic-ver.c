#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct deck // 카드의 모양과 값을 저장해줄 구조체 선언 자료형을 Deck이라고 지정
{
	char shape;
	char value;
}Deck;

typedef struct Node // 카드덱을 연결리스트로 구현하기 위해 구조체 선언 후 자료형을 node라고 지정
{
	Deck card;
	struct Node* next;
}node;

void Add_Node(node* head, Deck card) // 카드를 하나씩 이어주는 함수
{
	if (head->card.shape == 0) // 맨 첫번 째
	{
		head->card = card;
		head->next = NULL;
	}
	else // 두 번째 카드 부터
	{
		if (head->next != NULL)
			Add_Node(head->next, card);
		else
		{
			node* temp = (node*)malloc(sizeof(node)); // node만큼 크기를 할당받은 후 카드와 주소값 이어주기
			temp->card = card;
			temp->next = NULL;
			head->next = temp;
		}
	}
}	

void ary_swap(node* a, node* b) // n번째 와 0~n-1 사이의 임의의 수번째 카드를 바꿔주는 함수
{
	Deck temp = a->card;
	a->card = b->card;
	b->card = temp;
}

void ary_shuffle(node* deck) // 52장의 카드 덱을 무작위 섞어주는 함수
{
	int i, j;
	srand((unsigned int)time(NULL)); // 난수 시드 생성
	node * temp1 = deck; // 첫번째 노드부터 마지막 노드까지 차례대로 참조할 포인터
	for (i = 0; i < 52; i++)
	{
		node * temp2 = deck; // 임의의 j번째 노드를 참조할 포인터
		j = rand() % (52); // 0~51 사이의 임의의 수를 뽑아냄
		for (int s = 0; s < j; s++)
			temp2 = temp2->next; // j만큼 주소를 이동하여 j번째 카드의 위치로 이동
		ary_swap(temp1, temp2); // temp1와 temp2 주소 안에 있는 카드를 바꿈
		temp1 = temp1->next; // n번째 카드를 j번째와 스왑했다면 n+1번째 카드로 이동... 반복
	}
}

Deck hit(Deck a[], int n) // 덱에서 카드 한장을 반환해주는 함수
{
	Deck temp;
	temp.shape = a[n].shape; // 메인덱의 n번째 카드의 모양
	temp.value = a[n].value; // 메인덱의 n번째 카드의 숫자
	return temp;
}

int more(void) // hit을 할때 더 hit할건지 물어보는 함수
{
	char ch;
	printf("hit? (y/n) : ");
	scanf(" %c", &ch);
	if (ch == 'y')
		return 1; // y를 입력했으면 1을 반환, 아니면 0 반환
	else
		return 0;
}

void show_cards(node* cards)
{
	for (int i = 1; cards != NULL; cards = cards->next, i++)
		printf("%d  %c %c \n", i, cards->card.shape, cards->card.value); // 카드의 모양과 수 출력
	printf("\n");
}

int score(Deck a[])
{
	int score = 0;
	int ace = 0; // ace는 11 or 1로 계산하므로 내가 뽑은 ace의 개수를 저장하여 나중에 score 계산시 이용
	for (int i = 0; a[i].value != 0; i++)
	{
		if (a[i].value == 'A' || a[i].value == 'J' || a[i].value == 'Q' || a[i].value == 'K' || a[i].value == 'T')
		{
			if (a[i].value == 'A') // 숫자가 A면 일단 11을 증가 후 에이스 1증가
			{
				ace++;
				score += 11;
			}
			else
				score += 10; // A가 아니면 10증가
		}
		else
			score += a[i].value - 48; // 문자 0의 값이 48이므로 a[i].value에 -48을 해줘야함
	}

	for (int i = 0; i < ace; i++) // ace의 개수에 따라 점수를 빼주는 과정
	{
		if (score > 21) // ace가 포함됐을 때 스코어의 값이 21을 초과하면 -10을 해주어 ace를 1로 계산
			score -= 10;
		else
			break; // ace가 있지만 21을 넘지 않을 때는 탈출
	}
	return score;
}

int main(void)
{
	char Shape[] = {'S', 'D', 'H', 'C'};
	char Number[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
	// 숫자 10을 영어 Ten의 T로 지정
	node* deck = (node*)malloc(sizeof(node)); // 카드 덱 동적할당을 위해 선언한 deck 포인터
	deck->card.shape = 0; // 아무것도 안받은 상태로 초기화
	node* Player = (node*)malloc(sizeof(node)); // 플레이어의 덱
	node* Dealer = (node*)malloc(sizeof(node)); // 딜러의 덱
	int Player_score = 0; // 플레이어의 카드 덱 숫자의 합
	int Dealer_score = 0; // 딜러의 카드 덱 숫자의 합
	printf("Welcome to Casino!! \n\n");

	for (int i = 0; i < 4; i++)
	{
		for (int s = 0; s < 13; s++)
		{
			Deck card;
			card.shape = Shape[i];
			card.value = Number[s]; // 각 모양마다 A~K까지 카드를 하나씩 만들어주는 과정
			Add_Node(deck, card); // deck이라는 포인터에 카드를 하나씩 연결시켜주는 함수 호출
		}
	}
	show_cards(deck);
	ary_shuffle(deck); // 순서대로 만들어진 52장의 카드를 무작위로 섞어주는 함수 호출
	show_cards(deck); // 잘 섞였는지 출력 테스트
	/*

	for (int i = 0; i < 2; i++) // 플레이어와 딜러의 덱에 각각 2장씩 분배
	{
		Player[i] = hit(deck, count); // 메인 함수의 deck과 인덱스 번호를 매개변수로 넘겨줌
		count++; // 메인 덱 인덱스 +1
		Dealer[i] = hit(deck, count);
		count++; // 메인 덱 인덱스 +1
	}

	printf("Dealer cards\n"); // 딜러의 첫 카드는 안보여주고 두 번째 카드만 보여줌
	printf("  **** ** \n");
	printf("  %c %c \n\n", Dealer[1].shape, Dealer[1].value);

	printf("Player cards\n");
	show_cards(Player); // 플레이어의 현재 카드 출력

	Player_score = score(Player); // 플레이어 카드의 숫자 합
	Dealer_score = score(Dealer); // 딜러 카드의 숫자 합
	//printf("Player : %d, Dealer : %d \n", Player_score, Dealer_score); // 테스트용 스코어 출력
	
	if (Player_score == 21)
		printf("BlackJakc! Player Win!!\n"); // 처음받은 카드 2장의 합이 21이면 바로 승리
	else
	{
		while(Player_score <21) // 카드의 합이 21이하면 카드를 더 받을지 hit을 출력하며 물어보는 함수 호출
		{
			if (more())
			{
				Player[py_count] = hit(deck, count);
				printf("  %c %c\n", Player[py_count].shape, Player[py_count].value); // 받을 카드 출력
				py_count++; // 플레이어 카드 덱의 인덱스 번호 +1
				count++; // 메인 카드 덱의 인덱스 번호 +1
				Player_score = score(Player); // 플레이어 덱의 스코어 다시 계산
			}
			else
				break; // n을 입력하면 탈출
		}

		if (Player_score > 21) // 합이 21초과면 패배
			printf("\nPlayer Bust! Dealer Win!!\n");
		else
		{
			while (Dealer_score <= 16) // 딜러는 카드의 합이 무조건 16 이상이어함
			{
				Dealer[dl_count] = hit(deck, count);
				dl_count++;
				count++;
				Dealer_score = score(Dealer); // 카드 합 다시 계산
			}

			printf("\nDealer cards\n");
			show_cards(Dealer); // 딜러의 모든 카드 출력

			if (Dealer_score > 21)
				printf("Dealer Bust! Player Win!!\n");
			else if (Dealer_score == Player_score)
				printf("Draw!!\n");
			else if (Player_score > Dealer_score)
				printf("Player Win!!\n");
			else
				printf("Dealer Win!!\n");
		}
	}

	printf("\nPlayer score : %d\n", Player_score);
	printf("Dealer score : %d\n", Dealer_score);
	*/
	return 0;
}
