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
    if(elemento)
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
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
    printf("  Inserto 3, 2, 1, 6, 4, 7, 5 (en ese orden)\n");
    arbol_insertar(abb, &c);
    arbol_insertar(abb, &b);
    arbol_insertar(abb, &a);
    arbol_insertar(abb, &f);
    arbol_insertar(abb, &d);
    arbol_insertar(abb, &g);
    arbol_insertar(abb, &e);
    pa2m_afirmar(arbol_borrar(abb, &a) == SIN_ERROR, "Borro una hoja");
    pa2m_afirmar(abb->nodo_raiz->izquierda->izquierda == NULL, "Padre de la hoja anterior apunta ahora a NULL");
    printf("  Vuelvo a insertar el 1\n");
    arbol_insertar(abb, &a);
    pa2m_afirmar(arbol_borrar(abb, &b) == SIN_ERROR, "Borro el 2 que tiene un solo hijo (el 2 era hijo izquierdo del 3)");
    pa2m_afirmar(abb->nodo_raiz->izquierda->elemento == &a, "Ahora el 3 a su izquierda apunta al 1")
    pa2m_afirmar(arbol_borrar(abb, &f) == SIN_ERROR, "Borro el 6 que tiene dos hijos (4 a la izquierda, 7 a la derecha)");
    pa2m_afirmar(abb->nodo_raiz->derecha->elemento == &e, "Ahora el 5 ocupa el lugar que era del 6");
    pa2m_afirmar(abb->nodo_raiz->derecha->izquierda->elemento == &d, "El 4 ahora es hijo izquierdo del 5");
    pa2m_afirmar(abb->nodo_raiz->derecha->derecha->elemento == &g, "El 7 ahora es hijo derecho del 5");
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

void mostrar_elementos_vector(void** array, size_t cant){
    for(int i = 0; i < cant; i++){
        printf("%d ", *(int*)array[i]);
    }
    printf("\n");
}

void pruebas_recorrido_inorden(){
    pa2m_nuevo_grupo("Pruebas recorrido inorden");
    void* numeros[50];
    pa2m_afirmar(arbol_recorrido_inorden(NULL, numeros, 20) == 0, "Si el árbol es nulo recorre 0 elementos");
    abb_t* abb = arbol_crear(&comparador, NULL);
    pa2m_afirmar(arbol_recorrido_inorden(abb, NULL, 20) == 0, "Si el array es nulo recorre 0 elementos");
    pa2m_afirmar(arbol_recorrido_inorden(abb, numeros, 0) == 0, "Si el tamaño del array es nulo recorre 0 elementos");
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
    printf("  Inserto 3, 2, 1, 6, 4, 7, 5 (en ese orden)\n");
    arbol_insertar(abb, &c);
    arbol_insertar(abb, &b);
    arbol_insertar(abb, &a);
    arbol_insertar(abb, &f);
    arbol_insertar(abb, &d);
    arbol_insertar(abb, &g);
    arbol_insertar(abb, &e);
    size_t elementos_recorridos = arbol_recorrido_inorden(abb, numeros, 20);
    pa2m_afirmar(elementos_recorridos == 7, "Recorre todos los elementos del árbol");
    printf("  Muestro elementos recorridos inorder: ");
    mostrar_elementos_vector(numeros, elementos_recorridos);
    elementos_recorridos = arbol_recorrido_inorden(abb, numeros, 3);
    pa2m_afirmar(elementos_recorridos == 3, "Recorre 3 elementos del árbol");
    printf("  Muestro los 3 elementos recorridos inorder: ");
    mostrar_elementos_vector(numeros, elementos_recorridos);
    arbol_destruir(abb);
}

