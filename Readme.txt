Se entrega la implementacion de TDA ABB (árbol binario de busqueda), con una serie de métodos para su uso.

Compilacion: 
    gcc *.c -o abb -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

Ejecucion:
    ./abb

Ejecucion con valgrind:
    valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb

El archivo ejecutable realizará todas las pruebas necesarias para demostrar la correcta implementación del trabajo.

Un ABB es una estructura de datos donde los métodos para acceder a ellos son mas eficientes que en otros tipos de datos como, por ejemplo, listas. Un arbol binario es una colección de nodos, donde cada uno puede tener hasta 2 hijos, uno izquierdo y otro derecho. Existe un nodo llamado nodo raiz que es a partir del cual se accede al arbol para despues recorrerlo de la manera que se desee. Una característica fundamental del árbol binario de busqueda es la existencia de una regla para mantener los datos ordenados a partir de una clave. Por ejemplo, si el criterio de ordenamiento es con números de menor a mayor, partiendo de un nodo, todos aqueyos que se encuentren a su izquierda serán menores a él y todos los que se encuentren a su derecha serán mayores. De esta manera se facilita la búsqueda, inserción y eliminacion de elementos en el arbol, debido a que dicha regla acelera las distintas operaciones respecto a un arbol binario normal.

El objetivo de tener una función de destrucción  en el TDA es para facilitar al usuario el proceso de destruccion del arbol. Si bien para liberar el arbol se necesita un free(abb) (siendo abb el puntero a un arbol previamente creado), puede ser que el usuario almacene elementos que esten ocupando un espacio en el heap. Por lo cual el hecho de contar con una funcion destructora permite al ABB, antes de ser liberado, liberar cada nodo que posea en su estructura. Si no contaramos con dicha función, el usuario debería tomarse el tiempo de liberar elemento por elemento antes de destruir el arbol para no tener problemas de memoria. En el caso de que el usuario decida trabajar solo con elementos almacenados en el stack, no necesitaria proveer una función de destrucción.

Para la creación del árbol solo se necesita reservar el espacio necesario en la memoria dinamica por lo que su complejidad es o(1).
