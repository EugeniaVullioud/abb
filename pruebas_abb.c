#include "abb.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXIMO 200

//Funciones auxiliares del abb.

//Funcion auxiliar que destruye el dato. 
void destruir_dato(void* dato){
	free(dato);
}	

//Funcion auxiliar que compara claves.
int comparar_clave(const char *clave1, const char *clave2){
	return strcmp(clave1,clave2);
}

//Funcion auxiliar visitar.
bool visitar(const char *clave, void* dato, void* extra){
	
	if (*(size_t*)extra>=3){
		return false;
	}
	
	printf("%s\n",clave);
	printf("%d\n",*(int*)dato);
	*(size_t*)extra +=1;
	return true;
}


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/


/*prueba que se pueda crear el abb y que luego se pueda eliminar el abb. */
void prueba_crear_y_destruir_abb(){
	
	printf("INICIO DE PRUEBA DE CREACION Y ELIMINACION DE ABB\n");

    /* Declaro las variables a utilizar*/
	abb_t *abb_1= abb_crear(comparar_clave,NULL);
	const char *clave="papas con cheddar";
	
	/* Inicio de pruebas. */
    print_test("se creo el abb" , abb_1 != NULL);
    
    /* Pruebo que obtener la raiz de una abb vacio devuelve NULL. */
    print_test("el abb esta vacio", abb_obtener(abb_1,clave)==NULL);
   
	/* Pruebo que la cantidad de elementos de un abb vacio es 0. */
	print_test("la cantidad de elementos de un abb es 0", abb_cantidad(abb_1)==0);
 
	/* Pruebo que ver si una clave pertenece a un abb vacio es falso. */
    print_test("obtener la raiz de una abb vacio es falso", abb_pertenece(abb_1,clave)==false);
   
    /* Pruebo que no puedo quitar elementos de abbs vacios. */
	print_test("no se puede eliminar elementos en una abb vacio", abb_borrar(abb_1,clave)==NULL);
	
	/* Pruebo que que se puede destruir el abb sin la funcion de destruccion de los elementos. */
	abb_destruir(abb_1);
	print_test("abb destruido correctamente", true);
}


/*prueba que se pueda insertar y eliminar correctamente un elemento. */
void prueba_insertar_y_eliminar_1_elemento(){
	
	printf("INICIO DE PRUEBA DE INSERTAR Y ELIMINAR UN ELEMENTO\n");

    /* Declaro las variables a utilizar*/
	abb_t *abb_1= abb_crear(comparar_clave,NULL);
	
	char *clave="papas con cheddar";
	
	//int d=90;
	//void* dato=&d;
	char* dato="pasta";
	
	/* Inicio de pruebas. */
	
    print_test("agregar elemento al abb", abb_guardar(abb_1,clave,dato));
	
	/* Pruebo que el elemento insertado es el mismo que la raiz en el abb. */
	print_test("obtener la raiz del abb", abb_obtener(abb_1,clave)== dato);
	
	/* Pruebo que el la clave esta en el abb. */
    print_test("la clave pertenece al abb", abb_pertenece(abb_1,clave));
    
    /* Pruebo que la cantidad de elementos de un abb vacio no es 0. */
	print_test("la cantidad de elementos de un abb es 1", abb_cantidad(abb_1)==1);
    
	/* Pruebo que el elemento eliminado es el mismo que la raiz en el abb y que puedo eliminar la raiz. */
	print_test("eliminar la raiz del abb", abb_borrar(abb_1,clave)==dato);

	/* Pruebo que el elemento ya no esta en el abb. */
    print_test("el abb esta vacio", abb_obtener(abb_1,clave)==NULL);
   
	/* Pruebo que la cantidad de elementos de un abb vacio es 0. */
	print_test("la cantidad de elementos de un abb es 0", abb_cantidad(abb_1)==0);
 
	/* Pruebo que ver si la clave pertenece al abb luego de borrarla es falso. */
    print_test("obtener la clave borrada de una abb es falso", !abb_pertenece(abb_1,clave));

	/* Destruyo el abb. */
	abb_destruir(abb_1);
	print_test("abb destruido correctamente", true);

}


