#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "ArrayList.h"
#define OK 0
#define DENEID -1



int main()
{
    char seguir='s';
    int opcion=0;


    ArrayList* movieList;

    movieList = al_newArrayList();

    fileToMovieList(movieList);


    while(seguir=='s')
    {
        printf("1- Agregar pelicula\n");
        printf("2- Borrar pelicula\n");
        printf("3- Modificar pelicula\n");
        printf("4- Generar pagina web\n");
        printf("5- Limpiar la lista de peliculas\n");
        printf("6- Salir\n");

        scanf("%d",&opcion);

        switch(opcion)
        {
            case 1:
                system("cls");

                if(addMovieList(movieList) == DENEID) printf("Error en la funcion addMovieList\n");

                system("pause");
                break;
            case 2:
                system("cls");
                if(removeMovieList(movieList) == DENEID) printf("Error en la funcion removeMovieList\n");

                system("pause");
                break;
            case 3:
                system("cls");

                if(setMovieList(movieList) == DENEID) printf("Error en la funcion removeMovieList\n");

                system("pause");
                break;
            case 4:
                system("cls");

                if(generarPagina(movieList) == DENEID) printf("Error en la funcion generarPagina\n");

                system("pause");
               break;
            case 5:
                system("cls");
                if(movieList->clear(movieList) == DENEID)
                {


                    printf("ERROR en la funsion CLEAR en movieList\n");
                }
                else
                {


                    printf("el arrayList fue limpiado\n");
                }

                system("pause");
                break;
            case 6:
                seguir = 'n';
                break;


        }

        if(movieList->sort(movieList, compareMovie, 1) == DENEID ) printf("ERROR en la funsion sort de arrayList de EMovie");
        movieListToFile(movieList);
        system("cls");

    }

    return 0;
}
