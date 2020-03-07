#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>


typedef struct //校车的结构体
{
	int num;//车子的编号
	char id[50];//车牌号
	int set;//座位数
	char name[50];//司机姓名
	char tel[50];//联系电话
	char site[50];//当前车辆所在站点
	char belong[50];//归属校区
	char statu[50];//当前车辆状态
}Bus;

typedef struct BusNode 
{
	Bus data; //结点的数据域
	struct BusNode* next; //结点的指针域
} BusNode; //List为指向结构体Node的指针类型

typedef BusNode* BusList;

typedef struct SiteNode//站点
{
	char date[50];//站点名称
	struct SiteNode* next;
}SiteNode;
typedef SiteNode* SiteList;

BusList b; SiteList s;//定义车辆和站点结构体
int SiteNum = 0;//定义站点数目

//声明读写函数
int write_bus(); 
int write_site();

////////////初始化校车链表//////////
int InitBusList(BusList* L) //初始化链表
{
	BusList p;
	p = (BusList)malloc(sizeof(BusNode));  	//创建头结点
	p->next = NULL;
	*L = p;
	return 1;
}

////////////初始化站点链表//////////
int InitSiteList(SiteList* L) 
{
	SiteList p;
	p = (SiteList)malloc(sizeof(SiteNode));  	//创建头结点
	p->next = NULL;
	*L = p;
	return 1;
}

/////////插入校车信息到List中///////
int BusListInsert(BusList* L, Bus e)
{
	L = &b;
	BusList p;
	p = (BusList)malloc(sizeof(BusNode));	//为新建的结点开辟内存空间
	p->data = e;							//元素赋值 
	p->next = NULL;
	BusList t = (*L); 
	int i=1;
	while (t->next)
	{
		t = t->next; i++;
	}
	p->data.num = i;//给新元素一个顺序编号
	t->next = p;
	return 1;
}

/////////插入站点信息到List中指定位置///////
int SiteListInsert(SiteList* L, char e[50],int h) 
{
	L = &s;
	SiteList p1,p2;//p1指向新节点,p2指向新节点的前一个节点
	p2 = (*L);
	for (int i = 1; i < h; i++)
	{
		p2 = p2->next;
	}
	p1 = (SiteList)malloc(sizeof(SiteNode));	//为新建的结点开辟内存空间
	for (int j = 0; j < 50; j++)
	{
		p1->date[j] = e[j];
	}
	p1->next = p2->next;
	p2->next = p1;
	return 1;
}

////////输出所有校车信息/////
int prt_bus_information()
{
	BusList p=b->next;

	while (p)
	{
		printf("编号 %d  校区:%s  车牌号:%s  司机:%s  电话:%s  剩余座位数:%d  当前车辆状态:%s \n", 
			p->data.num, p->data.belong, p->data.id, p->data.name, p->data.tel, p->data.set, p->data.statu);
		p = p->next;
	}
	printf("\n");
	return 1;
}

////////输出所有站点信息/////
int prt_site_information()
{
	SiteList p = s->next;
	int i = 1;
	while (p)
	{
		printf("站点%d:%s   ",i, p->date);
		p = p->next;
		i++;
	}
	printf(" \n"); printf(" \n");
	return 1;
}

///////添加校车信息//////////
int add_bus_information(BusList* L)
{
menu2:
	printf("车辆信息\n");
	prt_bus_information();
	Bus  tmp;
	for (int i = 0; i < 49; i++)
	{
		tmp.belong[i] = '\0';
		tmp.id[i] = '\0';
		tmp.name[i] = '\0';
		tmp.tel[i]= '\0';
		tmp.site[i]= '\0';
		tmp.statu[i] = '\0';
	}
	printf("请输入需要添加的校车车牌号 \n");
	gets(tmp.id);
	printf("请输入司机姓名 \n");
	gets(tmp.name);
	printf("请输入司机联系电话 \n");
	gets(tmp.tel);
	printf("请输入车辆所属校区 \n");
	gets(tmp.belong);
	printf("请输入车辆当前状态 \n");
	gets(tmp.statu);
	printf("请输入车辆的座位数 \n");
	scanf("%d", &tmp.set);
	getchar();//过滤掉scanf输入敲入的回车

	printf("输入完成，正在添加...... \n\n");
	BusListInsert(L, tmp);

	BusList p7 = b->next;
	int e = 1;
	while (p7)//重新给链表内的车辆按顺序编号
	{
		p7->data.num = e;
		p7 = p7->next;
		e++;
	}
	write_bus();
	printf("添加完成！ \n");
	prt_bus_information();

	///////////菜单返回语句/////////
	int w;
	printf("\n");
	printf("继续输入按1,返回菜单0\n");
	scanf("%d", &w); getchar();printf("\n"); printf("\n");
	if (w)goto menu2;
	return 1;
}

