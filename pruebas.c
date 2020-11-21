#include "abb.h"
#include "pa2mm.h"

#define ERROR -1
#define SIN_ERROR 0

int comparador(void* elemento_1, void* elemento_2){
    if((*(int*)elemento_1) > (*(int*)elemento_2))
        return 1;
    else if((*(int*)elemento_1) < (*(int*)elemento_2))
        return -1;
    return 0;
}

void destructor(void* elemento){
    free((int*)elemento);
}

void pruebas_arbol_crear(){
    pa2m_nuevo_grupo("Pruebas crear árbol");
    abb_t* abb = arbol_crear(NULL, NULL);
    pa2m_afirmar(abb == NULL, "No crea el árbol si no recibe comparador")
    abb = arbol_crear(&comparador, &destructor);
    pa2m_afirmar(abb != NULL, "Crea el árbol");
    pa2m_afirmar(abb->nodo_raiz == NULL, "Nodo raíz igual a NULL");
    pa2m_afirmar(abb->comparador == &comparador, "El árbol apunta al comparador recibido");
    pa2m_afirmar(abb->destructor == &destructor, "El árbol apunta al destructor recibido");
    arbol_destruir(abb);
}

void pruebas_arbol_insertar(){
    pa2m_nuevo_grupo("Pruebas árbol insertar");
    abb_t* abb = arbol_crear(&comparador, NULL);
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    pa2m_afirmar(arbol_insertar(NULL, &a) == ERROR, "No inserta si no recibe puntero a un árbol");
    pa2m_afirmar(arbol_insertar(abb, &c) == SIN_ERROR, "Insertó un 3 (primer elemento)");
    pa2m_afirmar(abb->nodo_raiz != NULL, "Existe una raíz");
    pa2m_afirmar(comparador(abb->nodo_raiz->elemento, &c) == 0, "Elemento de la raíz correcto (un 3)");
    pa2m_afirmar(abb->nodo_raiz->izquierda == NULL, "Hijo izquierdo de nodo insertado igual a NULL");
    pa2m_afirmar(abb->nodo_raiz->derecha == NULL, "Hijo derecho de nodo insertado igual a NULL");
    pa2m_afirmar(arbol_insertar(abb, &b) == SIN_ERROR, "Insertó un 2");
    pa2m_afirmar(arbol_insertar(abb, &a) == SIN_ERROR, "Insertó un 1");
    pa2m_afirmar(arbol_insertar(abb, &e) == SIN_ERROR, "Insertó un 5");
    pa2m_afirmar(arbol_insertar(abb, &d) == SIN_ERROR, "Insertó un 4");
    pa2m_afirmar(arbol_insertar(abb, &f) == SIN_ERROR, "Insertó un 6");
    pa2m_afirmar(comparador(abb->nodo_raiz->izquierda->izquierda->elemento, &a) == 0, "El 1 en la posición correcta");
    pa2m_afirmar(comparador(abb->nodo_raiz->izquierda->elemento, &b) == 0, "El 2 en la posición correcta");
    pa2m_afirmar(comparador(abb->nodo_raiz->derecha->elemento, &e) == 0, "El 5 en la posición correcta");
    pa2m_afirmar(comparador(abb->nodo_raiz->derecha->izquierda->elemento, &d) == 0, "El 5 en la posición correcta");
    pa2m_afirmar(comparador(abb->nodo_raiz->derecha->derecha->elemento, &f) == 0, "El 6 en la posición correcta");
    arbol_destruir(abb);
}

void pruebas_arbol_borrar(){
    pa2m_nuevo_grupo("Pruebas árbol borrar");
    pa2m_afirmar(arbol_borrar(NULL, NULL) == ERROR, "No borra si recibe árbol nulo");
    abb_t* abb = arbol_crear(&comparador, NULL);
    pa2m_afirmar(arbol_borrar(abb, NULL) == ERROR, "No borra si recibe árbol vacío");
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    printf("  Inserto 3, 2, 1, 5, 4, 6\n");
    arbol_insertar(abb, &c);
    arbol_insertar(abb, &b);
    arbol_insertar(abb, &a);
    arbol_insertar(abb, &e);
    arbol_insertar(abb, &d);
    arbol_insertar(abb, &f);
    pa2m_afirmar(arbol_borrar(abb, &a) == SIN_ERROR, "Borro una hoja");
    pa2m_afirmar(abb->nodo_raiz->izquierda->izquierda == NULL, "Padre de la hoja anterior apunta ahora a NULL");
    arbol_destruir(abb);
}

