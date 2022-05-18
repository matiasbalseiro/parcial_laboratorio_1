/*
 ============================================================================
 Name        : parcialJueves.c
 Author      : franco
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "censista.h"
#include "zona.h"
#include "direcciones.h"
#include "fechasDeNacimiento.h"

#define CANT_CENSISTAS 10
#define CANT_ZONAS 10
#define LEN_NOMBRE 51
#define CANT_CALLES 4
#define LEN_CALLES 51

int main(void) {
	setbuf(stdout, NULL);
	Censista censistas[CANT_CENSISTAS];
//	Fechasdenacimiento fechas[CANT_CENSISTAS];
//	Direcciones direcciones[CANT_CENSISTAS];
	Zona zonas[CANT_ZONAS];
//	int respuesta;
	int opcionMenu;
	int idCensista = 0;
	char nombre[LEN_NOMBRE];
	char apellido[LEN_NOMBRE];
	int dia = 0;
	int mes = 0;
	int anio = 0;
	int edad = 0;
	char calleCensista[LEN_NOMBRE];
	int altura = 0;
	int idZona = 0;
	char calleZona[CANT_CALLES][LEN_CALLES];
	int localidad = 0;

	initCensistas(censistas, CANT_CENSISTAS);
	initZonas(zonas, CANT_ZONAS);

	do {
		if (utn_getNumero(&opcionMenu,

				"\n*****************************MENU PRINCIPAL*****************************\n\n"
						"1. Carga censista: \n"
						"2. Modificar censista: \n"
						"3. Dar de baja censista: \n"
						"4. Cargar zona: \n"
						"5. Asignar zona a censar: \n"
						"6. Carga de datos: \n"
						"7. Mostrar censistas: \n"
						"8. Mostrar zonas: \n"
						"9. Carga forzada Censistas: \n"
						"10. Carga Forzada Zonas: \n"
						"11. SALIR\n"
						"\nElija una opcion: ",

				"\nError opcion invalida", 1, 11, 2) == 0) {

		}
		switch (opcionMenu) {
		case 1:
		if (utn_getNombre(nombre, LEN_NOMBRE, "\nIndique el nombre del censista: ", "\nERROR, ingrese un nombre valido.\n", 2) == 0) {
			if (utn_getNombre(apellido, LEN_NOMBRE, "\nIndique el apellido del censista: ", "\nERROR, ingrese un apellido valido.\n", 2) == 0) {
				if (utn_getNumero(&dia, "\nIndique dia de nacimiento. (1 - 31): ", "ERROR\n", 1, 31, 2) == 0) {
					if (utn_getNumero(&mes, "\nIndique mes de nacimiento. (1 - 12): ", "ERROR\n", 1, 31, 2) == 0) {
						if (utn_getNumero(&anio, "\nIndique anio de nacimiento. (1970 - 2004): ", "ERROR\n", 1970, 2004, 2) == 0) {
							if (utn_getNumero(&edad, "\nIndique edad. (18 - 52): ", "ERROR\n", 18, 52, 2) == 0) {
								if (utn_getNombre(calleCensista, LEN_NOMBRE, "\nIndique calle: ", "\nERROR, ingrese una calle valida.\n", 2) == 0) {
									if (utn_getNumero(&altura, "\nIndique altura del domicilio. (1 - 10000): ", "ERROR\n", 1, 10000, 2) == 0) {
										cargarCensista(censistas, CANT_CENSISTAS, idCensista, nombre, apellido, dia, mes, anio, edad, calleCensista, altura);
									}
								}
							}
						}
					}
				}
			}
		}

			break;
		case 2:
			if(hayCensistaCargado(censistas, CANT_CENSISTAS) == 1){
				modificarCensista(censistas, CANT_CENSISTAS, idCensista);
			} else {
				printf("\nERROR, primero debes cargar al menos un censista.\n");
			}
			break;
		case 3:

			if(hayCensistaCargado(censistas, CANT_CENSISTAS) == 1){
				removerCensista(censistas, CANT_CENSISTAS, idCensista);
			} else {
				printf("\nERROR, primero debes cargar al menos un censista.\n");
			}

			break;
		case 4:

			if (utn_getNombre(calleZona[0], LEN_CALLES, "\nIndique la primer calle: ", "\nERROR\n", 2) == 0) {
				if (utn_getNombre(calleZona[1], LEN_CALLES, "\nIndique la segunda calle: ", "\nERROR\n", 2) == 0) {
					if (utn_getNombre(calleZona[2], LEN_CALLES, "\nIndique la tercer calle: ", "\nERROR\n", 2) == 0) {
						if (utn_getNombre(calleZona[3], LEN_CALLES, "\nIndique la cuarta calle: ", "\nERROR\n", 2) == 0) {
							if (utn_getNumero(&localidad, "\nIndique localidad. (1 - 10): ", "ERROR\n", 1, 10, 2) == 0) {
								cargarZona(zonas, CANT_ZONAS, idZona, calleZona, localidad);
							}
						}
					}
				}
			}

			break;
		case 5:
			if((hayCensistaCargado(censistas, CANT_CENSISTAS) && hayZonaCargada(zonas, CANT_ZONAS))== 1){
				asignarZona(zonas, CANT_ZONAS, censistas);
			} else {
				printf("\nERROR, Debes cargar al menos un censista y una zona.\n");
			}

			break;
		case 6:

			break;
		case 7:
			mostrarCensistas(censistas, CANT_CENSISTAS);
			break;
		case 8:
			mostrarZonas(zonas, CANT_ZONAS);
			break;
		case 9:
			cargaForzadaCensista(censistas);
			break;
		case 10:
			cargaForzadaZona(zonas);
			break;
		case 11:
			printf("Adios.");
			break;
		}
	} while (opcionMenu != 11);

	return 0;
}


