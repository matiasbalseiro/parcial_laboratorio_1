#include <stdio.h>
#include <stdlib.h>
#include "censista.h"
#include "zona.h"
#include "cargaDatos.h"
#include "utn.h"

int cargaDatosCensista(Censista *list, int len, char nombre[], char apellido[], int* dia, int* mes, int* anio, int* edad, char calle[], int* altura){

	int retorno = -1;

	if (utn_getNombre(nombre, LEN_NOMBRE, "\nIndique el nombre del censista: ", "\nERROR, ingrese un nombre valido.\n", 2) == 0) {
		if (utn_getNombre(apellido, LEN_NOMBRE, "\nIndique el apellido del censista: ", "\nERROR, ingrese un apellido valido.\n", 2) == 0) {
			if (utn_getNumero(dia, "\nIndique dia de nacimiento. (1 - 31): ", "ERROR\n", 1, 31, 2) == 0) {
				if (utn_getNumero(mes, "\nIndique mes de nacimiento. (1 - 12): ", "ERROR\n", 1, 31, 2) == 0) {
					if (utn_getNumero(anio, "\nIndique anio de nacimiento. (1970 - 2004): ", "ERROR\n", 1970, 2004, 2) == 0) {
						if (utn_getNumero(edad, "\nIndique edad. (18 - 52): ", "ERROR\n", 18, 52, 2) == 0) {
							if (utn_getNombre(calle, LEN_CALLE, "\nIndique calle: ", "\nERROR, ingrese una calle valida.\n", 2) == 0) {
								if (utn_getNumero(altura, "\nIndique altura del domicilio. (1 - 10000): ", "ERROR\n", 1, 10000, 2) == 0) {
									retorno = 0;
								}
							}
						}
					}
				}
			}
		}
	}
	return retorno;
}

int cargaDatosZona(Zona *list, int len, char calle[][51], int* localidad){

	int retorno = -1;
//	char calleZona[LEN_CALLE];

	if (utn_getNombre(calle[0], LEN_CALLE, "\nIndique la primer calle: ", "\nERROR\n", 2) == 0) {
		if (utn_getNombre(calle[1], LEN_CALLE, "\nIndique la segunda calle: ", "\nERROR\n", 2) == 0) {
			if (utn_getNombre(calle[2], LEN_CALLE, "\nIndique la tercer calle: ", "\nERROR\n", 2) == 0) {
				if (utn_getNombre(calle[3], LEN_CALLE, "\nIndique la cuarta calle: ", "\nERROR\n", 2) == 0) {
					if (utn_getNumero(localidad, "\n1)V.DOMINICO\n2)V.CORINA\n3)GERLI\n4)CHINGOLO\n5)V.OBRERA"
							"\n6)SOLANO\n7)BERNAL\n8)AVELLANEDA\n9)LANUS\n10)QUILMES\n\nIndique localidad.", "ERROR\n", 1, 10, 2) == 0) {
						retorno = 0;
					}
				}
			}
		}
	}


	return retorno;
}
