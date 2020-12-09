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

    if(token != NULL){

        int i;
        for ( i = 0 ; i < strlen(token) ; i++){

            if(token[i] == '\n') token[i] = '\0';

        }

    }

    return token;
}

int lower_than_string(void* key1, void* key2){
    char* k1=(char*) key1;
    char* k2=(char*) key2;
    if(strcmp(k1,k2)<0) return 1;
    return 0;
}

int lower_than_int(void* key1, void* key2){ 
/*esta funcion compara 2 keys int*/
    int k1 = (int*) (key1);
    int k2 = (int*) (key2);
    return k1<k2;
}

char * toString(int id){
/*Función que convierte una string a un int*/
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

int esNombreValido(char * nombreUsuario){
/*se valida el u¿nombre del usuario*/
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
/*se verifica que el usuario exista*/
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

Usuario * crearUsuario(char * username){

    Usuario * usuario = (Usuario *) malloc (sizeof(Usuario));
    if(usuario == NULL) printf("Error\n\n");

    usuario->username = _strdup(username);
    usuario->Favoritos = create_list();
    usuario->UnicornFriend = create_list();

    return usuario;

}

void cargarDatosUsuario(Usuario * usuario){
    /*se cargan los los datos favoritos del usuario*/
    char nombreArchivo[70];

    strcpy(nombreArchivo, "Usuarios/");
    strcat(nombreArchivo, usuario->username);
    strcat(nombreArchivo, "Favoritos.csv");

    FILE * fp = fopen(nombreArchivo, "r");
    char linea[1024];
    fgets(linea, 1023, fp);

    int cont = 0;

    while(get_csv_field(linea, cont) != NULL){

        push_back(usuario->Favoritos, get_csv_field(linea, cont));
        cont++;
    }

    fclose(fp);
    linea[0] = '\0';

    /*se cargan los amigos*/

    char nombreArchivoAmigos[70];

    strcpy(nombreArchivoAmigos, "Usuarios/");
    strcat(nombreArchivoAmigos, usuario->username);
    strcat(nombreArchivoAmigos, ".csv");

    fp = fopen(nombreArchivoAmigos, "r");

    fgets(linea, 1023, fp);

    cont = 0;

    while(get_csv_field(linea, cont) != NULL){

        push_back(usuario->UnicornFriend, get_csv_field(linea, cont));
        cont++;
    }

    fclose(fp);

    printf("\nDatos cargados correctamente\n\n");
    system("pause");
    system("cls");

}

int ingresarUsuario(Usuario ** usuario){
/*en base a la verificacion de usuario se ingresa un nombre para acceder en caso de que este exista en la base de datos, de lo contrario se solicita la creacion de este*/
    char nombreUsuario[30];

    printf("\nIngrese el nombre del usuario existente: ");

    fflush(stdin);
    scanf("%[^\n]s", nombreUsuario);
    fflush(stdin);

    if(usuarioExiste(nombreUsuario)){

        *usuario = crearUsuario(nombreUsuario);
        cargarDatosUsuario(*usuario);

    }
    else{
/*aqui se solicita el crear el usuario de no existir el ingresado*/
        printf("\nEL usuario no se encuentra, por favor, cree un nuevo usuario\n\n");
        system("pause");
        system("cls");
        return 0;
    }

    return 1;

}

void BusquedaPorAnio(TreeMap * map){
/*esta funcion busca las peliculas por el año y da la opcion de buscarlas por año especifico o entrega todas las peliculas ordenadas de menor a mayor*/
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

int nuevoUsuario(Usuario ** usuario){
/*se crea un usuario nuevo realizando las comprobaciones de no repitencia de nombres ademas de las solicitudes de caracteres que puede poseer*/
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

            fp = fopen(nombreArchivo, "w"); /*creamos el nuevo archivo*/
            if(fp == NULL){

                printf("\nError al crear el archivo\n\n");
                return 0;

            }

            FILE * archivoCSV = fopen("Usuarios.csv", "r+");
            if(archivoCSV == NULL){

                printf("\nError al crear el archivo\n\n");
                return 0;

            }

            /*para comprobar si es que el archivo está vacio o no*/
            fseek (archivoCSV, 0, SEEK_END);
            long lSize = ftell(archivoCSV);

            /*si es que esta vacio agregamos sin coma al principio*/
            if(lSize == 0){

                fprintf(archivoCSV, "%s", nombreUsuario);
                fclose(archivoCSV);

            }
            else{

                fprintf(archivoCSV, ",%s", nombreUsuario);
                fclose(archivoCSV);

            }

            /*luego reservamos memoria para un dato usuario y lo asignamos al usuario pasado por parametro*/
            *usuario = crearUsuario(nombreUsuario);

        }
        else{

            printf("\nYa existe un usuario con este nombre registrado\n\n");
            system("pause");
            system("cls");
            return 0;

        }

    }
    else{

        printf("\nEl nombre de usuario solo pude contener numeros y letras\n\n");
        system("pause");
        system("cls");
        return 0;

    }

    printf("\nUsuario creado con exito.\n\n");
    system("pause");
    system("cls");

    return 1;

}

void BusquedaPorGenero(HashMap * map){
/*se realiza la busqueda en la base de datos de acuerdo al genero solicitado entregando todas las peliculas que correspondan al genero */
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
            showMovieInformation(peli);
        }
        else{
            while(gen!=NULL){
            gen=next(lista);
            if (gen!=NULL && strcmp(gen, genero_)==0){
                showMovieInformation(peli);
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

void BusquedaPorDirector(HashMap *PelisDirector){
/*se busca en la base de datos la pelicula por nombre del director y se muestran por pantalla */    
    char * director[50];
    List * listaAux;
    Pelicula * resultAux;
    printf("Por favor ingrese el director que busca\n");
    fflush(stdin);
    scanf("%[^\n]s",director);
    fflush(stdin);

    if (firstMap(PelisDirector) == NULL){
        printf("No hay peliculas guardadas en la base de datos\n");
        return;
    }
/**/
    if (searchMap(PelisDirector,director)==NULL){/*se valida que el director tenga alguna pelicula en la lista*/
        printf("El director ingresado no pertenece a alguna pelicula de la base de datos\n");
        return;
    }
    listaAux= searchMap(PelisDirector,director);

    printf("Pelicula/as con director %s\n " , director);

    resultAux= first(listaAux);


    while (resultAux != NULL){
        showMovieInformation(resultAux);
        //if (->next == NULL)return;
        resultAux= next(listaAux);

    }
    printf("\n\n");\
    return;
}

void showMovieInformation(Pelicula * peli){
/*esta función es muy importante para nuestro programa, porque se usa en casi todas las funciones que buscan por categoría*/
    printf("\n");
    printf("Nombre de la pelicula: %s\n", peli->nombre);
    printf("Anio de la Pelicula: %d\n", peli->anio);

    printf("Director/es de la Pelicula:%s\n",peli->director); /*imprime el director de la pelicula*/

    printf("Clasificacion de la pelicula: %s\n", peli->clasificacionEdad);

    printf("Genero/s de la Pelicula:\n"); /*imprime el genero de la pelicula*/

    char * type = first(peli->genero); /*accede a la lista de generos*/

    while(type){

        printf("    %s\n", type); /*imprime el genero*/
        type = next(peli->genero); /*va al siguiente genero*/

    }
     printf("Ranking de la pelicula: %s\n", peli->ranking);
}

void peliculasfab(HashMap * Pelis,TreeMap * rankingTree,TreeMap* Peliwis,HashMap* clasifMap,HashMap*PelisDirector){


    system("cls");

    printf("\nWhat do you want to do?\n");
    printf("1: Importar Lista con sus peliculas favoritas\n");
    printf("2: Ingresar Manualmente pelicula\n");


    int option;
    do{

        scanf("%d", &option);

        if(option != 1 && option != 2){
            printf("Opcion invalida, por favor ingrese una opcion valida. \n");
        }

    }while(option != 1 && option != 2);


    if(option == 1){
    system("cls");
    printf("Por favor ingrese el nombre del archivo ");
    char name[50]; //the name of the file that has the games
    FILE * fp;

    do{

        fflush(stdin);
        scanf("%[^\n]s", name);
        fp = fopen( name , "r"); //opens the file in read
        if (fp == NULL){
            printf("Archivo Invalido, por favor ingrese un archivo valido! "); //if the file isn't valid this message will pop on the screen
        }
        fflush(stdin);

    }while(fp == NULL);

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

        Pelicula * nuevaPeli = crearPeli(nombre,anio, director, clasificacionEdad,Geneross, ranking);
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
        insertTreeMap(Peliwis,anio , nombre);
}
    printf("Sus Peliculas se importaron exitosamente (^_^) "); //message that pops out on the window if all the pokemon were imported correctly

    }

    else{


    char * nombre = (char *) malloc (30 * sizeof(char));
    int anio;
    char * director = (char *) malloc (30 * sizeof(char));
    char * clasificacionEdad = (char *) malloc (30 * sizeof(char));
    List * generos = create_list();
    char * ranking = (char *) malloc (30 * sizeof(char));


    printf("Por favor ingrese el nombre de la Pelicula \n");
    fflush(stdin);
    scanf("%[^\n]s",nombre);
    fflush(stdin);

    printf("Por favor ingrese el anio de la pelicula\n");
    scanf("%d", &anio);
    fflush(stdin);

    printf("Por favor ingrese el Director de la Pelicula \n");
    fflush(stdin);
    scanf("%[^\n]s",director);
    fflush(stdin);

    printf("Por favor ingrese la clasificacion de edad de la Pelicula \n");
    fflush(stdin);
    scanf("%s",clasificacionEdad);
    fflush(stdin);


    printf("\nCuantos generos tiene la pelicula? ");
        int cont;
        scanf("%d", &cont);
        int i = 1;

        while(cont>0){

            char * genero = (char *) malloc (20 * sizeof(char)); ; //reads all the types entered by the user
            printf("Ingrese genero numero %d: ", i);
            fflush(stdin);
            scanf("%[^\n]s", genero);
            fflush(stdin);

            push_back(generos, genero);

            i++;
            cont--;
        }
     printf("Por favor ingrese el Ranking de la Pelicula \n");
    fflush(stdin);
    scanf("%s",ranking);
    fflush(stdin);

    Pelicula * nuevaPeli = crearPeli(nombre,anio, director, clasificacionEdad,generos, ranking);
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
                        if (searchMap(PelisDirector, director) == NULL ){
                List * listadir = create_list();
                push_back(listadir, nuevaPeli);
                insertMap(PelisDirector, director, listadir);

            }
            else{
                List * auxLista = searchMap(PelisDirector, director);
                push_back(auxLista, nuevaPeli);
            }
        }
        insertTreeMap(Peliwis,anio , nombre);

}
}

void getTypes(List * typesList, char * types){

/*esta funcion obtiene los diferentes tipos de peliculas*/ 

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

void busquedaPornombre(HashMap * Pelis){

    char * name[50];
    Pelicula * aux;
    printf("Por favor ingrese el Nombre de la Pelicula\n");
    fflush(stdin);
    scanf("%[^\n]s",name);
    fflush(stdin);

    if (Pelis == NULL){
        printf("No hay peliculas guardadas en la base de datos\n");
        return;
    }
    if (searchMap(Pelis,name)==NULL){
        printf("El nombre ingresado no pertenece a alguna pelicula de la base de datos\n");
        return;
    }
    aux= searchMap(Pelis,name);

    if (aux != NULL){
        showMovieInformation(aux);
    }
    printf("\n\n");
    system("pause");
    system("cls");
    return;
}

Pelicula * crearPeli(char * nombre, int  anio,  char *  director, char  * clasificacionEdad,List * genero, char *  ranking){

    Pelicula * peliwi = (Pelicula *) malloc ( sizeof(Pelicula));
    peliwi->nombre = nombre;
    peliwi->anio = anio;
    peliwi->director = director;
    peliwi->clasificacionEdad = clasificacionEdad;
    peliwi->genero = genero;
    peliwi->ranking = ranking;
    return peliwi;

}

void importarpelis(HashMap* Pelis, TreeMap *rankingTree, TreeMap *peliwis, HashMap * clasifMap,HashMap* PelisDirector){
    //very important function that imports all the games from a csv file

    system("cls");

    FILE * fp;

        fp = fopen("pelis.txt", "r"); //opens the file in read

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

         Pelicula * nuevaPeli = crearPeli(nombre,anio, director, clasificacionEdad,Geneross, ranking);

            insertMap(Pelis, nuevaPeli->nombre ,nuevaPeli);

            if (searchTreeMap(rankingTree, ranking) == NULL){
                List * listaRanking =create_list();
                push_back(listaRanking, nuevaPeli);
                insertTreeMap(rankingTree, ranking, listaRanking);
            }
            else{
                List * auxLisst= searchTreeMap(rankingTree, ranking);
                push_back(auxLisst, nuevaPeli);

            }
            if (searchMap(PelisDirector, director) == NULL ){
                List * listadir = create_list();
                push_back(listadir, nuevaPeli);
                insertMap(PelisDirector, director, listadir);

            }
            else{
                List * auxLista = searchMap(PelisDirector, director);
                push_back(auxLista, nuevaPeli);
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

        insertTreeMap(peliwis,anio , nombre);

    }

}

void agregarFavorito(Usuario * usuario){

    char peliculaFavorita[50];
    char directorFavorito[30];
    char generoFavorito[30];
    char actorFavorito[30];
    char clasificacionFavorita[30];

    printf("Para llenar sus favoritos le pediremos los siguientes datos: \n\n");

    printf("Ingrese el nombre de su pelicula favorita: ");
    fflush(stdin);
    scanf("%[^\n]s", peliculaFavorita);
    printf("Ahora ingrese el nombre de su director favorito: ");
    fflush(stdin);
    scanf("%[^\n]s", directorFavorito);
    printf("Ahora ingrese el nombre de su genero favorito: ");
    fflush(stdin);
    scanf("%[^\n]s", generoFavorito);
    printf("Ahora ingrese el nombre de su actor favorito: ");
    fflush(stdin);
    scanf("%[^\n]s", actorFavorito);
    printf("Ahora ingrese el nombre de su clasificacion favorita: ");
    fflush(stdin);
    scanf("%[^\n]s", clasificacionFavorita);

    char nombreArchivo[60];
    strcpy(nombreArchivo, "Usuarios/");
    strcat(nombreArchivo, usuario->username); //insertaremos en el nombre del archivo el nombre del usuario
    strcat(nombreArchivo, "Favoritos.csv");
    FILE * fp = fopen(nombreArchivo, "w");

    fprintf(fp, "%s,%s,%s,%s,%s", peliculaFavorita, directorFavorito, generoFavorito, actorFavorito, clasificacionFavorita);
    fclose(fp);

    printf("\nLos datos han sido agregados correctamente, ahora puede buscar amigos\n\n");

    system("pause");
    system("cls");

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
        printf("\n\n");
    system("pause");
    system("cls");
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
    system("pause");
    system("cls");
        return;
    }

    printf("Pelicula/as con ranking %s\n", ranking);

    resultAux= first(listaAux);
    while (resultAux != NULL){
        showMovieInformation(resultAux);
        resultAux= next(listaAux);
    }
    printf("\n\n");
    system("pause");
    system("cls");
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
            showMovieInformation(auxPeli);
            auxPeli= next(auxLista);
        }
        auxLista= backTreeMap(rankingTree); //Previous value, lower than current
    }
        printf("\n\n");
    system("pause");
    system("cls");
    return;
}

