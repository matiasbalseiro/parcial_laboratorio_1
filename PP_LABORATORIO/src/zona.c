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

static char estado[3][51] = {" ", "PENDIENTE", "FINALIZADO"};
static char localidad[11][51] = {" ", "V.DOMINICO", "V.CORINA", "GERLI", "CHINGOLO", "V.OBRERA", "SOLANO", "BERNAL", "AVELLANEDA", "LANUS", "QUILMES"};

static int incrementarId();

/// @brief Incrementa el id
/// @return retorna el id
static int incrementarId(){
    static int id = 400;
    id++;
    return id;
}

/// @brief Indica que todas las posiciones del array estan vacias
///
/// @param list Puntero al array
/// @param len Largo del array
/// @return Retorna (-1) si hay error - (0) si no
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

/// @brief Agrega en un array de zonas existentes los valores recibidos
/// 	   como parametro en la primera posicion libre
/// @param list Puntero al array
/// @param len Largo del array
/// @param id Id de la zona
/// @param calle Array de calles
/// @param localidad Localidad de la zona
/// @return Retorna (-1) si hay error - (0) si no
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
					list[indexLibre].estado = PENDIENTE;
					list[indexLibre].idZona = incrementarId();
					list[indexLibre].isEmpty = 0;
					retorno = 0;
					mostrarZona(list[indexLibre]);

					printf("\nSE HA DADO DE ALTA LA ZONA\n");
		}
	}
	return retorno;
}

/// @brief Busca si hay un espacio libre para cargar una zona
///
/// @param list Puntero al array
/// @param len Largo del array
/// @return Retorna si hay un espacio vacio o (-1) si no
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