/*prueba que se pueda insertar y eliminar correctamente el elemento NULL. */
void prueba_insertar_y_eliminar_NULL(){
	
	printf("INICIO DE PRUEBA DE INSERCION Y ELIMINACION DEL ELEMENTO NULL\n");
	
    /* Declaro las variables a utilizar*/
	abb_t *abb_1= abb_crear(comparar_clave,NULL);
	
	char* nulo=NULL;
	int a=1;
	int *pa=&a;

	
	/* Inicio de pruebas. */
    print_test("insertar NULL en el abb", abb_guardar(abb_1,nulo,pa)==true);
	
	/* Pruebo que la clave esta en el abb. */
    print_test("la clave pertenece al abb", abb_pertenece(abb_1,nulo)==true);
        
    /* Pruebo que puedo obtener los datos en el abb. */
	print_test("obtener el dato1 del abb", abb_obtener(abb_1,nulo)==pa);

    /* Pruebo que la cantidad de elementos de un abb vacio no es 0. */
	print_test("la cantidad de elementos de un abb es 1", abb_cantidad(abb_1)==1);

	/* Pruebo que el elemento eliminado es el mismo que la raiz en el abb. */
	print_test("eliminar el elemento del abb", abb_borrar(abb_1,nulo)==pa);

	/* Pruebo que la clave esta en el abb. */
    print_test("la clave ya no pertenece al abb", abb_pertenece(abb_1,nulo)==false);
        
    /* Pruebo que puedo obtener los datos en el abb. */
	print_test("obtener el dato1 del abb ya no es posible", abb_obtener(abb_1,nulo)==NULL);
	
	/* Pruebo que la cantidad de elementos de un abb vacio es 0. */
	print_test("la cantidad de elementos de un abb es 0", abb_cantidad(abb_1)==0);
    
	/* Destruyo el abb. */
	abb_destruir(abb_1);
	print_test("abb destruido correctamente", true);

}