///////添加站点信息//////////
int add_site_information(SiteList* L)
{
	SiteNode  tmp; 
	int i;//i保存站点插入的位置
menu6:
	for (int i = 0; i < 49; i++)//给字符串初始化
	{
		tmp.date[i] = '\0';
	}
	
	printf("请输入新站点名称 \n");
	gets(tmp.date);
	printf("现在有%d个站,想把此站点添加到第几站? \n",SiteNum);
	scanf("%d", &i); 
	getchar();//过滤掉scanf输入敲入的回车
	
	if (i > (SiteNum + 1))i = (SiteNum + 1);
	SiteListInsert(L, tmp.date,i);
	SiteNum++;
	printf("添加完成！当前共有%d个站 \n",SiteNum);
	write_site();
	prt_site_information();

	///////////菜单返回语句/////////
	int w;
	printf("\n");
	printf("继续输入按1,返回菜单0\n");
	scanf("%d", &w); getchar();printf("\n"); printf("\n");
	if (w)goto menu6;
	return 1;
}

////////////把校车结构体数据存入文档中
int write_bus()
{
	FILE* fp;
	if ((fp = fopen("校车信息.hh", "wb+")) == NULL) //wb+新建一个二进制文件，已存在的文件将内容清空，允许读写
	{
		puts("Fail to open file!");
		exit(0);
	}
	
	BusList p = b->next;
	while (p)
	{
		fwrite(p, sizeof(BusNode), 1, fp);
		p = p->next;
	}
	fclose(fp);//关闭文件，数据流才存入磁盘
	printf("校车信息写入完毕！\n");
	return 1;
}

////////////从文档中读取校车结构体/////////
int read_bus()
{
	FILE* fp;
	if ((fp = fopen("校车信息.hh", "rb+")) == NULL)//rb+打开一个二进制文件，文件必须存在，允许读写
	{
		puts("Fail to open file!");
		exit(0);
	}
	BusList p = b;
	while (!feof(fp))//调试发现feof会多读一次，所以加上fread返回值判断
	{
		BusNode tmp;
		if (fread(&tmp, sizeof(BusNode), 1, fp))
		{
			BusListInsert(&b, tmp.data);//判断fscanf的返回数值，它指示成功读取的数据
		}
	}
	fclose(fp);
	printf("校车信息读取完毕！\n");
	return 1;
}

////////////把站点结构体数据存入文档中
int write_site()
{
	FILE* fp;
	if ((fp = fopen("站点信息.hh", "wb+")) == NULL) //wb+新建一个二进制文件，已存在的文件将内容清空，允许读写
	{
		puts("Fail to open file!");
		exit(0);
	}

	SiteList p = s->next;
	while (p)
	{
		fwrite(p, sizeof(SiteNode), 1, fp);
		p = p->next;
	}
	fclose(fp);//关闭文件，数据流才存入磁盘
	printf("站点信息写入完毕！\n");
	return 1;
}

////////////从文档中读取站点结构体/////////
int read_site()
{
	FILE* fp;
	if ((fp = fopen("站点信息.hh", "rb+")) == NULL)
	{
		puts("Fail to open file!");
		exit(0);
	}
	SiteList p = s;
	int i = 1;
	while (!feof(fp))//调试发现feof会多读一次，所以加上fread返回值判断
	{
		SiteNode tmp;
		if (fread(&tmp, sizeof(SiteNode), 1, fp))
		{
			SiteListInsert(&s, tmp.date,i);//判断fscanf的返回数值，它指示成功读取的数据
			i++; SiteNum++;
		}
	}
	fclose(fp);
	printf("站点信息读取完毕！\n"); printf("\n"); printf("\n");
	return 1;
}

