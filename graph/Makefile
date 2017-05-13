


all: roads.exe
	cat roads.test1 | ./$< 

roads.exe: roads.cpp
	g++ --std=c++11  $< -o $@


clean: 
	rm -f *.exe 
