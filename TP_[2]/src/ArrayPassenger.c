#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayPassenger.h"
#include "utn.h"

static const char TXT_TYPES[5][51] = {" ", "Primera", "Ejecutiva", "Premium", "Turista"};
static const char TXT_STATUS[3][51] = {" ","ACTIVO", "CANCELADO"};
static int increaseId();

/// @brief Incrementa el id
/// @return retorna el id del pasajero
static int increaseId(){
    static int id = 3000;
    id++;
    return id;
}

/// @brief  Para indicar que todas las posiciones del array están vacías, esta función pone la bandera
///         (isEmpty) en TRUE en todas las posiciones del array.
/// @param list Puntero al array de pasajeros
/// @param len Largo del array
/// @return Retorna (-1) si hay error [Largo invalido o puntero nulo] - (0) si esta Ok
int initPassengers(Passenger *list, int len) {

	int retorno;
	retorno = -1;

	if(list != NULL && len > 0){
		for(int i = 0; i < len; i++){
			list[i].isEmpty = 1;
		}
		retorno = 0;
	}
	return retorno;
}

/// @brief Agrega en un array de pasajeros existente los valores recibidos
///        como parámetro en la primer posición libre.
/// @param list Puntero al array de pasajeros
/// @param len Largo del array
/// @param id Id del pasajero
/// @param name Nombre del pasajero
/// @param lastName Apellido del pasajero
/// @param price Precio del pasaje
/// @param typePassenger Clase de vuelo
/// @param flycode Codigo de vuelo
/// @param statusFlight Estado de vuelo
/// @return Retorna (-1) si hay error [Largo invalido o puntero NULL o sin espacio libre] - (0) si es Ok
int addPassenger(Passenger *list, int len, int id, char name[], char lastName[], float price, int typePassenger, char flycode[], int statusFlight){
	int retorno;
	int indexLibre;
	retorno = -1;

	if(list != NULL && len > 0 && name != NULL && lastName != NULL && flycode != NULL){
			indexLibre = findIndexByIsEmpty(list, len);
			if(indexLibre != -1){
					strncpy(list[indexLibre].name, name, sizeof(list[indexLibre].name));
					strncpy(list[indexLibre].lastName, lastName, sizeof(list[indexLibre].lastName));
					list[indexLibre].price = price;
					list[indexLibre].typePassenger = typePassenger;
					strncpy(list[indexLibre].flycode, flycode, sizeof(list[indexLibre].flycode));
					list[indexLibre].statusFlight = statusFlight;
					list[indexLibre].id = increaseId();
					list[indexLibre].isEmpty = 0;
					retorno = 0;
					printHeader();
					printPassenger(list[indexLibre]);

					printf("\nCARGA EXITOSA. SE DIO DE ALTA AL PASAJERO\n");
		}
	}
	return retorno;
}

/// @brief Busca un pasajero recibiendo como parámetro de búsqueda su Id.
/// @param list Puntero al array de pasajeros
/// @param len Largo del array
/// @param id Id del pasajero
/// @return Retorna la posicion del indice del pasajero o (-1) si [Largo invalido o
///         puntero NULL o pasajero no encontrado]
int findPassengerById(Passenger *list, int len, int id) {
	int retorno;
	retorno = -1;

	if(list != NULL && len > 0 && id > 0 ){
				for(int i = 0; i < len; i++){
					if(list[i].id == id && list[i].isEmpty == 0){
						retorno = i;
						break;
					}
				}
			}
		return retorno;
	}