////////////查询车辆信息//////////////////
int query_bus()
{  
	int u;
	
menu3:
	printf("请输入需要查询的车辆编号\n");
	scanf("%d", &u); getchar();
	BusList p=b->next;
	while (p)
	{
		if (p->data.num == u)
		{
			printf("编号 %d  校区:%s  车牌号:%s  司机:%s  电话:%s  剩余座位数:%d  当前车辆状态:%s \n",
				p->data.num, p->data.belong, p->data.id, p->data.name, p->data.tel, p->data.set, p->data.statu);
			printf("\n");
			break;
		}
		else
		{
			p = p->next;
			if (!p)printf("未找到该车辆,请输入正确的车辆编号\n");
		}	
	}

	///////////菜单返回语句/////////
	///////////菜单返回语句/////////
	int w;
	printf("\n");
	printf("继续查询按1,返回菜单0\n");
	scanf("%d", &w); getchar();
	printf("\n"); printf("\n");
	if (w)goto menu3;
	return 1;
}

////////////查询站点信息//////////////////
int query_site()
{
	SiteNode tmp; int r = 1;
menu7:
	for (int i = 0; i < 49; i++)
	{
		tmp.date[i] = '\0';
	}
	r = 1;
	printf("请输入需要查询的站点名称\n");
	gets(tmp.date);
	SiteList p = s->next;
	while (p)
	{
		if ( ! strcmp( p->date,tmp.date ) )
		{ 
			printf("已找到%s，编号是%d\n",tmp.date,r);
			printf("\n");
			break;
		}
		else
		{
			p = p->next; r++;
			if (!p)printf("未找到该站点,请输入正确的站点名称\n");
		}
			
	}

	///////////菜单返回语句/////////
	int w;
	printf("\n");
	printf("继续查询按1,返回菜单0\n");
	scanf("%d", &w); getchar();printf("\n"); printf("\n");
	if (w)goto menu7;
	return 1;
}

////////////修改校车信息///////////
int change_bus()
{
menu4:
	printf("车辆信息修改*****************************\n");
	prt_bus_information();
	int u;
	int item;
	Bus  tmp;

	printf("请输入需要修改的车辆编号\n");
	scanf("%d", &u); getchar();

	BusList p = b->next;

	for (int i = 0; i < 49; i++)
	{
		tmp.belong[i] = '\0';
		tmp.id[i] = '\0';
		tmp.name[i] = '\0';
		tmp.tel[i] = '\0';
		tmp.site[i] = '\0';
		tmp.statu[i] = '\0';
	}
	printf("\n");
	printf("请输入需要修改的项目编号\n 1司机姓名 2联系电话 3所属校区 4当前状态 5剩余座位数 6车牌号 \n");
	scanf("%d", &item); getchar();
	if (item == 1)
	{
		printf("请输入修改后司机姓名 \n");
		gets(tmp.name);
		while (p)
		{
			if (p->data.num == u)
			{
				strcpy(p->data.name, tmp.name);
				break;
			}
			else
			{
				p = p->next; if (!p)printf("未找到该车辆,请输入正确的车辆编号\n");
			}	
		}
	}
	if (item == 2)
	{
		printf("请输入修改后司机联系电话 \n");
		gets(tmp.tel);
		while (p)
		{
			if (p->data.num == u)
			{
				strcpy(p->data.tel, tmp.tel);
				break;
			}
			else
			{
				p = p->next; if (!p)printf("未找到该车辆,请输入正确的车辆编号\n");
			}
		}
	}
	if (item == 3)
	{
		printf("请输入修改后车辆所属校区 \n");
		gets(tmp.belong);
		while (p)
		{
			if (p->data.num == u)
			{
				strcpy(p->data.belong, tmp.belong);
				break;
			}
			else
			{
				p = p->next; if (!p)printf("未找到该车辆,请输入正确的车辆编号\n");
			}
		}
	}
	if (item == 4)
	{
		printf("请输入修改后车辆状态 \n");
		gets(tmp.statu);
		while (p)
		{
			if (p->data.num == u)
			{
				strcpy(p->data.statu, tmp.statu);
				break;
			}
			else
			{
				p = p->next; if (!p)printf("未找到该车辆,请输入正确的车辆编号\n");
			}
		}
	}
	if (item == 5)
	{
		printf("请输入修改后车辆的座位数 \n");
		scanf("%d", &tmp.set); getchar();//过滤掉scanf输入敲入的回车
		while (p)
		{
			if (p->data.num == u)
			{
				p->data.set = tmp.set;
				break;
			}
			else
			{
				p = p->next; if (!p)printf("未找到该车辆,请输入正确的车辆编号\n");
			}
		}
	}
	if (item == 6)
	{
		printf("请输入需要修改后的校车车牌号 \n");
		gets(tmp.id);
		while (p)
		{
			if (p->data.num == u)
			{
				strcpy(p->data.id, tmp.id);
				break;
			}
			else
			{
				p = p->next; if (!p)printf("未找到该车辆,请输入正确的车辆编号\n");
			}
		}
	}
	write_bus();
	printf(" \n");
	prt_bus_information();

	///////////菜单返回语句/////////
	int w;
	printf("\n");
	printf("继续修改按1,返回菜单0\n");
	scanf("%d", &w); getchar();printf("\n"); printf("\n");
	if (w)goto menu4;
	return 1;
}

