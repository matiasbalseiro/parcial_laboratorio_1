#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "ArrayPassenger.h"

#define MAX_PASSENGERS 2000
#define LENGH_NAME 51
#define LEN_FLYCODE 50

int main(void) {
	setbuf(stdout, NULL);

	Passenger pasajeros[MAX_PASSENGERS];
	int opcionMenu;
	int id;
	char bufferName[LENGH_NAME];
	char bufferLastName[LENGH_NAME];
	float bufferPrice;
	int bufferTypePassenger;
	char bufferFlyCode[LEN_FLYCODE];
	int bufferStatusFlight;

	id = 0;
	bufferPrice = 0;
	bufferTypePassenger = 0;
	bufferStatusFlight = 0;

	if(initPassengers(pasajeros, MAX_PASSENGERS) == 0){
		do{
			if (utn_getNumero(&opcionMenu,

					"\n*****************************MENU PRINCIPAL*****************************\n\n"
							"1. ALTA \n"
							"2. MODIFICAR \n"
							"3. BAJA\n"
							"4. INFORMAR\n"
							"5. ALTA FORZADA\n"
							"6. SALIR\n"
							"\nElija una opcion: ",

					"\nError opcion invalida", 1, 6, 2) == 0) {
					switch(opcionMenu){
					case 1:
					if (utn_getNombre(bufferName, LEN_NAME, "\nIndique el nombre del pasajero: ", "\nERROR, ingrese un nombre valido.\n", 2) == 0) {
						if (utn_getNombre(bufferLastName, LEN_NAME, "\nIndique el apellido del pasajero: ", "\nERROR, ingrese un apellido valido.\n", 2) == 0) {
							if (utn_getNumeroFlotante(&bufferPrice, "\nIndique el precio del pasaje. ($0 - $3000000): $", "ERROR\n", 0, 3000000, 2) == 0) {
								if (utn_getNumero(&bufferTypePassenger, "\n1: Primera clase.\n2: Clase ejecutiva.\n3: Clase premium.\n4: Clase turista.\n\nIndique clase de viaje: ", "ERROR\n", 1, 4, 2) == 0) {
									if (utn_getDescripcion(bufferFlyCode, LEN_CODE, "\nIndique codigo de vuelo. (Hasta 9 caracteres): ", "ERROR\n", 2) == 0) {
										if (utn_getNumero(&bufferStatusFlight, "\n1: ACTIVO.\n2: CANCELADO.\n\nIndique, estado de vuelo: ", "ERROR\n", 1, 2, 2) == 0) {
											addPassenger(pasajeros, MAX_PASSENGERS, id, bufferName, bufferLastName, bufferPrice, bufferTypePassenger, bufferFlyCode, bufferStatusFlight);
										}
									}
								}
							}
						}
					}
						break;
					case 2:
						if(aPassenger(pasajeros, MAX_PASSENGERS) == 1){
							modifyPassenger(pasajeros, MAX_PASSENGERS, id);
						} else {
							printf("\nERROR, primero debes cargar al menos un pasajero.\n");
						}

						break;

					case 3:
						if(aPassenger(pasajeros, MAX_PASSENGERS) == 1){
							removePassenger(pasajeros, MAX_PASSENGERS, id);
						} else {
							printf("\nERROR, primero debes cargar al menos un pasajero.\n");
						}

						break;
					case 4:
						if(aPassenger(pasajeros, MAX_PASSENGERS) == 1){
							reportPassenger(pasajeros, MAX_PASSENGERS);

						} else {
							printf("\nERROR, primero debes cargar al menos un pasajero.\n");
						}

						break;
					case 5:
						printHeader();
						forcedCharge(pasajeros);

						break;
					case 6:
						printf("\nAdios.");
						break;
					}
				}
			}while(opcionMenu != 6);
	}
	return 0;
}

