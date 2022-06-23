
#ifndef PASSENGER_H_
#define PASSENGER_H_


typedef struct
{
	int id;
	char nombre[50];
	char apellido[50];
	float precio;
	int tipoPasajero;
	char codigoVuelo[10];
	int estadoVuelo;
}Passenger;

Passenger* Passenger_new();
Passenger* Passenger_newParametros(char *idStr, char *nombreStr, char *apellidoStr, char *precioStr, char *codigoVueloStr, char *tipoPasajeroStr, char *estadoVueloStr);

void Passenger_delete();
void Passenger_deleteAll(LinkedList* pArrayListPassenger);

int Passenger_setId(Passenger* this,int id);
int Passenger_getId(Passenger* this,int* id);

int Passenger_setNombre(Passenger* this,char* nombre);
int Passenger_getNombre(Passenger* this,char* nombre);

int Passenger_setApellido(Passenger* this,char* apellido);
int Passenger_getApellido(Passenger* this,char* apellido);

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo);
int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo);

int Passenger_setTipoPasajero(Passenger* this, int tipoPasajero);
int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero);

int Passenger_setPrecio(Passenger* this,float precio);
int Passenger_getPrecio(Passenger* this,float* precio);

int Passenger_setEstadoVuelo(Passenger* this,int estadoVuelo);
int Passenger_getEstadoVuelo(Passenger* this,int* estadoVuelo);

int Passenger_setAll(Passenger* this,int id, char* nombre, char* apellido, char* codigoVuelo, int tipoPasajero, float precio, int estadoVuelo);
int Passenger_getAll(Passenger* this,int* id, char* nombre, char* apellido, char* codigoVuelo, int* tipoPasajero, float* precio, int* estadoVuelo);

int Passenger_lastId(LinkedList* pArrayListPassenger);

int Passenger_printPassenger(LinkedList* pArrayListPassenger, int index);
void printHeader();

int Passenger_edit(LinkedList* pArrayListPassenger);
int Passenger_sort(LinkedList* pArrayListPassenger);

int Passenger_sortById(void* primerPasajero, void* segundoPasajero);
int Passenger_sortByName(void* primerPasajero, void* segundoPasajero);
int Passenger_sortByLastName(void* primerPasajero, void* segundoPasajero);
int Passenger_sortByPrice(void* primerPasajero, void* segundoPasajero);
int Passenger_sortFlyCode(void* primerPasajero, void* segundoPasajero);
int Passenger_sortTypePassenger(void* primerPasajero, void* segundoPasajero);
int Passenger_sortStatusFlight(void* primerPasajero, void* segundoPasajero);

int Passenger_traductorTipoPasajeroChar(char* tipoPasajero);
int Passenger_traductorEstadoVueloChar(char* estadoVuelo);

#endif /* PASSENGER_H_ */

