#include "abb.h"
#include "pila.c"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

/* Definición del struct nodo. */
typedef struct abb_nodo {
	const char* clave;
	void* dato;
	struct abb_nodo* der;
	struct abb_nodo* izq;
} abb_nodo_t;


/* Definición del struct abb. */
struct abb {
	abb_nodo_t* raiz;
	size_t cantidad;
	
	void (*destruir_dato) (void*);
	int (*comparar_clave) (const char *,const char *);
};


/* Definición del struct abb_iter. */
struct abb_iter {
	pila_t* pila;
	const abb_t *arbol;
};


/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

//Funciones auxiliares de los nodos.

/* Funcion auxiliar que crea un nodo. */
abb_nodo_t* crear_nodo(const char* clave, void* dato){
	abb_nodo_t* nodo=malloc(sizeof(abb_nodo_t));
	
	if (!nodo) return NULL;
	/*
	char* nueva_clave=malloc(sizeof(char)*(strlen(clave)+1));
	if(!nueva_clave){
		free(nodo);
		return NULL;
	}	
	strcpy(nueva_clave,clave);
	*/
	
	nodo->clave=clave;		
	nodo->dato=dato;
	nodo->der=NULL;
	nodo->izq=NULL;
	
	return nodo;
}

/* Funcion auxiliar que destruye un nodo. */
void destruir_nodo(abb_t* arbol,abb_nodo_t* nodo){
	
	if (!nodo)	return;
	if (arbol->destruir_dato) arbol->destruir_dato(nodo->dato);

	free(nodo);
	printf("fin destruir nodo\n");
}


//Funciones auxiliares de buscar.

/* Funcion auxiliar que busca nodos. */

abb_nodo_t* buscar(const abb_t *arbol, abb_nodo_t* nodo, const char* clave){
    
    if(!nodo) return NULL;
    int cmp=arbol->comparar_clave(clave,nodo->clave);
    
    if(cmp==0) return nodo;    
    if(cmp<0) return buscar(arbol, nodo->izq, clave);
    if(cmp>0)  return buscar(arbol, nodo->der, clave);
    return NULL;
}

/* Funcion auxiliar que busca padres. */
abb_nodo_t* buscar_padre(const abb_t *arbol, abb_nodo_t* nodo, const char* clave){
	
	if(!nodo) return NULL;
	
	abb_nodo_t* padre=nodo;
	int cmp=arbol->comparar_clave(clave,nodo->clave);
	
	if(cmp<0) buscar_padre(arbol, nodo->izq, clave);
	if(cmp>0) buscar_padre(arbol, nodo->der, clave);
	return padre;
}

/* Funcion auxiliar que swapea nodos. */
void swap( abb_t *arbol, abb_nodo_t *nodo1, abb_nodo_t *nodo2){
	abb_nodo_t* aux=crear_nodo(nodo1->clave,nodo1->dato);
	if (!aux) return;
	
	nodo1->clave=nodo2->clave;
	nodo1->dato=nodo2->dato;
	nodo2->clave=aux->clave;
	nodo2->dato=aux->dato;
	
	destruir_nodo(arbol,aux);
}



/* *****************************************************************
 *                  FUNCIONES AUXILIARES PARA BORRAR
 * *****************************************************************/


//Funcion auxiliar que borra nodos que son hojas.
void borrar_hoja( abb_t *arbol, abb_nodo_t* padre, const char *clave){
	
	if(arbol->comparar_clave(clave, padre->clave)<0){
		padre->izq=NULL;
	} else if (arbol->comparar_clave(clave, padre->clave)>0){
		padre->der=NULL;
	}
}


//Funcion auxiliar que borra nodos que tienen 1 hijo.
void borrar_1_hijo( abb_t *arbol, abb_nodo_t* nodo,abb_nodo_t* padre,const char *clave){
	printf("borro 1 hijo\n");
	if(arbol->comparar_clave(clave, padre->clave)<0){
		padre->izq=NULL;
	} else if (arbol->comparar_clave(clave, padre->clave)>0){
		padre->der=NULL;
	}
	swap(arbol,padre,nodo);
}	


//Funcion auxiliar que borra nodos que tienen 2 hijos.
void borrar_2_hijos( abb_t *arbol,abb_nodo_t* nodo, const char *clave){

	abb_nodo_t* derecho=nodo->der;

	abb_nodo_t* padre_izq=derecho;
	abb_nodo_t* izq=derecho->izq;
	
	while(izq->izq){
		padre_izq=izq;
		izq=izq->izq;
	}
	swap(arbol,izq,nodo);
	padre_izq->izq=NULL;
}	



/* ******************************************************************
 *                    PRIMITIVAS DEL ABB 
 * *****************************************************************/


