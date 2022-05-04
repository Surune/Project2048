/*
�뱸���а���б� 1109 ������
2�б� 2048 ������Ʈ 1�ܰ�
*/
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h> 
#include <time.h>
#define COL GetStdHandle(STD_OUTPUT_HANDLE)				//�۾� ����  ����
#define BLACK SetConsoleTextAttribute(COL, 0x0000);  	//����
#define GREEN SetConsoleTextAttribute(COL, 0x0002);  	//�ʷϻ�
#define GOLD SetConsoleTextAttribute(COL, 0x0006);  	//�ݻ�
#define ORIGINAL SetConsoleTextAttribute(COL, 0x0007); 	//���
#define HIGH_GREEN SetConsoleTextAttribute(COL, 0x000a);//���λ�
#define SKY_BLUE SetConsoleTextAttribute(COL, 0x000b); 	//�ϴû�
#define RED SetConsoleTextAttribute(COL, 0x000c);  		//������
#define YELLOW SetConsoleTextAttribute(COL, 0x000e);  	//�����
#define SIZE 6									// �������� ũ�� ����

int field[SIZE][SIZE];							// ������
int n = 10;
char dir;										// ����
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
	make_random();									// ������ ��ġ�� ���� ����
	make_random();
	print_field();									// ���� ������ ��Ȳ ���
	scanf("%c", &dir); 
	repeat();										// ���� ����
	if((dir == 'N')||(dir == 'n'))	main();
	printf("\n");
	if((dir == 'X')||(dir == 'x')) return 0;
	system("pause");
}

void print_loading()
{
	system("cls");
	ORIGINAL printf("\n\n\n\n\n\n          L O A D I N G . . .\n         ");
	for (int j = 10-n; j>0; j--)	printf("��");
	for(int i = 0; i<n; i++)		printf("��");
	n--;
	Sleep(700);
	if (n < 0)	return;
	else		print_loading();
}

void print_head()									// �⺻������ ����� �͵�
{
	system("cls");
	printf("  ����������������������������������\n  ��");
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
	YELLOW printf(" [���� : �뱸���а���б� 1109 ������]\n");
	ORIGINAL printf("�������������������ڦ�����������������\n");
	printf("       ���ϴ� Ű�� �Է����ּ���     \n");
	printf(" [ ��(W), �Ʒ�(S), ����(A), ������(D) ]\n");
	printf(" [      �� ����(N), ���� ����(X)      ]\n");
	printf("��������������������������������������\n");	
}

void print_field()								// �������� ����ϴ� �Լ�
{
	printf("\n");
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
	printf("\n");
}

void move_up()									// ���� �̴� �Լ�
{	
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
				field[i + 1][j] = 0;			// �Ʒ�ĭ�� ����
			}
		}
	}
}

void move_down()								// �Ʒ��� �̴� �Լ�
{	
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
				field[i - 1][j] = 0;				// ��ĭ�� ����
			}
		}
	}
}

void move_right()								// ���������� �̴� �Լ�
{	
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
				field[i][j - 1] = 0;				// ����ĭ�� ����
			}
		}
	}
}

void move_left()								// �������� �̴� �Լ�
{	
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
				field[i][j + 1] = 0;			// ������ĭ�� ����
			}
		}
	}
}

int check()										// ���������� Ȯ���ϴ� �Լ� 
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

void clear()									// �𼭸��� �ʱ�ȭ ��Ű�� �Լ� 
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

void make_random()						// �������� ���ڸ� ������ִ� �Լ��̴�. 
{
	int i, j;							//for�� ���� ���� ���� 
	int n=0;							//n�� ������ ���� 0�� ������ Ȯ���ϱ� ���� ���� �Լ��̴�. 
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
					if(rand()%5 == 4) field[i][j]=4;	// 20%�� Ȯ���� 4�� ����. 
					else field[i][j]=2;					// 80%�� Ȯ���� 2�� ����.
					return;				// ���ڸ� �ϳ� ���� �־����� ���������� �����Ų��. 
				}
				--n;					// ��� ĭ�� ���ڰ� ���� ���� Ȯ���� ���� ���ֱ� ���� 1�� ���ش�.
			}
		}
	}
}

void repeat()
{
	clear();
	
	if (check() == 2)				// 2048�� ��������ٸ�
	{
		print_head();
		GREEN printf("\n\n\n\n\n\n	    You Win! 'O'\n\n\n\n\n");
		return;									// ���� ����
	}
	if (check() == 0)				// ������ �� ���ٸ�
	{
		print_head();
		RED	printf("\n\n\n\n\n\n	    Game Over T_T\n\n\n\n\n");
		return;									// ���� ���� 
	}

	switch (dir)								// ��� �������� �а����� �Է¹ޱ�
	{
	case 'A':
	case 'a':
		print_head();
		printf("                  ��");					// ���� �Է¹���
		break;
	case 'D':
	case 'd':
		print_head();
		printf("                  ��");					// ������ �Է¹���
		break;
	case 'W':
	case 'w':
		print_head();
		printf("                  ��");					// ���� �Է¹���
		break;
	case 'S':
	case 's':
		print_head();
		printf("                  ��");					// �Ʒ��� �Է¹���
		break;
	}

	if ((dir == 'W')||(dir=='w'))								// end�� 1�̸� ������ �� �ְ�, �谡 �ԷµǴ� ��� ���� �δ� 
	{
		move_up();
		move_up();
		move_up();
		make_random();							// ������ ��ġ�� 2 Ȥ�� 4 ����
		print_field();	                        // ���� �� ���
	}

	if ((dir == 'S')||(dir=='s'))							// end�� 1�̸� ������ �� �ְ�, �鰡 �ԷµǴ� ��� ���� �δ� 
	{
		move_down();
		move_down();
		move_down();
		make_random();							// ������ ��ġ�� 2 Ȥ�� 4 ����
		print_field();       					// ���� �� ���
	}

	if ((dir == 'D')||(dir =='d'))						// end�� 1�̸� ������ �� �ְ�, �氡 �ԷµǴ� ��� ���� �δ� 
	{
		move_right();
		move_right();
		move_right();
		make_random();							// ������ ��ġ�� 2 Ȥ�� 4 ����
		print_field();       					// ���� �� ���.
	}

	if ((dir == 'A')||(dir == 'a'))							// end�� 1�̸� ������ �� �ְ�, �簡 �ԷµǴ� ��� ���� �δ� 
	{
		move_left();
		move_left();
		move_left();
		make_random();							// ������ ��ġ�� 2 Ȥ�� 4 ����
		print_field();        					// ���� �� ���. 
	}
}