#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define N 65

int i=0;//��ǰ�˺ű��
int flag1=0;//��¼�ɹ����
struct user
{
char user_Name[6];
char user_Pass[7];
char user_mibao[11];
}stu[3]={{"A0001","111111","liutao"},{"A0002","222222","wangqibing"},{"admin","333333","liuwang"}};//��ʼ���û����Ͷ�Ӧ����

int status[N][N]={{0},{0}};//��¼�������,0�ޣ�1����/��ң�2Ϊ����/���� 
int flag=0;//�ж���Ӯ 
int direct[2];//����
int Value1[N][N]={{0},{0}};//����Ȩֵ 
int Value2[N][N]={{0},{0}};//����Ȩֵ
int regrex,regrey,regrex1,regrey1; 
int count=0;//������������ 

void chess_board();//��ӡ���� 
void red_movexy();//�������ƶ����
void white_movexy();//�����ƶ���� 
void red_chess(int x,int y);//����
void white_chess(int x,int y);//����  
void print_Passwd();//��֤���� 
void xiugai_Passwd();//�޸����� 
void denglu();//��¼���� 
void zhaohui();//�һغ��� �� 

void man_man();//���˶�ս 
void man_machine();//�˻���ս
int judge_chess(int x,int y);//�ж����λ���Ƿ��¹� 
int judge_winner(int x,int y,int temp);//�ж���Ӯ 
void Regret();//���庯�� 
void sb();//������Ϸ���溯�� 
void regame(int &flag);//������Ϸ �� 

void machine_attack();//���Խ���Ȩֵ 
void machine_defend();//���Է���Ȩֵ 
void find_position();//Ѱ�����Ȩֵ �� 
 

 

void regame(int &flag)
{  
	for(int i=0;i<N;i++)
	for(int j=0;j<N;j++)
	status[i][j]=0;
	flag=0; 
}

void BackGround(unsigned int ForeColor, unsigned int BackGroundColor)  //��ɫ 
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);  //��ȡ����̨�ľ��
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//�ı䵱ǰ���ı�����������ɫ
}

void gotoxy(int x, int y)    //��꺯�� 
{
	HANDLE handle;
	COORD coord;   //��ȡ������ṹ��
	coord.X = x;
	coord.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);  //��ȡ����̨�����ֵΪ-11
	SetConsoleCursorPosition(handle, coord);   //�ƶ���굽x��y��
}

void chess_board()//��ӡ���� 
{
	int i,j;
	for(i=0;i<=30;i++)
	    for(j=0;j<=60;j+=4)
	    {
	    	gotoxy(j,i);
	    	printf("|");
		}
	for(i=0;i<=30;i+=2)
	    for(j=1;j<=57;j+=4)
	    {
	    	gotoxy(j,i);
	    	printf("---");
		}
}

void chess_menu()//��ӡ�����ԵĲ˵� 
{
	int i,j;
	for(i=1;i<=29;i++)
	{
		gotoxy(67,i);
		printf("||");
	}
	for(i=1;i<=29;i++)
	{
		gotoxy(89,i);
		printf("||");
	}
	gotoxy(69,1);
	printf("--------------------");
	gotoxy(69,29);
	printf("--------------------");
	gotoxy(75,3);
	printf("ģ   ʽ");
}

void red_movexy()//�����ƶ���� 
{
	loop2:gotoxy(direct[0],direct[1]);
	char key='y';
	int temp;
	while(key!=' ')
	{
	    key=getch();
		switch(key)
		{
			case 'W':
    		case 'w':
	    		direct[1]-=2;
	    		if(direct[1]<=1)
	    		    direct[1]=1;
    			break;
    		case 's':
    		case 'S':
    			direct[1]+=2;
	    		if(direct[1]>=29)
	    		    direct[1]=29;
    			break;
    		case 'a':
    		case 'A':
	    		direct[0]-=4;
	    		if(direct[0]<=2)
	    		    direct[0]=2;
	    		break;
    		case 'd':
    		case 'D':
	    		direct[0]+=4;
	    		if(direct[0]>=58)
	    		    direct[0]=58;
    			break;
    		case 'q':
    		case 'Q':
    		{ 
				int message=MessageBox(NULL,"�Ƿ�ȷ�����壿","������ʾ",MB_OKCANCEL);
		        if(IDCANCEL==message)
					break;
			    if(IDOK==message)
			    {
			    	Regret();
    				break;
    			}
    		}
    	}
    	gotoxy(direct[0],direct[1]);
    }
        temp=judge_chess(direct[1],direct[0]);
	    if(temp==1)
	    {
	    	gotoxy(70,22);
	    		BackGround(4, 0);
				printf("�����Ѿ������¹���");
			goto loop2;
		}
}

