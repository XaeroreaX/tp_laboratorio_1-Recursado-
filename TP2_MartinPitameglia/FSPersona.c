#include "FSPersona.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

SPersona cargarPersonaS()
{
    SPersona persona;
    char Estado;
    char buffer[1024];

    printf("ingrese el nombre de la persona:");
    fflush(stdin);
    gets(buffer);
    while(strlen(buffer) > 20)
    {
        printf("ingreso demasiados caracteres al nombre(maximo 20) por favor ingrese de nuevo\n");
        fflush(stdin);
        gets(buffer);
    }
    strcpy(persona.nombre, buffer);
    printf("ingrese la edad de la persona:");
    scanf("%d", &persona.edad);
    while(persona.edad < 1)
    {
        printf("ingreso mal la edad de la persona, por favor ingrese de nuevo:");
        scanf("%d", &persona.edad);
    }

    printf("ingrese el DNI de la persona:");
    scanf("%d", &persona.dni);
    while(persona.dni < 100000)
    {
        printf("ingreso mal el DNI de la persona, por favor ingrese de nuevo:");
        scanf("%d", &persona.dni);
    }

    printf("ingrese el estado civil de la persona\nsoltero = s\ncasado = c\n");
    Estado = tolower (getch());
    while(Estado != 's' && Estado != 'c')
    {
        printf("ingreso mal el estado civil de la persona, por favor ingrese de nuevo\n");
        Estado = tolower (getch());
    }
    if(Estado == 's')
    {
        persona.flagEstado = 0;
    }
    else
    {
        persona.flagEstado = 1;
    }

    return persona;
}


SPersona HarcodearS(char nombre[20],int edad,int dni, int flag)
{
    SPersona persona;
    strcpy(persona.nombre,nombre);
    persona.edad = edad;
    persona.dni = dni;
    persona.flagEstado = flag;
    return persona;
}


void mostraArrayS(int tam, SPersona persona[tam], int flagPos)
{
    int i;
    char estado[10];
    //char prueba[20] = "martin";
    for(i = 0; i < tam; i++)
    {
        if(persona[i].flagEstado == 1)
        {
            strcpy(estado, "casado");
        }
        else
        {
            if(persona[i].flagEstado == 0)
            {
                strcpy(estado, "soltero");
            }
        }
        if(persona[i].dni != 0)
        {
            if(flagPos == 1)
            {
                printf("posicion %d Nombre:%s----Edad:%d----DNI:%d----Estado:%s\n", i + 1, persona[i].nombre, persona[i].edad, persona[i].dni, estado);
            }
            else
            {
                printf("Nombre:%s----Edad:%d----DNI:%d---Estado:%s\n", persona[i].nombre, persona[i].edad, persona[i].dni, estado);
            }

        }

    }
    /*i = strcmp(persona[0].nombre,prueba);
    printf("la comparacion da %d",i);*/
}

void mostrarBarraEdadesS(int tam, SPersona persona[tam])
{
    int i;
    int Menores18 = 0, Mayores18 = 0, Mayores35 = 0, Mayor;
    for(i = 0; i < tam; i++)
    {
        if(persona[i].dni != 0)
        {
            if(persona[i].edad < 18)
            {
                Menores18++;
            }
            else
            {
                if(persona[i].edad > 35)
                {
                    Mayores35++;
                }
                else
                {
                    Mayores18++;
                }
            }
        }


    }
    if(Mayores18 >= Menores18)
    {
        if(Mayores18 > Mayores35)
        {
            Mayor = Mayores18;
        }
        else
        {
            Mayor = Mayores35;
        }
    }
    else
    {
        if(Menores18 >= Mayores35)
        {
            Mayor = Menores18;
        }
        else
        {
            Mayor = Mayores35;

        }

    }
    printf("\n\tBarra de edades contadas por *\n\n");
    for(i = Mayor; i > 0; i--)
    {
         if(i == Menores18)
        {
            printf("\t\t*");
            Menores18--;
        }
        else
        {
            printf("\t\t ");
        }

        if(i == Mayores18)
        {
            printf("\t*");
            Mayores18--;
        }
        else
        {
            printf("\t ");
        }

        if(i == Mayores35)
        {
            printf("\t*");
            Mayores35--;
        }
        else
        {
            printf("\t ");
        }

        printf("\n");
    }
    printf("\t       <18    19-35    >35");

}

void mostrarordenarS(int tam, SPersona Spersona[tam])
{
    SPersona persona[tam];
    SPersona Aux;
    int i, j;
    for(i = 0; i < tam; i++)
    {
        persona[i] = Spersona[i];
    }

    for(i = 0; i < tam-1; i++)
    {
        for(j = i+1; j < tam; j++)
        {
            if(strcmp(persona[j].nombre, persona[i].nombre) == -1)
            {
                Aux = persona[i];
                persona[i] = persona[j];
                persona[j] = Aux;
            }

        }
        for(j = i+1; j < tam; j++)
        {

            if(strcmp(persona[j].nombre, persona[i].nombre) == 0 && persona[i].dni > persona[j].dni)
            {
                Aux = persona[i];
                persona[i] = persona[j];
                persona[j] = Aux;
            }
        }
    }
    mostraArrayS(tam, persona, 0);


}

int buscarDatosCargadosS(int tam, SPersona persona[tam])
{
   int i = 0;

   while(i < tam)
   {
       if(persona[i].dni != 0)
       {
           return 1;
       }
       i++;
   }
    return 0;
}


