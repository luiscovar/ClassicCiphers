all:	cipher

cipher:	cipher.o Caesar.o
	g++ cipher.o Caesar.o -o cipher -std=c++11

cipher.o:	cipher.cpp
	g++ -g -c cipher.cpp -std=c++11

#Playfair.o:	Playfair.cpp Playfair.h CipherInterface.h
#	g++ -g -c Playfair.cpp

Caesar.o: Caesar.cpp Caesar.h CipherInterface.h
	g++ -g -c Caesar.cpp -std=c++11
# Uncomment this code once you add the appropriate files
#RowTransposition.o:	RowTransposition.cpp RowTransposition.h
#	g++ -g -c RowTransposition.cpp


clean:
	rm -rf *.o cipher
