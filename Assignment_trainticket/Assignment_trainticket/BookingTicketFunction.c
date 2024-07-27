#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#pragma warning (disable:4996)
#pragma warning (disable:6031)

//define maximum amount
#define MAX_TRAIN 30
#define MAX_TIME 10
#define MAX_SEAT 80


//YL
typedef struct {
	char trainId[7];
}train_Id;

typedef struct {
	char time[7];
}Time;

typedef struct
{
	train_Id trainID;
	char destination[50];
	Time time[10];
	char departureStation[50];
	char arrivalStation[50];
	int price;
	int availableSeat;
}scheduleInfo;

//MOK
//member information 
typedef struct
{
	char memberId[20];
	char name[30];
	char password[20];
	char rePassword[20];
	char gender;
	char IC[13];
	char contact_number[11];
	char email[30];

}Member;


//Global declaration
mainMenu();
int generateRandom(int, int);
BookingTicket(char memberID[10]);
SearchBookedTicket(char memberID[10]);
displayE_Ticket(char memberID[10]);
CancelBooking(char memberID[10], char bookingID[6]);
ModifyFunction(char memberID[10], char bookingID[6]);
BookingHistory(char memberID[10]);
float calculatePrice_Per_Seat(int DISTANCE);
float calculateTotalPrice(float* pricePerSeat, int* quantity);
char* PaymentStatus(int);
char* returnDepartTime(char direction, char trainID[6], int departStation);
char* returnArriveTime(char direction, char trainID[6], int arriveStation);
Logo();
MenuDesign();
displayNorthSchedule();
displaySouthSchedule();
readBinFile(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]);

typedef struct {
	int day, month, year;
}Date;

typedef struct {
	char MemberID[10];
	char TrainID[7];
	char direction;
	int departureStation;
	int arrivalStation;
	Date departureDate;
	char departureTime[6];
	char arrivalTime[6];
	int seatNo[10], quantity;
	float totalPrice;
	char paymentStatus[15];
	char ticketStatus[10];

}Booking_Input;


typedef struct {
	char MemberID[10];
	char BookingID[6];
	int year, month, day;
	int bookingHour, bookingMin, bookingSec;
	char TrainID[7];
	char direction;
	int departureStation;
	int arrivalStation;
	Date departureDate;
	int quantity, seatNo[10];
	float totalPrice;
	char paymentStatus[15];
	char ticketStatus[10];
	char departureTime[6];
	char arrivalTime[6];
}SearchBooking;

typedef struct {
	char cardHolderName[50];
	char cardNo[17];
}PaymentInfo;

main() {	
	
	mainMenu();

	system("pause");
}

mainMenu() {
	char memberID[10] = "";
	int choice;
	int modifyChoice, viewChoice;
	char askForContinue;
	char bookingIDToDelete[6];
	char bookingIDToModify[6];
	bool found;
	int i = 0;
	//read member Details
	Member member[30];
	FILE* memberDetails;
	memberDetails = fopen("member dat.txt", "r");
	if (memberDetails == NULL) {
		printf("Can't open file member dat.txt!");
		exit(-1);
	}
	
	while (fscanf(memberDetails, "%s %s %s %c %s %s", member[i].memberId, member[i].name, member[i].password, &member[i].gender,
		member[i].contact_number, member[i].email) == 6) {
		i++;
	}

	fclose(memberDetails);

	do{
		found = false;
		system("cls");
		Logo();
		rewind(stdin);
		printf("%33sPlease Enter Member ID > ", " ");
		scanf("%s", memberID);
		rewind(stdin);
		for (int j = 0; j < i; j++) {
			if (strcmp(memberID, member[j].memberId) == 0) {
				printf("\n%33sValid Member ID\n", " ");
				found = true;
				do {

					Logo();
					MenuDesign();
					printf("%45s%s", " ", "[Enter Your Choice] > ");
					scanf("%d", &choice);
					rewind(stdin);
					switch (choice) {
					case 1:
						BookingTicket(memberID);
						system("cls");
						break;
					case 2:
						printf("\n%45s%s\n", " ", "============================");
						printf("%45s%s\n", " ", "1. Search Booking Details");
						printf("%45s%s\n", " ", "2. Search E-Ticket");
						printf("%45s%s\n", " ", "============================");

						printf("%45s%s", " ", "Your choice > ");
						rewind(stdin);
						scanf("%d", &viewChoice);
						switch (viewChoice) {
						case 1:
							system("cls");
							Logo();
							printf("%33s%s\n", " ", " ____________________________________________________ ");
							printf("%33s%s\n", " ", "|               SEARCH BOOKING DETAIL                |");
							printf("%33s%s\n", " ", "|____________________________________________________|");
							SearchBookedTicket(memberID);
							break;
						case 2:
							system("cls");
							Logo();
							printf("%33s%s\n", " ", " ____________________________________________________ ");
							printf("%33s%s\n", " ", "|                      E_Ticket                      |");
							printf("%33s%s\n", " ", "|____________________________________________________|");
							displayE_Ticket(memberID);
							break;
						}
						system("cls");
						break;
					case 3:

						printf("\n%45s%s\n", " ", "_________________________________");
						printf("%45s%s\n", " ", "1. Modify Booking Details");
						printf("%45s%s\n", " ", "2. Cancel Booking");
						printf("%45s%s\n", " ", "_________________________________");
						printf("%45sEnter you choice > ", " ");
						rewind(stdin);
						scanf("%d", &modifyChoice);
						switch (modifyChoice) {
						case 1:
							system("cls");
							Logo();
							printf("%33s%s\n", " ", " ____________________________________________________ ");
							printf("%33s%s\n", " ", "|                   MODIFY BOOKING                   |");
							printf("%33s%s\n", " ", "|____________________________________________________|");
							do {
								printf("%33sEnter the Booking ID to modify: ", " ");
								rewind(stdin);
								scanf("%5s", bookingIDToModify);

								ModifyFunction(memberID, bookingIDToModify);
								printf("Continue to Modify? (Y/N) > ");
								rewind(stdin);
								scanf("%c", &askForContinue);
							} while (toupper(askForContinue) == 'Y');
							system("cls");
							break;
						case 2:
							system("cls");
							Logo();
							printf("%33s%s\n", " ", " ____________________________________________________ ");
							printf("%33s%s\n", " ", "|                   CANCEL BOOKING                   |");
							printf("%33s%s\n", " ", "|____________________________________________________|");
							do {
								printf("%33sEnter the Booking ID to delete: ", " ");
								rewind(stdin);
								scanf("%5s", bookingIDToDelete);

								CancelBooking(memberID, bookingIDToDelete);
								printf("Continue to Cancel? (Y/N) > ");
								rewind(stdin);
								scanf("%c", &askForContinue);
							} while (toupper(askForContinue) == 'Y');
							system("cls");
							break;
						}
					case 4:
						system("cls");
						Logo();
						printf("%33s%s\n", " ", " ____________________________________________________ ");
						printf("%33s%s\n", " ", "|                  BOOKING HISTORY                   |");
						printf("%33s%s\n", " ", "|____________________________________________________|");
						BookingHistory(memberID);
						break;
					case 5:
						exit(-1);
					default:
						printf("%33sInvalid choice. Please enter again.", " ");
					}

				} while (choice != 5);
			}
		}

		if (!found) {
			printf("%33sMember ID %s not found.\n"," ", memberID);
			printf("[ENTER to continue]");
			scanf("%[^\n]");
		}
	}while (!found);

}

//Function to generate a random booking number between min and max
int generateRandom(int min, int max) {
	return min + rand() % (max - min + 1);
}

char* PaymentStatus(int choicePaymentMethod) {
	static char paymentStatus[15]; // Changed to a simple character array
	char inputCardNo[17] = "", inputCardHolderName[50] = "";
	int countOfError = 0;
	int i;
	bool found;
	char tryAgainCardNo;

	PaymentInfo paymentInfo[100] = {
		{"ONG LI HOONG","1111111111111111"},{"ONG YEE LIN","2222222222222222"},
		{"TAN KOK HONG","3333333333333333"},{"MOK SHAO KANG","4444444444444444"},
		{"WONG WEI XIN","5555555555555555"},{"TEH ZHI QIN","6666666666666666"},
		{"CHONG YU TING","7777777777777777"},{"LIEW WAI MAN","8888888888888888"},
		{"LEE WEI HAO","9999999999999999"}
	};



	if (choicePaymentMethod == 1) {
		strcpy(paymentStatus, "Pending");
	}
	else if (choicePaymentMethod == 2) {
		do {
			i = 0; // Move i declaration outside the loop
			found = false; // Declaration of found before usage

			if (countOfError > 0) {
				if (strcmp(inputCardHolderName, paymentInfo[i].cardHolderName) != 0) {
					printf("%34s%s\n", " ", "Invalid Cardholder Name. Please try again.");
				}
			}
			printf("%34s%s", " ", "Enter your Cardholder Name (all capital letter) > ");
			rewind(stdin);
			scanf("%[^\n]", inputCardHolderName);

			while (i < 9 && !found) {
				if (strcmp(inputCardHolderName, paymentInfo[i].cardHolderName) == 0) {
					found = true; // Set flag to true when cardholder name is found
				}
				else {
					i++;
				}
			}

			if (found) {
				printf("%34sValid Cardholder Name.\n", " ");
				bool paymentSuccessful = false;
				char tryAgainCardNo = 'Y'; // Initialize to 'Y' to enter the loop

				while (!paymentSuccessful && toupper(tryAgainCardNo) == 'Y') {
					printf("%34sPlease Enter Card Number > ", " ");
					rewind(stdin);
					scanf("%s", inputCardNo);

					if (strcmp(inputCardNo, paymentInfo[i].cardNo) == 0) {
						printf("%34s%s\n", " ", "Payment Successful!");
						strcpy(paymentStatus, "Successful");
						paymentSuccessful = true;
					}
					else {
						printf("%34s%s\n", " ", "Invalid Card Number! Payment Unsuccessful.");
						strcpy(paymentStatus, "Unsuccessful");
						printf("Try Again? (Y/N) > ");
						rewind(stdin);
						scanf("%c", &tryAgainCardNo);
					}
				}
				if (!paymentSuccessful && toupper(tryAgainCardNo) == 'N') {
					printf("%34s%s\n", " ", "Invalid Card Number! Payment Unsuccessful.");
					strcpy(paymentStatus, "Unsuccessful");

				}
			}
			else {
				printf("%34s%s\n", " ", "Invalid Cardholder Name. Please try again.");
			}

			countOfError++;
		} while (!found);

		return paymentStatus; // Return paymentStatus after the loop
	}

}