void pruebas_arbol_buscar(){
    pa2m_nuevo_grupo("Pruebas árbol buscar");
    abb_t* abb = arbol_crear(&comparador, NULL);
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
    printf("  Inserto 3, 2, 1, 5, 4, 6\n");
    arbol_insertar(abb, &c);
    arbol_insertar(abb, &b);
    arbol_insertar(abb, &a);
    arbol_insertar(abb, &e);
    arbol_insertar(abb, &d);
    arbol_insertar(abb, &f);
    pa2m_afirmar(arbol_buscar(NULL, &a) == NULL, "No busca si no recibe árbol");
    pa2m_afirmar(arbol_buscar(abb, &a) == &a, "El 1 se encuentra en el árbol");
    pa2m_afirmar(arbol_buscar(abb, &b) == &b, "El 2 se encuentra en el árbol");
    pa2m_afirmar(arbol_buscar(abb, &c) == &c, "El 3 se encuentra en el árbol");
    pa2m_afirmar(arbol_buscar(abb, &d) == &d, "El 4 se encuentra en el árbol");
    pa2m_afirmar(arbol_buscar(abb, &e) == &e, "El 5 se encuentra en el árbol");
    pa2m_afirmar(arbol_buscar(abb, &f) == &f, "El 6 se encuentra en el árbol");
    pa2m_afirmar(arbol_buscar(abb, &g) == NULL, "El 7 NO se encuentra en el árbol");
    arbol_destruir(abb);
}

void pruebas_arbol_raiz(){
    pa2m_nuevo_grupo("Pruebas árbol raiz");
    pa2m_afirmar(arbol_raiz(NULL) == NULL, "Devuelve null si recibe árbol nulo");
    abb_t* abb = arbol_crear(comparador, NULL);
    pa2m_afirmar(arbol_raiz(abb) == NULL, "Devuelve null si la raíz es nula (árbol vacío)");
    int a = 1;
    arbol_insertar(abb, &a);
    printf("  Inserto un elemento\n");
    pa2m_afirmar(arbol_raiz(abb) == &a, "Elemento de la raíz correcto");
    arbol_destruir(abb);
}

void pruebas_arbol_vacio(){
    pa2m_nuevo_grupo("Pruebas árbol vacío");
    pa2m_afirmar(arbol_vacio(NULL) == true, "Devuelve true si recibe árbol nulo");
    abb_t* abb = arbol_crear(comparador, NULL);
    pa2m_afirmar(arbol_vacio(abb) == true, "Devuelve true si la raíz es nula (árbol vacío)");
    int a = 1;
    arbol_insertar(abb, &a);
    printf("  Inserto un elemento\n");
    pa2m_afirmar(arbol_vacio(abb) == false, "Devuelve false si existen elementos");
    arbol_destruir(abb);
}

void pruebas_destructor_borrar(){
    abb_t* abb = arbol_crear(&comparador, destructor);
    int* a = malloc(sizeof(int));
    *a = 1;
    int* b = malloc(sizeof(int));
    *b = 2;
    int* c = malloc(sizeof(int));
    *c = 3;
    int* d = malloc(sizeof(int));
    *d = 4;
    int* e = malloc(sizeof(int));
    *e = 5;
    int* f = malloc(sizeof(int));
    *f = 6;
    arbol_insertar(abb, c);
    arbol_insertar(abb, b);
    arbol_insertar(abb, a);
    arbol_insertar(abb, e);
    arbol_insertar(abb, d);
    arbol_insertar(abb, f);
    arbol_destruir(abb);
}

int main(){
    pruebas_arbol_crear();
    pruebas_arbol_insertar();
    pruebas_arbol_borrar();
    pruebas_arbol_buscar();
    pruebas_arbol_raiz();
    pruebas_arbol_vacio();
    pruebas_destructor_borrar();
    pa2m_mostrar_reporte();
    return 0;
}