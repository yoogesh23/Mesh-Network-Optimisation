#!/bin/bash

declare -A g
g=("1000" "1000" "1000")

declare -A rhs
rhs=("1000" "1000" "0")

declare -A open
open=("-1" "-1" "-1")

declare -A key
num_rows=3
num_columns=2

declare -A h 
h=("0" "10" "25")

declare -A adj
num_rows=3
num_columns=3
adj[0,0]=0
adj[0,1]=10
adj[0,2]=25
adj[1,0]=10
adj[1,1]=0
adj[1,2]=20
adj[2,0]=25
adj[2,1]=20
adj[2,2]=0

declare -A visited
visited=("-1" "-1" "-1")

declare -i start 
start= 0

declare -i goal 
goal= 2

declare -A sucs
num_rows=3
num_columns=2
sucs[0,0]=1
sucs[0,1]=2
sucs[1,0]=2
sucs[1,1]=-1
sucs[2,0]=-1
sucs[2,1]=-1

declare -A pred
num_rows=3
num_columns=2
pred[0,0]=-1
pred[0,1]=-1
pred[1,0]=0
pred[1,1]=-1
pred[2,0]=0
pred[2,1]=1

declare -i n
n = 0


cal_key () {
	if [ ${g[n]} -ge ${rhs[n]} ]
	then
   		key[$n,0] = ${rhs[n]}+${h[n]}
		key[$n,1] = ${rhs[n]}
	else
   		key[$n,0] = ${g[n]}+${h[n]}
		key[$n,1] = ${g[n]}
	fi
	
}

rem_visited(){
	declare -i i
	i = 0
	declare -i temp
	temp = 0
	while [ ${visited[i]} -ne $n -a $i -le 3 ]
	do
		i = $i + 1
	done
	while [ $i -le 3 ]
	do
		visited[$i]=${visited[$i+1]}

	done
		
	while((i<2))
	do
		visited[i]=visited[i+1];
		i++;
	done
	visited[i] = $n
}


add_visited () {	
	declare -i i
	i = 0
    	while [ ${visited[i]} -ne -1 -a $i -le 3 -a $n -le 3 ]
	do
		i = $i + 1
	done
	visited[i] = $n

}

rem_open(){
	declare -i i
	i = 0
	while [ $i -le 3 ]
	do
		if [ $n -eq ${open[i]} ]
		then
			open[i] = -1			  // if s in open then remove 
			add_visited()
		else
			i = $i + 1
		fi
	done
	
}

add_open(){
	declare -i i
	i = 0
    	rem_visited()					/// extra added later
	while [ ${open[i]} -ne -1 -a $i -le 3 -a $n -le 3 ]
	do
		i = $i + 1
	done	
	
	
	if [ $n -lt 3 ]; then
		open[i] = $n
	
}


min_rhs()
{	declare -i i
	i = 0
	declare -i k
	k = 0
	declare -i c
	c = 0
	declare -i min
	min = 1500
	
	for i in 0 1
	do	
		k = $sucs[$n,$i]
		c = $adj[$n,$k]
		c = $c+$g[$k]
		if [ $min -gt $c ]; then
			min = $c
		
	done
	
	rhs[$n] = $min
	
}


update_state(){	
	
	declare -i i
	i = 0
	declare -i flag
	flag = 0
	declare -i flag2
	flag2 = 0
	declare -i j
	j = 0
	for j in 0 1 2
	do
		cal_key $j
	done
	j = 0

	while [ $i  -lt 3 ]
	do
		if [ $n -eq ${visited[$i]} ]
		then
			flag = 1
			break
		else
			i = $i + 1
		fi
	done
	if [ $flag -eq 0 ]; then
		g[$n] = 1000
	
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
		
}}