BookingTicket(char memberID[10]) {
	char continueBooking;
	int Achoice, Dchoice;
	char SorN;
	int distance;
	float totalPrice = 0, PricePerSeat = 0;
	int choicePayMethod;
	int k;
	int totalQuantity_per_Day = 0;
	int countFileRow = 0, countOfError = 0, countFileRow1 = 0;



	Booking_Input bookingInput[30];
	SearchBooking readRecord[10];
	scheduleInfo northScheduleData[MAX_TRAIN];
	scheduleInfo southScheduleData[MAX_TRAIN];

	//Text file
	FILE* fptr;
	FILE* search;
	FILE* recordSeat, * addRecord;

	//Binary File
	readBinFile(northScheduleData, southScheduleData);


	system("cls");
	Logo();
	displayNorthSchedule();
	displaySouthSchedule();

	int i = 0;
	do {
		recordSeat = fopen("checkSeatAvailable.txt", "r");
		addRecord = fopen("checkSeatAvailable.txt", "a");

		fptr = fopen("BookingHistory.txt", "a");
		search = fopen("ForSearchPurpose.txt", "a");

		if (fptr == NULL) {
			printf("Can't open the file BookingHistory.txt!");
			exit(-1);
		}

		if (search == NULL) {
			printf("Can't open the file ForSearchPurpose.txt!");
			exit(-1);
		}
		if (recordSeat == NULL || addRecord == NULL) {
			printf("Can't open the file checkSeatAvailable.txt!");
			exit(-1);
		}

		char c;
		while ((c = fgetc(search)) != EOF) {
			if (c == '\n') {
				countFileRow1++;
			}
		}
		system("cls");
		Logo();
		displayNorthSchedule();
		displaySouthSchedule();
		do {
			printf("\n%44s%s", " ", "To North or To South? (N/S) > ");
			rewind(stdin);
			scanf("%c", &SorN);

		} while (toupper(SorN) != 'S' && toupper(SorN) != 'N');


		//choose Departure Station
		printf("%34s%s", " ", "----------------------------------------------------\n");
		printf("%34s%s", " ", "----------------------------------------------------\n");
		printf("%34s%s\n\n", " ", "Please select your Departure Station");
		if (toupper(SorN) == 'S') {
			system("cls");
			Logo();
			displaySouthSchedule();
			for (int j = 0; j < 9; j++) {
				printf("%34s%d. %s\n", " ", j + 1, southScheduleData[j].destination);
			}
		}
		else if (toupper(SorN) == 'N') {
			system("cls");
			Logo();
			displayNorthSchedule();
			for (int j = 0; j < 9; j++) {
				printf("%34s%d. %s\n", " ", j + 1, northScheduleData[j].destination);
			}
		}
		printf("%34s%s\n", " ", "----------------------------------------------------");
		do {
			printf("%34s%s", " ", "Departure Station > ");
			rewind(stdin);
			scanf("%d", &Dchoice);
		} while (Dchoice < 1 || Dchoice > 9);

		//choose Arrival Station
		printf("%34s%s", " ", "----------------------------------------------------\n");
		printf("%34s%s", " ", "----------------------------------------------------\n");
		printf("%34s%s\n\n", " ", "Please select your Arrival Station");
		if (toupper(SorN) == 'S') {
			for (int j = 1; j < 10; j++) {
				printf("%34s%d. %s\n", " ", j, southScheduleData[j].destination);
			}
		}
		else if (toupper(SorN) == 'N') {
			for (int j = 1; j < 10; j++) {
				printf("%34s%d. %s\n", " ", j, northScheduleData[j].destination);
			}
		}
		printf("%34s%s\n", " ", "----------------------------------------------------");
		do {
			printf("%34s%s", " ", "Arrival Station > ");
			rewind(stdin);
			scanf("%d", &Achoice);
		} while (Achoice < 1 || Achoice > 9);


		countOfError = 0;

		srand(time(NULL));

		time_t currentTime;
		time(&currentTime);

		// Converting the timestamp into a struct containing date and time components
		struct tm* localTime = localtime(&currentTime);
		int currentYear = localTime->tm_year + 1900;
		int currentMonth = localTime->tm_mon + 1;
		int currentDay = localTime->tm_mday;

		//Formatting and displaying the date and time
		char formattedTime[50]; // Buffer to hold formatted time
		strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", localTime);

		int randomNumber = generateRandom(1000, 9999);
		bool inputWrong;
		inputWrong = false;
		int duplicate;

		do {
			rewind(recordSeat);
			duplicate = 0;
			//input TrainID

			if (toupper(SorN) == 'S') {
				countOfError = 0;
				do {
					if (countFileRow > 0) {
						if (strcmp(bookingInput[i].TrainID, "TS1001") != 0 &&
							strcmp(bookingInput[i].TrainID, "TS1002") != 0 &&
							strcmp(bookingInput[i].TrainID, "TS1003") != 0 &&
							strcmp(bookingInput[i].TrainID, "TS1004") != 0 &&
							strcmp(bookingInput[i].TrainID, "TS1005") != 0 &&
							strcmp(bookingInput[i].TrainID, "TS1006") != 0 &&
							strcmp(bookingInput[i].TrainID, "TS1007") != 0 &&
							strcmp(bookingInput[i].TrainID, "TS1008") != 0 &&
							strcmp(bookingInput[i].TrainID, "TS1009") != 0 &&
							strcmp(bookingInput[i].TrainID, "TS1010") != 0) {
							printf("\n%34s%s\n", " ", "Please enter correct TrainID based on the direction you selected.");
						}
					}
					printf("\n%34s%s", " ", "Please Enter Train ID > ");
					rewind(stdin);
					scanf("%s", bookingInput[i].TrainID);
					countOfError++;
				} while (strcmp(bookingInput[i].TrainID, "TS1001") != 0 &&
					strcmp(bookingInput[i].TrainID, "TS1002") != 0 &&
					strcmp(bookingInput[i].TrainID, "TS1003") != 0 &&
					strcmp(bookingInput[i].TrainID, "TS1004") != 0 &&
					strcmp(bookingInput[i].TrainID, "TS1005") != 0 &&
					strcmp(bookingInput[i].TrainID, "TS1006") != 0 &&
					strcmp(bookingInput[i].TrainID, "TS1007") != 0 &&
					strcmp(bookingInput[i].TrainID, "TS1008") != 0 &&
					strcmp(bookingInput[i].TrainID, "TS1009") != 0 &&
					strcmp(bookingInput[i].TrainID, "TS1010")
					);
			}
			else if (toupper(SorN) == 'N') {
				countOfError = 0;
				do {
					if (countOfError > 0) {
						if (strcmp(bookingInput[i].TrainID, "TN1001") != 0 &&
							strcmp(bookingInput[i].TrainID, "TN1002") != 0 &&
							strcmp(bookingInput[i].TrainID, "TN1003") != 0 &&
							strcmp(bookingInput[i].TrainID, "TN1004") != 0 &&
							strcmp(bookingInput[i].TrainID, "TN1005") != 0 &&
							strcmp(bookingInput[i].TrainID, "TN1006") != 0 &&
							strcmp(bookingInput[i].TrainID, "TN1007") != 0 &&
							strcmp(bookingInput[i].TrainID, "TN1008") != 0 &&
							strcmp(bookingInput[i].TrainID, "TN1009") != 0 &&
							strcmp(bookingInput[i].TrainID, "TN1010") != 0) {
							printf("%34s%s\n", " ", "Please enter correct TrainID based on the direction you selected.");
						}
					}
					printf("%34s%s", " ", "Please Enter Train ID > ");
					rewind(stdin);
					scanf("%s", bookingInput[i].TrainID);
					countOfError++;
				} while (strcmp(bookingInput[i].TrainID, "TN1001") != 0 &&
					strcmp(bookingInput[i].TrainID, "TN1002") != 0 &&
					strcmp(bookingInput[i].TrainID, "TN1003") != 0 &&
					strcmp(bookingInput[i].TrainID, "TN1004") != 0 &&
					strcmp(bookingInput[i].TrainID, "TN1005") != 0 &&
					strcmp(bookingInput[i].TrainID, "TN1006") != 0 &&
					strcmp(bookingInput[i].TrainID, "TN1007") != 0 &&
					strcmp(bookingInput[i].TrainID, "TN1008") != 0 &&
					strcmp(bookingInput[i].TrainID, "TN1009") != 0 &&
					strcmp(bookingInput[i].TrainID, "TN1010")
					);
			}
			rewind(stdin);
			//Input departure date
			countOfError = 0;
			do {
				if (countOfError > 0) {
					if (bookingInput[i].departureDate.month > 12 || bookingInput[i].departureDate.month < 1) {
						printf("\n%34s%s\n", " ", "Please enter valid month between 1 - 12.");
					}
					if (bookingInput[i].departureDate.day > 31 || bookingInput[i].departureDate.day < 1) {
						printf("\n%34s%s\n", " ", "Please provide valid date that exists within the chosen month.");
					}
					if (bookingInput[i].departureDate.year < currentYear ||
						(bookingInput[i].departureDate.year == currentYear && bookingInput[i].departureDate.month < currentMonth) ||
						(bookingInput[i].departureDate.year == currentYear && bookingInput[i].departureDate.month == currentMonth && bookingInput[i].departureDate.day < currentDay)) {
						printf("\n%34s%s\n", " ", "Departure date cannot be earlier than the current date.");
					}
				}


				printf("\n%34s%s", " ", "Please Enter Departure date (dd mm yyyy) > ");
				scanf("%d %d %d", &bookingInput[i].departureDate.day,
					&bookingInput[i].departureDate.month,
					&bookingInput[i].departureDate.year);
				rewind(stdin);
				countOfError++;

			} while (bookingInput[i].departureDate.year < currentYear ||
				(bookingInput[i].departureDate.year == currentYear && bookingInput[i].departureDate.month < currentMonth) ||
				(bookingInput[i].departureDate.year == currentYear && bookingInput[i].departureDate.month == currentMonth && bookingInput[i].departureDate.day < currentDay) ||
				(bookingInput[i].departureDate.month > 12 || bookingInput[i].departureDate.month < 1) ||
				(bookingInput[i].departureDate.month == 1 && (bookingInput[i].departureDate.day > 31 || bookingInput[i].departureDate.day < 1)) ||
				(bookingInput[i].departureDate.month == 2 && (bookingInput[i].departureDate.day > 29 || bookingInput[i].departureDate.day < 1)) ||
				(bookingInput[i].departureDate.month == 3 && (bookingInput[i].departureDate.day > 31 || bookingInput[i].departureDate.day < 1)) ||
				(bookingInput[i].departureDate.month == 4 && (bookingInput[i].departureDate.day > 30 || bookingInput[i].departureDate.day < 1)) ||
				(bookingInput[i].departureDate.month == 5 && (bookingInput[i].departureDate.day > 31 || bookingInput[i].departureDate.day < 1)) ||
				(bookingInput[i].departureDate.month == 6 && (bookingInput[i].departureDate.day > 30 || bookingInput[i].departureDate.day < 1)) ||
				(bookingInput[i].departureDate.month == 7 && (bookingInput[i].departureDate.day > 31 || bookingInput[i].departureDate.day < 1)) ||
				(bookingInput[i].departureDate.month == 8 && (bookingInput[i].departureDate.day > 31 || bookingInput[i].departureDate.day < 1)) ||
				(bookingInput[i].departureDate.month == 9 && (bookingInput[i].departureDate.day > 30 || bookingInput[i].departureDate.day < 1)) ||
				(bookingInput[i].departureDate.month == 10 && (bookingInput[i].departureDate.day > 31 || bookingInput[i].departureDate.day < 1)) ||
				(bookingInput[i].departureDate.month == 11 && (bookingInput[i].departureDate.day > 30 || bookingInput[i].departureDate.day < 1)) ||
				(bookingInput[i].departureDate.month == 12 && (bookingInput[i].departureDate.day > 31 || bookingInput[i].departureDate.day < 1))
				);
			//input quantity
			countOfError = 0;
			do {
				if (countOfError > 0) {
					if (bookingInput[i].quantity > 9) {
						printf("%34s%s\n", " ", "Booking quantity is limited to 10 seats per Booking.");
					}
				}
				printf("\n%34s%s", " ", "Please Enter Quantity > ");
				scanf("%d", &bookingInput[i].quantity);
				rewind(stdin);
				countOfError++;
			} while (bookingInput[i].quantity > 10);

			k = 0;
			int invalidSeat;
			do {
				invalidSeat = 0;
				printf("\n");
				printf("%34sPlease Enter Seat No %d (1001 - 1080) > ", " ", k + 1);
				scanf("%d", &bookingInput[i].seatNo[k]);

				if (bookingInput[i].seatNo[k] < 1001 || bookingInput[i].seatNo[k]>1080) {
					printf("%34sOnly Seat between 1001 and 1080 are available.\n", " ");
					invalidSeat = 1;
					k = 0;
				}
				else {
					k++;
				}
			} while (k < bookingInput[i].quantity || invalidSeat == 1);

			int j = 0;
			while ((fscanf(recordSeat, "%6s %d %d %d %d",
				readRecord[j].TrainID,
				&readRecord[j].departureDate.day, &readRecord[j].departureDate.month, &readRecord[j].departureDate.year,
				&readRecord[j].quantity) == 5)) {
				int k = 0;
				while (k < readRecord[j].quantity && fscanf(recordSeat, " %d", &readRecord[j].seatNo[k]) == 1) {
					k++;
				}

				if (strcmp(bookingInput[i].TrainID, readRecord[j].TrainID) == 0) {
					if (bookingInput[i].departureDate.day == readRecord[j].departureDate.day && bookingInput[i].departureDate.month == readRecord[j].departureDate.month && bookingInput[i].departureDate.year == readRecord[j].departureDate.year) {
						for (int k = 0; k < bookingInput[i].quantity; k++) {
							for (int h = 0; h < readRecord[j].quantity; h++) {
								if (bookingInput[i].seatNo[k] != readRecord[j].seatNo[h]) {

								}
								else {
									printf("\n%34sSeat %d of Train %s is not available on %02d/%02d/%04d.\n", " ", bookingInput[i].seatNo[k], bookingInput[i].TrainID,
										bookingInput[i].departureDate.day, bookingInput[i].departureDate.month, bookingInput[i].departureDate.year);
									duplicate++;

								}
							}
						}
					}
				}

				j++;
			}
			if (strcmp(returnDepartTime(SorN, bookingInput[i].TrainID, Dchoice), "-") == 0 || strcmp(returnArriveTime(SorN, bookingInput[i].TrainID, Achoice), "-") == 0) {
				printf("%34s%s\n", " ", "This Train ID is not available for your trip.");
				duplicate++;

			}
		} while (duplicate > 0); // Repeat the loop if input is wrong



		distance = Achoice + 1 - Dchoice;
		PricePerSeat = calculatePrice_Per_Seat(distance);
		bookingInput[i].totalPrice = calculateTotalPrice(&PricePerSeat, &bookingInput[i].quantity);


		if (bookingInput[i].totalPrice > 0) {
			printf("%34s%s RM %.2f\n\n", " ", "TOTAL PRICE >", bookingInput[i].totalPrice);
			printf("%34s%s\n", " ", "==============================================");
			printf("%34s%s\n", " ", "Please select you payment method.");
			printf("%34s%s\n", " ", "1. Cash (Pay at Counter)");
			printf("%34s%s\n", " ", "2. Debit / Credit card");
			printf("%34s%s\n", " ", "==============================================");
			do {
				printf("%34s%s", " ", "[Your choice] > ");
				scanf("%d", &choicePayMethod);
			} while (choicePayMethod != 1 && choicePayMethod != 2);

			strcpy(bookingInput[i].paymentStatus, PaymentStatus(choicePayMethod));
			printf("%34sPayment status : %s\n", " ", bookingInput[i].paymentStatus);

			if (strcmp(bookingInput[i].paymentStatus, "Unsuccessful") != 0) {
				printf("%34s%s\n\n", " ", "Your booking have been recorded!");
				//Save into bookingDetails.txt and BookingHistory.txt
				fprintf(fptr, "%s ", memberID);
				fprintf(search, "%s ", memberID);

				fprintf(fptr, "B%04d ", randomNumber);
				fprintf(search, "B%04d ", randomNumber);

				fprintf(fptr, "%s ", formattedTime);
				fprintf(search, "%s ", formattedTime);

				fprintf(fptr, "%s ", bookingInput[i].TrainID);
				fprintf(search, "%s ", bookingInput[i].TrainID);
				fprintf(addRecord, "%s ", bookingInput[i].TrainID);

				fprintf(fptr, "%c ", SorN);
				fprintf(search, "%c ", SorN);

				fprintf(fptr, "%d ", Dchoice);
				fprintf(search, "%d ", Dchoice);

				fprintf(fptr, "%d ", Achoice);
				fprintf(search, "%d ", Achoice);

				fprintf(fptr, "%02d %02d %04d ", bookingInput[i].departureDate.day,
					bookingInput[i].departureDate.month,
					bookingInput[i].departureDate.year);
				fprintf(search, "%02d %02d %04d ", bookingInput[i].departureDate.day,
					bookingInput[i].departureDate.month,
					bookingInput[i].departureDate.year);
				fprintf(addRecord, "%02d %02d %04d ", bookingInput[i].departureDate.day,
					bookingInput[i].departureDate.month,
					bookingInput[i].departureDate.year);

				fprintf(fptr, "%d ", bookingInput[i].quantity);
				fprintf(search, "%d ", bookingInput[i].quantity);
				fprintf(addRecord, "%d ", bookingInput[i].quantity);

				fprintf(fptr, "%s ", returnDepartTime(SorN, bookingInput[i].TrainID, Dchoice));
				fprintf(search, "%s ", returnDepartTime(SorN, bookingInput[i].TrainID, Dchoice));

				fprintf(fptr, "%s ", returnArriveTime(SorN, bookingInput[i].TrainID, Achoice));
				fprintf(search, "%s ", returnArriveTime(SorN, bookingInput[i].TrainID, Achoice));

				fprintf(fptr, "%.2f ", bookingInput[i].totalPrice);
				fprintf(search, "%.2f ", bookingInput[i].totalPrice);

				fprintf(fptr, "%s ", bookingInput[i].paymentStatus);
				fprintf(search, "%s ", bookingInput[i].paymentStatus);

				if (strcmp(bookingInput[i].paymentStatus, "Successful") == 0) {
					strcpy(bookingInput[i].ticketStatus, "Booked");
					fprintf(fptr, "%s ", bookingInput[i].ticketStatus);
					fprintf(search, "%s ", bookingInput[i].ticketStatus);
				}
				else if (strcmp(bookingInput[i].paymentStatus, "Pending") == 0) {
					strcpy(bookingInput[i].ticketStatus, "Pending");
					fprintf(fptr, "%s ", bookingInput[i].ticketStatus);
					fprintf(search, "%s ", bookingInput[i].ticketStatus);
				}

				k = 0;
				do {
					k++;
					fprintf(fptr, "%d ", bookingInput[i].seatNo[k - 1]);
					fprintf(search, "%d ", bookingInput[i].seatNo[k - 1]);
					fprintf(addRecord, "%d ", bookingInput[i].seatNo[k - 1]);
				} while (k < bookingInput[i].quantity);
				fprintf(fptr, "\n");
				fprintf(search, "\n");
				fprintf(addRecord, "\n");

				fclose(addRecord);
				fclose(fptr);
				fclose(search);


			}

			else {
				printf("%34s%s\n", " ", "Booking Failed! Please check whether the Card Number you enter is wrong.");
			}

		}
		else {
			printf("%34s%s\n", " ", "Booking Failed! Please check that you does't select wrong direction.");
		}

		i++;

		printf("\nContinue Booking? (Y/N) > ");
		rewind(stdin);
		scanf("%c", &continueBooking);
		rewind(stdin);
		switch (toupper(continueBooking)) {
		case 'Y':
			continue;

		case 'N':
			system("cls");
			mainMenu();
		}

		while (i > 29) {
			printf("%34s%s\n", " ", "Booking cannot be added due to Booking restrictions.");
		}
		fclose(readRecord);


	} while (toupper(continueBooking) == 'Y' || countFileRow1 > 29);

}

