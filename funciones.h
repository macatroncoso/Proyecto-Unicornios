#ifndef funciones_h
#define funciones_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#include "hashmap.h"
#include "treemap.h"


typedef struct Pelicula{
    char * nombre;
     int anio;
    char * director;
    char * clasificacionEdad;
    List * genero;
    char * ranking;
} Pelicula;

typedef struct Usuario{
    char * username;
    List * Favoritos;
    List * UnicornFriend;
} Usuario;

 char *get_txt_field (char * , int );

char * toString(int );

void BusquedaPorGenero(HashMap *);

void BusquedaPorDirector(HashMap *);

int lower_than_string(void* , void* );

int lower_than_int(void* , void* );
//Pelis, rankingTree, Peliwis,clasifMap);

void peliculasfab(HashMap *,TreeMap*,TreeMap*,HashMap*,HashMap*);

void showMovieInformation(Pelicula * );

void getTypes(List * , char * );

void BusquedaPorAnio(TreeMap * );

Pelicula * crearPeli(char * , int ,  char * , char  *,List * , char * );

void searchByName(TreeMap * );

void busquedaPorClasif (HashMap *);

void busquedaPornombre(HashMap * );

void rankingMayMen (TreeMap * );

void rankingDado (TreeMap * );

void funcionRanking (TreeMap *);

void showMovieInfo (Pelicula * ); //Muestra la info completa del dato.

void importarpelis(HashMap*,TreeMap*,TreeMap*,HashMap*,HashMap*);

void cargarDatosUsuario(Usuario *);

//retorna 1 si ingresa correctamente, 0 en caso contario
int ingresarUsuario(Usuario **);

//retorna 1 si el usuario se crea correctamente, 0 en caso contario
int nuevoUsuario(Usuario **);


#endif // funciones_h
