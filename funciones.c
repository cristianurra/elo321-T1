#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

int prueba(void);
void clean(char temp[]);
void copy(char temp[], int i);

int prueba()
{

    char temp[50];
    int c = 0;
    int i, j;
    char aux;
    producto *prod;

    FILE *f;
    f = fopen("productos.txt", "r");
    if (f == NULL)
    {
        printf("Fichero no encontrado.\n");
        exit(1);
    }

    while (!feof(f))
    {
        fgets(temp, 50, f);
        c++;
    }
    rewind(f);

    prod = (producto *)malloc(c * sizeof(producto));
    if (prod == NULL)
    {
        printf("Error al reservar memoria.\n");
        exit(1);
    }

    for (i = 0; !feof(f); i++)
    {
        clean(temp);
        aux = '0';
        for (j = 0; aux != ','; j++)
        {
            aux = fgetc(f);
            if (aux != ',')
            {
                temp[j] = aux;
            }
        }
        copy(temp, i);

        fgets(temp, 10, f);
    }
}

void clean(char temp[])
{
    int i;
    for (i = 0; i < 50; i++)
    {
        temp[i] = '\0';
    }
}

void copy(char temp[], int i)
{
    int N = strlen(temp) + 1;
    prod[i].nombre = (char *)malloc(N * sizeof(char));
    if (prod[i].nombre == NULL)
    {
        printf("Error al reservar memoria.\n");
        exit(1);
    }
    strcpy(prod[i].nombre, temp);
}
