#include "funciones.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

char * _strdup (const char *s) {
    size_t len = strlen (s) + 1;
    void *new = malloc (len);

    if (new == NULL)
    	return NULL;

    return (char *) memcpy (new, s, len);
}

char *get_csv_field (char * tmp, int k) {

    char * tmpDup = _strdup(tmp);

    const char character[2] = ",";
    char *token = (char *) malloc (50 * sizeof (char));

    int i = 0;

    token = strtok(tmpDup, character);

    while(i < k && token != NULL){

        token = strtok(NULL, character);
        i++;
    }

    return token;
}

int lower_than_string(void* key1, void* key2){
    char* k1=(char*) key1;
    char* k2=(char*) key2;
    if(strcmp(k1,k2)<0) return 1;
    return 0;
}

int lower_than_int(void* key1, void* key2){ //This function compare 2 keys *int
    int k1 = *((int*) (key1));
    int k2 = *((int*) (key2));
    return k1<k2;
}

char * toString(int id){

 //function that convert a string to a int
    int digitos = 0;
    int aux = id;
    int numAlreves = 0;
    int auxDigitos;

    while(aux != 0){

        aux = aux / 10;
        digitos++;

    }

    aux = id;
    auxDigitos = digitos;
    digitos--;

    char * idString = (char *) malloc ( (auxDigitos + 1) * sizeof(char));

    while(aux != 0){

        numAlreves = numAlreves + ( (aux % 10) * pow(10, digitos) );
        aux = aux / 10;
        digitos--;

    }

    aux = id;
    digitos = auxDigitos;
    int i = 0;

    while(numAlreves > 0){

        idString[i] = (numAlreves%10) + 48;
        i++;
        numAlreves = numAlreves / 10;

    }

    idString[i] = '\0';

    return idString;

}

void cargarDatosUsuario(char * nombreUsuario){

    printf("Se cargan los datos\n");
    return;

}

int esNombreValido(char * nombreUsuario){

    size_t length = strlen(nombreUsuario);
    int i;

    for (i = 0 ; i < length ; i++){

        if(isalpha(nombreUsuario[i]) == 0 && isdigit(nombreUsuario[i]) == 0){

            return 0;

        }

    }

    return 1;

}

int usuarioExiste(char * nombreUsuario){

    FILE * usuariosCSV = fopen("Usuarios.csv", "r");
    if(usuariosCSV == NULL){

        printf("\nError");

    }

    char linea[2048];
    fgets(linea, 2047, usuariosCSV);

    char * usuarioObtenido = get_csv_field(linea, 0);

    int cont = 1;

    while(usuarioObtenido != NULL){

        if(strcmp(usuarioObtenido, nombreUsuario) == 0){

            return 1;

        }

        usuarioObtenido = get_csv_field(linea, cont);
        cont++;

    }

    return 0;

}

int ingresarUsuario(){

    char nombreUsuario[30];

    printf("\nIngrese el nombre del usuario existente: ");

    fflush(stdin);
    scanf("%[^\n]s", nombreUsuario);
    fflush(stdin);

    if(usuarioExiste(nombreUsuario)){

        cargarDatosUsuario(nombreUsuario);

    }
    else{

        printf("\nEL usuario no se encuentra, por favor, cree un nuevo usuario\n\n");
        return 0;

    }

    return 1;


}

int crearUsuario(){

    char nombreUsuario[30];

    printf("\nIngrese el nombre del usuario nuevo: ");

    fflush(stdin);
    scanf("%[^\n]s", nombreUsuario);
    fflush(stdin);

    FILE * fp;

    char nombreArchivo[50];

    strcpy(nombreArchivo, "Usuarios/");
    strcat(nombreArchivo, nombreUsuario);
    strcat(nombreArchivo,".csv");

    if(esNombreValido(nombreUsuario)){

        if(!usuarioExiste(nombreUsuario)){

            fp = fopen(nombreArchivo, "w"); //creamos el nuevo archivo
            if(fp == NULL){

                printf("\nError al crear el archivo\n\n");
                return 0;

            }

            FILE * archivoCSV = fopen("Usuarios.csv", "r+");
            if(archivoCSV == NULL){

                printf("\nError al crear el archivo\n\n");
                return 0;

            }

            //para comprobar si es que el archivo está vacio o no
            fseek (archivoCSV, 0, SEEK_END);
            long lSize = ftell(archivoCSV);

            //si es que esta vacio agregamos sin coma al principio
            if(lSize == 0){

                fprintf(archivoCSV, "%s", nombreUsuario);
                fclose(archivoCSV);

            }
            else{

                fprintf(archivoCSV, ",%s", nombreUsuario);

                fclose(archivoCSV);

            }

        }
        else{

            printf("\nYa existe un usuario con este nombre registrado\n\n");
            return 0;

        }

    }
    else{

        printf("\nEl nombre de usuario solo pude contener numeros y letras\n\n");
        return 0;

    }

    printf("\nUsuario creado con exito.\n\n");
    system("pause");
    system("cls");

    return 1;

}

