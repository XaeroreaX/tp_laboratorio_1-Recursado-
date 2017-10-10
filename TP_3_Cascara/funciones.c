#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "ArrayList.h"
#define OK 0
#define DENEID -1





/**-------------------------------------------------------*////1)

/** \brief añade una pelicula a un arrayList
 *
 * \param  arraylist donde se almacena las peliculas
 * \return entero (-1) si falla al añadir una pelicula en el arraylist  (0) si añadio exitosamente la pelicula
 *
 */


int addMovieList(ArrayList* movieList)
{
    int returnAux = DENEID;
    EMovie* movie;

    if(movieList == NULL) return returnAux;

    movie = addMovie();

    if(movie != NULL)
        returnAux = movieList->add(movieList, movie);


    return returnAux;
}

/**-------------------------------------------------------*////2)

/** \brief da elegir una pelicula para borrar en el arraylist
 *
 * \param arraylist de peliculas
 * \return entero (-1) si hay un error en el remove de una pelicula (0) si remueve exitosamente
 *
 */


int removeMovieList(ArrayList* movieList)
{

    int returnAux = DENEID, index;


    if(movieList == NULL) return returnAux;

    returnAux = OK;
    if(movieList->isEmpty(movieList) == 0)
    {

        printf("ingrese el indice la pelicula que quiere borrar:\n0)Cancel");
        if(showMovieListIndex(movieList) == DENEID) printf("Error en la funcion showMovieList");
        scanf("%d", &index);
        while(index < 0 || index > movieList->len(movieList))
        {
            printf("elijio mal la pelicula que quiere borrar, por favor ingrese de nuevo\n");
            scanf("%d", &index);
        }

        index--;

        if(index >= 0)
            returnAux = movieList->remove(movieList, index);
        else
            returnAux = OK;


    }
    else printf("no hay peliculas almacenadas\n");

    return returnAux;
}

/**-------------------------------------------------------*////3)

int setMovieList(ArrayList* movieList)
{
    int returnAux = DENEID, index;
    EMovie* movie;

    if(movieList == NULL) return returnAux;

    returnAux = OK;

    if(movieList->isEmpty(movieList) == 0)
    {

        printf("ingrese el indice la pelicula que quiere modificar:\n0)Cancel");
        if( showMovieListIndex(movieList) == DENEID) printf("Error en la funcion showMovieList");

        scanf("%d", &index);

        while(index < 0 || index > movieList->len(movieList))
        {
            printf("elijio mal la pelicula que quiere modificar, por favor ingrese de nuevo\n");
            scanf("%d", &index);
        }


        index--;
        if(index >= 0)
        {

            movie = addMovie();

            if(movie != NULL)
                returnAux = movieList->set(movieList, index, movie);
        }
        else
            returnAux = OK;
    }
    else printf("no hay peliculas almacenadas\n");

    return returnAux;

}

/**-------------------------------------------------------*////4)

int generarPagina(ArrayList* movieList)
{
    int i, returnAux = DENEID, val;

    EMovie* movie;

    FILE* file;

    movie = (EMovie*) malloc(sizeof(EMovie));

    if(movieList == NULL || movie == NULL) return returnAux;

    if(movieList->isEmpty(movieList) == 0)
    {

        if(i >= 0)
        {

            file = fopen("index.HTML", "w");

            if(file == NULL) return returnAux;


            for(i = 0; i < movieList->len(movieList); i++)
            {

                movie = (EMovie*) movieList->get(movieList, i);




                fprintf(file,"<img  src=%s alt=%s style=width:200px;hight:200px>",movie->linkImagen,movie->titulo);

                        //titulo
                fprintf(file,"<h2><a href=#>%s</a></h2>",movie->titulo);

                        //otros aspectos

                fprintf(file,"<h3><li> Genero: %s</li>   <li>Puntaje: %d </li>     <li>Duracion: %d </li>               </h3>",movie->genero,movie->puntaje,movie->duracion);

                fprintf(file,"<pre>%s</pre>", movie->descripcion);


            }




            printf("pagina generada esxitosamente");

        }
    }
    else
    {
        file = fopen("index.HTML", "w");
        fprintf(file,"");

        printf("no hay peliculas almacenadas\n");
    }
    fclose(file);
    returnAux = OK;
    return returnAux;
}

/**-------------------------------------------------------*////n)

