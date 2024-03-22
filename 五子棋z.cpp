#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define N 65

int i=0;//当前账号标记
int flag1=0;//登录成功标记
struct user
{
char user_Name[6];
char user_Pass[7];
char user_mibao[11];
}stu[3]={{"A0001","111111","liutao"},{"A0002","222222","wangqibing"},{"admin","333333","liuwang"}};//初始化用户名和对应密码

int status[N][N]={{0},{0}};//记录棋盘情况,0无，1红棋/玩家，2为白棋/电脑 
int flag=0;//判断输赢 
int direct[2];//方向
int Value1[N][N]={{0},{0}};//计算权值 
int Value2[N][N]={{0},{0}};//计算权值
int regrex,regrey,regrex1,regrey1; 
int count=0;//计算棋子数量 

void chess_board();//打印棋盘 
void red_movexy();//红子棋移动光标
void white_movexy();//白棋移动光标 
void red_chess(int x,int y);//红棋
void white_chess(int x,int y);//白棋  
void print_Passwd();//验证函数 
void xiugai_Passwd();//修改密码 
void denglu();//登录函数 
void zhaohui();//找回函数 旺 

void man_man();//人人对战 
void man_machine();//人机对战
int judge_chess(int x,int y);//判断这个位置是否下过 
int judge_winner(int x,int y,int temp);//判断输赢 
void Regret();//悔棋函数 
void sb();//进入游戏界面函数 
void regame(int &flag);//重置游戏 王 

void machine_attack();//电脑进攻权值 
void machine_defend();//电脑防守权值 
void find_position();//寻找最佳权值 涛 
 

 

void regame(int &flag)
{  
	for(int i=0;i<N;i++)
	for(int j=0;j<N;j++)
	status[i][j]=0;
	flag=0; 
}

void BackGround(unsigned int ForeColor, unsigned int BackGroundColor)  //颜色 
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);  //获取控制台的句柄
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//改变当前光标的背景和字体颜色
}

void gotoxy(int x, int y)    //光标函数 
{
	HANDLE handle;
	COORD coord;   //获取坐标轴结构体
	coord.X = x;
	coord.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);  //获取控制台句柄，值为-11
	SetConsoleCursorPosition(handle, coord);   //移动光标到x，y处
}

void chess_board()//打印棋盘 
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

void chess_menu()//打印棋盘旁的菜单 
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
	printf("模   式");
}

void red_movexy()//红棋移动光标 
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
				int message=MessageBox(NULL,"是否确定悔棋？","友情提示",MB_OKCANCEL);
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
				printf("这里已经被人下过了");
			goto loop2;
		}
}

void white_movexy()//白棋移动光标 
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
				int message=MessageBox(NULL,"是否确定悔棋？","友情提示",MB_OKCANCEL);
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
				printf("这里已经被人下过了");
			goto loop1;
		}
}

void red_chess(int x,int y)//打印红棋 
{
	BackGround(4,0);
	regrex=x;//记录上一落子的位置 ,方便悔棋 
	regrey=y;
	count++;
	printf("●");
	status[x][y]=1;
}

void white_chess(int x,int y)//打印白棋
{
	BackGround(7,0);
	regrex1=x;
	regrey1=y;
	printf("●");
	count++;
	status[x][y]=2;
}

void machine_chess(int x,int y)//电脑落子
{
	BackGround(7,0);
	status[x][y]=2;
	regrex1=x;
	regrey1=y;
	count++;
	gotoxy(y,x);
	printf("●");
}

int judge_chess(int x,int y)//判断这个地方是否有棋子
{
	if(status[x][y]==0)
		return 0;
	else
		return 1;
} 

