/*
�뱸���а���б� 1109 ������
2�б� 2048 ������Ʈ 2�ܰ�
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h> 
#include <time.h>
#define COL GetStdHandle(STD_OUTPUT_HANDLE)				//�۾� ����  ����
#define BLACK SetConsoleTextAttribute(COL, 0x0000);  	//����
#define GREEN SetConsoleTextAttribute(COL, 0x0002);  	//�ʷϻ�
#define PURPLE SetConsoleTextAttribute(COL, 0x0005);  	//����� 
#define GOLD SetConsoleTextAttribute(COL, 0x0006);  	//�ݻ�
#define HIGH_GREEN SetConsoleTextAttribute(COL, 0x000a);//���λ�
#define SKY_BLUE SetConsoleTextAttribute(COL, 0x000b); 	//�ϴû�
#define RED SetConsoleTextAttribute(COL, 0x000c);  		//������
#define YELLOW SetConsoleTextAttribute(COL, 0x000e);  	//�����
#define MAGENTA SetConsoleTextAttribute(COL, 0x000d);	//���ֻ� 
#define ORIGINAL SetConsoleTextAttribute(COL, 0x000f); 	//���
#define SIZE 6											// �������� ũ�� ����
#define UP 72											// ����Ű ������ �ƽ�Ű�ڵ尪
#define DOWN 80 										// ����Ű �Ʒ����� �ƽ�Ű�ڵ尪
#define ENTER 13                                		// ����Ű�� �ƽ�Ű�ڵ尪 

int field[SIZE][SIZE];									// ������
int temp[5]={0,0,0,0,2};                    			// �÷��̾� ID(3�ڸ�)+����+�ܰ� 
int num[5][5];											// ��� ���� 
char dir;												// ����

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
	make_random();									// ������ ��ġ�� ���� ����
	make_random();									// ������ ��ġ�� ���� ���� 
	printf("\n");
	print_field();									// ���� ������ ��Ȳ ���
	repeat();										// ���� ����
	printf("         NEW GAME : Press N");
	int re=getch();
	if((re==78)||(re==110))	main();	
	system("pause");
}

void new_game()										// ���� �ʱ�ȭ 
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			field[i][j] = 0;
	}

	temp[4]=0;										// ���� �ʱ�ȭ 
	temp[5]=2;                    					// �ܰ� �ʱ�ȭ 
}

void scan_ID_1(int name)							// ID �Է¹޴� �Լ� 1 
{
    int key=0;
	system("cls");
	HIGH_GREEN printf("\n\n\n\n  ����������������������������������\n");
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

void scan_ID_2(int name)							// ID �Է¹޴� �Լ� 2
{
    int key=0;
	system("cls");
	HIGH_GREEN printf("\n\n\n\n  ����������������������������������\n");
	printf("  ��     [ USE ��, ��, ENTER ]    ��\n");
	printf("  ��        What's Your ID?       ��\n");
	printf("  ��                              ��\n  ��");
	GREEN printf("              ��              ");
	HIGH_GREEN printf("��\n  ��             ");
	if(name==64)   name=90;
	if(name==91)   name=65;
    GREEN printf("%c %c A", temp[0], name);
    HIGH_GREEN printf("            ��\n  ��");
    GREEN printf("              ��              ");
	HIGH_GREEN printf("��\n  ����������������������������������");
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

void scan_ID_3(int name)							// ID �Է¹޴� �Լ� 3
{
    int key=0;
	system("cls");
	HIGH_GREEN printf("\n\n\n\n  ����������������������������������\n");
	printf("  ��     [ USE ��, ��, ENTER ]    ��\n");
	printf("  ��        What's Your ID?       ��\n");
	printf("  ��                              ��\n  ��");
	GREEN printf("                ��            ");
	HIGH_GREEN printf("��\n  ��             ");
	if(name==64)   name=90;
	if(name==91)   name=65;
    GREEN printf("%c %c %c", temp[0], temp[1], name);
    HIGH_GREEN printf("            ��\n  ��");
    GREEN printf("                ��            ");
	HIGH_GREEN printf("��\n  ����������������������������������");
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

void print_loading(int n)							// �ε�â ��� �Լ� 
{
	system("cls");
	ORIGINAL printf("\n\n\n\n\n\n          L O A D I N G . . .\n         ");
	for (int j = 10-n; j>0; j--)	printf("��");
	for(int i = 0; i<n; i++)		printf("��");
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
	printf("  ����������������������������������\n");
	YELLOW printf(" [����:�뱸���а���б� 1109 ������]\n");
	ORIGINAL printf("�������������������ڦ�����������������\n");
	printf("����(W), �Ʒ�(S), ����(A), ������(D)��\n");
	printf("��     �� ����(N), ���� ����(X)     ��\n");
	printf("��������������������������������������\n");	
}

void print_field()									// �������� ����ϴ� �Լ�
{
	MAGENTA printf(" ID : %c%c%c SCORE : %5d�� STAGE : %3d", temp[0], temp[1], temp[2], temp[3], temp[4]/2);
    ORIGINAL printf("\n");	
	for (int i = 1; i<5; i++)
	{
		if (i == 1)
			printf("  ����������������������������������\n");
		else
			printf("  ����������������������������������\n");

		for (int j = 1; j<5; j++)
		{
			if (field[i][j] == 0)
				printf("  ��    ");
			else
				printf("  ��%4d", field[i][j]);
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
			if (field[i][j] == 0)				// ��ĭ�� ������
			{
				field[i][j] = field[i + 1][j];	// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
				field[i + 1][j] = 0;			// �Ʒ�ĭ�� ����
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// ��ĭ�� ������
			{
				field[i][j] = field[i + 1][j];	// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
				field[i + 1][j] = 0;			// �Ʒ�ĭ�� ����
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// ��ĭ�� ������
			{
				field[i][j] = field[i + 1][j];	// �Ʒ�ĭ�� ���� ��ĭ�� �ְ�
				field[i + 1][j] = 0;			// �Ʒ�ĭ�� ����
			}
			if (field[i][j] == field[i + 1][j])	// ���Ϸ� ���� ������
			{
				field[i][j] += field[i + 1][j];	// ��ĭ�� �Ʒ�ĭ�� ���� ���ϰ�
				temp[3] += field[i][j];			// ���� �߰�
				field[i + 1][j] = 0;			// �Ʒ�ĭ�� ����
			}
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] != field[i][j])	check = 1;	// �����̱� ���� ������ �İ� ���� �ʴٸ�
		}
	}

	if (check)	make_random();	// ���� ����
}

void move_down()									// �Ʒ��� �̴� �Լ�
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
			if (field[i][j] == 0)				// ��ĭ�� ������
			{
				field[i][j] = field[i - 1][j];	// ��ĭ�� ���� ��ĭ�� �ְ�
				field[i - 1][j] = 0;				// ��ĭ�� ����
			}
		}
	}
	for (int i = SIZE - 2; i > 0; i--)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// ��ĭ�� ������
			{
				field[i][j] = field[i - 1][j];	// ��ĭ�� ���� ��ĭ�� �ְ�
				field[i - 1][j] = 0;				// ��ĭ�� ����
			}
		}
	}
	for (int i = SIZE - 2; i > 0; i--)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// ��ĭ�� ������
			{
				field[i][j] = field[i - 1][j];	// ��ĭ�� ���� ��ĭ�� �ְ�
				field[i - 1][j] = 0;				// ��ĭ�� ����
			}
			if (field[i][j] == field[i - 1][j])	// ���Ϸ� ���� ������
			{
				field[i][j] += field[i - 1][j];	// �Ʒ�ĭ�� ��ĭ�� ���� ���ϰ�
				temp[3] += field[i][j];			// ���� �߰�
				field[i - 1][j] = 0;				// ��ĭ�� ����
			}
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] != field[i][j])	check = 1;	// �����̱� ���� ������ �İ� ���� �ʴٸ�
		}
	}

	if (check)	make_random();	// ���� ����
}

void move_right()									// ���������� �̴� �Լ�
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
			if (field[i][j] == 0)				// ��ĭ�� ������
			{
				field[i][j] = field[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
				field[i][j - 1] = 0;				// ����ĭ�� ����
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = SIZE - 2; j > 0; j--)
		{
			if (field[i][j] == 0)				// ��ĭ�� ������
			{
				field[i][j] = field[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
				field[i][j - 1] = 0;				// ����ĭ�� ����
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = SIZE - 2; j > 0; j--)
		{
			if (field[i][j] == 0)				// ��ĭ�� ������
			{
				field[i][j] = field[i][j - 1];	// ����ĭ�� ���� ��ĭ�� �ְ�
				field[i][j - 1] = 0;				// ����ĭ�� ����
			}
			if (field[i][j] == field[i][j - 1])	// �¿�� ���� ������
			{
				field[i][j] += field[i][j - 1];	// ������ĭ�� ����ĭ�� ���� ���ϰ�
				temp[3] += field[i][j];			// ���� �߰�
				field[i][j - 1] = 0;				// ����ĭ�� ����
			}
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] != field[i][j])	check = 1;	// �����̱� ���� ������ �İ� ���� �ʴٸ�
		}
	}

	if (check)	make_random();	// ���� ����
}

void move_left()									// �������� �̴� �Լ�
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
			if (field[i][j] == 0)				// ��ĭ�� ������
			{
				field[i][j] = field[i][j + 1];	// ������ĭ�� ���� ��ĭ�� �ְ�
				field[i][j + 1] = 0;			// ������ĭ�� ����
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// ��ĭ�� ������
			{
				field[i][j] = field[i][j + 1];	// ������ĭ�� ���� ��ĭ�� �ְ�
				field[i][j + 1] = 0;			// ������ĭ�� ����
			}
		}
	}
	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (field[i][j] == 0)				// ��ĭ�� ������
			{
				field[i][j] = field[i][j + 1];	// ������ĭ�� ���� ��ĭ�� �ְ�
				field[i][j + 1] = 0;			// ������ĭ�� ����
			}
			if (field[i][j] == field[i][j + 1])	// �¿�� ���� ������
			{
				field[i][j] += field[i][j + 1];	// ����ĭ�� ������ĭ�� ���� ���ϰ�
				temp[3] += field[i][j];			// ���� �߰�
				field[i][j + 1] = 0;			// ������ĭ�� ����
			}
		}
	}

	for (int i = 1; i < SIZE - 1; i++)
	{
		for (int j = 1; j < SIZE - 1; j++)
		{
			if (copy[i][j] != field[i][j])	check = 1;	// �����̱� ���� ������ �İ� ���� �ʴٸ�
		}
	}

	if (check)	make_random();	// ���� ����
}

int check()											// ���������� Ȯ���ϴ� �Լ� 
{
	int end = 0;
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			if (field[i][j] == 0)
				end = 1;						// �� ĭ�� ������ 1 ��ȯ

			if (field[i][j] == field[i + 1][j])
				end = 1;						// ���Ʒ��� ���� ���� ������ 1 ��ȯ

			if (field[i][j] == field[i][j + 1])
				end = 1;						// �¿�� ���� ���� ������ 1 ��ȯ

			if (field[i][j] == 2048)
				end = 2;						// 2048�� ��������� 2 ��ȯ
		}
	}
	return end;
}

void clear()										// �𼭸��� �ʱ�ȭ ��Ű�� �Լ� 
{
	for (int i = 0; i < SIZE; i++)
	{
		field[i][0] = 0;						// �� �𼭸� �ʱ�ȭ (�����Ⱚ ����)
		field[i][SIZE-1] = 0;					// �� �𼭸� �ʱ�ȭ (�����Ⱚ ����)
	}

	for (int j = 0; j < SIZE; j++)
	{
		field[0][j] = 0;						// �� �𼭸� �ʱ�ȭ (�����Ⱚ ����)
		field[SIZE-1][j] = 0;					// �� �𼭸� �ʱ�ȭ (�����Ⱚ ����)
	}
}

void make_random()									// �������� ���ڸ� ������ִ� �Լ�
{
	int i, j;							//for�� ���� ���� ���� 
	int n=0;							//n: ������ ���� 0�� ������ Ȯ���ϱ� ���� ���� ����
	srand((unsigned)time(NULL));		//���� ������ ���� �ڵ� 
	for(i=1; i<SIZE-1; i++)
	{
		for(j=1; j<SIZE-1; j++)
		{
			if(field[i][j]==0) n++;		//�������� 0�� ������ Ȯ���Ѵ�. 
		}
	}
	
	for(i=1; i<SIZE-1; i++)
	{
		for(j=1; j<SIZE-1; j++)
		{
			if(field[i][j]==0)			// 0�� ��ġ���� ���ο� ���ڸ� �־�� �Ѵ�. 
			{
				if(rand()%n ==0)		// 1/n�� Ȯ���� �� ��ġ�� ���ο� ���ڰ� ����. 
				{
					if(rand()%5 == 4) field[i][j]=4;	// 20%�� Ȯ���� 4
					else field[i][j]=2;					// 80%�� Ȯ���� 2
					return;				// ���ڸ� �ϳ� �־����� ���������� �����Ų��. 
				}
				--n;					// ��� ĭ�� ���ڰ� ���� ���� Ȯ���� ���� ���ֱ� ���� 1�� ���ش�.
			}
		}
	}
}

void repeat()										// �ݺ��� �Լ� 
{
	clear();
	
	dir=0;
	scanf("%c", &dir); 
	
	if((dir == 'N')||(dir == 'n'))	main();	
	
	if((check() == 2)||(check() == 0)||(dir == 'X')||(dir == 'x'))	// ������ ���� ������ ��� 
	{
		ending();
		return;
	}
	
	switch (dir)								// ��� �������� �а����� �Է¹ޱ�
	{
	case 'A':
	case 'a':
		print_head();
		PURPLE printf("                  ��");					// ���� �Է¹���
		ORIGINAL printf("\n");
		break;
	case 'D':
	case 'd':
		print_head();
		PURPLE printf("                  ��");					// ������ �Է¹���
		ORIGINAL printf("\n");
		break;
	case 'W':
	case 'w':
		print_head();
		PURPLE printf("                  ��");					// ���� �Է¹���
		ORIGINAL printf("\n");
		break;
	case 'S':
	case 's':
		print_head();
		PURPLE printf("                  ��");					// �Ʒ��� �Է¹���
		ORIGINAL printf("\n");
		break;
	}

	if ((dir == 'W')||(dir=='w'))								// ������ �� �ְ�, �谡 �ԷµǴ� ��� ���� �δ� 
	{
		move_up();
		print_field();	                        // ���� �� ���
	}

	if ((dir == 'S')||(dir=='s'))								// ������ �� �ְ�, �鰡 �ԷµǴ� ��� �Ʒ��� �δ� 
	{
		move_down();
		print_field();       					// ���� �� ���
	}

	if ((dir == 'D')||(dir =='d'))								// ������ �� �ְ�, �氡 �ԷµǴ� ��� ���������� �δ� 
	{
		move_right();
		print_field();       					// ���� �� ���
	}

	if ((dir == 'A')||(dir == 'a'))								// ������ �� �ְ�, �簡 �ԷµǴ� ��� �������� �δ� 
	{
		move_left();
		print_field();        					// ���� �� ���
	}
	
	temp[4]++;
	repeat(); 
}

/*
2016.09.30 20:40
���� ������� �����ϴ� �� ������ �ʿ�.
���̵� �Է�, ���̵� ���� �ܰ� ���, ����ǥ ���
�ּ� �߰� �� ����, ���� ���� ��� ����, �̴� ��� ����
���� �ʱ�ȭ�� ������ �ʱ�ȭ �߰�
���� ��� ����(2048 ����, ������ �� ���� ���, X �Է¹��� ��� : ���� ���� -> ����ǥ ���, ����� �����) 
*/

