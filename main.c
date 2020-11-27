#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "hashmap.h"
#include "funciones.h"
#include "treemap.h"

int main()
{

    HashMap * Pelis = createMap(500);

     importarpelis( Pelis);

    int opcion = 1;
    int salir = 0;

    do{
       printf("Bienvenido al Unicornio Cinefilo! Una App de fans para fans, aqui podras almacenar todas tus peliculas favoritas,\n");
       printf("conocer amigos, recibir recomendaciones, y muchas cosas divertidas mas! Empecemos: Que quieres hacer?\n\n");
       printf("Opcion 1: Ingresar si es que ya eres un usuario existente \n\n");
       printf("Opcion 2: Crea un usuario nuevo el cual nombre debe ser alfanumero y UNICO, \n");
       printf("no pueden haber dos usuarios con el mismo nombre. \n\n");

        printf("Opcion 1 <3 : Ingresar\n");
        printf("Opcion 2 <3 : Crear Usuario\n\n");

        printf("Ingrese una opcion: ");

        scanf("%d", &opcion);

        if(opcion != 1 && opcion != 2){

            printf("\nLa opcion ingresada no es correcta\n\n");
            system("pause");
            system("cls");

        }
        else{

            switch(opcion){

                case 1: salir = ingresarUsuario();
                break;
                case 2: salir = crearUsuario();
                break;

            }

        }

    }while(salir != 1);

    int option; //a number to guide our menu :3

    while(1){

        //our menu to print all our options :D
        printf("\nBienvenides al menu principal de El Unicornio cinefilo, que desea hacer?  \n\n");
        printf("Opcion 1 <3 : Sus peliculas favoritas! \n");
        printf("Opcion 2 <3 : Busqueda de peliculas por genero \n");
        printf("Opcion 3 <3 : Busqueda de peliculas por anio \n");
        printf("Opcion 4 <3 : Busqueda de peliculas por director \n");
        printf("Opcion 5 <3 : Busqueda de peliculas por nombre \n");
        printf("Opcion 6 <3 : Busqueda de peliculas por clasificacion \n");
        printf("Opcion 7 <3 : Busqueda de peliculas por Rating  \n");
        printf("Opcion 8 <3 : Busqueda de amigos \n");
        printf("Opcion 9 <3 : Cerrar sesion \n");
        do{
            scanf("%d", &option);
            if ((option > 9) || (option < 1))
               printf("Opcion Invalida, por favor seleccione una opcion valida del menu <3 \n");

        }while ((option > 9) || (option < 1));  //this "While" validates that the option entered is valid!


        if(option == 9){

            break;  //breaks the program

        }

    }




    return 0;
}
