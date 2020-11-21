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
    nodo_abb_t* nodo_aux;
    int comparacion = comparador(nodo->elemento, elemento);
    if(comparacion == -1){
        nodo_aux = insertar_nodo(nodo->derecha, comparador, elemento);
        if(!nodo_aux)
            return NULL;
        nodo->derecha = nodo_aux;
    }else{
        nodo_aux = insertar_nodo(nodo->izquierda, comparador, elemento);
        if(!nodo_aux)
            return NULL;
        nodo->izquierda = nodo_aux;
    }
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

/*
*
*/
void* borrar_nodo(nodo_abb_t* nodo, abb_comparador comparador, abb_liberar_elemento destructor, void* elemento, bool* elemento_borrado){
    if(!comparador || !nodo)
        return NULL;
    int comparacion = comparador(nodo->elemento, elemento);
    if(comparacion == -1){
        nodo->derecha = borrar_nodo(nodo->derecha, comparador, destructor, elemento, elemento_borrado);
    }else if(comparacion == 1){
        nodo->izquierda = borrar_nodo(nodo->izquierda, comparador, destructor, elemento, elemento_borrado);
    } else {
        // SI LLEGA ACA ES QUE YA LO ENCONTRO -> HAY QUE BORRAR
        if(nodo->izquierda && nodo->derecha){
            //tiene dos hijos
        } else if (nodo->izquierda || nodo->derecha){
            //tiene un hijo
        } else {
            //no tiene hijos -> es hoja
            if(destructor)
                destructor(elemento);
            free(nodo);
            *elemento_borrado = true;
            return NULL;
        }
    }
    return nodo;
}

int arbol_borrar(abb_t* arbol, void* elemento){
    if(arbol_vacio(arbol) || !(arbol->comparador))
        return ERROR;
    //TENER EN CUENTA CASO EN EL QUE SE BORRA LA RAIZ
    bool elemento_borrado = false;
    arbol->nodo_raiz = borrar_nodo(arbol->nodo_raiz, arbol->comparador, arbol->destructor, elemento, &elemento_borrado);
    return (elemento_borrado) ? SIN_ERROR : ERROR;
}

/*
*
*/
void* buscar_nodo(nodo_abb_t* nodo, abb_comparador comparador, void* elemento){
    if(!nodo || !comparador)
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