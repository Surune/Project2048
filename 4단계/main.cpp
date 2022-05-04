/*							대구과학고등학교 1109 서진규
							2학기 2048 프로젝트 4단계
---------------------------------------------------------------------------------
									<PATCH NOTE>
									
---------------------------------- [1단계 완성]---------------------------------- 

2016.09.30 20:40
점수 순서대로 나열하는 거 마무리 필요.
아이디 입력, 아이디 점수 단계 출력, 순위표 출력
주석 추가 및 수정, 난수 생성 방식 수정, 미는 방법 수정
게임 초기화시 데이터 초기화 추가
종료 방식 수정(2048 생성, 움직일 수 없는 경우, X 입력받은 경우 : 게임 종료 -> 순위표 출력, 재시작 물어보기)

2016.10.09 01:50
highscore 함수 완성(점수 정렬)
버그 : 방향키 한번에 많이 입력하는 경우, 상관없는 키 입력받는 경우에도 스테이지 올라감
-> 방향키 입력 방식 scanf에서 getch로 바꿈
주석 수정
repeat 함수 부분 : switch와 if문 부분 합침
temp 변수 꼬임 -> 수정 완료

2016.10.10 16:20
highscore 점수 저장 안되는 부분 수정 
이름이 같은 경우 추가 
이름이 같은 경우 : 점수가 같은 경우 스테이지 적은 것으로 출력

2016.10.12 16:20
이름이 같은 경우: 점수가 낮은 경우로 기록되면 두 점수 모두 출력되는 오류 수정 

---------------------------------- [2단계 완성]---------------------------------- 

2016.10.16 14:00
찬스-달팽이 배열 코드 추가, 포인터 사용하도록 변경 

2016.10.21 20:00
상단에 찬스, 입력키 소개 추가
player 배열에 찬스 남은 횟수 추가 

2016.10.22 14:30
chance 함수 : for문 + 개별 대입으로 바꿈(오류 등으로 인해) 
repeat 함수 : chance 남은 횟수에 따라 나누어 실행하도록 수정 

---------------------------------- [3단계 완성]---------------------------------- 

2016.10.22
repeat 함수 : case Undo, Redo 추가
변수 field, player : Undo가 가능하도록 3차원 배열로 수정
변수 here 추가 : 3차원 배열 중 출력할 2차원 배열 선택하는 변수 
-> 이에 맞춰 모든 출력 함수의 index값 변경 
move_up,down,left,right 함수 : 숫자판을 하나씩 밀어 올리고 복사본(copy)을 마지막에 끼워넣도록 수정 
chance 함수 : 숫자판을 하나씩 밀어 올리고 달팽이배열(arr)을 마지막에 끼워넣도록 수정 
모든 함수에서 한 번 움직일 때마다 player 정보를 한 칸씩 위로 올리고 새로 끼워 넣어 저장하도록 수정 
repeat 함수가 아닌 chance 함수 내에서 남은 찬스 횟수가 차감되도록 변경 
종료시 N(새 게임) 혹은 X(종료)를 입력 받았을 때에만 진행되도록 변경 -> retry 함수 생성 
scan_ID_1,2,3 함수 : getch를 이용하여 입력받은 값이 방향키가 아닌 경우- 다시 방향키로 입력한 경우 제대로 입력이 되지 않는 버그 수정
주석 수정 및 추가

2016.11.06
undo redo가 다시 안되는 점 수정 
=>make_random함수에서 here=4로 초기화하는 부분 추가
불필요한 주석 삭제 및 수정 
print_head에 undo와 redo 입력키 소개 

---------------------------------- [4단계 완성]---------------------------------- 
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h> 
#include <conio.h> 
#include <time.h>

#define COL GetStdHandle(STD_OUTPUT_HANDLE)				// 글씨 색상 변경
#define GREEN SetConsoleTextAttribute(COL, 0x0002);  	// 초록색
#define PURPLE SetConsoleTextAttribute(COL, 0x0005);  	// 보라색 
#define HIGH_GREEN SetConsoleTextAttribute(COL, 0x000a);// 연두색
#define SKY_BLUE SetConsoleTextAttribute(COL, 0x000b); 	// 하늘색
#define RED SetConsoleTextAttribute(COL, 0x000c);  		// 빨간색
#define YELLOW SetConsoleTextAttribute(COL, 0x000e);  	// 노란색
#define MAGENTA SetConsoleTextAttribute(COL, 0x000d);	// 자주색 
#define ORIGINAL SetConsoleTextAttribute(COL, 0x000f); 	// 흰색

#define SIZE 6											// 숫자판의 크기 설정
#define UP 72											// 방향키 위쪽의 아스키코드값
#define DOWN 80 										// 방향키 아래쪽의 아스키코드값
#define ENTER 13                                		// 엔터키의 아스키코드값 

int field[5][SIZE][SIZE]={0};							// 숫자판
int player[5][6]={{0},{0},{0},{0},{0,0,0,0,1,3}};		// 플레이어 ID(3자리)+점수+단계+찬스 남은 횟수 
int num[6][5];											// 순위표
char dir;												// 방향
int here=4;												// Undo, Redo시 출력할 배열의 위치(높이)를 결정해 주는 변수 
 
void new_game();
void scan_ID_1(int);
void scan_ID_2(int);
void scan_ID_3(int);
void print_loading(int);
void print_head();
void print_field();
void chance();
int check();
void clear();
void make_random();
void repeat();
void ending();
void retry();

int main()
{
	new_game();										// 변수 초기화 
	scan_ID_1(65); 									// ID(이름) 입력받음 
	scan_ID_2(65);
	scan_ID_3(65);
	print_loading(10);
	print_head();
	make_random();									// 랜덤한 위치에 숫자 생성
	make_random();									// 랜덤한 위치에 숫자 생성 
	printf("\n");
	print_field();									// 현재 숫자판 상황 출력
	repeat();										// 게임 진행
}

void new_game()										// 변수 초기화 
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			field[4][i][j] = 0;

	player[4][3]=0;									// 점수 초기화 
	player[4][4]=1;                    				// 단계 초기화 
	player[4][5]=3;									// 찬스 남은 횟수 초기화 
}

void scan_ID_1(int name)							// ID 입력받는 함수 1 
{
    int key=0;
	system("cls");
	HIGH_GREEN printf("\n\n\n\n");
	printf("  ┏━━━━━━━━━━━━━━━┓\n");
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
    	player[4][0]=name;
        return;
	}
    else 
    {
    	if(key==224)	key=getch();
		
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
    GREEN printf("%c %c A", player[4][0], name);
    HIGH_GREEN printf("            ┃\n  ┃");
    GREEN printf("              ↓              ");
	HIGH_GREEN printf("┃\n  ┗━━━━━━━━━━━━━━━┛");
    key=getch();
    if(key==ENTER)
    {
    	player[4][1]=name;
        return;
	}
    else
    {
    	if(key==224)	key=getch();
		
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
    GREEN printf("%c %c %c", player[4][0], player[4][1], name);
    HIGH_GREEN printf("            ┃\n  ┃");
    GREEN printf("                ↓            ");
	HIGH_GREEN printf("┃\n  ┗━━━━━━━━━━━━━━━┛");
    key=getch();
    if(key==ENTER)
    {
    	player[4][2]=name;
        return;
	}
    else
    {
    	if(key==224)	key=getch(); 
		
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
	Sleep(150);
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
	printf("│ ↑: W ↓: S ←: A →: D 찬스: C  │\n");
	printf("│UNDO: U REDO: R 재시작: N 종료: X │\n");
	printf("└─────────────────┘\n");	
}

void print_field()									// 숫자판을 출력하는 함수
{
	MAGENTA printf(" ID : %c%c%c SCORE : %5d점 STAGE : %3d", player[4][0], player[4][1], player[4][2], player[here][3], player[here][4]);
    ORIGINAL printf("\n");	
	for (int i = 1; i<5; i++)
	{
		if (i == 1)
			printf("  ┏━━━┳━━━┳━━━┳━━━┓\n");
		else
			printf("  ┣━━━╋━━━╋━━━╋━━━┫\n");

		for (int j = 1; j<5; j++)
		{
			if (field[here][i][j] == 0)
				printf("  ┃    ");
			else
				printf("  ┃%4d", field[here][i][j]);
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

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			copy[i][j] = field[4][i][j];			// copy 배열에 복사 
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// 빈칸이 있으면
			{
				copy[i][j] = copy[i + 1][j];		// 아랫칸의 값을 빈칸에 넣고
				copy[i + 1][j] = 0;					// 아랫칸을 비운다
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// 빈칸이 있으면
			{
				copy[i][j] = copy[i + 1][j];		// 아랫칸의 값을 빈칸에 넣고
				copy[i + 1][j] = 0;					// 아랫칸을 비운다
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// 빈칸이 있으면
			{
				copy[i][j] = copy[i + 1][j];		// 아랫칸의 값을 빈칸에 넣고
				copy[i + 1][j] = 0;					// 아랫칸을 비운다
			}
			if (copy[i][j] == copy[i + 1][j])		// 상하로 값이 같으면
			{
				copy[i][j] += copy[i + 1][j];		// 윗칸에 아랫칸의 값을 더하고
				player[4][3] += copy[i][j];			// 점수 추가
				copy[i + 1][j] = 0;					// 아랫칸을 비운다
			}
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)	
		{
			if (copy[i][j] != field[4][i][j])		// 움직이기 전과 움직인 후가 다르다면
				check = 1;							// check에 1 저장
		}
	}

	if (check)										// 움직이기 전과 움직인 후가 다르다면 
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)	
			{		
				for(int k = 0; k < 4; k++)
				{
					field[k][i][j]=field[k+1][i][j];// 배열 밀어 올리기 
					player[k][j]=player[k+1][j]; 	// 플레이어 정보 밀어 올리기 
				}
				
				field[4][i][j]=copy[i][j];			// 배열 옮겨 담기 
			}
		}	
		
		make_random();								// 난수 생성
		player[4][4]++;								// 스테이지 증가
	}
}

void move_down()									// 아래로 미는 함수
{	
	int copy[SIZE][SIZE], check = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			copy[i][j] = field[4][i][j];			// copy 배열에 복사 
		}
	}
	
	for (int i = SIZE - 2; i > 0; i--)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// 빈칸이 있으면
			{
				copy[i][j] = copy[i - 1][j];		// 윗칸의 값을 빈칸에 넣고
				copy[i - 1][j] = 0;					// 윗칸을 비운다
			}
		}
	}
	for (int i = SIZE - 2; i > 0; i--)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{	
			if (copy[i][j] == 0)					// 빈칸이 있으면
			{
				copy[i][j] = copy[i - 1][j];		// 윗칸의 값을 빈칸에 넣고
				copy[i - 1][j] = 0;					// 윗칸을 비운다
			}
		}
	}
	for (int i = SIZE - 2; i > 0; i--)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// 빈칸이 있으면
			{
				copy[i][j] = copy[i - 1][j];		// 윗칸의 값을 빈칸에 넣고
				copy[i - 1][j] = 0;					// 윗칸을 비운다
			}
			if (copy[i][j] == copy[i - 1][j])		// 상하로 값이 같으면
			{
				copy[i][j] += copy[i - 1][j];		// 아랫칸에 윗칸의 값을 더하고
				player[4][3] += copy[i][j];			// 점수 추가
				copy[i - 1][j] = 0;					// 윗칸을 비운다
			}
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)	
		{
			if (copy[i][j] != field[4][i][j])		// 움직이기 전과 움직인 후가 다르다면
				check = 1;							// check에 1 저장
		}
	}

	if (check)										// 움직이기 전과 움직인 후가 다르다면 
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)	
			{		
				for(int k = 0; k < 4; k++)
				{
					field[k][i][j]=field[k+1][i][j];// 배열 밀어 올리기 
					player[k][j]=player[k+1][j]; 	// 플레이어 정보 밀어 올리기 
				}
				
				field[4][i][j]=copy[i][j];			// 배열 옮겨 담기 
			}
		}	
		
		make_random();								// 난수 생성
		player[4][4]++;								// 스테이지 증가
	}
}

void move_right()									// 오른쪽으로 미는 함수
{	
	int copy[SIZE][SIZE], check = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			copy[i][j] = field[4][i][j];			// copy 배열에 복사 
		}
	}
	
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = SIZE - 2; j > 0; j--)
		{
			if (copy[i][j] == 0)				// 빈칸이 있으면
			{
				copy[i][j] = copy[i][j - 1];	// 왼쪽칸의 값을 빈칸에 넣고
				copy[i][j - 1] = 0;				// 왼쪽칸을 비운다
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = SIZE - 2; j > 0; j--)
		{
			if (copy[i][j] == 0)				// 빈칸이 있으면
			{
				copy[i][j] = copy[i][j - 1];	// 왼쪽칸의 값을 빈칸에 넣고
				copy[i][j - 1] = 0;				// 왼쪽칸을 비운다
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = SIZE - 2; j > 0; j--)
		{
			if (copy[i][j] == 0)				// 빈칸이 있으면
			{
				copy[i][j] = copy[i][j - 1];	// 왼쪽칸의 값을 빈칸에 넣고
				copy[i][j - 1] = 0;				// 왼쪽칸을 비운다
			}
			if (copy[i][j] == copy[i][j - 1])	// 좌우로 값이 같으면
			{
				copy[i][j] += copy[i][j - 1];	// 오른쪽칸에 왼쪽칸의 값을 더하고
				player[4][3] += copy[i][j];			// 점수 추가
				copy[i][j - 1] = 0;				// 왼쪽칸을 비운다
			}
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)	
		{
			if (copy[i][j] != field[4][i][j])		// 움직이기 전과 움직인 후가 다르다면
				check = 1;							// check에 1 저장
		}
	}

	if (check)										// 움직이기 전과 움직인 후가 다르다면 
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)	
			{		
				for(int k = 0; k < 4; k++)
				{
					field[k][i][j]=field[k+1][i][j];// 배열 밀어 올리기 
					player[k][j]=player[k+1][j]; 	// 플레이어 정보 밀어 올리기 
				}
				
				field[4][i][j]=copy[i][j];			// 배열 옮겨 담기 
			}
		}	
		
		make_random();								// 난수 생성
		player[4][4]++;								// 스테이지 증가
	}
}

void move_left()									// 왼쪽으로 미는 함수
{
	int copy[SIZE][SIZE], check=0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			copy[i][j] = field[4][i][j];			// copy 배열에 복사 
		}
	}
	
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// 빈칸이 있으면
			{
				copy[i][j] = copy[i][j + 1];		// 오른쪽칸의 값을 빈칸에 넣고
				copy[i][j + 1] = 0;					// 오른쪽칸을 비운다
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// 빈칸이 있으면
			{
				copy[i][j] = copy[i][j + 1];		// 오른쪽칸의 값을 빈칸에 넣고
				copy[i][j + 1] = 0;					// 오른쪽칸을 비운다
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// 빈칸이 있으면
			{
				copy[i][j] = copy[i][j + 1];		// 오른쪽칸의 값을 빈칸에 넣고
				copy[i][j + 1] = 0;					// 오른쪽칸을 비운다
			}
			if (copy[i][j] == copy[i][j + 1])		// 좌우로 값이 같으면
			{
				copy[i][j] += copy[i][j + 1];		// 왼쪽칸에 오른쪽칸의 값을 더하고
				player[4][3] += copy[i][j];			// 점수 추가
				copy[i][j + 1] = 0;					// 오른쪽칸을 비운다
			}
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)	
		{
			if (copy[i][j] != field[4][i][j])		// 움직이기 전과 움직인 후가 다르다면
				check = 1;							// check에 1 저장
		}
	}

	if (check)										// 움직이기 전과 움직인 후가 다르다면 
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)	
			{		
				for(int k = 0; k < 4; k++)
				{
					field[k][i][j]=field[k+1][i][j];// 배열 밀어 올리기 
					player[k][j]=player[k+1][j]; 	// 플레이어 정보 밀어 올리기 
				}
				
				field[4][i][j]=copy[i][j];			// 배열 옮겨 담기 
			}
		}	
		
		make_random();								// 난수 생성
		player[4][4]++;								// 스테이지 증가
	}
}

void chance()										// 찬스 함수 
{
	int arr[(SIZE-2)][(SIZE-2)] = {0};
	int i, j;

	for(i=0; i<4; i++)		arr[0][i]=field[4][1][i+1];
	arr[1][3]=field[4][2][1];
	arr[2][3]=field[4][2][2];
	arr[3][3]=field[4][2][3];
	arr[3][2]=field[4][2][4];
	arr[3][1]=field[4][3][1];
	for(j=3; j>0; j--)		arr[j][0]=field[4][3][5-j];
	for(i=1; i<3; i++)		arr[1][i]=field[4][4][i];
	for(i=2; i>0; i--)		arr[2][i]=field[4][4][5-i];

    for(int i=1; i<SIZE-1; i++)
	{
		for(int j=1; j<SIZE-1; j++)
		{	
			for(int k = 0; k < 4; k++)
			{
				field[k][i][j]=field[k+1][i][j];	// 배열 밀어 올리기 
				player[k][j]=player[k+1][j]; 		// 플레이어 정보 밀어 올리기 
			}
				
				field[4][i][j]=arr[i-1][j-1];		// 배열 옮겨 담기 
		}
	}
	
	player[4][5]--;									// 찬스 남은 횟수 차감 
}

int check()											// 종료조건을 확인하는 함수 
{
	int end = 0;
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			if (field[4][i][j] == 0)
				end = 1;						// 빈 칸이 있으면 1 반환

			if (field[4][i][j] == field[4][i + 1][j])
				end = 1;						// 위아래로 같은 값이 있으면 1 반환

			if (field[4][i][j] == field[4][i][j + 1])
				end = 1;						// 좌우로 같은 값이 있으면 1 반환

			if (field[4][i][j] == 2048)
				end = 2;						// 2048이 만들어지면 2 반환
		}
	}
	return end;
}

void clear()										// 모서리를 초기화 시키는 함수 
{
	for (int i = 0; i < SIZE; i++)
	{
		field[4][i][0] = 0;							// 각 모서리 초기화 (쓰레기값 방지)
		field[4][i][SIZE-1] = 0;					// 각 모서리 초기화 (쓰레기값 방지)
	}

	for (int j = 0; j < SIZE; j++)
	{
		field[4][0][j] = 0;							// 각 모서리 초기화 (쓰레기값 방지)
		field[4][SIZE-1][j] = 0;					// 각 모서리 초기화 (쓰레기값 방지)
	}
}

void make_random()									// 랜덤으로 숫자를 만들어주는 함수
{
	here=4; 
	int i, j;										// for문 돌릴 변수 선언 
	int n=0;										// n : 게임판 내의 0의 개수
	srand((unsigned)time(NULL));					// 난수 생성을 위한 코드 

	for(i=1; i<SIZE-1; i++)
	{
		for(j=1; j<SIZE-1; j++)
		{
			if(field[4][i][j]==0) n++;				// 게임판의 0의 개수 확인
		}
	}
	
	for(i=1; i<SIZE-1; i++)
	{
		for(j=1; j<SIZE-1; j++)
		{
			if(field[4][i][j]==0)					// 0의 위치에만 새로운 숫자를 넣어야 한다. 
			{
				if(rand()%n ==0)					// 1/n의 확률로 이 위치에 새로운 숫자가 들어간다. 
				{
					if(rand()%5 == 4) 
						field[4][i][j]=4;			// 20%의 확률로 4
					else 
						field[4][i][j]=2;			// 80%의 확률로 2
					return;							// 숫자를 넣었으면 난수생성 종료
				}
				--n;								// 모든 칸에 숫자가 새로 생길 확률이 같게 해주기 위해 1을 빼준다.
			}
		}
	}
}

void repeat()										// 반복할 함수(게임의 기본 함수) 
{
	clear();
	
	dir = 0;
	dir = getch();

	if((dir == 'N')||(dir == 'n'))	main();	
	
	if((check() == 2)||(check() == 0)||(dir == 'X')||(dir == 'x'))	// 게임이 끝날 조건일 경우 
	{
		ending();
		return;
	}
	
	switch (dir)									// 어느 방향으로 밀것인지 입력받기
	{
		case 'A':
		case 'a':									// 움직일 수 있고, A가 입력되는 경우
			print_head();
			PURPLE printf("                  ←");
			ORIGINAL printf("\n");
			move_left();
			print_field();        					// 계산된 값 출력
			break;

		case 'D':
		case 'd':									// 움직일 수 있고, D가 입력되는 경우
			print_head();
			PURPLE printf("                  →");	// 오른쪽 입력받음
			ORIGINAL printf("\n");
			move_right();
			print_field();       					// 계산된 값 출력
			break;

		case 'W':
		case 'w':									// 움직일 수 있고, W가 입력되는 경우
			print_head();
			PURPLE printf("                  ↑");	// 위쪽 입력받음
			ORIGINAL printf("\n");
			move_up();
			print_field();							// 계산된 값 출력
			break;

		case 'S':
		case 's':									// 움직일 수 있고, S가 입력되는 경우
			print_head();
			PURPLE printf("                  ↓");	// 아래쪽 입력받음
			ORIGINAL printf("\n");
			move_down();
			print_field();       					// 계산된 값 출력
			break;

		case 'C':
		case 'c':									// 찬스를 입력받은 경우
			print_head();
			if(player[4][5]>0)						// 찬스가 남았다면 
			{
				PURPLE printf("        CHANCE : 남은 횟수 %d회", player[4][5]-1);
				ORIGINAL printf("\n");
				chance();							// 찬스 사용 
			}
			else									// 찬스를 다 사용했다면 
			{
				PURPLE printf("      CHANCE를 다 사용하셨습니다.");
				ORIGINAL printf("\n");
			}
			print_field();       					// 계산된 값 출력
			break;

		case 'U':
		case 'u':
			print_head();			
			if((here<1)||(player[here][4]<2))		// 되돌릴 수 없는 경우 
			{
				PURPLE printf("      더 이상 되돌릴 수 없습니다.\n");
				print_field();
				break;
			}
			PURPLE printf("      	         UNDO");
			ORIGINAL printf("\n");
			here--;									// 배열의 높이 차감 
			print_field();        					// 되돌린 값 출력
			break;

		case 'R':
		case 'r':
			print_head();
			if(here>=4)								// 되돌릴 수 없는 경우 
			{
				PURPLE printf("      더 이상 되돌릴 수 없습니다.\n");
				print_field();
				break;
			}
			PURPLE printf("      	         REDO");
			ORIGINAL printf("\n");
			here++;									// 배열의 높이 증가 
			print_field();        					// 되돌린 값 출력
			break;
			
		default:									// 잘못된 키가 입력되는 경우
			print_head();
			PURPLE printf("         잘못 입력하셨습니다.");
			ORIGINAL printf("\n");
			print_field();       					// 계산된 값 출력
	}
			repeat();
}

void high_score()
{
	int i, j, temp;

	for(i=0; i<5; i++)
		num[5][i]=player[4][i];

	for(i=0; i<6; i++)								// 이름이 같은 경우 
	{
		if((num[i][0] == num[5][0])&&(num[i][1] == num[5][1])&&(num[i][2] == num[5][2]))
		{
			if(num[i][3] < num[5][3])
			{
				num[i][3] = num[5][3];
				num[i][4] = num[5][4];
				num[5][3] = -1;
			}
			
			if(num[i][3] == num[5][3])
			{
				if(num[i][4] > num[5][4])
				{
					num[i][3] = num[5][3];
					num[i][4] = num[5][4];
					num[5][3] = -1;
				}

			}		
			
			if(num[i][3] > num[5][3])
			{
				num[5][3] = -1;
			}		
		}
	}

	for(i=0; i<5; i++)								// 정렬
	{
		for(j=0; j<(6-i)-1; j++)
		{
			if(num[j][3] < num[j+1][3])
			{
				for (int p = 0; p < 5; p++)
				{
					temp = num[j][p];
					num[j][p] = num[j+1][p];
					num[j+1][p] = temp;
				}
			}
		}
	}
} 

void ending()										// 순위표 출력 함수 
{
	print_head();
	ORIGINAL printf("\n");
	high_score();
	Sleep(600);
	printf("   ┌──────────────┐\n");
	printf("   │  No.   ID    SCORE   STAGE │\n");
	printf("   │  1     %c%c%c   %5d     %3d │\n", num[0][0], num[0][1], num[0][2], num[0][3], num[0][4]);	
	printf("   │  2     %c%c%c   %5d     %3d │\n", num[1][0], num[1][1], num[1][2], num[1][3], num[1][4]);		
	printf("   │  3     %c%c%c   %5d     %3d │\n", num[2][0], num[2][1], num[2][2], num[2][3], num[2][4]);		
	printf("   │  4     %c%c%c   %5d     %3d │\n", num[3][0], num[3][1], num[3][2], num[3][3], num[3][4]);	
	printf("   │  5     %c%c%c   %5d     %3d │\n", num[4][0], num[4][1], num[4][2], num[4][3], num[4][4]);
	printf( "   ├──────────────┤\n   │");
	RED printf("  0     %c%c%c   %5d     %3d", player[4][0], player[4][1], player[4][2], player[4][3], player[4][4]);
	ORIGINAL printf(" │\n   └──────────────┘\n");
	Sleep(600);
	YELLOW printf("        NEW GAME : N, EXIT : X");
	retry();
}

void retry()
{
	int re=getch();
	if((re==78)||(re==110))			main();			// N을 입력받으면 main함수 첫부분으로 -> 처음부터 
	else if((re==88)||(re==120))	return;			// X를 입력받으면 main함수 repeat 다음 부분으로 -> 종료 
	else retry();									// 다른 키를 입력받으면 다시 입력받기 
}
