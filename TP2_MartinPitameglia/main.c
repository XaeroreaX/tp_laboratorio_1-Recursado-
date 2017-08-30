#include "FSPersona.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define T 20


int main()
{
    SPersona persona[T];
    int Seleccion, quit = 1,i;

    for(i = 0; i<T;i++)
    {
        persona[i] = HarcodearS("", 0, 0, 0);
    }


    while(quit == 1)
    {
        i = buscarDatosCargadosS(T, persona);
        if(i == 0)
        {
            printf("el vector no esta cargado\n\n");
        }
        else
        {
            printf("los datos del vector son:\n");
            mostraArrayS(T, persona, 1);
            printf("\n");
        }
        printf("-------------elija una de las 5 opciones-------------\n");
        printf("1. Agregar una persona\n2. Borrar una persona\n3. Imprimir lista ordenada por nombre\n4. Imprimir grafico de edades\n5. salir\n");
        scanf("%d",&Seleccion);
        switch(Seleccion)
        {
            case 1:
                printf("ingrese la posicion de la persona que quiera agregar(1 - 20)\n");
                scanf("%d", &i);
                while(i > 20 || i < 1)
                {
                    printf("ingreso mal la posicion de la persona, por favor ingrese de nuevo\n");
                    scanf("%d", &i);
                }
                persona[i - 1] = cargarPersonaS();

                break;
            case 2:
                printf("ingrese la posicion de la persona que quiera borrar de la tabla\n");
                scanf("%d", &i);
                while(i > 20 || i < 1)
                {
                    printf("ingreso mal la posicion de la persona, por favor ingrese de nuevo\n");
                    scanf("%d", &i);
                }
                persona[i - 1] = HarcodearS("", 0, 0, 0);
                break;
            case 3:
                i = buscarDatosCargadosS(T, persona);
                if(i == 0)
                {
                    printf("no se puede ordenar un vector sin datos\n");
                }
                else
                {
                    mostrarordenarS(T, persona);
                }


                break;
            case 4:
                i = buscarDatosCargadosS(T, persona);
                if(i == 0)
                {
                    printf("no se puede mostrar la barra de * sin valores en el vector\n");
                }
                else
                {
                    mostrarBarraEdadesS(T, persona);
                }
                break;
            case 5:
                quit = 0;
                break;
            default:
                printf("ingreso mal en la seleccion");
                break;
        }
        printf("\n");
        system("pause");
        system("cls");
    }

    return 0;
}