void white_movexy()//�����ƶ���� 
{
	loop1:gotoxy(direct[0],direct[1]);
	char key='y';
	int temp;
	while(key!='0')
	{
	    key=getch();
		switch(key)
		{
    		case 72:
	    		direct[1]-=2;
	    		if(direct[1]<=1)
	    		    direct[1]=1;
    			break;
    		case 80:
    			direct[1]+=2;
	    		if(direct[1]>=29)
	    		    direct[1]=29;
    			break;
    		case 75:
	    		direct[0]-=4;
	    		if(direct[0]<=2)
	    		    direct[0]=2;
	    		break;
    		case 77:
	    		direct[0]+=4;
	    		if(direct[0]>=58)
	    		    direct[0]=58;
    			break;
    		case 'B':
    		case 'b':
    		{ 
				int message=MessageBox(NULL,"�Ƿ�ȷ�����壿","������ʾ",MB_OKCANCEL);
		        if(IDCANCEL==message)
					break;
			    if(IDOK==message)
			    {
			    	Regret();
    				break;
    			}
    		}
    	}
    	gotoxy(direct[0],direct[1]);
    }
        temp=judge_chess(direct[1],direct[0]);
	    if(temp==1)
	    {
	    	gotoxy(70,22);
	    		BackGround(4, 0);
				printf("�����Ѿ������¹���");
			goto loop1;
		}
}

void red_chess(int x,int y)//��ӡ���� 
{
	BackGround(4,0);
	regrex=x;//��¼��һ���ӵ�λ�� ,������� 
	regrey=y;
	count++;
	printf("��");
	status[x][y]=1;
}

void white_chess(int x,int y)//��ӡ����
{
	BackGround(7,0);
	regrex1=x;
	regrey1=y;
	printf("��");
	count++;
	status[x][y]=2;
}

void machine_chess(int x,int y)//��������
{
	BackGround(7,0);
	status[x][y]=2;
	regrex1=x;
	regrey1=y;
	count++;
	gotoxy(y,x);
	printf("��");
}

int judge_chess(int x,int y)//�ж�����ط��Ƿ�������
{
	if(status[x][y]==0)
		return 0;
	else
		return 1;
} 

int judge_winner(int x,int y,int temp)//�ж���Ӯ 
{ 
	int i,j,n1,n2;
	n1=n2=0;
	for(i=x,j=y+4;j<=58;j+=4)//��
	{
		if(status[i][j]==temp)
		    n1++;
		else
		    break;
	}
	for(i=x,j=y;j>=2;j-=4)//��
	{
		if(status[i][j]==temp)
		    n2++;
		else
		    break;
	}
	if(n1+n2>=5)
	    return temp;
	n1=n2=0;
	for(i=x,j=y;i>=1;i-=2)//�� 
	{
		if(status[i][j]==temp)
		    n1++;
		else
		    break;
	}
	for(i=x+2,j=y;i<=30;i+=2)//�� 
	{
		if(status[i][j]==temp)
		    n2++;
		else
		    break;
	}
	if(n1+n2>=5)
	    return temp;
	n1=n2=0;
	for(i=x-2,j=y+4;i>=1&&j<=58;i-=2,j+=4)//���� 
	{
		if(status[i][j]==temp)
		    n1++; 
		else
		    break;
	}
	for(i=x,j=y;i<=30&&j>=2;i+=2,j-=4)//����
	{
		if(status[i][j]==temp)
		    n2++; 
		else
		    break;
	}
	if(n1+n2>=5)
	    return temp;
	n1=n2=0;
	for(i=x,j=y;i>=0&&j>=0;i-=2,j-=4)//���� 
	{
		if(status[i][j]==temp)
		    n1++; 
		else
		    break;
	}
	for(i=x+2,j=y+4;i<=30&&j<=58;i+=2,j+=4)//����
	{
		if(status[i][j]==temp)
		    n2++; 
		else
		    break;
	}
	if(n1+n2>=5)
	    return temp;
	return 0;
}