////////////修改站点信息///////////
int change_site()
{
	printf("站点信息修改*****************************\n");
	prt_site_information();

	SiteNode  tmp1;
	SiteNode  tmp2;
menu8:
	for (int i = 0; i < 49; i++)
	{
		tmp1.date[i] = '\0';
		tmp2.date[i] = '\0';
	}
	printf("请输入需要修改的站点名称\n");
	gets(tmp1.date);

	SiteList p = s->next;

	printf("请输入修改后的站点名称 \n");
	gets(tmp2.date);
	while (p)
	{
		if (!strcmp(p->date, tmp1.date))
		{
			strcpy(p->date,tmp2.date);
			break;
		}
		else
		{
			p = p->next;
			if (!p)printf("未找到该站点,请输入正确的站点名称\n");
		}
	}

	write_site();
	printf(" \n");
	prt_site_information();

	///////////菜单返回语句/////////
	int w;
	printf("\n");
	printf("继续修改按1,返回菜单0\n");
	scanf("%d", &w); getchar();printf("\n"); printf("\n");
	if (w)goto menu8;
	return 1;
}

//////////////删除车辆信息//////////////
int del_bus()
{
menu5:
	printf("车辆信息删除*****************************\n");
	prt_bus_information();
	int u;
	printf("请输入需要删除的车辆编号\n");
	scanf("%d", &u); getchar();
	BusList p = b->next;
	BusList p2 = b;
	while (p)
	{
		if (p->data.num == u)
		{
			p2->next = p->next;
			break;
		}
		else
		{
			p = p->next;
			p2 = p2->next;
			if (!p)printf("未找到该车辆,请输入正确的车辆编号\n");
		}
	}

	BusList p7 = b->next;
	int e = 1;
	while (p7)//重新给链表内的车辆按顺序编号
	{
		p7->data.num = e;
		p7 = p7->next;
		e++;
	}
	write_bus();
	printf(" \n");
	prt_bus_information();

	///////////菜单返回语句/////////
	int w;
	printf("\n");
	printf("继续删除按1,返回菜单0\n");
	scanf("%d", &w); getchar();printf("\n"); printf("\n");
	if (w)goto menu5;

	return 1;
}
//////////////删除站点信息//////////////
int del_site()
{
	printf("站点信息删除*****************************\n");
	prt_site_information();
	
	SiteNode  tmp1;
menu9:
	for (int i = 0; i < 49; i++)
	{
		tmp1.date[i] = '\0';
	}

	SiteList p = s->next;
	SiteList p2 = s;
	printf("请输入需要删除的站点名称\n");
	gets(tmp1.date);

	while (p)
	{
		if (!strcmp(p->date, tmp1.date))
		{
			p2->next = p->next;
			SiteNum--;
			break;
		}
		else
		{
			p = p->next;
			p2 = p2->next;
			if (!p)printf("未找到该站点,请输入正确的站点名称\n");
		}	
	}

	write_site();
	printf(" \n");
	prt_site_information();

	///////////菜单返回语句/////////
	int w;
	printf("\n"); 
	printf("继续删除按1,返回菜单0\n"); 
	scanf("%d", &w); getchar();printf("\n"); printf("\n");
	if (w)goto menu9;
	return 1;
}

