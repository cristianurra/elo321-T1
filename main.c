#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fun.h"
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>





#define SIZE 512




#define SIZE 512
#define LSIZ 128
#define RSIZ 10

int contar_productos();
void read_pedidos(Elemento *elemento, char *line, Lista *lista);
Lista *inicializacion()
{
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->fin = NULL;
    return lista;
}

/* inserción en una lista vacía */
int ins_en_lista_vacia(Lista *lista, char *dato)
{
    Elemento *nuevo_elemento;
    if ((nuevo_elemento = (Elemento *)malloc(sizeof(Elemento))) == NULL)
        return -1;
    if ((nuevo_elemento->dato = (char *)malloc(50 * sizeof(char))) == NULL)
        return -1;
    strcpy(nuevo_elemento->dato, dato);
    nuevo_elemento->siguiente = NULL;
    lista->inicio = nuevo_elemento;
    lista->fin = nuevo_elemento;
    lista->tamano++;
    return 0;
}

/*inserción al final de la lista */
int ins_fin_lista(Lista *lista, Elemento *actual, char *dato)
{
    Elemento *nuevo_elemento;
    if ((nuevo_elemento = (Elemento *)malloc(sizeof(Elemento))) == NULL)
        return -1;
    if ((nuevo_elemento->dato = (char *)malloc(50 * sizeof(char))) == NULL)
        return -1;
    strcpy(nuevo_elemento->dato, dato);
    actual->siguiente = nuevo_elemento;
    nuevo_elemento->siguiente = NULL;
    lista->fin = nuevo_elemento;
    lista->tamano++;
    return 0;
}

/* eliminación al inicio de la lista */
int sup_inicio(Lista *lista)
{
    if (lista->tamano == 0)
        return -1;
    Elemento *sup_elemento;
    sup_elemento = lista->inicio;
    lista->inicio = lista->inicio->siguiente;
    if (lista->tamano == 1)
        lista->fin = NULL;
    free(sup_elemento->dato);
    free(sup_elemento);
    lista->tamano--;
    return 0;
}

/* visualización de la lista */
void visualizacion(Lista *lista)
{
    Elemento *actual;
    actual = lista->inicio;
    while (actual != NULL)
    {
        //printf("%s\n", actual->dato);
        actual = actual->siguiente;
    }
}

void parse_producto_from_line(producto *prod, char *line)
{
    char *pt;
    pt = strtok(line, ",");
    int x;
    char *nombre = malloc(sizeof(char) * 50);
    strcpy(nombre, pt);
    prod->nombre = nombre;
    for (x = 1; x <= 3; x++)
    {
        pt = strtok(NULL, ",");
        switch (x)
        {
        case 1:
            prod->precio = atoi(pt);
            break;
        case 2:
            prod->codigo = atoi(pt);
            break;
        case 3:
            prod->tiempo_prep = atoi(pt);
            break;
        default:
            break;
        }
    }
}

int contar_productos()
{
    int c = 0;
    char line[RSIZ][LSIZ];
    char fname[20] = "productos.txt";
    FILE *fptr = NULL;
    int i = 0;
    int tot = 0;

    fptr = fopen(fname, "r");
    while (fgets(line[i], LSIZ, fptr))
    {
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    tot = i;
    for (i = 0; i < tot; ++i)
    {
        c++;
    }
    fclose(fptr);
    return c;
}

int read_productos(producto *prods)
{
    FILE *fp = fopen("productos.txt", "r");
    char *line = NULL;
    size_t len = 0;
    size_t read;

    if (fp == NULL)
        exit(EXIT_FAILURE);

    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        parse_producto_from_line(&prods[i], line);
        i++;
    }
    fclose(fp);
    return i;
}

void read_pedidos(Elemento *elemento, char *line, Lista *lista)
{
    char *pt;
    int c = 0;
    pt = strtok(line, ",");
    char *nombre = malloc(sizeof(char) * 50);
    while (pt != NULL)
    {
        strcpy(nombre, pt);
        if (c == 0)
        {
            ins_en_lista_vacia(lista, nombre);
        }
        else
        {
            ins_fin_lista(lista, lista->fin, nombre);
        }
        c++;
        pt = strtok(NULL, ",");
    }
}

