ifndef SGDK
$(error Defina a variável de ambiente SGDK apontando para a instalação do SGDK)
endif

all:
	make -f $(SGDK)/makefile.gen

clean:
	make -f $(SGDK)/makefile.gen clean

.PHONY: all clean
