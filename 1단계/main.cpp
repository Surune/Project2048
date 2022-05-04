/*
대구과학고등학교 1109 서진규
2학기 2048 프로젝트 1단계
*/
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h> 
#include <time.h>
#define COL GetStdHandle(STD_OUTPUT_HANDLE)				//글씨 색상  변경
#define BLACK SetConsoleTextAttribute(COL, 0x0000);  	//검정
#define GREEN SetConsoleTextAttribute(COL, 0x0002);  	//초록색
#define GOLD SetConsoleTextAttribute(COL, 0x0006);  	//금색
#define ORIGINAL SetConsoleTextAttribute(COL, 0x0007); 	//흰색
#define HIGH_GREEN SetConsoleTextAttribute(COL, 0x000a);//연두색
#define SKY_BLUE SetConsoleTextAttribute(COL, 0x000b); 	//하늘색
#define RED SetConsoleTextAttribute(COL, 0x000c);  		//빨간색
#define YELLOW SetConsoleTextAttribute(COL, 0x000e);  	//노란색
#define SIZE 6									// 숫자판의 크기 설정

int field[SIZE][SIZE];							// 숫자판
int n = 10;
char dir;										// 방향
void print_loading();
void print_head();
void print_field();
int check();
void clear();
void make_random();
void repeat();

int main()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			field[i][j] = 0;
	}
	print_loading();
	print_head();
	make_random();									// 랜덤한 위치에 숫자 생성
	make_random();
	print_field();									// 현재 숫자판 상황 출력
	scanf("%c", &dir); 
	repeat();										// 게임 진행
	if((dir == 'N')||(dir == 'n'))	main();
	printf("\n");
	if((dir == 'X')||(dir == 'x')) return 0;
	system("pause");
}

void print_loading()
{
	system("cls");
	ORIGINAL printf("\n\n\n\n\n\n          L O A D I N G . . .\n         ");
	for (int j = 10-n; j>0; j--)	printf("■");
	for(int i = 0; i<n; i++)		printf("□");
	n--;
	Sleep(700);
	if (n < 0)	return;
	else		print_loading();
}

void print_head()									// 기본적으로 출력할 것들
{
	system("cls");
	printf("  ┌───────────────┐\n  │");
	SKY_BLUE printf(" ■■■ ■■■ ■  ■ ■■■");
	ORIGINAL printf(" G│\n  │");
	SKY_BLUE printf("     ■ ■  ■ ■  ■ ■  ■");
	ORIGINAL printf(" A│\n  │");
	SKY_BLUE printf(" ■■■ ■  ■ ■■■ ■■■");
	ORIGINAL printf(" M│\n  │");
	SKY_BLUE printf(" ■     ■  ■     ■ ■  ■");
	ORIGINAL printf(" E│\n  │");
	SKY_BLUE printf(" ■■■ ■■■     ■ ■■■");
	ORIGINAL printf(" !│\n");
	printf("  └───────────────┘\n");
	YELLOW printf(" [제작 : 대구과학고등학교 1109 서진규]\n");
	ORIGINAL printf("─────────★─────────\n");
	printf("       원하는 키를 입력해주세요     \n");
	printf(" [ 위(W), 아래(S), 왼쪽(A), 오른쪽(D) ]\n");
	printf(" [      새 게임(N), 게임 종료(X)      ]\n");
	printf("───────────────────\n");	
}

void print_field()								// 숫자판을 출력하는 함수
{
	printf("\n");
	for (int i = 1; i<5; i++)
	{
		if (i == 1)
			printf("  ┏━━━┳━━━┳━━━┳━━━┓\n");
		else
			printf("  ┣━━━╋━━━╋━━━╋━━━┫\n");

		for (int j = 1; j<5; j++)
		{
			if (field[i][j] == 0)
				printf("  ┃    ");
			else
				printf("  ┃%4d", field[i][j]);
			if (j == 4)
				printf("  ┃");
		}
		printf("\n");

		if (i == 4)
			printf("  ┗━━━┻━━━┻━━━┻━━━┛\n");
	}
	printf("\n");
}

void move_up()									// 위로 미는 함수
{	
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// 빈칸이 있으면
			{
				field[i][j] = field[i + 1][j];	// 아랫칸의 값을 빈칸에 넣고
				field[i + 1][j] = 0;			// 아랫칸을 비운다
			}

			if (field[i][j] == field[i + 1][j])	// 상하로 값이 같으면
			{
				field[i][j] += field[i + 1][j];	// 윗칸에 아랫칸의 값을 더하고
				field[i + 1][j] = 0;			// 아랫칸을 비운다
			}
		}
	}
}

void move_down()								// 아래로 미는 함수
{	
	for (int i = SIZE - 2; i > 0; i--)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// 빈칸이 있으면
			{
				field[i][j] = field[i - 1][j];	// 윗칸의 값을 빈칸에 넣고
				field[i - 1][j] = 0;				// 윗칸을 비운다
			}

			if (field[i][j] == field[i - 1][j])	// 상하로 값이 같으면
			{
				field[i][j] += field[i - 1][j];	// 아랫칸에 윗칸의 값을 더하고
				field[i - 1][j] = 0;				// 윗칸을 비운다
			}
		}
	}
}

void move_right()								// 오른쪽으로 미는 함수
{	
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = SIZE - 2; j > 0; j--)
		{
			if (field[i][j] == 0)				// 빈칸이 있으면
			{
				field[i][j] = field[i][j - 1];	// 왼쪽칸의 값을 빈칸에 넣고
				field[i][j - 1] = 0;				// 왼쪽칸을 비운다
			}
			
			if (field[i][j] == field[i][j - 1])	// 좌우로 값이 같으면
			{
				field[i][j] += field[i][j - 1];	// 오른쪽칸에 왼쪽칸의 값을 더하고
				field[i][j - 1] = 0;				// 왼쪽칸을 비운다
			}
		}
	}
}

