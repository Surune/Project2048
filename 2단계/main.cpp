/*
대구과학고등학교 1109 서진규
2학기 2048 프로젝트 2단계
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h> 
#include <time.h>
#define COL GetStdHandle(STD_OUTPUT_HANDLE)				//글씨 색상  변경
#define BLACK SetConsoleTextAttribute(COL, 0x0000);  	//검정
#define GREEN SetConsoleTextAttribute(COL, 0x0002);  	//초록색
#define PURPLE SetConsoleTextAttribute(COL, 0x0005);  	//보라색 
#define GOLD SetConsoleTextAttribute(COL, 0x0006);  	//금색
#define HIGH_GREEN SetConsoleTextAttribute(COL, 0x000a);//연두색
#define SKY_BLUE SetConsoleTextAttribute(COL, 0x000b); 	//하늘색
#define RED SetConsoleTextAttribute(COL, 0x000c);  		//빨간색
#define YELLOW SetConsoleTextAttribute(COL, 0x000e);  	//노란색
#define MAGENTA SetConsoleTextAttribute(COL, 0x000d);	//자주색 
#define ORIGINAL SetConsoleTextAttribute(COL, 0x000f); 	//흰색
#define SIZE 6											// 숫자판의 크기 설정
#define UP 72											// 방향키 위쪽의 아스키코드값
#define DOWN 80 										// 방향키 아래쪽의 아스키코드값
#define ENTER 13                                		// 엔터키의 아스키코드값 

int field[SIZE][SIZE];									// 숫자판
int temp[5]={0,0,0,0,2};                    			// 플레이어 ID(3자리)+점수+단계 
int num[5][5];											// 기록 저장 
char dir;												// 방향

void new_game();
void scan_ID_1(int);
void scan_ID_2(int);
void scan_ID_3(int);
void print_loading(int);
void print_head();
void print_field();
int check();
void clear();
void make_random();
void repeat();
void ending();

int main()
{
	new_game();
	scan_ID_1(65); 
	scan_ID_2(65);
	scan_ID_3(65);
	print_loading(10);
	print_head();
	make_random();									// 랜덤한 위치에 숫자 생성
	make_random();									// 랜덤한 위치에 숫자 생성 
	printf("\n");
	print_field();									// 현재 숫자판 상황 출력
	repeat();										// 게임 진행
	printf("         NEW GAME : Press N");
	int re=getch();
	if((re==78)||(re==110))	main();	
	system("pause");
}

void new_game()										// 변수 초기화 
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			field[i][j] = 0;
	}

	temp[4]=0;										// 점수 초기화 
	temp[5]=2;                    					// 단계 초기화 
}

void scan_ID_1(int name)							// ID 입력받는 함수 1 
{
    int key=0;
	system("cls");
	HIGH_GREEN printf("\n\n\n\n  ┏━━━━━━━━━━━━━━━┓\n");
	printf("  ┃     [ USE ↑, ↓, ENTER ]    ┃\n");
	printf("  ┃        What's Your ID?       ┃\n");
	printf("  ┃                              ┃\n  ┃");
	GREEN printf("            ↑                ");
	HIGH_GREEN printf("┃\n  ┃             ");
	if(name==64)   name=90;
	if(name==91)   name=65;
    GREEN printf("%c A A", name);
	HIGH_GREEN printf("            ┃\n  ┃");
    GREEN printf("            ↓                ");
	HIGH_GREEN printf("┃\n  ┗━━━━━━━━━━━━━━━┛");
    key=getch();
    if(key==ENTER)
    {
    	temp[0]=name;
        return;
	}
    else
    {
		key=getch();
		 
    	switch(key)
    	{
        	case DOWN: 
            	scan_ID_1(name+1);      break;
        	case UP: 
            	scan_ID_1(name-1);      break;
        	default:
            	scan_ID_1(name);
    	}
	}
	return;
}

void scan_ID_2(int name)							// ID 입력받는 함수 2
{
    int key=0;
	system("cls");
	HIGH_GREEN printf("\n\n\n\n  ┏━━━━━━━━━━━━━━━┓\n");
	printf("  ┃     [ USE ↑, ↓, ENTER ]    ┃\n");
	printf("  ┃        What's Your ID?       ┃\n");
	printf("  ┃                              ┃\n  ┃");
	GREEN printf("              ↑              ");
	HIGH_GREEN printf("┃\n  ┃             ");
	if(name==64)   name=90;
	if(name==91)   name=65;
    GREEN printf("%c %c A", temp[0], name);
    HIGH_GREEN printf("            ┃\n  ┃");
    GREEN printf("              ↓              ");
	HIGH_GREEN printf("┃\n  ┗━━━━━━━━━━━━━━━┛");
    key=getch();
    if(key==ENTER)
    {
    	temp[1]=name;
        return;
	}
    else
    {
		key=getch(); 
		
    	switch(key)
    	{
        	case DOWN: 
            	scan_ID_2(name+1);      break;
        	case UP: 
            	scan_ID_2(name-1);      break;
        	default:
            	scan_ID_2(name);
    	}
	}
	return;
}

void scan_ID_3(int name)							// ID 입력받는 함수 3
{
    int key=0;
	system("cls");
	HIGH_GREEN printf("\n\n\n\n  ┏━━━━━━━━━━━━━━━┓\n");
	printf("  ┃     [ USE ↑, ↓, ENTER ]    ┃\n");
	printf("  ┃        What's Your ID?       ┃\n");
	printf("  ┃                              ┃\n  ┃");
	GREEN printf("                ↑            ");
	HIGH_GREEN printf("┃\n  ┃             ");
	if(name==64)   name=90;
	if(name==91)   name=65;
    GREEN printf("%c %c %c", temp[0], temp[1], name);
    HIGH_GREEN printf("            ┃\n  ┃");
    GREEN printf("                ↓            ");
	HIGH_GREEN printf("┃\n  ┗━━━━━━━━━━━━━━━┛");
    key=getch();
    if(key==ENTER)
    {
    	temp[2]=name;
        return;
	}
    else
    {
		key=getch(); 
		
    	switch(key)
    	{
        	case DOWN: 
            	scan_ID_3(name+1);      break;
        	case UP: 
            	scan_ID_3(name-1);      break;
        	default:
            	scan_ID_3(name);
    	}
	}
	return;
}

void print_loading(int n)							// 로딩창 출력 함수 
{
	system("cls");
	ORIGINAL printf("\n\n\n\n\n\n          L O A D I N G . . .\n         ");
	for (int j = 10-n; j>0; j--)	printf("■");
	for(int i = 0; i<n; i++)		printf("□");
	n--;
	Sleep(500);
	if (n < 0)	return;
	else		print_loading(n);
}

void print_head()									// 기본적으로 출력할 것들
{
	system("cls"); 
	ORIGINAL printf("  ┌───────────────┐\n  │");
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
	YELLOW printf(" [제작:대구과학고등학교 1109 서진규]\n");
	ORIGINAL printf("┌────────★────────┐\n");
	printf("│위(W), 아래(S), 왼쪽(A), 오른쪽(D)│\n");
	printf("│     새 게임(N), 게임 종료(X)     │\n");
	printf("└─────────────────┘\n");	
}

void print_field()									// 숫자판을 출력하는 함수
{
	MAGENTA printf(" ID : %c%c%c SCORE : %5d점 STAGE : %3d", temp[0], temp[1], temp[2], temp[3], temp[4]/2);
    ORIGINAL printf("\n");	
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
}

void move_up()										// 위로 미는 함수
{	
	int copy[SIZE][SIZE], check = 0;

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			copy[i][j] = field[i][j];
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// 빈칸이 있으면
			{
				field[i][j] = field[i + 1][j];	// 아랫칸의 값을 빈칸에 넣고
				field[i + 1][j] = 0;			// 아랫칸을 비운다
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// 빈칸이 있으면
			{
				field[i][j] = field[i + 1][j];	// 아랫칸의 값을 빈칸에 넣고
				field[i + 1][j] = 0;			// 아랫칸을 비운다
			}
		}
	}
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
				temp[3] += field[i][j];			// 점수 추가
				field[i + 1][j] = 0;			// 아랫칸을 비운다
			}
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] != field[i][j])	check = 1;	// 움직이기 전과 움직인 후가 같지 않다면
		}
	}

	if (check)	make_random();	// 난수 생성
}

void move_down()									// 아래로 미는 함수
{	
	int copy[SIZE][SIZE], check = 0;

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			copy[i][j] = field[i][j];
		}
	}

	for (int i = SIZE - 2; i > 0; i--)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// 빈칸이 있으면
			{
				field[i][j] = field[i - 1][j];	// 윗칸의 값을 빈칸에 넣고
				field[i - 1][j] = 0;				// 윗칸을 비운다
			}
		}
	}
	for (int i = SIZE - 2; i > 0; i--)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// 빈칸이 있으면
			{
				field[i][j] = field[i - 1][j];	// 윗칸의 값을 빈칸에 넣고
				field[i - 1][j] = 0;				// 윗칸을 비운다
			}
		}
	}
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
				temp[3] += field[i][j];			// 점수 추가
				field[i - 1][j] = 0;				// 윗칸을 비운다
			}
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] != field[i][j])	check = 1;	// 움직이기 전과 움직인 후가 같지 않다면
		}
	}

	if (check)	make_random();	// 난수 생성
}

void move_right()									// 오른쪽으로 미는 함수
{	
	int copy[SIZE][SIZE], check = 0;

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			copy[i][j] = field[i][j];
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = SIZE - 2; j > 0; j--)
		{
			if (field[i][j] == 0)				// 빈칸이 있으면
			{
				field[i][j] = field[i][j - 1];	// 왼쪽칸의 값을 빈칸에 넣고
				field[i][j - 1] = 0;				// 왼쪽칸을 비운다
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = SIZE - 2; j > 0; j--)
		{
			if (field[i][j] == 0)				// 빈칸이 있으면
			{
				field[i][j] = field[i][j - 1];	// 왼쪽칸의 값을 빈칸에 넣고
				field[i][j - 1] = 0;				// 왼쪽칸을 비운다
			}
		}
	}
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
				temp[3] += field[i][j];			// 점수 추가
				field[i][j - 1] = 0;				// 왼쪽칸을 비운다
			}
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] != field[i][j])	check = 1;	// 움직이기 전과 움직인 후가 같지 않다면
		}
	}

	if (check)	make_random();	// 난수 생성
}

void move_left()									// 왼쪽으로 미는 함수
{
	int copy[SIZE][SIZE], check=0;

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
				copy[i][j] = field[i][j];
		}
	}
	
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// 빈칸이 있으면
			{
				field[i][j] = field[i][j + 1];	// 오른쪽칸의 값을 빈칸에 넣고
				field[i][j + 1] = 0;			// 오른쪽칸을 비운다
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// 빈칸이 있으면
			{
				field[i][j] = field[i][j + 1];	// 오른쪽칸의 값을 빈칸에 넣고
				field[i][j + 1] = 0;			// 오른쪽칸을 비운다
			}
		}
	}
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
				temp[3] += field[i][j];			// 점수 추가
				field[i][j + 1] = 0;			// 오른쪽칸을 비운다
			}
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] != field[i][j])	check = 1;	// 움직이기 전과 움직인 후가 같지 않다면
		}
	}

	if (check)	make_random();	// 난수 생성
}

int check()											// 종료조건을 확인하는 함수 
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

void clear()										// 모서리를 초기화 시키는 함수 
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

void make_random()									// 랜덤으로 숫자를 만들어주는 함수
{
	int i, j;							//for문 돌릴 변수 선언 
	int n=0;							//n: 게임판 내의 0의 개수를 확인하기 위해 만든 변수
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
					if(rand()%5 == 4) field[i][j]=4;	// 20%의 확률로 4
					else field[i][j]=2;					// 80%의 확률로 2
					return;				// 숫자를 하나 넣었으면 난수생성을 종료시킨다. 
				}
				--n;					// 모든 칸에 숫자가 새로 생길 확률이 같게 해주기 위해 1을 빼준다.
			}
		}
	}
}

void repeat()										// 반복할 함수 
{
	clear();
	
	dir=0;
	scanf("%c", &dir); 
	
	if((dir == 'N')||(dir == 'n'))	main();	
	
	if((check() == 2)||(check() == 0)||(dir == 'X')||(dir == 'x'))	// 게임이 끝날 조건일 경우 
	{
		ending();
		return;
	}
	
	switch (dir)								// 어느 방향으로 밀것인지 입력받기
	{
	case 'A':
	case 'a':
		print_head();
		PURPLE printf("                  ←");					// 왼쪽 입력받음
		ORIGINAL printf("\n");
		break;
	case 'D':
	case 'd':
		print_head();
		PURPLE printf("                  →");					// 오른쪽 입력받음
		ORIGINAL printf("\n");
		break;
	case 'W':
	case 'w':
		print_head();
		PURPLE printf("                  ↑");					// 위쪽 입력받음
		ORIGINAL printf("\n");
		break;
	case 'S':
	case 's':
		print_head();
		PURPLE printf("                  ↓");					// 아래쪽 입력받음
		ORIGINAL printf("\n");
		break;
	}

	if ((dir == 'W')||(dir=='w'))								// 움직일 수 있고, ↑가 입력되는 경우 위로 민다 
	{
		move_up();
		print_field();	                        // 계산된 값 출력
	}

	if ((dir == 'S')||(dir=='s'))								// 움직일 수 있고, ↓가 입력되는 경우 아래로 민다 
	{
		move_down();
		print_field();       					// 계산된 값 출력
	}

	if ((dir == 'D')||(dir =='d'))								// 움직일 수 있고, →가 입력되는 경우 오른쪽으로 민다 
	{
		move_right();
		print_field();       					// 계산된 값 출력
	}

	if ((dir == 'A')||(dir == 'a'))								// 움직일 수 있고, ←가 입력되는 경우 왼쪽으로 민다 
	{
		move_left();
		print_field();        					// 계산된 값 출력
	}
	
	temp[4]++;
	repeat(); 
}

/*
2016.09.30 20:40
점수 순서대로 나열하는 거 마무리 필요.
아이디 입력, 아이디 점수 단계 출력, 순위표 출력
주석 추가 및 수정, 난수 생성 방식 수정, 미는 방법 수정
게임 초기화시 데이터 초기화 추가
종료 방식 수정(2048 생성, 움직일 수 없는 경우, X 입력받은 경우 : 게임 종료 -> 순위표 출력, 재시작 물어보기) 
*/