/*prueba que se pueda insertar y eliminar correctamente muchos elementos guardados en el stack, mantienendo el invariante. */
void prueba_insertar_y_eliminar_varios_elementos_memoria_estatica(){

	printf("INICIO DE PRUEBAS CON VARIOS ELEMENTOS GUARDADOS CON MEMORIA ESTATICA\n");

    /* Declaro las variables a utilizar*/

	abb_t *abb_1=abb_crear(comparar_clave,NULL);
	
	int v1=30;
	int* valor_1=&v1;
	
	int v2=90;
	int* valor_2=&v2;
	
	int v3=20;
	int* valor_3=&v3;
	
	int v4=05;
	int* valor_4=&v4;
	
	int v5=3;
	int* valor_5=&v5;
	
	int v6=1;
	int* valor_6=&v6;
	
	char *clave_1="30";
	char *clave_2="90";
	char *clave_3="20";
	char *clave_4="5";
	char *clave_5="3";
	char *clave_6="1";
	
	
	/* Inicio de pruebas. */
	printf("BORRADO DE UNA HOJA\n");
	
	print_test("agregar elemento_1 en el abb", abb_guardar(abb_1,clave_1,valor_1)==true);
	print_test("agregar elemento_2 en el abb", abb_guardar(abb_1,clave_2,valor_2)==true);
	
	/* Pruebo que el las claves estan en el abb. */
    print_test("la clave1 pertenece al abb", abb_pertenece(abb_1,clave_1));
    print_test("la clave2 pertenece al abb", abb_pertenece(abb_1,clave_2));
    
    /* Pruebo que puedo obtener los datos en el abb. */
	print_test("obtener el dato1 del abb", abb_obtener(abb_1,clave_1)==valor_1);
	print_test("obtener el dato2 del abb", abb_obtener(abb_1,clave_2)==valor_2);
	
    /* Pruebo que la cantidad de elementos de un abb vacio no es 0. */
	print_test("la cantidad de elementos del abb es 2", abb_cantidad(abb_1)==2);
    
    /* Pruebo que el elemento eliminado es el mismo que el que inserte en el abb y que puedo eliminar hojas. */
	print_test("eliminar una hoja del abb", abb_borrar(abb_1,clave_2)==valor_2);
	
	/* Pruebo que la cantidad de elementos de un abb vacio no es 0. */
	print_test("la cantidad de elementos del abb es 1", abb_cantidad(abb_1)==1);
	
	printf("fin prueba de borrado de hojas \n \n");
   
	printf("BORRADO DE UN NODO CON UN HIJO\n");
    
    /* Pruebo que me permita agregar elementos luego de haber eliminado. */  
    print_test("insertar elemento_3 en el abb", abb_guardar(abb_1,clave_3,valor_3));
	print_test("insertar elemento_4 en el abb", abb_guardar(abb_1,clave_4,valor_4));
	
    /* Pruebo que la cantidad de elementos de un abb vacio no es 0. */
	print_test("la cantidad de elementos del abb es 3", abb_cantidad(abb_1)==3);
    
    /* Pruebo que puedo eliminar un nodo que tenga un hijo. */
	print_test("eliminar un nodo con un hijo del abb", abb_borrar(abb_1,clave_3)==valor_3);
	
	/* Pruebo que el la clave no esta en el abb. */
    print_test("la clave no pertenece al abb", abb_pertenece(abb_1,clave_3)==false);
    
    /* Pruebo que el hijo esta en el abb. */
    print_test("el hijo del nodo borrado pertenece al abb", abb_pertenece(abb_1,clave_4)==true);
	
	/* Pruebo que puedo obtener los datos en el abb. */
	print_test("obtener el dato del hijo del nodo borrado del abb", abb_obtener(abb_1,clave_4)==valor_4);
	
	/* Pruebo que la cantidad de elementos de un abb vacio no es 0. */
	print_test("la cantidad de elementos del abb es 2", abb_cantidad(abb_1)==2);
	
	printf("fin prueba de borrado de nodos con un hijo \n \n");
	
	printf("BORRADO DE UN NODO CON DOS HIJOS\n");
	
	/* Pruebo que puedo insertar luego de borrar un nodo que tenia un hijo. */
	print_test("agregar elemento_3 en el abb", abb_guardar(abb_1,clave_3,valor_3)==true);
	
	/* Pruebo que las claves estan en el abb. */
    print_test("la clave1 pertenece al abb", abb_pertenece(abb_1,clave_1)==true);
    print_test("la clave4 pertenece al abb", abb_pertenece(abb_1,clave_4)==true);
    print_test("la clave3 pertenece al abb", abb_pertenece(abb_1,clave_3)==true);
    
	/* Pruebo que la cantidad de elementos de un abb vacio no es 0. */
	print_test("la cantidad de elementos del abb es 3", abb_cantidad(abb_1)==3);
    
    /* Pruebo que puedo seguir insertando. */
    print_test("agregar elemento_5 en el abb", abb_guardar(abb_1,clave_5,valor_5)==true);
    print_test("agregar elemento_6 en el abb", abb_guardar(abb_1,clave_6,valor_6)==true);
    print_test("agregar elemento_2 en el abb", abb_guardar(abb_1,clave_2,valor_2)==true);
    
    /* Pruebo que la cantidad de elementos de un abb vacio no es 0. */
	print_test("la cantidad de elementos del abb es 6", abb_cantidad(abb_1)==6);
	
	/* Pruebo que puedo eliminar un nodo que tenga un hijo. */
	print_test("eliminar un nodo con dos hijos del abb", abb_borrar(abb_1,clave_4)==valor_4);
	
	/* Pruebo que el la clave no esta en el abb. */
    print_test("la clave no pertenece al abb", abb_pertenece(abb_1,clave_4)==false);
	
	/* Pruebo que no puedo obtener los datos del nodo borrado en el abb. */
	print_test("obtener el dato del nodo borrado del abb es NULL", abb_obtener(abb_1,clave_4)==NULL);
	
	/* Pruebo que la cantidad de elementos de un abb vacio no es 0. */
	print_test("la cantidad de elementos del abb es 5", abb_cantidad(abb_1)==5);
	
	printf("fin prueba de borrado de nodos con dos hijos \n \n");
	
	/* Pruebo que puedo seguir borrando. */
	print_test("eliminar un nodo con un hijo del abb", abb_borrar(abb_1,clave_3)==valor_3);
	print_test("eliminar un nodo con un hijo del abb", abb_borrar(abb_1,clave_5)==valor_5);
	print_test("eliminar una hoja del abb", abb_borrar(abb_1,clave_2)==valor_2);
	print_test("eliminar una hoja del abb", abb_borrar(abb_1,clave_6)==valor_6);
	print_test("eliminar la raiz del abb", abb_borrar(abb_1,clave_1)==valor_1);
	
	/* Pruebo que se respeta el CASO BORDE: el abb se comporta como si recien fuera creado. */
	
	/* Pruebo que obtener la raiz de una abb vacio devuelve NULL. */
    print_test("el abb esta vacio", abb_obtener(abb_1,clave_1)==NULL);
   
	/* Pruebo que la cantidad de elementos de un abb vacio es 0. */
	print_test("la cantidad de elementos de un abb es 0", abb_cantidad(abb_1)==0);
 
	/* Pruebo que ver si una clave pertenece a un abb vacio es falso. */
    print_test("obtener la raiz de una abb vacio es falso", abb_pertenece(abb_1,clave_1)==false);
   
    /* Pruebo que no puedo quitar elementos de abbs vacios. */
	print_test("no se puede eliminar elementos en una abb vacio", abb_borrar(abb_1,clave_1)==NULL);
	
	/* Pruebo que que se puede destruir el abb sin la funcion de destruccion de los elementos. */
	abb_destruir(abb_1);
	print_test("abb destruido correctamente", true);
	
}