/// @brief Elimina de manera lógica (isEmpty Flag en 1) un pasajero recibiendo como parámetro su Id.
/// @param list Puntero al array de pasajeros
/// @param len Largo del array
/// @param id Id del pasajero
/// @return Retorna (-1) si hay error [Largo invalido o puntero NULL o si no
///         encontro al pasajero] - (0) si es Ok
int removePassenger(Passenger *list, int len, int id) {

	int retorno;
	retorno = -1;
	int index;
	int bufferId;

	if (list != NULL && len > 0) {
		printHeader();
		printPassengers(list, len);
			if(utn_getNumero(&bufferId, "\n\nIndique ID a dar de baja. \n", "ERROR\n", 3000, 7000, 2) == 0){
				id = bufferId;
		}
		index = findPassengerById(list, len, id);
		if (index != -1) {
			list[index].isEmpty = 1;
			printf("BAJA EXITOSA. SE HAN GUARDADO LOS CAMBIOS\n");
			retorno = 0;
		} else {
			printf("ERROR, no se ha encontrado pasajero asociado a ese ID.");
		}
	}
	return retorno;
}

/// @brief Modifica al pasajero por el id
/// @param list Puntero al array de pasajeros
/// @param len Largo del array
/// @param id id del pasajero
/// @return Retorna -1 si hay error
int modifyPassenger(Passenger *list, int len, int id){

	int retorno = -1;
	int index;
	int opcionMenu;
	int bufferId;
	char bufferName[LEN_NAME];
	char bufferLastName[LEN_NAME];
	float bufferPrice;
	int bufferTypePassenger;
	char bufferFlyCode[LEN_NAME];

	if (list != NULL && len > 0) {
		printHeader();
		printPassengers(list, len);
		if (utn_getNumero(&bufferId, "\nIndique ID a modificar. \n", "ERROR\n", 3000, 7000, 2) == 0) {
			id = bufferId;
		}
		index = findPassengerById(list, len, id);
		if (index != -1){
			printHeader();
			printPassenger(list[index]);
				do{
					if (utn_getNumero(&opcionMenu,

							"\n*****************************MENU MODIFICAR*****************************\n\n"
									"1. NOMBRE \n"
									"2. APELLIDO \n"
									"3. PRECIO\n"
									"4. TIPO DE PASAJERO\n"
									"5. CODIGO DE VUELO\n"
									"6. REGRESAR AL MENU PRINCIPAL\n"
									"\nElija una opcion: ",

							"\nError opcion invalida", 1, 6, 2) == 0) {
							switch(opcionMenu){
							case 1:
								if(utn_getNombre(bufferName,LEN_NAME,"\nIndique el nombre del pasajero: ","\nERROR, ingrese un nombre valido.\n",2) == 0){
									strncpy(list[index].name, bufferName, sizeof(list[index].name));
									printf("Modificacion realizada.");
								}
								break;
							case 2:
								if(utn_getNombre(bufferLastName,LEN_NAME,"\nIndique el apellido del pasajero: ","\nERROR, ingrese un apellido valido.\n",2) == 0){
									strncpy(list[index].lastName, bufferLastName, sizeof(list[index].lastName));
									printf("Modificacion realizada.");
								}
								break;
							case 3:
								if(utn_getNumeroFlotante(&bufferPrice, "\nIndique el precio del pasaje. ($0 - $3000000): $", "\nERROR, ingrese el precio dentro del rango establecido.\n", 0, 3000000, 2) == 0){
									list[index].price = bufferPrice;
									printf("Modificacion realizada.");
								}
								break;
							case 4:
								if(utn_getNumero(&bufferTypePassenger, "\n1: Primera clase.\n2: Clase ejecutiva.\n3: Clase premium.\n4: Clase turista.\n\nIndique clase de viaje: ", "ERROR, indique clase de viaje.", 1, 4, 2) == 0){
									list[index].typePassenger = bufferTypePassenger;
									printf("Modificacion realizada.");
								}
								break;
							case 5:
								if(utn_getDescripcion(bufferFlyCode, LEN_CODE,"Indique codigo de vuelo. (Hasta 9 caracteres): ", "ERROR, ingrese el codigo dentro del rango establecido.", 2) == 0){
									strncpy(list[index].flycode, bufferFlyCode, sizeof(list[index].flycode));
									printf("Modificacion realizada.");
									printHeader();
									printPassenger(list[index]);
								}
								break;
							case 6:
								printf("Regresando al menu principal...\n");
								retorno = 0;
								break;
							}
					}
				}while(opcionMenu != 6);
		} else {
			printf("ERROR, no se ha encontrado pasajero asociado a ese ID.");
		}
	}
	return retorno;
}

