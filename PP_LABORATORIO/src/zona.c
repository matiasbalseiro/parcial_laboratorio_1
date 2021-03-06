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
#include "menu.h"

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
					switch (localidad) {
						case 1:
							strncpy(list[indexLibre].localidadZona, "V.DOMINICO", sizeof(list[indexLibre].localidadZona));
							break;
						case 2:
							strncpy(list[indexLibre].localidadZona, "V.CORINA", sizeof(list[indexLibre].localidadZona));
							break;
						case 3:
							strncpy(list[indexLibre].localidadZona, "GERLI", sizeof(list[indexLibre].localidadZona));
							break;
						case 4:
							strncpy(list[indexLibre].localidadZona, "CHINGOLO", sizeof(list[indexLibre].localidadZona));
							break;
						case 5:
							strncpy(list[indexLibre].localidadZona, "V.OBRERA", sizeof(list[indexLibre].localidadZona));
							break;
						case 6:
							strncpy(list[indexLibre].localidadZona, "SOLANO", sizeof(list[indexLibre].localidadZona));
							break;
						case 7:
							strncpy(list[indexLibre].localidadZona, "BERNAL", sizeof(list[indexLibre].localidadZona));
							break;
						case 8:
							strncpy(list[indexLibre].localidadZona, "AVELLANEDA", sizeof(list[indexLibre].localidadZona));
							break;
						case 9:
							strncpy(list[indexLibre].localidadZona, "LANUS", sizeof(list[indexLibre].localidadZona));
							break;
						case 10:
							strncpy(list[indexLibre].localidadZona, "QUILMES", sizeof(list[indexLibre].localidadZona));
							break;
					}
					//list[indexLibre].localidadZona = localidad;
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