SearchBookedTicket(char memberID[10]) {
	char searchBookingId[6] = "";
	char askForContinue;
	char destinationD[30], destinationA[30];
	SearchBooking searchBooking[30];
	bool bookingFound;
	bool memberIdFound = false;

	scheduleInfo northScheduleData[MAX_TRAIN];
	scheduleInfo southScheduleData[MAX_TRAIN];

	readBinFile(northScheduleData, southScheduleData);


	FILE* search;
	search = fopen("ForSearchPurpose.txt", "r");
	if (search == NULL) {
		printf("Can't open the file ForSearchPurpose.txt!");
		exit(-1);
	}

	do {
		bookingFound = false;

		printf("\n%37s%s", " ", "Please enter BookingID > ");
		scanf("%5s", searchBookingId);
		rewind(stdin);
		rewind(search); // Reset file pointer to the beginning of the file

		int i = 0;
		while (fscanf(search, "%9s %5s %d-%d-%d %d:%d:%d %6s %c %d %d %d %d %d %d %5s %5s %f %s %s",
			searchBooking[i].MemberID, searchBooking[i].BookingID,
			&searchBooking[i].year, &searchBooking[i].month, &searchBooking[i].day,
			&searchBooking[i].bookingHour, &searchBooking[i].bookingMin, &searchBooking[i].bookingSec,
			searchBooking[i].TrainID, &searchBooking[i].direction, &searchBooking[i].departureStation, &searchBooking[i].arrivalStation,
			&searchBooking[i].departureDate.day, &searchBooking[i].departureDate.month, &searchBooking[i].departureDate.year,
			&searchBooking[i].quantity, searchBooking[i].departureTime, searchBooking[i].arrivalTime,
			&searchBooking[i].totalPrice, searchBooking[i].paymentStatus, searchBooking[i].ticketStatus) == 21) {
			int k = 0;
			while (k < searchBooking[i].quantity && fscanf(search, " %d", &searchBooking[i].seatNo[k]) == 1) {
				k++;
			}

			if(strcmp(memberID,searchBooking[i].MemberID) == 0){
				memberIdFound = true;
				if (strcmp(searchBookingId, searchBooking[i].BookingID) == 0) {

					bookingFound = true;
					if (toupper(searchBooking[i].direction) == 'S') {
						strcpy(destinationD, southScheduleData[searchBooking[i].departureStation - 1].destination);
						strcpy(destinationA, southScheduleData[searchBooking[i].arrivalStation].destination);
					}
					else {
						strcpy(destinationD, northScheduleData[searchBooking[i].departureStation - 1].destination);
						strcpy(destinationA, northScheduleData[searchBooking[i].arrivalStation].destination);
					}
					printf("%36s_______________________________________________\n", " ");
					printf("%36s| %s%s%23s|\n", " ", "Member ID : ", searchBooking[i].MemberID, " ");
					printf("%36s| %s%s%26s|\n", " ", "Booking ID : ", searchBooking[i].BookingID, " ");
					printf("%36s| %s%04d-%02d-%02d %02d:%02d:%02d |\n", " ", "Booking Date and Time : ",
						searchBooking[i].year, searchBooking[i].month, searchBooking[i].day,
						searchBooking[i].bookingHour, searchBooking[i].bookingMin, searchBooking[i].bookingSec);
					printf("%36s| %s%-33s|\n", " ", "Train ID : ", searchBooking[i].TrainID);
					printf("%36s| %s%-25s|\n", " ", "Departure Staion : ", destinationD);
					printf("%36s| %s%-26s|\n", " ", "Arrival Station : ", destinationA);
					printf("%36s| %s%02d %02d %04d%17s|\n", " ", "Departure Date : ",
						searchBooking[i].departureDate.day, searchBooking[i].departureDate.month, searchBooking[i].departureDate.year, " ");
					printf("%36s| %s%-33d|\n", " ", "Quantity : ", searchBooking[i].quantity);
					printf("%36s| %s%-27s|\n", " ", "Departure Time : ", searchBooking[i].departureTime);
					printf("%36s| %s%-29s|\n", " ", "Arrival Time : ", searchBooking[i].arrivalTime);
					for (int k = 0; k < searchBooking[i].quantity; ++k) {
						printf("%36s| %s %d: %-29d|\n", " ", "Seat Number", k + 1, searchBooking[i].seatNo[k]);
					}
					printf("%36s| %s%-30.2f|\n", " ", "Total Price : ", searchBooking[i].totalPrice);
					printf("%36s| %s%-27s|\n", " ", "Payment Status : ", searchBooking[i].paymentStatus);
					printf("%36s| %s%-28s|\n", " ", "Ticket Status : ", searchBooking[i].ticketStatus);
					printf("%36s|_____________________________________________|\n", " ");
				}
			}
			

			i++;
		}
		if (!memberIdFound) {
			printf("%33sThe member ID %s did not make any reservations.\n", " ",memberID);
			printf("[ENTER to continue]");
			scanf("%[^\n]");
		}
		if (!bookingFound) {
			printf("\n%45sBooking ID %s not found.\n\n", " ", searchBookingId);
		}

		printf("%36sContinue to search? (Y/N) > ", " ");
		rewind(stdin);
		scanf("%c", &askForContinue);
	} while (toupper(askForContinue) == 'Y');

	fclose(search);

}

