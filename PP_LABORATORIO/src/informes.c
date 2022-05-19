/*
 * informes.c
 *
 *  Created on: 19 may. 2022
 *      Author: matias
 */
#define CANT_CENSISTAS_ZONAS 10;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "informes.h"
#include "utn.h"
#include "zona.h"
#include "censista.h"

/// @param zonas Puntero al array
/// @param censistas Puntero al array
/// @param len Largo del array
/// @return
int censistasActivosYZonaPendiente(Zona *zonas, Censista *censistas, int len){
	int retorno = -1;
	int contador = 0;

	if(zonas != NULL && censistas != NULL && len > 0){
		for(int i = 0; i < len; i++){
			if(censistas[i].isEmpty == 0 && censistas[i].estado == ACTIVO){
				for(int j = 0; j < len; j++){
					if(zonas[i].isEmpty == 0 && zonas[i].estado == PENDIENTE && censistas[i].idZona == zonas[j].idZona){
						contador++;
						retorno = 0;
					}
				}
			}
		}
		printf("Cantidad de censistas en estado Activo con zona Pendiente: %d\n\n", contador);
	}

	return retorno;
}

int casasAusentes(Zona *zonas, int len){
	int retorno = -1;
	int total = 0;

	if(zonas != NULL && len > 0){
		for(int i = 0; i < len; i++){
			if(zonas[i].isEmpty == 0 && zonas[i].estado == FINALIZADO){
				total += zonas[i].ausentes;
			}
		}
	}
	return total;
}

int localidadCasasAusentes(Zona *zonas, int len){
	int retorno = -1;
	int total = 0;
	if(zonas != NULL && len > 0){
		for(int i = 0; i < len; i++){
			if(zonas[i].isEmpty == 0 && zonas[i].estado == FINALIZADO){
				for(int j = 0; j < len; j++){
					if(zonas[i].ausentes > zonas[j].ausentes){
						total += zonas[i].ausentes;
					}
				}
			}
		}

	}

	return retorno;
}

int cantidadCensos(Zona *zonas, int len){
	int retorno = -1;
	int contadorCensos = 0;

	if(zonas != NULL && len > 0){
		for(int i = 0; i < len; i++){
			if(zonas[i].isEmpty == 0 && zonas[i].estado == FINALIZADO){
				contadorCensos++;
			}
		}
	}

	return contadorCensos;
}

/// @brief Ordena los censistas activos por orden alfabetico
/// @param censistas Puntero al array
/// @param len Largo del array
/// @return Retorna -1 si hubo error y 0 si no
int censistasOrdenados(Censista *censistas, int len){
	int retorno = -1;
	int estaOrdenado;
	Censista bufferApellido;

	if(censistas != NULL && len > 0){
		do{
			estaOrdenado = 1;
			len--;
			for(int i = 0; i < len; i++){
				if(censistas[i].estado == ACTIVO){
					if (stricmp(censistas[i].apellido, censistas[i + 1].apellido) > 0) {
					bufferApellido = censistas[i];
					censistas[i] = censistas[i + 1];
					censistas[i + 1] = bufferApellido;
					estaOrdenado = 0;
				} else if (stricmp(censistas[i].apellido, censistas[i + 1].apellido) == 0 && stricmp(censistas[i].nombre, censistas[i + 1].nombre) == 0) {
					bufferApellido = censistas[i];
					censistas[i] = censistas[i + 1];
					censistas[i + 1] = bufferApellido;
					estaOrdenado = 0;
				}
				}
		}
		}while(estaOrdenado == 0);
		retorno = 0;

		mostrarCensistasActivos(censistas , len);
	}
	return retorno;
}