/*prueba que se pueda insertar y eliminar correctamente muchos elementos guardados en memoria dinamica, mantienendo el invariante. */
void prueba_insertar_y_eliminar_varios_elementos_memoria_dinamica(){
	
	printf("INICIO DE PRUEBAS CON VARIOS ELEMENTOS GUARDADOS CON MEMORIA DINAMICA\n");

    /* Declaro las variables a utilizar*/

	abb_t *abb_1=abb_crear(comparar_clave,destruir_dato);	
	
	
	int* entero_1=malloc(sizeof(int));
	int* entero_2=malloc(sizeof(int));

	*entero_1=1;
	*entero_2=100;

	char *clave_1="clave_1";
	char *clave_2="clave_2";
	
	/* Inicio de pruebas. */

	/* Pruebo que me permita insertar elementos pedidos con memoria dinamica. */ 
	print_test("guardar elemento dinamico en el abb", abb_guardar(abb_1,clave_1,entero_1)==true);
	print_test("guardar elemento dinamico en el abb", abb_guardar(abb_1,clave_2,entero_2)==true);
		
	/* Pruebo que el las claves estan en el abb. */
    print_test("la clave1 pertenece al abb", abb_pertenece(abb_1,clave_1)==true);
    print_test("la clave2 pertenece al abb", abb_pertenece(abb_1,clave_2)==true);
    
    /* Pruebo que puedo obtener los datos en el abb. */
	print_test("obtener el dato1 del abb", abb_obtener(abb_1,clave_1)==entero_1);
	print_test("obtener el dato2 del abb", abb_obtener(abb_1,clave_2)==entero_2);

    /* Pruebo que la cantidad de elementos de un abb vacio no es 0. */
	print_test("la cantidad de elementos del abb es 2", abb_cantidad(abb_1)==2);

	/* Destruyo el abb. */
	abb_destruir(abb_1);
	print_test("abb con elementos dinamicos ha sido destruido correctamente", true);
	
}


