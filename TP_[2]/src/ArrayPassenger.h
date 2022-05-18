#ifndef ARRAYPASSENGER_H_
#define ARRAYPASSENGER_H_

#define LEN_NAME 51
#define LEN_CODE 10
#define LEN_FORCED_CHARGE 5

struct {
	int id;
	char name[51];
	char lastName[51];
	float price;
	char flycode[10];
	int typePassenger;
	int statusFlight;
	int isEmpty;
}typedef Passenger;


int initPassengers(Passenger *list, int len);
int addPassenger(Passenger *list, int len, int id, char name[], char lastName[], float price, int typePassenger, char flycode[], int statusFlight);
int findPassengerById(Passenger *list, int len, int id);
int removePassenger(Passenger *list, int len, int id);
int modifyPassenger(Passenger *list, int len, int id);
int sortPassengers(Passenger *list, int len, int order);
int printPassengers(Passenger *list, int length);
int sortPassengersByCode(Passenger *list, int len, int order);
int findIndexById(Passenger *list, int len, int id);
int findIndexByIsEmpty(Passenger *list, int len);
void printPassenger(Passenger list);
void printHeader();
int aPassenger(Passenger *list, int len);
int forcedCharge(Passenger *list);
int countPassengers(Passenger *list, int len);
float totalPrice(Passenger *list, int len);
float averagePrice(Passenger *list, int len);
int exceedAverage(Passenger *list, int len);
int reportPassenger(Passenger *list, int len);

#endif /* ARRAYPASSENGER_H_ */