displayE_Ticket(char memberID[10]) {
	char searchBookingId[6] = "";
	char askForContinue;
	char destinationD[30], destinationA[30];
	SearchBooking searchBooking[30];
	bool bookingFound;
	bool memberIdFound = false;


	scheduleInfo northScheduleData[MAX_TRAIN];
	scheduleInfo southScheduleData[MAX_TRAIN];

	readBinFile(northScheduleData, southScheduleData);


	FILE* search;
	search = fopen("ForSearchPurpose.txt", "r");
	if (search == NULL) {
		printf("Can't open the file ForSearchPurpose.txt!");
		exit(-1);
	}

	do {
		bookingFound = false;
		printf("\n%40s%s", " ", "Please enter BookingID > ");
		scanf("%5s", searchBookingId);

		rewind(search); // Reset file pointer to the beginning of the file

		int i = 0;
		while (fscanf(search, "%9s %5s %d-%d-%d %d:%d:%d %6s %c %d %d %d %d %d %d %5s %5s %f %s %s",
			searchBooking[i].MemberID, searchBooking[i].BookingID,
			&searchBooking[i].year, &searchBooking[i].month, &searchBooking[i].day,
			&searchBooking[i].bookingHour, &searchBooking[i].bookingMin, &searchBooking[i].bookingSec,
			searchBooking[i].TrainID, &searchBooking[i].direction, &searchBooking[i].departureStation, &searchBooking[i].arrivalStation,
			&searchBooking[i].departureDate.day, &searchBooking[i].departureDate.month, &searchBooking[i].departureDate.year,
			&searchBooking[i].quantity, searchBooking[i].departureTime, searchBooking[i].arrivalTime,
			&searchBooking[i].totalPrice, searchBooking[i].paymentStatus, searchBooking[i].ticketStatus) == 21) {
			int k = 0;
			while (k < searchBooking[i].quantity && fscanf(search, " %d", &searchBooking[i].seatNo[k]) == 1) {
				k++;
			}

			if(strcmp(memberID,searchBooking[i].MemberID) == 0) {
				memberIdFound = true;
				if (strcmp(searchBookingId, searchBooking[i].BookingID) == 0) {

					bookingFound = true;
					if (strcmp(searchBooking[i].ticketStatus, "Booked") == 0) {
						if (toupper(searchBooking[i].direction) == 'S') {
							strcpy(destinationD, southScheduleData[searchBooking[i].departureStation - 1].destination);
							strcpy(destinationA, southScheduleData[searchBooking[i].arrivalStation].destination);
						}
						else {
							strcpy(destinationD, northScheduleData[searchBooking[i].departureStation - 1].destination);
							strcpy(destinationA, northScheduleData[searchBooking[i].arrivalStation].destination);
						}
						printf("%29s_______________________________________________________________\n", " ");
						printf("%29s| %s%s%39s|\n", " ", "Member ID : ", searchBooking[i].MemberID, " ");
						printf("%29s| %s%s%42s|\n", " ", "Booking ID : ", searchBooking[i].BookingID, " ");
						printf("%29s| %s%04d-%02d-%02d%36s|\n", " ", "Booking Date: ",
							searchBooking[i].year, searchBooking[i].month, searchBooking[i].day, " ");
						printf("%29s| %s%-21s%s%02d %02d %04d |\n", " ", "Train ID : ", searchBooking[i].TrainID, "Departure Date : ",
							searchBooking[i].departureDate.day, searchBooking[i].departureDate.month, searchBooking[i].departureDate.year);
						printf("%29s|_____________________________________________________________|\n", " ");

						printf("%29s| %-30s%-30s|\n", " ", "[Departure Staion]", "[Arrival Station]");
						printf("%29s| %-30s%-30s|\n", " ", destinationD, destinationA);
						printf("%29s|_____________________________________________________________|\n", " ");
						printf("%29s| %-30s%-30s|\n", " ", "[Departure Time]", "[Arrival Time]");
						printf("%29s| %-30s%-30s|\n", " ", searchBooking[i].departureTime, searchBooking[i].arrivalTime);
						printf("%29s|_____________________________________________________________|\n", " ");

						printf("%29s| %s%-49d|\n", " ", "Quantity : ", searchBooking[i].quantity);

						printf("%29s| %-30s%-30s|\n", " ", "[Seat No]", " ");
						for (int k = 0; k < searchBooking[i].quantity; ++k) {
							printf("%29s| %s %d: %-45d|\n", " ", "Seat Number", k + 1, searchBooking[i].seatNo[k]);
						}
						printf("%29s|                                                             |\n", " ");
						printf("%29s| %s%-46.2f|\n", " ", "Total Price : ", searchBooking[i].totalPrice);
						printf("%29s| %s%-44s|\n", " ", "Ticket Status : ", searchBooking[i].ticketStatus);
						printf("%29s| %49s%02d %02d %04d |\n", " ", "Ticket valid until : ",
							searchBooking[i].departureDate.day, searchBooking[i].departureDate.month, searchBooking[i].departureDate.year);
						printf("%29s|_____________________________________________________________|\n", " ");
					}
					else {
						printf("%38sOnly BOOKED ticket can be generate.\n", " ");
					}
				}
			}


			i++;
		}
		if (!memberIdFound) {
			printf("%33sMember ID %s did not make any reservations.\n", " ", memberID);
		}
		if (!bookingFound) {
			printf("\n%37sBooking ID %s not found.\n\n", " ", searchBookingId);
		}

		printf("%37sContinue to search? (Y/N) > ", " ");
		rewind(stdin);
		scanf("%c", &askForContinue);
	} while (toupper(askForContinue) == 'Y');

	fclose(search);

}

