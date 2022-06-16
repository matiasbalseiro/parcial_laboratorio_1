/*
 * zona.h
 *
 *  Created on: 15 may. 2022
 *      Author: matia
 */
#ifndef ZONA_H_
#define ZONA_H_

#include "censista.h"

#define CANT_CALLES 4
#define LEN_CALLES 51
#define CANT_CALLES 4
#define LEN_CARGA_ZONA 5

struct {
	int idZona;
	char calles[CANT_CALLES][LEN_CALLES];
	int localidadZona;
	int estado; //pendiente2/finalizado1
	int inSitu;
	int virtual;
	int ausentes;
	int isEmpty;
}typedef Zona;

int initZonas(Zona *list, int len);

int cargarZona(Zona *list, int len, int id, char calle[][51], int localidad);

int cargarDatos(Zona *zonas,int inSitu, int virtual, int ausentes, int len, Censista *censistas);

int mostrarZonas(Zona *list, int len);

void mostrarZona(Zona list);

int buscarIndexPorIsEmptyZona(Zona *list, int len);

int hayZonaCargada(Zona *list, int len);

int asignarZona(Zona *zonas, int len, Censista *censistas);

int cargaForzadaZona(Zona *list);





#endif /* ZONA_H_ */