void machine_attack()//���Խ���Ȩֵ �������ڷ��� 
{
	int i1,j1;
	int k1,k2,k;
	for(int i=1;i<=30;i+=2)
	{
		for(int j=2;j<=58;j+=4)
		{
			if(status[i][j])
				Value1[i][j]=0;
			if(status[i][j]==0)//Ѱ�ҿ�λ 
			{
				k1=k2=0;
				for(i1=i,j1=j-4;j1>=2;j1-=4)//������Ѱ�ҵ���������
				{
					if(status[i1][j1]==2)
						k1++;
					else
						break;
				}
				for(i1=i,j1=j+4;j1<=58;j1+=4)//������Ѱ�ҵ���������
				{
					if(status[i1][j1]==2)
						k2++;
					else
						break;
				}
				k=k1>k2? k1:k2;//k=������������� 
				k1=k2=0;
				for(i1=i-2,j1=j;i1>=1;i1-=2)//������Ѱ�ҵ���������
				{
					if(status[i1][j1]==2)
						k1++;
					else
						break;
				}
				for(i1=i+2,j1=j;i1<=30;i1+=2)//������Ѱ�ҵ���������
				{
					if(status[i1][j1]==2)
						k2++;
					else
						break;
				}
				k1=k1>k2? k1:k2;
				k=k>k1? k:k1;
				k1=k2=0;
				for(i1=i-2,j1=j-4;i1>=0&&j1>=0;i1-=2,j1-=4)//��������Ѱ�ҵ���������
				{
					if(status[i1][j1]==2)
						k1++;
					else
						break;
				}
				for(i1=i+2,j1=j+4;i1<=30&&j1<=58;i1+=2,j1+=4)//��������Ѱ�ҵ���������
				{
					if(status[i1][j1]==2 )
						k2++;
					else
						break;
				}
				k1=k1>k2? k1:k2;
				k=k>k1?k:k1;
				k1=k2=0;
				for(i1=i+2,j1=j-4;i1<=30&&j1>=2;i1+=2,j1-=4)//��������Ѱ�ҵ���������
				{
					if(status[i1][j1]==2)
						k1++;
					else
						break;
				}
				for(i1=i-2,j1=j+4;i1>=1&&j1<=58;i1-=2,j1+=4)//��������Ѱ�ҵ���������
				{
					if(status[i1][j1]==2)
						k2++;
					else
						break;
				}
				k1=k1>k2? k1:k2;
				k=k>k1?k:k1;
				switch(k) //k�ǰ˸��������������� 
				{ 
					case 3:
						Value1[i][j]=15;break;                       
					case 4:
						Value1[i][j]=25;break; 
					default:
						Value1[i][j]=3+2*k;break;
				}
			}
		}
	}
}

