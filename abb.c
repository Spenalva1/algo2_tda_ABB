#include "abb.h"

#define ERROR -1
#define SIN_ERROR 0

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    if(!comparador)
        return NULL;
    abb_t* abb = calloc(1, sizeof(abb_t));
    if(!abb)
        return NULL;
    abb->comparador = comparador;
    abb->destructor = destructor;
    return abb;
}

/*
*
*/
nodo_abb_t* insertar_nodo(nodo_abb_t* nodo, abb_comparador comparador, void* elemento){
    if(!comparador)
        return NULL;
    if(!nodo){
        nodo_abb_t* nodo_nuevo = calloc(1, sizeof(nodo_abb_t));
        if(!nodo_nuevo)
            return NULL;
        nodo_nuevo->elemento = elemento;
        nodo = nodo_nuevo;
        return nodo;
    }
    int comparacion = comparador(nodo->elemento, elemento);
    if(comparacion == -1)
        nodo->derecha = insertar_nodo(nodo->derecha, comparador, elemento);
    else
        nodo->izquierda = insertar_nodo(nodo->izquierda, comparador, elemento);
    return nodo;
}

int arbol_insertar(abb_t* arbol, void* elemento){
    if(!arbol || !(arbol->comparador))
        return ERROR;
    nodo_abb_t* nueva_raiz = insertar_nodo(arbol->nodo_raiz, arbol->comparador, elemento);
    if(!nueva_raiz)
        return ERROR;
    arbol->nodo_raiz = nueva_raiz;
    return SIN_ERROR;
}

void* buscar_nodo(nodo_abb_t* nodo, abb_comparador comparador, void* elemento){
    if(!nodo)
        return NULL;
    int comparacion = comparador(nodo->elemento, elemento);
    if(comparacion == -1)
        return buscar_nodo(nodo->derecha, comparador, elemento);
    else if (comparacion == 1)
        return buscar_nodo(nodo->izquierda, comparador, elemento);
    return elemento;
}

void* arbol_buscar(abb_t* arbol, void* elemento){
    if(!arbol || !(arbol->comparador))
        return NULL;
    return buscar_nodo(arbol->nodo_raiz, arbol->comparador, elemento);
}

void* arbol_raiz(abb_t* arbol){
    if(!arbol || !(arbol->nodo_raiz))
        return NULL;
    return arbol->nodo_raiz->elemento;
}

bool arbol_vacio(abb_t* arbol){
    return (!arbol || !(arbol->nodo_raiz));
}

void destruir_nodos(nodo_abb_t* nodo, abb_liberar_elemento destructor){
    if(!nodo)
        return;
    destruir_nodos(nodo->izquierda, destructor);
    destruir_nodos(nodo->derecha, destructor);
    if(destructor)
        destructor(nodo->elemento);
    free(nodo);
}

void arbol_destruir(abb_t* arbol){
    if(!arbol)
        return;
    destruir_nodos(arbol->nodo_raiz, arbol->destructor);
    free(arbol);
}