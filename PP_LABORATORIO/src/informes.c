/*
 * informes.c
 *
 *  Created on: 19 may. 2022
 *      Author: matias
 */
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
int informeA(Zona *zonas, Censista *censistas, int len){
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