abb_t* abb_crear(abb_comparar_clave_t comparar_clave, abb_destruir_dato_t destruir_dato){
	
	abb_t* arbol=malloc(sizeof(abb_t));
    if(!arbol) return NULL;
    
    arbol->raiz=NULL;
	arbol->comparar_clave=comparar_clave;
    arbol->destruir_dato = destruir_dato;
    arbol->cantidad =0; 
    
    return arbol;
}


bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	
	//si el arbol esta vacio.
	if (arbol->cantidad==0){
		abb_nodo_t* nuevo=crear_nodo(clave,dato);
		if (!nuevo) return false;
		
		arbol->raiz=nuevo;
		arbol->cantidad++;
		return true;
	}
	//si la clave ya esta, reemplazo el valor del dato por el nuevo.
	abb_nodo_t* buscado=buscar(arbol,arbol->raiz,clave);

	if (!buscado) {
		abb_nodo_t* nuevo=crear_nodo(clave,dato);
		if (!nuevo) return false;
		
		abb_nodo_t* padre= buscar_padre(arbol,arbol->raiz,clave);
		
		if(arbol->comparar_clave(clave, padre->clave)<0){
			padre->izq=nuevo;
		} else if (arbol->comparar_clave(clave, padre->clave)>0){
			padre->der=nuevo;
		}
	} else {
		printf("%s\n",buscado->clave);
		buscado->dato=dato;
		return true;
	}
	arbol->cantidad++;
	return true;
}


void *abb_borrar(abb_t *arbol, const char *clave){
	//printf("antes de buscar\n");
	abb_nodo_t* nodo_a_borrar= buscar(arbol,arbol->raiz,clave);
	if (!nodo_a_borrar) return NULL;
	//printf("despues de buscar\n");
	void* dato=nodo_a_borrar->dato;
	
	abb_nodo_t* padre= buscar_padre(arbol,arbol->raiz,clave);
	if (nodo_a_borrar->izq) printf("izq true\n");
	if (nodo_a_borrar->der) printf("der true\n");
	if (!nodo_a_borrar->izq) printf("izq false\n");
	if (!nodo_a_borrar->der) printf("der false\n");

	//CASO 3: 2 HIJOS.
	if (nodo_a_borrar->der && nodo_a_borrar->izq){
		printf("borro 2 hijo\n");
		borrar_2_hijos(arbol,nodo_a_borrar,clave);
	}
	//CASO 1: SIN HIJOS.
	if (!nodo_a_borrar->izq && !nodo_a_borrar->der){
		printf("borro hoja\n");
		borrar_hoja(arbol,padre,clave);
	}
	//CASO 2: 1 HIJO.
	else if (!nodo_a_borrar->izq || !nodo_a_borrar->der){ 
		printf("borro 1 hijo\n");
		borrar_1_hijo(arbol,nodo_a_borrar,padre,clave);
	}	
	destruir_nodo(arbol,nodo_a_borrar);
	arbol->cantidad--;
	return dato;
}


void *abb_obtener(const abb_t *arbol, const char *clave){
	abb_nodo_t* buscado=buscar(arbol,arbol->raiz,clave);
	
	if(!buscado) return NULL;
	return buscado->dato;
}


bool abb_pertenece(const abb_t *arbol, const char *clave){
	abb_nodo_t* buscado=buscar(arbol,arbol->raiz,clave);
	
	if(!buscado) return false;
	return true;
}


size_t abb_cantidad(abb_t *arbol){
	return arbol->cantidad;
}


//destruye los nodos en postorder para no perder las referencias.
void _abb_destruir(abb_t *arbol,abb_nodo_t* nodo){
	
	if (!nodo) return;
	_abb_destruir(arbol,nodo->izq);
	_abb_destruir(arbol,nodo->der);
	destruir_nodo(arbol,nodo);
}


void abb_destruir(abb_t *arbol){

	_abb_destruir(arbol,arbol->raiz);
    free(arbol);
}





/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

/*
INORDER. usa una pila.

Crear: Apilo raíz y todos los hijos izquierdos
Avanzar: Desapilo
		 Apilo hijo derecho del desapilado (si existe) y todos los hijos izquierdos
		 
Destruir: Destruyo la pila.
*/

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
	
	abb_iter_t *iter=malloc(sizeof(abb_iter_t));
	if (!iter) return NULL;
	
	iter->pila=pila_crear();
	if (!iter->pila) return NULL;
	
	iter->arbol=arbol;
	
	//apilo la raiz y todos los hijoz izq
	if (!arbol->raiz) return iter;
	
	pila_apilar(iter->pila,arbol->raiz);
	abb_nodo_t* izq=arbol->raiz->izq;
	
	while(izq){
		pila_apilar(iter->pila,izq);
		izq=izq->izq;
	}
	return iter;
}


