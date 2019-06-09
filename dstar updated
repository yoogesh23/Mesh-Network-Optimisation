#!/bin/bash

g=(1000 1000 1000)						# g(s) for all nodes are set to infinte 

rhs=(1000 1000 0)						# rhs(s) of all except goal is set infinte and rhs(goal) = 0
open=(-1 -1 -1)							# open list is empty 
declare -A key
num_rows=3
num_columns=2
h=(0 1 1)                               			# heuristics calculated based on the no of hops from start node

declare -A adj							#adjcency matrix has to path cost and need to be updated if cost changes 
num_rows=3
num_columns=3

adj[0,0]=0
adj[0,1]=10
adj[0,2]=25
adj[1,0]=1000
adj[1,1]=0
adj[1,2]=20
adj[2,0]=1000
adj[2,1]=1000
adj[2,2]=0

visited=(-1 -1 -1)

declare -i start=0                                		#start node; in our case its node '0'
declare -i goal=2 						# goal node; in our case its node '2'
			
declare -A sucs							# successors of each node
num_rows=3
num_columns=2
sucs[0,0]=1
sucs[0,1]=2
sucs[1,0]=2
sucs[1,1]=-1
sucs[2,0]=-1
sucs[2,1]=-1

declare -A pred							# predecessors of each node 
num_rows=3
num_columns=2
pred[0,0]=-1
pred[0,1]=-1
pred[1,0]=0
pred[1,1]=-1
pred[2,0]=0
pred[2,1]=1	

declare -i n=0

next=(-1 -1 -1)						#stores the next hop node of each node; path is extracted from this

cal_key () {	
	
	local i=0
	echo "cal_key"
	read llk
	while [ $i -lt 3 ]
	do
	
		if [ ${g[${i}]} -ge ${rhs[${i}]} ]
			then
			key[${i},0]=$((${rhs[${i}]}+${h[${i}]}))                #calculating key value for each node
			key[${i},1]=${rhs[${i}]}

		else
			key[${i},0]=$((${g[${i}]}+${h[${i}]}))
			key[${i},1]=${g[${i}]}
			
		fi
		i=$(($i+1))
	done
	#visited[${i}]=-1
	return
}



