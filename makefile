cc=gcc
exec=playmusic
obj=main.o link.o
flags=-Wall

$(exec):$(obj)
	$(cc) $^ -o $@ $(flags)
%.o:%.c
	$(cc) -c $< -o $@ $(flags)
clean:
	rm $(exec) $(obj)