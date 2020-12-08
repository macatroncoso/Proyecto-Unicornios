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
    int k1 = (int*) (key1);
    int k2 = (int*) (key2);
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
        if (par!=NULL){
          peli = par->value;
        }
        else break;
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
        if (strcmp(peli->director, name)==0){
            printf("%s\n", peli->nombre);
        }
        par = nextMap(map);
        if (par!=NULL){
          peli = par->value;
        }
        else break;
    }
    system("pause");
    system("cls");
}

void BusquedaPorAnio(TreeMap * map){
    system("cls");
    int option;
    int anio_;

    do{
            printf("Busqueda por anio: \n");
            printf("Opcion 1: Busqueda por un anio en particular \n");
            printf("Opcion 2: Mostrar todas las peliculas de la base de datos ordenados de menor a mayor \n");
            scanf("%d",&option);
            if ((option > 2) || (option < 1)){
                printf("Ingrese una opcion valida! \n");
            }
            if (option == 1){
                do{
                    printf("Ingrese el anio que desea buscar: ");
                    fflush(stdin);
                    scanf("%d",&anio_);
                    fflush(stdin);
                    if (searchTreeMap(map, anio_)== NULL){
                        printf("No se encontro el anio, ingrese otro anio \n");
                    }

                }while(searchTreeMap(map,anio_)==NULL);

                void * name = searchTreeMap(map, anio_);
                if (name==NULL) break;
                while(isEqual(map,map->current->key,anio_)){
                    printf("Anio: %d \t Nombre pelicula: %s\n",map->current->key, name);
                    name = nextTreeMap(map);

                }




            }
            else{
                printf("Peliculas ordenadas de menor a mayor: \n");
                imprimemeEnOrden(map->root);
            }

    }while ((option > 2) || (option < 1));

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

void importarpelis(HashMap* Pelis, TreeMap *ranking, TreeMap *peliwis){
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
            
            if (searchTreeMap(rankingTree, ranking) == NULL){
                List * listaRanking =create_list();
                push_back(listaRanking, nuevaPeli);
                insertTreeMap(rankingTree, ranking, listaRanking);
            }
            else{
                List * auxList= searchTreeMap(rankingTree, ranking);
                push_back(auxList, nuevaPeli);
               
            }

            if (searchMap(clasifMap, clasificacionEdad) == NULL ){
                List * listaClasif = create_list();
                push_back(listaClasif, nuevaPeli);
                insertMap(clasifMap, clasificacionEdad, listaClasif);
            }
            else{
                List * auxList= searchMap(clasifMap, clasificacionEdad);
                push_back(auxList, nuevaPeli);
            }
        }
        insertTreeMap(peliwis,anio , nombre);
    }
}

void funcionRanking (TreeMap * rankingTree){
    int opcion;
    printf("******Submenu de ranking******\n\n");
    printf("(1) Para mostrar las peliculas mediante un ranking especifico\n");
    printf("(2) Para mostrar las peliculas por orden de ranking, de mayor a menor\n");
    printf("Ingrese la opcion que desee (1 o 2) \n\n");
    do{
        scanf("%d",&opcion);
        if(opcion != 1 && opcion != 2){
            printf("La opcion ingresada es invalida\n");
            printf("Elija la funcion 1 o 2\n");
        }
    }while (opcion != 1 && opcion != 2);

    if (opcion == 1){
        rankingDado(rankingTree);
    }
    else{
        rankingMayMen(rankingTree);
    }
    return;
}

void rankingDado (TreeMap * rankingTree){

    fflush(stdin);
    char * ranking[50];
    List * listaAux;
    Pelicula * resultAux;
    printf("Ingrese el ranking de la pelicula que desea buscar\n");
    printf("El numero debe estar entre 1 y 10\n");
    fflush(stdin);

    //do{
    scanf("%s", &ranking);

    listaAux = searchTreeMap(rankingTree, ranking);

    resultAux= first(listaAux);
    if (listaAux == NULL){
        printf("El ranking ingresado no pertenece a alguna pelicula de la base de datos\n");
        return;
    }

    printf("Pelicula/as con ranking %s\n", ranking);

    resultAux= first(listaAux);
    while (resultAux != NULL){
        showMovieInfo(resultAux);
        resultAux= next(listaAux);
    }
    printf("\n\n");
    return;

}

void rankingMayMen (TreeMap * rankingTree){
    printf("\n");

    if (rankingTree == NULL) return; // If tree is empty
    Pelicula * auxPeli; //auxVar to save info and show it
    List * auxLista;
    auxLista= lastTreeMap (rankingTree); //gets the last value, higher from map

    while (auxLista != NULL){

        auxPeli= first(auxLista);
        while(auxPeli != NULL){
            showMovieInfo (auxPeli);
            auxPeli= next(auxLista);
        }
        auxLista= backTreeMap(rankingTree); //Previous value, lower than current
    }
    printf("\n\n");
    return;
}
void busquedaPorClasif (HashMap * clasifMap){
    char * clasif[50];
    List * listaAux;
    Pelicula * resultAux;
    printf("Por favor ingrese la clasificacion de edad mostrar peliculas\n");
    scanf(" %s",&clasif);

    if (clasifMap == NULL){
        printf("No hay peliculas guardadas en la base de datos\n");
        return;
    }
    if (searchMap(clasifMap,clasif)==NULL){
        printf("La clasificacion ingresada no pertenece a alguna pelicula de la base de datos\n");
        return;
    }
    listaAux= searchMap(clasifMap,clasif);

    printf("Pelicula/as con clasificacion %s\n " , clasif);

    resultAux= first(listaAux);


    while (resultAux != NULL){
        showMovieInfo(resultAux);
        //if (->next == NULL)return;
        resultAux= next(listaAux);

    }
    printf("\n\n");\
    return;
}