int judge_winner(int x,int y,int temp)//判断输赢 
{ 
	int i,j,n1,n2;
	n1=n2=0;
	for(i=x,j=y+4;j<=58;j+=4)//右
	{
		if(status[i][j]==temp)
		    n1++;
		else
		    break;
	}
	for(i=x,j=y;j>=2;j-=4)//左
	{
		if(status[i][j]==temp)
		    n2++;
		else
		    break;
	}
	if(n1+n2>=5)
	    return temp;
	n1=n2=0;
	for(i=x,j=y;i>=1;i-=2)//上 
	{
		if(status[i][j]==temp)
		    n1++;
		else
		    break;
	}
	for(i=x+2,j=y;i<=30;i+=2)//下 
	{
		if(status[i][j]==temp)
		    n2++;
		else
		    break;
	}
	if(n1+n2>=5)
	    return temp;
	n1=n2=0;
	for(i=x-2,j=y+4;i>=1&&j<=58;i-=2,j+=4)//右上 
	{
		if(status[i][j]==temp)
		    n1++; 
		else
		    break;
	}
	for(i=x,j=y;i<=30&&j>=2;i+=2,j-=4)//左下
	{
		if(status[i][j]==temp)
		    n2++; 
		else
		    break;
	}
	if(n1+n2>=5)
	    return temp;
	n1=n2=0;
	for(i=x,j=y;i>=0&&j>=0;i-=2,j-=4)//左上 
	{
		if(status[i][j]==temp)
		    n1++; 
		else
		    break;
	}
	for(i=x+2,j=y+4;i<=30&&j<=58;i+=2,j+=4)//右下
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

void machine_attack()//电脑进攻权值 进攻优于防守 
{
	int i1,j1;
	int k1,k2,k;
	for(int i=1;i<=30;i+=2)
	{
		for(int j=2;j<=58;j+=4)
		{
			if(status[i][j])
				Value1[i][j]=0;
			if(status[i][j]==0)//寻找空位 
			{
				k1=k2=0;
				for(i1=i,j1=j-4;j1>=2;j1-=4)//往左数寻找电脑棋子数
				{
					if(status[i1][j1]==2)
						k1++;
					else
						break;
				}
				for(i1=i,j1=j+4;j1<=58;j1+=4)//往右数寻找电脑棋子数
				{
					if(status[i1][j1]==2)
						k2++;
					else
						break;
				}
				k=k1>k2? k1:k2;//k=左右最多棋子数 
				k1=k2=0;
				for(i1=i-2,j1=j;i1>=1;i1-=2)//往上数寻找电脑棋子数
				{
					if(status[i1][j1]==2)
						k1++;
					else
						break;
				}
				for(i1=i+2,j1=j;i1<=30;i1+=2)//往下数寻找电脑棋子数
				{
					if(status[i1][j1]==2)
						k2++;
					else
						break;
				}
				k1=k1>k2? k1:k2;
				k=k>k1? k:k1;
				k1=k2=0;
				for(i1=i-2,j1=j-4;i1>=0&&j1>=0;i1-=2,j1-=4)//往左上数寻找电脑棋子数
				{
					if(status[i1][j1]==2)
						k1++;
					else
						break;
				}
				for(i1=i+2,j1=j+4;i1<=30&&j1<=58;i1+=2,j1+=4)//往右下数寻找电脑棋子数
				{
					if(status[i1][j1]==2 )
						k2++;
					else
						break;
				}
				k1=k1>k2? k1:k2;
				k=k>k1?k:k1;
				k1=k2=0;
				for(i1=i+2,j1=j-4;i1<=30&&j1>=2;i1+=2,j1-=4)//往左下数寻找电脑棋子数
				{
					if(status[i1][j1]==2)
						k1++;
					else
						break;
				}
				for(i1=i-2,j1=j+4;i1>=1&&j1<=58;i1-=2,j1+=4)//往右上数寻找电脑棋子数
				{
					if(status[i1][j1]==2)
						k2++;
					else
						break;
				}
				k1=k1>k2? k1:k2;
				k=k>k1?k:k1;
				switch(k) //k是八个方向最多的棋子数 
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

void machine_defend()//防守权值
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
				for(i1=i,j1=j-4;j1>=2;j1-=4)//往左数寻找玩家棋子数
				{
					if(status[i1][j1]==1)
						k1++;
					else
						break;
				}
				for(i1=i,j1=j+4;j1<=58;j1+=4)//往右数寻找玩家棋子数
				{
					if(status[i1][j1]==1)
						k2++; 
					else
						break;
				}
				k=k1>k2? k1:k2;
				k1=k2=0;
				for(i1=i-2,j1=j;i1>=1;i1-=2)//往上数寻找玩家棋子数
				{
					if(status[i1][j1]==1)
						k1++;
					else
						break;
				}
				for(i1=i+2,j1=j;i1<=30;i1+=2)//往下数寻找玩家棋子数
				{
					if(status[i1][j1]==1)
						k2++;
					else
						break;
				}
				k1=k1>k2? k1:k2;
				k=k>k1?k:k1;
				k1=k2=0;
				for(i1=i-2,j1=j-4;i1>=1&&j1>=2;i1-=2,j1-=4)//往左上数寻找玩家棋子数
				{
					if(status[i1][j1]==1)
						k1++;
					else
						break;
				}
				for(i1=i+2,j1=j+4;i1<=30&&j1<=58;i1+=2,j1+=4)//往右下数寻找玩家棋子数
				{
					if(status[i1][j1]==1)
						k2++;
					else
						break;
				}
				k1=k1>k2? k1:k2;
				k=k>k1?k:k1;
				k1=k2=0;
				for(i1=i+2,j1=j-4;i1<=30&&j1>=2;i1+=2,j1-=4)//往左下数寻找玩家棋子数
				{
					if(status[i1][j1]==1)
						k1++;
					else
						break;
				}
				for(i1=i-2,j1=j+4;i1>=1&&j1<=58;i1-=2,j1+=4)//往右上数寻找玩家棋子数
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

void find_position()//找到最有价值的位置
{
	int k1=0, k2=0;
	int i, j, max=0;
	for( i=1;i<=30;i+=2)
		for( j=2;j<=58;j+=4)//防守权值判断 
		{
			if(max<=Value1[i][j])
			{
				max=Value1[i][j];
				k1=i;
				k2=j;
			}
		}
	for( i=1;i<=30;i+=2)//进攻权值判断 
		for( j=2;j<=58;j+=4)
		{
			if(max<=Value2[i][j])
			{
				max=Value2[i][j];
				k1=i;
				k2=j;
			}
		}
	direct[1]=k1;  //将找到的位置传给光标
	direct[0]=k2;
}

void man_man()//人人对战模式
{
	loop5:system("cls");
	char key;
	int control;
	gotoxy(35, 3);
	printf("1.红 子 先 手");
	
	gotoxy(35, 5);
	printf("2.白 子 先 手");
	
	gotoxy(35,7);
	printf("3.返回上一界面"); 
	
	gotoxy(35, 9);
	printf("(输入相应序号选择)");
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
	printf("   人 人 对 战    "); 
	gotoxy(72,7);
	printf("红子：\n");
	gotoxy(72,8);
	printf("WSAD控制方向\n");
	gotoxy(72,9);
	printf("空格落子\n");
	gotoxy(72,10);
	printf("Q键悔棋\n");
	gotoxy(72,12);
	printf("白子:");
	gotoxy(72,13);
	printf("↑↓←→控制方向\n");
	gotoxy(72,14);
	printf("0键落子\n");
	gotoxy(72,15);
	printf("B键悔棋\n");
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
			printf("   红 子 执 手    "); 
			red_movexy();
			red_chess(direct[1],direct[0]);
			flag=judge_winner(direct[1],direct[0],1);
		}
		else
		{
			gotoxy(70,22);
			BackGround(6,0);
			printf("   白 子 执 手    "); 
			white_movexy();
			white_chess(direct[1],direct[0]);
			flag=judge_winner(direct[1],direct[0],2);
		}
		control=-control;
	}
	if(flag==1)
	{
		BackGround(7,0);
		MessageBox(NULL,"游戏结束，红子胜利","五子棋游戏",MB_OK);
		regame(flag) ;
	}
	if(flag==2)
	{
		MessageBox(NULL,"游戏结束，白子胜利","五子棋游戏",MB_OK);
		regame(flag) ;
	}
	if(count>=225)
	{
		MessageBox(NULL,"游戏结束，平局","五子棋游戏",MB_OK);
		regame(flag) ;
	}
	sb();
}

void man_machine()//人机对战模式 
{
	loop6:system("cls");
	char key;
	int control,z=11;
	gotoxy(35, 3);
	printf("1.玩 家 先 手（玩家为红子）");
	
	gotoxy(35, 5);
	printf("2.电 脑 先 手（电脑为白子）");
	
	gotoxy(35,7);
	printf("3.返回上一界面"); 
	
	gotoxy(35, 9);
	printf("(输入相应序号选择)");
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
	printf("   人 机 对 战    ");
	gotoxy(75,10);
	printf("WSAD控制方向");
	gotoxy(75,11);
	printf("空格落子");
	gotoxy(75,12);
	printf("Q键悔棋");
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
			printf("   玩 家 执 手    "); 
			red_movexy();
			red_chess(direct[1],direct[0]);
			flag=judge_winner(direct[1],direct[0],1);
			if(key=' ')
			{
				z++;
			}
			gotoxy(75,14);
			printf("当前步数:%d",z);
		}
		else
		{
			gotoxy(70,22);
			BackGround(6,0);
			printf("   电 脑 执 手    "); 
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
		MessageBox(NULL,"游戏结束，你还别说，还挺牛逼!","五子棋游戏",MB_OK);
		regame(flag) ;
	}
	if(flag==2)
	{
		MessageBox(NULL,"游戏结束，垃圾，废物，狗屎","五子棋游戏",MB_OK);
		regame(flag) ;
	}
	if(count>=225)
	{
		MessageBox(NULL,"平局","五子棋游戏",MB_OK);
		regame(flag) ;
	}
	sb();
}

void Regret()//悔棋函数 
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

void welcome1()//游戏菜单 
{
	int k;
	char choose;
	system("cls");
	for(k=2;k<=16;k+=2)//游戏菜单 
	{
		gotoxy(35,k);	
    	printf("|-----------------|");
	}
	gotoxy(35, 3);
	printf("|  五 子 棋 游 戏 |");
	
	gotoxy(35, 5);
	printf("|     菜    单    |");
	
	gotoxy(35, 7);
	printf("|  1.人 人 对 战  |");
	
	gotoxy(35, 9);
	printf("|  2.人 机 对 战  |");
	
	gotoxy(35, 11);	
	printf("|  3.游 戏 帮 助  |");
	
	gotoxy(35, 13);	
	printf("|  4.最 快 步 数  |");
	
	gotoxy(35, 15);
	printf("|  5.退 出 游 戏  |");
	
	gotoxy(35, 18);
	printf("温馨提示:输入菜单对应序号进行操作");
	
	gotoxy(35, 20);
	printf("祝您游戏愉快！");
	
	gotoxy(35, 22);
}

void welcome2()
{
	int k;
	char choose;
		system("cls");
	for(k=2;k<=8;k+=2)//游戏菜单 
	{
		gotoxy(35,k);	
    	printf("|-----------------|");
	}
	gotoxy(35, 3);
	printf("|  五 子 棋 游 戏 |");
	
	gotoxy(35, 5);
	printf("|1.用户登录  |");
	
	gotoxy(35,7);
	printf("|2.游客登录  |"); 
	gotoxy(35,11);
	printf("温馨提示:输入对应序号进行操作");
	gotoxy(35, 13);

} 

char Gametips()//游戏帮助 
{
	char choose;
	int key;
	
	system("cls");
	
	gotoxy(35, 3);
	printf("游戏操作："); 
		
	gotoxy(35, 5);
	printf("① 红色棋子WASD移动光标选择下棋位置,按空格键确认,按Q悔棋"); 
		
	gotoxy(35, 7);
	printf("② 白色棋子↑↓←→移动光标选择下棋位置,按0确认,按B悔棋");
		
	gotoxy(35, 19);
	printf("（按E键返回，按其它任意键退出）");
	
	return getch();
}

char Updatediary()//最快步数 
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
	printf("按E键返回，按其它任意键退出）");
	return getch();
} 




void print_Passwd(void)
{
system("pause");
system("cls");
int k;//选择继续还是找回 
int flag=0;//密码正确标记
char p[5];//临时用户名
char s[6];//临时密码
char num=0;//密码次数
char temp;//登录后改密码
gotoxy(35,1);
printf(" ------------\n");
gotoxy(35,2);
printf("|请输入登录名|:\n");
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
printf("请输入密码:\n");
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
printf(" |   没有此用户      | \n");
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
printf(" |密码输入错误超过3次,系统自动退出! |\n");
gotoxy(35,13);
printf(" -----------------------------------\n");
exit(0);
}
gotoxy(35,6);
printf(" ------------------\n");
gotoxy(35,7);
printf(" |密码错误!        |\n");
gotoxy(35,8);
printf(" |请重新输入密码:  |\n");
gotoxy(35,9);
printf(" ------------------\n");
system("cls");
gotoxy(35,1);
printf(" -------------------\n");
gotoxy(35,2);
printf(" |是否找回密码      |\n");
gotoxy(35,3);
printf(" |继续按1，找回按2  |\n");
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
	printf("|请重新输入        |\n"); 
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
printf("登录成功!\n");
flag1=1;
if(flag1==1)
{
if(strcmp("admin",p)==0)
{
gotoxy(35,2);
printf(" ----------------------\n");
gotoxy(35,3);
printf(" |注:你是VIP超级用户! |\n");
gotoxy(35,4);
printf(" ----------------------\n");
}
else
{
gotoxy(35,2);
printf(" ----------------------\n");
gotoxy(35,3);
printf("|   注:你是普通用户    |\n");
gotoxy(35,4);
printf(" ----------------------\n");
}
gotoxy(35,5);
printf(" -----------------------------\n");
gotoxy(35,6);
printf("|请按1修改密码,其他键近入游戏:|\n");
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
void xiugai_Passwd(void)//修改密码
{

char p[10];//新密码
system("cls");
gotoxy(35,1);
printf(" -----------------------------\n");
gotoxy(35,2);
printf("|请输入新密码:                |\n");
gotoxy(35,3);
printf(" -----------------------------\n");
gotoxy(35,4);
scanf("%s",p);
system("cls");
strcpy(stu[i].user_Pass,p);
gotoxy(35,5);
printf(" -----------------------------\n");
gotoxy(35,6);
printf("|    修改密码成功:            |\n");
gotoxy(35,7);
printf("|     请重新登录:             |\n");
gotoxy(35,8);
printf(" -----------------------------\n");
sb();
}

void sb(void)//游戏界面 
{
	
	system("title 五子棋");
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
			int message=MessageBox(NULL,"是否退出？","友情提示",MB_OKCANCEL);
			if(IDCANCEL==message)
				goto loop;
			if(IDOK==message)
			{
				break;
			}
	}
}
void denglu()//登录函数 
{ 

void print_Passwd(void);
void xiugai_Passwd(void);
while(1)
{
print_Passwd();
}

}

void zhaohui()//找回函数 
{
int i;
int flag=0;
char l[10];	
char p[6];
gotoxy(35,5);
printf(" ------------\n");
gotoxy(35,6);
printf("|请输入登录名|:\n");
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
printf("|这个账号是谁的:              |\n");
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
printf("|这个账号的密码是:            |\n");
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
printf(" |   密保错误       | \n");
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
printf(" |   没有此用户      | \n");
gotoxy(35,11);
printf(" --------------------\n");
exit(0);
}


}

int main()
{
	system("title 五子棋");
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