/// @brief Ordena el array de pasajeros por apellido y
///        tipo de pasajero de manera ascendente o descendente.
/// @param list Puntero al array de pasajeros
/// @param len Largo del array
/// @param order Orden ascendente o descendente
/// @return Retorna (-1) si hay error [Largo invalido o puntero NULL] - (0) si es Ok
int sortPassengers(Passenger *list, int len, int order) {

	Passenger bufferLastName;
	int bufferOrder;
	int retorno;
	int i;
	int isOrder;
	retorno = -1;

	if (list != NULL && len > 0) {
		if (utn_getNumero(&bufferOrder, "\n1: Orden ascendente (A - Z) \n2: Orden descendente (Z - A)\n\nIndique orden: ", "ERROR\n", 1, 2, 2) == 0) {
			order = bufferOrder;
			}

		do {
			isOrder = 1;
			len--;
			for (i = 0; i < len; i++) {
				if (order == 1) {
					if (stricmp(list[i].lastName, list[i + 1].lastName) > 0) {
						bufferLastName = list[i];
						list[i] = list[i + 1];
						list[i + 1] = bufferLastName;
						isOrder = 0;
					} else if (stricmp(list[i].lastName, list[i + 1].lastName) == 0 && list[i].typePassenger > list[i + 1].typePassenger) {
						bufferLastName = list[i];
						list[i] = list[i + 1];
						list[i + 1] = bufferLastName;
						isOrder = 0;
					}
				} else {
					if (stricmp(list[i].lastName, list[i + 1].lastName) < 0) {
						bufferLastName = list[i];
						list[i] = list[i + 1];
						list[i + 1] = bufferLastName;
						isOrder = 0;
					} else if (stricmp(list[i].lastName, list[i + 1].lastName) == 0 && list[i].typePassenger < list[i + 1].typePassenger) {
						bufferLastName = list[i];
						list[i] = list[i + 1];
						list[i + 1] = bufferLastName;
						isOrder = 0;
					}
				}
			}
		} while (isOrder == 0);
		retorno = 0;
	}
	return retorno;
}

/// @brief Imprime el array de pasajeros de forma encolumnada.
/// @param list Puntero al array de pasajeros
/// @param length Largo del array
/// @return Retorna (-1) si hay error [Largo invalido o puntero NULL] - (0) si es Ok
int printPassengers(Passenger *list, int length) {
	int retorno;
	retorno = -1;

	if(list != NULL && length > 0){
		for(int i = 0; i < length; i++){
			printPassenger(list[i]);
		}
		retorno = 0;
	}

return retorno;
}

