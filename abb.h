#ifndef ABB_H
#define ABB_H


#include <stdbool.h>
#include <stdlib.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* El abb esta planteado como un puntero a un arbol. */
struct abb;
typedef struct abb abb_t;


/* tipo de función para comparar claves. */
typedef int (*abb_comparar_clave_t) (const char *, const char *);

/* tipo de función para destruir dato. */
typedef void (*abb_destruir_dato_t) (void *);


/* El iterador esta planteado como un iterador externo. */
struct abb_iter;
typedef struct abb_iter abb_iter_t;



/* ******************************************************************
 *	                    PRIMITIVAS DEL ABB
 * *****************************************************************/


/* Crea el abb. */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/* Guarda un elemento en el abb, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura abb fue inicializada.
 * Post: Se almacenó el par (clave, dato).
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/* Borra un elemento del abb y devuelve el dato asociado.  Devuelve
 * NULL si el dato no estaba.
 * Pre: La estructura abb fue inicializada.
 * Post: El elemento fue borrado de la estructura y se lo devolvió,
 * en el caso de que estuviera guardado.
 */
void *abb_borrar(abb_t *arbol, const char *clave);

/* Obtiene el valor de un elemento del abb, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura abb fue inicializada.
 */
void *abb_obtener(const abb_t *arbol, const char *clave);

/* Determina si clave pertenece o no al abb.
 * Pre: La estructura abb fue inicializada.
 * Post: devuelve verdadero si la clave estaba, falso en caso contrario.
 */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/* Devuelve la cantidad de elementos del abb.
 * Pre: La estructura abb fue inicializada.
 */
size_t abb_cantidad(abb_t *arbol);

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura abb fue inicializada.
 * Post: La estructura abb fue destruida.
 */
void abb_destruir(abb_t *arbol);



/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

/* Crea un iterador para el abb. Que empieza en el elemento mas de la izquierda del abb.
 * Pre: el abb fue creado.
 * Post: devuelve un nuevo iterador para el abb, posicionado en el elemento mas a la izquierda.
 */ 
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

/* Avanza una posicion en el iterador, lo cual implica que va a el nodo de la derecha y a todos sus hijos izquierdos. Devuelve verdadero si pudo avanzar y falso en caso contrario.
 * Pre: el iterador fue creado.
 * Post: el iterador esta en el elemento mas a la izquierda.
 */ 
bool abb_iter_in_avanzar(abb_iter_t *iter);

/* Obtiene la clave del elemento de el abb al cual apunta el iterador actualmente. Si el abb tiene
 * elementos, se devuelve la clave, si está vacía devuelve NULL.
 * Pre: el iterador fue creado.
 * Post: se devolvió la clave de el abb, cuando no está vacía.
 */
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

/* Analiza si el iterador llego al final. Devuelve verdadero en caso de ser cierto y falso en caso contrario.
 * Pre: el iterador fue creado.
 * Post: devolvio verdadero si el iterador esta al final, en caso contrario devolvio false.
 */
bool abb_iter_in_al_final(const abb_iter_t *iter);

/* Destruye el iterador de el abb.
 * Pre: el iterador fue creado.
 * Post: se elimino el iterador.
 */
void abb_iter_in_destruir(abb_iter_t* iter);


/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);



/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
//
// Las pruebas no acceden a los miembros del struct abb ni a los miembros del struct abb_iter.
//
// Empleaa la función print_test(), como se ha visto en TPs anteriores.

void pruebas_abb_alumno(void);

#endif // ABB_H