void machine_defend()//����Ȩֵ
{
	int i1, j1;
	int k1,k2,k;
	for(int i=1;i<=30;i+=2)
	{
		for(int j=2;j<=58;j+=4)
		{
			if(status[i][j])
				Value2[i][j]=0;
			if(status[i][j]==0)
			{
				k1=k2=0;
				for(i1=i,j1=j-4;j1>=2;j1-=4)//������Ѱ�����������
				{
					if(status[i1][j1]==1)
						k1++;
					else
						break;
				}
				for(i1=i,j1=j+4;j1<=58;j1+=4)//������Ѱ�����������
				{
					if(status[i1][j1]==1)
						k2++; 
					else
						break;
				}
				k=k1>k2? k1:k2;
				k1=k2=0;
				for(i1=i-2,j1=j;i1>=1;i1-=2)//������Ѱ�����������
				{
					if(status[i1][j1]==1)
						k1++;
					else
						break;
				}
				for(i1=i+2,j1=j;i1<=30;i1+=2)//������Ѱ�����������
				{
					if(status[i1][j1]==1)
						k2++;
					else
						break;
				}
				k1=k1>k2? k1:k2;
				k=k>k1?k:k1;
				k1=k2=0;
				for(i1=i-2,j1=j-4;i1>=1&&j1>=2;i1-=2,j1-=4)//��������Ѱ�����������
				{
					if(status[i1][j1]==1)
						k1++;
					else
						break;
				}
				for(i1=i+2,j1=j+4;i1<=30&&j1<=58;i1+=2,j1+=4)//��������Ѱ�����������
				{
					if(status[i1][j1]==1)
						k2++;
					else
						break;
				}
				k1=k1>k2? k1:k2;
				k=k>k1?k:k1;
				k1=k2=0;
				for(i1=i+2,j1=j-4;i1<=30&&j1>=2;i1+=2,j1-=4)//��������Ѱ�����������
				{
					if(status[i1][j1]==1)
						k1++;
					else
						break;
				}
				for(i1=i-2,j1=j+4;i1>=1&&j1<=58;i1-=2,j1+=4)//��������Ѱ�����������
				{
					if(status[i1][j1]==1)
						k2++;
					else
						break;
				}
				k1=k1>k2? k1:k2;
				k=k>k1?k:k1;
			    switch(k)
				{
					case 3:
						Value2[i][j]=10;break;                 
					case 4:                                       
						Value2[i][j]=20;break;
					default:
						Value2[i][j]=2+k*2;
				}
			}
		}
	}
}

void find_position()//�ҵ����м�ֵ��λ��
{
	int k1=0, k2=0;
	int i, j, max=0;
	for( i=1;i<=30;i+=2)
		for( j=2;j<=58;j+=4)//����Ȩֵ�ж� 
		{
			if(max<=Value1[i][j])
			{
				max=Value1[i][j];
				k1=i;
				k2=j;
			}
		}
	for( i=1;i<=30;i+=2)//����Ȩֵ�ж� 
		for( j=2;j<=58;j+=4)
		{
			if(max<=Value2[i][j])
			{
				max=Value2[i][j];
				k1=i;
				k2=j;
			}
		}
	direct[1]=k1;  //���ҵ���λ�ô������
	direct[0]=k2;
}

void man_man()//���˶�սģʽ
{
	loop5:system("cls");
	char key;
	int control;
	gotoxy(35, 3);
	printf("1.�� �� �� ��");
	
	gotoxy(35, 5);
	printf("2.�� �� �� ��");
	
	gotoxy(35,7);
	printf("3.������һ����"); 
	
	gotoxy(35, 9);
	printf("(������Ӧ���ѡ��)");
	key=getch();
	system("cls");
	if(key=='1')
		control=1;
	else if(key=='2')
		control=-1;
	else if(key=='3')
	    sb();
	else
		goto loop5;
	gotoxy(70,5);
	printf("   �� �� �� ս    "); 
	gotoxy(72,7);
	printf("���ӣ�\n");
	gotoxy(72,8);
	printf("WSAD���Ʒ���\n");
	gotoxy(72,9);
	printf("�ո�����\n");
	gotoxy(72,10);
	printf("Q������\n");
	gotoxy(72,12);
	printf("����:");
	gotoxy(72,13);
	printf("�����������Ʒ���\n");
	gotoxy(72,14);
	printf("0������\n");
	gotoxy(72,15);
	printf("B������\n");
	direct[1]=15;
	direct[0]=30;
	chess_board();
	chess_menu();
	while(flag==0)
	{
		if(control==1)
		{
			gotoxy(70,22);
			BackGround(6,0);
			printf("   �� �� ִ ��    "); 
			red_movexy();
			red_chess(direct[1],direct[0]);
			flag=judge_winner(direct[1],direct[0],1);
		}
		else
		{
			gotoxy(70,22);
			BackGround(6,0);
			printf("   �� �� ִ ��    "); 
			white_movexy();
			white_chess(direct[1],direct[0]);
			flag=judge_winner(direct[1],direct[0],2);
		}
		control=-control;
	}
	if(flag==1)
	{
		BackGround(7,0);
		MessageBox(NULL,"��Ϸ����������ʤ��","��������Ϸ",MB_OK);
		regame(flag) ;
	}
	if(flag==2)
	{
		MessageBox(NULL,"��Ϸ����������ʤ��","��������Ϸ",MB_OK);
		regame(flag) ;
	}
	if(count>=225)
	{
		MessageBox(NULL,"��Ϸ������ƽ��","��������Ϸ",MB_OK);
		regame(flag) ;
	}
	sb();
}

