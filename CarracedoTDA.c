#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char mandato[1];
char nombre[10];

typedef struct legislador
{
    char lnombre[10];
} legislador;

typedef struct nodo
{
    legislador chico;
    struct nodo *siguiente;

} nodo;

// typedef struct lista
// {
//     nodo *chico;
//     // int longitud;
// } lista;

// lista *chicosBuenos;
// lista *chicosMalos;

nodo *chicosBuenos = NULL;
nodo *chicosMalos = NULL;

legislador crearLegislador(char mandato[1], char nombre[10]);
nodo *crearNodo(legislador *milegislador);
void agregar(nodo **milista, nodo *nuevoNodo);
void ingresarVotos();
void procesar(legislador *milegislador);
void mostrar(nodo **milista);
void pedirLegislador();
nodo *eliminarListaVieja(nodo **milista, legislador *milegislador);
void eliminar(nodo *puntero, nodo **milista);
int esMiembro(nodo **milista, legislador *milegislador);

int main()
{
    ingresarVotos();
}

legislador crearLegislador(char mandato[1], char nombre[10])
{
    legislador milegislador;
    strcpy(milegislador.lnombre, nombre);
    return milegislador;
}

nodo *crearNodo(legislador *milegislador)
{
    nodo *nuevoNodo = (nodo *)malloc(sizeof(nodo));
    strcpy(nuevoNodo->chico.lnombre, milegislador->lnombre);
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void agregar(nodo **milista, nodo *nuevoNodo)
{
    if (*milista == NULL)
    {
        *milista = nuevoNodo;
    }
    else
    {
        nodo *puntero;
        puntero = *milista;
        while (puntero->siguiente != NULL)
        {
            puntero = puntero->siguiente;
        }
        puntero->siguiente = nuevoNodo;
    }
}

void ingresarVotos()
{
    printf("Ingrese voto de legislador: F (Favorable) / D (Desfavorable) o E para finalizar\n");
    scanf("%s", mandato);
    if (strcmp(mandato, "E") != 0)
    {
        pedirLegislador();
    }
    printf("Fin de carga\n");
    printf("Chicos Buenos:\n");
    mostrar(&chicosBuenos);
    printf("\n");
    printf("\nChicos Malos:\n");
    mostrar(&chicosMalos);
}

void pedirLegislador()
{
    if (strcmp(mandato, "E") != 0)
    {
        printf("Ingrese nombre de legislador\n");
        scanf("%s", nombre);
        while (strcmp(mandato, "E") != 0)
        {
            legislador milegislador = crearLegislador(mandato, nombre);
            procesar(&milegislador);
            printf("Ingrese voto de legislador: F (Favorable) / D (Desfavorable) o E para finalizar\n");
            scanf("%s", mandato);
            pedirLegislador();
        }
    }
    else if (strcmp(mandato, "E") == 0)
    {
        return;
    }
}

void procesar(legislador *milegislador)
{
    nodo *eliminado = NULL;
    if (strcmp(mandato, "D") == 0)
    {
        eliminado = eliminarListaVieja(&chicosBuenos, milegislador);
        if (eliminado != NULL)
        {
            printf("El legislador %s cambio su votacion.\n", eliminado->chico.lnombre);
            agregar(&chicosMalos, eliminado);
            eliminar(eliminado, &chicosBuenos);
        }
        else
        {
            if (esMiembro(&chicosMalos, milegislador) == 0)
            {
                nodo *nuevoNodo = crearNodo(milegislador);
                agregar(&chicosMalos, nuevoNodo);
                // printf("Agrego a %s a chicos malos\n", milegislador->lnombre);
            }
            else
            {
                printf("Ya estaba en la lista\n");
            }
        }
    }

    else if (strcmp(mandato, "F") == 0)
    {
        eliminado = eliminarListaVieja(&chicosMalos, milegislador);
        // printf("eliminado es %s\n", eliminado->chico.lnombre);
        if (eliminado != NULL)
        {
            // printf("151 Ese fulano ya estaba en la otra lista.\n");
            agregar(&chicosBuenos, eliminado);
            eliminar(eliminado, &chicosMalos);
        }
        else
        {
            if (esMiembro(&chicosBuenos, milegislador) == 0)
            {
                nodo *nuevoNodo = crearNodo(milegislador);
                agregar(&chicosBuenos, nuevoNodo);
                // printf("Agrego %s a chicos Buenos\n", milegislador->lnombre);
            }
            else
            {
                printf("Ya estaba en la lista\n");
            }
        }
    }
}

void mostrar(nodo **milista)
{
    if (*milista == NULL) // CAMBIE ACA
    {
        printf("Lista vacia\n");
    }
    else
    {
        nodo *puntero;
        puntero = *milista;
        int cont = 1;
        printf("Legislador %d: %s\n", cont, puntero->chico.lnombre);
        while (puntero->siguiente != NULL)
        {
            puntero = puntero->siguiente;
            cont++;
            printf("Legislador %d: %s\n", cont, puntero->chico.lnombre);
        }
        printf("Fin de lista\n");
    }
}

nodo *eliminarListaVieja(nodo **milista, legislador *milegislador)
{
    if (*milista != NULL)
    {
        nodo *puntero = *milista;
        if (strcmp(puntero->chico.lnombre, milegislador->lnombre) == 0)
        {
            // eliminar(puntero, milista);
            return puntero;
        }
        else if (strcmp(puntero->chico.lnombre, milegislador->lnombre) != 0)
        {
            while (puntero->siguiente)
            {
                puntero = puntero->siguiente;
                if (strcmp(puntero->chico.lnombre, milegislador->lnombre) == 0)
                {
                    // printf("225 Puntero es:  %s\n", puntero->chico.lnombre);
                    // eliminar(puntero, milista);
                    return puntero;
                }
            }
            return NULL;
        }
        return puntero;
    }
    return NULL;
}

void eliminar(nodo *puntero, nodo **milista)
{
    if (*milista != NULL)
    {
        nodo *anterior;

        if (strcmp(puntero->chico.lnombre, (*milista)->chico.lnombre) == 0)
        {
            if (puntero->siguiente == NULL)
            {
                *milista = (*milista)->siguiente; // Elimino el primero
                printf("Elimino el unico\n");
            }
            else if ((puntero->siguiente != NULL) && ((*milista)->siguiente))
            {
                printf("Entro a borrar el primero\n");
                nodo *aux = (puntero)->siguiente;
                printf("Aux tiene %p\n", aux);
                (*puntero).siguiente = NULL;
                *milista = aux;
            }
        }

        else if ((strcmp(puntero->chico.lnombre, (*milista)->chico.lnombre) != 0)) // Si no es el primero
        {
            anterior = *milista; // Ubico el anterior en cima de la lista
            printf("Ubico el anterior en cima de la lista\n");
            if (strcmp(puntero->chico.lnombre, anterior->siguiente->chico.lnombre) == 0) // Si es el segundo
            {
                printf("Si es el segundo\n");
                nodo *aux = (puntero)->siguiente;
                (*puntero).siguiente = NULL;
                anterior->siguiente = aux;
                printf("Enlazo el anterior al proximo\n");
            }
        
            else if (strcmp(puntero->chico.lnombre, anterior->siguiente->chico.lnombre) != 0)
            { // Si no es el segundo
                printf("Si no es el segundo\n");
                while (anterior->siguiente != NULL)
                {
                    anterior = anterior->siguiente;
                    if (strcmp(puntero->chico.lnombre, anterior->siguiente->chico.lnombre) == 0) // Si es el siguiente
                    {
                        nodo *aux = puntero->siguiente;
                        puntero->siguiente = NULL;
                        anterior->siguiente = aux;
                        printf("270 Enlazo el anterior al proximo");
                        return;
                    }
                    else if (strcmp(puntero->chico.lnombre, anterior->siguiente->chico.lnombre) != 0)
                    {
                        printf("255 Termino de buscar\n");
                    }
                }

                if (strcmp(puntero->chico.lnombre, anterior->siguiente->chico.lnombre) != 0)
                {
                    printf("260 Termino de buscar\n");
                }
                        }
        }
    }
    else
    {
        printf("Nada que hacer aca\n");
    }
}

int esMiembro(nodo **milista, legislador *milegislador) // Devuelve 1 si el nombre esta en la lista
{
    if (*milista == NULL)
    {
        // printf("Lista vacia\n");
        return 0;
    }
    else
    {
        nodo *puntero;
        puntero = *milista;
        // printf("Primer Nombre de la lista es %s\n", puntero->chico.lnombre);
        if (strcmp(puntero->chico.lnombre, milegislador->lnombre) == 0)
        {
            return 1;
        }
        else if (strcmp(puntero->chico.lnombre, milegislador->lnombre) != 0)
        {

            while (puntero->siguiente != NULL)
            {
                puntero = puntero->siguiente;
                if (strcmp(puntero->chico.lnombre, milegislador->lnombre) == 0)
                {
                    return 1;
                }
            }
        }
        // printf("Fin de comparacion\n");
    }
}