void high_score()
{
	int i, j, temp[6];
	int check = 0;
	
	for(i=0; i<5; i++)								// ����
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
					check = 1; 							// �������� ��ȯ�� �Ͼ
				}
			}
		}
 		if(check==0) break;							// �������� ��ȯ�� ������ �ߴ� 
	}
} 

void ending()										// ����ǥ ��� �Լ� 
{
	print_head();
	ORIGINAL printf("\n");
	Sleep(750);
	printf("   ��������������������������������\n");
	printf("   ��  No.   ID    SCORE   STAGE ��\n");
	printf("   ��  1     %c%c%c   %5d     %3d ��\n", num[0][0], num[0][1], num[0][2], num[0][3], num[0][4]);	
	printf("   ��  2     %c%c%c   %5d     %3d ��\n", num[1][0], num[1][1], num[1][2], num[1][3], num[1][4]);		
	printf("   ��  3     %c%c%c   %5d     %3d ��\n", num[2][0], num[2][1], num[2][2], num[2][3], num[2][4]);		
	printf("   ��  4     %c%c%c   %5d     %3d ��\n", num[3][0], num[3][1], num[3][2], num[3][3], num[3][4]);	
	printf("   ��  5     %c%c%c   %5d     %3d ��\n", num[4][0], num[4][1], num[4][2], num[4][3], num[4][4]);
	printf( "   ��������������������������������\n   ��");
	RED printf("  0     %c%c%c   %5d     %3d", temp[0], temp[1], temp[2], temp[3], temp[4]);
	ORIGINAL printf(" ��\n   ��������������������������������\n");
	Sleep(700);
	return;
} 
