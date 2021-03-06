PostPackagesCollection
======================	

		****************************************
		************* Tema 1 la SD *************
		*** Centru de Colectare a pachetelor ***
		****************************************
	
Detalii de implementare:

In rezolvarea acestei teme s-au folosit implementarile de stive si cozi
din laboratoarele anterior rezolvate, cu cateva modificari. 

Odata citit numarul N de ghisee, se aloca memorie pentru o serie de vectori
de dimemsiune N:
	- queues: 	  vector de cozi
	- stacks:     vector de stive
	- WEIGHT_MIN: aici se retine greutatea minima acceptata a fiecarei stiva
	- WEIGHT_MAX: aici se retine greutatea maxima acceptata a fiecarei stiva
	- Q:		  numarul maxim de elemente acceptate de fiecare stiva
	- K:		  greutatea maxima acceptata de fiecare stiva
	- working:    1 pentru ghiseu la care se lucreaza, 0 altfel
	
Explicarea implementarii fiecarei comenzi:

	* OPEN_WINDOW <WINDOW_ID> <WEIGHT_MIN> <WEIGHT_MAX> <Q> <K> *
Se deschide ghiseul cu indexul WINDOW_ID. Il marcam ca fiind functional,
asadar working[WINDOW_ID] devine 1. Apoi stabilim pe rand greutatea minima,
maxima, numarul maxim de elemente acceptate de stiva si greutatea maxima
acceptata de stiva

	* ADD_PERSON <PERSONAL_ID> <PACKAGE_WEIGHT> <WINDOW_ID> *
Se afla PERSONAL_ID si PACKAGE_WEIGHT si se adauga aceasta structura la
coada corespunzatoare ghiseului WINDOW_ID.
Cum coada nu are o limita, dimensiunea acesteia se mareste din 10 in 10, 
in functie de nevoie.

	* PROCESS <WINDOW_ID> <N_PEOPLE> *
Se elimina primii N_PEOPLE din coada WINDOW_ID si se adauga intr-un vector
persToProcess. Fiecare persoana este apoi procesata dupa cum urmeaza:
	Fiecare ghișeu are o stivă de pachete colectate.
	In momentul în care se procesează un pachet și el este acceptat, 
pachetul se pune în stiva ghișeului respectiv.
	Stiva poate ține maxim Q elemente si maxim K grame.
	Dacă se depășesc Q elemente sau K grame, stiva este golită și conținutul ei 
este trimis spre livrare.
	Atentie! Pachetul care nu a putut fi adǎugat deoarece stiva nu a putut 
să îl suporte va fi introdus în stivǎ dupǎ golirea acesteia.

	* PROCESS_ALL <WINDOW_ID> *
Se executa aceleasi operatii ca la PROCESS <WINDOW_ID> <N_PEOPLE>, acum insa
pe toate persoanele aflate la coasa WINDOW_ID

	* PRINT_STACKS * || * FLUSH_STACKS * || * PRINT_QUEUES *
Comenzi de afisare la iesirea standard despre starea stivelor si cozilor.
FLUSH_STACKS goleste in plus stivele.