void BusquedaPorGenero(HashMap * map){
    system("cls");
    printf("Ingrese el genero que desea buscar: ");
    char genero_[50];
    fflush(stdin);
    scanf("%[^\n]s", genero_);
    fflush(stdin);

    List * lista = create_list();

    Pair * par = firstMap(map);
    Pelicula * peli = par->value;
    while(par!=NULL){

        lista = peli->genero;
        char * gen = first(lista);
        if (gen!= NULL && strcmp(gen, genero_)==0){
            printf("%s\n", peli->nombre);
        }
        else{
            while(gen!=NULL){
            gen=next(lista);
            if (gen!=NULL && strcmp(gen, genero_)==0){
                printf("%s\n", peli->nombre);
            }
            }
        }

        par = nextMap(map);
        peli = par->value;
    }
    system("pause");
    system("cls");
}


void BusquedaPorDirector(HashMap *map){
    system("cls");

    printf("Ingrese el nombre y apellido del director que desea buscar: ");
    char name[50];
    fflush(stdin);
    scanf("%[^\n]s", name);
    fflush(stdin);

    Pair * par = firstMap(map);
    Pelicula * peli = par->value;
    while(par!=NULL){
        if (strcmp((char*)peli->director, (char*)name)==0){
            printf("%s\n", peli->nombre);
        }
        par = nextMap(map);
        peli = par->value;
    }
    system("pause");
    system("cls");

}

void getTypes(List * typesList, char * types){

//function that get the different types of the game :)

    char caracter[2] = "/";
    char * type;

    type = strtok(types, caracter); //separates the string if there's more than one type//
    while(type != NULL){

        if(type[0] == ' '){

            size_t si_ze = strlen(type);
            int i;
            for (i = 0 ; i < si_ze - 1; i++){

                type[i] = type[i + 1];

            }

            type[si_ze - 1] = '\0';

        }
        push_back(typesList, type);
        type = strtok(NULL, caracter);

    }

}






Pelicula * crearPeli(char * nombre,  List * genero, char *  director , char *  ranking, char  * clasificacionEdad, int  anio){

    Pelicula * peliwi = (Pelicula *) malloc (sizeof(Pelicula));
    peliwi->nombre = nombre;
    peliwi->genero = genero;
    peliwi->director = director;
    peliwi->ranking = ranking;
    peliwi->clasificacionEdad = clasificacionEdad;
    peliwi->anio = anio;
    return peliwi;


}

void importarpelis(HashMap* Pelis){
    //very important function that imports all the games from a csv file

    system("cls");

    FILE * fp;

        fp = fopen("Pelis.txt", "r"); //opens the file in read

    char line [1024];

    while( fgets(line, 1023, fp) != NULL ){  //read and get every field of the csv file

        char * nombre = get_csv_field(line, 0);
        int anio = atoi(get_csv_field(line, 1));

        List * Geneross = create_list();

        char * director = get_csv_field(line, 2);
        char * clasificacionEdad = get_csv_field(line, 3);
        char * Genero = get_csv_field(line, 4);
        getTypes(Geneross, Genero);

        char * ranking = get_csv_field(line, 5);

        Pelicula * nuevaPeli = crearPeli(nombre,Geneross, director, ranking, clasificacionEdad, anio);
        if (searchMap(Pelis, nombre) == NULL){
            insertMap(Pelis, nuevaPeli->nombre ,nuevaPeli);

    }

}

}