add_visited (){                            #adding a node to visited list.												   // once added to the visited list it need not be removed even added to 
	echo "add_visited"
	read llk
	local i=0 
	n="$1"			   # open list once again.
	
	if [ ${visited[0]} -eq -1 ]
	then
		visited[0]=$n
	
	else
	
		while [[ "${visited[${i}]}" != -1 && "$i" -lt 2 ]]
		do	
			                                       
			i=$(($i+1))
		done
	
		visited[${i}]=$n
	fi
	return
}
rem_open () {
	local -i i=0
	n="$1"
	echo "rem_open"
	read llk
	while [ $i -lt 3 ]
	do
		if [ "$n" -eq "${open[${i}]}" ]
		then
			open[${i}]=-1                         # if s in open then remove 
			add_visited "$n"
		else
			i=$(($i+1))
		fi
	done
}
add_open () {	
	local -i i=0
	n="$1"
	echo "add_open"
	read llk
	while ["${open[${i}]}" != -1] && [ "$i" -lt 3 ] && [ "$n" -lt 3 ]               #// adding s to open list
	do
		i=$(($i+1))
	done
	
	if ["$n" -lt 3 ]
	then
		open[${i}]="$n"
	fi
}
min_rhs (){
	local -i i=0
	local -i k=0
	local -i c=0
	local -i min =1500
	n="$1"
	echo "min_rhs"
	read llk
	for (( i=0; i<2; i++ ))
	do	
		k=${sucs[${n},${i}]}
		c=${adj[${n},${k}]}
		c="$c" + ${g[${k}]}
	
		if [ $min -lt $c ]
		then
			min="$c"
			
			next[${n}]="$k"                     #storing the path 
		
		fi
	done
	
	rhs[$n]="$min"
	
}
update_state (){	
	n="$1"
	echo "update_state"
	read llk
	local -i i=0
	local -i flag=0
	local -i flag2=0
		cal_key 
	
	
	while [ $i -lt 3 ]                           # s not visited
	do
		if [ $n=${visited[${i}]} ]
		then
			flag=1;
			break
		else
		
		  i=$(($i+1))
		fi
	done
	if [ $flag -eq 0 ]
	then
			g[$n]=1000; 
			 
		                        #  g(s) = infinite
	fi
	
	if [ $n != $goal ]
	then	
		
		min_rhs "$n"                               # rhs = min {c(s,s') + g(s') where s' belongs to succ of s} 
	fi
	i=0
	
	while [ $i -lt 3 ]
	do
		if [ ${open[${i}]} != -1 ] && [ ${open[${i}]} = $n ]
		then
			flag2=1									#	// if s is in open list  
		fi
		i=$(($i+1))
	done
	if [ "$flag2" = 1 ]
	then
		rem_open "$n"                             # remove s from open list
	fi
	
		
	if [ ${g["$n"]} != ${rhs["$n"]} ]                      # if s is inconsistant i.e. g(s)!=rhs(s) 
	then
		add_open "$n"
		                         # if g(s)!=rhs(s) then add to open list
	fi
	
	
}
min_key (){                                  #finds the minimum key and returns to the check loop function 
	echo "min_key" 									#//  for expanding in the shortest path
	read llk	
	local -i min=2
	local -i i=0
	local -i j
	local -i flag=0									
	
	cal_key
	j=-1                                                        
	i=0
	min=-1
	if [ ${open[0]} != -1 ]
	then
		min=0	
		i=1
		
		while [ ${open[${i}]} != -1 ] && [ "$i"-lt 3 ]
		do
			if [ ${key[${open[${i}]},0]} -lt ${key[${open[${min}]},0]} ]
				then
					min="$i"
				
			elif [ ${key[${open[${i}]},1]} -lt ${key[${open[${min}]},1]} ] && [ ${key[${open[${i}]},0]} = ${key[${open[${min}]},0]} ]
				then
					min="$i"
				
			else
					i=$(($i+1))
			fi
		done
	fi
	n=${open["$min"]}
	
			
		
	return "$min"
}
check_loop(){
	local -i i
	local -i j
	local -i min=0
	echo "check_loop"
	read llk
	cal_key
	
	min_key
	min="$?"
	if [ "$min" -eq -1 ]
	then
		return "0"
	fi

	if [[ "${key[${n},0]}" -lt "${key[${start},0]}" ]]
	then
			return "1"
			
	
	elif [ ${key[${n},1]} -lt ${key[${start},1]} ]
	then
			return "1"                                          # // checking the initial condition to enter shortest path
		
	
	elif [ "${rhs[${start}]}" != "${g[${start}]}" ]
	then
			return "1"
		
	fi
	
	
	return "0"
		
		
		
}
shortest_path (){	
	echo "shortest_path"
	read llk
	local -i i=0
	local -i z
	check_loop
	f="$?"
	while [ $f -eq 1 ]
	do	
		rem_open "$n"
		if [ ${g[${n}]} -gt ${rhs[${n}]} ]
		then	
			
			local -i i=0
			g[${n}]=${rhs[${n}]}
			
			while [ "$i" -lt 2 ] && [ ${pred["${n}","${i}"]} != -1 ]
			do   
			
				update_state "${pred[${n},${i}]}"
				i=$(($i+1))          									# // update predecesor of s
			done
			
			cal_key
		
		
		elif [ ${g[${n}]} -lt ${rhs[${n}]} ]                           #  // update predecesor U {s};  meaning updating s and then its preds
		then		
			g[${n}]=1000											#// g[s] = infinite
			update_state "$n"                             	
			i=0
			while [ "$i" -lt 2 ] && [ ${pred[${n},${i}]} != -1 ]
			do   
				update_state "${pred[${n},${i}]}" 				#// updating pred of s
				i=$(($i+1))                                                  
			done
			
		fi
		check_loop
		f="$?"
	done
}
print_path ()
{	echo "print_path"
	read llk
	local -i i=0
	#printf("\nPath is %d ",start);
	for (( i=0; i<2; i++ ))
	do
	
		if [ "${next[${i}]}" != "$goal" ]
		then
			echo "------>" ${next[${i}]}
			#printf("---> %d",next[i]);   
		                                									#  // printing path
		elif [ "${next[${i}]}" == "$goal" ]
		then
			echo "------>" ${next[${i}]}
			#printf("---> %d\n",next[i]);
			break
		fi
	done
	return	
}
change_cost()
{	
	local -i s
	local -i d
	local -i cost
	#// Test space for twin route replanning
	echo "change_cost"
	read llk
	local -i node
	local -i s2
	local -i d2
	local -i cost2
	local -i i
	local -i source1
	local -i dest1
	local -i source2
	local -i dest2
#//	printf("\n Enter the node to be moved ");
#//	scanf("%d",&node);                                                         // node to be moved
	
	echo "Enter source node"
	read s
	echo "Enter desti node"
	read d
	echo "cost"
	read cost
	echo "cost updates"
#	update_state"$s"                                             updating 1st link
	#adj[${s2},${d2}]=$cost2;
	for(( i = 0; i<2; i++ ))
	do
		if [ "${sucs[$s,$i]}" = $d ]
		then
			adj[$s,$d]=$cost
			source1=$s
			dest1=$d		#// finding the source and destination node from the link
			break

		elif [ ${pred[$s,$i]} = $d ]
		then
			adj[$d,$s]=$cost
			source1=$d
			dest1=$s
			break
		fi
	done
	
	
	echo "Enter source node"
	read s2
	echo "Enter desti node"
	read d2
	echo "cost"
	read cost2
	echo "cost updates"
	adj[${s2},${d2}]=$cost2
	for(( i=0; i<2; i++ ))
	do
		if [ ${sucs[$s2,$i]} = $d2 ]
		then
			adj[$s2,$d2]=$cost2
			source2=$s2
			dest2=$d2  #                      	// finding the source and destination node from the link
			break

		elif [ pred[$s2,$i] = $d2 ]
		then
			adj[$d2,$s2]=$cost2
			source2=$d2
			dest2=$s2
			break
		fi
	done

	#// characterisation block for finding the moved node
	
	if [ $source1 -eq $dest2 ]
	then
		node=$source1

	elif [ $source2 -eq $dest1 ]
	then
		node=$source2
	fi
	
	#//characterisation done; node identified
	if [ $node -eq 1 ]                                                          
	then
		update_state "1"     #   // update preference for different nodes
		update_state "$start"
		cal_key
	
	elif [ $node -eq $start ]
	then
		update_state "$start"
		cal_key
	
	elif [ $node -eq $goal ]
	then
		update_state "1"
		update_state "$start"
		cal_key
	fi
	
	shortest_path
	cal_key
	print_path
}
main (){	
	local -i i=0
	
	
	g[2]=1000											#// 1000 ~ infinite
	rhs[2]=0											#		// Initilization
	open[0]=2
	echo "main"
	read llk
	cal_key 
	shortest_path 
	cal_key
	print_path                        				#first run
	while [ "$i" -lt 5 ]
	do
		change_cost  #changing the cost for 3 times as i<3
		i=$(($i+1))
	done
	return 0
		
}
main