/// @brief Verifica si hay al menos una zona cargada
///
/// @param list Puntero al array
/// @param len Largo del array
/// @return Retorna (0) si hay error - (1) si no
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
/// @brief
///
/// @param zonas Puntero al array
/// @param len Largo del array
/// @param censistas Puntero al array
/// @return Retorna (-1) si hay error - (0) si no
int asignarZona(Zona *zonas, int len, Censista *censistas){
	int retorno = -1;

	int bufferIdZona;
	int bufferIdCensista;
	int posicionDeZona;
	int flagCensista = 0;

	if(zonas != NULL && censistas != NULL && len > 0){
		mostrarZonasPendientes(zonas, len);
		utn_getNumero(&bufferIdZona, "\n\nIndique ID de zona a censar. \n", "ERROR\n", 400, 500, 2);

		for(int i = 0; i < len; i++){
			if(bufferIdZona == zonas[i].idZona && zonas[i].estado == PENDIENTE){
				posicionDeZona = i;
				for(int j = 0; j < len; j++){
					if(censistas[j].estado == ACTIVO && censistas[j].idZona == zonas[i].idZona){
						printf("Este zona ya fue asignada");
						flagCensista = 1;
						retorno = 0;
						break;
					}
				}
			}
		}
	}
		if(flagCensista == 0){
				mostrarCensistasPendientes(censistas, len);
				utn_getNumero(&bufferIdCensista, "\n\nIndique ID del censista para la zona. \n", "ERROR\n", 1000, 1300, 2);
				for(int i = 0; i < len; i++){
				if(bufferIdCensista == censistas[i].idCensista && censistas[i].estado == LIBERADO){
					censistas[i].idZona = zonas[posicionDeZona].idZona;
					censistas[i].estado = ACTIVO;
					printf("Censista asignado ID: %d a la zona ID: %d\n", censistas[i].idCensista, zonas[posicionDeZona].idZona);
					retorno = 0;
					break;
				} else {
					printf("ERROR, no se puede asignar ese censista.");
					break;
				}
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


/// @brief
///
/// @param zonas Puntero al array
/// @param inSitu Cargados in situ
/// @param virtual Cargados virtualmente
/// @param ausentes Ausentes
/// @param len Largo del array
/// @param censistas Puntero al array
/// @return Retorna (-1) si hay error - (0) si no
int cargarDatos(Zona *zonas,int inSitu, int virtual, int ausentes, int len, Censista *censistas){

	int retorno = -1;
	int bufferIdZona;
	int bufferInSitu;
	int bufferVirtual;
	int bufferAusentes;

	if(zonas != NULL && censistas != NULL && len > 0){
		mostrarZonas(zonas, censistas, len);
		if(utn_getNumero(&bufferIdZona, "\n\nIndique ID de zona a finalizar. \n", "ERROR\n", 400, 700, 2) == 0){ // arreglar: finalizar solamente zonas asignadas y que no me finalice cualquiera
			for(int i = 0; i < len; i++){
				if(zonas[i].idZona == bufferIdZona && zonas[i].estado == PENDIENTE){
					for(int j = 0; j < len; j++){
						if(censistas[j].idZona == zonas[i].idZona){
							if(utn_getNumero(&bufferInSitu, "\nIndique censados in situ: (0-400): ", "ERROR\n", 0, 400, 2) == 0){
								if(utn_getNumero(&bufferVirtual, "\nIndique censados de manera virtual: (0 - 400): ", "ERROR\n", 0, 400, 2) == 0){
									if(utn_getNumero(&bufferAusentes, "\nIndique ausentes. (0 - 400): ", "ERROR\n", 0, 400, 2) == 0){
										ausentes = bufferAusentes;
									}
									virtual = bufferVirtual;
								}
								inSitu = bufferInSitu;
							}
						} else {
							printf("ERROR, no tiene ningun censista asociado.");
							break;
						}
					}
				}
			}
		} else {
			printf("ERROR, no se encontro el ID a finalizar.");
		}

		for(int i = 0; i < len; i++){
			if(zonas[i].estado == PENDIENTE && bufferIdZona == zonas[i].idZona){
				for(int j = 0; j < len; j++){
					if(censistas[j].estado == ACTIVO && censistas[j].idZona == zonas[i].idZona){
						zonas[i].inSitu = inSitu;
						zonas[i].virtual = virtual;
						zonas[i].ausentes = ausentes;
						zonas[i].estado = FINALIZADO;
						censistas[j].estado = LIBERADO;

						retorno = 0;
					}
				}
			}
		}
	}
	return retorno;
}

/// @brief Muestra la lista de zonas
///
/// @param list Puntero al array
/// @param len Largo del array
/// @return Retorna (0) si hay error - (1) si no
//int mostrarZonas(Zona *list, int len) {
//	int retorno;
//	retorno = -1;
//
//	if(list != NULL && len > 0){
//		for(int i = 0; i < len; i++){
//			mostrarZona(list[i]);
//		}
//		retorno = 0;
//	}
//
//return retorno;
//}
/// @brief Muestra una zona
///
/// @param list Puntero al array
void mostrarZona(Zona list){

	if(list.isEmpty == 0) {
		printf("ID: %d - CALLE 1: %s - CALLE 2: %s - CALLE 3: %s - CALLE 4: %s - LOCALIDAD: %s - ESTADO: %s\n",
				list.idZona, list.calles[0], list.calles[1], list.calles[2], list.calles[3], localidad[list.localidadZona], estado[list.estado]);
	}
}

/// @brief Carga forzada de zonas
///
/// @param list Puntero al array
/// @return Retorna (-1) si hay error - (0) si no
int cargaForzadaZona(Zona *list){
	int retorno = -1;
	int i;
	printf("\nINFORMAR ZONA/S\n\n");

	Zona zonas[LEN_CARGA_ZONA] = {{400,{"POSADAS","PICO","CAXARAVILLE", "CAMPICHUELO"}, 2, PENDIENTE, 0, 0, 0, 0},
								{402,{"algo","algo2","algo3", "algo4"}, 3, PENDIENTE, 0, 0, 0, 0},
								{403,{"EEEEE","MARADONA","EL ", "DIEEEO"}, 4, PENDIENTE, 0, 0, 0, 0},
								{404,{"MESSI","HACE","UN", "GOL"}, 5, PENDIENTE, 0, 0, 0, 0},
								{405,{"DDDD","algAAo2","aEEEE3", "aWWWW4"}, 6, PENDIENTE, 0, 0, 0, 0}};




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

//// @brief Muestra una zona con sus datos y estado "pendiente"
///
/// @param list Puntero al array
void mostrarZonaPendiente(Zona list){

	if(list.isEmpty == 0 && list.estado == PENDIENTE) {
		printf("ID: %d - CALLE 1: %s - CALLE 2: %s - CALLE 3: %s - CALLE 4: %s - LOCALIDAD: %s - ESTADO: %s\n",
				list.idZona, list.calles[0], list.calles[1], list.calles[2], list.calles[3], localidad[list.localidadZona], estado[list.estado]);
	}

}

/// @brief Muestra la lista de zonas con sus datos y estado "pendiente"
///
/// @param list Puntero al array
/// @param len Largo del array
/// @return Retorna (0) si hay error - (1) si no
int mostrarZonasPendientes(Zona *list, int len) {
	int retorno;
	retorno = -1;

	if(list != NULL && len > 0){
		for(int i = 0; i < len; i++){
			mostrarZonaPendiente(list[i]);
		}
		retorno = 0;
	}

return retorno;
}

int mostrarZonas(Zona *zonas, Censista *censistas, int len){

	int retorno = -1;

	if(zonas != NULL && censistas != NULL && len){
		for(int i = 0; i < len; i++){
			if(zonas[i].isEmpty == 0){
				printf("\nID: %d \nCALLE 1: %s - CALLE 2: %s - CALLE 3: %s - CALLE 4: %s \nLOCALIDAD: %s \nESTADO: %s \nCENSADOS: IN SITU: %d - VIRTUALES: %d - AUSENTES: %d\n",
						zonas[i].idZona,
						zonas[i].calles[0], zonas[i].calles[1], zonas[i].calles[2], zonas[i].calles[3],
						localidad[zonas[i].localidadZona],
						estado[zonas[i].estado],
						zonas[i].inSitu, zonas[i].virtual, zonas[i].ausentes);
				retorno = 0;
				for(int j = 0; j < len; j++){
					if(censistas[j].idZona == zonas[i].idZona && censistas[j].estado == ACTIVO){
						printf("RESPONSABLE: NOMBRE: %s - APELLIDO: %s\n\n", censistas[j].nombre, censistas[j].apellido);
					}
				}
			}
		}
	}
	return retorno;
}