bool abb_iter_in_avanzar(abb_iter_t *iter){
	
	if(abb_iter_in_al_final(iter)) return false;
	
	abb_nodo_t* actual=	pila_desapilar(iter->pila);
	if (actual->der) pila_apilar(iter->pila,actual->der);
	
	//abb_nodo_t *izq=iter->arbol->raiz->izq;
	abb_nodo_t* izq=actual->der->izq;
	
	while(izq){
		pila_apilar(iter->pila,izq);
		izq=izq->izq;
	}
	
	return true;
}


const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	return pila_ver_tope(iter->pila);
}


bool abb_iter_in_al_final(const abb_iter_t *iter){
	return pila_esta_vacia(iter->pila);
}


void abb_iter_in_destruir(abb_iter_t* iter){
	free(iter->pila);
	free(iter);
}



/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

void abb_iterar(abb_nodo_t* nodo, bool visitar(const char *, void *, void *), void *extra,bool continuar) {
	
	if(!nodo || !continuar) return;
	abb_iterar(nodo->izq, visitar, extra,continuar);
	continuar=visitar(nodo->clave, nodo->dato, extra);
	abb_iterar(nodo->der, visitar, extra,continuar);
}


void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
	
	bool continuar=true;
	abb_nodo_t *actual=arbol->raiz; 
	
	abb_iterar(actual,visitar,extra,continuar);
}


/*
//Funcion auxiliar que borra nodos que son hojas.
void borrar_hoja( abb_t *arbol, abb_nodo_t* padre, const char *clave){
	
	if(arbol->comparar_clave(clave, padre->clave)<0){
		padre->izq=NULL;
	} else if (arbol->comparar_clave(clave, padre->clave)>0){
		padre->der=NULL;
	}
}


//Funcion auxiliar que borra nodos que tienen 1 hijo.
void borrar_1_hijo( abb_t *arbol, abb_nodo_t* nodo,abb_nodo_t* padre,const char *clave){

	if(arbol->comparar_clave(clave, padre->clave)<0){
		padre->izq=NULL;
	} else if (arbol->comparar_clave(clave, padre->clave)>0){
		padre->der=NULL;
	}
	swap(arbol,padre,nodo);
}	


//Funcion auxiliar que borra nodos que tienen 2 hijos.
void borrar_2_hijos( abb_t *arbol,abb_nodo_t* nodo, const char *clave){

	abb_nodo_t* derecho=nodo->der;
	
	abb_nodo_t* padre_izq=derecho;
	abb_nodo_t* izq=derecho->izq;
	
	while(izq->izq){
		padre_izq=izq;
		izq=izq->izq;
	}
	swap(arbol,izq,nodo);
	padre_izq->izq=NULL;
}	


/////////////////////////7


//Funcion auxiliar que borra nodos que son hojas.
void borrar_hoja( abb_t *arbol, const char *clave){
	
	abb_nodo_t* padre= buscar_padre(arbol,arbol->raiz,clave);
	abb_nodo_t* nodo_a_borrar;
	
	if(arbol->comparar_clave(clave, padre->clave)<0){
		nodo_a_borrar=padre->izq;
		padre->izq=NULL;
	} else if (arbol->comparar_clave(clave, padre->clave)>0){
		nodo_a_borrar=padre->der;
		padre->der=NULL;
	}
	printf("atnes de destruir \n");
	destruir_nodo(arbol,nodo_a_borrar);
}


//Funcion auxiliar que borra nodos que tienen 1 hijo.
void borrar_1_hijo( abb_t *arbol, const char *clave){
	abb_nodo_t* padre= buscar_padre(arbol,arbol->raiz,clave);
	abb_nodo_t* nodo_a_borrar;
	
	if(arbol->comparar_clave(clave, padre->clave)<0){
		nodo_a_borrar=padre->izq;
		padre->izq=NULL;
	} else if (arbol->comparar_clave(clave, padre->clave)>0){
		nodo_a_borrar=padre->der;
		padre->der=NULL;
	}
	swap(arbol,padre,nodo_a_borrar);
	destruir_nodo(arbol,nodo_a_borrar);
}	


//Funcion auxiliar que borra nodos que tienen 2 hijos.
void borrar_2_hijos( abb_t *arbol, const char *clave){
	
	abb_nodo_t* nodo_a_borrar=buscar(arbol,arbol->raiz,clave);	
	abb_nodo_t* derecho=nodo_a_borrar->der;
	
	abb_nodo_t* padre_izq=derecho;
	abb_nodo_t* izq=derecho->izq;
	
	while(izq->izq){
		padre_izq=izq;
		izq=izq->izq;
	}
	swap(arbol,izq,nodo_a_borrar);
	destruir_nodo(arbol,izq);
	padre_izq->izq=NULL;
}	

*/