void high_score()
{
	int i, j, temp[6];
	int check = 0;
	
	for(i=0; i<5; i++)								// 정렬
	{
		for(j=0; j<(6-i)-1; j++)
		{
			if(num[j][3] > num[j+1][3])
			{
				for (int p = 0; p < 5; p++)
				{
					temp[p] = num[j][p];
					num[j][p] = num[j + 1][p];
					num[j + 1][p] = num[p];
					check = 1; 							// 데이터의 교환이 일어남
				}
			}
		}
 		if(check==0) break;							// 데이터의 교환이 없으면 중단 
	}
} 

void ending()										// 순위표 출력 함수 
{
	print_head();
	ORIGINAL printf("\n");
	Sleep(750);
	printf("   ┌──────────────┐\n");
	printf("   │  No.   ID    SCORE   STAGE │\n");
	printf("   │  1     %c%c%c   %5d     %3d │\n", num[0][0], num[0][1], num[0][2], num[0][3], num[0][4]);	
	printf("   │  2     %c%c%c   %5d     %3d │\n", num[1][0], num[1][1], num[1][2], num[1][3], num[1][4]);		
	printf("   │  3     %c%c%c   %5d     %3d │\n", num[2][0], num[2][1], num[2][2], num[2][3], num[2][4]);		
	printf("   │  4     %c%c%c   %5d     %3d │\n", num[3][0], num[3][1], num[3][2], num[3][3], num[3][4]);	
	printf("   │  5     %c%c%c   %5d     %3d │\n", num[4][0], num[4][1], num[4][2], num[4][3], num[4][4]);
	printf( "   ├──────────────┤\n   │");
	RED printf("  0     %c%c%c   %5d     %3d", temp[0], temp[1], temp[2], temp[3], temp[4]);
	ORIGINAL printf(" │\n   └──────────────┘\n");
	Sleep(700);
	return;
} 