CancelBooking(char memberID[10], char bookingID[6]) {

	int countFileRow = 0;
	int countFileRowH = 0;
	bool found = false;
	FILE* originalFile, * tempFile, * originalHistory, * temphistory, * originalCheckSeat, * tempCheckSeat;
	int duplicate = 0;
	char paymentStatus[10];
	char ticketStatus[10];
	SearchBooking searchBooking[100];
	SearchBooking readRecord[100];
	bool memberIdFound = false;


	char tempFileName[] = "temp.txt";
	originalFile = fopen("ForSearchPurpose.txt", "r");
	tempFile = fopen(tempFileName, "w");
	originalHistory = fopen("BookingHistory.txt", "r");
	temphistory = fopen("tempHistory.txt", "w");
	originalCheckSeat = fopen("checkSeatAvailable.txt", "r");
	tempCheckSeat = fopen("tempCheckSeat.txt", "w");

	if (originalFile == NULL) {
		printf("Can't open the file ForSearchPurpose.txt!");
		exit(-1);
	}

	if (tempFile == NULL) {
		printf("Can't create temporary file!");
		exit(-1);
	}
	if (originalHistory == NULL) {
		printf("Can't open the BookingHistory file!");
		exit(-1);
	}
	if (temphistory == NULL) {
		printf("Can't create temporary file!");
		exit(-1);
	}


	char c;
	while ((c = fgetc(originalFile)) != EOF) {
		if (c == '\n') {
			countFileRow++;
		}
	}
	rewind(originalFile);



	for (int i = 0; i < countFileRow; i++) {

		fscanf(originalFile, "%s %s %d-%d-%d %d:%d:%d %s %c %d %d %d %d %d %d %5s %5s %f %s %s", searchBooking[i].MemberID, searchBooking[i].BookingID,
			&searchBooking[i].year, &searchBooking[i].month, &searchBooking[i].day,
			&searchBooking[i].bookingHour, &searchBooking[i].bookingMin, &searchBooking[i].bookingSec,
			searchBooking[i].TrainID, &searchBooking[i].direction, &searchBooking[i].departureStation, &searchBooking[i].arrivalStation,
			&searchBooking[i].departureDate.day, &searchBooking[i].departureDate.month, &searchBooking[i].departureDate.year,
			&searchBooking[i].quantity, searchBooking[i].departureTime, searchBooking[i].arrivalTime,
			&searchBooking[i].totalPrice, searchBooking[i].paymentStatus, searchBooking[i].ticketStatus);


		int k = 0;
		do {
			fscanf(originalFile, " %d", &searchBooking[i].seatNo[k]);
			k++;
		} while (k < searchBooking[i].quantity);
		fscanf(originalFile, "\n");

		if(strcmp(memberID,searchBooking[i].MemberID)==0) {
			memberIdFound = true;
			if (strcmp(bookingID, searchBooking[i].BookingID) != 0) {
				fprintf(tempFile, "%9s ", searchBooking[i].MemberID);
				fprintf(tempFile, "%5s ", searchBooking[i].BookingID);
				fprintf(tempFile, "%04d-%02d-%02d %02d:%02d:%02d ",
					searchBooking[i].year, searchBooking[i].month, searchBooking[i].day,
					searchBooking[i].bookingHour, searchBooking[i].bookingMin, searchBooking[i].bookingSec);
				fprintf(tempFile, "%5s ", searchBooking[i].TrainID);
				fprintf(tempFile, "%c ", searchBooking[i].direction);
				fprintf(tempFile, "%d ", searchBooking[i].departureStation);
				fprintf(tempFile, "%d ", searchBooking[i].arrivalStation);
				fprintf(tempFile, "%02d %02d %04d ", searchBooking[i].departureDate.day, searchBooking[i].departureDate.month, searchBooking[i].departureDate.year);
				fprintf(tempFile, "%d ", searchBooking[i].quantity);
				fprintf(tempFile, "%s ", searchBooking[i].departureTime);
				fprintf(tempFile, "%s ", searchBooking[i].arrivalTime);
				fprintf(tempFile, "%.2f ", searchBooking[i].totalPrice);
				fprintf(tempFile, "%s ", searchBooking[i].paymentStatus);
				fprintf(tempFile, "%s ", searchBooking[i].ticketStatus);
				k = 0;
				do {

					fprintf(tempFile, "%d ", searchBooking[i].seatNo[k]);
					k++;
				} while (k < searchBooking[i].quantity);
				fprintf(tempFile, "\n");
			}
			else {
				found = true;

				int j = 0;
				while ((fscanf(originalCheckSeat, "%6s %d %d %d %d",
					readRecord[j].TrainID,
					&readRecord[j].departureDate.day, &readRecord[j].departureDate.month, &readRecord[j].departureDate.year,
					&readRecord[j].quantity) == 5)) {
					int k = 0;
					while (k < readRecord[j].quantity && fscanf(originalCheckSeat, " %d", &readRecord[j].seatNo[k]) == 1) {
						k++;
					}
					if (strcmp(searchBooking[i].TrainID, readRecord[j].TrainID) != 0) {
						fprintf(tempCheckSeat, "%s %d %d %d %d ", readRecord[j].TrainID,
							readRecord[j].departureDate.day, readRecord[j].departureDate.month, readRecord[j].departureDate.year, readRecord[j].quantity);
						k = 0;
						do {
							k++;
							fprintf(tempCheckSeat, "%d ", readRecord[j].seatNo[k - 1]);
						} while (k < readRecord[j].quantity);
						fprintf(tempCheckSeat, "\n");
					}
					else {
						if (searchBooking[i].departureDate.day == readRecord[j].departureDate.day && searchBooking[i].departureDate.month == readRecord[j].departureDate.month && searchBooking[i].departureDate.year == readRecord[j].departureDate.year) {
							for (int k = 0; k < searchBooking[i].quantity; k++) {
								for (int h = 0; h < readRecord[j].quantity; h++) {
									if (searchBooking[i].seatNo[k] != readRecord[j].seatNo[h]) {
										fprintf(tempCheckSeat, "%s %d %d %d %d ", readRecord[j].TrainID,
											readRecord[j].departureDate.day, readRecord[j].departureDate.month, readRecord[j].departureDate.year, readRecord[j].quantity);
										k = 0;
										do {
											k++;
											fprintf(tempCheckSeat, "%d ", readRecord[j].seatNo[k - 1]);
										} while (k < readRecord[j].quantity);
										fprintf(tempCheckSeat, "\n");

									}


								}
							}

						}
						else {
							fprintf(tempCheckSeat, "%s %d %d %d %d ", readRecord[j].TrainID,
								readRecord[j].departureDate.day, readRecord[j].departureDate.month, readRecord[j].departureDate.year, readRecord[j].quantity);
							k = 0;
							do {
								k++;
								fprintf(tempCheckSeat, "%d ", readRecord[j].seatNo[k - 1]);
							} while (k < readRecord[j].quantity);
							fprintf(tempCheckSeat, "\n");
						}
					}
					j++;
				}

				printf("%33sCancel Successful! \n\n", " ");
			}
		}
		else {
			fprintf(tempFile, "%9s ", searchBooking[i].MemberID);
			fprintf(tempFile, "%5s ", searchBooking[i].BookingID);
			fprintf(tempFile, "%04d-%02d-%02d %02d:%02d:%02d ",
				searchBooking[i].year, searchBooking[i].month, searchBooking[i].day,
				searchBooking[i].bookingHour, searchBooking[i].bookingMin, searchBooking[i].bookingSec);
			fprintf(tempFile, "%5s ", searchBooking[i].TrainID);
			fprintf(tempFile, "%c ", searchBooking[i].direction);
			fprintf(tempFile, "%d ", searchBooking[i].departureStation);
			fprintf(tempFile, "%d ", searchBooking[i].arrivalStation);
			fprintf(tempFile, "%02d %02d %04d ", searchBooking[i].departureDate.day, searchBooking[i].departureDate.month, searchBooking[i].departureDate.year);
			fprintf(tempFile, "%d ", searchBooking[i].quantity);
			fprintf(tempFile, "%s ", searchBooking[i].departureTime);
			fprintf(tempFile, "%s ", searchBooking[i].arrivalTime);
			fprintf(tempFile, "%.2f ", searchBooking[i].totalPrice);
			fprintf(tempFile, "%s ", searchBooking[i].paymentStatus);
			fprintf(tempFile, "%s ", searchBooking[i].ticketStatus);
			k = 0;
			do {

				fprintf(tempFile, "%d ", searchBooking[i].seatNo[k]);
				k++;
			} while (k < searchBooking[i].quantity);
			fprintf(tempFile, "\n");
		}
	}

	char c1;
	while ((c1 = fgetc(originalHistory)) != EOF) {
		if (c1 == '\n') {
			countFileRowH++;
		}
	}
	rewind(originalHistory);

	for (int i = 0; i < countFileRowH; i++) {

		fscanf(originalHistory, "%s %s %d-%d-%d %d:%d:%d %s %c %d %d %d %d %d %d %5s %5s %f %s %s",searchBooking[i].MemberID, searchBooking[i].BookingID,
			&searchBooking[i].year, &searchBooking[i].month, &searchBooking[i].day,
			&searchBooking[i].bookingHour, &searchBooking[i].bookingMin, &searchBooking[i].bookingSec,
			searchBooking[i].TrainID, &searchBooking[i].direction, &searchBooking[i].departureStation, &searchBooking[i].arrivalStation,
			&searchBooking[i].departureDate.day, &searchBooking[i].departureDate.month, &searchBooking[i].departureDate.year,
			&searchBooking[i].quantity, searchBooking[i].departureTime, searchBooking[i].arrivalTime,
			&searchBooking[i].totalPrice, searchBooking[i].paymentStatus, searchBooking[i].ticketStatus);


		int k = 0;
		do {
			fscanf(originalHistory, " %d", &searchBooking[i].seatNo[k]);
			k++;
		} while (k < searchBooking[i].quantity);
		fscanf(originalHistory, "\n");

		if (strcmp(bookingID, searchBooking[i].BookingID) != 0) {

			fprintf(temphistory, "%9s ", searchBooking[i].MemberID);
			fprintf(temphistory, "%5s ", searchBooking[i].BookingID);
			fprintf(temphistory, "%04d-%02d-%02d %02d:%02d:%02d ",
				searchBooking[i].year, searchBooking[i].month, searchBooking[i].day,
				searchBooking[i].bookingHour, searchBooking[i].bookingMin, searchBooking[i].bookingSec);
			fprintf(temphistory, "%5s ", searchBooking[i].TrainID);
			fprintf(temphistory, "%c ", searchBooking[i].direction);
			fprintf(temphistory, "%d ", searchBooking[i].departureStation);
			fprintf(temphistory, "%d ", searchBooking[i].arrivalStation);
			fprintf(temphistory, "%02d %02d %04d ", searchBooking[i].departureDate.day, searchBooking[i].departureDate.month, searchBooking[i].departureDate.year);
			fprintf(temphistory, "%d ", searchBooking[i].quantity);
			fprintf(temphistory, "%s ", searchBooking[i].departureTime);
			fprintf(temphistory, "%s ", searchBooking[i].arrivalTime);
			fprintf(temphistory, "%.2f ", searchBooking[i].totalPrice);
			fprintf(temphistory, "%s ", searchBooking[i].paymentStatus);
			fprintf(temphistory, "%s ", searchBooking[i].ticketStatus);
			k = 0;
			do {
				fprintf(temphistory, "%d ", searchBooking[i].seatNo[k]);
				k++;
			} while (k < searchBooking[i].quantity);
			fprintf(temphistory, "\n");
		}
		else {
			fprintf(temphistory, "%9s ", searchBooking[i].MemberID);
			fprintf(temphistory, "%5s ", searchBooking[i].BookingID);
			fprintf(temphistory, "%04d-%02d-%02d %02d:%02d:%02d ",
				searchBooking[i].year, searchBooking[i].month, searchBooking[i].day,
				searchBooking[i].bookingHour, searchBooking[i].bookingMin, searchBooking[i].bookingSec);
			fprintf(temphistory, "%5s ", searchBooking[i].TrainID);
			fprintf(temphistory, "%c ", searchBooking[i].direction);
			fprintf(temphistory, "%d ", searchBooking[i].departureStation);
			fprintf(temphistory, "%d ", searchBooking[i].arrivalStation);
			fprintf(temphistory, "%02d %02d %04d ", searchBooking[i].departureDate.day, searchBooking[i].departureDate.month, searchBooking[i].departureDate.year);
			fprintf(temphistory, "%d ", searchBooking[i].quantity);
			fprintf(temphistory, "%s ", searchBooking[i].departureTime);
			fprintf(temphistory, "%s ", searchBooking[i].arrivalTime);
			fprintf(temphistory, "%.2f ", searchBooking[i].totalPrice);
			strcpy(paymentStatus, "Cancelled");
			strcpy(ticketStatus, "Cancelled");
			fprintf(temphistory, "%s ", paymentStatus);
			fprintf(temphistory, "%s ", ticketStatus);
			k = 0;
			do {
				fprintf(temphistory, "%d ", searchBooking[i].seatNo[k]);
				k++;
			} while (k < searchBooking[i].quantity);
			fprintf(temphistory, "\n");
		}
	}

	fclose(originalFile);
	fclose(tempFile);
	fclose(originalHistory);
	fclose(temphistory);
	fclose(originalCheckSeat);
	fclose(tempCheckSeat);
	if (!memberIdFound) {
		printf("%33sMember ID %s did not make any reservation.\n", " ", memberID);
	}


	if (!found) {
		printf("%33sBooking ID %s not found!\n", " ", bookingID);
	}



	remove("ForSearchPurpose.txt");
	rename("temp.txt", "ForSearchPurpose.txt");
	remove("BookingHistory.txt");
	rename("temphistory.txt", "BookingHistory.txt");
	remove("checkSeatAvailable.txt");
	rename("tempCheckSeat.txt", "checkSeatAvailable.txt");
}

