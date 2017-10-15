# TEC-Royale
## Tecnologico de Costa Rica, sede Alajuela, Proyecto 1, Principios de sistemas operativos, II Semestre, 2017
## Estudiantes: Jason David Espinoza - 2015073934, Jose Miguel Hernandez - 2015079760

### Version 1.3
* Se cuenta con todas las funcionalidades de la biblioteca mypthread, incluyendo 3 algoritmos diferentes de scheduling

* Se crea el mazo de cartas con un algoritmo genetico, provocando que las nuevas cartas aumenten de nivel y sus atributos de batalla mejoren. Las primeras cartas son los guerreros basicos, siempren salen en el mismo orden

* Se puede seleccionar una carta cuando quiera sin interrumpir el proceso del juego

* Los guerreros en el campo de batalla se moveran solos, buscando la torre enemiga

* Siempre que se escoge un guerrero, este caera justo al frente de la torre principal, y el mismo guerrero decide hacia donde ir, si por el camino de arriba o por el camino de abajo

### Como jugar?
De primera entrada vera el tablero con solo las torres y los puentes, y debajo del tablero estaran 5 cartas, para escoger una carta solo debe de presionar los numeros que van del 1 al 5, para escoger la carta correspondiente.
Apenas presiona el numero, se generara una nueva carta y el guerrero escogido caera en el campo de batalla.

### Bibliografia

* A Library Implementation of POSIX Threads under UNIX. (1993). San Diego. Retrieved from http://moss.csc.ncsu.edu/~mueller/ftp/pub/PART/pthreads_usenix93.pdf
* Implementing a Thread Library on Linux. (2002). Evan Jones. Retrieved from http://www.evanjones.ca/software/threading.html
*  Matthew, N., & Stones, R. (2008). Beginning Linux® Programming (4th ed.). Indianapolis: Wiley Publishing, Inc.