/// @brief Ordena el array de pasajeros por código de vuelo y
///        estado de vuelo de manera ascendente o descendente.
/// @param list Puntero al array de pasajeros
/// @param len Largo del array
/// @param order [1] ascendente - [0] descendente
/// @return Retorna (-1) si hay error [Largo invalido o puntero NULL] - (0) si es Ok
int sortPassengersByCode(Passenger *list, int len, int order) {
	int retorno;
	retorno = -1;

	Passenger bufferFlyCode;
	int i;
	int bufferOrder;
	int isOrder;
	retorno = -1;

	if (list != NULL && len > 0){
		if (utn_getNumero(&bufferOrder, "\n1: Orden dascendente (1 - 9), (A - Z) \n2: Orden descendente (9 - 1), (Z - A)\n\nIndique orden: ", "ERROR\n", 1, 2, 2) == 0) {
			order = bufferOrder;
			}

		do {
			isOrder = 1;
			len--;
			for (i = 0; i < len; i++){
				if (order == 1){
					if (stricmp(list[i].flycode, list[i + 1].flycode) > 0){
						bufferFlyCode = list[i];
						list[i] = list[i + 1];
						list[i + 1] = bufferFlyCode;
						isOrder = 0;
					} else if (stricmp(list[i].flycode, list[i + 1].flycode) == 0 && list[i].statusFlight > list[i + 1].statusFlight){
						bufferFlyCode = list[i];
						list[i] = list[i + 1];
						list[i + 1] = bufferFlyCode;
						isOrder = 0;
					}
				}else{
					if (stricmp(list[i].flycode, list[i + 1].flycode) < 0){
						bufferFlyCode = list[i];
						list[i] = list[i + 1];
						list[i + 1] = bufferFlyCode;
						isOrder = 0;
					} else if (stricmp(list[i].flycode, list[i + 1].flycode) == 0 && list[i].statusFlight < list[i + 1].statusFlight){
						bufferFlyCode = list[i];
						list[i] = list[i + 1];
						list[i + 1] = bufferFlyCode;
						isOrder = 0;
					}
				}
			}
		}while (isOrder == 0);

		return retorno;
	}

return 0;
}