void pruebas_recorrido_preorden(){
    pa2m_nuevo_grupo("Pruebas recorrido preorden");
    void* numeros[50];
    pa2m_afirmar(arbol_recorrido_preorden(NULL, numeros, 20) == 0, "Si el árbol es nulo recorre 0 elementos");
    abb_t* abb = arbol_crear(&comparador, NULL);
    pa2m_afirmar(arbol_recorrido_preorden(abb, NULL, 20) == 0, "Si el array es nulo recorre 0 elementos");
    pa2m_afirmar(arbol_recorrido_preorden(abb, numeros, 0) == 0, "Si el tamaño del array es nulo recorre 0 elementos");
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
    printf("  Inserto 3, 2, 1, 6, 4, 7, 5 (en ese orden)\n");
    arbol_insertar(abb, &c);
    arbol_insertar(abb, &b);
    arbol_insertar(abb, &a);
    arbol_insertar(abb, &f);
    arbol_insertar(abb, &d);
    arbol_insertar(abb, &g);
    arbol_insertar(abb, &e);
    size_t elementos_recorridos = arbol_recorrido_preorden(abb, numeros, 20);
    pa2m_afirmar(elementos_recorridos == 7, "Recorre todos los elementos del árbol");
    printf("  Muestro elementos recorridos preorden: ");
    mostrar_elementos_vector(numeros, elementos_recorridos);
    elementos_recorridos = arbol_recorrido_preorden(abb, numeros, 3);
    pa2m_afirmar(elementos_recorridos == 3, "Recorre 3 elementos del árbol");
    printf("  Muestro los 3 elementos recorridos preorden: ");
    mostrar_elementos_vector(numeros, elementos_recorridos);
    arbol_destruir(abb);
}

void pruebas_recorrido_postorden(){
    pa2m_nuevo_grupo("Pruebas recorrido postorden");
    void* numeros[50];
    pa2m_afirmar(arbol_recorrido_postorden(NULL, numeros, 20) == 0, "Si el árbol es nulo recorre 0 elementos");
    abb_t* abb = arbol_crear(&comparador, NULL);
    pa2m_afirmar(arbol_recorrido_postorden(abb, NULL, 20) == 0, "Si el array es nulo recorre 0 elementos");
    pa2m_afirmar(arbol_recorrido_postorden(abb, numeros, 0) == 0, "Si el tamaño del array es nulo recorre 0 elementos");
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
    printf("  Inserto 3, 2, 1, 6, 4, 7, 5 (en ese orden)\n");
    arbol_insertar(abb, &c);
    arbol_insertar(abb, &b);
    arbol_insertar(abb, &a);
    arbol_insertar(abb, &f);
    arbol_insertar(abb, &d);
    arbol_insertar(abb, &g);
    arbol_insertar(abb, &e);
    size_t elementos_recorridos = arbol_recorrido_postorden(abb, numeros, 20);
    pa2m_afirmar(elementos_recorridos == 7, "Recorre todos los elementos del árbol");
    printf("  Muestro elementos recorridos postorden: ");
    mostrar_elementos_vector(numeros, elementos_recorridos);
    elementos_recorridos = arbol_recorrido_postorden(abb, numeros, 3);
    pa2m_afirmar(elementos_recorridos == 3, "Recorre 3 elementos del árbol");
    printf("  Muestro los 3 elementos recorridos postorden: ");
    mostrar_elementos_vector(numeros, elementos_recorridos);
    arbol_destruir(abb);
}

bool mostrar_elemento_al_iterar(void* elemento, void* extra){
    printf("%d ", *(int*)elemento);
    return false;
}

bool mostrar_elemento_al_iterar_hasta_el_4(void* elemento, void* extra){
    printf("%d ", *(int*)elemento);
    return *(int*)elemento == 4;
}

