all: main

main:
	cl main.cpp
	main 

clean: 
		del *.obj
		del *.exe 