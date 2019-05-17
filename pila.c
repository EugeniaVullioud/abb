#include "pila.h"
#include <stdlib.h>

#define  CAPACIDAD_INICIAL 1
#define  REDIMENSION 2


/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};


/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/


pila_t* pila_crear(void){
    
    pila_t* pila = malloc(sizeof(pila_t));

    if (pila == NULL) {
        return NULL;
    }
    pila->datos = malloc(sizeof(void**));

    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }
    pila->capacidad=CAPACIDAD_INICIAL; 
    pila->cantidad=0; 
    return pila;

}


void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
	
}	


bool pila_esta_vacia(const pila_t *pila){
	
	return (pila->cantidad==0);
}
	

void pila_redimensionar(pila_t *pila, size_t tamanio ){
	
	void* datos_nuevo=realloc(pila->datos, tamanio*sizeof(void*));
	
	pila->datos=datos_nuevo;
	pila->capacidad=tamanio; 

}

		
bool pila_apilar(pila_t *pila, void* valor){

	if (pila->cantidad == pila->capacidad){

		size_t nueva_capacidad= REDIMENSION * pila->capacidad;
		
		pila_redimensionar(pila, nueva_capacidad);
		
		if (pila->datos==NULL) return false;
	
	}
	
	pila->datos[pila->cantidad]=valor;
	pila->cantidad+=1;
	
	return true;
	 
	
}


void* pila_ver_tope(const pila_t *pila){

	if ( ! pila_esta_vacia(pila)){
		return pila->datos[pila->cantidad-1];
	}
	return NULL;	
}


void* pila_desapilar(pila_t *pila){

	if ( pila_esta_vacia(pila)) return NULL;
	
	void* tope=pila_ver_tope(pila);
			
	pila->cantidad-=1;
	
	if (pila->capacidad/4==pila->cantidad && pila->cantidad>2){
		
		size_t nueva_capacidad= pila->capacidad / REDIMENSION;
		
		pila_redimensionar(pila, nueva_capacidad);
		
		if (pila->datos==NULL) return NULL;	
	}
	return tope;
}