/////////////校区校车分配管理///////////
int dtb_bus()
{
	int u;
	Bus  tmp;
	
menu10:
	for (int i = 0; i < 49; i++)
	{
		tmp.belong[i] = '\0';
	}
	BusList p = b->next;
	prt_bus_information();
	printf("请输入需要重新分配校区的车辆编号\n");
	scanf("%d", &u); getchar();

	printf("请输入修改后车辆所属的校区 \n");
	gets(tmp.belong);
	while (p)
	{
		if (p->data.num == u)
		{
			strcpy(p->data.belong, tmp.belong);
			break;
		}
		else
		{
			p = p->next;
			if (!p)printf("未找到该车辆,请输入正确的车辆编号\n");
		}
	}
	write_bus();
	printf(" \n");
	prt_bus_information();
	///////////菜单返回语句/////////
	int w;
	printf("\n");
	printf("继续分配按1,返回菜单0\n");
	scanf("%d", &w); getchar();printf("\n"); printf("\n");
	if (w)goto menu10;
	return 1;
}

/////////////校车预约管理///////////
int order_bus()
{
	int u;
	
menu11:
	prt_bus_information();BusList p = b->next;
	printf("请输入想要乘坐的车辆编号\n");
	scanf("%d", &u); getchar();
	while (p)
	{
		if (p->data.num == u)
		{
			if (p->data.set > 0)
			{
				p->data.set--;
				printf("\n"); printf("预约成功,%s校车还剩余%d个座位\n",p->data.belong,p->data.set);  printf("\n");
				break;
			}
			else
			{
				printf("\n"); printf("没有空余座位，请选择其他车辆\n"); printf("\n");
				break;
			}
		}
		else
			p = p->next;
	}
	write_bus();
	printf(" \n");
	prt_bus_information();

	///////////菜单返回语句/////////
	int w;
	printf("\n"); 
	printf("继续预约按1,返回菜单0\n"); 
	scanf("%d", &w); getchar();printf("\n");printf("\n");
	if (w)goto menu11;
	return 1;
}

int look()
{

	printf("站点信息\n");
	prt_site_information();
	printf("车辆信息\n");
	prt_bus_information();
	return 1;
}

int main()
{
	system("color 4e");
	InitBusList(&b); 
	InitSiteList(&s);
	read_bus();
	read_site();
	prt_site_information();
	prt_bus_information();
	
	int f;
menu:
	system("cls");
	printf("*****************************************************************************\n");
	printf("************************欢迎来到武汉科技大学校车管理系统*********************\n");
	printf("*****************************************************************************\n");
	printf("\n");
	printf("\n");
	printf("请输入演示功能\n");
	printf("\n");
	printf("             0.保存退出系统                        1.查看已存信息\n"); printf("\n");
	printf("             2.添加校车信息                        3.查询校车信息\n"); printf("\n");
	printf("             4.修改校车信息                        5.删除校车信息\n"); printf("\n");
	printf("             6.添加站点信息                        7.查询站点信息\n"); printf("\n");
	printf("             8.修改站点信息                        9.删除站点信息\n"); printf("\n");
	printf("            10.校区分配管理                       11.校车预约管理\n"); printf("\n");
	printf("\n");
	printf("\n");
	printf("************************················*********************\n");
	printf("************************················*********************\n");
	scanf("%d", &f); getchar();
	if (f == 0)return 0;
	if (f == 1)
	{
		system("cls"); look(); printf("按0键返回主菜单\n"); getchar(); goto menu;
	}
	if (f == 2)
	{
		system("cls"); add_bus_information(&b);  goto menu;
	}
	if (f == 3)
	{
		system("cls"); query_bus();  goto menu;
	}
	if (f == 4)
	{
		system("cls"); change_bus();  goto menu;
	}
	if (f == 5)
	{
		system("cls"); del_bus();  goto menu;
	}
	if (f == 6)
	{
		system("cls"); add_site_information(&s);  goto menu;
	}
	if (f == 7)
	{
		system("cls"); query_site();  goto menu;
	}
	if (f == 8)
	{
		system("cls"); change_site();  goto menu;
	}
	if (f == 9)
	{
		system("cls"); del_site(); goto menu;
	}
	if (f == 10)
	{
		system("cls"); dtb_bus();  goto menu;
	}
	if (f == 11)
	{
		system("cls"); order_bus();  goto menu;
	}
}