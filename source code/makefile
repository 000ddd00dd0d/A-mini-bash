OBJECTS=myshell.o utility.o type_prompt.o read_command.o cd.o echo.o\
		dir.o showenviron.o myshell_ins.o help.o
myshell: ${OBJECTS}
	gcc -o myshell ${OBJECTS}
myshell.o: myshell.c myshell.h
utility.o: utility.c myshell.h
type_prompt.o: type_prompt.c
read_command.o: read_command.c
cd.o: cd.c
dir.o: dir.c
echo.o: echo.c
myshell_ins.o: myshell_ins.c myshell.h
help.o: help.c
showenviron.o: showenviron.c
clean:
	rm -f *.o