/*Prueba que funcione bien para grandes cantidades de datos. */
void prueba_de_volumen(){
	
	printf("INICIO DE PRUEBA DE VOLUMEN\n");
	
	/* Declaro las variables a utilizar*/
	abb_t *abb_1= abb_crear(comparar_clave,destruir_dato);
	
	/* Inicio de pruebas. */
	//const char* claves[MAXIMO];
	int* valores[MAXIMO];
    bool ok = true;
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(MAXIMO*largo_clave);


    for(int i = 0; i < MAXIMO; i++){
		valores[i] = malloc(sizeof(int));
		*claves[i]=(char)i;
		*valores[i] = i;
        ok = abb_guardar(abb_1,claves[i], valores[i]);
        if (!ok) break;
    }

    print_test("Prueba agregar en volumen.", ok);
	
	/* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < MAXIMO; i++) {
        ok = abb_pertenece(abb_1, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb_1, claves[i]) == valores[i];
        if (!ok) break;
    }

    print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb_1) == MAXIMO);
	
	bool seguir = true;
	for(int i = 0; i < MAXIMO; i++){
        
        /* Pruebo que el elemento eliminado es el primero que encole. */
        seguir=abb_borrar(abb_1,claves[i])==valores[i];
        if (!seguir) break;
        
    }
	
	print_test("Prueba eliminar en volumen.", seguir);

	/* Pruebo que se respeta el CASO BORDE: el abb se comporta como si recien fuera creado. */
	
	/* Pruebo que obtener la raiz de una abb vacio devuelve NULL. */
    print_test("el abb esta vacio", abb_obtener(abb_1,claves[0])==NULL);
   
	/* Pruebo que la cantidad de elementos de un abb vacio es 0. */
	print_test("la cantidad de elementos de un abb es 0", abb_cantidad(abb_1)==0);
 
	/* Pruebo que ver si una clave pertenece a un abb vacio es falso. */
    print_test("obtener la raiz de una abb vacio es falso", abb_pertenece(abb_1,claves[0])==false);
   
    /* Pruebo que no puedo quitar elementos de abbs vacios. */
	print_test("no se puede eliminar elementos en una abb vacio", abb_borrar(abb_1,claves[0])==NULL);
	
	/* Pruebo que que se puede destruir el abb sin la funcion de destruccion de los elementos. */
	abb_destruir(abb_1);
	print_test("abb destruido correctamente", true);
	
	free(claves);
}




/* ******************************************************************
 *                   PRUEBAS DEL ITERADOR EXTERNO
 * *****************************************************************/


/*prueba que se pueda recorrer correctamente el abb con recorrido inorder, mantienendo el invariante, con el iterador externo. */
void prueba_iterador_externo(){

	printf("INICIO DE PRUEBAS DE ITERADOR EXTERNO INORDER\n");

    /* Declaro las variables a utilizar*/

	abb_t *abb_1= abb_crear(comparar_clave,NULL);
	
	int v1=30;
	int* valor_1=&v1;
	
	int v2=90;
	int* valor_2=&v2;
	
	int v3=20;
	int* valor_3=&v3;
	
	int v4=35;
	int* valor_4=&v4;
	
	char *clave_1="c1";
	char *clave_2="c2";
	char *clave_3="c3";
	char *clave_4="c4";
	
	
	print_test("agregar elemento_1 en el abb", abb_guardar(abb_1,clave_3,valor_3)==true);
	print_test("agregar elemento_2 en el abb", abb_guardar(abb_1,clave_2,valor_2)==true);
	print_test("agregar elemento_3 en el abb", abb_guardar(abb_1,clave_1,valor_1)==true);
	print_test("agregar elemento_4 en el abb", abb_guardar(abb_1,clave_4,valor_4)==true);
	
	abb_iter_t *iterador= abb_iter_in_crear(abb_1);
	
	
	/* Inicio de pruebas. */

	/* Pruebo que el largo de una abb no es 0. */
	print_test("la cantidad de nodos es 4", abb_cantidad(abb_1)==4);
		
	/* Pruebo que la raiz en el abb corresponde al elemento al que apunta el iterador. */
	print_test("el actual del abb es el elemento mas a la izquierda", abb_iter_in_ver_actual(iterador)==clave_1);
	
	/* Avanzo el iterador. */
	print_test("avanzo el iterador", abb_iter_in_avanzar(iterador)==true);
	
	/* Pruebo que el ultimo elemento en el abb corresponde al elemento al que apunta el iterador. */
	print_test("obtener el actual del abb", abb_iter_in_ver_actual(iterador)==clave_1);
	
	/* Pruebo que el largo de una abb no es 0. */
	print_test("la cantidad de nodos es 4", abb_cantidad(abb_1)==4);
	
	/* Avanzo el iterador. */
	print_test("avanzo el iterador", abb_iter_in_avanzar(iterador)==true);
	print_test("obtener el actual del abb", abb_iter_in_ver_actual(iterador)==clave_4);
	print_test("avanzo el iterador", abb_iter_in_avanzar(iterador)==true);
	print_test("obtener el actual del abb", abb_iter_in_ver_actual(iterador)==clave_2);
	print_test("avanzo el iterador", abb_iter_in_avanzar(iterador)==true);
		print_test("obtener el actual del abb", abb_iter_in_ver_actual(iterador)==clave_2);
	print_test("avanzo el iterador", abb_iter_in_avanzar(iterador)==true);
   
    /* Pruebo que no puedo avanzar el iterador. */
	print_test("no puedo avanzar el iterador", abb_iter_in_avanzar(iterador)==false);
    
    /* Pruebo que el iterador esta al final del abb. */
    print_test("iterador esta en el final del abb", abb_iter_in_al_final(iterador)==true);
    
    /* Pruebo que el largo de una abb no es 0. */
	print_test("la cantidad de nodos es 4", abb_cantidad(abb_1)==4);
	
	/* Destruyo el iterador del abb. */
	abb_iter_in_destruir(iterador);
	print_test("iterador destruido correctamente", true);

	
}