ModifyFunction(char memberID[10], char bookingID[6]) {
	int k, j,h;
	int countFileRow = 0;
	int modifyDetailsChoice;
	int newDay, newMonth, newYear;
	int newSeatNo[10];
	bool found = false;
	bool memberIdFound = false;
	SearchBooking modifyBooking[100];
	SearchBooking readRecord[50];
	FILE* modify, * tempModify, * originalCheckSeat, * tempCheckSeat;
	FILE* originalHistory, * temphistory;
	originalHistory = fopen("BookingHistory.txt", "r");
	temphistory = fopen("tempHistory.txt", "w");
	modify = fopen("ForSearchPurpose.txt", "r");
	tempModify = fopen("tempModify.txt", "w");
	originalCheckSeat = fopen("checkSeatAvailable.txt", "r");
	tempCheckSeat = fopen("tempCheckSeat.txt", "w");

	if (modify == NULL || tempModify == NULL || originalCheckSeat == NULL || tempCheckSeat == NULL) {
		printf("Can't open file");
		exit(-1);
	}


	char c;
	while ((c = fgetc(modify)) != EOF) {
		if (c == '\n') {
			countFileRow++;
		}
	}
	rewind(modify);



	for (int i = 0; i < countFileRow; i++) {
		fscanf(modify, "%s %s %d-%d-%d %d:%d:%d %s %c %d %d %d %d %d %d %5s %5s %f %s %s",modifyBooking[i].MemberID, modifyBooking[i].BookingID,
			&modifyBooking[i].year, &modifyBooking[i].month, &modifyBooking[i].day,
			&modifyBooking[i].bookingHour, &modifyBooking[i].bookingMin, &modifyBooking[i].bookingSec,
			modifyBooking[i].TrainID, &modifyBooking[i].direction, &modifyBooking[i].departureStation, &modifyBooking[i].arrivalStation,
			&modifyBooking[i].departureDate.day, &modifyBooking[i].departureDate.month, &modifyBooking[i].departureDate.year,
			&modifyBooking[i].quantity, modifyBooking[i].departureTime, modifyBooking[i].arrivalTime,
			&modifyBooking[i].totalPrice, modifyBooking[i].paymentStatus, modifyBooking[i].ticketStatus);


		k = 0;
		do {
			fscanf(modify, " %d", &modifyBooking[i].seatNo[k]);
			k++;
		} while (k < modifyBooking[i].quantity);
		fscanf(modify, "\n");


		if(strcmp(memberID,modifyBooking[i].MemberID) == 0) {
			memberIdFound = true;
			if (strcmp(bookingID, modifyBooking[i].BookingID) == 0) {
				found = true;
				printf("%33sValid Booking ID\n\n", " ");
				printf("%33s==============================\n", " ");
				printf("%33sWhat do you want to modify?\n\n", " ");
				printf("%33s1. Departure Date\n", " ");
				printf("%33s2. Seat No\n", " ");
				printf("%33s==============================\n", " ");

				printf("%33s[Your choice] > ", " ");
				scanf("%d", &modifyDetailsChoice);
				switch (modifyDetailsChoice) {
				case 1:
					j = 0;
					while ((fscanf(originalCheckSeat, "%6s %d %d %d %d",
						readRecord[j].TrainID,
						&readRecord[j].departureDate.day, &readRecord[j].departureDate.month, &readRecord[j].departureDate.year,
						&readRecord[j].quantity) == 5)) {
						k = 0;
						while (k < readRecord[j].quantity && fscanf(originalCheckSeat, " %d", &readRecord[j].seatNo[k]) == 1) {
							k++;
						}

						if (strcmp(modifyBooking[i].TrainID, readRecord[j].TrainID) == 0) {
							
							if (modifyBooking[i].departureDate.day == readRecord[j].departureDate.day && modifyBooking[i].departureDate.month == readRecord[j].departureDate.month && modifyBooking[i].departureDate.year == readRecord[j].departureDate.year) {
								for (k = 0; k < modifyBooking[i].quantity; k++) {
									for (h = 0; h < readRecord[j].quantity; h++) {
										if (modifyBooking[i].seatNo[k] != readRecord[j].seatNo[h]) {
											fprintf(tempCheckSeat, "%s %d %d %d %d", readRecord[j].TrainID,
												readRecord[j].departureDate.day, readRecord[j].departureDate.month, readRecord[j].departureDate.year, readRecord[j].quantity);
											k = 0;
											do {
												k++;
												fprintf(tempCheckSeat, " %d", readRecord[j].seatNo[k - 1]);
											} while (k < readRecord[j].quantity);
											fprintf(tempCheckSeat, "\n");

										}

									}
								}
							}
							else {
	
								fprintf(tempCheckSeat, "%s %d %d %d %d", readRecord[j].TrainID,
									readRecord[j].departureDate.day, readRecord[j].departureDate.month, readRecord[j].departureDate.year, readRecord[j].quantity);
								k = 0;
								do {
									k++;
									fprintf(tempCheckSeat, " %d", readRecord[j].seatNo[k - 1]);
								} while (k < readRecord[j].quantity);
								fprintf(tempCheckSeat, "\n");
							}
						}

						j++;
					}
					printf("%33sPrevious Departure Date : %02d-%02d-%04d\n", " ", modifyBooking[i].departureDate.day, modifyBooking[i].departureDate.month, modifyBooking[i].departureDate.year);
					printf("%33sNew Departure Date (DD MM YYYY) : ", " ");
					scanf("%d %d %d", &newDay, &newMonth, &newYear);
					modifyBooking[i].departureDate.day = newDay;
					modifyBooking[i].departureDate.month = newMonth;
					modifyBooking[i].departureDate.year = newYear;
					break;
				case 2:
					j = 0;
					while ((fscanf(originalCheckSeat, "%6s %d %d %d %d",
						readRecord[j].TrainID,
						&readRecord[j].departureDate.day, &readRecord[j].departureDate.month, &readRecord[j].departureDate.year,
						&readRecord[j].quantity) == 5)) {
						int k = 0;
						while (k < readRecord[j].quantity && fscanf(originalCheckSeat, " %d", &readRecord[j].seatNo[k]) == 1) {
							k++;
						}

						if (strcmp(modifyBooking[i].TrainID, readRecord[j].TrainID) == 0) {
							if (modifyBooking[i].departureDate.day == readRecord[j].departureDate.day && modifyBooking[i].departureDate.month == readRecord[j].departureDate.month && modifyBooking[i].departureDate.year == readRecord[j].departureDate.year) {
								for (int k = 0; k < modifyBooking[i].quantity; k++) {
									for (int h = 0; h < readRecord[j].quantity; h++) {
										if (modifyBooking[i].seatNo[k] != readRecord[j].seatNo[h]) {
											fprintf(tempCheckSeat, "%s %d %d %d %d", readRecord[j].TrainID,
												readRecord[j].departureDate.day, readRecord[j].departureDate.month, readRecord[j].departureDate.year, readRecord[j].quantity);
											k = 0;
											do {
												k++;
												fprintf(tempCheckSeat, " %d", readRecord[j].seatNo[k - 1]);
											} while (k < readRecord[j].quantity);
											fprintf(tempCheckSeat, "\n");

										}

									}
								}
							}
						}

						j++;
					}
					k = 0;
					do {
						k++;
						printf("%33sPrevious Seat Number %d : %d\n", " ", k, modifyBooking[i].seatNo[k - 1]);
						printf("%33sPlease Enter Seat number %d > ", " ", k);
						scanf("%d", &newSeatNo[k - 1]);
						modifyBooking[i].seatNo[k - 1] = newSeatNo[k - 1];
						rewind(stdin);
					} while (k < modifyBooking[i].quantity);
					break;
				default:
					printf("%33sInvalid choice. Please enter again.", " ");
					break;
				}
				//New Modify details
				fprintf(tempModify, "%9s ", modifyBooking[i].MemberID);
				fprintf(tempModify, "%5s ", modifyBooking[i].BookingID);
				fprintf(tempModify, "%04d-%02d-%02d %02d:%02d:%02d ",
					modifyBooking[i].year, modifyBooking[i].month, modifyBooking[i].day,
					modifyBooking[i].bookingHour, modifyBooking[i].bookingMin, modifyBooking[i].bookingSec);
				fprintf(tempModify, "%5s ", modifyBooking[i].TrainID);
				fprintf(tempModify, "%c ", modifyBooking[i].direction);
				fprintf(tempModify, "%d ", modifyBooking[i].departureStation);
				fprintf(tempModify, "%d ", modifyBooking[i].arrivalStation);

				fprintf(tempModify, "%02d %02d %04d ", modifyBooking[i].departureDate.day, modifyBooking[i].departureDate.month, modifyBooking[i].departureDate.year);
				fprintf(tempModify, "%d ", modifyBooking[i].quantity);
				fprintf(tempModify, "%s ", modifyBooking[i].departureTime);
				fprintf(tempModify, "%s ", modifyBooking[i].arrivalTime);

				fprintf(tempModify, "%.2f ", modifyBooking[i].totalPrice);
				fprintf(tempModify, "%s ", modifyBooking[i].paymentStatus);
				fprintf(tempModify, "%s ", modifyBooking[i].ticketStatus);

				k = 0;
				do {
					fprintf(tempModify, "%d ", modifyBooking[i].seatNo[k]);
					k++;
				} while (k < modifyBooking[i].quantity);
				fprintf(tempModify, "\n");

				//New Modify History details
				fprintf(temphistory, "%9s ", modifyBooking[i].MemberID);
				fprintf(temphistory, "%5s ", modifyBooking[i].BookingID);
				fprintf(temphistory, "%04d-%02d-%02d %02d:%02d:%02d ",
					modifyBooking[i].year, modifyBooking[i].month, modifyBooking[i].day,
					modifyBooking[i].bookingHour, modifyBooking[i].bookingMin, modifyBooking[i].bookingSec);
				fprintf(temphistory, "%5s ", modifyBooking[i].TrainID);
				fprintf(temphistory, "%c ", modifyBooking[i].direction);
				fprintf(temphistory, "%d ", modifyBooking[i].departureStation);
				fprintf(temphistory, "%d ", modifyBooking[i].arrivalStation);

				fprintf(temphistory, "%02d %02d %04d ", modifyBooking[i].departureDate.day, modifyBooking[i].departureDate.month, modifyBooking[i].departureDate.year);
				fprintf(temphistory, "%d ", modifyBooking[i].quantity);
				fprintf(temphistory, "%s ", modifyBooking[i].departureTime);
				fprintf(temphistory, "%s ", modifyBooking[i].arrivalTime);

				fprintf(temphistory, "%.2f ", modifyBooking[i].totalPrice);
				fprintf(temphistory, "%s ", modifyBooking[i].paymentStatus);
				fprintf(temphistory, "%s ", modifyBooking[i].ticketStatus);


				k = 0;
				do {
					fprintf(temphistory, "%d ", modifyBooking[i].seatNo[k]);
					k++;
				} while (k < modifyBooking[i].quantity);
				fprintf(temphistory, "\n");

				//New Modify check seat
				fprintf(tempCheckSeat, "%5s ", modifyBooking[i].TrainID);
				fprintf(tempCheckSeat, "%02d %02d %04d ", modifyBooking[i].departureDate.day, modifyBooking[i].departureDate.month, modifyBooking[i].departureDate.year);
				fprintf(tempCheckSeat, "%d", modifyBooking[i].quantity);
				k = 0;
				do {
					fprintf(tempCheckSeat, " %d", modifyBooking[i].seatNo[k]);
					k++;
				} while (k < modifyBooking[i].quantity);
				fprintf(tempCheckSeat, "\n");
				printf("\n%33sModify Successful! Please check from your View Ticket Details.\n\n", " ");


			}
			else {
				//did not modify details (ForSearchPurpose.txt)

				fprintf(tempModify, "%9s ", modifyBooking[i].MemberID);
				fprintf(tempModify, "%5s ", modifyBooking[i].BookingID);
				fprintf(tempModify, "%04d-%02d-%02d %02d:%02d:%02d ",
					modifyBooking[i].year, modifyBooking[i].month, modifyBooking[i].day,
					modifyBooking[i].bookingHour, modifyBooking[i].bookingMin, modifyBooking[i].bookingSec);
				fprintf(tempModify, "%5s ", modifyBooking[i].TrainID);
				fprintf(tempModify, "%c ", modifyBooking[i].direction);
				fprintf(tempModify, "%d ", modifyBooking[i].departureStation);
				fprintf(tempModify, "%d ", modifyBooking[i].arrivalStation);

				fprintf(tempModify, "%02d %02d %04d ", modifyBooking[i].departureDate.day, modifyBooking[i].departureDate.month, modifyBooking[i].departureDate.year);
				fprintf(tempModify, "%d ", modifyBooking[i].quantity);
				fprintf(tempModify, "%s ", modifyBooking[i].departureTime);
				fprintf(tempModify, "%s ", modifyBooking[i].arrivalTime);
				fprintf(tempModify, "%.2f ", modifyBooking[i].totalPrice);
				fprintf(tempModify, "%s ", modifyBooking[i].paymentStatus);
				fprintf(tempModify, "%s ", modifyBooking[i].ticketStatus);
				k = 0;
				do {
					fprintf(tempModify, "%d ", modifyBooking[i].seatNo[k]);
					k++;
				} while (k < modifyBooking[i].quantity);
				fprintf(tempModify, "\n");

				//did not modify details (checkSeatAvailable.txt)
				fprintf(tempCheckSeat, "%5s ", modifyBooking[i].TrainID);
				fprintf(tempCheckSeat, "%02d %02d %04d ", modifyBooking[i].departureDate.day, modifyBooking[i].departureDate.month, modifyBooking[i].departureDate.year);
				fprintf(tempCheckSeat, "%d ", modifyBooking[i].quantity);
				k = 0;
				do {
					fprintf(tempCheckSeat, "%d ", modifyBooking[i].seatNo[k]);
					k++;
				} while (k < modifyBooking[i].quantity);
				fprintf(tempCheckSeat, "\n");

				//did not modify details (history)
				fprintf(temphistory, "%9s ", modifyBooking[i].MemberID);
				fprintf(temphistory, "%5s ", modifyBooking[i].BookingID);
				fprintf(temphistory, "%04d-%02d-%02d %02d:%02d:%02d ",
					modifyBooking[i].year, modifyBooking[i].month, modifyBooking[i].day,
					modifyBooking[i].bookingHour, modifyBooking[i].bookingMin, modifyBooking[i].bookingSec);
				fprintf(temphistory, "%5s ", modifyBooking[i].TrainID);
				fprintf(temphistory, "%c ", modifyBooking[i].direction);
				fprintf(temphistory, "%d ", modifyBooking[i].departureStation);
				fprintf(temphistory, "%d ", modifyBooking[i].arrivalStation);

				fprintf(temphistory, "%02d %02d %04d ", modifyBooking[i].departureDate.day, modifyBooking[i].departureDate.month, modifyBooking[i].departureDate.year);
				fprintf(temphistory, "%d ", modifyBooking[i].quantity);
				fprintf(temphistory, "%s ", modifyBooking[i].departureTime);
				fprintf(temphistory, "%s ", modifyBooking[i].arrivalTime);

				fprintf(temphistory, "%.2f ", modifyBooking[i].totalPrice);
				fprintf(temphistory, "%s ", modifyBooking[i].paymentStatus);
				fprintf(temphistory, "%s ", modifyBooking[i].ticketStatus);


				k = 0;
				do {
					fprintf(temphistory, "%d ", modifyBooking[i].seatNo[k]);
					k++;
				} while (k < modifyBooking[i].quantity);
				fprintf(temphistory, "\n");

			}
		}
		else{
			//New Modify details
			fprintf(tempModify, "%9s ", modifyBooking[i].MemberID);
			fprintf(tempModify, "%5s ", modifyBooking[i].BookingID);
			fprintf(tempModify, "%04d-%02d-%02d %02d:%02d:%02d ",
				modifyBooking[i].year, modifyBooking[i].month, modifyBooking[i].day,
				modifyBooking[i].bookingHour, modifyBooking[i].bookingMin, modifyBooking[i].bookingSec);
			fprintf(tempModify, "%5s ", modifyBooking[i].TrainID);
			fprintf(tempModify, "%c ", modifyBooking[i].direction);
			fprintf(tempModify, "%d ", modifyBooking[i].departureStation);
			fprintf(tempModify, "%d ", modifyBooking[i].arrivalStation);

			fprintf(tempModify, "%02d %02d %04d ", modifyBooking[i].departureDate.day, modifyBooking[i].departureDate.month, modifyBooking[i].departureDate.year);
			fprintf(tempModify, "%d ", modifyBooking[i].quantity);
			fprintf(tempModify, "%s ", modifyBooking[i].departureTime);
			fprintf(tempModify, "%s ", modifyBooking[i].arrivalTime);

			fprintf(tempModify, "%.2f ", modifyBooking[i].totalPrice);
			fprintf(tempModify, "%s ", modifyBooking[i].paymentStatus);
			fprintf(tempModify, "%s ", modifyBooking[i].ticketStatus);

			k = 0;
			do {
				fprintf(tempModify, "%d ", modifyBooking[i].seatNo[k]);
				k++;
			} while (k < modifyBooking[i].quantity);
			fprintf(tempModify, "\n");

			//New Modify History details
			fprintf(temphistory, "%9s ", modifyBooking[i].MemberID);
			fprintf(temphistory, "%5s ", modifyBooking[i].BookingID);
			fprintf(temphistory, "%04d-%02d-%02d %02d:%02d:%02d ",
				modifyBooking[i].year, modifyBooking[i].month, modifyBooking[i].day,
				modifyBooking[i].bookingHour, modifyBooking[i].bookingMin, modifyBooking[i].bookingSec);
			fprintf(temphistory, "%5s ", modifyBooking[i].TrainID);
			fprintf(temphistory, "%c ", modifyBooking[i].direction);
			fprintf(temphistory, "%d ", modifyBooking[i].departureStation);
			fprintf(temphistory, "%d ", modifyBooking[i].arrivalStation);

			fprintf(temphistory, "%02d %02d %04d ", modifyBooking[i].departureDate.day, modifyBooking[i].departureDate.month, modifyBooking[i].departureDate.year);
			fprintf(temphistory, "%d ", modifyBooking[i].quantity);
			fprintf(temphistory, "%s ", modifyBooking[i].departureTime);
			fprintf(temphistory, "%s ", modifyBooking[i].arrivalTime);

			fprintf(temphistory, "%.2f ", modifyBooking[i].totalPrice);
			fprintf(temphistory, "%s ", modifyBooking[i].paymentStatus);
			fprintf(temphistory, "%s ", modifyBooking[i].ticketStatus);


			k = 0;
			do {
				fprintf(temphistory, "%d ", modifyBooking[i].seatNo[k]);
				k++;
			} while (k < modifyBooking[i].quantity);
			fprintf(temphistory, "\n");

			//New Modify check seat
			fprintf(tempCheckSeat, "%5s ", modifyBooking[i].TrainID);
			fprintf(tempCheckSeat, "%02d %02d %04d ", modifyBooking[i].departureDate.day, modifyBooking[i].departureDate.month, modifyBooking[i].departureDate.year);
			fprintf(tempCheckSeat, "%d ", modifyBooking[i].quantity);
			k = 0;
			do {
				fprintf(tempCheckSeat, "%d ", modifyBooking[i].seatNo[k]);
				k++;
			} while (k < modifyBooking[i].quantity);
			fprintf(tempCheckSeat, "\n");
		}

	}


	fclose(modify);
	fclose(tempModify);
	fclose(originalCheckSeat);
	fclose(tempCheckSeat);
	fclose(originalHistory);
	fclose(temphistory);

	if(!memberIdFound){
		printf("%33sMember id %s did not make any reservation.\n", " ", memberID);
		if (!found) {
			printf("%33sBooking ID not found.\n", " ");
		}
	}

	remove("ForSearchPurpose.txt");
	rename("tempModify.txt", "ForSearchPurpose.txt");
	remove("checkSeatAvailable.txt");
	rename("tempCheckSeat.txt", "checkSeatAvailable.txt");
	remove("BookingHistory.txt");
	rename("tempHistory.txt", "BookingHistory.txt");

}

