cc=gcc
flags=-Wall
obj=Servidor_TP6.o funciones.o
main: $(obj)
	$(cc) $(flags) -o $@ $^
clean:
	rm *.o main
