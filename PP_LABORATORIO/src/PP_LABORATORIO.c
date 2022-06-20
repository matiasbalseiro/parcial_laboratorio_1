/*
 ============================================================================
 Name        : PP_LABORATORIO.c
 Author      : matias
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "menu.h"
#include "censista.h"
#include "zona.h"
#include "direcciones.h"
#include "fechasDeNacimiento.h"
#include "cargaDatos.h"

#define CANT_CENSISTAS 10
#define CANT_ZONAS 10
#define LEN_NOMBRE 51
#define CANT_CALLES 4
#define LEN_CALLES 51

int main(void) {
	setbuf(stdout, NULL);
	Censista censistas[CANT_CENSISTAS];
	Zona zonas[CANT_ZONAS];
	int opcion;
	int idCensista = 0;
	char nombre[LEN_NOMBRE];
	char apellido[LEN_NOMBRE];
	int dia = 0;
	int mes = 0;
	int anio = 0;
	int edad = 0;
	char calleCensista[LEN_CALLES];
	int altura = 0;
	int idZona = 0;
	char calleZona[CANT_CALLES][LEN_CALLES];
	int localidad = 0;
	int bufferInSitu = 0;
	int bufferVirtual = 0;
	int bufferAusentes = 0;

	initCensistas(censistas, CANT_CENSISTAS);
	initZonas(zonas, CANT_ZONAS);

	do {
		opcion = menuPrincipal();

		switch (opcion) {
		case 1:
			cargaDatosCensista(censistas, CANT_CENSISTAS, nombre, apellido, &dia, &mes, &anio, &edad, calleCensista, &altura);
			cargarCensista(censistas, CANT_CENSISTAS, idCensista, nombre, apellido, dia, mes, anio, edad, calleCensista, altura);
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
			cargaDatosZona(zonas, CANT_ZONAS, calleZona, &localidad);
			cargarZona(zonas, CANT_ZONAS, idZona, calleZona, localidad);
			break;
		case 5:
			if((hayCensistaCargado(censistas, CANT_CENSISTAS) && hayZonaCargada(zonas, CANT_ZONAS))== 1){
				asignarZona(zonas, CANT_ZONAS, censistas);
			} else {
				printf("\nERROR, Debes cargar al menos un censista y una zona.\n");
			}
			break;
		case 6:
			if((hayCensistaCargado(censistas, CANT_CENSISTAS) && hayZonaCargada(zonas, CANT_ZONAS))== 1){
					cargarDatos(zonas, bufferInSitu, bufferVirtual, bufferAusentes, CANT_ZONAS, censistas);

			} else {
				printf("\nERROR, Debes cargar al menos un censista y una zona.\n");
			}
			break;
		case 7:
			mostrarCensistas(censistas, CANT_CENSISTAS);
			break;
		case 8:
			mostrarZonasDatos(zonas, censistas, CANT_ZONAS);
			break;
		case 9:
			cargaForzadaCensista(censistas);
			break;
		case 10:
			cargaForzadaZona(zonas);
			break;
		case 11:
			printf("Adios.");
			//modificarZona(zonas, CANT_CENSISTAS_ZONAS, bufferId);
			//removerZona(zonas, censistas, CANT_CENSISTAS);
			break;
		/*case 12:

			break;
		case 13:
			printf("Adios.");
			break;*/
		}
	} while (opcion != 11);

	return 0;
}