void main()
{
	
	pid_t pid1;
	int p1[2], readbytes1;
	char buffer1[SIZE];
	pipe( p1 );
	if ( (pid1=fork()) == 0 ) //Hijo 1
	{ // hijo 
		close( p1[1] ); /* cerramos el lado de escritura del pipe */
    while( (readbytes1=read( p1[0], buffer1, SIZE )) > 0){
		write( 1, buffer1, readbytes1 );
		}
		
    close( p1[0] );
    exit(0);
  }
  
  
	pid_t pid2;  //Hijo 2
	int p2[2], readbytes2;
	char buffer2[SIZE];
	pipe( p2 );
	if ( (pid2=fork()) == 0 )
	{ // hijo
		close( p2[1] ); /* cerramos el lado de escritura del pipe */
		while( (readbytes2=read( p2[0], buffer2, SIZE )) > 0){
			write( 1, buffer2, readbytes2 );

		}
    close( p2[0] );
    exit(0);
  }
	




  else
  { // aca se ejecuta el padre
	  
	int total_ventas=0;
	  
	int n_items = contar_productos(); // Cambiar por función
    int i;
    char *pedido;
    Lista *lista = inicializacion();
    Elemento *actual;
    producto *productos = malloc(n_items * sizeof(producto));
    read_productos(productos);
    printf("======= Los productos disponibles son =======:\n \n");
    for (i = 0; i < n_items; i++)
    {
        producto prod = productos[i];
        printf("%s, con un valor de %d pesos.  \n", prod.nombre, prod.precio);
        // printf("Producto N: %s, P: %d, C: %d, T: %d\n", prod.nombre, prod.precio, prod.codigo, prod.tiempo_prep);
    }
    actual = NULL;
    FILE *fp = fopen("pedidos.txt", "r");
    char *line = NULL;
    size_t len = 0;
    size_t read;

    if (fp == NULL)
    {
        exit(EXIT_FAILURE);
    }
    getline(&line, &len, fp);
    read_pedidos(actual, line, lista);
    fclose(fp);
    visualizacion(lista);
    
    printf("\n======= Los ID de los productos pedidos son =======:\n \n");
    int timer1=1;
    int timer2=1;
    while (lista->inicio != NULL)  //Aca se empiezan a delegar los pedidos a los procesos hijo
    {	
        for (i = 0; i < n_items; i++)
        {
            producto prod = productos[i];
            if (strcmp(lista->inicio->dato, prod.nombre) == 0)
            {
				
                
            	
            	
            	
            	
            	
            	
            	
            	
				
				
				
				

				//printf("%d\n",codigo);
				
				int codigo=0;
				char cod[6];
				if (timer1<1){ //significa que el proceso hijo 1 esta desocupado
					close( p1[0] ); /* cerramos el lado de lectura del pipe 1 */
					codigo=prod.codigo;
					sprintf(cod,"%d\n",codigo);
					strcpy( buffer1, cod);  /*esto se envia al proceso hijo 1*/
					write( p1[1], buffer1, strlen( buffer1 ) );
					total_ventas+=prod.precio;
					sup_inicio(lista);
					timer1=prod.tiempo_prep;
					printf("Hijo 1 vende ID %d\n",codigo);
					break;
				}


				if (timer2<1){ //significa que el proceso hijo 2 esta desocupado
					close( p2[0] ); /* cerramos el lado de lectura del pipe 2 */
					codigo=prod.codigo;
					sprintf(cod,"%d\n",codigo);
					strcpy( buffer2, cod);  /*esto se envia al proceso hijo 2*/	
					write( p2[1], buffer2, strlen( buffer2 ) );			
					total_ventas+=prod.precio;
					sup_inicio(lista);
					timer2=prod.tiempo_prep;
					printf("Hijo 2 vende ID %d\n",codigo);
					
				}				
				timer1=timer1-1;
				timer2=timer2-1;


				
		
            }
        }
        
        //sup_inicio(lista);

    }
	  
  		close( p1[1] ); /*aca se cierran los pipes*/
		close( p2[1] );
		
		waitpid( pid1, NULL, 0 );
		waitpid( pid2, NULL, 0 );
		printf("====Proceso terminado. Se vendio uhn total de $%d ====\n",total_ventas);
}	

    
    

  
  

  exit( 0 );
    
    
    
}
