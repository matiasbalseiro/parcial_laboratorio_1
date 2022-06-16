/*
 * censista.c
 *
 *  Created on: 15 may. 2022
 *      Author: matia
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "censista.h"
#include "fechasDeNacimiento.h"
#include "direcciones.h"
#include "zona.h"

static int incrementarId();

/// @brief Incrementa el id
/// @return retorna el id
static int incrementarId(){
    static int id = 1000;
    id++;
    return id;
}

/// @brief Indica que todas las posiciones del array estan vacias
///
/// @param list Puntero al array
/// @param len Largo del array
/// @return Retorna (-1) si hay error - (0) si no
int initCensistas(Censista *list, int len) {

	int retorno = -1;

	if(list != NULL && len > 0){
		for (int i = 0; i < len; i++) {
			list[i].isEmpty = 1;
		}
		retorno = 0;
	}

	return retorno;
}

/// @brief Agrega en un array de censistas existentes los valores recibidos
/// 	   como parametro en la primera posicion libre
/// @param list Puntero al array
/// @param len Largo del array
/// @param id Id del censista
/// @param nombre Nombre del censista
/// @param apellido Apellido del censista
/// @param dia Dia de nacimiento del censista
/// @param mes Mes de nacimiento del censista
/// @param anio Anio de nacimiento del censista
/// @param edad Edad del censista
/// @param calle Calle domicilio del censista
/// @param altura Altura domicilio del censista
/// @return Retorna (-1) si hay error - (0) si no
int cargarCensista(Censista *list, int len, int id, char nombre[], char apellido[], int dia, int mes, int anio, int edad, char calle[], int altura){
	int retorno;
	int indexLibre;
	retorno = -1;

	if(list != NULL && len > 0 && nombre != NULL && apellido != NULL){
			indexLibre = buscarIndexPorIsEmpty(list, len);
			if(indexLibre != -1){
					strncpy(list[indexLibre].nombre, nombre, sizeof(list[indexLibre].nombre));
					strncpy(list[indexLibre].apellido, apellido, sizeof(list[indexLibre].apellido));
					list[indexLibre].fechadenacimiento.dia = dia;
					list[indexLibre].fechadenacimiento.mes = mes;
					list[indexLibre].fechadenacimiento.anio = anio;
					list[indexLibre].edad = edad;
					strncpy(list[indexLibre].direccion.calle, calle, sizeof(list[indexLibre].direccion.calle));
					list[indexLibre].direccion.altura = altura;
					list[indexLibre].estado = 3;
					list[indexLibre].idCensista = incrementarId();
					list[indexLibre].isEmpty = 0;
					retorno = 0;
					mostrarCensista(list[indexLibre]);

					printf("\nCARGA EXITOSA. SE DIO DE ALTA AL PASAJERO\n");
		}
	}
	return retorno;
}

/// @brief Busca si hay un espacio libre para cargar un censista
///
/// @param list Puntero al array
/// @param len Largo del array
/// @return Retorna si hay un espacio vacio o (-1) si no
int buscarIndexPorIsEmpty(Censista *list, int len){

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

/// @brief Si el censista esta "activo" lo pone "inactivo", si esta
/// 	   "inactivo" o "liberado" lo borra de manera logica
/// @param list Puntero al array
/// @param len Largo del array
/// @param id Id del censista
/// @return Retorna (0) si hay error - (1) si no
int removerCensista(Censista *list, int len, int id) {

	int retorno;
	retorno = -1;
	int index;
	int bufferId;
	int flag = 0;

	if (list != NULL && len > 0) {
		mostrarCensistas(list, len);
			if(utn_getNumero(&bufferId, "\n\nIndique ID a dar de baja. \n", "ERROR\n", 1000, 2000, 2) == 0){
				id = bufferId;
		}
		index = buscarCensistaPorId(list, len, id);
		if (index != -1){
			if(list[index].estado == 1) {
				list[index].estado = 2;
				printf("CENSISTA INACTIVO. SE HAN GUARDADO LOS CAMBIOS\n");
				flag = 1;
			}
			if(list[index].estado != 1 && flag == 0){
				list[index].isEmpty = 1;
				printf("BAJA EXITOSA. SE HAN GUARDADO LOS CAMBIOS\n");

			}
			retorno = 0;
		} else {
			printf("ERROR, no se ha encontrado censista asociado a ese ID.");
		}
	}
	return retorno;
}

/// @brief
///
/// @param list Puntero al array
/// @param len Largo del array
/// @param id Id del censista
/// @return Retorna (0) si hay error - (1) si no
int modificarCensista(Censista *list, int len, int id){

	int retorno = -1;
	int index;
	int opcionMenu;
	int opcionMenuFecha;
	int opcionMenuDomicilio;
	int bufferId;
	char bufferNombre[LEN_NOMBRE];
	char bufferApellido[LEN_NOMBRE];
	int bufferDia;
	int bufferMes;
	int bufferAnio;
	int bufferEdad;
	char bufferCalle[LEN_NOMBRE];
	int bufferAltura;

	if (list != NULL && len > 0) {
		mostrarCensistas(list, len);
		if (utn_getNumero(&bufferId, "\nIndique ID a modificar. \n", "ERROR\n", 1000, 2000, 2) == 0) {
			id = bufferId;
		}
		index = buscarCensistaPorId(list, len, id);
		if (index != -1){
			mostrarCensista(list[index]);
				do{
					if (utn_getNumero(&opcionMenu,

							"\n*****************************MENU MODIFICAR*****************************\n\n"
									"1. NOMBRE \n"
									"2. APELLIDO \n"
									"3. FECHA DE NACIMIENTO\n"
									"4. EDAD\n"
									"5. DOMICILIO\n"
									"6. REGRESAR AL MENU PRINCIPAL\n"
									"\nElija una opcion: ",

							"\nError opcion invalida", 1, 6, 2) == 0) {
							switch(opcionMenu){
							case 1:
								if(utn_getNombre(bufferNombre,LEN_NOMBRE,"\nIndique el nombre del censista: ","\nERROR, ingrese un nombre valido.\n",2) == 0){
									strncpy(list[index].nombre, bufferNombre, sizeof(list[index].nombre));
									printf("Modificacion realizada.");
								}
								break;
							case 2:
								if(utn_getNombre(bufferApellido,LEN_NOMBRE,"\nIndique el apellido del censista: ","\nERROR, ingrese un apellido valido.\n",2) == 0){
									strncpy(list[index].apellido, bufferApellido, sizeof(list[index].apellido));
									printf("Modificacion realizada.");
								}
								break;
							case 3:
								do{
									if (utn_getNumero(&opcionMenuFecha,

													"\n*****************************MODIFICAR FECHA DE NACIMIENTO*****************************\n\n"
															"1. DIA: \n"
															"2. MES: \n"
															"3. ANIO: \n"
															"4. VOLVER ATRAS \n"
															"\nElija una opcion: ",

															"\nError opcion invalida", 1, 4, 2) == 0) {
											}
									switch(opcionMenuFecha){
									case 1:
										if(utn_getNumero(&bufferDia, "\nIndique dia de nacimiento. (1 - 31): ", "ERROR", 1, 31, 2) == 0){
											list[index].fechadenacimiento.dia = bufferDia;
											printf("Modificacion realizada.");
										}
										break;
									case 2:
										if(utn_getNumero(&bufferMes, "\nIndique mes de nacimiento. (1 - 12): ", "ERROR", 1, 12, 2) == 0){
											list[index].fechadenacimiento.mes = bufferMes;
											printf("Modificacion realizada.");
										}
										break;
									case 3:
										if(utn_getNumero(&bufferAnio, "\nIndique anio de nacimiento. (1970 - 2004): ", "ERROR", 18, 52, 2) == 0){
											list[index].fechadenacimiento.anio = bufferAnio;
											printf("Modificacion realizada.");
										}
										break;
									case 4:
										printf("Volver atras");
										break;
									}
								}while(opcionMenuFecha != 4);

								break;
							case 4:
								if(utn_getNumero(&bufferEdad, "\nIndique anio de nacimiento. (1970 - 2004): ", "ERROR", 18, 52, 2) == 0){
									list[index].edad = bufferEdad;
									printf("Modificacion realizada.");
								}
								break;
							case 5:

								do{
									if (utn_getNumero(&opcionMenuDomicilio,

													"\n*****************************MODIFICAR DOMICILIO*****************************\n\n"
															"1. CALLE: \n"
															"2. ALTURA: \n"
															"3. VOLVER ATRAS \n"
															"\nElija una opcion: ",

															"\nError opcion invalida", 1, 3, 2) == 0) {
											}
									switch(opcionMenuDomicilio){
									case 1:
										if(utn_getNombre(bufferCalle, LEN_NOMBRE, "\nIndique calle: ", "\nERROR, ingrese una calle valida.\n", 2) == 0){
											strncpy(list[index].direccion.calle, bufferCalle, sizeof(list[index].direccion.calle));
											printf("Modificacion realizada.");
										}
										break;
									case 2:
										if(utn_getNumero(&bufferAltura, "\nIndique altura del domicilio. (1 - 10000): ", "ERROR", 1, 10000, 2) == 0){
											list[index].direccion.altura = bufferAltura;
											printf("Modificacion realizada.");
										}
										break;
									case 3:
										printf("Volver atras");
										break;
									}
								}while(opcionMenuDomicilio != 3);
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

/// @brief Busca censista por mediante su id
///
/// @param list Puntero al array
/// @param len Largo del array
/// @param id Id del censista
/// @return Retorna si encuentra el id buscado o (-1) si no
int buscarCensistaPorId(Censista *list, int len, int id) {
	int retorno;
		retorno = -1;

		if(list != NULL && len > 0 && id > 0 ){
			for(int i = 0; i < len; i++){
				if(list[i].idCensista == id && list[i].isEmpty == 0){
					retorno = i;
					break;
				}
			}
		}
	return retorno;
}

/// @brief Verifica si hay al menos un censista cargada
///
/// @param list Puntero al array
/// @param len Largo del array
/// @return Retorna (0) si hay error - (1) si no
int hayCensistaCargado(Censista *list, int len) {
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
/// @param list Puntero al array
/// @param len Largo del array
/// @param id Id del censista
/// @return Retorna (-1) si hay error - (0) si no
//int existeCensistaPorId(Censista *list, int len, int id){
//	int retorno = -1;
//
//		if(list != NULL && len > 0){
//			for(int i = 0; i < len; i++){
//				if(list[i].isEmpty == 0 && list[i].idCensista == id){
//					retorno = 0;
//					break;
//				}
//			}
//		}
//	return retorno;
//}

//int censistaLiberado(Censista *list, int len){
//	int retorno = -1;
//
//	if(list != NULL && len > 0) {
//		for(int i = 0; i < len; i++) {
//			if(list[i].isEmpty == 0 && list[i].estado == 3) {
//				retorno = i;
//			}
//		}
//	}
//	return retorno;
//}

/// @brief Muestra la lista de censistas
///
/// @param list Puntero al array
/// @param len Largo del array
/// @return Retorna (0) si hay error - (1) si no
int mostrarCensistas(Censista *list, int len) {
	int retorno;
	retorno = -1;

	if(list != NULL && len > 0){
		for(int i = 0; i < len; i++){
			mostrarCensista(list[i]);
		}
		retorno = 0;
	}

return retorno;
}

/// @brief Muestra un censista
///
/// @param list Puntero al array
void mostrarCensista(Censista list){

	char ESTADO[4][51] = {" ", "ACTIVO", "INACTIVO", "LIBERADO"};


	if(list.isEmpty == 0) {
		printf("ID: %d - Nombre: %s - Apellido: %s - Fecha de nacimiento: %d/%d/%d - Edad: %d - Domicilio: %s %d - Estado: %s\n",
				list.idCensista, list.nombre, list.apellido,
				list.fechadenacimiento.dia, list.fechadenacimiento.mes,
				list.fechadenacimiento.anio, list.edad,
				list.direccion.calle, list.direccion.altura, ESTADO[list.estado]);
	}
}

/// @brief Carga forzada de censistas
///
/// @param list Puntero al array
/// @return Retorna (-1) si hay error - (0) si no
int cargaForzadaCensista(Censista *list){
	int retorno = -1;
	int i;
	printf("\nINFORMAR CENSISTA/S\n\n");

	Censista censistas[LEN_CARGA_CENSISTA] = {{1001, "BART", "SIMPSON",{12, 3, 1992}, 19,{"CALLE FALSA", 123}, 1,0},
											{1002, "MARGE", "BOUVIE",{1, 4, 1980}, 42,{"AV SIEMPRE VIVA", 752}, 1, 0},
											{1003, "NELSON", "MUNTZ",{12, 5, 2000}, 22,{"SPRINGFIELD", 1888}, 1, 0},
											{1004, "PATTY", "SELMA",{6, 2, 1972}, 50,{"JEREMIAS", 1552}, 1, 0},
											{1005, "NED", "FLANDERS",{15, 1, 1977}, 45,{"MR BURNS", 666}, 1, 0}};

	if(list != NULL){
		for(i = 0; i < LEN_CARGA_CENSISTA; i++){
			list[i] = censistas[i];
			list[i].isEmpty = 0;
			retorno = 0;
			mostrarCensista(list[i]);
		}
	}
	return retorno;
}

