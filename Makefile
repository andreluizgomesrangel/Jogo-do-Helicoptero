all: compila
compila:
	g++ -o trabalhocg trab5.cpp Biblioteca.cpp Cenario.cpp Helicopter.cpp Tiro.cpp Circle.cpp Quad.cpp biblioteca_tiny/tinyxml2.cpp -lglut -lGL -lGLU
	@echo
	@echo ----------------------------------------
	@echo        COMPUTACAO GRAFICA
	@echo        TRABALHO FINAL        
	@echo   ANDRE LUIZ GOMES RANGEL DOS SANTOS
	@echo   GIULIANO LACERDA
	@echo ----------------------------------------
	@echo 



clean:
	rm *.o
