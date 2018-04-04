#include <stdio.h>
#include <stdlib.h>

#define DATA(A,B,C,D) data[(A)*5+(B)][(C)*5+(D)]

int data[25][25];//�洢ͼ���ڽӾ���

int NodeNum;//�ҵ��Ľڵ����

bool flag[25];//�ýڵ��Ƿ��Ѿ����ҵ���·��

class MyStack
{
public:
	MyStack();
	int StackData[10240][25][25];
	int StackPos[10240];
	int top;
	void push(int pos);
	int pop();
	bool IsEmpty();
}*s;

MyStack::MyStack()
{
	top=-1;
	for(int k=0;k<10240;k++)
	{
		StackPos[k]=-1;
		for(int i=0;i<25;i++)
		{
			for(int j=0;j<25;j++)
			{
				StackData[k][i][j]=0;
			}
		}
	}
}

void MyStack::push(int pos)
{
	top++;
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<25;j++)
		{
			StackData[top][i][j]=data[i][j];
		}
	}
	StackPos[top]=pos;
}

int MyStack::pop()
{
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<25;j++)
		{
			data[i][j]=StackData[top][i][j];
		}
	}
	return StackPos[top--];
}

bool MyStack::IsEmpty()
{
	return top==-1?true:false;
}

int findMin(int pos)//�ҵ���pos�ڵ������Ľڵ㣬�Ҹýڵ��ͨ����һ�ڵ�Ŀ��������٣�Ϊ�˻���ʱ��ʡʱ��
{
	int temppos=-1,minpos=-1,temptime=0,mintime=5;
	for(int i=0;i<25;i++)
	{
		if(data[pos][i]==1&&i!=pos&&flag[i]==false)
		{
			temppos=i;
			temptime=0;
			for(int j=0;j<25;j++)
			{
				if(data[temppos][j]==1&&j!=temppos&&flag[j]==false)	temptime++;
			}
			if(temptime<mintime)
			{
				mintime=temptime;
				minpos=temppos;
			}
		}
	}
	return minpos;
}

int main()
{
	freopen("out.txt","w",stdout);
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<25;j++)
		{
			if(i!=j)	data[i][j]=0;
				else	data[i][j]=1;
		}
	}			
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(i<=3)	DATA(i,j,i+1,j)=DATA(i+1,j,i,j)=1;
			if(j<=3)	DATA(i,j,i,j+1)=DATA(i,j+1,i,j)=1;
		}
	}
	DATA(0,1,0,0)=DATA(0,0,0,1)=0;
	DATA(0,1,0,2)=DATA(0,2,0,1)=0;
	DATA(0,1,1,1)=DATA(1,1,0,1)=0;
#if 0
	for(int i=0;i<25;i++)
		for(int j=0;j<25;j++)
			printf("i=%d,j=%d,data[%d]][%d]=%d\n",i,j,i,j,data[i][j]);
#endif
	for(int i=0;i<25;i++)
		flag[i]=false;
	s=new MyStack();
	NodeNum=1;
	flag[0]=true;
	int temppos=-1;
	int pos=0;
	while(1)
	{
		temppos=findMin(pos);
		if(temppos==-1)//û�ҵ�
		{
			if(NodeNum==24)//�Ѿ��ҵ���
			{
				printf("�д�\n");
				printf("��Ϊ��");
				for(int k=0;k<24;k++)
				{
					printf("%d\t",s->StackPos[k]);
				}
				printf("%d\n",pos);
				break;
			}
			else//û�ҵ���
			{
				if(s->IsEmpty()==true)//ջ�ѿգ��޽�
				{
					printf("�޴�\n");
					break;
				}
				else//ջ�ǿգ����ݣ���ջ
				{
					printf("unfind(before pop):pos=%d,temppos=%d\n",pos,temppos);
					NodeNum--;
					flag[pos]=false;
					temppos=s->pop();
					printf("unfind(after pop):pos=%d,temppos=%d\n",pos,temppos);
					pos=temppos;
				}
			}
		}
		else//�ҵ���
		{
			printf("find:pos=%d,temppos=%d\n",pos,temppos);
			data[pos][temppos]=data[temppos][pos]=0;//�ȸ�ֵ��ѹջ�Ա㵯ջʱ�����ظ��߸ýڵ�
			s->push(pos);
			flag[temppos]=true;
			NodeNum++;
			pos=temppos;
		}
	}
	delete s;
	fclose(stdout);
	freopen("con","w",stdout);
	system("pause");
	fclose(stdout);
	return 0;
}