BookingHistory(char memberID[10]) {
	FILE* history;
	char ticketStatus[10];
	char destinationD[30], destinationA[30];
	bool memberIdFound = false;
	history = fopen("BookingHistory.txt", "r");
	if (history == NULL) {
		printf("Can't open the file BookingHistory.txt!");
		exit(-1);
	}

	SearchBooking searchBooking[100];

	//read bin file
	scheduleInfo northScheduleData[MAX_TRAIN];
	scheduleInfo southScheduleData[MAX_TRAIN];

	readBinFile(northScheduleData, southScheduleData);

	int countFileRow = 0;
	char c;
	while ((c = fgetc(history)) != EOF) {
		if (c == '\n') {
			countFileRow++;
		}
	}
	rewind(history);

	for (int i = 0; i < countFileRow; i++) {

		fscanf(history, "%s %s %d-%d-%d %d:%d:%d %s %c %d %d %d %d %d %d %5s %5s %f %s %s",searchBooking[i].MemberID, searchBooking[i].BookingID,
			&searchBooking[i].year, &searchBooking[i].month, &searchBooking[i].day,
			&searchBooking[i].bookingHour, &searchBooking[i].bookingMin, &searchBooking[i].bookingSec,
			searchBooking[i].TrainID, &searchBooking[i].direction, &searchBooking[i].departureStation, &searchBooking[i].arrivalStation,
			&searchBooking[i].departureDate.day, &searchBooking[i].departureDate.month, &searchBooking[i].departureDate.year,
			&searchBooking[i].quantity, searchBooking[i].departureTime, searchBooking[i].arrivalTime,
			&searchBooking[i].totalPrice, searchBooking[i].paymentStatus, searchBooking[i].ticketStatus);


		int k = 0;
		do {
			fscanf(history, " %d", &searchBooking[i].seatNo[k]);
			k++;
		} while (k < searchBooking[i].quantity);
		fscanf(history, "\n");
		if(strcmp(memberID,searchBooking[i].MemberID) == 0) {
			memberIdFound = true;
			printf("%33s=====================================================\n", " ");
			printf("%33sMember : %s\n", " ", searchBooking[i].MemberID);
			printf("%33sBooking ID : %s\n", " ", searchBooking[i].BookingID);
			printf("%33sBooking Date and Time : %04d-%02d-%02d %02d:%02d:%02d\n", " ",
				searchBooking[i].year, searchBooking[i].month, searchBooking[i].day,
				searchBooking[i].bookingHour, searchBooking[i].bookingMin, searchBooking[i].bookingSec);
			printf("%33sTrain ID : %s\n", " ", searchBooking[i].TrainID);
			if (toupper(searchBooking[i].direction) == 'S') {
				strcpy(destinationD, southScheduleData[searchBooking[i].departureStation - 1].destination);
				strcpy(destinationA, southScheduleData[searchBooking[i].arrivalStation].destination);
			}
			else {
				strcpy(destinationD, northScheduleData[searchBooking[i].departureStation - 1].destination);
				strcpy(destinationA, northScheduleData[searchBooking[i].arrivalStation].destination);
			}
			printf("%33sTrain ID : %s\n", " ", destinationD);
			printf("%33sTrain ID : %s\n", " ", destinationA);
			printf("%33sDeparture Date : %02d %02d %04d\n", " ",
				searchBooking[i].departureDate.day, searchBooking[i].departureDate.month, searchBooking[i].departureDate.year);
			printf("%33sQuantity : %d\n", " ", searchBooking[i].quantity);
			printf("%33sDeparture Time : %s\n", " ", searchBooking[i].departureTime);
			printf("%33sArrival Time : %s\n", " ", searchBooking[i].arrivalTime);

			printf("%33sTotal Price : %.2f\n", " ", searchBooking[i].totalPrice);
			printf("%33sPayment Status : %s\n", " ", searchBooking[i].paymentStatus);
			printf("%33sTicket Status : %s\n", " ", searchBooking[i].ticketStatus);

			for (int k = 0; k < searchBooking[i].quantity; ++k) {
				printf("%33sSeat Number %d: %d\n", " ", k + 1, searchBooking[i].seatNo[k]);
			}
			printf("\n");
		}
		
	}

	if (!memberIdFound) {
		printf("%33sMember ID %s did not make any reservation.\n", " ", memberID);
	}

	fclose(history);

	printf("\n\n[Enter for Back to MENU]");
	scanf("[^\n]");
	printf("\n\n");

}

