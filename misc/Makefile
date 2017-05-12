


all: queue_two_stack.exe making_anagrams.exe 
	./$< 

queue_two_stack.exe: queue_two_stack.cc
	g++ --std=c++11  $< -o $@

making_anagrams.exe: making_anagrams.cc
	g++ --std=c++11  $< -o $@

clean: 
	rm -f *.exe 