void pruebas_con_cada_elemento_inorden(){
    pa2m_nuevo_grupo("Pruebas con cada elemento inorden");
    int extra = 0;
    pa2m_afirmar(abb_con_cada_elemento(NULL, ABB_RECORRER_INORDEN, &mostrar_elemento_al_iterar, &extra) == 0, "Si el árbol es nulo recorre 0 elementos");
    abb_t* abb = arbol_crear(&comparador, NULL);
    pa2m_afirmar(abb_con_cada_elemento(abb, ABB_RECORRER_INORDEN, NULL, &extra) == 0, "Si la funcion es nula recorre 0 elementos");
    pa2m_afirmar(abb_con_cada_elemento(abb, 55, &mostrar_elemento_al_iterar, &extra) == 0, "Si el recorrido no existe recorre 0 elementos");
    pa2m_afirmar(abb_con_cada_elemento(abb, ABB_RECORRER_INORDEN, &mostrar_elemento_al_iterar, &extra) == 0, "Si el árbol está vacío recorre 0 elementos");
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
    printf("  Inserto 3, 2, 1, 6, 4, 7, 5 (en ese orden)\n");
    arbol_insertar(abb, &c);
    arbol_insertar(abb, &b);
    arbol_insertar(abb, &a);
    arbol_insertar(abb, &f);
    arbol_insertar(abb, &d);
    arbol_insertar(abb, &g);
    arbol_insertar(abb, &e);
    printf("  Imprimo elementos con interador interno de forma inorden:\n  ");
    size_t iteraciones = abb_con_cada_elemento(abb, ABB_RECORRER_INORDEN, &mostrar_elemento_al_iterar, &extra);
    printf("\n");
    pa2m_afirmar(iteraciones == 7, "Iteró sobre 7 elementos");
    printf("  Imprimo elementos con interador interno de forma inorden hasta el 3:\n  ");
    iteraciones = abb_con_cada_elemento(abb, ABB_RECORRER_INORDEN, &mostrar_elemento_al_iterar_hasta_el_4, &extra);
    printf("\n");
    pa2m_afirmar(iteraciones == 4, "Iteró sobre 4 elementos");
    arbol_destruir(abb);
}

void pruebas_con_cada_elemento_preorden(){
    pa2m_nuevo_grupo("Pruebas con cada elemento preorden");
    int extra = 0;
    pa2m_afirmar(abb_con_cada_elemento(NULL, ABB_RECORRER_PREORDEN, &mostrar_elemento_al_iterar, &extra) == 0, "Si el árbol es nulo recorre 0 elementos");
    abb_t* abb = arbol_crear(&comparador, NULL);
    pa2m_afirmar(abb_con_cada_elemento(abb, ABB_RECORRER_PREORDEN, NULL, &extra) == 0, "Si la funcion es nula recorre 0 elementos");
    pa2m_afirmar(abb_con_cada_elemento(abb, 55, &mostrar_elemento_al_iterar, &extra) == 0, "Si el recorrido no existe recorre 0 elementos");
    pa2m_afirmar(abb_con_cada_elemento(abb, ABB_RECORRER_PREORDEN, &mostrar_elemento_al_iterar, &extra) == 0, "Si el árbol está vacío recorre 0 elementos");
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
    printf("  Inserto 3, 2, 1, 6, 4, 7, 5 (en ese orden)\n");
    arbol_insertar(abb, &c);
    arbol_insertar(abb, &b);
    arbol_insertar(abb, &a);
    arbol_insertar(abb, &f);
    arbol_insertar(abb, &d);
    arbol_insertar(abb, &g);
    arbol_insertar(abb, &e);
    printf("  Imprimo elementos con interador interno de forma preorden:\n  ");
    size_t iteraciones = abb_con_cada_elemento(abb, ABB_RECORRER_PREORDEN, &mostrar_elemento_al_iterar, &extra);
    printf("\n");
    pa2m_afirmar(iteraciones == 7, "Iteró sobre 7 elementos");
    printf("  Imprimo elementos con interador interno de forma preorden hasta el 3:\n  ");
    iteraciones = abb_con_cada_elemento(abb, ABB_RECORRER_PREORDEN, &mostrar_elemento_al_iterar_hasta_el_4, &extra);
    printf("\n");
    pa2m_afirmar(iteraciones == 5, "Iteró sobre 5 elementos");
    arbol_destruir(abb);
}

