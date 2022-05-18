/*
 * zona.c
 *
 *  Created on: 15 may. 2022
 *      Author: matia
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "zona.h"
#include "censista.h"

static int incrementarId();

/// @brief Incrementa el id
/// @return retorna el id del pasajero
static int incrementarId(){
    static int id = 400;
    id++;
    return id;
}

int initZonas(Zona *list, int len) {

	int retorno = -1;

	if(list != NULL && len > 0){
		for (int i = 0; i < len; i++) {
			list[i].isEmpty = 1;
		}
		retorno = 0;
	}

	return retorno;
}

int cargarZona(Zona *list, int len, int id, char calle[][51], int localidad){
	int retorno;
	int indexLibre;

	retorno = -1;

	if(list != NULL && len > 0 && calle != NULL){
			indexLibre = buscarIndexPorIsEmptyZona(list, len);
			if(indexLibre != -1){
					strncpy(list[indexLibre].calles[0], calle[0], sizeof(list[indexLibre].calles[0]));
					strncpy(list[indexLibre].calles[1], calle[1], sizeof(list[indexLibre].calles[1]));
					strncpy(list[indexLibre].calles[2], calle[2], sizeof(list[indexLibre].calles[2]));
					strncpy(list[indexLibre].calles[3], calle[3], sizeof(list[indexLibre].calles[3]));
					list[indexLibre].localidadZona = localidad;
					list[indexLibre].estado = 1; //PENDIENTE
					list[indexLibre].idZona = incrementarId();
					list[indexLibre].isEmpty = 0;
					retorno = 0;
					mostrarZona(list[indexLibre]);

					printf("\nSE HA DADO DE ALTA LA ZONA\n");
		}
	}
	return retorno;
}

int buscarIndexPorIsEmptyZona(Zona *list, int len){

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

int hayZonaCargada(Zona *list, int len) {
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

int asignarZona(Zona *zonas, int len, Censista *censistas){
	int retorno = -1;

	int bufferIdZona;
	int bufferIdCensista;
	int posicionDeZona;
	int flag = 0;

	if(zonas != NULL && len > 0 && censistas != NULL && len > 0){
		mostrarZonas(zonas, len);
		utn_getNumero(&bufferIdZona, "\n\nIndique ID de zona a censar. \n", "ERROR\n", 400, 500, 2);

		for(int i = 0; i < len; i++){
			if(zonas[i].isEmpty == 0 && zonas[i].estado == 1 && bufferIdZona == zonas[i].idZona){
				posicionDeZona = i;
				for(int j = 0; j < len; j++){
					if(censistas[j].isEmpty == 0 && censistas[j].estado == 1 && censistas[j].idZona == zonas[i].idZona){
						flag = 1;
						printf("Esta zona ya fue asignada.");
						break;
					}
				}
			}
		}
		if(flag == 0){
			mostrarCensistas(censistas, len);
			utn_getNumero(&bufferIdCensista, "\n\nIndique ID del censista para la zona. \n", "ERROR\n", 1000, 1300, 2);

			for(int i = 0; i < len; i++){
				if(censistas[i].isEmpty == 0 && censistas[i].estado == 3 && bufferIdCensista == censistas[i].idCensista){
					censistas[i].idZona = zonas[posicionDeZona].idZona;
					censistas[i].estado = 1;
					printf("Censista asignado ID:%d", censistas[i].idCensista);
				}
			}
			retorno = 0;
		}
	}

	return retorno;
}

//if(flag == 0){
//			for(int i = 0; i < len; i++){
//				if(censistas[i].estado == 3){
//					censistas[i].idZona = zonas[posicionDeZona].idZona;
//					censistas[i].estado = 1;
//					printf("Censista asignado.");
//				}
//			}
//		}
//		retorno = 0;


int mostrarZonas(Zona *list, int len) {
	int retorno;
	retorno = -1;

	if(list != NULL && len > 0){
		for(int i = 0; i < len; i++){
			mostrarZona(list[i]);
		}
		retorno = 0;
	}

return retorno;
}
void mostrarZona(Zona list){

	char ESTADO[3][51] = {" ", "PENDIENTE", "FINALIZADO"};

	if(list.isEmpty == 0) {
		printf("ID: %d - CALLE 1: %s - CALLE 2: %s - CALLE 3: %s - CALLE 4: %s - LOCALIDAD: %d - ESTADO: %s\n",
				list.idZona, list.calles[0], list.calles[1], list.calles[2], list.calles[3], list.localidadZona, ESTADO[list.estado]);
	}
}

int cargaForzadaZona(Zona *list){
	int retorno = -1;
	int i;
	printf("\nINFORMAR ZONA/S\n\n");

	Zona zonas[LEN_CARGA_ZONA] = {{400,{"POSADAS","PICO","CAXARAVILLE", "CAMPICHUELO"}, 1, 2, 0},
								{402,{"algo","algo2","algo3", "algo4"}, 1, 2, 0},
								{403,{"EEEEE","MARADONA","EL ", "DIEEEO"}, 1, 2, 0},
								{404,{"MESSI","HACE","UN", "GOL"}, 1, 2, 0},
								{405,{"DDDD","algAAo2","aEEEE3", "aWWWW4"}, 1, 2, 0}};




	if(list != NULL){
		for(i = 0; i < LEN_CARGA_ZONA; i++){
			list[i] = zonas[i];
			list[i].isEmpty = 0;
			retorno = 0;
			mostrarZona(list[i]);
		}
	}
	return retorno;
}