/* ******************************************************************
 *                   PRUEBAS DEL ITERADOR INTERNO
 * *****************************************************************/


/*prueba que se pueda insertar y eliminar un elemento correctamente con el iterador interno. */
void prueba_iterador_interno(){

	printf("\nINICIO DE PRUEBA DE IMPRIMIR CON UN ITERADOR INTERNO\n");

    /* Declaro las variables a utilizar*/
	abb_t *abb_1= abb_crear(comparar_clave,NULL);
	
	size_t aux=0;
	
	int v1=30;
	int* valor_1=&v1;
	
	int v2=20;
	int* valor_2=&v2;
	
	int v3=35;
	int* valor_3=&v3;
	
	
	char *c1="clave_1";
	char *c2="clave_2";
	char *c3="clave_3";
	

	/* Inicio de pruebas. */
	
	abb_guardar(abb_1,c1,valor_1);
	abb_guardar(abb_1,c2,valor_2);
	abb_guardar(abb_1,c3,valor_3);
	
	/* Pruebo que se impriman los datos. */
	printf("Impresion de los datos de los nodos\n");
	abb_in_order(abb_1, visitar, &aux);
	
	/* Chequeo la condicion de corte. */
	print_test("auxiliar tiene que ser 3",aux==3);
	
	/* Destruyo el abb. */
	abb_destruir(abb_1);
	print_test("abb destruido correctamente", true);
	
	
	printf("\nINICIO PROBAR CON EL ITERADOR EXTERNO\n");
	
	abb_t *abb_2= abb_crear(comparar_clave,NULL);
	abb_iter_t *iterador=abb_iter_in_crear(abb_2);
	print_test("iterador", iterador);
	
	size_t aux2=0;
	print_test("insertar elemento_1 en el abb", abb_guardar(abb_1,c1,valor_1));
	print_test("insertar elemento_2 en el abb", abb_guardar(abb_1,c2,valor_2));
	print_test("insertar elemento_3 en el abb", abb_guardar(abb_1,c3,valor_3));

	printf("Impresion de los datos de los nodos\n");
	abb_in_order(abb_2, visitar, &aux2);
	
	/* Destruyo el iterador del abb. */
	abb_iter_in_destruir(iterador);
	print_test("iterador destruido correctamente", true);
	
	/* Destruyo el abb. */
	abb_destruir(abb_2);
	print_test("abb destruido correctamente", true);
}



void pruebas_abb_alumno(void){
	
	//pruebas del abb.
	
	printf("\nINICIO DE PRUEBA del abb\n");
	//prueba_crear_y_destruir_abb(); //FUNCIONA
	//prueba_insertar_y_eliminar_1_elemento();
	//prueba_insertar_y_eliminar_NULL();
	//prueba_insertar_y_eliminar_varios_elementos_memoria_estatica();
	//prueba_insertar_y_eliminar_varios_elementos_memoria_dinamica(); //FUNCIONA
	//prueba_de_volumen();
	
	//pruebas del iterador externo.
	printf("\nINICIO DE PRUEBA DEL ITERADOR EXTERNO\n");
	prueba_iterador_externo();
	
	//pruebas del iterador interno.
	printf("\nINICIO DE PRUEBA DEL ITERADOR INTERNO\n");
	//prueba_iterador_interno();
	
}