int buscarZonaPorId(Zona *list, int len, int id) {
	int retorno;
		retorno = -1;

		if(list != NULL && len > 0 && id > 0 ){
			for(int i = 0; i < len; i++){
				if(list[i].idZona == id && list[i].isEmpty == 0){
					retorno = i;
					break;
				}
			}
		}
	return retorno;
}
/// @brief Busca una zona y la borra de manera logica
///
/// @param zonas Puntero al array
/// @param censistas Puntero al array
/// @param len Largo del array
/// @return Retorna -1 si hay error y 0 si no
int removerZona(Zona *zonas, Censista *censistas, int len){
	int retorno = -1;
	int bufferId;
	int flag = 0;

	if(zonas != NULL && len > 0){
		mostrarZonasPendientesYFinalizadas(zonas, len);
		if(utn_getNumero(&bufferId, "\n\nIndique ID a dar de baja. \n", "ERROR\n", 400, 2000, 2) == 0){

		for(int i = 0; i < len; i++){
			if(zonas[i].isEmpty == 0 && bufferId == zonas[i].idZona && zonas[i].estado == FINALIZADO){
				for(int j = 0; j < len; j++){
					if(censistas[j].idZona != zonas[i].idZona){
						zonas[i].isEmpty = 1;
						flag = 1;
						retorno = 0;
					}
				}
			}
		}
		if(flag == 0){
			for(int i = 0; i < len; i++){
				if(zonas[i].isEmpty == 0 && bufferId == zonas[i].idZona && zonas[i].estado == PENDIENTE){
					for(int j = 0; j < len; j++){
						if(censistas[j].idZona == zonas[i].idZona){
							censistas[j].estado = LIBERADO;
							zonas[i].isEmpty = 1;
							retorno = 0;
						}
				}
			}
		}

	}
}
	}
	return retorno;

}
/// @brief Pide el id de zona y modifica sus datos
///
/// @param list Puntero al array
/// @param len Largo del array
/// @param id Id de la zona
/// @return Retorna -1 si hay error y 0 si no
int modificarZona(Zona *list, int len, int id){

	int retorno = -1;
	int index;
	int bufferId;
	int bufferLocalidad;
	char bufferCalleUno[51];
	char bufferCalleDos[51];
	char bufferCalleTres[51];
	char bufferCalleCuatro[51];
	int opcion;
	int opcionCalles;

	if (list != NULL && len > 0) {
		mostrarZonasPendientes(list, len);
		if (!utn_getNumero(&bufferId, "\nIndique ID a modificar. \n", "ERROR\n", 400, 500, 2)) {
			id = bufferId;
		}
		index = buscarZonaPorId(list, len, id);
		if (index != -1){
			mostrarZona(list[index]);
				do{
					opcion = menuModificarZonas();
					switch(opcion){
					case 1:
						do{
							opcionCalles = menuModificarCalles();
							switch(opcionCalles){
							case 1:
								if(utn_getNombre(bufferCalleUno, LEN_CALLES, "\nIndique calle: ", "\nERROR\n", 2) == 0){
									strncpy(list[index].calles[0], bufferCalleUno, sizeof(list[index].calles[0]));
									printf("Modificacion realizada.");
								}
								break;
							case 2:
								if(utn_getNombre(bufferCalleDos, LEN_CALLES, "\nIndique calle: ", "\nERROR\n", 2) == 0){
									strncpy(list[index].calles[1], bufferCalleDos, sizeof(list[index].calles[1]));
									printf("Modificacion realizada.");
								}
								break;
							case 3:
								if(utn_getNombre(bufferCalleTres, LEN_CALLES, "\nIndique calle: ", "\nERROR\n", 2) == 0){
									strncpy(list[index].calles[2], bufferCalleTres, sizeof(list[index].calles[2]));
									printf("Modificacion realizada.");
								}
								break;
							case 4:
								if(utn_getNombre(bufferCalleCuatro, LEN_CALLES, "\nIndique calle: ", "\nERROR\n", 2) == 0){
									strncpy(list[index].calles[3], bufferCalleCuatro, sizeof(list[index].calles[3]));
									printf("Modificacion realizada.");
								}
								break;
							case 5:
								printf("Volver atras");
								break;
							}
						}while(opcionCalles != 5);

						break;
					case 2:
						if(utn_getNumero(&bufferLocalidad, "\n1)V.DOMINICO\n2)V.CORINA\n3)GERLI\n4)CHINGOLO\n5)V.OBRERA"
								"\n6)SOLANO\n7)BERNAL\n8)AVELLANEDA\n9)LANUS\n10)QUILMES\n\nIndique localidad.", "ERROR\n", 1, 10, 2) == 0){
							switch (bufferLocalidad) {
								case 1:
									strncpy(list[index].localidadZona, "V.DOMINICO", sizeof(list[index].localidadZona));
									break;
								case 2:
									strncpy(list[index].localidadZona, "V.CORINA", sizeof(list[index].localidadZona));
									break;
								case 3:
									strncpy(list[index].localidadZona, "GERLI", sizeof(list[index].localidadZona));
									break;
								case 4:
									strncpy(list[index].localidadZona, "CHINGOLO", sizeof(list[index].localidadZona));
									break;
								case 5:
									strncpy(list[index].localidadZona, "V.OBRERA", sizeof(list[index].localidadZona));
									break;
								case 6:
									strncpy(list[index].localidadZona, "SOLANO", sizeof(list[index].localidadZona));
									break;
								case 7:
									strncpy(list[index].localidadZona, "BERNAL", sizeof(list[index].localidadZona));
									break;
								case 8:
									strncpy(list[index].localidadZona, "AVELLANEDA", sizeof(list[index].localidadZona));
									break;
								case 9:
									strncpy(list[index].localidadZona, "LANUS", sizeof(list[index].localidadZona));
									break;
								case 10:
									strncpy(list[index].localidadZona, "QUILMES", sizeof(list[index].localidadZona));
									break;
							}
							printf("Modificacion realizada.");
						}
						break;
					}
				}while(opcion != 3);
		} else {
			printf("ERROR, no se ha encontrado zona asociado a ese ID.");
		}
		retorno = 0;
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
/// @brief Asigna una zona pendiente a un censista y pone a este ultimo como "activo"
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
	int flag = 0;

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
	if (flagCensista == 0) {
		mostrarCensistasPendientes(censistas, len);
		utn_getNumero(&bufferIdCensista, "\n\nIndique ID del censista para la zona. \n", "ERROR\n", 1000, 1300, 2);
		for (int i = 0; i < len; i++) {
			if (bufferIdCensista == censistas[i].idCensista && censistas[i].estado == LIBERADO) {
				censistas[i].idZona = zonas[posicionDeZona].idZona;
				censistas[i].estado = ACTIVO;
				flag = 1;
				printf("Censista asignado ID: %d a la zona ID: %d\n", censistas[i].idCensista, zonas[posicionDeZona].idZona);
				retorno = 0;
				break;
			}
		}
		if (flag == 0) {
			printf("ERROR, ese ID de censista no existe.\n");
		}
	}
	return retorno;
}

/// @brief Carga datos de una zona asignada y la finaliza
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
	int bufferInSitu = 0;
	int bufferVirtual = 0;
	int bufferAusentes = 0;
	int flag = 0;

	if(zonas != NULL && censistas != NULL && len > 0){
		mostrarZonasDatos(zonas, censistas, len);
		if(utn_getNumero(&bufferIdZona, "\n\nIndique ID de zona a finalizar. \n", "ERROR\n", 400, 700, 2) == 0){
			for(int i = 0; i < len; i++){
				if(zonas[i].idZona == bufferIdZona && zonas[i].estado == PENDIENTE){
					for(int j = 0; j < len; j++){
						if(censistas[j].idZona == zonas[i].idZona){
							if(!utn_getNumero(&bufferInSitu, "\nIndique censados in situ: (0-400): ", "ERROR\n", 0, 400, 2)){
								if(!utn_getNumero(&bufferVirtual, "\nIndique censados de manera virtual: (0 - 400): ", "ERROR\n", 0, 400, 2)){
									if(!utn_getNumero(&bufferAusentes, "\nIndique ausentes. (0 - 400): ", "ERROR\n", 0, 400, 2)){
										ausentes = bufferAusentes;
										flag = 1;
									}
									virtual = bufferVirtual;
								}
								inSitu = bufferInSitu;
							}
						}
					}
					if(flag == 0){
						printf("ERROR, no se puede finalizar una zona si no hay censista asignado.\n");
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

/// @brief Muestra una zona
///
/// @param list Puntero al array
void mostrarZona(Zona list){

	if(list.isEmpty == 0) {
		printf("ID: %d - CALLE 1: %s - CALLE 2: %s - CALLE 3: %s - CALLE 4: %s - LOCALIDAD: %s - ESTADO: ",
				list.idZona, list.calles[0], list.calles[1], list.calles[2], list.calles[3], list.localidadZona);
		switch(list.estado){
		case 1:
			printf("PENDIENTE\n");
			break;
		case 2:
			printf("FINALIZADO\n");
			break;
		}
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

	Zona zonas[LEN_CARGA_ZONA] = {{400,{"POSADAS","PICO","CAXARAVILLE", "CAMPICHUELO"}, "V.DOMINICO", PENDIENTE, 0, 0, 0, 0},
								{402,{"algo","algo2","algo3", "algo4"}, "V.OBRERA", PENDIENTE, 0, 0, 0, 0},
								{403,{"EEEEE","MARADONA","EL ", "DIEEEO"}, "BERNAL", PENDIENTE, 0, 0, 0, 0},
								{404,{"MESSI","HACE","UN", "GOL"}, "SOLANO", PENDIENTE, 0, 0, 0, 0},
								{405,{"DDDD","algAAo2","aEEEE3", "aWWWW4"}, "GERLI", PENDIENTE, 0, 0, 0, 0}};




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
		printf("ID: %d - CALLE 1: %s - CALLE 2: %s - CALLE 3: %s - CALLE 4: %s - LOCALIDAD: %s - ESTADO: ",
				list.idZona, list.calles[0], list.calles[1], list.calles[2], list.calles[3], list.localidadZona);
		switch(list.estado){
		case 1:
			printf("PENDIENTE\n");
			break;
		case 2:
			printf("FINALIZADO\n");
			break;
		}
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

//// @brief Muestra zonas pendientes y finalizadas
///
/// @param list Puntero al array
void mostrarZonaPendienteYFinalizada(Zona list){

	if(list.isEmpty == 0) {
		printf("ID: %d - CALLE 1: %s - CALLE 2: %s - CALLE 3: %s - CALLE 4: %s - LOCALIDAD: %s - ESTADO: ",
				list.idZona, list.calles[0], list.calles[1], list.calles[2], list.calles[3], list.localidadZona);
		switch(list.estado){
		case 1:
			printf("PENDIENTE\n");
			break;
		case 2:
			printf("FINALIZADO\n");
			break;
		}
	}

}

/// @brief Muestra la lista de zonas pendientes y finalizadas
///
/// @param list Puntero al array
/// @param len Largo del array
/// @return Retorna (0) si hay error - (1) si no
int mostrarZonasPendientesYFinalizadas(Zona *list, int len) {
	int retorno;
	retorno = -1;

	if(list != NULL && len > 0){
		for(int i = 0; i < len; i++){
			mostrarZonaPendienteYFinalizada(list[i]);
		}
		retorno = 0;
	}

return retorno;
}

/// @brief Muestra las zonas con todos sus datos
///
/// @param zonas Puntero al array
/// @param censistas Puntero al array
/// @param len Largo del array
/// @return Retorna (-1) si hay error - (0) si no
int mostrarZonasDatos(Zona *zonas, Censista *censistas, int len){

	int retorno = -1;
	int flag = 0;

	if(zonas != NULL && censistas != NULL && len){
		for(int i = 0; i < len; i++){
			if(zonas[i].isEmpty == 0){
				printf("\nID: %d \nCALLE 1: %s - CALLE 2: %s - CALLE 3: %s - CALLE 4: %s \nLOCALIDAD: %s \nCENSADOS: IN SITU: %d - VIRTUALES: %d - AUSENTES: %d\nESTADO: ",
						zonas[i].idZona,
						zonas[i].calles[0], zonas[i].calles[1], zonas[i].calles[2], zonas[i].calles[3],
						zonas[i].localidadZona,
						zonas[i].inSitu, zonas[i].virtual, zonas[i].ausentes);
				switch(zonas[i].estado){
				case 1:
					printf("PENDIENTE\n");
					break;
				case 2:
					printf("FINALIZADO\n");
					break;
				}
				retorno = 0;
				for(int j = 0; j < len; j++){
					if(censistas[j].idZona == zonas[i].idZona && censistas[j].estado == ACTIVO){
						printf("RESPONSABLE: NOMBRE: %s - APELLIDO: %s\n\n", censistas[j].nombre, censistas[j].apellido);
						flag = 1;
					}
				}
				if(flag == 0){
					printf("NO HAY RESPONSABLE ASIGNADO\n");
				}
			}
		}
	}
	return retorno;
}
