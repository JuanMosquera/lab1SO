#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base_struct.h"
#include <time.h>

const int SIZE = 150000;
FILE *archivo;// archivo

//////////////////////////////////////////////////////
/*define una structura tipo nodo */
struct Nodo {
    
    int id;
    item_t item_n;
    struct Nodo *siguiente;
};

/*crea el nodo tipo structura para agregar a la lista */
struct Nodo* crearNodo(int id, item_t itemnodo) {
    struct Nodo *nuevoNodo = (struct Nodo*) malloc(sizeof(struct Nodo));
    
    nuevoNodo->id=id;
    nuevoNodo->item_n=itemnodo;  
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

/*crea la lista  de nodos en base al array de elementos*/
void crearLista(item_t *nodos, int tam, struct Nodo **lista) {
    *lista = NULL;  // Inicializar la lista ligada a NULL
    struct Nodo *nodoActual = NULL;
    
    
    for (int i = 0; i < tam; i++) {
        struct Nodo *nuevoNodo = crearNodo(nodos[i].id, nodos[i]);
        
        if (*lista == NULL) {  // Si la lista está vacía
            *lista = nuevoNodo;
            nodoActual = *lista;
        } else {
            nodoActual->siguiente = nuevoNodo;
            nodoActual = nodoActual->siguiente;
        }
    }
}

void imprimirLista(struct Nodo *lista) {
    struct Nodo *nodoActual = lista;
    int  cont=0;

    while (nodoActual != NULL) {
        //printf(get_city_t(nodoActual->item_n.city));
        //printf("ciudad %s\n",city_names[nodoActual->item_n.city] );
        printf("Id: %d\n", nodoActual->id);
        cont++;
        nodoActual = nodoActual->siguiente;
    }
    printf("%d",cont);
}

////////////////////////////////////////////////////////////////// punto 1


int numeroPersonas(struct Nodo* cabeza,char ciudad[] ) {
    int contador = 0;
    while (cabeza != NULL) {
        if (strcmp(city_names[cabeza->item_n.city], ciudad) == 0) {
            contador++;
        }
        cabeza = cabeza->siguiente;
    }
    return contador;
}

void personasPorCiudad(struct Nodo *lista) {
    struct Nodo *nodoActual = lista;
    const int tamano = sizeof(city_names) / sizeof(city_names[0]);
    int habitantes=0;
    char nCiudad[20];

    for (int i = 0; i < tamano; i++) {
        printf("%s ", city_names[i]);
        strcpy(nCiudad,city_names[i]);
        habitantes = numeroPersonas(nodoActual,nCiudad);
        printf("habitantes   %d \n ", habitantes);
        if (archivo != NULL) { // Verificar si se abrió el archivo correctamente
                    fprintf(archivo,"%s ", city_names[i]);
                    fprintf(archivo,"habitantes   %d \n ", habitantes);
                    
            }
    }   
}

/*cuenta el numero de personas en el array de element*/
int numeroPersonas2(item_t *nodos1,int tam1,char ciudad[] ) {
    int contador = 0;
    
    for (int i = 0; i < tam1; i++) {
        
        if (strcmp(city_names[nodos1[i].city], ciudad) == 0) {
            contador++;
        }
        
    }
    return contador;
}
/*cuanta el numero de personar en una ciudad en el array de element*/
void personasPorCiudad2(item_t *nodos, int tam) {
    
    const int tamano = sizeof(city_names) / sizeof(city_names[0]);
    int habitantes=0;
    char nCiudad[20];

    for (int i = 0; i < tamano; i++) {
        printf("%s ", city_names[i]);
        strcpy(nCiudad,city_names[i]);
        habitantes = numeroPersonas2(nodos,tam,nCiudad);
        printf("habitantes   %d \n ", habitantes);
        if (archivo != NULL) { // Verificar si se abrió el archivo correctamente
                    fprintf(archivo,"%s ", city_names[i]);
                    fprintf(archivo,"habitantes   %d \n ", habitantes);
                    
            }
    }   
}

////////////////////////////////////////////////////// punto 2

float promedio_ingresos_por_edad_ciudad(item_t *personas, int n, int edad_min, int edad_max, const char* ciudad) {
    float total_ingresos = 0.0;
    int n_personas = 0;
    for (int i = 0; i < n; i++) {
        if (personas[i].age >= edad_min && personas[i].age <= edad_max && strcmp(city_names[personas[i].city], ciudad) == 0) {
            total_ingresos += personas[i].income;
            n_personas++;
        }
    }
    if (n_personas > 0) {
        return total_ingresos / n_personas;
    } else {
        return 0.0;
    }
}
// la funcion para lista
float promedio_ingresos_por_edad_ciudad2(struct Nodo *lista,  int edad_min, int edad_max, const char* ciudad) {
    struct Nodo *nodoActual = lista;
    float total_ingresos = 0.0;
    int n_personas = 0;

    while (nodoActual != NULL) {
        if (nodoActual->item_n.age >= edad_min && nodoActual->item_n.age <= edad_max && strcmp(city_names[nodoActual->item_n.city], ciudad) == 0) {
            total_ingresos += nodoActual->item_n.income;
            n_personas++;
        }

        nodoActual = nodoActual->siguiente;
    }   

    if (n_personas > 0) {
        return total_ingresos / n_personas;
    } else {
        return 0.0;
    }
}

////////////////////////////////////////////////////
//punto 3


float probabilidad_enfermedad(item_t *personas, int tam, int edad_limite) {
    int contador_mayores = 0;
    int contador_enfermos = 0;
    const char* enfermedad = "Yes";

    for (int i = 0; i < tam; i++) {
        if (personas[i].age > edad_limite) {
            contador_mayores++;
            if (strcmp(illness_values[personas[i].illness], enfermedad) == 0) {
                contador_enfermos++;
            }
        }
    }

    if (contador_mayores == 0) {
        return 0.0;
    }

    return (float) contador_enfermos / contador_mayores;
}


float probabilidad_enfermedad2(struct Nodo *lista, int edad_limite) {
    struct Nodo *nodoActual = lista;
    int contador_mayores = 0;
    int contador_enfermos = 0;
    const char* enfermedad = "Yes";

    while (nodoActual != NULL) {
        if (nodoActual->item_n.age> edad_limite) {
            contador_mayores++;
            if (strcmp(illness_values[nodoActual->item_n.illness], enfermedad) == 0) {
                contador_enfermos++;
            }
        }

        nodoActual = nodoActual->siguiente;
    } 

    if (contador_mayores == 0) {
        return 0.0;
    }

    return (float) contador_enfermos / contador_mayores;
}


////////////////////////////////////punto 4

void buscar_persona_por_id(item_t *personas, int tam, int id_buscado) {
    int i;
    for (i = 0; i < tam; i++) {
        if (personas[i].id == id_buscado-1) {
            printf("Informacion de la persona con ID %d:\n", personas[i].id);
            printf("Ciudad: %s\n", city_names[personas[i].city]);
            printf("Genero: %s\n", gender_names[personas[i].gender]);
            printf("Edad: %d\n", personas[i].age);
            printf("Ingresos: %.d\n", personas[i].income);
            printf("Efermedad: %s\n", illness_values[personas[i].illness]);
            if (archivo != NULL) { // Verificar si se abrió el archivo correctamente
                    fprintf(archivo,"Informacion de la persona con ID %d:\n", personas[i].id);
                    fprintf(archivo,"Ciudad: %s\n", city_names[personas[i].city]);
                    fprintf(archivo,"Genero: %s\n", gender_names[personas[i].gender]);
                    fprintf(archivo,"Edad: %d\n", personas[i].age);
                    fprintf(archivo,"Ingresos: %.d\n", personas[i].income);
                    fprintf(archivo,"Efermedad: %s\n", illness_values[personas[i].illness]);
            }
            return;
        }
    }
    printf("No se encontro una persona con el ID %d\n", id_buscado);
}

void buscar_persona_por_id2( struct Nodo *lista , int id_buscado) {
    struct Nodo *nodoActual = lista;

    while (nodoActual != NULL) {
        if (nodoActual->item_n.id == id_buscado-1) {
            printf("Informacion de la persona con ID %d:\n", nodoActual->item_n.id);
            printf("Ciudad: %s\n", city_names[nodoActual->item_n.city]);
            printf("Genero: %s\n", gender_names[nodoActual->item_n.gender]);
            printf("Edad: %d\n", nodoActual->item_n.age);
            printf("Ingresos: %.d\n", nodoActual->item_n.income);
            printf("Efermedad: %s\n", illness_values[nodoActual->item_n.illness]);
            if (archivo != NULL) { // Verificar si se abrió el archivo correctamente
                    fprintf(archivo,"Informacion de la persona con ID %d:\n", nodoActual->item_n.id);
                    fprintf(archivo,"Ciudad: %s\n", city_names[nodoActual->item_n.city]);
                    fprintf(archivo,"Genero: %s\n", gender_names[nodoActual->item_n.gender]);
                    fprintf(archivo,"Edad: %d\n", nodoActual->item_n.age);
                    fprintf(archivo,"Ingresos: %.d\n", nodoActual->item_n.income);
                    fprintf(archivo,"Efermedad: %s\n", illness_values[nodoActual->item_n.illness]);
            }
            return;
        }
        
    nodoActual = nodoActual->siguiente;
    } 
    printf("No se encontro una persona con el ID %d\n", id_buscado);
}

//////////////////////punto 5/////////

void insertar_despues(struct Nodo *lista, int posicion, item_t nod) {
    struct Nodo *nodoActual = lista;
    struct Nodo *nuevo_nodo = crearNodo(posicion, nod);

   // while (nodoActual->id < dir) {
    for (int i = 0; i < posicion; i++) { 
        nodoActual = nodoActual->siguiente;
    }
    
    nuevo_nodo->siguiente = nodoActual->siguiente; // inserta el nuevo nodo
    nodoActual->siguiente = nuevo_nodo;

    while (nodoActual != NULL) {
        
        nodoActual->id = (nodoActual->id)+1;
        nodoActual = nodoActual->siguiente;
    }

}
    
    
    /*// libera la memoria de la lista
    Nodo* actual = cabeza;
    while (actual != NULL) {
        Nodo* temp = actual;
        actual = actual->siguiente;
        free(temp);
    */
    

    
int numeroPersonasedad3(struct Nodo* cabeza,char ciudad[],int edad1 ) {
    int contador = 0;
    while (cabeza != NULL) {
        if ((strcmp(city_names[cabeza->item_n.city], ciudad) == 0) &&  cabeza->item_n.age==edad1){
            contador++;
        }
        cabeza = cabeza->siguiente;
    }
    return contador;
}

void personasPorCiudadedad3(struct Nodo *lista, int edad) {
    struct Nodo *nodoActual = lista;
    const int tamano = sizeof(city_names) / sizeof(city_names[0]);
    int habitantes=0;
    char nCiudad[20];

    for (int i = 0; i < tamano; i++) {
        printf("%s ", city_names[i]);
        strcpy(nCiudad,city_names[i]);
        habitantes = numeroPersonasedad3(nodoActual,nCiudad, edad);
        printf("habitantes   %d \n ", habitantes);
        if (archivo != NULL) { // Verificar si se abrió el archivo correctamente
                    fprintf(archivo,"%s ", city_names[i]);
                    fprintf(archivo, "habitantes   %d \n ", habitantes);
        }
    }   
}

/*cuenta el numero de personas en el array de element*/
int numeroPersonasedad(item_t *nodos1,int tam1,char ciudad[],int edad1 ) {
    int contador = 0;
    
    for (int i = 0; i < tam1; i++) {
        
        if ((strcmp(city_names[nodos1[i].city], ciudad) == 0)&& nodos1[i].age==edad1) {
            contador++;
        }
        
    }
    return contador;
}
/*cuanta el numero de personar en una ciudad en el array de element*/
void personasPorCiudadedad(item_t *nodos, int tam, int edad) {
    
    const int tamano = sizeof(city_names) / sizeof(city_names[0]);
    int habitantes=0;
    char nCiudad[20];

    for (int i = 0; i < tamano; i++) {
        printf("%s ", city_names[i]);
        strcpy(nCiudad,city_names[i]);
        habitantes = numeroPersonasedad(nodos,tam,nCiudad,edad);
        printf("habitantes   %d \n ", habitantes);
        if (archivo != NULL) { // Verificar si se abrió el archivo correctamente
                    fprintf(archivo,"%s ", city_names[i]);
                    fprintf(archivo, "habitantes   %d \n ", habitantes);
        }
    }   
}
/*
void guardar_resultados(float resultado1) {
                FILE *archivo;// crear la variable por fuera 
                archivo = fopen("resultados.txt", "w"); // Abrir archivo en modo escritura en f7
                
                if (archivo != NULL) { // Verificar si se abrió el archivo correctamente
                    fprintf(archivo, "Resultado 1: %.2f\n", resultado1);
                    
                    fclose(archivo); // Cerrar archivo en el f 7
                    printf("Los resultados se han guardado en el archivo 'resultados.txt'.\n");
                } else {
                    printf("No se pudo abrir el archivo 'resultados.txt'.\n");
                }
            }
*/


//////////////////////////MAIN//////////////////////
int main(int argc, char *argv[]){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    item_t element;
    int line_number = 0;

    item_t items[SIZE];
    while ((read = getline(&line, &len, fp)) != -1) {
   	if(line_number > 0){
		char *token;
		char *s = NULL;
   		int i=0;
   		while ((token = strtok_r(line , ",", &line))) {
       			city_t result_city;
			gender_t result_gender;
			bool_t result_illness;
			switch(i){
				case 0:
					element.id = atoi(token);
					break;
				case 1:
					result_city = get_city_t(token);
					if(result_city == E)
						printf("City not defined\n");
					element.city = result_city;
					break;
				case 2:
					result_gender = get_gender_t(token);
					if(result_gender == NO)
						printf("Gender not defined\n");
					element.gender = result_gender;
					break;
				case 3:
					element.age = atoi(token);
					break;
				case 4:
					element.income = atoi(token);
					break;
				case 5:
					s = token;
                                        while(*s != '\n') {
                                                ++s;
                                        }
                                        *s = '\0';
					result_illness = get_illness_t(token);
					if(result_illness == fuzzy)
						printf("Value not defined\n");
					element.illness = result_illness;
					break;
			}
			i++;
    		}
		items[line_number - 1] = element;
    	}
	line = NULL;
	line_number++;
    }

    
    
	int num_elementos = sizeof(items) / sizeof(item_t);
    struct Nodo *lista = NULL;// creacion de lista vacia
    crearLista(items, num_elementos, &lista);
    /*forma de ejecutar el codigo 
        se compila 
        gcc -c main.c -o main.o
        gcc -c base_struct.c -o base_struct.o
        gcc base_struct.o main.o -o program
        ./program toy_dataset.csv
 */

    clock_t inicio, fin;
    double tiempo_total;
    char opcion[10];
    char opcion_int[10];
    int numeroCiudad = 0;
    char ciudad[10];// if si es null
    int an =0;
    int id_buscado =0;
    float prob = 0;
    int edad_limite = 0;
    float promedio = 0;
    int edad_max = 0;
    int edad_min = 0;
    
    while (strcmp(opcion, "salir") != 0) {
        printf("Seleccione una opcion:\n");
        printf("Opcion 1 cantidad de personas por cada ciudad.\n");
        printf("Opcion 2 el promedio de ingresos de las personas que viven en la misma ciudad.\n");
        printf("Opcion 3 la probabilidad de estar enfermo a cierta edad\n");
        printf("Opcion 4 recuperar un elemento a partir de su id \n");
        printf("Opcion 5 insertar un nuevo elemento en la mitad de los datos, utilice el id\n");
        printf("Opcion 6 cantidad de personas que viven en cada ciudad y que además tienen X años.\n");
        printf("Opcion 7 archivo de salida con los resultados de la invocación de las funciones.\n");
        printf(" Salir\n\n");
        
        printf("Opcion seleccionada: ");
        scanf("%s", opcion);
        
        if (strcmp(opcion, "1") == 0) {////////////////////////////
            printf("\n");


            printf("***ejecutado con la lista***\n");
            inicio = clock();
            personasPorCiudad(lista);
            fin = clock();
            tiempo_total = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
            printf("El tiempo de ejecución fue de %.4f segundos.\n", tiempo_total);
            printf("\n");
            printf("\n");


            printf("***ejecutado con arreglo***\n");
            inicio = clock();
            personasPorCiudad2(items,num_elementos);
            fin = clock();
            tiempo_total = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
            printf("El tiempo de ejecución fue de %.4f segundos.\n", tiempo_total);
            printf("\n");

        } else if (strcmp(opcion, "2") == 0) {////////////////////////////
            printf("\n");
            printf("Seleccionaste la opcion 2\n");
            printf("ingresar la ciudad 1.Dallas, 2.New York City, 3.Los Angeles, 4.Mountain View, 5.Boston, 6.Washington D.C., 7.San Diego, 8.Austin : \n");
            printf("\ningresar el numero de la ciudad: ");
            scanf("%s", opcion_int);
            numeroCiudad = atoi(opcion_int);
            
            strcpy(ciudad,city_names[numeroCiudad-1]);
            printf("ingresar la edad minima: ");
            scanf("%s", opcion_int);
            edad_min = atoi(opcion_int);
            
            printf("ingresar la edad maxima: ");
            scanf("%s", opcion_int);
            edad_max = atoi(opcion_int);
            printf("\n");
            

            inicio = clock();
            promedio = promedio_ingresos_por_edad_ciudad(items, num_elementos, edad_min, edad_max, ciudad);
            printf("Promedio de ingresos en la ciudad %s para personas entre %d y %d años: %.2f  array\n", ciudad, edad_min, edad_max, promedio);
            fin = clock();
            
            tiempo_total = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
            printf("El tiempo de ejecución fue de %.4f segundos.\n\n", tiempo_total);
            

            inicio = clock();
            promedio = promedio_ingresos_por_edad_ciudad2(lista,  edad_min, edad_max, ciudad);
            printf("Promedio de ingresos en la ciudad %s para personas entre %d y %d años: %.2f lista\n", ciudad, edad_min, edad_max, promedio);
            fin = clock();
            
            tiempo_total = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
            printf("El tiempo de ejecución fue de %.4f segundos.\n", tiempo_total);
            printf("\n");
            printf("\n");

        } else if (strcmp(opcion, "3") == 0) {////////////////////////////
            printf("\n");
            printf("Seleccionaste la opcion 3\n");
            printf("ingresar la edad: ");
            scanf("%s", opcion_int);
            edad_limite = atoi(opcion_int);
            

            inicio = clock();
            prob = probabilidad_enfermedad(items, num_elementos, edad_limite);
            printf("La probabilidad de estar enfermo si se es mayor de %d años es: %.7f  array\n", edad_limite, prob);
            fin = clock();
            
            tiempo_total = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
            printf("El tiempo de ejecución fue de %.4f segundos.\n", tiempo_total);
            

            inicio = clock();
            prob = probabilidad_enfermedad2(lista, edad_limite);
            printf("La probabilidad de estar enfermo si se es mayor de %d años es: %.7f\n  lista", edad_limite, prob);
            fin = clock();
            
            tiempo_total = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
            printf("El tiempo de ejecución fue de %.4f segundos.\n", tiempo_total);
            printf("\n");
            printf("\n");

        } else if (strcmp(opcion, "4") == 0) {////////////////////////////
            printf("\n");
            printf("Seleccionaste la opcion 4.\n");
            printf("ingrese el id a buscar: ");
            scanf("%s", opcion_int);
            id_buscado = atoi(opcion_int);
            printf("\n");

            inicio = clock();
            buscar_persona_por_id(items, num_elementos, id_buscado);
            fin = clock();
            tiempo_total = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
            printf("El tiempo de ejecución fue de %.4f segundos. array \n ", tiempo_total);
            printf("\n");

            inicio = clock();
            buscar_persona_por_id2(lista, id_buscado);
            fin = clock();
            tiempo_total = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
            printf("El tiempo de ejecución fue de %.4f segundos. lista\n  ", tiempo_total);
            printf("\n");   
            printf("\n");

        } else if (strcmp(opcion, "5") == 0) {////////////////////////////
            printf("\n");
            printf("Seleccionaste la opcion 5.\n");
            

            inicio = clock();
            item_t nuevo_element;
            nuevo_element.id=75000;
            nuevo_element.city=items[100].city;
            nuevo_element.age=items[1000].age;
            nuevo_element.gender=items[20000].gender;
            nuevo_element.income=items[40000].income;
            nuevo_element.illness=items[60000].illness;
    
            insertar_despues(lista, 75000,nuevo_element);
            fin = clock();
            tiempo_total = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
            printf("El tiempo de ejecución fue de %.4f segundos.\n", tiempo_total);
            
            //imprimirLista(lista);
            printf("\n");

        } else if (strcmp(opcion, "6") == 0) {////////////////////////////
            printf("\n");
            printf("Seleccionaste la opcion 6.\n");
            printf("ingresar la edad: ");
            scanf("%s", opcion_int);
            an = atoi(opcion_int);

            inicio = clock();
            printf("\n\nEjecucion con el arreglo\n");
            personasPorCiudadedad3(lista, an);
            fin = clock();
            tiempo_total = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
            printf("El tiempo de ejecución fue de %.4f segundos.\n", tiempo_total);
            
            inicio = clock();
            printf("\n\nEjecucion con la lista\n");
            personasPorCiudadedad(items,num_elementos, an);
            fin = clock();
            tiempo_total = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
            printf("El tiempo de ejecución fue de %.4f segundos.\n", tiempo_total);
            printf("\n");
            printf("\n");

        } else if (strcmp(opcion, "7") == 0) {////////////////////////////
            printf("\n");
            printf("\n");
            printf("Seleccionaste la opcion 7.\n");


            archivo = fopen("resultados.txt", "w"); // Abrir archivo en modo escritura en f7

            personasPorCiudad(lista);
            personasPorCiudad2(items,num_elementos);

            if(ciudad!= NULL){
                promedio = promedio_ingresos_por_edad_ciudad(items, num_elementos, edad_min, edad_max, ciudad);
                if (archivo != NULL) { // Verificar si se abrió el archivo correctamente
                    fprintf(archivo,"Promedio de ingresos en la ciudad %s para personas entre %d y %d años: %.2f \n", ciudad, edad_min, edad_max, promedio);
                    
            }
                promedio = promedio_ingresos_por_edad_ciudad2(lista,  edad_min, edad_max, ciudad);
                if (archivo != NULL) { // Verificar si se abrió el archivo correctamente
                    fprintf(archivo,"Promedio de ingresos en la ciudad %s para personas entre %d y %d años: %.2f \n", ciudad, edad_min, edad_max, promedio);
                    
            }
            }
           
            prob = probabilidad_enfermedad(items, num_elementos, edad_limite);
            if (archivo != NULL) { // Verificar si se abrió el archivo correctamente
                    fprintf(archivo, "La probabilidad de estar enfermo si se es mayor de %d años es: %.7f\n ", edad_limite, prob);
                    
            }
            prob = probabilidad_enfermedad2(lista, edad_limite);
            if (archivo != NULL) { // Verificar si se abrió el archivo correctamente
                    fprintf(archivo, "La probabilidad de estar enfermo si se es mayor de %d años es: %.7f\n ", edad_limite, prob);
                    
            }

            buscar_persona_por_id(items, num_elementos, id_buscado);
            buscar_persona_por_id2(lista, id_buscado);

            personasPorCiudadedad3(lista, an);
            personasPorCiudadedad(items,num_elementos, an);
            

            fclose(archivo); // Cerrar archivo en el f 7
            printf("Los resultados se han guardado en el archivo 'resultados.txt'.\n");

        
        } else if (strcmp(opcion, "salir") == 0) {////////////////////////////
            printf("Saliendo del programa...\n");
        } else {
            printf("Opcion invalida. Intente de nuevo.\n");
        }
    }
    
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}


