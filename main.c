#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base_struct.h"

const int SIZE = 150000;

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
    
    while (nodoActual != NULL) {
        //printf(get_city_t(nodoActual->item_n.city));
        printf("ciudad %s\n",city_names[nodoActual->item_n.city] );
        printf("Id: %d\n", nodoActual->id);
        nodoActual = nodoActual->siguiente;
    }
}




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
    }   
}

//////////////////////////////////////////////////////

/*
typedef struct {
    char ciudad[20];
    float ingresos;
    int edad;
} Persona;

void promedioIngresos(Persona personas[], int tam, int edadMinima, int edadMaxima) {
    float totalIngresos = 0.0;
    int numPersonas = 0;
    
    for (int i = 0; i < tam; i++) {
        if (personas[i].edad >= edadMinima && personas[i].edad <= edadMaxima) {
            totalIngresos += personas[i].ingresos;
            numPersonas++;
        }
    }

    if (numPersonas > 0) {
        float promedio = totalIngresos / numPersonas;
        printf("El promedio de ingresos para personas entre %d y %d años es: %.2f\n", edadMinima, edadMaxima, promedio);
    } else {
        printf("No se encontraron personas en el rango de edad especificado\n");
    }
}
*/
// la funcion para el array
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


////////////////////////////////////punto 3

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

    ///////////////////////// numero 1
    printf("Persona %d: %d años \n", items[1].id, items[1].age);
    printf("ciudad %s\n",city_names[items[1].city] );

	int num_elementos = sizeof(items) / sizeof(item_t);

    //printf("El numero de elementos en el array de personas es: %d\n", num_elementos);

    struct Nodo *lista = NULL;
    crearLista(items, num_elementos, &lista);
    //imprimirLista(lista);
    //personasPorCiudad(lista);
    //personasPorCiudad2(items,num_elementos);
    ///////////////////////////////////////////////////////////////


    ////////////////////////// pregunta 2
    //int n_personas = sizeof(personas) / sizeof(struct Persona);
    //num_elementos ya esta determinado en la linea 245
    int edad_min = 25;
    int edad_max = 40;
    const char* ciudad = "Dallas";
    //float promedio = promedio_ingresos_por_edad_ciudad(items, num_elementos, edad_min, edad_max, ciudad);
    float promedio = promedio_ingresos_por_edad_ciudad2(lista,  edad_min, edad_max, ciudad);
    printf("Promedio de ingresos en la ciudad %s para personas entre %d y %d años: %.2f\n", ciudad, edad_min, edad_max, promedio);
   ////////////////////////// pregunta 2

   //////pregunta 3///////////////
   
    int edad_limite = 60;

    //float prob = probabilidad_enfermedad(items, num_elementos, edad_limite);
    //printf("La probabilidad de estar enfermo si se es mayor de %d años es: %.7f\n", edad_limite, prob);
    float prob = probabilidad_enfermedad2(lista, edad_limite);
    printf("La probabilidad de estar enfermo si se es mayor de %d años es: %.7f\n", edad_limite, prob);
////////////////////////////////////////////


    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}