void man_machine()//�˻���սģʽ 
{
	loop6:system("cls");
	char key;
	int control,z=11;
	gotoxy(35, 3);
	printf("1.�� �� �� �֣����Ϊ���ӣ�");
	
	gotoxy(35, 5);
	printf("2.�� �� �� �֣�����Ϊ���ӣ�");
	
	gotoxy(35,7);
	printf("3.������һ����"); 
	
	gotoxy(35, 9);
	printf("(������Ӧ���ѡ��)");
	key=getch();
	system("cls");
	if(key=='1')
		control=1;
	else if(key=='2')
	{
		control=1;
		machine_chess(13,26);
	}
	else if(key=='3')
	    sb(); 
	else 
		goto loop6;
	gotoxy(70,5);
	printf("   �� �� �� ս    ");
	gotoxy(75,10);
	printf("WSAD���Ʒ���");
	gotoxy(75,11);
	printf("�ո�����");
	gotoxy(75,12);
	printf("Q������");
	direct[1]=15;
	direct[0]=30;
	chess_board();
	chess_menu();
	while(flag==0)
	{
		if(control==1)
		{
			gotoxy(70,22);
			BackGround(6,0);
			printf("   �� �� ִ ��    "); 
			red_movexy();
			red_chess(direct[1],direct[0]);
			flag=judge_winner(direct[1],direct[0],1);
			if(key=' ')
			{
				z++;
			}
			gotoxy(75,14);
			printf("��ǰ����:%d",z);
		}
		else
		{
			gotoxy(70,22);
			BackGround(6,0);
			printf("   �� �� ִ ��    "); 
			machine_defend();
			machine_attack();
			find_position();
			machine_chess(direct[1],direct[0]);
			flag=judge_winner(direct[1],direct[0],2);
		}
		control=-control;
	}
	gotoxy(8,18);
	if(flag==1)
	{
		BackGround(7,0);
		MessageBox(NULL,"��Ϸ�������㻹��˵����ͦţ��!","��������Ϸ",MB_OK);
		regame(flag) ;
	}
	if(flag==2)
	{
		MessageBox(NULL,"��Ϸ�����������������ʺ","��������Ϸ",MB_OK);
		regame(flag) ;
	}
	if(count>=225)
	{
		MessageBox(NULL,"ƽ��","��������Ϸ",MB_OK);
		regame(flag) ;
	}
	sb();
}

void Regret()//���庯�� 
{
	gotoxy(regrey,regrex);
	BackGround(0,0);
 	printf(" ");
	status[regrex][regrey]=0;
	gotoxy(regrey1,regrex1);
	BackGround(0,0);
 	printf(" ");
	status[regrex1][regrey1]=0;
	count-=2;
} 

void welcome1()//��Ϸ�˵� 
{
	int k;
	char choose;
	system("cls");
	for(k=2;k<=16;k+=2)//��Ϸ�˵� 
	{
		gotoxy(35,k);	
    	printf("|-----------------|");
	}
	gotoxy(35, 3);
	printf("|  �� �� �� �� Ϸ |");
	
	gotoxy(35, 5);
	printf("|     ��    ��    |");
	
	gotoxy(35, 7);
	printf("|  1.�� �� �� ս  |");
	
	gotoxy(35, 9);
	printf("|  2.�� �� �� ս  |");
	
	gotoxy(35, 11);	
	printf("|  3.�� Ϸ �� ��  |");
	
	gotoxy(35, 13);	
	printf("|  4.�� �� �� ��  |");
	
	gotoxy(35, 15);
	printf("|  5.�� �� �� Ϸ  |");
	
	gotoxy(35, 18);
	printf("��ܰ��ʾ:����˵���Ӧ��Ž��в���");
	
	gotoxy(35, 20);
	printf("ף����Ϸ��죡");
	
	gotoxy(35, 22);
}

