all:	cipher

cipher:	cipher.o Caesar.o Playfair.o Vignere.o RowTransposition.o Railfence.o
	g++ cipher.o caesar.o Playfair.o Vignere.o RowTransposition.o Railfence.o -o cipher -std=c++11

cipher.o:	cipher.cpp
	g++ -g -c cipher.cpp -std=c++11

Playfair.o:	Playfair.cpp Playfair.h CipherInterface.h
	g++ -g -c Playfair.cpp -std=c++11

Caesar.o: Caesar.cpp Caesar.h CipherInterface.h
	g++ -g -c Caesar.cpp -std=c++11

RowTransposition.o:	RowTransposition.cpp RowTransposition.h
	g++ -g -c RowTransposition.cpp -std=c++11

Railfence.o: Railfence.cpp Railfence.h
	g++ -g -c Railfence.cpp -std=c++11

Vignere.o: Vignere.cpp Vignere.h
	g++ -g -c Vignere.cpp -std=c++11

clean:
	rm -rf *.o *.gch cipher
