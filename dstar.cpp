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
	if [ $n -ne $goal ]; then
		min_rhs $n			   //  min sE succ
	i = 0
	
	
	while [ $i -lt 3 ]
	do
		if [ ${open[i]} -ne -1 -a  ${open[i]} -eq $n ]; then
		flag2 = 1
		
		i = $i + 1
	done
	if [ $flag2 -eq 1 ]; then
		rem_open $n
	
		
	if [ ${g[n]} -ne ${trhs[n]} ]; then
		add_open $n                           // if g(s)!=rhs(s) then add to open list
	
	
}

min_key(){
	declare -i i
	i = 0
	declare -i flag
	flag = 0
	declare -i min
	min = 2
	declare -i j
	j = 0
	int min=2,i=0,j, flag =0;
	for((j=0;j<3;j++))
	do
		cal_key $j
	done
	j = -1
		
	i = 0
min = -1
if [ ${open[0]} -ne -1 ]; 
then
min =0	
i=1

while [ ${open[i]} -ne -1 -a $i -lt 3 ]
do
	if [ ${key[${open[i]}][0]} -lt ${key[${open[min]}][0]} ]; then
		min = i
				
			
			
		
	else if [ ${key[${open[i]}][1]} -lt ${key[${open[$min]}][1]} -a ${key[${open[$i]}][0]} -eq ${key[${open[$min]}][0]} ]; then
		min =i
	else
		i = $i + 1
	
done
}
	n = ${open[min]}
	//	n = min                                          // changing the code

	return min;                      %% should change
}

check_loop(){
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

shortest_path()
{	
	echo "IN SHORTEST PATH"
	declare -i i=0
	declare -i z=0
	declare -i kl=0
	kl=check_loop
	
	while[ $kl ]
	do	
		echo "In value of n is $n"
		rem_open $n
		if [ ${g[n]} -ge ${rhs[n]} ]
		do	
			i=0
			g[n]=${rhs[n]}
			#printf("/n g[0] %d",g[n]);
			#printf("\n rhs[n] %d",rhs[n]);
			while [ $i -le 1 -a ${pred[n]} -ne -1 } ]
			do   
				#printf("\n\nexpanding %d\n",pred[n][i]);
				update_state ${pred[n,i]} 
				i=$i+1    // update predecesor of s
			done
			#printf("In pred update end\n");
			for(( j=0; j<3; j++ ))
			do
				cal_key $j
			done
			declare -i i			
			for(i=0;i<3;i++)
			do
			declare -i r
				for(( r=0; r<2; r++ ))
				do
					echo -n ${key[i,r]}
				done
			declare -i q
			for(( q=0; q<3; q++ ))
			do
				echo -n "g" ${g[q]}
			done	
		done
	done
}


declare -i i=0
declare -i z=0
declare -i j=0
declare -i cost=0
echo ("In main \n");

	
g[2]=1000
rhs[2]=0
open[0]=2

for(( i=0; i<3; i++ ))
do
	echo "open list" ${open[i]}
done

for(( i=0; i<3; i++ ))
do
	cal_key $i
done

read $z
shortest_path

for(( i=0; i<3; i++ ))
do
	echo "open list" ${open[i]}
done

for(( i=0; i<3; i++ ))
do
	echo "rhs" ${rhs[i]}	
done

for(( i=0; i<3; i++ ))
do
	echo "g" ${g[i]}	
done

for(( i=0; i<3; i++ ))
do
	cal_key $i
done
		
for(( i=0; i<3; i++ ))
do
	for(( j=0; j<2; j++ ))
		do
			echo -n ${key[i,j]}
		done
done
for(( i=0; i<3; i++ ))
do
	echo "visited" ${visited[i]}
done
for(( i=2; i>=0; i-- ))
do 
	echo ${visied[i]} "------>"
done

#D*

echo "Enter source node"
read s
echo "Enter desti node"
read d
echo "cost"
read cost
echo "cost updates"
update_state $s

echo "update done for D*"

h[2]=20;

for(( i=0; i<3; i++ ))
do
	cal_key $i
done

for(( i=0; i<3; i++ ))
do 
	for(( j=0; j<2; j++ ))
	do
		echo -n ${key[i,j]}
	done
done

shortest_path

for(( i=0; i<3; i++ ))
do
	echo "open list" ${open[i]}
done

for(( i=0; i<3; i++ ))
do
	echo "rhs" ${rhs[i]}	
done

for(( i=0; i<3; i++ ))
do
	echo "g" ${g[i]}	
done

for(( i=0; i<3; i++ ))
do
	cal_key $i
done
		
for(( i=0; i<3; i++ ))
do
	for(( j=0; j<2; j++ ))
		do
			echo -n ${key[i,j]}
		done
done
for(( i=0; i<3; i++ ))
do
	echo "visited" ${visited[i]}
done
for(( i=2; i>=0; i-- ))
do 
	echo ${visied[i]} "------>"
done
