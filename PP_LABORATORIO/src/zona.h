/*
 * zona.h
 *
 *  Created on: 15 may. 2022
 *      Author: matias
 */
#ifndef ZONA_H_
#define ZONA_H_

#include "censista.h"

#define CANT_CALLES 4
#define LEN_CALLES 51
#define LEN_CARGA_ZONA 5
#define PENDIENTE 1
#define FINALIZADO 2

struct {
	int idZona;
	char calles[CANT_CALLES][LEN_CALLES];
	int localidadZona;
	int estado;
	int inSitu;
	int virtual;
	int ausentes;
	int isEmpty;
}typedef Zona;

int initZonas(Zona *list, int len);

int cargarZona(Zona *list, int len, int id, char calle[][51], int localidad);

int buscarZonaPorId(Zona *list, int len, int id);

int removerZona(Zona *zonas, Censista *censistas, int len);

int modificarZona(Zona *list, int len, int id);

int cargarDatos(Zona *zonas,int inSitu, int virtual, int ausentes, int len, Censista *censistas);

int mostrarZonasDatos(Zona *zonas, Censista *censistas, int len);

void mostrarZona(Zona list);

int buscarIndexPorIsEmptyZona(Zona *list, int len);

int hayZonaCargada(Zona *list, int len);

int asignarZona(Zona *zonas, int len, Censista *censistas);

int cargaForzadaZona(Zona *list);

void mostrarZonaPendiente(Zona list);

int mostrarZonasPendientes(Zona *list, int len);

void mostrarZonaPendienteYFinalizada(Zona list);

int mostrarZonasPendientesYFinalizadas(Zona *list, int len);




#endif /* ZONA_H_ */