void welcome2()
{
	int k;
	char choose;
		system("cls");
	for(k=2;k<=8;k+=2)//��Ϸ�˵� 
	{
		gotoxy(35,k);	
    	printf("|-----------------|");
	}
	gotoxy(35, 3);
	printf("|  �� �� �� �� Ϸ |");
	
	gotoxy(35, 5);
	printf("|1.�û���¼  |");
	
	gotoxy(35,7);
	printf("|2.�ο͵�¼  |"); 
	gotoxy(35,11);
	printf("��ܰ��ʾ:�����Ӧ��Ž��в���");
	gotoxy(35, 13);

} 

char Gametips()//��Ϸ���� 
{
	char choose;
	int key;
	
	system("cls");
	
	gotoxy(35, 3);
	printf("��Ϸ������"); 
		
	gotoxy(35, 5);
	printf("�� ��ɫ����WASD�ƶ����ѡ������λ��,���ո��ȷ��,��Q����"); 
		
	gotoxy(35, 7);
	printf("�� ��ɫ���ӡ��������ƶ����ѡ������λ��,��0ȷ��,��B����");
		
	gotoxy(35, 19);
	printf("����E�����أ�������������˳���");
	
	return getch();
}

char Updatediary()//��첽�� 
{
	system("cls");
	
	gotoxy(35,3);
	int k;
	k=0;
	if(k>=count)
	{
		k=count;
		printf("%d",k);
	}
	else
	{
		printf("%d",count);
	}
	

	gotoxy(35,7);
	printf("��E�����أ�������������˳���");
	return getch();
} 




void print_Passwd(void)
{
system("pause");
system("cls");
int k;//ѡ����������һ� 
int flag=0;//������ȷ���
char p[5];//��ʱ�û���
char s[6];//��ʱ����
char num=0;//�������
char temp;//��¼�������
gotoxy(35,1);
printf(" ------------\n");
gotoxy(35,2);
printf("|�������¼��|:\n");
gotoxy(35,3);
printf(" ------------\n");
gotoxy(35,4);
scanf("%s",p);
for(i=0;i<3;i++)
{
if(strcmp(stu[i].user_Name,p)==0)
{
flag=1;
break;
}
}

if(1==flag)
{
gotoxy(35,5);
printf(" ------------\n");
gotoxy(35,6);
printf("����������:\n");
gotoxy(35,7);
printf(" ------------\n");
gotoxy(35,8);
scanf("%s",s);
}
else
{
gotoxy(35,5);
printf(" --------------------\n");
gotoxy(35,6);
printf(" |   û�д��û�      | \n");
gotoxy(35,7);
printf(" --------------------\n");
exit(0);
}
system("cls");
while(strcmp(stu[i].user_Pass,s)!=0)
{
num++;
if(3==num)
{
gotoxy(35,11);
printf(" -----------------------------------\n");
gotoxy(35,12);
printf(" |����������󳬹�3��,ϵͳ�Զ��˳�! |\n");
gotoxy(35,13);
printf(" -----------------------------------\n");
exit(0);
}
gotoxy(35,6);
printf(" ------------------\n");
gotoxy(35,7);
printf(" |�������!        |\n");
gotoxy(35,8);
printf(" |��������������:  |\n");
gotoxy(35,9);
printf(" ------------------\n");
system("cls");
gotoxy(35,1);
printf(" -------------------\n");
gotoxy(35,2);
printf(" |�Ƿ��һ�����      |\n");
gotoxy(35,3);
printf(" |������1���һذ�2  |\n");
gotoxy(35,4);
printf(" -------------------\n");
gotoxy(35,5);
scanf("%d",&k) ;
switch(k)
{
	case 1:
	gotoxy(35,6);
	printf(" -------------------\n");
	gotoxy(35,7);
	printf("|����������        |\n"); 
	gotoxy(35,8);
	printf(" -------------------\n");
	gotoxy(35,9);
	scanf("%s",s);
	break;
	case 2:zhaohui();
	break;
}

}
gotoxy(35,1);
printf("��¼�ɹ�!\n");
flag1=1;
if(flag1==1)
{
if(strcmp("admin",p)==0)
{
gotoxy(35,2);
printf(" ----------------------\n");
gotoxy(35,3);
printf(" |ע:����VIP�����û�! |\n");
gotoxy(35,4);
printf(" ----------------------\n");
}
else
{
gotoxy(35,2);
printf(" ----------------------\n");
gotoxy(35,3);
printf("|   ע:������ͨ�û�    |\n");
gotoxy(35,4);
printf(" ----------------------\n");
}
gotoxy(35,5);
printf(" -----------------------------\n");
gotoxy(35,6);
printf("|�밴1�޸�����,������������Ϸ:|\n");
gotoxy(35,7);
printf(" -----------------------------\n");
gotoxy(35,8);
scanf("%d",&temp);
if(1==temp)
{
xiugai_Passwd();
}
else
{
sb(); 
}
}
}
void xiugai_Passwd(void)//�޸�����
{

char p[10];//������
system("cls");
gotoxy(35,1);
printf(" -----------------------------\n");
gotoxy(35,2);
printf("|������������:                |\n");
gotoxy(35,3);
printf(" -----------------------------\n");
gotoxy(35,4);
scanf("%s",p);
system("cls");
strcpy(stu[i].user_Pass,p);
gotoxy(35,5);
printf(" -----------------------------\n");
gotoxy(35,6);
printf("|    �޸�����ɹ�:            |\n");
gotoxy(35,7);
printf("|     �����µ�¼:             |\n");
gotoxy(35,8);
printf(" -----------------------------\n");
sb();
}