/// @brief Busca si hay un espacio libre para cargar un pasajero
/// @param list Puntero al array de pasajeros
/// @param len Array length
/// @return Retorna si hay un espacio vacio o (-1) si [Largo invalido o
///         puntero NULL]
int findIndexByIsEmpty(Passenger *list, int len){

	int retorno = -1;

	if (list != NULL && len > 0) {
		for (int i = 0; i < len; i++) {
			if (list[i].isEmpty == 1) {
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/// @brief Verifica si hay al menos un pasajero cargado
/// @param list Puntero al array de pasajeros
/// @param len Largo del array
/// @return Retorna 1 si hay al menos un pasajero cargado 0 si no
int aPassenger(Passenger *list, int len) {
	int retorno = 0;
	if (list != NULL && len > 0) {
		for (int i = 0; i < len; i++) {
			if (list[i].isEmpty == 0) {
				retorno = 1;
				break;
			}
		}
	}
	return retorno;
}

/// @brief Imprime el array de un solo pasajero de forma encolumnada
/// @param list Puntero al array de pasajeros
void printPassenger(Passenger list) {

	if(list.isEmpty == 0) {
		printf("|%*d|%*s|%*s|%*.2f|%*s|%*s|%*s|\n", -13, list.id, -13, list.name, -13, list.lastName, -13, list.price, -13, TXT_TYPES[list.typePassenger], -13, list.flycode, -13, TXT_STATUS[list.statusFlight]);
	}
}

/// @brief Muestra el encabezado del informe de pasajeros
void printHeader(){

	printf("\n|%*s|%*s|%*s|%*s|%*s|%*s|%*s|\n\n",-13,"ID",-13, "Nombre", -13, "Apellido", -13, "Precio", -13, "Clase", -13, "Codigo", -13, "Estado");
}


/// @brief Carga forzada de pasajeros
/// @param list Puntero al array de pasajeros
/// @return Retorna (-1) si hay error - (0) si es Ok
int forcedCharge(Passenger *list){
	int retorno = -1;
	int i;
	Passenger passengers[LEN_FORCED_CHARGE] = {{4001, "BART", "SIMPSON", 165000.50, "AR465D", 3, 1, 0},
												{4002, "MARGE", "BOUVIE", 156000.90, "BR156E", 2, 2, 0},
												{4003, "NELSON", "MUNTZ", 110000.00, "FR897G", 1, 1, 0},
												{4004, "PATTY", "SELMA", 320000.65, "CH847R", 3, 1, 0},
												{4005, "NED", "FLANDERS", 245000.00, "AR748R", 1, 2, 0}};

	if(list != NULL){
		for(i = 0; i < 5; i++){
			list[i] = passengers[i];
			list[i].isEmpty = 0;
			retorno = 0;
			printPassenger(list[i]);
		}
	}
	return retorno;
}

/// @brief Cuenta la cantidad de pasajeros cargados
/// @param list Puntero al array de pasajeros
/// @param len Largo del array
/// @return Retorna la cantidad de pasajeros
int countPassengers(Passenger *list, int len){

	int countPassenger;
	int i;
	countPassenger = 0;

	if(list != NULL && len > 0){
		for(i = 0; i < len; i++){
			if(list[i].isEmpty == 0){
				countPassenger++;
			}
		}
	}
	return countPassenger;
}

/// @brief Calcula el precio total de los pasajes
/// @param list Puntero al array de pasajeros
/// @param len Largo del array
/// @return Retorna el precio total de los pasajes
float totalPrice(Passenger *list, int len){

	float total;
	int i;

	total = 0;

	if(list != NULL && len > 0){
		for(i = 0; i < len; i++){
			if(list[i].isEmpty == 0){
				total += list[i].price;
			}
		}
	}
	return total;
}

/// @brief Calcula el promedio del precio de los pasajes
/// @param list Puntero al array de pasajeros
/// @param len Largo del array
/// @return Retorna el promedio de los pasajes
float averagePrice(Passenger *list, int len){

	float average;
	int quantityPassengers;
	float total;

	if(list != NULL && len > 0){
		total = totalPrice(list, len);
		quantityPassengers = countPassengers(list, len);

		average = total / quantityPassengers;
	}
	return average;
}

/// @brief Calcula cuantos pasajeros se excedieron del
///        promedio del precio de los pasajes
/// @param list Puntero al array de pasajeros
/// @param len Largo del array
/// @return Retorna la cantidad de pasajeros excedidos
int exceedAverage(Passenger *list, int len){

	int count;
	float promedio;
	int i;

	count = 0;

	promedio = averagePrice(list, len);

	if(list != NULL && len > 0){
		for(i = 0; i < len; i++){
			if(list[i].isEmpty == 0 && list[i].price > promedio){
				count++;
			}
		}
	}
	return count;
}

/// @brief Muestra el informe de los pasajeros
/// @param list Puntero al array de pasajeros
/// @param len Largo del array
/// @return Retorna el informe de los pasajeros
int reportPassenger(Passenger *list, int len){

	int retorno = -1;
	int opcionMenu;
	float totalPric;
	float averagePric;
	int exceedAverag;
	int order;
	order = 0;

	if (list != NULL && len > 0) {
				do{
					if (utn_getNumero(&opcionMenu,

							"\n*****************************MENU INFORMAR*****************************\n\n"
									"1. Listado de pasajeros por apellido y tipo de pasajero \n"
									"2. Total, promedio de precio de pasajes y cuantos pasajeros superan el promedio \n"
									"3. Listado de pasajeros por codigo de vuelo y estado de vuelo 'ACTIVO' \n"
									"4. Regresar al menu principal\n"

									"\nElija una opcion: ",

							"\ERROR, opcion invalida", 1, 4, 2) == 0) {
							switch(opcionMenu){
							case 1:

								sortPassengers(list, len, order);
								printHeader();
								printPassengers(list, len);

								break;
							case 2:
								totalPric = totalPrice(list, len);
								averagePric = averagePrice(list, len);
								exceedAverag = exceedAverage(list, len);

								printf("\nPrecio total de los pasajes: $%.2f\n", totalPric);
								printf("Promedio de precios de los pasajes: $%.2f\n", averagePric);
								printf("%d pasajeros superan el precio promedio.\n", exceedAverag);

								break;
							case 3:
								sortPassengersByCode(list, len, order);
								printHeader();
								printPassengers(list, len);
								break;
							case 4:
								printf("Regresando al menu principal...\n");
								retorno = 0;
								break;
							}
					}
				}while(opcionMenu != 4);
		} else {
			printf("ERROR, no se ha encontrado pasajero asociado a ese ID.");
		}
	return retorno;
}