void pruebas_con_cada_elemento_postorden(){
    pa2m_nuevo_grupo("Pruebas con cada elemento postorden");
    int extra = 0;
    pa2m_afirmar(abb_con_cada_elemento(NULL, ABB_RECORRER_POSTORDEN, &mostrar_elemento_al_iterar, &extra) == 0, "Si el árbol es nulo recorre 0 elementos");
    abb_t* abb = arbol_crear(&comparador, NULL);
    pa2m_afirmar(abb_con_cada_elemento(abb, ABB_RECORRER_POSTORDEN, NULL, &extra) == 0, "Si la funcion es nula recorre 0 elementos");
    pa2m_afirmar(abb_con_cada_elemento(abb, 55, &mostrar_elemento_al_iterar, &extra) == 0, "Si el recorrido no existe recorre 0 elementos");
    pa2m_afirmar(abb_con_cada_elemento(abb, ABB_RECORRER_POSTORDEN, &mostrar_elemento_al_iterar, &extra) == 0, "Si el árbol está vacío recorre 0 elementos");
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
    printf("  Inserto 3, 2, 1, 6, 4, 7, 5 (en ese orden)\n");
    arbol_insertar(abb, &c);
    arbol_insertar(abb, &b);
    arbol_insertar(abb, &a);
    arbol_insertar(abb, &f);
    arbol_insertar(abb, &d);
    arbol_insertar(abb, &g);
    arbol_insertar(abb, &e);
    printf("  Imprimo elementos con interador interno de forma postorden:\n  ");
    size_t iteraciones = abb_con_cada_elemento(abb, ABB_RECORRER_POSTORDEN, &mostrar_elemento_al_iterar, &extra);
    printf("\n");
    pa2m_afirmar(iteraciones == 7, "Iteró sobre 7 elementos");
    printf("  Imprimo elementos con interador interno de forma postorden hasta el 3:\n  ");
    iteraciones = abb_con_cada_elemento(abb, ABB_RECORRER_POSTORDEN, &mostrar_elemento_al_iterar_hasta_el_4, &extra);
    printf("\n");
    pa2m_afirmar(iteraciones == 4, "Iteró sobre 4 elementos");
    arbol_destruir(abb);
}

void insertar_balanceadamente(abb_t* abb, int** numeros, int cantidad, int* insertados){
    int mitad = cantidad / 2;
    if(arbol_insertar(abb, *(numeros+mitad)) == SIN_ERROR)
        (*insertados)++;
    if(mitad <= 0)
        return;
    insertar_balanceadamente(abb, numeros, mitad, insertados);
    if(mitad == cantidad-1)
        return;
    insertar_balanceadamente(abb, numeros + mitad + 1, (cantidad - mitad - 1), insertados);
}

void pruebas_con_muchos_nodos(){
    pa2m_nuevo_grupo("Pruebas con muchos nodos");
    int* numeros[1000];
    for(int i = 0; i < 1000; i++){
        numeros[i] = malloc(sizeof(int));
        *(numeros[i]) = i;
    }
    int insertados = 0;
    abb_t* abb = arbol_crear(comparador, destructor);
    insertar_balanceadamente(abb, numeros, 1000, &insertados);
    pa2m_afirmar(insertados == 1000, "Se insertaron 1000 elementos");
    int* numero = malloc(sizeof(int));
    *numero = 1000;
    pa2m_afirmar(arbol_insertar(abb, numero) == SIN_ERROR, "Inserto un elemento más");
    pa2m_afirmar(*((int*)arbol_buscar(abb, numero)) == 1000, "El último elemento insertado se encuentra en el arbol");
    pa2m_afirmar(arbol_borrar(abb, numeros[999]) == SIN_ERROR, "Borro nodo con un hijo");
    pa2m_afirmar(arbol_borrar(abb, numero) == SIN_ERROR, "Borro nodo sin hijos");    
    pa2m_afirmar(arbol_borrar(abb, numeros[500]) == SIN_ERROR, "Borro nodo con dos hijos");
    arbol_destruir(abb);
}

int main(){
    /*pruebas_arbol_crear();
    pruebas_arbol_insertar();
    pruebas_arbol_borrar();
    pruebas_arbol_buscar();
    pruebas_arbol_raiz();
    pruebas_arbol_vacio();
    pruebas_destructor_borrar();
    pruebas_recorrido_inorden();
    pruebas_recorrido_preorden();
    pruebas_recorrido_postorden();
    pruebas_con_cada_elemento_inorden();
    pruebas_con_cada_elemento_preorden();
    pruebas_con_cada_elemento_postorden();*/
    pruebas_con_muchos_nodos();
    pa2m_mostrar_reporte();
    return 0;
}