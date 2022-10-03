typedef struct
{
    char *nombre;
    int precio;
    int codigo;
    int tiempo_prep;
} producto;

typedef struct ElementoLista
{
    char *dato;
    struct ElementoLista *siguiente;
} Elemento;

typedef struct ListaIdentificar
{
    Elemento *inicio;
    Elemento *fin;
    int tamano;
} Lista;

int ins_en_lista_vacia(Lista *lista, char *dato);

int ins_fin_lista(Lista *lista, Elemento *actual, char *dato);

int sup_inicio(Lista *lista);

void visualizacion(Lista *lista);
