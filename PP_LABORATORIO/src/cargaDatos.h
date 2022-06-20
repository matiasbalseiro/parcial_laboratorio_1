/*
 * cargaDatos.h
 *
 *  Created on: 16 jun. 2022
 *      Author: Matias
 */

#ifndef CARGADATOS_H_
#define CARGADATOS_H_
#define LEN_NOMBRE 51
#define LEN_CALLE 51

int cargaDatosCensista(Censista *list, int len, char nombre[], char apellido[], int* dia, int* mes, int* anio, int* edad, char calle[], int* altura);
int cargaDatosZona(Zona *list, int len, char calle[][51], int* localidad);

#endif /* CARGADATOS_H_ */