void move_left()								// 왼쪽으로 미는 함수
{	
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// 빈칸이 있으면
			{
				field[i][j] = field[i][j + 1];	// 오른쪽칸의 값을 빈칸에 넣고
				field[i][j + 1] = 0;			// 오른쪽칸을 비운다
			}

			if (field[i][j] == field[i][j + 1])	// 좌우로 값이 같으면
			{
				field[i][j] += field[i][j + 1];	// 왼쪽칸에 오른쪽칸의 값을 더하고
				field[i][j + 1] = 0;			// 오른쪽칸을 비운다
			}
		}
	}
}

int check()										// 종료조건을 확인하는 함수 
{
	int end = 0;
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			if (field[i][j] == 0)
				end = 1;						// 빈 칸이 있으면 1 반환

			if (field[i][j] == field[i + 1][j])
				end = 1;						// 위아래로 같은 값이 있으면 1 반환

			if (field[i][j] == field[i][j + 1])
				end = 1;						// 좌우로 같은 값이 있으면 1 반환

			if (field[i][j] == 2048)
				end = 2;						// 2048이 만들어지면 2 반환
		}
	}
	return end;
}

void clear()									// 모서리를 초기화 시키는 함수 
{
	for (int i = 0; i < SIZE; i++)
	{
		field[i][0] = 0;						// 각 모서리 초기화 (쓰레기값 방지)
		field[i][SIZE-1] = 0;					// 각 모서리 초기화 (쓰레기값 방지)
	}

	for (int j = 0; j < SIZE; j++)
	{
		field[0][j] = 0;						// 각 모서리 초기화 (쓰레기값 방지)
		field[SIZE-1][j] = 0;					// 각 모서리 초기화 (쓰레기값 방지)
	}
}

void make_random()						// 랜덤으로 숫자를 만들어주는 함수이다. 
{
	int i, j;							//for문 돌릴 변수 선언 
	int n=0;							//n은 게임판 내의 0의 개수를 확인하기 위해 만든 함수이다. 
	srand((unsigned)time(NULL));		//난수 생성을 위한 코드 
	for(i=1; i<SIZE-1; i++)
	{
		for(j=1; j<SIZE-1; j++)
		{
			if(field[i][j]==0) n++;		//게임판의 0의 개수를 확인한다. 
		}
	}
	
	for(i=1; i<SIZE-1; i++)
	{
		for(j=1; j<SIZE-1; j++)
		{
			if(field[i][j]==0)			// 0의 위치에만 새로운 숫자를 넣어야 한다. 
			{
				if(rand()%n ==0)		// 1/n의 확률로 이 위치에 새로운 숫자가 들어간다. 
				{
					if(rand()%5 == 4) field[i][j]=4;	// 20%의 확률로 4가 들어간다. 
					else field[i][j]=2;					// 80%의 확률로 2가 들어간다.
					return;				// 숫자를 하나 새로 넣었으면 난수생성을 종료시킨다. 
				}
				--n;					// 모든 칸에 숫자가 새로 생길 확률이 같게 해주기 위해 1을 빼준다.
			}
		}
	}
}

void repeat()
{
	clear();
	
	if (check() == 2)				// 2048이 만들어졌다면
	{
		print_head();
		GREEN printf("\n\n\n\n\n\n	    You Win! 'O'\n\n\n\n\n");
		return;									// 게임 종료
	}
	if (check() == 0)				// 움직일 수 없다면
	{
		print_head();
		RED	printf("\n\n\n\n\n\n	    Game Over T_T\n\n\n\n\n");
		return;									// 게임 종료 
	}

	switch (dir)								// 어느 방향으로 밀것인지 입력받기
	{
	case 'A':
	case 'a':
		print_head();
		printf("                  ←");					// 왼쪽 입력받음
		break;
	case 'D':
	case 'd':
		print_head();
		printf("                  →");					// 오른쪽 입력받음
		break;
	case 'W':
	case 'w':
		print_head();
		printf("                  ↑");					// 위쪽 입력받음
		break;
	case 'S':
	case 's':
		print_head();
		printf("                  ↓");					// 아래쪽 입력받음
		break;
	}

	if ((dir == 'W')||(dir=='w'))								// end가 1이면 움직일 수 있고, ↑가 입력되는 경우 위로 민다 
	{
		move_up();
		move_up();
		move_up();
		make_random();							// 랜덤한 위치에 2 혹은 4 생성
		print_field();	                        // 계산된 값 출력
	}

	if ((dir == 'S')||(dir=='s'))							// end가 1이면 움직일 수 있고, ↓가 입력되는 경우 위로 민다 
	{
		move_down();
		move_down();
		move_down();
		make_random();							// 랜덤한 위치에 2 혹은 4 생성
		print_field();       					// 계산된 값 출력
	}

	if ((dir == 'D')||(dir =='d'))						// end가 1이면 움직일 수 있고, →가 입력되는 경우 위로 민다 
	{
		move_right();
		move_right();
		move_right();
		make_random();							// 랜덤한 위치에 2 혹은 4 생성
		print_field();       					// 계산된 값 출력.
	}

	if ((dir == 'A')||(dir == 'a'))							// end가 1이면 움직일 수 있고, ←가 입력되는 경우 위로 민다 
	{
		move_left();
		move_left();
		move_left();
		make_random();							// 랜덤한 위치에 2 혹은 4 생성
		print_field();        					// 계산된 값 출력. 
	}
}