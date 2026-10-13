ifndef SGDK_PATH
$(error Defina a variável de ambiente SGDK_PATH apontando para a instalação do SGDK)
endif

all:
	make -f $(SGDK_PATH)/makefile.gen

clean:
	make -f $(SGDK_PATH)/makefile.gen clean

.PHONY: all clean
