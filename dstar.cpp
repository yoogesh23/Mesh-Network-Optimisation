#include <stdio.h>

int g[3]={1000,1000,1000};
int rhs[3]={1000,1000,0};
int open[3]= {-1,-1,-1};
int key[3][2]; 
int h[3]={0,10,25};
//int adj[3][3] = {0,10,25, 10,0,20, 25,20,0};
int adj[3][3] = {0,10,25, 1000,0,20, 1000,1000,0};
int visited[3]= {-1,-1,-1};
int start = 0,goal = 2;
int sucs[3][2] = {1,2, 2,-1, -1,-1};
int pred[3][2] = {-1,-1, 0,-1, 0,1};
int n = 0;

void cal_key(int n)
{
	if(g[n]>=rhs[n])
	{
		key[n][0]= rhs[n]+h[n];
		key[n][1]=rhs[n];
	}
	else
	{
		key[n][0]= g[n]+h[n];
		key[n][1]=g[n];
		
	}	
}

void rem_visited(int n)
{
	int i=0, temp=0;
	while((i<3)&&(visited[i]!=n))
	{
		i++;
			
	}
	while((i<2))
	{
		visited[i]=visited[i+1];
		i++;
	}
	visited[i] = -1;
}

void add_visited(int n)
{	
	int i=0;
	printf("/n adding %d to visited ",n);
	while((visited[i]!=-1)&&i<3&&n<3)
	{
		i++;
	}
	visited[i]= n;
	return;
}

void rem_open(int n)
{
	int i=0;
	printf("/n Removing %d from open ",n);
	while(i<3)
	{
		if(n==open[i])
		{
			open[i] = -1;                         // if s in open then remove 
			add_visited(n);
		}
		else
			i++;
	}	
}

void add_open(int n)
{	
	int i =0;
	printf("/n Adding %d to open ",n);
	rem_visited(n);                               /// extra added later
	while((open[i]!=-1)&&i<3&&n<3)
	{
		i++;
	}
	
	if(n<3)
	open[i] = n;
	for(i=0;i<3;i++)
		printf(" open list %d\n",open[i]);
	
}

void min_rhs(int n)
{	
	int i=0,k=0,c=0,min =1500;
	for(i=0;i<2;i++)
	{	
		k = sucs[n][i];
		c = adj[n][k];
		c = c+g[k];
		if(min>c)
		{
			min = c;
		}
	}
	printf("\n %d is the rhs of %d\n",min,n);
	rhs[n] = min;
	
}


void update_state(int n)
{	
	printf("\n updating %d ",n);
	int i = 0, flag = 0, flag2 = 0;
	for(int j=0;j<3;j++)
		cal_key(j);
	printf(" hello");
	for(int j=0;j<3;j++)
		printf("\n visited %d",visited[j]);
	while(i<3)                           //  s not visited
	{
		if(n==visited[i])
		{
			flag = 1;
			printf(" hello %d",i);
			break;
		}
		
		else
		{
		  i++;
		}
	}
	printf(" hello dude");
	if(flag==0)
		{
			g[n] = 1000;  
			printf("\n In update and N is in visited :");                         //  g(s) = infinite
		}
	if(n!=goal)
	{	
		printf(" hello bro");
		min_rhs(n);                               //  min sE succ 
	}
	i=0;
	while(i<3)
	{
		if((open[i]!=-1)&&(open[i]==n))
		{
			flag2 =1;
		}
		i++;
	}
	if(flag2==1)
	{
		rem_open(n);
	}
		
	if(g[n]!=rhs[n])
	{
		add_open(n);                           // if g(s)!=rhs(s) then add to open list
	}
	
}

int min_key()
{	
	int min=2,i=0,j, flag =0;
	for(j=0;j<3;j++)
		cal_key(j);
	j =-1;
	for(int p=0;p<3;p++)
	{
		printf("\n the open lis %d",open[p]);
	}	
	i=0;
min = -1;
if(open[0]!=-1)
{
min =0;	
i=1;

while((open[i]!=-1)&&i<3)
{	printf(" \nvalue of i %d\n",i);
	if(key[open[i]][0]<key[open[min]][0])
		{
			min = i;
			printf("In one \n");
			
			
		}
		else if((key[open[i]][1]<key[open[min]][1])&&(key[open[i]][0]==key[open[min]][0]))
		{
			min =i;
			printf("In two \n");
			
		}
		else
			i++;
	
}
}
	n = open[min];
	//	n = min;                                          // changing the code
		
		printf("In min_key \n");
		printf("\n min value %d",min);
		
	return min;
}

