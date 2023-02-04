cp prog tests/solution
cd tests
for (( t = 1; t <= 10; t++ ));
do
	a=`cat $t.in`
	if [[ ("$a" = "") ]];
	then
		continue 
	fi

    ./solution preprocess --nodes "$t.nodes" --edges "$t.edges" --output "graph.b"
	touch out.txt
	./solution search --graph "graph.b" --input "$t.in" --output out.txt
	
	a=`diff "$t.out" -q out.txt`
	if [[ ("$a" = "") ]];
	then
		echo "Test $t OK"
	else
		echo "Test $t WA"
		break
	fi
	rm -rf "out.txt" "graph.b"
done