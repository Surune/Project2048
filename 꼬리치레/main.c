/*							�뱸���а���б� 1109 ������
							2�б� 2048 ������Ʈ 4�ܰ�
---------------------------------------------------------------------------------
									<PATCH NOTE>
									
---------------------------------- [1�ܰ� �ϼ�]---------------------------------- 

2016.09.30 20:40
���� ������� �����ϴ� �� ������ �ʿ�.
���̵� �Է�, ���̵� ���� �ܰ� ���, ����ǥ ���
�ּ� �߰� �� ����, ���� ���� ��� ����, �̴� ��� ����
���� �ʱ�ȭ�� ������ �ʱ�ȭ �߰�
���� ��� ����(2048 ����, ������ �� ���� ���, X �Է¹��� ��� : ���� ���� -> ����ǥ ���, ����� �����)

2016.10.09 01:50
highscore �Լ� �ϼ�(���� ����)
���� : ����Ű �ѹ��� ���� �Է��ϴ� ���, ������� Ű �Է¹޴� ��쿡�� �������� �ö�
-> ����Ű �Է� ��� scanf���� getch�� �ٲ�
�ּ� ����
repeat �Լ� �κ� : switch�� if�� �κ� ��ħ
temp ���� ���� -> ���� �Ϸ�

2016.10.10 16:20
highscore ���� ���� �ȵǴ� �κ� ���� 
�̸��� ���� ��� �߰� 
�̸��� ���� ��� : ������ ���� ��� �������� ���� ������ ���

2016.10.12 16:20
�̸��� ���� ���: ������ ���� ���� ��ϵǸ� �� ���� ��� ��µǴ� ���� ���� 

---------------------------------- [2�ܰ� �ϼ�]---------------------------------- 

2016.10.16 14:00
����-������ �迭 �ڵ� �߰�, ������ ����ϵ��� ���� 

2016.10.21 20:00
��ܿ� ����, �Է�Ű �Ұ� �߰�
player �迭�� ���� ���� Ƚ�� �߰� 

2016.10.22 14:30
chance �Լ� : for�� + ���� �������� �ٲ�(���� ������ ����) 
repeat �Լ� : chance ���� Ƚ���� ���� ������ �����ϵ��� ���� 

---------------------------------- [3�ܰ� �ϼ�]---------------------------------- 

2016.10.22
repeat �Լ� : case Undo, Redo �߰�
���� field, player : Undo�� �����ϵ��� 3���� �迭�� ����
���� here �߰� : 3���� �迭 �� ����� 2���� �迭 �����ϴ� ���� 
-> �̿� ���� ��� ��� �Լ��� index�� ���� 
move_up,down,left,right �Լ� : �������� �ϳ��� �о� �ø��� ���纻(copy)�� �������� �����ֵ��� ���� 
chance �Լ� : �������� �ϳ��� �о� �ø��� �����̹迭(arr)�� �������� �����ֵ��� ���� 
��� �Լ����� �� �� ������ ������ player ������ �� ĭ�� ���� �ø��� ���� ���� �־� �����ϵ��� ���� 
repeat �Լ��� �ƴ� chance �Լ� ������ ���� ���� Ƚ���� �����ǵ��� ���� 
����� N(�� ����) Ȥ�� X(����)�� �Է� �޾��� ������ ����ǵ��� ���� -> retry �Լ� ���� 
scan_ID_1,2,3 �Լ� : getch�� �̿��Ͽ� �Է¹��� ���� ����Ű�� �ƴ� ���- �ٽ� ����Ű�� �Է��� ��� ����� �Է��� ���� �ʴ� ���� ����
�ּ� ���� �� �߰�

2016.11.06
undo redo�� �ٽ� �ȵǴ� �� ���� 
=>make_random�Լ����� here=4�� �ʱ�ȭ�ϴ� �κ� �߰�
���ʿ��� �ּ� ���� �� ���� 
print_head�� undo�� redo �Է�Ű �Ұ� 

---------------------------------- [4�ܰ� �ϼ�]---------------------------------- 
2016.11.26
ai �Լ� �߰� : �ΰ������� �����ϴ� �Լ� 
move �Լ� �߰� �� repeat �Լ� ���� :  ai�� ���Ͽ� move �Լ� �и� 

2016.11.27
tutorial �Լ� �߰� �� print_head �Լ� ���� : �������� ���Ͽ� ����Ű ���� �߰� 
�ּ� �߰� 
��ü�� ������ 

2016.12.02
player �迭-> ����ü�� �����Ͽ� ��� 
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h> 
#include <conio.h> 
#include <time.h>

#define COL GetStdHandle(STD_OUTPUT_HANDLE)				// �۾� ���� ����
#define GREEN SetConsoleTextAttribute(COL, 0x0002);  	// �ʷϻ�
#define PURPLE SetConsoleTextAttribute(COL, 0x0005);  	// ����� 
#define HIGH_GREEN SetConsoleTextAttribute(COL, 0x000a);// ���λ�
#define SKY_BLUE SetConsoleTextAttribute(COL, 0x000b); 	// �ϴû�
#define RED SetConsoleTextAttribute(COL, 0x000c);  		// ������
#define YELLOW SetConsoleTextAttribute(COL, 0x000e);  	// �����
#define MAGENTA SetConsoleTextAttribute(COL, 0x000d);	// ���ֻ� 
#define ORIGINAL SetConsoleTextAttribute(COL, 0x000f); 	// ���

#define SIZE 6											// �������� ũ�� ����
#define UP 72											// ����Ű ������ �ƽ�Ű�ڵ尪
#define DOWN 80 										// ����Ű �Ʒ����� �ƽ�Ű�ڵ尪
#define ENTER 13                                		// ����Ű�� �ƽ�Ű�ڵ尪 

typedef struct info
{
	int field[5][SIZE][SIZE];
	int name_1; 
	int name_2; 
	int name_3;
	int score[5];
	int stage[5];
	int chance[5];
} Player;
Player new_player;
int num[6][5];											// ����ǥ
char dir;												// ����
int here=4;												// Undo, Redo�� ����� �迭�� ��ġ(����)�� ������ �ִ� ���� 
int copy[SIZE][SIZE];

void new_game();
void scan_ID_1(int);
void scan_ID_2(int);
void scan_ID_3(int);
void print_loading(int);
void tutorial();
void print_head();
void print_field();
void chance();
int check();
void clear();
void make_random();
void repeat();
void ending();
void retry();
void ai();
void move();
void memory();

int main()
{
	new_game();										// ���� �ʱ�ȭ 
	scan_ID_1(65); 									// ID(�̸�) �Է¹��� 
	scan_ID_2(65);
	scan_ID_3(65);
//	print_loading(10);
//	tutorial();
	print_head();
	make_random();									// ������ ��ġ�� ���� ����
	make_random();									// ������ ��ġ�� ���� ���� 
	printf("\n");
	print_field();									// ���� ������ ��Ȳ ���
	repeat();										// ���� ����
}

void new_game()										// ���� �ʱ�ȭ 
{
	int i, j, k;
	
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			for(k = 0; k < SIZE ; k++)
				new_player.field[k][i][j] = 0;		// ������ �ʱ�ȭ 

	for (i =0; i < 5; i++)
	{
		new_player.score[i]=0;								// ���� �ʱ�ȭ 
		new_player.stage[i]=1;                    			// �ܰ� �ʱ�ȭ 
		new_player.chance[i]=3;							// ���� ���� Ƚ�� �ʱ�ȭ 
	}
}

void scan_ID_1(int name)							// ID �Է¹޴� �Լ� 1 
{
    int key=0;
	system("cls");
	HIGH_GREEN printf("\n\n\n\n\n");
	printf("  ����������������������������������\n");
	printf("  ��     [ USE ��, ��, ENTER ]    ��\n");
	printf("  ��        What's Your ID?       ��\n");
	printf("  ��                              ��\n  ��");
	GREEN printf("            ��                ");
	HIGH_GREEN printf("��\n  ��             ");
	if(name==64)   name=90;
	if(name==91)   name=65;
    GREEN printf("%c A A", name);
	HIGH_GREEN printf("            ��\n  ��");
    GREEN printf("            ��                ");
	HIGH_GREEN printf("��\n  ����������������������������������");
    key=getch();
    if(key==ENTER)
    {
    	new_player.name_1=name;
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

void scan_ID_2(int name)							// ID �Է¹޴� �Լ� 2
{
    int key=0;
	system("cls");
	HIGH_GREEN printf("\n\n\n\n\n  ����������������������������������\n");
	printf("  ��     [ USE ��, ��, ENTER ]    ��\n");
	printf("  ��        What's Your ID?       ��\n");
	printf("  ��                              ��\n  ��");
	GREEN printf("              ��              ");
	HIGH_GREEN printf("��\n  ��             ");
	if(name==64)   name=90;
	if(name==91)   name=65;
    GREEN printf("%c %c A", new_player.name_1, name);
    HIGH_GREEN printf("            ��\n  ��");
    GREEN printf("              ��              ");
	HIGH_GREEN printf("��\n  ����������������������������������");
    key=getch();
    if(key==ENTER)
    {
    	new_player.name_2=name;
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

void scan_ID_3(int name)							// ID �Է¹޴� �Լ� 3
{
    int key=0;
	system("cls");
	HIGH_GREEN printf("\n\n\n\n\n  ����������������������������������\n");
	printf("  ��     [ USE ��, ��, ENTER ]    ��\n");
	printf("  ��        What's Your ID?       ��\n");
	printf("  ��                              ��\n  ��");
	GREEN printf("                ��            ");
	HIGH_GREEN printf("��\n  ��             ");
	if(name==64)   name=90;
	if(name==91)   name=65;
    GREEN printf("%c %c %c", new_player.name_1, new_player.name_2, name);
    HIGH_GREEN printf("            ��\n  ��");
    GREEN printf("                ��            ");
	HIGH_GREEN printf("��\n  ����������������������������������");
    key=getch();
    if(key==ENTER)
    {
    	new_player.name_3=name;
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

void tutorial()										// ����Ű �������ִ� �Լ� 
{
	print_head();
	ORIGINAL printf("\n�������������������ڦ�����������������\n");
	printf("��         [ ����Ű ���� ]          ��\n");
	printf("��                                  ��\n");
	printf("��  ");
	MAGENTA printf("��: W   ��: S   ��: A   ��: D   ");
	ORIGINAL printf("��\n");
	printf("��                                  ��\n��");
	MAGENTA printf("   ����: C   UNDO: U   REDO: R    ");
	ORIGINAL printf("��\n");
	printf("��                                  ��\n��");
	MAGENTA printf("  �ڵ�: P   �����: N   ����: X   ");
	ORIGINAL printf("��\n");
	printf("��                                  ��\n");
	printf("��������������������������������������\n");	
	Sleep(5000);
}

void print_loading(int n)							// �ε�â ��� �Լ� 
{
	int i, j;
	
	system("cls");
	ORIGINAL printf("\n\n\n\n\n\n\n          L O A D I N G . . .\n\n\n         ");
	for(j = 10-n; j>0; j--)	printf("��");
	for(i = 0; i<n; i++)		printf("��");
	n--;
	Sleep(500);
	if (n < 0)	return;
	else		print_loading(n);
}

void print_head()									// �⺻������ ����� �͵�
{
	system("cls"); 
	ORIGINAL printf("  ����������������������������������\n  ��");
	SKY_BLUE printf(" ���� ���� ��  �� ����");
	ORIGINAL printf(" G��\n  ��");
	SKY_BLUE printf("     �� ��  �� ��  �� ��  ��");
	ORIGINAL printf(" A��\n  ��");
	SKY_BLUE printf(" ���� ��  �� ���� ����");
	ORIGINAL printf(" M��\n  ��");
	SKY_BLUE printf(" ��     ��  ��     �� ��  ��");
	ORIGINAL printf(" E��\n  ��");
	SKY_BLUE printf(" ���� ����     �� ����");
	ORIGINAL printf(" !��\n");
	printf("  ����������������������������������\n\n");
	YELLOW printf("  [����:�뱸���а���б� 1109 ������]\n\n");
}

void print_field()									// �������� ����ϴ� �Լ�
{
	int i, j;
	MAGENTA printf("\n ID : %c%c%c SCORE : %5d�� STAGE : %3d", new_player.name_1, new_player.name_2, new_player.name_3, new_player.score[4], new_player.stage[4]);
    ORIGINAL printf("\n");	
	for (i = 1; i<5; i++)
	{
		if (i == 1)
			printf("\n  ����������������������������������\n");
		else
			printf("  ����������������������������������\n");

		for (j = 1; j<5; j++)
		{
			if (new_player.field[4][i][j] == 0)
				printf("  ��    ");
			else
				printf("  ��%4d", new_player.field[4][i][j]);
			if (j == 4)
				printf("  ��");
		}
		printf("\n");

		if (i == 4)
			printf("  ����������������������������������\n");
	}
}

void move_up()										// ���� �̴� �Լ�
{	
	int check = 0;
	int i, j, k;
	
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			copy[i][j] = new_player.field[4][i][j];	// copy �迭�� ���� 
		}
	}

	for (i = 1; i < SIZE - 1; i++)
	{
		for (j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// ��ĭ�� ������
			{
				copy[i][j] = copy[i + 1][j];		// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
				copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
			}
		}
	}
	for (i = 1; i < SIZE - 1; i++)
	{
		for (j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// ��ĭ�� ������
			{
				copy[i][j] = copy[i + 1][j];		// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
				copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
			}
		}
	}
	for (i = 1; i < SIZE - 1; i++)
	{
		for (j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// ��ĭ�� ������
			{
				copy[i][j] = copy[i + 1][j];		// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
				copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
			}
			if (copy[i][j] == copy[i + 1][j])		// ���Ϸ� ���� ������
			{
				copy[i][j] += copy[i + 1][j];		// ��ĭ�� �Ʒ�ĭ�� ���� ���ϰ�
				new_player.score[4] += copy[i][j];	// ���� �߰�
				copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
			}
		}
	}

	for (i = 1; i < SIZE - 1; i++)
	{
		for (j = 1; j < SIZE - 1; j++)	
		{
			if (copy[i][j] != new_player.field[4][i][j])	// �����̱� ���� ������ �İ� �ٸ��ٸ�
				check = 1;							// check�� 1 ����
		}
	}

	if (check)										// �����̱� ���� ������ �İ� �ٸ��ٸ� 
	{
		memory();
		make_random();								// ���� ����
		new_player.stage[4]++;						// �������� ����
	}
}

void move_down()									// �Ʒ��� �̴� �Լ�
{	
	int copy[SIZE][SIZE], check = 0;
	int i, j, k;
	
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			copy[i][j] = new_player.field[4][i][j];			// copy �迭�� ���� 
		}
	}
	
	for (i = SIZE - 2; i > 0; i--)
	{
		for (j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// ��ĭ�� ������
			{
				copy[i][j] = copy[i - 1][j];		// ��ĭ�� ���� ��ĭ�� �ְ�
				copy[i - 1][j] = 0;					// ��ĭ�� ����
			}
		}
	}
	for (i = SIZE - 2; i > 0; i--)
	{
		for (j = 1; j < SIZE - 1; j++)
		{	
			if (copy[i][j] == 0)					// ��ĭ�� ������
			{
				copy[i][j] = copy[i - 1][j];		// ��ĭ�� ���� ��ĭ�� �ְ�
				copy[i - 1][j] = 0;					// ��ĭ�� ����
			}
		}
	}
	for (i = SIZE - 2; i > 0; i--)
	{
		for (j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// ��ĭ�� ������
			{
				copy[i][j] = copy[i - 1][j];		// ��ĭ�� ���� ��ĭ�� �ְ�
				copy[i - 1][j] = 0;					// ��ĭ�� ����
			}
			if (copy[i][j] == copy[i - 1][j])		// ���Ϸ� ���� ������
			{
				copy[i][j] += copy[i - 1][j];		// �Ʒ�ĭ�� ��ĭ�� ���� ���ϰ�
				new_player.score[4] += copy[i][j];			// ���� �߰�
				copy[i - 1][j] = 0;					// ��ĭ�� ����
			}
		}
	}

	for (i = 1; i < SIZE - 1; i++)
	{
		for (j = 1; j < SIZE - 1; j++)	
		{
			if (copy[i][j] != new_player.field[4][i][j])		// �����̱� ���� ������ �İ� �ٸ��ٸ�
				check = 1;							// check�� 1 ����
		}
	}
	
	if (check)										// �����̱� ���� ������ �İ� �ٸ��ٸ� 
	{
		memory();
		make_random();								// ���� ����
		new_player.stage[4]++;						// �������� ����
	}
}

void move_right()									// ���������� �̴� �Լ�
{	
	int copy[SIZE][SIZE], check = 0;
	int i, j, k;
	
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			copy[i][j] = new_player.field[4][i][j];			// copy �迭�� ���� 
		}
	}
	
	for (i = 1; i < SIZE - 1; i++)
	{
		for (j = SIZE - 2; j > 0; j--)
		{
			if (copy[i][j] == 0)				// ��ĭ�� ������
			{
				copy[i][j] = copy[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
				copy[i][j - 1] = 0;				// ����ĭ�� ����
			}
		}
	}
	for (i = 1; i < SIZE - 1; i++)
	{
		for (j = SIZE - 2; j > 0; j--)
		{
			if (copy[i][j] == 0)				// ��ĭ�� ������
			{
				copy[i][j] = copy[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
				copy[i][j - 1] = 0;				// ����ĭ�� ����
			}
		}
	}
	for (i = 1; i < SIZE - 1; i++)
	{
		for (j = SIZE - 2; j > 0; j--)
		{
			if (copy[i][j] == 0)				// ��ĭ�� ������
			{
				copy[i][j] = copy[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
				copy[i][j - 1] = 0;				// ����ĭ�� ����
			}
			if (copy[i][j] == copy[i][j - 1])	// �¿�� ���� ������
			{
				copy[i][j] += copy[i][j - 1];	// ������ĭ�� ����ĭ�� ���� ���ϰ�
				new_player.score[4] += copy[i][j];			// ���� �߰�
				copy[i][j - 1] = 0;				// ����ĭ�� ����
			}
		}
	}

	for (i = 1; i < SIZE - 1; i++)
	{
		for (j = 1; j < SIZE - 1; j++)	
		{
			if (copy[i][j] != new_player.field[4][i][j])		// �����̱� ���� ������ �İ� �ٸ��ٸ�
				check = 1;							// check�� 1 ����
		}
	}
	
	if (check)										// �����̱� ���� ������ �İ� �ٸ��ٸ� 
	{
		memory();
		make_random();								// ���� ����
		new_player.stage[4]++;						// �������� ����
	}
}

void move_left()									// �������� �̴� �Լ�
{
	int copy[SIZE][SIZE], check=0;
	int i, j, k;
	
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			copy[i][j] = new_player.field[4][i][j];			// copy �迭�� ���� 
		}
	}
	
	for (i = 1; i < SIZE - 1; i++)
	{
		for (j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// ��ĭ�� ������
			{
				copy[i][j] = copy[i][j + 1];		// ������ĭ�� ���� ��ĭ�� �ְ�
				copy[i][j + 1] = 0;					// ������ĭ�� ����
			}
		}
	}
	for (i = 1; i < SIZE - 1; i++)
	{
		for (j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// ��ĭ�� ������
			{
				copy[i][j] = copy[i][j + 1];		// ������ĭ�� ���� ��ĭ�� �ְ�
				copy[i][j + 1] = 0;					// ������ĭ�� ����
			}
		}
	}
	for (i = 1; i < SIZE - 1; i++)
	{
		for (j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] == 0)					// ��ĭ�� ������
			{
				copy[i][j] = copy[i][j + 1];		// ������ĭ�� ���� ��ĭ�� �ְ�
				copy[i][j + 1] = 0;					// ������ĭ�� ����
			}
			if (copy[i][j] == copy[i][j + 1])		// �¿�� ���� ������
			{
				copy[i][j] += copy[i][j + 1];		// ����ĭ�� ������ĭ�� ���� ���ϰ�
				new_player.score[4] += copy[i][j];			// ���� �߰�
				copy[i][j + 1] = 0;					// ������ĭ�� ����
			}
		}
	}

	for (i = 1; i < SIZE - 1; i++)
	{
		for (j = 1; j < SIZE - 1; j++)	
		{
			if (copy[i][j] != new_player.field[4][i][j])		// �����̱� ���� ������ �İ� �ٸ��ٸ�
				check = 1;							// check�� 1 ����
		}
	}

	if (check)										// �����̱� ���� ������ �İ� �ٸ��ٸ� 
	{
		memory();
		make_random();								// ���� ����
		new_player.stage[4]++;						// �������� ����
	}
}

void chance()										// ���� �Լ� 
{
	int x=-1, y=0, d=1, k=4, i, p=0;
	while (k+1) 
	{
		for (i=0; i<k; i++)
		{
			x+=d;
			copy[y][x] = new_player.field[4][p/4][p%4];
			p++;
		}
			k--;
		
		for (i=0; i<k; i++)
		{
			y+=d;
			copy[y][x] = new_player.field[4][p/4][p%4];
			p++;
		}
			d*=-1;
	}

	memory();
	
	new_player.chance[4]--;							// ���� ���� Ƚ�� ���� 
}

void memory()										// ������ �о� �ø��� �Լ� 
{
	int i, j, k;
	 
	for(i=0; i<SIZE; i++)
	{
		for(j=0; j<SIZE; j++)
		{	
			for(k = 0; k < 4; k++)
			{
				new_player.field[k][i][j]= new_player.field[k+1][i][j];	// �迭 �о� �ø��� 
			}
			
			new_player.field[4][i][j]=copy[i][j];			// �迭 �Ű� ��� 
		}
	}
	
	for(k=0; k<4; k++)
	{
		new_player.score[k]=new_player.score[k+1]; 		
		new_player.stage[k]=new_player.stage[k+1];
		new_player.chance[k]=new_player.stage[k+1];	// �÷��̾� ���� �о� �ø���
	}
}

int check()											// ���������� Ȯ���ϴ� �Լ� 
{
	int end = 0;
	int i, j;
	
	for (i = 1; i < 5; i++)
	{
		for (j = 1; j < 5; j++)
		{
			if (new_player.field[4][i][j] == 0)
				end = 1;						// �� ĭ�� ������ 1 ��ȯ

			if (new_player.field[4][i][j] == new_player.field[4][i + 1][j])
				end = 1;						// ���Ʒ��� ���� ���� ������ 1 ��ȯ

			if (new_player.field[4][i][j] == new_player.field[4][i][j + 1])
				end = 1;						// �¿�� ���� ���� ������ 1 ��ȯ

			if (new_player.field[4][i][j] == 2048)
				end = 2;						// 2048�� ��������� 2 ��ȯ
		}
	}
	return end;
}

void clear()										// �𼭸��� �ʱ�ȭ ��Ű�� �Լ� 
{
	int i, j;
	
	for (i = 0; i < SIZE; i++)
	{
		new_player.field[4][i][0] = 0;							// �� �𼭸� �ʱ�ȭ (�����Ⱚ ����)
		new_player.field[4][i][SIZE-1] = 0;					// �� �𼭸� �ʱ�ȭ (�����Ⱚ ����)
	}

	for (j = 0; j < SIZE; j++)
	{
		new_player.field[4][0][j] = 0;							// �� �𼭸� �ʱ�ȭ (�����Ⱚ ����)
		new_player.field[4][SIZE-1][j] = 0;					// �� �𼭸� �ʱ�ȭ (�����Ⱚ ����)
	}
}

void make_random()									// �������� ���ڸ� ������ִ� �Լ�
{
	here=4; 
	int i, j;										// for�� ���� ���� ���� 
	int n=0;										// n : ������ ���� 0�� ����
	srand((unsigned)time(NULL));					// ���� ������ ���� �ڵ� 

	for(i=1; i<SIZE-1; i++)
	{
		for(j=1; j<SIZE-1; j++)
		{
			if(new_player.field[4][i][j]==0) n++;				// �������� 0�� ���� Ȯ��
		}
	}
	
	for(i=1; i<SIZE-1; i++)
	{
		for(j=1; j<SIZE-1; j++)
		{
			if(new_player.field[4][i][j]==0)					// 0�� ��ġ���� ���ο� ���ڸ� �־�� �Ѵ�. 
			{
				if(rand()%n ==0)					// 1/n�� Ȯ���� �� ��ġ�� ���ο� ���ڰ� ����. 
				{
					if(rand()%5 == 4) 
						new_player.field[4][i][j]=4;			// 20%�� Ȯ���� 4
					else 
						new_player.field[4][i][j]=2;			// 80%�� Ȯ���� 2
					return;							// ���ڸ� �־����� �������� ����
				}
				--n;								// ��� ĭ�� ���ڰ� ���� ���� Ȯ���� ���� ���ֱ� ���� 1�� ���ش�.
			}
		}
	}
}

void move()											// dir�� ���� �������� �������ִ� �Լ� 
{
	switch (dir)									// ��� �������� �а����� �Է¹ޱ�
	{
		case 'A':
		case 'a':									// ������ �� �ְ�, A�� �ԷµǴ� ���
			print_head();
			PURPLE printf("                  ��");
			ORIGINAL printf("\n");
			move_left();
			print_field();        					// ���� �� ���
			break;

		case 'D':
		case 'd':									// ������ �� �ְ�, D�� �ԷµǴ� ���
			print_head();
			PURPLE printf("                  ��");	// ������ �Է¹���
			ORIGINAL printf("\n");
			move_right();
			print_field();       					// ���� �� ���
			break;

		case 'W':
		case 'w':									// ������ �� �ְ�, W�� �ԷµǴ� ���
			print_head();
			PURPLE printf("                  ��");	// ���� �Է¹���
			ORIGINAL printf("\n");
			move_up();
			print_field();							// ���� �� ���
			break;

		case 'S':
		case 's':									// ������ �� �ְ�, S�� �ԷµǴ� ���
			print_head();
			PURPLE printf("                  ��");	// �Ʒ��� �Է¹���
			ORIGINAL printf("\n");
			move_down();
			print_field();       					// ���� �� ���
			break;

		case 'C':
		case 'c':									// ������ �Է¹��� ���
			print_head();
			if(new_player.chance>0)						// ������ ���Ҵٸ� 
			{
				PURPLE printf("        CHANCE : ���� Ƚ�� %dȸ", new_player.chance-1);
				ORIGINAL printf("\n");
				chance();							// ���� ��� 
			}
			else									// ������ �� ����ߴٸ� 
			{
				PURPLE printf("      CHANCE�� �� ����ϼ̽��ϴ�.");
				ORIGINAL printf("\n");
			}
			print_field();       					// ���� �� ���
			break;

		case 'U':
		case 'u':
			print_head();			
			if((here<1)||(new_player.stage[here]<2))		// �ǵ��� �� ���� ��� 
			{
				PURPLE printf("      �� �̻� �ǵ��� �� �����ϴ�.\n");
				print_field();
				break;
			}
			PURPLE printf("      	         UNDO");
			ORIGINAL printf("\n");
			here--;									// �迭�� ���� ���� 
			print_field();        					// �ǵ��� �� ���
			break;

		case 'R':
		case 'r':
			print_head();
			if(here>=4)								// �ǵ��� �� ���� ��� 
			{
				PURPLE printf("      �� �̻� �ǵ��� �� �����ϴ�.\n");
				print_field();
				break;
			}
			PURPLE printf("      	         REDO");
			ORIGINAL printf("\n");
			here++;									// �迭�� ���� ���� 
			print_field();        					// �ǵ��� �� ���
			break;

		default:									// �߸��� Ű�� �ԷµǴ� ���
			print_head();
			PURPLE printf("         �߸� �Է��ϼ̽��ϴ�.");
			ORIGINAL printf("\n");
			print_field();       					// ���� �� ���
			repeat();
	}
 } 

void repeat()										// �ݺ��� �Լ�(������ �⺻ �Լ�) 
{
	clear();
	
	dir = 0;
	dir = getch();

	if((dir == 'N')||(dir == 'n'))	main();	
	
	if((check() == 2)||(check() == 0)||(dir == 'X')||(dir == 'x'))	// ������ ���� ������ ��� 
	{
		ending();
		return;
	}
	
	if((dir=='P')||(dir=='p'))	ai();
	move();
	repeat();
}

void high_score()									// ���� ���� -> ���� ���� 
{
	int i, j, p, temp;

	for(i=0; i<5; i++)
	{
		num[5][i]=new_player.score[i];
	}

	for(i=0; i<6; i++)								// �̸��� ���� ��� 
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

	for(i=0; i<5; i++)								// ����
	{
		for(j=0; j<(6-i)-1; j++)
		{
			if(num[j][3] < num[j+1][3])
			{
				for (p = 0; p < 5; p++)
				{
					temp = num[j][p];
					num[j][p] = num[j+1][p];
					num[j+1][p] = temp;
				}
			}
		}
	}
} 

void ending()										// ����ǥ ��� �Լ� 
{
	print_head();
	ORIGINAL printf("\n");
	high_score();
	Sleep(600);
	printf("   ��������������������������������\n");
	printf("   ��  No.   ID    SCORE   STAGE ��\n");
	printf("   ��  1     %c%c%c   %5d     %3d ��\n", num[0][0], num[0][1], num[0][2], num[0][3], num[0][4]);	
	printf("   ��  2     %c%c%c   %5d     %3d ��\n", num[1][0], num[1][1], num[1][2], num[1][3], num[1][4]);		
	printf("   ��  3     %c%c%c   %5d     %3d ��\n", num[2][0], num[2][1], num[2][2], num[2][3], num[2][4]);		
	printf("   ��  4     %c%c%c   %5d     %3d ��\n", num[3][0], num[3][1], num[3][2], num[3][3], num[3][4]);	
	printf("   ��  5     %c%c%c   %5d     %3d ��\n", num[4][0], num[4][1], num[4][2], num[4][3], num[4][4]);
	printf( "   ��������������������������������\n   ��");
	RED printf("  0     %c%c%c   %5d     %3d", new_player.name_1, new_player.name_2, new_player.name_3, new_player.score, new_player.stage);
	ORIGINAL printf(" ��\n   ��������������������������������\n\n");
	Sleep(600);
	YELLOW printf("        NEW GAME : N, EXIT : X");
	retry();
}

void retry()										// ��õ� ����� �Լ� 
{
	int re=getch();
	if((re==78)||(re==110))			main();			// N�� �Է¹����� main�Լ� ù�κ����� -> ó������ 
	else if((re==88)||(re==120))	return;			// X�� �Է¹����� main�Լ� repeat ���� �κ����� -> ���� 
	else retry();									// �ٸ� Ű�� �Է¹����� �ٽ� �Է¹ޱ� 
}

void ai()
{
	int temp_score=new_player.score[4];
	int i, j, x, y, z;
	int pushto[3]={0, 0, 0};	
	
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			copy[i][j] = new_player.field[4][i][j];	// temp �迭�� ���� 

	for(x=0; i<3; i++)
	{
		for(y=0; j<4; j++)
		{
			pushto[x]=y;
			
			switch (pushto[0])						// �ѹ� �����̸� 
			{
				case 0:								// �������� �����̴� ���
				
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j + 1];		// ������ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j + 1] = 0;					// ������ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j + 1];		// ������ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j + 1] = 0;					// ������ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j + 1];		// ������ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j + 1] = 0;					// ������ĭ�� ����
						}
						if (copy[i][j] == copy[i][j + 1])		// �¿�� ���� ������
						{
							copy[i][j] += copy[i][j + 1];		// ����ĭ�� ������ĭ�� ���� ���ϰ�
							new_player.score[4] += copy[i][j];			// ���� �߰�
							copy[i][j + 1] = 0;					// ������ĭ�� ����
						}
					}
				}
				break;

				case 1:								// ���������� �����̴� ���
				
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = SIZE - 2; j > 0; j--)
					{
						if (copy[i][j] == 0)				// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j - 1] = 0;				// ����ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = SIZE - 2; j > 0; j--)
					{
						if (copy[i][j] == 0)				// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j - 1] = 0;				// ����ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = SIZE - 2; j > 0; j--)
					{
						if (copy[i][j] == 0)				// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j - 1] = 0;				// ����ĭ�� ����
						}
						if (copy[i][j] == copy[i][j - 1])	// �¿�� ���� ������
						{
							copy[i][j] += copy[i][j - 1];	// ������ĭ�� ����ĭ�� ���� ���ϰ�
							new_player.score[4] += copy[i][j];			// ���� �߰�
							copy[i][j - 1] = 0;				// ����ĭ�� ����
						}
					}
				}
				break;

				case 2:								// �������� �����̴� ���
				
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i + 1][j];		// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
							copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i + 1][j];		// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
							copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i + 1][j];		// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
							copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
						}
						if (copy[i][j] == copy[i + 1][j])		// ���Ϸ� ���� ������
						{
							copy[i][j] += copy[i + 1][j];		// ��ĭ�� �Ʒ�ĭ�� ���� ���ϰ�
							new_player.score[4] += copy[i][j];	// ���� �߰�
							copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
						}
					}
				}
				break;

				case 3:								// �Ʒ��� �����̴� ���

				for (i = SIZE - 2; i > 0; i--)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i - 1][j];		// ��ĭ�� ���� ��ĭ�� �ְ�
							copy[i - 1][j] = 0;					// ��ĭ�� ����
						}
					}
				}
				for (i = SIZE - 2; i > 0; i--)
				{
					for (j = 1; j < SIZE - 1; j++)
					{	
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i - 1][j];		// ��ĭ�� ���� ��ĭ�� �ְ�
							copy[i - 1][j] = 0;					// ��ĭ�� ����
						}
					}
				}
				for (i = SIZE - 2; i > 0; i--)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i - 1][j];		// ��ĭ�� ���� ��ĭ�� �ְ�
							copy[i - 1][j] = 0;					// ��ĭ�� ����
						}
						if (copy[i][j] == copy[i - 1][j])		// ���Ϸ� ���� ������
						{
							copy[i][j] += copy[i - 1][j];		// �Ʒ�ĭ�� ��ĭ�� ���� ���ϰ�
							new_player.score[4] += copy[i][j];			// ���� �߰�
							copy[i - 1][j] = 0;					// ��ĭ�� ����
						}
					}
				}
				break;
			}
			switch (pushto[1])						// �ι� �����̸� 
			{
				case 0:								// �������� �����̴� ���
				
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j + 1];		// ������ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j + 1] = 0;					// ������ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j + 1];		// ������ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j + 1] = 0;					// ������ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j + 1];		// ������ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j + 1] = 0;					// ������ĭ�� ����
						}
						if (copy[i][j] == copy[i][j + 1])		// �¿�� ���� ������
						{
							copy[i][j] += copy[i][j + 1];		// ����ĭ�� ������ĭ�� ���� ���ϰ�
							new_player.score[4] += copy[i][j];			// ���� �߰�
							copy[i][j + 1] = 0;					// ������ĭ�� ����
						}
					}
				}
				break;

				case 1:								// ���������� �����̴� ���
				
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = SIZE - 2; j > 0; j--)
					{
						if (copy[i][j] == 0)				// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j - 1] = 0;				// ����ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = SIZE - 2; j > 0; j--)
					{
						if (copy[i][j] == 0)				// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j - 1] = 0;				// ����ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = SIZE - 2; j > 0; j--)
					{
						if (copy[i][j] == 0)				// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j - 1] = 0;				// ����ĭ�� ����
						}
						if (copy[i][j] == copy[i][j - 1])	// �¿�� ���� ������
						{
							copy[i][j] += copy[i][j - 1];	// ������ĭ�� ����ĭ�� ���� ���ϰ�
							new_player.score[4] += copy[i][j];			// ���� �߰�
							copy[i][j - 1] = 0;				// ����ĭ�� ����
						}
					}
				}
				break;

				case 2:								// �������� �����̴� ���
				
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i + 1][j];		// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
							copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i + 1][j];		// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
							copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i + 1][j];		// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
							copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
						}
						if (copy[i][j] == copy[i + 1][j])		// ���Ϸ� ���� ������
						{
							copy[i][j] += copy[i + 1][j];		// ��ĭ�� �Ʒ�ĭ�� ���� ���ϰ�
							new_player.score[4] += copy[i][j];	// ���� �߰�
							copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
						}
					}
				}
				break;

				case 3:								// �Ʒ��� �����̴� ���

				for (i = SIZE - 2; i > 0; i--)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i - 1][j];		// ��ĭ�� ���� ��ĭ�� �ְ�
							copy[i - 1][j] = 0;					// ��ĭ�� ����
						}
					}
				}
				for (i = SIZE - 2; i > 0; i--)
				{
					for (j = 1; j < SIZE - 1; j++)
					{	
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i - 1][j];		// ��ĭ�� ���� ��ĭ�� �ְ�
							copy[i - 1][j] = 0;					// ��ĭ�� ����
						}
					}
				}
				for (i = SIZE - 2; i > 0; i--)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i - 1][j];		// ��ĭ�� ���� ��ĭ�� �ְ�
							copy[i - 1][j] = 0;					// ��ĭ�� ����
						}
						if (copy[i][j] == copy[i - 1][j])		// ���Ϸ� ���� ������
						{
							copy[i][j] += copy[i - 1][j];		// �Ʒ�ĭ�� ��ĭ�� ���� ���ϰ�
							new_player.score[4] += copy[i][j];			// ���� �߰�
							copy[i - 1][j] = 0;					// ��ĭ�� ����
						}
					}
				}
				break;
			}
			switch (pushto[2])						// ���� �����̸� 
			{
				case 0:								// �������� �����̴� ���
				
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j + 1];		// ������ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j + 1] = 0;					// ������ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j + 1];		// ������ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j + 1] = 0;					// ������ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j + 1];		// ������ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j + 1] = 0;					// ������ĭ�� ����
						}
						if (copy[i][j] == copy[i][j + 1])		// �¿�� ���� ������
						{
							copy[i][j] += copy[i][j + 1];		// ����ĭ�� ������ĭ�� ���� ���ϰ�
							new_player.score[4] += copy[i][j];			// ���� �߰�
							copy[i][j + 1] = 0;					// ������ĭ�� ����
						}
					}
				}
				break;

				case 1:								// ���������� �����̴� ���
				
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = SIZE - 2; j > 0; j--)
					{
						if (copy[i][j] == 0)				// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j - 1] = 0;				// ����ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = SIZE - 2; j > 0; j--)
					{
						if (copy[i][j] == 0)				// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j - 1] = 0;				// ����ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = SIZE - 2; j > 0; j--)
					{
						if (copy[i][j] == 0)				// ��ĭ�� ������
						{
							copy[i][j] = copy[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
							copy[i][j - 1] = 0;				// ����ĭ�� ����
						}
						if (copy[i][j] == copy[i][j - 1])	// �¿�� ���� ������
						{
							copy[i][j] += copy[i][j - 1];	// ������ĭ�� ����ĭ�� ���� ���ϰ�
							new_player.score[4] += copy[i][j];			// ���� �߰�
							copy[i][j - 1] = 0;				// ����ĭ�� ����
						}
					}
				}
				break;

				case 2:								// �������� �����̴� ���
				
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i + 1][j];		// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
							copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i + 1][j];		// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
							copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
						}
					}
				}
				for (i = 1; i < SIZE - 1; i++)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i + 1][j];		// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
							copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
						}
						if (copy[i][j] == copy[i + 1][j])		// ���Ϸ� ���� ������
						{
							copy[i][j] += copy[i + 1][j];		// ��ĭ�� �Ʒ�ĭ�� ���� ���ϰ�
							new_player.score[4] += copy[i][j];	// ���� �߰�
							copy[i + 1][j] = 0;					// �Ʒ�ĭ�� ����
						}
					}
				}
				break;

				case 3:								// �Ʒ��� �����̴� ���

				for (i = SIZE - 2; i > 0; i--)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i - 1][j];		// ��ĭ�� ���� ��ĭ�� �ְ�
							copy[i - 1][j] = 0;					// ��ĭ�� ����
						}
					}
				}
				for (i = SIZE - 2; i > 0; i--)
				{
					for (j = 1; j < SIZE - 1; j++)
					{	
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i - 1][j];		// ��ĭ�� ���� ��ĭ�� �ְ�
							copy[i - 1][j] = 0;					// ��ĭ�� ����
						}
					}
				}
				for (i = SIZE - 2; i > 0; i--)
				{
					for (j = 1; j < SIZE - 1; j++)
					{
						if (copy[i][j] == 0)					// ��ĭ�� ������
						{
							copy[i][j] = copy[i - 1][j];		// ��ĭ�� ���� ��ĭ�� �ְ�
							copy[i - 1][j] = 0;					// ��ĭ�� ����
						}
						if (copy[i][j] == copy[i - 1][j])		// ���Ϸ� ���� ������
						{
							copy[i][j] += copy[i - 1][j];		// �Ʒ�ĭ�� ��ĭ�� ���� ���ϰ�
							new_player.score[4] += copy[i][j];			// ���� �߰�
							copy[i - 1][j] = 0;					// ��ĭ�� ����
						}
					}
				}
				break;
			}
		
		if(check()==0)								// ������ �Է¹��� ���
		{
			print_head();
			if(new_player.chance>0)						// ������ ���Ҵٸ� 
			{
				PURPLE printf("        CHANCE : ���� Ƚ�� %dȸ", new_player.chance-1);
				ORIGINAL printf("\n");
				chance();							// ���� ��� 
			}
			else									// ������ �� ����ߴٸ� 
			{
				PURPLE printf("      CHANCE�� �� ����ϼ̽��ϴ�.");
				ORIGINAL printf("\n");
			}
			print_field();       					// ���� �� ���
			break;
		}
			
		}
	}
	Sleep(500);										// 0.5�� ������
    move();
    ORIGINAL printf("\n");
	print_field();       					        // ���� �� ���
	ai();
}