char* returnDepartTime(char direction, char trainID[6], int departStation) {
	int i = 0, j = 0, k = 0;
	static char DepartTime[6];

	scheduleInfo northScheduleData[MAX_TRAIN];
	scheduleInfo southScheduleData[MAX_TRAIN];

	readBinFile(northScheduleData, southScheduleData);

	if (toupper(direction) == 'N') {
		if (strcmp(trainID, "TN1001") == 0) {
			j = 0;
		}
		else if (strcmp(trainID, "TN1002") == 0) {
			j = 1;
		}
		else if (strcmp(trainID, "TN1003") == 0) {
			j = 2;
		}
		else if (strcmp(trainID, "TN1004") == 0) {
			j = 3;
		}
		else if (strcmp(trainID, "TN1005") == 0) {
			j = 4;
		}
		else if (strcmp(trainID, "TN1006") == 0) {
			j = 5;
		}
		else if (strcmp(trainID, "TN1007") == 0) {
			j = 6;
		}
		else if (strcmp(trainID, "TN1008") == 0) {
			j = 7;
		}
		else if (strcmp(trainID, "TN1009") == 0) {
			j = 8;
		}
		else if (strcmp(trainID, "TN1010") == 0) {
			j = 9;
		}
		i = departStation - 1;

		strcpy(DepartTime, northScheduleData[i].time[j].time);

	}
	else if (toupper(direction) == 'S') {
		if (strcmp(trainID, "TS1001") == 0) {
			j = 0;
		}
		else if (strcmp(trainID, "TS1002") == 0) {
			j = 1;
		}
		else if (strcmp(trainID, "TS1003") == 0) {
			j = 2;
		}
		else if (strcmp(trainID, "TS1004") == 0) {
			j = 3;
		}
		else if (strcmp(trainID, "TS1005") == 0) {
			j = 4;
		}
		else if (strcmp(trainID, "TS1006") == 0) {
			j = 5;
		}
		else if (strcmp(trainID, "TS1007") == 0) {
			j = 6;
		}
		else if (strcmp(trainID, "TS1008") == 0) {
			j = 7;
		}
		else if (strcmp(trainID, "TS1009") == 0) {
			j = 8;
		}
		else if (strcmp(trainID, "TS1010") == 0) {
			j = 9;
		}
		i = departStation - 1;
		strcpy(DepartTime, northScheduleData[i].time[j].time);
	}
	return DepartTime;
}

char* returnArriveTime(char direction, char trainID[6], int arriveStation) {
	int i = 0, j = 0, k = 0;
	static char ArriveTime[6];
	scheduleInfo northScheduleData[MAX_TRAIN];
	scheduleInfo southScheduleData[MAX_TRAIN];

	readBinFile(northScheduleData, southScheduleData);

	if (toupper(direction) == 'N') {
		if (strcmp(trainID, "TN1001") == 0) {
			j = 0;
		}
		else if (strcmp(trainID, "TN1002") == 0) {
			j = 1;
		}
		else if (strcmp(trainID, "TN1003") == 0) {
			j = 2;
		}
		else if (strcmp(trainID, "TN1004") == 0) {
			j = 3;
		}
		else if (strcmp(trainID, "TN1005") == 0) {
			j = 4;
		}
		else if (strcmp(trainID, "TN1006") == 0) {
			j = 5;
		}
		else if (strcmp(trainID, "TN1007") == 0) {
			j = 6;
		}
		else if (strcmp(trainID, "TN1008") == 0) {
			j = 7;
		}
		else if (strcmp(trainID, "TN1009") == 0) {
			j = 8;
		}
		else if (strcmp(trainID, "TN1010") == 0) {
			j = 9;
		}
		k = arriveStation;

		strcpy(ArriveTime, northScheduleData[k].time[j].time);



	}
	else if (toupper(direction) == 'S') {
		if (strcmp(trainID, "TS1001") == 0) {
			j = 0;
		}
		else if (strcmp(trainID, "TS1002") == 0) {
			j = 1;
		}
		else if (strcmp(trainID, "TS1003") == 0) {
			j = 2;
		}
		else if (strcmp(trainID, "TS1004") == 0) {
			j = 3;
		}
		else if (strcmp(trainID, "TS1005") == 0) {
			j = 4;
		}
		else if (strcmp(trainID, "TS1006") == 0) {
			j = 5;
		}
		else if (strcmp(trainID, "TS1007") == 0) {
			j = 6;
		}
		else if (strcmp(trainID, "TS1008") == 0) {
			j = 7;
		}
		else if (strcmp(trainID, "TS1009") == 0) {
			j = 8;
		}
		else if (strcmp(trainID, "TS1010") == 0) {
			j = 9;
		}
		k = arriveStation;
		strcpy(ArriveTime, northScheduleData[k].time[j].time);
	}
	return ArriveTime;
}

float calculatePrice_Per_Seat(int DISTANCE) {
	return 8.00 * DISTANCE;
}

float calculateTotalPrice(float* pricePerSeat, int* quantity) {
	float total = (*pricePerSeat) * (*quantity);
	return total;
}

Logo() {
	printf("%s\n", " /$$$$$$$$/$$           /$$                   /$$           /$$$$$$$                      /$$       /$$                    ");
	printf("%s\n", "|__  $$__/__/          | $$                  | $$          | $$__  $$                    | $$      |__/                    ");
	printf("%s\n", "   | $$   /$$  /$$$$$$$| $$   /$$  /$$$$$$  /$$$$$$        | $$  \\ $$  /$$$$$$   /$$$$$$ | $$   /$$ /$$ /$$$$$$$   /$$$$$$ ");
	printf("%s\n", "   | $$  | $$ /$$_____/| $$  /$$/ /$$__  $$|_  $$_/        | $$$$$$$  /$$__  $$ /$$__  $$| $$  /$$/| $$| $$__  $$ /$$__  $$");
	printf("%s\n", "   | $$  | $$| $$      | $$$$$$/ | $$$$$$$$  | $$          | $$__  $$| $$  \\ $$| $$  \\ $$| $$$$$$/ | $$| $$  \\ $$| $$  \\ $$");
	printf("%s\n", "   | $$  | $$| $$      | $$_  $$ | $$_____/  | $$ /$$      | $$  \\ $$| $$  | $$| $$  | $$| $$_  $$ | $$| $$  | $$| $$  | $$");
	printf("%s\n", "   | $$  | $$|  $$$$$$$| $$ \\  $$|  $$$$$$$  |  $$$$/      | $$$$$$$/|  $$$$$$/|  $$$$$$/| $$ \\  $$| $$| $$  | $$|  $$$$$$$");
	printf("%s\n", "   |__/  |__/ \\_______/|__/  \\__/ \\_______/   \\___/        |_______/  \\______/  \\______/ |__/  \\__/|__/|__/  |__/ \\____  $$");
	printf("%s\n", "                                                                                                                  /$$  \\ $$");
	printf("%s\n", "                                                                                                                 |  $$$$$$/");
	printf("%s\n", "                                                                                                                  \\______/ ");

}

MenuDesign() {


	printf("%34s%s%20s\n", " ", "    ############################################    ", " ");
	printf("%34s%s%20s\n", " ", "   #################            #################   ", " ");
	printf("%34s%s%20s\n", " ", "  ################################################  ", " ");
	printf("%34s%s%20s\n", " ", "!!################################################!!", " ");
	printf("%34s%s%20s\n", " ", " #####========================================##### ", " ");
	printf("%34s%s%20s\n", " ", "!####|                                        |####!", " ");
	printf("%34s%s%20s\n", " ", " ####|       1. Ticket Booking                |#### ", " ");
	printf("%34s%s%20s\n", " ", "!####!                                        !####!", " ");
	printf("%34s%s%20s\n", " ", " ####!       2. View Booking Details          !#### ", " ");
	printf("%34s%s%20s\n", " ", "!####!                                        !####!", " ");
	printf("%34s%s%20s\n", " ", " ####!       3. Modify Booking                !#### ", " ");
	printf("%34s%s%20s\n", " ", "!####!                                        !####!", " ");
	printf("%34s%s%20s\n", " ", " ####!       4. All booking history           !#### ", " ");
	printf("%34s%s%20s\n", " ", "!####!                                        !####!", " ");
	printf("%34s%s%20s\n", " ", " ####|       5. Exit                          |#### ", " ");
	printf("%34s%s%20s\n", " ", "!####|                                        |####!", " ");
	printf("%34s%s%20s\n", " ", " #####========================================##### ", " ");
	printf("%34s%s%20s\n", " ", "!!################################################!!", " ");
	printf("%34s%s%20s\n", " ", " ################################################## ", " ");
	printf("%34s%s%20s\n", " ", "  ###########      ##############      ###########  ", " ");
	printf("%34s%s%20s\n", " ", "   ##########      ##############      ##########   ", " ");
	printf("%34s%s%20s\n", " ", "    ############################################    ", " ");
	printf("%34s%s%20s\n", " ", "     ##########################################     ", " ");
	printf("%34s%s%20s\n", " ", "           //                          \\\\            ", " ");
	printf("%34s%s%20s\n", " ", "      ====//============================\\\\====        ", " ");
	printf("%34s%s%20s\n", " ", "         //                              \\\\          ", " ");
	printf("%34s%s%20s\n", " ", "   =====//================================\\\\=====     ", " ");
	printf("%34s%s%20s\n", " ", "       //                                  \\\\        ", " ");
}

displayNorthSchedule() {
	char time[6];
	int i, j;

	scheduleInfo northScheduleData[MAX_TRAIN];
	scheduleInfo southScheduleData[MAX_TRAIN];

	readBinFile(northScheduleData, southScheduleData);

	printf("\n\nNorth Way Train Schedule:\n\n");
	printf("| %-20s |", "DESTINATION");
	for (int i = 0; i < MAX_TRAIN; i++)
	{
		if (strcmp(northScheduleData[i].trainID.trainId, "") != 0)
		{
			printf(" %8s |", northScheduleData[i].trainID.trainId);
		}
	}

	printf("\n--------------------------------------------------------------------------------------------------------------------------------------");
	printf("\n");
	for (int i = 0; i < MAX_TRAIN; i++)
	{
		if (strcmp(northScheduleData[i].destination, "") != 0)
		{
			printf("| %-20s |", northScheduleData[i].destination);
			for (int j = 0; j < MAX_TIME; j++)
			{
				printf(" %8s |", northScheduleData[i].time[j].time);
			}
			printf("\n");
		}
	}
	printf("\n");

}

displaySouthSchedule() {
	char time[6];
	int i, j;

	scheduleInfo northScheduleData[MAX_TRAIN];
	scheduleInfo southScheduleData[MAX_TRAIN];

	readBinFile(northScheduleData, southScheduleData);

	printf("\n\nSouth Way Train Schedule:\n\n");
	printf("| %-20s |", "DESTINATION");
	for (int i = 0; i < MAX_TRAIN; i++) {
		if (strcmp(southScheduleData[i].trainID.trainId, "") != 0) {
			printf(" %8s |", southScheduleData[i].trainID.trainId);
		}
	}
	printf("\n--------------------------------------------------------------------------------------------------------------------------------------");
	printf("\n");
	for (int i = 0; i < MAX_TRAIN; i++)
	{
		if (strcmp(southScheduleData[i].destination, "") != 0)
		{
			printf("| %-20s |", southScheduleData[i].destination);
			for (int j = 0; j < MAX_TIME; j++)
			{
				printf(" %8s |", southScheduleData[i].time[j].time);
			}
			printf("\n");
		}
	}
	printf("\n");
}

readBinFile(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]) {
	FILE* NSFile;

	NSFile = fopen("NSFile.bin", "rb");
	if (NSFile == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	for (int i = 0; i < MAX_TRAIN; i++) {
		fread(&northScheduleData[i], sizeof(scheduleInfo), 1, NSFile);
	}
	for (int i = 0; i < MAX_TRAIN; i++) {
		fread(&southScheduleData[i], sizeof(scheduleInfo), 1, NSFile);
	}
	fclose(NSFile);
}