void sb(void)//��Ϸ���� 
{
	
	system("title ������");
	system("mode con cols=92 lines=33");
	
	char choose,temp;
	loop:welcome1();
	choose=getch();
	
	
	switch(choose)
	{
		case '1':
			man_man();
			break;
		case '2':
			man_machine();
			break;
		case '3':
			temp=Gametips();
			if(temp=='E'||temp=='e')
				goto loop;
			break;
		case '4':
			temp=Updatediary();
			if(temp=='E'||temp=='e')
				goto loop;
			break;
		case '5':
			int message=MessageBox(NULL,"�Ƿ��˳���","������ʾ",MB_OKCANCEL);
			if(IDCANCEL==message)
				goto loop;
			if(IDOK==message)
			{
				break;
			}
	}
}
void denglu()//��¼���� 
{ 

void print_Passwd(void);
void xiugai_Passwd(void);
while(1)
{
print_Passwd();
}

}

void zhaohui()//�һغ��� 
{
int i;
int flag=0;
char l[10];	
char p[6];
gotoxy(35,5);
printf(" ------------\n");
gotoxy(35,6);
printf("|�������¼��|:\n");
gotoxy(35,7);
printf(" ------------\n");
gotoxy(35,8);
scanf("%s",p);
for(i=0;i<3;i++)
{
if(strcmp(stu[i].user_Name,p)==0)
{
flag=1;
break;
}
}

if(1==flag)
{
gotoxy(35,5);
printf(" -----------------------------\n");
gotoxy(35,6);
printf("|����˺���˭��:              |\n");
gotoxy(35,7);
printf(" -----------------------------\n");
gotoxy(35,9);
scanf("%s",l);
for(i=0;i<3;i++)
{
if(strcmp(stu[i].user_mibao,l)==0)
{
flag=1;
break;
}
}

if(flag==1)
{
gotoxy(35,10);
printf(" -----------------------------\n");
gotoxy(35,11);
printf("|����˺ŵ�������:            |\n");
gotoxy(35,12);
printf(" -----------------------------\n");
gotoxy(35,13);
printf("%-10s\n",stu[i].user_Pass);
print_Passwd();
}
else
{
gotoxy(35,10);
printf(" --------------------\n");
gotoxy(35,11);
printf(" |   �ܱ�����       | \n");
gotoxy(35,12);
printf(" --------------------\n");
exit(0);
}
}
else
{
gotoxy(35,9);
printf(" --------------------\n");
gotoxy(35,10);
printf(" |   û�д��û�      | \n");
gotoxy(35,11);
printf(" --------------------\n");
exit(0);
}


}

int main()
{
	system("title ������");
	system("mode con cols=92 lines=33");
	char a;
	loop:welcome2();
	a=getch();
	switch(a)
	{
	case '1':denglu();
		break;
	case '2':sb();
		break;
	}
	return 0;
}

