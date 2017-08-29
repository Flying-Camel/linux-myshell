OBJECTS = mysh.o myset.o mycat.o myps.o mypwd.o mycd.o mycp.o mymkdir.o myls.o myhead.o mytail.o myrm.o mysort.o myenv.o myjobs.o

mysh : $(OBJECTS)
	gcc -o mysh $(OBJECTS)

mysh.o : mysh.c
	gcc -c mysh.c
myset.o : myset.c
	gcc -c myset.c
mycat.o: mycat.c
	gcc -c mycat.c
myps.o: myps.c
	gcc -c myps.c
mypwd.o: mypwd.c
	gcc -c mypwd.c
mycd.o: mycd.c
	gcc -c mycd.c
mycp.o: mycp.c
	gcc -c mycp.c

mymkdir.o: mymkdir.c
	gcc -c mymkdir.c

myls.o: myls.c
	gcc -c myls.c

myhead.o: myhead.c
	gcc -c myhead.c

mytail.o: mytail.c
	gcc -c mytail.c

myrm.o: myrm.c
	gcc -c myrm.c

mysort.o: mysort.c
	gcc -c mysort.c

myenv.o: myenv.c
	gcc -c myenv.c

myjobs.o: myjobs.c
	gcc -c myjobs.c

