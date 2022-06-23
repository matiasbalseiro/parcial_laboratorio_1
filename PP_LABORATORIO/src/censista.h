/*
 * censista.h
 *
 *  Created on: 15 may. 2022
 *      Author: matias
 */

#ifndef CENSISTA_H_
#define CENSISTA_H_

#define LEN_NOMBRE 51
#define LEN_CALLE 51
#define LEN_CARGA_CENSISTA 5
#define ACTIVO 1
#define INACTIVO 2
#define LIBERADO 3

typedef struct {
	int dia;
	int mes;
	int anio;
} Fechadenacimiento;

typedef struct {
	char calle[51];
	int altura;
} Direccion;

typedef struct {
	int idCensista;
	char nombre[51];
	char apellido[51];
	Fechadenacimiento fechadenacimiento;
	int edad;
	Direccion direccion;
	int estado; //activo inactivo liberado
	int idZona;
	int isEmpty;
} Censista;

int initCensistas(Censista *list, int len);

int cargarCensista(Censista *list, int len, int id, char nombre[], char apellido[],
					int dia, int mes, int anio, int edad, char calle[], int altura);

int removerCensista(Censista *list, int len, int id);

int modificarCensista(Censista *list, int len, int id);

int buscarCensistaPorId(Censista *list, int len, int id);

int buscarIndexPorIsEmpty(Censista *list, int len);

int hayCensistaCargado(Censista *list, int len);

int existeCensistaPorId(Censista *list, int len, int id);

int censistaLiberado(Censista *list, int len);

int mostrarCensistas(Censista *list, int len);

int mostrarCensistasActivos(Censista *list, int len);

void mostrarCensista(Censista list);

int cargaForzadaCensista(Censista *list);

int mostrarCensistaPendiente(Censista list);

int mostrarCensistasPendientes(Censista *list, int len);

#endif /* CENSISTA_H_ */