int check_loop()
{
	int i,j, min = 0;
	for(j=0;j<3;j++)
		cal_key(j);
	
	min = min_key();
	if(min==-1)
	{
		return 0;
	}
	
	printf("problem located \n");
	if(key[n][0]<key[start][0])
	{
			return 1;
			printf("Target 1 \n");
	}
	else if(key[n][1]<key[start][1])
	{
			return 1;
			printf("Target 2 \n");
	}
	else if(rhs[start]!=g[start])
	{
			return 1;
			printf("Target 3 \n");
	}
	printf("Target 0\n");	
	return 0;
		
		
		
}

void shortest_path()
{	
		printf("In shortest path");
	int i = 0, z;
	while(check_loop())
	{	
	
		printf("In flag 1 //////////////////////////\n");
		printf("In value of n is %d \n",n);
		rem_open(n);
		if(g[n]>rhs[n])
		{	
			printf("In flag 2.................. \n");
			i = 0;
			g[n] = rhs[n];
			printf("/n g[0] %d",g[n]);
			printf("\n rhs[n] %d",rhs[n]);
			while((i<2)&&(pred[n][i]!=-1))
			{   
				printf("In pred update \n");
				printf("\n\nexpanding %d\n",pred[n][i]);
				update_state(pred[n][i]); 
				i++;              // update predecesor of s
			}
			printf("In pred update end\n");
			for(int j=0;j<3;j++)
				cal_key(j);
			for(i=0;i<3;i++)
				for(int r=0;r<2;r++)
					printf(" \t %d ",key[i][r]);
			for(int q=0;q<3;q++)
				printf(" g %d\n",g[q]);	
		}
	}
}

int main(void)
{	int i=0,j,z,cost=0;
	int s,d;
	printf("In main \n");
	
	printf("In main 2 \n");
	
	g[2] = 1000;
	rhs[2] = 0;
	open[0] = 2;
	for(i=0;i<3;i++)
		printf(" open list %d\n",open[i]);
	for(i=0;i<3;i++)
		cal_key(i);
	scanf("%d",&z);
	shortest_path();
	for(i=0;i<3;i++)
		printf(" open list %d\n",open[i]);
	for(i=0;i<3;i++)
		printf(" rhs %d\n",rhs[i]);	
	for(i=0;i<3;i++)
		printf(" g %d\n",g[i]);	
	for(i=0;i<3;i++)
		cal_key(i);
		
	for(i=0;i<3;i++)
		for(j=0;j<2;j++)
			printf(" \t %d ",key[i][j]);
	for(i=0;i<3;i++)
		printf("\n visited %d\n",visited[i]);	
	for(i=2;i>=0;i--)
		printf(" %d ---> ",visited[i]);

	
	// D*
	
	printf("\n Enter the source node ---> destination node to update path");
	
	scanf("%d %d",&s,&d);
	
	printf("\n update the cost :");
	scanf("%d",&cost);
	adj[s][d] = cost;
	printf("\n cost updated :");
	update_state(s);
	printf("\n update done from D* :");
	h[2] = 20;
	for(i=0;i<3;i++)
		cal_key(i);
 
	for(i=0;i<3;i++)
		for(j=0;j<2;j++)
			printf(" \t %d ",key[i][j]);
			
			
			
	shortest_path();
	
	
	for(i=0;i<3;i++)
		printf(" open list %d\n",open[i]);
	for(i=0;i<3;i++)
		printf(" rhs %d\n",rhs[i]);	
	for(i=0;i<3;i++)
		printf(" g %d\n",g[i]);	
	for(i=0;i<3;i++)
		cal_key(i);
		
	for(i=0;i<3;i++)
		for(int j=0;j<2;j++)
			printf(" \t %d ",key[i][j]);
	for(i=0;i<3;i++)
		printf("\n visited %d\n",visited[i]);	
	for(i=2;i>=0;i--)
		printf(" %d ---> ",visited[i]);
	return 0;
		
}
