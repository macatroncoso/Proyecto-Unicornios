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
    char * genero;
    int year;
    int clasificacionEdad;
    char * director;
    char * ranking;
} Pelicula;

typedef struct Usuario{
    char * username;
    int password;
    List * Peliculas;
    List * Favoritos;
    List * UnicornFriend;

} Usuario;

 char *get_txt_field (char * , int );

char * toString(int );

int lower_than_string(void* , void* );

int lower_than_int(void* , void* );

void cargarDatosUsuario(char *);

//retorna 1 si ingresa correctamente, 0 en caso contario
int ingresarUsuario();

//retorna 1 si el usuario se crea correctamente, 0 en caso contario
int crearUsuario();


#endif // funciones_h
