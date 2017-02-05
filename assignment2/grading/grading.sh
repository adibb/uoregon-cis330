gcc -std=c99 -c triangle1.c
diff -y -B -b triangle1.output triangle1.master
numdiffs=`diff  -B -b triangle1.output triangle1.master | wc -l`
gcc -std=c99 -c triangle2.c
./test-triangle2
diff -y -B -b triangle2.output triangle2.master
numdiffs=`diff  -B -b triangle2.output triangle2.master | wc -l`
gcc -std=c99 -c test.c
./test
diff -y -B -b test.output test.master
numdiffs=`diff  -B -b test.output test.master | wc -l`
gcc -std=c99 -c mountain.c
./mountain
diff -y -B -b mountain.output mountain.master
numdiffs=`diff  -B -b mountain.output mountain.master | wc -l`
gcc -std=c99 -c main.c
./main
diff -y -B -b main.output main.master
numdiffs=`diff  -B -b main.output main.master | wc -l`
