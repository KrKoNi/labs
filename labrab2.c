/*  Структура содержит информацию о пассажирах: номер рейса (число), фамилию (указатель), вложенную структуру – дату выезда (строка фиксированной длины) и количество минут в пути. Найти пассажиров заданного рейса. Удалить пассажиров заданной фамилией.*/
/*  Структура содержит информацию о пассажирах: номер рейса (число), фамилию (указатель), вложенное объединение – дату выезда (строка фиксированной длины) и количество минут в пути. Найти наиболее продолжительные рейсы. Удалить рейсы с заданной датой выезда.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
union ticket {
    char date [9];
    int time;
};
struct passenger {
    int flightNumber;
    char* lastName;
    union ticket tick;
};
typedef struct passenger pass;
void input (int n, pass* array) {
    for (int i = 0; i < n; i++) {
        printf("Enter %dnd flight number: ", i);
        scanf("%d", &array[i].flightNumber);
        printf("Enter %dnd passenger last name: ", i);
        fflush(stdin);
        array[i].lastName = (char*)malloc(255);
        fgets(array[i].lastName, 255, stdin);
        array[i].lastName = (char*)realloc(array[i].lastName, strlen(array[i].lastName));
    }
}
void outputOneStruct (pass* arr) {
    printf("Flight number: %d\nPassenger last name: %s", arr->flightNumber, arr->lastName);
}

void output (int n, pass* array) {
    for (int i = 0; i < n; i++) {
        outputOneStruct(array+i);
    }
}

void searchByFlightNumber (int n, pass* array) {
    int flightNum;
    printf("Enter flight number u looking for: ");
    scanf("%d", &flightNum);
    for (int i = 0; i < n; i++) {
        if (array[i].flightNumber == flightNum) {
            outputOneStruct(array+i);
        }
    }
}
void deleteByLastName (int *n, pass* array) {
    char* lastname;
    lastname = (char*)malloc(255);
    fflush(stdin);
    fgets(lastname, 255, stdin);
    lastname = (char*)realloc(lastname, strlen(lastname));
    for (int i = 0; i < *n; i++) {
        if (!strcmp(lastname, array[i].lastName)) {
            for (int j = i; j < *n - 1; j++)
                array[j] = array[j+1];
            i--;
            (*n)--;
            array = (pass*)realloc(array, (*n) * sizeof(pass));
        }
    }
    output(*n, array);
}

void searchLongestFlight (int n, pass* array) {
    int flightLength, t = 0;
    
    for (int i = 0; i < n; i++) {
        array[i].tick.time = array[i].flightNumber % 1000;
    }
    int max = -1;
    int* flightArray = (int*)calloc(1, sizeof(int));
    for (int i = 0; i < n; i++) {
        flightLength = array[i].tick.time;
        if (flightLength > max) {
            max = flightLength;
            t = 0;
            flightArray = (int*)realloc(flightArray, (t+1)*sizeof(int));
            flightArray[t] = i;
            t++;
        }
        else if ( flightLength == max ) {
            flightArray[t] = i;
            t++;
        }
    }
    for (int i = 0; i < t; i++) {
        outputOneStruct(array+flightArray[i]);
    }
}
void deleteByDateFlight (int *n, pass* array) {
    char dateflight [9];
    short day, month, year;
    for (int i = 0; i < *n; i++) {
        snprintf(array[i].tick.date, 9, "%d-%d-%d", array[i].flightNumber / 10000000, (array[i].flightNumber / 100000) % 100, (array[i].flightNumber / 1000) % 100);
        
    }
    fflush(stdin);
    printf("Enter date of flight u wanna delete in format 'dd mm yy': ");
    scanf("%hd", &day);
    scanf("%hd", &month);
    scanf("%hd", &year);
    snprintf(dateflight, 9, "%d-%d-%d", day, month, year);
    for (int i = 0; i < *n; i++) {
        if (!strcmp(dateflight, array[i].tick.date) || strcmp(dateflight, array[i].tick.date) > 9) {
            for (int j = i; j < *n - 1; j++)
                array[j] = array[j+1];
            i--;
            (*n)--;
            array = (pass*)realloc(array, (*n) * sizeof(pass));
        }
    }
    output(*n, array);
}
int main () {
    double start = clock();
    int n, choice;
    printf("Enter n: ");
    scanf("%d", &n);
    pass *array = (pass*)malloc(n * sizeof(pass));
    if (array == NULL) {printf("ERROR"); return 0;}
    input(n, array);
    output(n, array);
    printf("What do u wanna do\n1 - search passengers by flight number,\n2 - delete passenger by last name,\n3 - search longest flights,\n4 - delete by flight date:\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            searchByFlightNumber(n, array);
            break;
        case 2:
            deleteByLastName(&n, array);
            break;
        case 3:
            searchLongestFlight(n, array);
            break;
        case 4:
            deleteByDateFlight(&n, array);
            break;
        default:
            break;
    }
    printf("\ntime: %.4lfs\n", (clock() - start) / CLOCKS_PER_SEC);
    free(array);
    return 0;
}