void busquedaPorClasif (HashMap * clasifMap){
    char * clasif[50];
    List * listaAux;
    Pelicula * resultAux;
    printf("Por favor ingrese la clasificacion de edad mostrar peliculas\n");
    scanf(" %s",clasif);

    if (clasifMap == NULL){
        printf("No hay peliculas guardadas en la base de datos\n");

    system("pause");
    system("cls");
        return;
    }
    if (searchMap(clasifMap,clasif)==NULL){
        printf("La clasificacion ingresada no pertenece a alguna pelicula de la base de datos\n");

    system("pause");
    system("cls");
        return;
    }
    listaAux= searchMap(clasifMap,clasif);

    printf("Pelicula/as con clasificacion %s\n " , clasif);

    resultAux= first(listaAux);


    while (resultAux != NULL){
        showMovieInformation(resultAux);
        //if (->next == NULL)return;
        resultAux= next(listaAux);

    }
        printf("\n\n");
    system("pause");
    system("cls");
    return;
}

void amigos(Usuario * usuario){

    system("cls");
    int option;
    char amiko[30];

    do{

        printf("Ingrese la opcion que desea hacer\n\n");
        printf("Opcion 1: Agregar amigos por username \n");
        printf("Opcion 2: Mostrar amigos \n\n");
        scanf("%d",&option);

        if ((option > 2) || (option < 1)){
            printf("Ingrese una opcion valida! \n\n");
        }


    }while ((option > 2) || (option < 1));

    if (option == 1){

        printf("Ingrese el username del Unicornio amigo: ");
        fflush(stdin);
        scanf("%s",amiko);
        fflush(stdin);
        if (usuarioExiste(amiko)){

            char nombreArchivo[70];
            strcpy(nombreArchivo, "Usuarios/");
            strcat(nombreArchivo, usuario->username);
            strcat(nombreArchivo, ".csv");

            FILE * fp = fopen(nombreArchivo, "r+");

            if(fp == NULL){

                printf("\nError\n\n");
                return;

            }

            //para comprobar si es que el archivo está vacio o no
            fseek (fp, 0, SEEK_END);
            long lSize = ftell(fp);

            //si es que esta vacio agregamos sin coma al principio
            if(lSize == 0){

                fprintf(fp, "%s", amiko);
                fclose(fp);

            }
            else{

                fprintf(fp, ",%s", amiko);
                fclose(fp);

            }

            push_back(usuario->UnicornFriend, _strdup(amiko));
            printf("\nEl usuario se ha agregado a la lista de amigos correctamente\n\n");

        }
        else{

            printf("\nNo hemos encontrado ningun usuario con este nombre\n\n");

        }

    }
    else{

        char * amigo = first(usuario->UnicornFriend);

        if(amigo == NULL){

            printf("\nEl usuario aun no tiene amigos\n\n");
            system("pause");
            system("cls");
            return;

        }

        printf("\nAmigos del usuario %s: \n\n", usuario->username);

        while(amigo != NULL){
            printf("Amigo: %s\n", amigo);
            amigo = next(usuario->UnicornFriend);
        }

        printf("\n");

    }

    system("pause");
    system("cls");


}