int fileToMovieList(ArrayList* movieList)
{
    FILE* file;
    int returnAux = DENEID, index, size, len;

    EMovie* movie;



    file = fopen("data.dat", "rb");

    if(file == NULL || movieList == NULL)
    {
        fclose(file);
        return returnAux;
    }

    fseek(file, 0 , SEEK_END);

    size = ftell(file)/sizeof(EMovie);

    rewind(file);

    for(index = 0; index<size; index++)
    {
        movie = (EMovie*) malloc(sizeof(EMovie));

        len = fread(movie, sizeof(EMovie), 1,file);
  //      printf("%d-%s\n",len, movie->titulo);

        returnAux = movieList->add(movieList, movie);
        if(returnAux == DENEID) break;

    }
/*
    len = showMovieListIndex(movieList);
        if(len == DENEID) printf("Error en la funcion showMovieList");*/

    fclose(file);
    return returnAux;
}


/**-------------------------------------------------------*////n)

int movieListToFile(ArrayList* movieList)
{
    FILE* file;
    int returnAux = DENEID, index, size, len;

    EMovie* movie;

    movie = (EMovie*) malloc(sizeof(EMovie));

    file = fopen("data.dat", "w+b");

    if(file == NULL || movieList == NULL)
    {
        fclose(file);
        return returnAux;
    }

    //fseek(file, 0 , SEEK_END);



    for(index = 0; index < movieList->len(movieList); index++)
    {
        movie =(EMovie*) movieList->get(movieList, index);

        len = fwrite(movie, sizeof(EMovie), 1 ,file);

        //printf("%d-%d-%s",index,len, movie->titulo);
    }



    fclose(file);
    return returnAux;
}

/**-------------------------------------------------------*////n)

int showMovieListIndex(ArrayList* movieList)
{
    int i, returnAux = DENEID;

    EMovie* movie;

    movie = (EMovie*) malloc(sizeof(EMovie));

    if(movieList == NULL || movie == NULL) return returnAux;

    for(i = 0; i < movieList->len(movieList); i++)
    {
        movie = (EMovie*) movieList->get(movieList, i);
        printf("\n%d)titulo:%s", (i + 1), movie->titulo);
    }

    printf("\n");
    returnAux = i;

    return returnAux;
}

/**-------------------------------------------------------*////n)

EMovie* addMovie()
{
    EMovie* movie;

    movie = (EMovie*) malloc(sizeof(EMovie));

    /*char titulo[20];
    char genero[20];
    int duracion;
    char descripcion[50];
    int puntaje;
    char linkImagen[50];*/

    if(movie != NULL)
    {
        printf("\nIngrese el titulo de la pelicula:");
        cargarCaracter(50, movie->titulo);

        printf("\nIngrese el genero de la pelicula:");
        cargarCaracter(100,movie->genero);

        printf("\nIngrese el duracion de la pelicula(en minutos):");
        fflush(stdin);
        scanf("%d", &movie->duracion);
        while(movie->duracion < 3)
        {
            fflush(stdin);
            printf("\nIngreso mal el duracion de la pelicula, por favor ingrese de nuevo:");
            scanf("%d", &movie->duracion);
        }

        printf("\nIngrese la descripcion de la pelicula:");
        cargarCaracter(800, movie->descripcion);

        printf("\nIngrese el puntuacion de la pelicula(de 10 a 100):");
        fflush(stdin);
        scanf("%d", &movie->puntaje);
        while(movie->puntaje < 10 || movie->puntaje > 100)
        {
            fflush(stdin);
            printf("\nIngreso mal la puntuacion de la pelicula, por favor ingrese de nuevo:");
            scanf("%d", &movie->puntaje);
        }

        printf("\nIngrese un link para la imagen de la pelicula:");
        cargarCaracter(800, movie->linkImagen);

    }

    return movie;
}

/**-------------------------------------------------------*////n)

int compareMovie(void* MovieA, void* MovieB)
{

    if( strcmp(((EMovie*)MovieA)->titulo, ((EMovie*)MovieB)->titulo) == 1)
    {
        return 1;
    }
    if( strcmp(((EMovie*)MovieA)->titulo, ((EMovie*)MovieB)->titulo) == -1)
    {
        return -1;
    }
    return 0;


}

/**-------------------------------------------------------////n)

int charAddDinamic(char* caracter)
{
    int len, returnAux = DENEID;
    char* aux;

    caracter = (char*) malloc(sizeof(char) * 1024);

    if(caracter == NULL) return returnAux;

    fflush(stdin);
    scanf("%1023[^\n]", caracter);

    len = strlen(caracter);

    aux = (char*) realloc(caracter, sizeof(char*)* len+1);

    if(aux != NULL)
    {
        caracter = aux;
        returnAux = OK;
    }

    return returnAux;
}*/

/**-------------------------------------------------------*////n)

void cargarCaracter(int tam, char caracteres[tam])
{
    char buffer[1024];

    fflush(stdin);

    gets(buffer);
    while(strlen(buffer) > tam)
    {
        printf("ingreso mal la cadena de caracteres, ingrese de nuevo");
        fflush(stdin);
        gets(buffer);
    }
    strcpy(caracteres, buffer);

}

