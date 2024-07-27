#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include<time.h>
#include<math.h>
#include<stdbool.h>

#pragma warning (disable : 4996)
#pragma warning (disable : 6031)
#pragma warning (disable : 4024)
#pragma warning (disable : 6262)
#pragma warning (disable : 6054)
#pragma warning (disable : 6385)
#pragma warning (disable : 6001)
#pragma warning (disable : 6063)
#pragma warning (disable : 4098)

// staff module
#define MAX_MANAGER 3 
#define MAX_ADMIN 100
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_BLUE "\x1b[34m"
#define AC_NORMAL "\033[0m"

// member module
#define IC_LENGTH 12
#define HP_LENGTH 10
#define MAX_MEMBER 100
#define MEMBER_ID 7
#define MAX_MEMBER 100
#define CAPTCHA_LENGTH 4

// schedule module
#define MAX_TRAIN 30
#define MAX_TIME 10
#define MAX_SEATCOL 10
#define MAX_SEATROW 8

// booking module
#define MAX_TRAIN 30
#define MAX_TIME 10
#define MAX_SEAT 80

// staff module
struct Date
{
	int day;
	int month;
	int year;
};

typedef struct {
	char id[7];
	char username[51];
	char iC[51];
	char email[51];
	char gender;
	char contactNumber[51];
	char position[31];
	char password[51];
	struct Date birth;
}staffdetail;

//member module 
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

// schedule module
typedef struct {
	char trainId[7];
}train_Id;

typedef struct {
	char time[7];
}Time;

typedef struct
{
	char seat[4];
}Seat;

typedef struct
{
	train_Id trainID;
	Seat bookedSeat[10];
}checkSeat;

typedef struct
{
	train_Id trainID;
	char destination[50];
	Time time[10];
	char departureStation[50];
	char arrivalStation[50];
	int price;
}scheduleInfo;

// booking module
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


int menu();
void magnet();

// staff modu
int staffMenu();
int signinManagerMenu();
int signinAdminMenu();
int managerMenu(staffdetail admin[]);
int adminMenu(staffdetail admin[], Member members[]);
void managersignIn(staffdetail admin[]);
void adminsignin(staffdetail admin[], Member members[]);
int logOut(staffdetail admin[]);
int readFile(staffdetail admin[]);

int viewAdmin(staffdetail admin[]);
int searchAdmin(staffdetail admin[]);
int addAdmin(staffdetail admin[]);
int modifyAdmin(staffdetail admin[]);
int deleteAdmin(staffdetail admin[]);
int resetPw(staffdetail admin[], int* password);

int validationName(int* error, char username[]);
int validationIC(int* error, char ic[]);
int validationEmail(int* error, char email[]);
int compareEmail(staffdetail admin[], int* error, char email[], int* cmpEmail, int* sameIndex);
int validationGender(int* error, char gender[]);
int validationContactNumber(int* error, char cNumber[]);
int validationPosition(int* error, char position[]);
int hidePW(char pw[]);
int validationPw(int* error, char pw[]);
int validationbirthdate(int* error, int day[], int month[], int year[]);
int validationID(int* error, char id[]);
int validationselect(int* error, char ans);
void errorMessage(int e);

// member module
void toUpperCase(char* str);
void loadMembers(Member members[], int* memberCount);
void saveMembers(Member members[], int* memberCount);
void appendMember(Member newMember);
int allDigit(const char* str);
void getEmail(const char* email);
int validEmail(const char* email);
void modifyPassword(Member members[], int memberCount);
void forgotandFind(Member members[], int memberCount);
void deleteAccount(Member members[], int* memberCount);
void memberRegister(Member members[], int* memberCount);
void staff_maintain_member(Member members[], int memberCount);
void searchMember(Member member[], int memberCount);
void staff_maintain_menu(Member members[], staffdetail admin[]);
int bookandtrain(char memberID[]);
void memberLogin(Member members[], int memberCount);
void memberMenu(Member members[], int memberCount);
void member();

// schedule module
//function declaration for validation check;
bool isValidTimeFormat(const char* time);
int isValidDestination(const char* destination);
bool isSameDestination(const scheduleInfo scheduleData[], int scheduleCount, const char* destination);
int validateStations(const char* departure, const char* arrival, const scheduleInfo* scheduleData);
int findValue(const char(*arr)[MAX_SEATROW], int size, const char* value);
int validateTrainID(const char* trainID);

//function declaration for write and read file
void writeData();
int readData(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]);

//function declaration for display schedule
void viewNorthSouthSchedule(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]);
void displayNorthSchedule(scheduleInfo northScheduleData[]);
void displaySouthSchedule(scheduleInfo southScheduleData[]);

//function declaration for search schedule
void search(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]);
void displayAllSchedule(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]);

//function declaration for edit schedule
void addSchedule(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]);
void modifySchedule(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]);
void deleteSchedule(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]);

//function declaration for check seat
void checkSeatAvailability_n();
void checkSeatAvailability_s();

//for member and staff function
int TrainSchedulingMainForMember(char memberID[]);
int TrainSchedulingMainForStaff(staffdetail admin[], Member members[]);


// booking module
void mainMenu(char memberID[]);
int generateRandom(int, int);
void BookingTicket(char memberID[]);
void SearchBookedTicket(char memberID[]);
void displayE_Ticket(char memberID[]);
void CancelBooking(char memberID[], char bookingID[]);
void ModifyFunction(char memberID[], char bookingID[]);
void BookingHistory(char memberID[]);
float calculatePrice_Per_Seat(int DISTANCE);
float calculateTotalPrice(float* pricePerSeat, int* quantity);
char* PaymentStatus(int);
char* returnDepartTime(char direction, char trainID[6], int departStation);
char* returnArriveTime(char direction, char trainID[6], int arriveStation);
void Logo();
void MenuDesign();
void displayNorthSchedule1();
void displaySouthSchedule1();
void readBinFile(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]);


void main() {
	magnet();
	menu();
	system("pause");
}

//menu
int menu() {
	system("cls");
	int mode;
	printf(" \t\t __  __          _____ _   _ ______ _____ _____ _____    _____ ____      _   _____ _   _ \n");
	printf(" \t\t|  \\/  |   /\\   / ____| \\ | |  ____|_   _|_   _/ ____|  |_   _|  _ \\    / \\ |__ __| \\ | |\n");
	printf(" \t\t| \\  / |  /  \\ | |  __|  \\| | |__    | |   | || |         | | | |_) |  / _ \\  | | |  \\| |\n");
	printf(" \t\t| |\\/| | / /\\ \\| | |_ | . ` |  __|   | |   | || |         | | |  _ <  / ___ \\ | | | . ` |\n");
	printf(" \t\t| |  | |/ ____ \\ |__| | |\\  | |____  | |  _| || |____     | | | | \\ \\/ /   \\ \\| |_| |\\  |\n");
	printf(" \t\t|_|  |_/_/    \\_\\_____|_| \\_|______| |_| |_____\\_____|    |_| |_|  \\/_/     \\_\\___|_| \\_|\n");
	do {

		printf("\t\t\t\t============================================\n");
		printf("\t\t\t\t=           TRAIN SYSTEM                   =\n");
		printf("\t\t\t\t============================================\n");
		printf("\t\t\t\t=                                          =\n");
		printf("\t\t\t\t=            1.Staff                       =\n");
		printf("\t\t\t\t=            2.Member                      =\n");
		printf("\t\t\t\t=            3.schedule                    =\n");
		printf("\t\t\t\t=            4.Booking                     =\n");
		printf("\t\t\t\t=            5.Exit                        =\n");
		printf("\t\t\t\t=                                          =\n");
		printf("\t\t\t\t============================================\n\n");

		printf("\t\t Enter your mode number:");
		rewind(stdin);
		scanf("%d", &mode);

		switch (mode)
		{
		case 1:
			staffMenu();
			break;
		case 2:
			member();
			break;
		case 3:
			member();
			break;
		case 4:
			member();
			break;
		case 5:
			printf("\t\t\t\t\t %sExiting the system. Goodbye!%s\n", AC_GREEN, AC_NORMAL);
			exit(0);
			break;
		default:
			printf("\t\t\t\t %sInvalid choice. Please select (1-5).%s\n", AC_RED, AC_NORMAL);
			break;
		}
	} while (mode != 5);
}

void magnet()
{
	int i, j;
	for (i = 0; i < 30; ++i) { // Move the train 30 times
		system("cls");
		for (j = 0; j < i; j++) {
			printf(" ");
		}
		printf("___________   _______________________________________^__ \n");
		for (j = 0; j < i; j++) {
			printf(" ");
		}
		printf(" ___   ___ |||  ___   ___   ___    ___ ___  |   __  ,----\\ \n");
		for (j = 0; j < i; j++) {
			printf(" ");
		}
		printf("|   | |   |||| |   | |   | |   |  |   |   | |  |  | |_____\\ \n");
		for (j = 0; j < i; j++) {
			printf(" ");
		}
		printf("|___| |___|||| |___| |___| |___|  | O | O | |  |  |        \\ \n");
		for (j = 0; j < i; j++) {
			printf(" ");
		}
		printf("           |||                    |___|___| |  |__|         )\n");
		for (j = 0; j < i; j++) {
			printf(" ");
		}
		printf("___________|||______________________________|______________/ \n");
		for (j = 0; j < i; j++) {
			printf(" ");
		}
		printf("           |||                                        /-------- \n");
		for (j = 0; j < i; j++) {
			printf(" ");
		}
		printf("-----------'''---------------------------------------'\n");
		printf("\n");
		Sleep(80); // Sleep for 100 milliseconds (0.08 seconds)
	}
	printf(" \t\t __  __          _____ _   _ ______ _____ _____ _____    _____ ____      _   _____ _   _ \n");
	Sleep(100);
	printf(" \t\t|  \\/  |   /\\   / ____| \\ | |  ____|_   _|_   _/ ____|  |_   _|  _ \\    / \\ |__ __| \\ | |\n");
	Sleep(100);
	printf(" \t\t| \\  / |  /  \\ | |  __|  \\| | |__    | |   | || |         | | | |_) |  / _ \\  | | |  \\| |\n");
	Sleep(100);
	printf(" \t\t| |\\/| | / /\\ \\| | |_ | . ` |  __|   | |   | || |         | | |  _ <  / ___ \\ | | | . ` |\n");
	Sleep(100);
	printf(" \t\t| |  | |/ ____ \\ |__| | |\\  | |____  | |  _| || |____     | | | | \\ \\/ /   \\ \\| |_| |\\  |\n");
	Sleep(100);
	printf(" \t\t|_|  |_/_/    \\_\\_____|_| \\_|______| |_| |_____\\_____|    |_| |_|  \\/_/     \\_\\___|_| \\_|\n");
	Sleep(100);

	printf("\n\n\n\t\t\t\t\t\t%sWELCOME TO MAGNETIC!!!!%s\n\n", AC_GREEN, AC_NORMAL);
	Sleep(3000);
}

// staff module

int staffMenu() {
	int choose;
	//system("cls");

	do {
		printf("\t\t\t\t============================================\n");
		printf("\t\t\t\t=                                          =\n");
		printf("\t\t\t\t=              1. Manager                  =\n");
		printf("\t\t\t\t=              2. Admin                    =\n");
		printf("\t\t\t\t=              3. back                     =\n");
		printf("\t\t\t\t=                                          =\n");
		printf("\t\t\t\t============================================\n");

		printf("\t\t Enter your mode number:");
		rewind(stdin);
		scanf("%d", &choose);

		switch (choose)
		{
		case 1:
			signinManagerMenu();
			break;
		case 2:
			signinAdminMenu();
			break;
		case 3:
			return menu();
			break;
		default:
			printf("\t\t\t\t%sInvalid choice. Please select (1-3).%s\n", AC_RED, AC_NORMAL);
			break;
		}
	} while (choose != 3);
}

int signinManagerMenu() {
	staffdetail admin[MAX_ADMIN];
	int choose, password;
	do {
		printf("\t\t\t\t============================================\n");
		printf("\t\t\t\t=                                          =\n");
		printf("\t\t\t\t=              1. Login                    =\n");
		printf("\t\t\t\t=              2. back                     =\n");
		printf("\t\t\t\t=                                          =\n");
		printf("\t\t\t\t============================================\n");

		printf("\t\tEnter your mode number:");
		rewind(stdin);
		scanf("%d", &choose);

		switch (choose)
		{
		case 1:
			managersignIn(admin);
			break;
		case 2:
			return staffMenu();
			break;
		default:
			printf("\t\t\t\t%sInvalid choice. Please select (1-2).%s\n", AC_RED, AC_NORMAL);
			break;
		}
	} while (choose != 3);
}

int signinAdminMenu() {
	staffdetail admin[MAX_ADMIN];
	Member members[MAX_MEMBER];
	int choose, password;
	do {
		//system("cls");
		printf("\t\t\t\t============================================\n");
		printf("\t\t\t\t=                                          =\n");
		printf("\t\t\t\t=              1. Login                    =\n");
		printf("\t\t\t\t=              2. forgot password          =\n");
		printf("\t\t\t\t=              3. back                     =\n");
		printf("\t\t\t\t=                                          =\n");
		printf("\t\t\t\t============================================\n");

		printf("\t\tEnter your mode number:");
		rewind(stdin);
		scanf("%d", &choose);

		switch (choose)
		{
		case 1:
			adminsignin(admin, members);
			break;
		case 2:
			resetPw(admin, &password);
			break;
		case 3:
			return staffMenu();
			break;
		default:
			printf("\t\t\t\t %sInvalid choice. Please select (1-3).%s\n", AC_RED, AC_NORMAL);
			break;
		}
	} while (choose != 3);
}

int managerMenu(staffdetail admin[]) {

	int select;
	do {
		printf("\t\t\t\t============================================\n");
		printf("\t\t\t\t=          StaffAdmin Information          =\n");
		printf("\t\t\t\t============================================\n");
		printf("\t\t\t\t=                                          =\n");
		printf("\t\t\t\t=            1.View Admin                  =\n");
		printf("\t\t\t\t=            2.Searh Admin                 =\n");
		printf("\t\t\t\t=            3.Add Admin                   =\n");
		printf("\t\t\t\t=            4.Modify Admin                =\n");
		printf("\t\t\t\t=            5.Delete Admin                =\n");
		printf("\t\t\t\t=            6.LogOut                      =\n");
		printf("\t\t\t\t=                                          =\n");
		printf("\t\t\t\t============================================\n\n");


		printf("\t\t Enter your Selection: ");
		rewind(stdin);
		scanf("%d", &select);

		switch (select)
		{
		case 1:
			viewAdmin(admin);
			break;
		case 2:
			searchAdmin(admin);
			break;
		case 3:
			addAdmin(admin);
			break;
		case 4:
			modifyAdmin(admin);
			break;
		case 5:
			deleteAdmin(admin);
			break;
		case 6:
			logOut(admin);
			break;
		default:
			printf("\t\t\t\t%s Invalid choice. Please select (1-6).%s\n", AC_RED, AC_NORMAL);
			break;
		}
	} while (select != 1 && select != 2 && select != 3 && select != 4 && select != 5 && select != 6);
}

int adminMenu(staffdetail admin[], Member members[]) {
	int select;
	do {
		printf("\t\t\t\t============================================\n");
		printf("\t\t\t\t=                                          =\n");
		printf("\t\t\t\t=            1.Member Information          =\n");
		printf("\t\t\t\t=            2.Schedule Information        =\n");
		printf("\t\t\t\t=            3.LogOut                      =\n");
		printf("\t\t\t\t=                                          =\n");
		printf("\t\t\t\t============================================\n\n");

		printf("\t\t Enter your Selection: ");
		rewind(stdin);
		scanf("%d", &select);

		switch (select)
		{
		case 1:
			staff_maintain_menu(admin, members);
			break;
		case 2:
			TrainSchedulingMainForStaff(admin, members);
			break;
		case 3:
			logOut(admin);
			break;
		default:
			printf("\t\t\t\t%s Invalid choice. Please select (1-3).%s\n", AC_RED, AC_NORMAL);
			break;
		}
	} while (select != 1 && select != 2 && select != 3);
}

// manager signin
void managersignIn(staffdetail admin[]) {
	system("cls");
	int lastIndex = readFile(admin);
	staffdetail manager[MAX_MANAGER];
	FILE* fstaffdetail;
	char id[51];
	int error, found = 0;
	char password[51];
	int validOption, loginSuccess = 0;
	fstaffdetail = fopen("staffmanager.txt", "r");
	if (fstaffdetail == NULL) {
		printf("\t\tUnable to open file");
		exit(-1);
	}
	while (fscanf(fstaffdetail, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%02d-%02d-%04d\n", &manager[lastIndex].id, &manager[lastIndex].username, &manager[lastIndex].iC, &manager[lastIndex].email, &manager[lastIndex].gender, &manager[lastIndex].contactNumber, &manager[lastIndex].position, &manager[lastIndex].password, &manager[lastIndex].birth.day, &manager[lastIndex].birth.month, &manager[lastIndex].birth.year) != EOF) {
		lastIndex++;
	}
	fclose(fstaffdetail);

	printf("\t\t\t\t============================================\n");
	printf("\t\t\t\t=                  LOGIN                   =\n");
	printf("\t\t\t\t============================================\n\n");
	do {
		error = 0;
		printf("\t\tEnter Manager ID:");
		rewind(stdin);
		scanf("%[^\n]", &id);
		validationID(&error, id);

	} while (error == 1);

	do {
		error = 0;
		printf("\t\tEnter Password:");
		rewind(stdin);
		/*	scanf("%[^\n]", &password);*/
		hidePW(password);
		validationPw(&error, password);

	} while (error == 1);

	for (int i = 0;i < lastIndex;i++) {
		//check validation
		if (strcmp(id, manager[i].id) == 0) {
			if (strcmp(password, manager[i].password) == 0) {
				system("cls");
				printf("\n\t\t\t\t\t\t%sLogin successfuly !!!%s", AC_GREEN, AC_NORMAL);
				printf("\n\t\t\t\t\t\t%sWelcome!%s%s\n\n", AC_BLUE, manager[i].username, AC_NORMAL);
				found = 1;
				managerMenu(admin);
			}
		}
	}
	if (found == 0) {
		errorMessage(16);
	}

}

// admin signin
void adminsignin(staffdetail admin[], Member members[]) {
	system("cls");
	FILE* fstaffdetail;
	int error, loginCount = 0, pw;
	int validOption, loginSuccess = 0;
	char id[51];
	char password[51];
	char option;
	int lastIndex = readFile(admin);
	printf("\t\t\t\t============================================\n");
	printf("\t\t\t\t=                  LOGIN                   =\n");
	printf("\t\t\t\t============================================\n\n");
	do {
		do {
			error = 0;
			printf("\t\tEnter Admin ID:");
			rewind(stdin);
			scanf("%[^\n]", &id);
			validationID(&error, id);

		} while (error == 1);

		do {
			error = 0;
			printf("\t\tEnter Password:");
			rewind(stdin);
			//scanf("%[^\n]", &password);
			hidePW(password);
			validationPw(&error, password);

		} while (error == 1);

		for (int i = 0;i < lastIndex;i++) {
			//check validation
			if (strcmp(id, admin[i].id) == 0) {
				if (strcmp(password, admin[i].password) == 0) {
					printf("\n\t\t\t\t\t\t%sLogin successfuly !!!%s", AC_GREEN, AC_NORMAL);
					printf("\n\t\t\t\t\t\t%sWelcome!%s%s\n", AC_BLUE, admin[i].username, AC_NORMAL);
					loginSuccess = 1;
					adminMenu(admin, members);
				}
			}
		}
		if (loginSuccess == 0) {
			printf("\n\t\t\t\t%s Your ID or password is wrong, try again!%s\n\n", AC_RED, AC_NORMAL);
			loginCount++;
		}

		if (loginCount >= 2) {
			do {
				printf("\n\t\t Forgot password ? (Y/N) >");
				rewind(stdin);
				scanf("%c", &option);
				option = toupper(option);

				if (option == 'Y') {
					resetPw(admin, &pw);
					if (pw == 1) {
						loginCount = 0;
					}
					validOption = 0;
				}
				else {
					validOption = 2;
				}
			} while (validOption == -1);
		}
	} while (loginSuccess != 1);
}

// logout
int logOut(staffdetail admin[]) {
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t============================================\n");
	printf("\t\t\t\t=          LogOut Staff                    =\n");
	printf("\t\t\t\t============================================\n");

	printf("\n\t\t\t\t\t\t%sLogOut successfuly !!!%s\n", AC_GREEN, AC_NORMAL);
	return staffMenu();
}

// readfile admin
int readFile(staffdetail admin[]) {
	FILE* fstaffdetail;
	int lastIndex = 0, current;
	fstaffdetail = fopen("staffadmin.txt", "r");
	staffdetail edit;
	if (fstaffdetail == NULL)
	{
		printf("\t\tUnable to open the file\n");
		exit(-1);
	}
	while (fscanf(fstaffdetail, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%02d-%02d-%04d\n", &admin[lastIndex].id, &admin[lastIndex].username, &admin[lastIndex].iC, &admin[lastIndex].email, &admin[lastIndex].gender, &admin[lastIndex].contactNumber, &admin[lastIndex].position, &admin[lastIndex].password, &admin[lastIndex].birth.day, &admin[lastIndex].birth.month, &admin[lastIndex].birth.year) != EOF) {
		lastIndex++;
	}
	fclose(fstaffdetail);

	return lastIndex;
}

// forgot password
int resetPw(staffdetail admin[], int* password) {
	FILE* fstaffdetail;
	int lastIndex, current;
	lastIndex = readFile(admin);
	staffdetail change;
	int error, found;
	char newPw[21], confirm[21], changePw, email[51];

	printf("\t\t\t\t============================================\n");
	printf("\t\t\t\t=                CHANGE PASSWORD           =\n");
	printf("\t\t\t\t============================================\n\n");
	do {
		error = 0;
		printf("\t\t Enter Admin ID:");
		rewind(stdin);
		scanf("%[^\n]", &change.id);
		validationID(&error, change.id);

	} while (error == 1);
	found = 0;
	for (int i = 0;i < lastIndex; i++) {
		if (strcmp(change.id, admin[i].id) == 0) {
			current = i;
			found = 1;
			do {
				error = 0;
				printf("\t\t Do you want change password? (Y/N): ");
				rewind(stdin);
				scanf("%c", &changePw);
				changePw = toupper(changePw);

				if (changePw != 'Y' && changePw != 'N') {
					error = 1;
				}
			} while (error == 1);

			if (changePw == 'Y') {
				printf("%65s\n", "Security Question");
				printf("\t\t\t\t============================================\n");
				do {
					error = 0;
					printf("\t\t Enter Staff E-mail:");
					rewind(stdin);
					scanf("%s", &email);
					validationEmail(&error, email);

					if (strcmp(email, admin[current].email) == 0) {
						do {
							error = 0;
							printf("\t\t Enter new password:");
							rewind(stdin);
							//scanf("%[^\n]", &newPw);
							hidePW(newPw);
							validationPw(&error, newPw);

						} while (error == 1);

						do {
							error = 0;
							printf("\t\t Enter confirm password:");
							rewind(stdin);
							//scanf("%[^\n]", &confirm);
							hidePW(confirm);
							validationPw(&error, confirm);

						} while (error == 1);

						if (strcmp(newPw, confirm) == 0) {
							strcpy(admin[current].id, admin[current].id);
							strcpy(admin[current].username, admin[current].username);
							strcpy(admin[current].iC, admin[current].iC);
							strcpy(admin[current].email, admin[current].email);
							admin[current].gender = admin[current].gender;
							strcpy(admin[current].contactNumber, admin[current].contactNumber);
							strcpy(admin[current].position, admin[current].position);
							strcpy(admin[current].password, newPw);
							admin[current].birth.day = admin[current].birth.day;
							admin[current].birth.month = admin[current].birth.month;
							admin[current].birth.year = admin[current].birth.year;
							*password = 1;
						}
						else {
							errorMessage(15);
							error = 1;
						}
					}
					else {
						printf("\t\t\t%sEmail invalid,please enter valid email%s\n", AC_RED, AC_NORMAL);
						error = 1;
					}
				} while (error == 1);
			}
			else {
				*password = 0;
				found = 0;
			}
		}
	}
	if (found != 1) {
		printf("\t\t\t\t\t\t%sdata not found%s\n", AC_RED, AC_NORMAL);
	}
	else if (found == 1) {
		printf("\n\t\t\t\t\t%sPassword Changed successfuly !!!%s\n", AC_GREEN, AC_NORMAL);
		printf("\n\t\t\t\t\t%sPlease Log in Again%s\n", AC_BLUE, AC_NORMAL);

		fstaffdetail = fopen("staffadmin.txt", "w");
		if (fstaffdetail == NULL) {
			printf("\t\tUnable to open file");
			exit(-1);
		}

		for (int i = 0;i < lastIndex;i++) {
			fprintf(fstaffdetail, "%s|%s|%s|%s|%c|%s|%s|%s|%02d-%02d-%04d\n", admin[i].id, admin[i].username, admin[i].iC, admin[i].email, admin[i].gender, admin[i].contactNumber, admin[i].position, admin[i].password, admin[i].birth.day, admin[i].birth.month, admin[i].birth.year);
		}
		fclose(fstaffdetail);
	}
}

// view admin
int viewAdmin(staffdetail admin[]) {
	FILE* fstaffdetail;
	int lastIndex = readFile(admin);
	int count = 0;

	system("cls");
	printf("%65s\n", "View Admin Information");
	printf("%s\n", "========================================================================================================================");
	printf("%-7s %-15s %-15s %-25s %-7s %-13s %-20s %s\n", "StaffID", "Name", "IC", "Email", "Gender", "Position", "ContactNumber", "Birthdate");
	printf("%s\n", "========================================================================================================================");

	for (int i = 0;i < lastIndex;i++) {
		printf("%-7s %-15s %-15s %-25s %-7c %-13s %-20s %02d-%02d-%04d\n", admin[i].id, admin[i].username, admin[i].iC, admin[i].email, admin[i].gender, admin[i].position, admin[i].contactNumber, admin[i].birth.day, admin[i].birth.month, admin[i].birth.year);
		count++;
	}
	printf("%s\n", "========================================================================================================================");
	printf("\n%65s %d\n\n", "Total admin is", count);
	return managerMenu(admin);
}

// search admin
int searchAdmin(staffdetail admin[]) {
	FILE* fstaffdetail;
	char name[51];
	char gender;
	int lastIndex = readFile(admin);
	int count = 0;
	int error, found;
	printf("\t\t\t\t============================================\n");
	printf("\t\t\t\t=        Search Admin Information          =\n");
	printf("\t\t\t\t============================================\n");

	do {
		error = 0;
		printf("\t\t Enter Admin name:");
		rewind(stdin);
		scanf("%[^\n]", &name);
		validationName(&error, name);

	} while (error == 1);

	do {
		error = 0;
		printf("\t\t Enter Admin Gender:");
		rewind(stdin);
		scanf("%c", &gender);
		validationGender(&error, gender);

	} while (error == 1);
	system("cls");
	printf("%65s\n", "Search Admin Information");
	printf("%s\n", "========================================================================================================================");
	printf("%-7s %-15s %-15s %-25s %-7s %-13s %-20s %s\n", "staffID", "Name", "IC", "Email", "Gender", "Position", "ContactNumber", "Birthdate");
	printf("%s\n", "========================================================================================================================");
	found = 0;
	for (int i = 0;i < lastIndex;i++) {
		if (strcmp(name, admin[i].username) == 0) {
			if (gender == admin[i].gender) {
				printf("%-7s %-15s %-15s %-25s %-7c %-13s %-20s %02d-%02d-%04d\n", admin[i].id, admin[i].username, admin[i].iC, admin[i].email, admin[i].gender, admin[i].position, admin[i].contactNumber, admin[i].birth.day, admin[i].birth.month, admin[i].birth.year);
				count++;
				found = 1;
			}
		}
	}
	if (found == 1) {
		printf("%s\n", "========================================================================================================================");
		printf("\n%65s %d\n\n", "Total record is", count);
	}
	else {
		errorMessage(17);
	}
	return managerMenu(admin);
}

// add admin
int addAdmin(staffdetail admin[]) {
	FILE* fstaffdetail;
	int lastIndex = readFile(admin);
	int count = 0;
	int cmpIC, cmpEmail, sameIndex;
	int id;
	char idNo[7], ans;
	int error;
	int index;
	staffdetail add;
	system("cls");
	printf("\t\t\t\t============================================\n");
	printf("\t\t\t\t=          Add Admin Information           =\n");
	printf("\t\t\t\t============================================\n");
	count += lastIndex;
	printf("\n\t\t\t\t%sNow Admin Information record have %d !!!%s\n\n", AC_YELLOW, count, AC_NORMAL);
	do {
		do {
			error = 0;
			if (count < MAX_ADMIN) {
				printf("\t\t Add Admin ? (Y = Yes)(N = No):");
				rewind(stdin);
				scanf("%c", &ans);
				validationselect(&error, ans);
			}
			else {
				printf("\n\t\t\t\t%sAdmin record is maximum,record must be 100 only%s\n\n", AC_RED, AC_NORMAL);
				return managerMenu(admin);
			}
		} while (error == 1);
		if (toupper(ans) == 'Y') {
			// Name
			do {
				error = 0;
				printf("\t\t Enter Staff Username:");
				rewind(stdin);
				scanf("%[^\n]", &add.username);
				validationName(&error, add.username);

			} while (error == 1);

			// IC
			do {
				error = 0;
				printf("\t\t Enter Staff IC:");
				rewind(stdin);
				scanf("%s", &add.iC);
				validationIC(&error, add.iC);

			} while (error == 1);

			// Email
			do {
				error = 0;
				printf("\t\t Enter Staff E-mail:");
				rewind(stdin);
				scanf("%s", &add.email);
				validationEmail(&error, add.email);
				compareEmail(admin, &error, add.email, &cmpEmail, &sameIndex);
				if (error == 1) {
					errorMessage(20);
				}

			} while (error == 1);

			// Gender
			do {
				error = 0;
				printf("\t\t Enter Staff Gender[F/M]:");
				rewind(stdin);
				scanf("%c", &add.gender);
				validationGender(&error, add.gender);

			} while (error == 1);

			// contact number
			do {
				error = 0;
				printf("\t\t Enter Staff Contact Number[012-3456789]:");
				rewind(stdin);
				scanf("%s", &add.contactNumber);
				validationContactNumber(&error, add.contactNumber);

			} while (error == 1);

			// position
			do {
				error = 0;
				printf("\t\t Enter Staff position:");
				rewind(stdin);
				scanf("%[^\n]", &add.position);
				validationPosition(&error, add.position);

			} while (error == 1 || error == 2);

			// password
			do {
				error = 0;
				printf("\t\t Enter Staff Password[8-15 alphabets or numbers]:");
				rewind(stdin);
				hidePW(add.password);
				validationPw(&error, add.password);

			} while (error == 1);

			// Date
			do {
				error = 0;
				printf("\t\t Enter birthday[dd-mm-yyyy] :");
				rewind(stdin);
				scanf(" %02d-%02d-%04d", &add.birth.day, &add.birth.month, &add.birth.year);
				validationbirthdate(&error, add.birth.day, add.birth.month, add.birth.year);

			} while (error == 1);
			//generate id
			index = lastIndex - 1;
			sscanf(admin[index].id, "%[^0-9]%d", &admin[lastIndex].id, &id);
			id++;
			// turn integer id to string idNo
			itoa(id, idNo, 10);
			//strcat(admin[lastIndex].id, idNo);
			printf("\n\t\t\t\t\t%sNew id is %s%s\n", AC_YELLOW, strcat(admin[lastIndex].id, idNo), AC_NORMAL);
			//strcpy(admin[lastIndex].id = admin[lastIndex].id);
			strcpy(admin[lastIndex].username, add.username);
			strcpy(admin[lastIndex].iC, add.iC);
			strcpy(admin[lastIndex].email, add.email);
			admin[lastIndex].gender = add.gender;
			strcpy(admin[lastIndex].contactNumber, add.contactNumber);
			strcpy(admin[lastIndex].position, add.position);
			strcpy(admin[lastIndex].password, add.password);
			admin[lastIndex].birth.day = add.birth.day;
			admin[lastIndex].birth.month = add.birth.month;
			admin[lastIndex].birth.year = add.birth.year;
			fstaffdetail = fopen("staffadmin.txt", "a");
			fprintf(fstaffdetail, "%s|%s|%s|%s|%c|%s|%s|%s|%02d-%02d-%04d\n", admin[lastIndex].id, admin[lastIndex].username, admin[lastIndex].iC, admin[lastIndex].email, admin[lastIndex].gender, admin[lastIndex].contactNumber, admin[lastIndex].position, admin[lastIndex].password, admin[lastIndex].birth.day, admin[lastIndex].birth.month, admin[lastIndex].birth.year);
			lastIndex++;
			fclose(fstaffdetail);

			//system("cls");
			printf("\t\t\t\t\t%sAdd in successfully !%s\n", AC_GREEN, AC_NORMAL);
			printf("\t\t\t\t\t%sPlease go to sign in !%s\n\n", AC_BLUE, AC_NORMAL);
		}
		else {

			return managerMenu(admin);
		}
	} while (toupper(ans) == 'Y');
	return managerMenu(admin);
}

// modify admin
int modifyAdmin(staffdetail admin[]) {
	FILE* fstaffdetail;
	int lastIndex = readFile(admin);
	int current;
	int found;
	int cmpIC, cmpEmail, sameIndex;
	char editId[7], ans;
	int error;
	staffdetail edit;
	int check;
	system("cls");
	printf("\t\t\t\t============================================\n");
	printf("\t\t\t\t=          Modify Admin Information        =\n");
	printf("\t\t\t\t============================================\n");
	do {
		do {
			check = 0;
			do {
				error = 0;
				printf("\t\tEnter Admin ID:");
				rewind(stdin);
				scanf("%[^\n]", &editId);
				validationID(&error, editId);
			} while (error == 1);

			printf("%65s\n", "Modify Admin Information");
			printf("%s\n", "========================================================================================================================");
			printf("%-7s %-15s %-15s %-25s %-7s %-13s %-20s %s\n", "StaffID", "Name", "IC", "Email", "Gender", "Position", "ContactNumber", "Birthdate");
			printf("%s\n", "========================================================================================================================");

			for (current = 0;current < lastIndex;current++) {
				if (strcmp(editId, admin[current].id) == 0) {
					printf("%-7s %-15s %-15s %-25s %-7c %-13s %-20s %02d-%02d-%04d\n", admin[current].id, admin[current].username, admin[current].iC, admin[current].email, admin[current].gender, admin[current].position, admin[current].contactNumber, admin[current].birth.day, admin[current].birth.month, admin[current].birth.year);

					do {
						error = 0;
						printf("\n\t\t Enter Staff Username:");
						rewind(stdin);
						scanf("%[^\n]", &edit.username);
						validationName(&error, edit.username);

					} while (error == 1);

					do {
						error = 0;
						printf("\t\t Enter Staff IC:");
						rewind(stdin);
						scanf("%s", &edit.iC);
						validationIC(&error, edit.iC);

					} while (error == 1);

					do {
						error = 0;
						printf("\t\t Enter Staff E-mail:");
						rewind(stdin);
						scanf("%s", &edit.email);
						validationEmail(&error, edit.email);
						compareEmail(admin, &error, edit.email, &cmpEmail, &sameIndex);
						if (sameIndex == current) {
							cmpEmail = 0;
							error = 0;
						}
					} while (cmpEmail != 0 || error == 1);

					do {
						error = 0;
						printf("\t\t Enter Staff Gender[F/M]:");
						rewind(stdin);
						scanf("%c", &edit.gender);
						validationGender(&error, edit.gender);

					} while (error == 1);

					do {
						error = 0;
						printf("\t\t Enter Staff Contact Number[012-3456789]:");
						rewind(stdin);
						scanf("%s", &edit.contactNumber);
						validationContactNumber(&error, edit.contactNumber);

					} while (error == 1);

					do {
						error = 0;
						printf("\t\t Enter Staff position:");
						rewind(stdin);
						scanf("%[^\n]", &edit.position);
						validationPosition(&error, edit.position);

					} while (error == 1);

					do {
						error = 0;
						printf("\t\t Enter birthday[dd-mm-yyyy] :");
						rewind(stdin);
						scanf(" %02d-%02d-%04d", &edit.birth.day, &edit.birth.month, &edit.birth.year);
						validationbirthdate(&error, edit.birth.day, edit.birth.month, edit.birth.year);

					} while (error == 1);

					strcpy(admin[current].id, editId);
					strcpy(admin[current].username, edit.username);
					strcpy(admin[current].iC, edit.iC);
					strcpy(admin[current].email, edit.email);
					admin[current].gender = edit.gender;
					strcpy(admin[current].contactNumber, edit.contactNumber);
					strcpy(admin[current].position, edit.position);
					admin[current].birth.day = edit.birth.day;
					admin[current].birth.month = edit.birth.month;
					admin[current].birth.year = edit.birth.year;

					printf("\n");
					printf("%s\n", "========================================================================================================================");
					printf("%-7s %-15s %-15s %-25s %-7s %-13s %-20s %s\n", "StaffID", "Name", "IC", "Email", "Gender", "Position", "ContactNumber", "Birthdate");
					printf("%s\n", "========================================================================================================================");

					printf("%-7s %-15s %-15s %-25s %-7c %-13s %-20s %02d-%02d-%04d\n", admin[current].id, admin[current].username, admin[current].iC, admin[current].email, admin[current].gender, admin[current].position, admin[current].contactNumber, admin[current].birth.day, admin[current].birth.month, admin[current].birth.year);
					check++;
				}
			}
			if (check != 1) {
				printf("\n%s %65s %s\n", AC_RED, "Invalid Id,No record found", AC_NORMAL);
			}
			do {
				error = 0;
				printf("\n\t\t Any more record to modify ? (Y = Yes)(N = No):");
				rewind(stdin);
				scanf("%c", &ans);
				validationselect(&error, ans);
				system("cls");
			} while (error == 1);
		} while (toupper(ans) == 'Y');
	} while (check == 0);


	fstaffdetail = fopen("staffadmin.txt", "w");
	if (fstaffdetail == NULL)
	{
		printf("\t\tUnable to open the file\n");
		exit(-1);
	}
	for (int i = 0;i < lastIndex;i++) {
		fprintf(fstaffdetail, "%s|%s|%s|%s|%c|%s|%s|%s|%02d-%02d-%04d\n", admin[i].id, admin[i].username, admin[i].iC, admin[i].email, admin[i].gender, admin[i].contactNumber, admin[i].position, admin[i].password, admin[i].birth.day, admin[i].birth.month, admin[i].birth.year);
	}
	fclose(fstaffdetail);
	printf("\t\t\t\t\t\t%sEdit in successfully !%s\n\n", AC_GREEN, AC_NORMAL);
	return managerMenu(admin);
}

// delete admin
int deleteAdmin(staffdetail admin[]) {
	int lastIndex = readFile(admin);
	int error, check, current;
	char confirmYesNo;
	staffdetail deleteData;
	FILE* fstaffdetail;
	system("cls");
	check = 0;
	do {
		do {
			error = 0;
			printf("\t\t Enter Admin ID:");
			rewind(stdin);
			scanf("%[^\n]", &deleteData.id);
			validationID(&error, deleteData.id);

		} while (error == 1);

		for (int i = 0;i < lastIndex;i++) {
			if (strcmp(deleteData.id, admin[i].id) == 0) {
				printf("\t\t----------------------------------------------------------------------\n");
				printf("\t\t-                             Confirmation:                          -\n");
				printf("\t\t----------------------------------------------------------------------\n");

				printf("%s\n", "========================================================================================================================");
				printf("%-7s %-15s %-15s %-25s %-7s %-13s %-20s %s\n", "StaffID", "Name", "IC", "Email", "Gender", "Position", "ContactNumber", "Birthdate");
				printf("%s\n", "========================================================================================================================");

				printf("%-7s %-15s %-15s %-25s %-7c %-13s %-20s %02d-%02d-%04d\n", admin[i].id, admin[i].username, admin[i].iC, admin[i].email, admin[i].gender, admin[i].position, admin[i].contactNumber, admin[i].birth.day, admin[i].birth.month, admin[i].birth.year);
				current = i;
				check = 1;
			}
		}
		if (check != 1) {
			printf("\t\t\t\t\t\t%sInvalid ID %s\n", AC_RED, AC_NORMAL);
		}
		else {
			do {
				error = 0;
				printf("\t\tConfirm Delete? (Y/N): ");
				rewind(stdin);
				scanf("%c", &confirmYesNo);
				confirmYesNo = toupper(confirmYesNo);

				if (confirmYesNo != 'Y' && confirmYesNo != 'N') {
					error = 1;
				}
				if (confirmYesNo == 'Y') {
					for (int i = current;i < lastIndex - 1;i++) {
						admin[i] = admin[i + 1];
					}
					lastIndex--;
					printf("\n\t\t\t\t\t\t%sDelete successfuly !!!%s\n", AC_GREEN, AC_NORMAL);
				}
				else {
					system("cls");
					printf("\n");
					return managerMenu(admin);
				}
				if (error == 1) {
					errorMessage(1);
				}
			} while (error == 1);
		}

	} while (check == 0);
	FILE* deleteAdmin;
	deleteAdmin = fopen("staffadmin.txt", "w");
	if (deleteAdmin == NULL) {
		printf("\t\tUnable to open file");
		exit(-1);
	}
	for (int i = 0;i < lastIndex;i++) {
		fprintf(deleteAdmin, "%s|%s|%s|%s|%c|%s|%s|%s|%02d-%02d-%04d\n", admin[i].id, admin[i].username, admin[i].iC, admin[i].email, admin[i].gender, admin[i].contactNumber, admin[i].position, admin[i].password, admin[i].birth.day, admin[i].birth.month, admin[i].birth.year);
	}
	fclose(deleteAdmin);
	return managerMenu(admin);
}

// validation check  Name
int validationName(int* error, char username[]) {
	*error = 0;
	int countlength = strlen(username);

	for (int i = 0;i < countlength;i++) {
		if (!isalpha(username[i]) && !isspace(username[i])) {
			*error = 1;
		}
	}

	if (*error != 0) {
		errorMessage(1);
	}
	return *error;
}

// validation check ic
int validationIC(int* error, char ic[]) {
	*error = 0;
	int countlength = strlen(ic);
	for (int i = 0;i < countlength;i++) {
		if (!isdigit(ic[i])) {
			*error = 1;
		}
	}
	if (*error != 0) {
		errorMessage(2);
	}
	return *error;
}

// validation check email
int validationEmail(int* error, char email[]) {
	int at_count = 0, dot_count = 0;
	*error = 0;
	//validation check of '@' and '.'
	int countlength = strlen(email);
	for (int i = 0; i < countlength; i++) {
		if (email[i] == '@') {
			at_count++;
		}
		else if (email[i] == '.') {
			dot_count++;;
		}
	}
	if (at_count != 1 || dot_count != 1) {
		*error = 1;
	}
	if (*error != 0) {
		errorMessage(3);
	}
	return *error;
}

// compare email
int compareEmail(staffdetail admin[], int* error, char email[], int* cmpEmail, int* sameIndex) {
	int lastIndex = readFile(admin);
	int emailSame = 0;
	for (int i = 0;i < lastIndex;i++) {
		if (strcmp(email, admin[i].email) == 0) {
			emailSame = 1;
			*error = 1;
			*sameIndex = i;
		}
	}

	if (emailSame == 1) {
		*cmpEmail = 1;
	}
	else {
		*cmpEmail = 0;
	}
	return *error;
}

// validation check Gender
int validationGender(int* error, char gender[]) {
	*error = 0;

	if (toupper(gender != 'F') && toupper(gender != 'M')) {
		*error = 1;
	}
	if (*error != 0) {
		errorMessage(4);
	}
	return *error;
}

// validation check contact number
int validationContactNumber(int* error, char cNumber[]) {
	*error = 0;
	int i;
	int countlength = strlen(cNumber);
	if (countlength < 11 || countlength > 12) {
		errorMessage(5);
		*error = 1;
	}
	if (cNumber[3] != '-') {
		errorMessage(6);
		*error = 1;
	}

	for (i = 0;i < 3;i++) {
		if (!isdigit(cNumber[i])) {
			*error = 1;
		}
	}

	for (i = 4;i < countlength;i++) {
		if (!isdigit(cNumber[i])) {
			*error = 1;
		}
	}
	for (i = 0;i < countlength;i++) {
		if (isspace(cNumber[i])) {
			*error = 1;
		}
	}
	if (*error != 0) {
		errorMessage(7);
	}
	return *error;
}

// validation check position 
int validationPosition(int* error, char position[]) {
	*error = 0;

	int countlength = strlen(position);
	if (strcmp(position, "Manager") == 0 || strcmp(position, "manager") == 0) {
		*error = 2;
	}

	for (int i = 0;i < countlength; i++) {
		if (!isalpha(position[i])) {
			*error = 1;
		}
	}
	if (*error == 1) {
		errorMessage(8);
	}
	else if (*error == 2) {
		errorMessage(19);
	}
	return *error;
}

// validation check password
int validationPw(int* error, char pw[]) {
	*error = 0;
	int countlength = strlen(pw);
	if (countlength < 8 || countlength > 15) {
		*error = 1;
	}
	if (*error != 0) {
		errorMessage(9);
	}
	return *error;
}

int hidePW(char pw[]) {
	int i = 0;
	char ch;

	rewind(stdin);
	while ((ch = getch())) {
		// Check for backspace
		if (ch == 8) {
			if (i > 0) {
				i--;
				pw[i] = '\0';
				printf("\b \b");
			}
		}
		// Check for Enter key
		else if (ch == '\r' || ch == '\n') {
			pw[i] = '\0';
			printf("\n");
			// Return the length of the password
			return i;
		}
		else {
			pw[i] = ch;
			i++;
			printf("*");
		}
	}
	return i;
}

// validation check birthdate
int validationbirthdate(int* error, int day[], int month[], int year[]) {

	time_t seconds = time(NULL);
	struct Date* current_time = localtime(&seconds);

	SYSTEMTIME t;
	GetLocalTime(&t);

	*error = 0;
	if (day <= 0 || day > 31) {
		errorMessage(12);
		*error = 1;
	}

	if (month <= 0 || month > 12) {
		errorMessage(13);
		*error = 1;
	}

	int currentYear = t.wYear;
	int y = year;
	int age = currentYear - y;

	if (age < 18 || age > 60) {
		errorMessage(14);
		*error = 1;
	}
	return *error;
}

// validation check ID
int validationID(int* error, char id[]) {
	*error = 0;
	int countlength = strlen(id);
	for (int i = 0;i < 2;i++) {
		if (!isalpha(id[i])) {
			if (!isupper(id[i])) {
				*error = 1;
				errorMessage(10);
			}
		}
	}

	for (int i = 2;i < countlength;i++) {
		if (!isdigit(id[i]) && isspace(id[i])) {
			*error = 1;
		}
	}
	if (*error == 1) {
		errorMessage(11);
	}
	return *error;
}

int validationselect(int* error, char ans) {
	*error = 0;
	if (toupper(ans != 'Y') && toupper(ans != 'N')) {
		*error = 1;
	}
	if (*error == 1) {
		errorMessage(18);
	}
	return *error;
}

// error msg for validation check 
void errorMessage(int e) {
	int error = e;
	switch (error)
	{
	case 1:
		printf("\t\t%s Invalid Name,Name must be in character.%s\n", AC_RED, AC_NORMAL);
		break;
	case 2:
		printf("\t\t%s Invalid IC,IC number must be digit.%s\n", AC_RED, AC_NORMAL);
		break;
	case 3:
		printf("\t\t%s Invalid Email,Email must be between '@' and '.'.%s\n", AC_RED, AC_NORMAL);
		break;
	case 4:
		printf("\t\t%s Invalid Gender,Gender must be 'F' or 'M'.%s\n", AC_RED, AC_NORMAL);
		break;
	case 5:
		printf("\t\t%s Contact number must be in 11 t0 12 numbers.%s\n", AC_RED, AC_NORMAL);
		break;
	case 6:
		printf("\t\t%s Missing character '-'.%s\n", AC_RED, AC_NORMAL);
		break;
	case 7:
		printf("\t\t%s Contact number must be in format '012-3456789'.%s\n", AC_RED, AC_NORMAL);
		break;
	case 8:
		printf("\t\t%s Invalid position,Position must be in character\n %s", AC_RED, AC_NORMAL);
		break;
	case 9:
		printf("\t\t%s Invalid Password,Password must be consist of 8 to 12 alphabets and numbers.%s\n", AC_RED, AC_NORMAL);
		break;
	case 10:
		printf("\t\t%s Invalid ID,First character of ID must be uppercase alphabet %s.\n", AC_RED, AC_NORMAL);
		break;
	case 11:
		printf("\t\t%s StaffAdmin ID must be in format 'AD1001'%s\n", AC_RED, AC_NORMAL);
		break;
	case 12:
		printf("\t\t%s Invalid day. Day must be 1 to 31.%s\n", AC_RED, AC_NORMAL);
		break;
	case 13:
		printf("\t\t%s Invalid month. Month must be 1 to 12.%s\n", AC_RED, AC_NORMAL);
		break;
	case 14:
		printf("\t\t%s Invalid year.%s\n", AC_RED, AC_NORMAL);
		break;
	case 15:
		printf("\t\t%s Password are not same.%s\n", AC_RED, AC_NORMAL);
		break;
	case 16:
		printf("\n\t\t\t\t%sYour ID or password is wrong, try again!%s\n\n", AC_RED, AC_NORMAL);
		break;
	case 17:
		printf("\n\t\t\t\t\t\t%s No record !!!%s\n\n", AC_RED, AC_NORMAL);
		break;
	case 18:
		printf("\n\t\t\t\t%s Invalid,please select Y = (Yes) or N = (No)%s\n", AC_RED, AC_NORMAL);
		break;
	case 19:
		printf("\t\t%s Invalid,cannot type Manager position !!!%s\n", AC_RED, AC_NORMAL);
		break;
	case 20:
		printf("\t\t%s Invalid Email,The email have same data %s.\n", AC_RED, AC_NORMAL);
		break;
	default:
		break;
	}
}



// member module

//转string大写
void toUpperCase(char* str)
{
	while (*str)
	{
		*str = toupper((unsigned char)*str);
		str++;
	}
}

//read file array
void loadMembers(Member members[], int* memberCount)
{

	FILE* loadFile = fopen("final.dat", "rb");
	if (loadFile == NULL) {
		printf("\t\t\t\033[0;32mNo member registered, please ask user to register an account\033[0m\n\n");
		return;
	}

	(*memberCount) = 0;

	while (fread(&members[*memberCount], sizeof(Member), 1, loadFile))
	{
		(*memberCount)++;

	}
	fclose(loadFile);
}

void saveMembers(Member members[], int* memberCount)
{

	FILE* saveFile = fopen("final.dat", "wb");
	if (saveFile == NULL)
	{
		printf("\t\tError opening file");
		return;
	}

	for (int i = 0; i < memberCount; i++)
	{
		fwrite(&members[i], sizeof(Member), 1, saveFile);
	}

	fclose(saveFile);
}

//ADD new member(add)
void appendMember(Member newMember)
{
	FILE* appendFile = fopen("final.dat", "ab");
	if (appendFile == NULL)
	{
		printf("\t\tError opening file");
		return;
	}

	fwrite(&newMember, sizeof(Member), 1, appendFile);

	fclose(appendFile);
}

//check the string is all number
int allDigit(const char* str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (!isdigit(str[i]))
		{
			return 0;
		}
	}

	return 1;
}

//get user email
void getEmail(const char* email)
{
	int valid = 0;

	while (!valid)
	{
		printf("\t\tEnter your email:");
		scanf("\t\t%29s", email);
		rewind(stdin);

		if (validEmail(email))
		{
			valid = 1;
		}
		else
		{
			printf("\t\tInvalid Email Format, Please Try Again (Invalid Format: \033[0;33mXXX@gmail.com)\033[0m\n");
		}

	}
}

//email format check
int validEmail(const char* email)
{
	int atCount = 0;//@
	int dotCount = 0;//.
	int lenEmail = strlen(email);

	if (!isalpha(email[0]))
	{
		printf("\t\tFirst character should be letter\n");
		return 0;
	}

	for (int i = 0; i < lenEmail; i++)
	{
		char c = email[i];

		if (c == '@')
		{
			atCount++;
		}
		else if (c == '.')
		{
			dotCount++;
		}

		if (!isalnum(c) && c != '.' && c != '@')
		{
			return 0;
		}

	}

	if (atCount != 1 || dotCount < 1 || email[lenEmail - 1] == '.' || email[lenEmail - 1] == '@')
	{
		return 0;
	}

	const char* gmailCheck = "@gmail.com";
	const char* emailCheck = email + lenEmail - strlen(gmailCheck);

	if (strcmp(emailCheck, gmailCheck) != 0)
	{
		return 0;
	}

	return 1;
}

//reset password(modify)
void modifyPassword(Member members[], int memberCount)//会中毒
{
	Member input_reset_password;
	int found = 0;
	char newPassword[20] = { 0 };

	printf("\t\tPlease enter your Member ID:");
	scanf("%19s", input_reset_password.memberId);
	toUpperCase(input_reset_password.memberId);
	rewind(stdin);

	printf("\t\tPlease enter your IC Number:");
	scanf("%13s", input_reset_password.IC);
	rewind(stdin);

	for (int i = 0; i < memberCount; i++)
	{
		if (strcmp(members[i].memberId, input_reset_password.memberId) == 0 && strcmp(members[i].IC, input_reset_password.IC) == 0)
		{
			printf("\t\tMember ID and IC Number verified. You can enter your new password now\n");
			printf("\t\tPlease enter your new password:");
			scanf("%20s", newPassword);

			strcpy(members[i].password, newPassword);
			printf("\t\tYour Account Password reset successfully!\n");
			found = 1;

		}
	}

	if (!found)
	{
		printf("\t\tMember not exists, please try again\n");
	}
	else
	{
		saveMembers(members, memberCount);
	}


}

void forgotandFind(Member members[], int memberCount)
{
	Member forgot;
	int found = 0;
	char verifEmail[30] = { 0 };
	int attemp = 0;

	while (attemp < 3 && !found) {
		printf("\t\tEnter Your IC Number:");
		scanf("%13s", forgot.IC);
		rewind(stdin);

		for (int i = 0; i < memberCount; i++) {
			if (strcmp(members[i].IC, forgot.IC) == 0) {
				found = 1;
				printf("\n\t\tMember found! Please enter your binding email to get back your password\n");
				printf("\t\tYour binding email:");
				scanf("%29s", verifEmail);
				rewind(stdin);

				if (strcmp(members[i].email, verifEmail) == 0) {
					char randomCaptcha[CAPTCHA_LENGTH + 1];
					const char* captchaChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

					srand(time(NULL));  // Ensure random seed for captcha generation
					for (int j = 0; j < CAPTCHA_LENGTH; j++) {
						int numC = rand() % 62;
						randomCaptcha[j] = captchaChars[numC];
					}
					randomCaptcha[CAPTCHA_LENGTH] = '\0';

					char userCaptcha[CAPTCHA_LENGTH + 1] = { 0 };
					printf("\t\tPlease enter the captcha code to complete the progress: \033[0;33m%s\033[0m\n", randomCaptcha);
					printf("\t\tPlease enter the generated captcha:");
					do {
						scanf("%4s", userCaptcha);
						rewind(stdin);

						if (strcmp(randomCaptcha, userCaptcha) == 0) {
							printf("\t\tCaptcha verified successfully!\n");
							printf("\t\tOur HONORABLE Member, your account password is \033[0;33m%s\033[0m\n", members[i].password);
							return;  // End function after successful password recovery
						}
						else {
							printf("\t\tIncorrect Captcha, please try again\n");
						}
					} while (strcmp(randomCaptcha, userCaptcha) != 0);
				}
				else {
					printf("\t\tEmail not correct! Security system active\n");
					exit(0);
				}
			}
		}

		if (!found) {
			printf("\t\tInvalid IC, Member not found!\n");
			attemp++;
		}
	}

	if (attemp >= 3 && !found) {
		printf("\t\tTry Attempt exceed limit. Please try later\n");
		exit(0);
	}
}

void deleteAccount(Member members[], int* memberCount)
{
	Member inputDelete;
	int deleteConfirm;
	int found = 0;

	printf("\t\tEnter the Member ID of the account you want to delete:");
	scanf("%19s", inputDelete.memberId);
	toUpperCase(inputDelete.memberId);
	rewind(stdin);

	printf("\t\tEnter the password of the account you want to delete\033[0;33m(Please check if the letter is in uppercase or lowercase):\033[0m");
	scanf("%19s", inputDelete.password);
	rewind(stdin);


	int index = 0;
	int memCount = memberCount;
	for (int i = 0; i < memCount; i++)
	{
		if (strcmp(members[i].memberId, inputDelete.memberId) == 0 && strcmp(members[i].password, inputDelete.password) == 0) {
			index = i;
			found = 1;
			memCount--;

		}
	}

	for (int i = index; i < memCount; i++)
	{
		members[i] = members[i + 1];
	}


	memberCount = memCount;

	if (!found)
	{
		printf("\t\tAccount not found or incorrect password.\n");
	}
	else
	{


		do
		{
			printf("\t\t\033[0;31mConfirm to delete your account? This will eliminate all your data!!\033[0m\n");
			printf("\t\tConfirm enter 1\n");
			printf("\t\tEXIT enter 2\n");
			printf("\t\tPlease enter your option:");
			scanf("%d", &deleteConfirm);
			rewind(stdin);

			switch (deleteConfirm)
			{
			case 1:

				saveMembers(members, memberCount);
				printf("\t\tYour account has been deleted\n");

			case 2:
				exit(0);
				break;
			default:
				printf("\t\tInvalid option, please try again");
				break;
			}

		} while (deleteConfirm < 1 || deleteConfirm > 2);


	}
}

//this is whole member register program (SYSTEM 1)
void memberRegister(Member members[], int* memberCount)
{
	printf("\t\t\t\t=======================================\n");
	printf("\t\t\t\t||                                   ||\n");
	printf("\t\t\t\t||        MEMBER REGISTATION         ||\n");
	printf("\t\t\t\t||                                   ||\n");
	printf("\t\t\t\t=======================================\n\n");


	if (*memberCount > MAX_MEMBER)
	{
		printf("\t\t\tMember limit reached, cannot register more members.\n");
		return;
	}

	Member* newMember = &members[*memberCount];

	int validName;
	do
	{
		validName = 1;
		int i = 0;

		printf("\t\tEnter Your Account Username:");
		scanf("%49s", newMember->name);
		rewind(stdin);

		while (newMember->name[i] != '\0' && validName)
		{
			if (!isalpha(newMember->name[i]))
			{
				validName = 0;
				system("cls");
				printf("\t\tInvalid Symbol Exist, Please try again\n");

			}
			i++;
		}



	} while (validName == 0);

	int passwordMatch = 0;
	while (!passwordMatch)
	{
		char tempPassword[15] = { 0 };
		printf("\t\tEnter Your Password (min 8 character):");
		scanf("%19s", tempPassword);
		rewind(stdin);

		if (strlen(tempPassword) >= 8)
		{
			printf("\t\t\033[0;33mRe-Enter Your Password:\033[0m");
			scanf("%19s", newMember->rePassword);
			rewind(stdin);

			if (strcmp(tempPassword, newMember->rePassword) == 0)
			{
				strcpy(newMember->password, tempPassword);
				passwordMatch = 1;
			}
			else
			{
				printf("\t\tThe Password not match, Please enter again!\n");
			}
		}
		else
		{
			printf("\t\tYour password too short, please enter at least 8 character\n");
		}



	}

	int validGender = 0;
	while (!validGender)
	{
		printf("\t\tEnter Your Gender(F/M/O):");
		scanf(" %c", &newMember->gender);
		rewind(stdin);
		newMember->gender = toupper(newMember->gender);

		if (newMember->gender == 'F' || newMember->gender == 'M' || newMember->gender == 'O')
		{
			validGender = 1;
		}
		else
		{
			printf("\t\tInvalid Gender, Please Enter M(Male) or F(Female) or O(Other)\n");
		}
	}

	int validIC = 0;
	while (!validIC)
	{
		printf("\t\tEnter Your IC/MyKad Number:");
		scanf("%13s", newMember->IC);
		rewind(stdin);

		int uniIC = 1;

		for (int i = 0; i < *memberCount; i++)
		{
			if (strcmp(members[i].IC, newMember->IC) == 0)
			{
				uniIC = 0;

			}
		}

		if (uniIC && (strlen(newMember->IC) == IC_LENGTH && allDigit(newMember->IC)))
		{
			validIC = 1;
		}
		else
		{
			if (!uniIC)
			{
				printf("\t\tThis IC Number has been registered, please try another IC Number");
			}
			else
			{
				printf("\t\tInvalid IC/MyKad Number. It should be 12 digits longs and does not contain symbol\n");
			}


		}
	}

	int validHP = 0;
	while (!validHP)
	{
		printf("\t\tEnter Contact/HP Number:");
		scanf("%10s", newMember->contact_number);
		rewind(stdin);

		if (strlen(newMember->contact_number) == HP_LENGTH && allDigit(newMember->contact_number))
		{
			if (newMember->contact_number[0] == '0' && newMember->contact_number[1] == '1')
			{
				validHP = 1;
			}
			else
			{
				printf("\t\tInvalid Contact Number format. It should start with '01'\n");
			}
		}
		else
		{
			printf("\t\tInvalid Hand-Phone Number. It should be 10 digits longs and does not contain symbol\n");
		}
	}

	getEmail(newMember->email);


	//generate ID
	const char* prefix = "M";
	char randomNumber[MEMBER_ID + 1];

	int num = rand() % 100000;
	int i = MEMBER_ID - 2;
	for (;i >= 0; i--)
	{
		randomNumber[i] = '0' + num % 10;
		num = num / 10;
	}

	randomNumber[MEMBER_ID - 1] = '\0';

	strcpy(newMember->memberId, prefix);
	strcat(newMember->memberId, randomNumber);


	char randomCaptcha[CAPTCHA_LENGTH + 1];
	const char* captchaChar = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyxz0123456789";

	for (int i = 0; i < CAPTCHA_LENGTH; i++)
	{
		int numC = rand() % 62;
		randomCaptcha[i] = captchaChar[numC];
	}
	randomCaptcha[CAPTCHA_LENGTH] = '\0';

	char userCaptcha[CAPTCHA_LENGTH + 1] = { 0 };
	int validCaptcha = 0;
	printf("\n\t\tPlease enter the captcha code to complete the registration: \033[0;33m%s\033[0m\n\n", randomCaptcha);
	printf("\t\tPlease enter the generated captcha:");
	while (!validCaptcha)
	{
		if (scanf("%4s", userCaptcha) != 1)
		{
			rewind(stdin);
			printf("\t\tInvalid input, please try again");
		}
		else
		{
			if (strcmp(randomCaptcha, userCaptcha) == 0)
			{
				validCaptcha = 1;
				system("cls");
				printf("\t\tCaptcha verificate successfully!\n");
			}
			else
			{
				printf("\t\tIncorrect Captcha, please try again\n");
			}
		}

	}

	if (validCaptcha)
	{
		printf("\t\tRegistration Completed. Welcome, %s. Your member ID is \033[38;5;46m%s\033[0m\n", newMember->name, newMember->memberId);
		appendMember(*newMember);
		(*memberCount)++;

	}




}

// display member information
void staff_maintain_member(Member members[], int memberCount)
{

	if (memberCount == 0)
	{
		printf("\n\t\tNo Member Registered\n");
		return;

	}


	printf("\n");
	printf("\n\t---------------------------------------| Registered Member |---------------------------------------\n\n");
	printf("\t%-20s %-20s %-10s %-20s %-15s\n", "Member ID", "Member Name", "Gender", "Contact Number", "Email");
	printf("\t---------------------------------------------------------------------------------------------------\n\n");

	for (int i = 0; i < memberCount; i++)
	{
		printf("\t%-20s %-20s %-10c %-20s %-15s\n\n\n", members[i].memberId, members[i].name, members[i].gender, members[i].contact_number, members[i].email);
	}

}

void searchMember(Member members[], int memberCount)
{

	char searchName[30];
	int found = 0;

	printf("\t\tEnter a user name: ");
	scanf("%29s", searchName);

	for (int i = 0; i < memberCount; i++)
	{
		if (strcmp(searchName, members[i].name) == 0)
		{
			if (!found)
			{
				printf("\t\tMembers found:\n");
				found = 1;
			}
			printf("\t\t-----------------------------\n");
			printf("\t\tMember ID: %s\n", members[i].memberId);
			printf("\t\tName: %s\n", members[i].name);
			printf("\t\tGender: %c\n", members[i].gender);
			printf("\t\tContact Number: %s\n", members[i].contact_number);
			printf("\t\tEmail: %s\n\n", members[i].email);
		}
	}

	if (!found)
	{
		printf("\t\tNo members found with the name '%s'.\n", searchName);
	}
}

void staff_maintain_menu(Member members[], staffdetail admin[])//这个是用来check 注册过的member的信息的
{
	int memberCount = 0;
	loadMembers(members, &memberCount);
	int staff_maintain_option;

	do
	{
		printf("\t\t\t\t==========================================\n");
		printf("\t\t\t\t||                                      ||\n");
		printf("\t\t\t\t||      Staff Maintain Member Menu      ||\n");
		printf("\t\t\t\t||                                      ||\n");
		printf("\t\t\t\t==========================================\n");
		printf("\t\t\t\t||                                      ||\n");
		printf("\t\t\t\t||  1.Display Member information        ||\n");
		printf("\t\t\t\t||  2.Search Member                     ||\n");
		printf("\t\t\t\t||  3.Back To Menu                      ||\n");
		printf("\t\t\t\t||                                      ||\n");
		printf("\t\t\t\t==========================================\n\n");
		printf("\t\tEnter you choice:");
		if (scanf("%d", &staff_maintain_option) != 1)
		{
			rewind(stdin);
			printf("\t\tInvalid Option, Please enter again\n");
			staff_maintain_option = -1;
		}
		else
		{
			rewind(stdin);
			switch (staff_maintain_option)
			{
			case 1:
				staff_maintain_member(members, memberCount);
				break;
			case 2:
				searchMember(members, memberCount);
				break;
			case 3:
				adminMenu(admin, members);
			default:
				printf("\t\tInvalid Option, Please enter again\n");
			}


		}

	} while (staff_maintain_option != 0);
}

int bookandtrain(char memberID[])
{

	system("cls");
	int bookAndTrain;
	do
	{
		printf("\t\t\t\t===================================================\n");
		printf("\t\t\t\t||                                               ||\n");
		printf("\t\t\t\t||         1.Book Your Favourite Ticket Now      ||\n");
		printf("\t\t\t\t||         2.Train Schedule                      ||\n");
		printf("\t\t\t\t||         0.Exit                                ||\n");
		printf("\t\t\t\t||                                               ||\n");
		printf("\t\t\t\t===================================================\n\n");

		printf("\t\tEnter Your Option:");
		if (scanf("%d", &bookAndTrain) != 1)
		{
			rewind(stdin);
			printf("\t\tInvalid Option, Please enter again\n");
			bookAndTrain = -1;
		}
		else
		{
			rewind(stdin);
		}

		switch (bookAndTrain)
		{
		case 1:
			mainMenu(memberID);
			break;
		case 2:
			TrainSchedulingMainForMember(memberID);
			break;
		case 0:
			exit(0);
		default:
			printf("\t\tInvalid Option, please enter again\n");

		}bookAndTrain = 0;




		//go to book\schedule section
	} while (bookAndTrain < 1 || bookAndTrain > 2);
}

//void staffManage(Member members[])
//{
//	int memberCount = 0;
//	loadMembers(members, memberCount);
//	int staffOption;
//	do
//	{
//		printf("\t\t\t\t==========================================\n");
//		printf("\t\t\t\t||                                      ||\n");
//		printf("\t\t\t\t||  1.Member Information                ||\n");
//		printf("\t\t\t\t||  2.Schedule Information              ||\n");
//		printf("\t\t\t\t||  3.Back                              ||\n");
//		printf("\t\t\t\t||                                      ||\n");
//		printf("\t\t\t\t==========================================\n\n");
//		printf("\t\tEnter your option:");
//		scanf("%d", &staffOption);
//		rewind(stdin);
//
//		switch (staffOption)
//		{
//		case 1:
//			staff_maintain_menu(members, memberCount);
//			break;
//		case 2:
//			//yl schedule
//			break;
//		case 3:
//			memberMenu(members, memberCount);
//			break;
//		}
//
//
//	} while (staffOption < 1 || staffOption > 3);
//	
//}

//this is whole login part(search)
void memberLogin(Member members[], int memberCount)
{
	Member inputLogin;
	int foundPassword = 0;
	int foundMember = 0;
	int attempMember = 0;
	int attempPassword = 0;


	printf("\t\t\t\t===========================================================================\n");
	printf("\t\t\t\t||                                                                       ||\n");
	printf("\t\t\t\t||                  Login to Your Registered Account                     ||\n");
	printf("\t\t\t\t||                                                                       ||\n");
	printf("\t\t\t\t===========================================================================\n\n");

	while (attempMember < 3 && !foundMember)
	{
		printf("\t\tEnter your Account Member ID:");
		if (scanf("%20s", inputLogin.memberId) != 1)
		{
			rewind(stdin);
			printf("\t\tInvalid input, please try again\n");
		}
		else
		{
			rewind(stdin);
			toUpperCase(inputLogin.memberId);

			foundMember = 0;
			for (int i = 0; i < memberCount; i++)
			{
				if (strcmp(members[i].memberId, inputLogin.memberId) == 0)
				{
					foundMember = 1;
					printf("\n\t\tMember Found!\n\n");

					while (true)
					{
						if (attempPassword < 3 && !foundPassword)
						{
							printf("\t\tEnter your account Password \033[0;33m(Please check if the letter is in uppercase or lowercase):\033[0m");
							if (scanf("%20s", inputLogin.password) != 1)
							{
								rewind(stdin);
								printf("\t\tInvalid input, please try again\n");
								attempMember++;
								attempPassword++;

							}
							else
							{
								rewind(stdin);

								if (strcmp(members[i].password, inputLogin.password) == 0)
								{
									printf("\t\tLogin Successfully.Welcome, Our HONORABLE member, %s!\n", members[i].name);
									foundPassword = 1;
									bookandtrain(members[i].memberId);
								}
								else
								{
									printf("\t\tInvalid Password, please enter again\n");
									attempPassword++;


								}

								if (attempPassword >= 3)
								{
									printf("\n\t\tAttempt Limit exceed, please try later\n");
									exit(0);
								}
							}
						}
					}
					return -1;
				}
			}
		}
		if (!foundMember)
		{
			printf("\t\tInvalid Member, please try again\n");
			attempMember++;

		}

		if (attempMember >= 3)
		{
			printf("\n\t\tAttempt Limit exceed, please try later\n");
			exit(0);
		}
	}
}

//this is home page for member information module(主页)
void memberMenu(Member members[], int memberCount)
{
	int memberOption;

	do
	{
		printf("\t\t\t\t================================================\n");
		printf("\t\t\t\t||                                            ||\n");
		printf("\t\t\t\t||            MEMBER INFORMATION              ||\n");
		printf("\t\t\t\t||                                            ||\n");
		printf("\t\t\t\t================================================\n");
		printf("\t\t\t\t||                                            ||\n");
		printf("\t\t\t\t||  1.Register an new account                 ||\n");//add
		printf("\t\t\t\t||  2.Login Account                           ||\n");//search
		printf("\t\t\t\t||  3.Forgot and Find password                ||\n");//search
		printf("\t\t\t\t||  4.Modify Password                         ||\n");// modify
		printf("\t\t\t\t||  5.Delete your account                     ||\n");// modify
		printf("\t\t\t\t||  6.Back                                    ||\n");
		printf("\t\t\t\t||                                            ||\n");
		printf("\t\t\t\t================================================\n");
		printf("\n");
		printf("\t\tEnter your option(1-6)\n");
		printf("\t\tYour Option:");
		if (scanf("%d", &memberOption) != 1)
		{
			rewind(stdin);
			system("cls");
			printf("\t\t\t\t\033[38;5;196mInvalid Option, Please try Again\033[0m\n\n");
			memberOption = -1;
		}
		else
		{
			rewind(stdin);
			switch (memberOption)
			{
			case 1:
				memberRegister(members, &memberCount);
				break;
			case 2:
				memberLogin(members, memberCount);
				break;
			case 3:
				forgotandFind(members, memberCount);
				break;
			case 4:
				modifyPassword(members, memberCount);
				break;
			case 5:
				deleteAccount(members, memberCount);
				break;
			case 6:
				return menu();
				break;
			default:
				system("cls");
				printf("\t\t\t\t\033[38;5;196mInvalid Option, Please try Again\033[0m\n\n");
				break;
			}

		}memberOption = 0;

	} while (memberOption < 1 || memberOption > 5);

}

void member()
{
	Member member[MAX_MEMBER];
	int memberCount = 0;
	srand(time(NULL));

	loadMembers(member, &memberCount);

	memberMenu(member, memberCount);
}

// schedule Module

int TrainSchedulingMainForMember(char memberID[]) {
	int choice;
	scheduleInfo northScheduleData[MAX_TRAIN];
	scheduleInfo southScheduleData[MAX_TRAIN];
	scheduleInfo scheduleData[MAX_TRAIN];

	//close this when the file exist at your PC
		// writeData();
	readData(northScheduleData, southScheduleData);

	do
	{
		printf("\n************************************\n");
		printf("1. North Schedule\n");
		printf("2. South Schedule\n");
		printf("3. Display all schedule\n");
		printf("4. Search for more details\n");
		printf("5. Back\n");
		printf("************************************\n");
		printf("Enter your choice (1-5): ");

		if (scanf("%d", &choice) != 1)
		{
			printf("Invalid input. Please enter a number.\n");
			while (getchar() != '\n');

		}
		else if (choice < 1 || choice > 5)
		{
			printf("Invalid choice. Please enter a number between 1 and 8.\n");
		}
		else
		{
			switch (choice) {
			case 1:
				displayNorthSchedule(northScheduleData);
				break;
			case 2:
				displaySouthSchedule(southScheduleData);
				break;
			case 3:
				displayAllSchedule(northScheduleData, southScheduleData);
				break;
			case 4:
				search(northScheduleData, southScheduleData);
				break;
			case 5:
				bookandtrain(memberID);
				break;
			default:
				printf("Invalid number. Please enter again.\n");
				break;
			}
		}
	} while (choice != 5);

	return 0;
}

int TrainSchedulingMainForStaff(staffdetail admin[], Member members[]) {
	int choice;

	scheduleInfo northScheduleData[MAX_TRAIN];
	scheduleInfo southScheduleData[MAX_TRAIN];
	scheduleInfo scheduleData[MAX_TRAIN];

	//close this when the file exist at your PC
		// writeData();
	readData(northScheduleData, southScheduleData);

	do
	{
		printf("\n************************************\n");
		printf("1. Display all schedule\n");
		printf("2. Add Schedule\n");
		printf("3. Modify Schedule\n");
		printf("4. Delete Schedule\n");
		printf("5. Back\n");
		printf("************************************\n");
		printf("Enter your choice (1-5): ");

		if (scanf("%d", &choice) != 1)
		{
			printf("Invalid input. Please enter a number.\n");
			while (getchar() != '\n');

		}
		else if (choice < 1 || choice > 5)
		{
			printf("Invalid choice. Please enter a number between 1 and 8.\n");
		}
		else
		{
			switch (choice) {
			case 1:
				displayAllSchedule(northScheduleData, southScheduleData);
				break;
			case 2:
				addSchedule(northScheduleData, southScheduleData);
				break;
			case 3:
				modifySchedule(northScheduleData, southScheduleData);
				break;
			case 4:
				deleteSchedule(northScheduleData, southScheduleData);
				break;
			case 5:
				adminMenu(admin, members);
				break;
			default:
				printf("Invalid number. Please enter again.\n");
				break;
			}
		}
	} while (choice != 5);

	return 0;
}

bool isValidTimeFormat(const char* time) {
	if (strlen(time) == 5)
	{
		if (time[2] != ':')
			return false;

		int hours = (time[0] - '0') * 10 + (time[1] - '0');
		int minutes = (time[3] - '0') * 10 + (time[4] - '0');

		if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
			return false;
	}
	else if (strcmp(time, "-") != 0 && strcmp(time, "TD") != 0 && strcmp(time, "TM") != 0)
	{
		return false;
	}
	return true;
}

bool isSameDestination(const scheduleInfo scheduleData[], int scheduleCount, const char* destination) {
	for (int i = 0; i < scheduleCount; i++)
	{
		if (strcmp(scheduleData[i].destination, destination) == 0) {
			return true;
		}
	}
	return false;
}

int isValidDestination(const char* destination) {
	while (*destination) {
		if (!isalpha(*destination) && !isspace(*destination) && !ispunct(*destination))
		{
			return 0;
		}
		destination++;
	}
	return 1;
}

int validateStations(const char* departure, const char* arrival, const scheduleInfo* scheduleData) {
	int departureFound = 0, arrivalFound = 0;
	int departureIndex = -1, arrivalIndex = -1;

	for (int i = 0; i < MAX_TRAIN; i++) {
		if (strcmp(scheduleData[i].destination, departure) == 0) {
			departureFound = 1;
			departureIndex = i;
		}
		if (strcmp(scheduleData[i].destination, arrival) == 0) {
			arrivalFound = 1;
			arrivalIndex = i;
		}
	}
	if (!departureFound || !arrivalFound || departureIndex >= arrivalIndex) {
		printf("NOTE: Invalid departure or arrival station.\n");
		return 0;
	}
	return 1;
}

void writeData() {
	FILE* NSFile;
	NSFile = fopen("NSFile.bin", "wb");

	if (NSFile == NULL)
	{
		printf("Error opening file.");
		exit(-1);
	}

	scheduleInfo schedule_n[MAX_TRAIN] = {
		{"TN1001", "Gemas", "-", "-", "08:05", "-", "-", "-", "-", "-", "15:20", "-"},
		{"TN1002", "Batang Melaka", "-", "-", "08:23", "-", "-", "-", "-", "-", "15:39", "-"},
		{"TN1003", "Pulau Sebang", "-", "-", "08:37", "-", "-", "-", "-", "-", "15:54", "-"},
		{"TN1004", "Seremban", "-", "-", "09:10", "-", "-", "-", "-", "-", "16:28", "-"},
		{"TN1005", "Kajang", "-", "-", "10:01", "-", "-", "-", "-", "-", "17:19", "-"},
		{"TN1006", "Bandar Tasik Selatan", "-", "-", "10:20", "-", "-", "-", "-", "-", "17:38", "-"},
		{"TN1007", "KL Sentral", "08:47", "09:50", "10:45", "11:08", "11:32", "13:37", "15:00", "15:55", "18:00", "18:31"},
		{"TN1008", "Kuala Lumpur", "08:53", "09:56", "10:54", "11:14", "11:38", "13:43", "15:06", "16:01", "18:06", "18:37"},
		{"TN1009", "Kepong Sentral", "09:14", "-", "-", "-", "11:59", "-", "15:22", "-", "-", "-"},
		{"TN1010", "Sungai Buloh", "09:22", "10:24", "11:17", "11:37", "12:07", "14:06", "15:30", "16:24", "18:29", "19:05"}
	};

	for (int i = 0; i < MAX_TRAIN; i++)
	{
		fwrite(&schedule_n[i], sizeof(scheduleInfo), 1, NSFile);
	}

	scheduleInfo schedule_s[MAX_TRAIN] = {
		{"TS1001", "Arau", "-", "-", "07:48", "-", "09:53", "-", "-", "13:58", "-", "-"},
		{"TS1002", "Alor Setar", "-", "-", "08:09", "-", "10:14", "-", "-", "14:19", "-", "-"},
		{"TS1003", "Sungai Petani", "-", "-", "08:39", "-", "10:44", "-", "-", "14:49", "-", "-"},
		{"TS1004", "Tasek Gelugor", "-", "-", "08:51", "-", "10:56", "-", "-", "15:01", "-", "-"},
		{"TS1005", "Butterworth", "-", "07:50", "-", "-", "-", "12:45", "-", "-", "16:05", "-"},
		{"TS1006", "Bukit Mertajam", "-", "08:01", "-", "-", "-", "12:56", "-", "-", "16:16", "-"},
		{"TS1007", "Taiping", "-", "08:49", "09:47", "-", "11:52", "13:42", "-", "15:57", "17:02", "-"},
		{"TS1008", "Kuala Kangsar", "-", "09:06", "10:03", "-", "12:08", "13:58", "-", "16:13", "17:18", "-"},
		{"TS1009", "Ipoh", "08:22", "09:36", "10:32", "12:02", "12:37", "14:27", "15:30", " 16:42", "17:47", "18:35"},
		{"TS1010", "Batu Gajah", "08:35", "09:50", "10:46", "12:15", "12:51", "14:41", "15:43", "16:56", "18:01", "18:48"}
	};

	for (int i = 0; i < MAX_TRAIN; i++)
	{
		fwrite(&schedule_s[i], sizeof(scheduleInfo), 1, NSFile);
	}
	fclose(NSFile);
}

int readData(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]) {
	FILE* NSFile;
	int scheduleSCount = 0, scheduleNCount = 0;
	int count = 0;
	NSFile = fopen("NSFile.bin", "rb");
	if (NSFile == NULL)
	{
		printf("Error opening file.\n");
		exit(-1);
	}
	for (int i = 0; i < MAX_TRAIN; i++)
	{
		fread(&northScheduleData[i], sizeof(scheduleInfo), 1, NSFile);
		scheduleNCount++;
	}
	for (int i = 0; i < MAX_TRAIN; i++)
	{
		fread(&southScheduleData[i], sizeof(scheduleInfo), 1, NSFile);
		scheduleSCount++;
	}
	return count = (scheduleNCount + scheduleSCount);
}

void viewNorthSouthSchedule(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]) {

	char confirm;
	int answer;

	printf("\nDo you want to view the schedule first? (Y/N): ");
	scanf(" %c", &confirm);
	rewind(stdin);

	if (toupper(confirm) == 'Y') {
		printf("====================\n");
		printf("1. North Schedule\n");
		printf("2. South Schedule\n");
		printf("3. All Schedule\n");
		printf("4. Exit\n");
		printf("====================\n");
		printf("Enter your choice: ");
		scanf("%d", &answer);
		rewind(stdin);

		if (answer < 1 || answer > 4) {
			printf("Invalid choice. Please enter a number between 1 and 4.\n");
		}
		else {
			switch (answer) {
			case 1:
				displayNorthSchedule(northScheduleData);
				break;
			case 2:
				displaySouthSchedule(southScheduleData);
				break;
			case 3:
				displayAllSchedule(northScheduleData, southScheduleData);
				break;
			case 4:
				printf("Exiting view schedule.\n");
				break;
			default:
				printf("Invalid choice. Please enter a number between 1 and 4.\n");
				break;
			}
		}
	}
	else if (toupper(confirm) == 'N')
	{
		printf("Proceeding without viewing schedule.\n");
	}
	else
	{
		printf("Invalid input. Enter Y or N only.\n");
	}

	printf("\n");
}

void search(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]) {
	char direction;
	char answer;
	char viewSeat;
	int startingIndex;
	int endingIndex;
	int distance;
	int found = 0;
	scheduleInfo search_Schedule;

	//array to store arrival time
	char arrivalTimes[MAX_TRAIN][MAX_TIME][7];

	do
	{
		int validInput = 0;
		viewNorthSouthSchedule(northScheduleData, southScheduleData);

		printf("Which way are you going?\n");
		printf("Enter N (north) or S (south): ");
		scanf("%c", &direction);
		rewind(stdin);

		//search for north schedule
		if (toupper(direction) == 'N')
		{
			printf("\nEnter your departure station: ");
			scanf("%[^\n]", search_Schedule.departureStation);
			rewind(stdin);
			printf("Enter your arrival station: ");
			scanf("%[^\n]", search_Schedule.arrivalStation);
			rewind(stdin);


			if (validateStations(search_Schedule.departureStation, search_Schedule.arrivalStation, northScheduleData))
			{
				validInput = 1;
			}

			if (validInput)
			{
				printf("\nNorthbound Schedule:\n");
				for (int i = 0; i < MAX_TRAIN; i++)
				{
					if (strcmp(northScheduleData[i].destination, search_Schedule.arrivalStation) == 0)
					{
						endingIndex = i;
						for (int j = 0; j < MAX_TIME; j++)
						{
							strcpy(arrivalTimes[i][j], northScheduleData[i].time[j].time);
						}
					}
				}

				for (int i = 0; i < MAX_TRAIN; i++)
				{
					if (strcmp(northScheduleData[i].destination, search_Schedule.departureStation) == 0)
					{
						startingIndex = i;
						distance = endingIndex - startingIndex;
						search_Schedule.price = distance * 8;
						printf("Departure Station: %s\n", search_Schedule.departureStation);
						printf("Arrival Station: %s\n", search_Schedule.arrivalStation);
						printf("---------------------------------------------------------------\n");
						printf("| %10s | %15s | %15s | %10s |\n", "Train ID", "Departure Time", "Arrival Time", "Price(RM)");
						printf("---------------------------------------------------------------\n");
						for (int j = 0; j < MAX_TIME; j++)
						{
							if (strcmp(northScheduleData[i].time[j].time, "-") != 0)
							{
								printf("| %10s | %15s | %15s | %10d |\n", northScheduleData[j].trainID.trainId, northScheduleData[i].time[j].time, arrivalTimes[endingIndex][j], search_Schedule.price);
								found = 1;
							}
						}
						printf("---------------------------------------------------------------\n");
						printf("\n");
					}
				}
				printf("View available seats?: ");
				scanf("%c", &viewSeat);
				rewind(stdin);

				do
				{
					switch (toupper(viewSeat))
					{
					case 'Y':
						checkSeatAvailability_n();
						break;
					case 'N':
						printf("proceeding without viewing seats.\n");
						break;
					default:
						printf("Invalid input. Enter Y or N only.\n");
						break;
					}
					printf("Continue to view seats? (Y/N): ");
					scanf("%c", &viewSeat);
				} while (toupper(viewSeat) != 'N');

			}
		}
		else if (toupper(direction) == 'S')
		{
			rewind(stdin);
			printf("\nEnter your departure station: ");
			scanf("%[^\n]", search_Schedule.departureStation);
			rewind(stdin);
			printf("Enter your arrival station: ");
			scanf("%[^\n]", search_Schedule.arrivalStation);
			rewind(stdin);

			if (validateStations(search_Schedule.departureStation, search_Schedule.arrivalStation, southScheduleData)) {
				validInput = 1;
			}

			if (validInput)
			{
				printf("\nSouthbound Schedule:\n");
				for (int i = 0; i < MAX_TRAIN; i++)
				{
					if (strcmp(southScheduleData[i].destination, search_Schedule.arrivalStation) == 0)
					{
						endingIndex = i;
						for (int j = 0; j < MAX_TIME; j++)
						{
							strcpy(arrivalTimes[i][j], southScheduleData[i].time[j].time);
						}
					}
				}

				for (int i = 0; i < MAX_TRAIN; i++)
				{
					if (strcmp(southScheduleData[i].destination, search_Schedule.departureStation) == 0)
					{
						startingIndex = i;
						distance = endingIndex - startingIndex;
						search_Schedule.price = distance * 8;
						printf("Departure Station: %s\n", search_Schedule.departureStation);
						printf("Arrival Station: %s\n", search_Schedule.arrivalStation);
						printf("---------------------------------------------------------------\n");
						printf("| %10s | %15s | %15s | %10s |\n", "Train ID", "Departure Time", "Arrival Time", "Price(RM)");
						printf("---------------------------------------------------------------\n");
						for (int j = 0; j < MAX_TIME; j++)
						{
							if (strcmp(southScheduleData[i].time[j].time, "-") != 0)
							{
								printf("| %10s | %15s | %15s | %10d |\n", southScheduleData[j].trainID.trainId, southScheduleData[i].time[j].time, arrivalTimes[endingIndex][j], search_Schedule.price);
								found = 1;
							}
						}
						printf("---------------------------------------------------------------\n");
						printf("\n");
					}
				}
				printf("View available seats?: ");
				scanf("%c", &viewSeat);
				rewind(stdin);

				do
				{
					switch (toupper(viewSeat))
					{
					case 'Y':
						checkSeatAvailability_s();
						break;
					case 'N':
						printf("proceeding without viewing seats.\n");
						break;
					default:
						printf("Invalid input. Enter Y or N only.\n");
						break;
					}

					printf("Continue to view seats? (Y/N): ");
					scanf("%c", &viewSeat);

				} while (toupper(viewSeat) != 'N');
			}

		}
		else if (toupper(direction) != 'N' && toupper(direction) != 'S')
		{
			printf("NOTE: Invalid input. Try again.\n\n");
		}

		printf("Continue to search your destination? (Y/N): ");
		scanf(" %c", &answer);
		rewind(stdin);
		printf("\n");
	} while (toupper(answer) != 'N');
}

void displayNorthSchedule(scheduleInfo northScheduleData[]) {

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
	printf("NOTE: \n");
	printf("TD = Train delayed\n");
	printf("TM = Train maintenance\n");
}

void displaySouthSchedule(scheduleInfo southScheduleData[]) {

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
	printf("NOTE: \n");
	printf("TD = Train delayed\n");
	printf("TM = Train maintenance\n");
}

void displayAllSchedule(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]) {
	displayNorthSchedule(northScheduleData);
	displaySouthSchedule(southScheduleData);
}

void addSchedule(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]) {

	char answer;
	int scheduleCount = 11;

	do {
		viewNorthSouthSchedule(northScheduleData, southScheduleData);
		printf("Add N(north) or S(south) schedule?: ");
		scanf(" %c", &answer);
		rewind(stdin);
		if (toupper(answer) == 'N')
		{
			printf("Add Schedule Info:\n");
			printf("Enter destination: ");
			scanf("%[^\n]", northScheduleData[scheduleCount].destination);
			rewind(stdin);

			while (!isValidDestination(northScheduleData[scheduleCount].destination) || isSameDestination(northScheduleData, scheduleCount, northScheduleData[scheduleCount].destination))
			{
				if (!isValidDestination(northScheduleData[scheduleCount].destination))
				{
					printf("Invalid destination format.\n");
					printf("\n");
				}
				if (isSameDestination(northScheduleData, scheduleCount, northScheduleData[scheduleCount].destination))
				{
					printf("Destination already exists. Please enter different destination name.\n");
					printf("\n");
				}
				printf("Enter destination: ");
				scanf("%[^\n]", northScheduleData[scheduleCount].destination);
				rewind(stdin);
			}

			printf("\nThe time must be in HH:MM format or '-'\n");
			printf("Enter departure time (up to 10 times): \n");
			for (int i = 0; i < MAX_TIME; i++)
			{
				char time[6];
				printf("Time %d: ", i + 1);
				scanf("%5s", time);
				rewind(stdin);

				while (!isValidTimeFormat(time)) {
					printf("Invalid time format.\n");
					printf("Enter time in HH:MM format or '-', TD or TM only: ");
					scanf("%5s", time);
					rewind(stdin);
				}

				strcpy(northScheduleData[scheduleCount].time[i].time, time);
			}
			scheduleCount++;

			displayNorthSchedule(northScheduleData);
		}
		else if (toupper(answer) == 'S')
		{

			printf("Add Schedule Info:\n");
			printf("Enter destination: ");
			scanf("%[^\n]", southScheduleData[scheduleCount].destination);
			rewind(stdin);

			while (!isValidDestination(southScheduleData[scheduleCount].destination) || isSameDestination(southScheduleData, scheduleCount, southScheduleData[scheduleCount].destination))
			{
				if (!isValidDestination(southScheduleData[scheduleCount].destination))
				{
					printf("Invalid destination format.\n");
					printf("\n");
				}
				if (isSameDestination(southScheduleData, scheduleCount, southScheduleData[scheduleCount].destination))
				{
					printf("Destination already exists. Please enter different destination name.\n");
					printf("\n");
				}
				printf("Enter destination: ");
				scanf("%[^\n]", southScheduleData[scheduleCount].destination);
				rewind(stdin);
			}

			printf("\nThe time must be in HH:MM format or '-'\n");
			printf("Enter departure time (up to 10 times): \n");
			for (int i = 0; i < MAX_TIME; i++) {
				char time[6];
				printf("Time %d: ", i + 1);
				scanf("%5s", time);
				rewind(stdin);

				while (!isValidTimeFormat(time)) {
					printf("Invalid time format.\n");
					printf("Enter time in HH:MM format or '-', TD or TM only: ");
					scanf("%5s", time);
					rewind(stdin);
				}

				strcpy(southScheduleData[scheduleCount].time[i].time, time);
			}
			scheduleCount++;

			displaySouthSchedule(southScheduleData);
		}
		else
		{
			printf("Invalid input. Enter N or S only.");
		}

		printf("Do you wish to enter another record? (Y/N): ");
		scanf(" %c", &answer);
		rewind(stdin);

	} while (toupper(answer) != 'N');

	FILE* NSFile;
	NSFile = fopen("NSFile.bin", "ab");

	if (NSFile == NULL)
	{
		printf("Error opening file.\n");
		exit(-1);
	}
	for (int i = 0; i < scheduleCount; i++)
	{
		fwrite(&northScheduleData, sizeof(scheduleInfo), 1, NSFile);
	}
	for (int i = 0; i < scheduleCount; i++)
	{
		fwrite(&southScheduleData, sizeof(scheduleInfo), 1, NSFile);
	}

	fclose(NSFile);
}

void modifySchedule(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]) {

	viewNorthSouthSchedule(northScheduleData, southScheduleData);

	char editDestination[50];
	int foundCount = 0;
	int index = 0;
	scheduleInfo temp;
	char answer;
	char option;

	do {
		printf("NOTE: You can only modify the schedule once per time.\n");
		printf("Modify N(north) or S(south) schedule?: ");
		scanf(" %c", &option);
		rewind(stdin);

		if (toupper(option) == 'N')
		{

			printf("Enter destination you want edit\n");
			printf("Destination: ");
			scanf("%[^\n]", editDestination);
			rewind(stdin);
			printf("\n");

			for (int i = 0; i < MAX_TRAIN; i++)
			{
				strcpy(temp.trainID.trainId, northScheduleData[index].trainID.trainId);
				if (strcmp(editDestination, northScheduleData[i].destination) == 0)
				{
					foundCount++;
					index = i;
				}
			}
			if (foundCount < 1)
			{
				printf("No destination is found.\n");
			}
			else
			{
				printf("Record found:\n");
				printf("Enter Info to Update: \n\n");

				do {
					printf("Enter new destination: ");
					scanf("%[^\n]", temp.destination);
					rewind(stdin);

					if (strcmp(temp.destination, editDestination) != 0 && isSameDestination(northScheduleData, MAX_TRAIN, temp.destination))
					{
						printf("Destination name already exists. Please enter a different destination.\n");
						printf("\n");
					}
					else if (!isValidDestination(temp.destination))
					{
						printf("Invalid destiantion.\n");
						printf("\n");
					}
				} while ((strcmp(temp.destination, editDestination) != 0 && isSameDestination(northScheduleData, MAX_TRAIN, temp.destination)) || !isValidDestination(temp.destination));


				printf("The time can be '-' and each time entered must contained ':' \n");
				printf("If there are any train issues: \n");
				printf("TD = train delayed\n");
				printf("TM = train maintenance\n");
				printf("Enter departure time (up to 10 times): \n");
				for (int i = 0; i < MAX_TIME; i++)
				{
					char time[6];
					printf("Time %d: ", i + 1);
					scanf("%s", temp.time[i].time);
					rewind(stdin);

					if (!isValidTimeFormat(temp.time[i].time))
					{
						printf("Invalid time format.\n");
						printf("Enter time in HH:MM format or '-', TD or TM only.\n");
						i--;
					}
				}

				printf("\nAnswer to update? (Y=Yes): ");
				scanf(" %c", &answer);
				rewind(stdin);

				if (toupper(answer) == 'Y')
				{
					northScheduleData[index] = temp;
					displayNorthSchedule(northScheduleData);
				}
				else {
					printf("No changes made.\n");
				}
			}
		}
		else if (toupper(option) == 'S')
		{

			printf("Enter destination you want edit\n");
			printf("Destination: ");
			scanf("%[^\n]", editDestination);
			rewind(stdin);
			printf("\n");

			for (int i = 0; i < MAX_TRAIN; i++)
			{
				strcpy(temp.trainID.trainId, southScheduleData[index].trainID.trainId);
				if (strcmp(editDestination, southScheduleData[i].destination) == 0)
				{
					foundCount++;
					index = i;
				}
			}
			if (foundCount < 1)
			{
				printf("No destination is found.\n\n");
			}
			else
			{
				printf("Record found: \n\n");
				printf("Enter Info to Update: \n");

				do {
					printf("Enter new destination: ");
					scanf("%[^\n]", temp.destination);
					rewind(stdin);

					if (strcmp(temp.destination, editDestination) != 0 && isSameDestination(southScheduleData, MAX_TRAIN, temp.destination))
					{
						printf("Destination name already exists. Please enter a different destination.\n");
						printf("\n");
					}
					else if (!isValidDestination(temp.destination))
					{
						printf("Invalid destiantion.\n");
						printf("\n");
					}
				} while ((strcmp(temp.destination, editDestination) != 0 && isSameDestination(southScheduleData, MAX_TRAIN, temp.destination)) || !isValidDestination(temp.destination));

				printf("The time can be '-' and each time entered must contained ':' \n");
				printf("If there are any train issues: \n");
				printf("TD = train delayed\n");
				printf("TM = train maintenance\n");
				printf("Enter departure time (up to 10 times): \n");
				for (int i = 0; i < MAX_TIME; i++)
				{
					char time[6];
					printf("Time %d: ", i + 1);
					scanf("%s", temp.time[i].time);
					rewind(stdin);

					if (!isValidTimeFormat(temp.time[i].time))
					{
						printf("Invalid time format.\n");
						printf("Enter time in HH:MM format or '-', TD or TM only.\n");
						i--;
					}
				}

				printf("\nanswer to update? (Y=Yes): ");
				rewind(stdin);
				scanf(" %c", &answer);

				if (toupper(answer) == 'Y')
				{
					southScheduleData[index] = temp;
					displaySouthSchedule(southScheduleData);
				}
				else {
					printf("No changes made.\n");
				}
			}
		}
		else
		{
			printf("Invalid choice. Enter N or S only.\n");
		}

		printf("Do you want to continue modifying the schedule? (Y/N): ");
		scanf(" %c", &answer);
		rewind(stdin);
		printf("\n");
	} while (toupper(answer) != 'N');

	FILE* NSFile;
	NSFile = fopen("NSFile.bin", "wb");
	if (NSFile == NULL)
	{
		printf("Error opening file.\n");
		exit(-1);
	}

	for (int i = 0; i < MAX_TRAIN; i++)
	{
		fwrite(&northScheduleData[i], sizeof(scheduleInfo), 1, NSFile);
	}
	for (int i = 0; i < MAX_TRAIN; i++)
	{
		fwrite(&southScheduleData[i], sizeof(scheduleInfo), 1, NSFile);
	}

	fclose(NSFile);
}

void deleteSchedule(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]) {
	char answer;

	do {
		viewNorthSouthSchedule(northScheduleData, southScheduleData);

		char deleteDestination[50];
		int found = 0;

		printf("You can only delete 1 schedule per time \n");
		printf("Delete N(north) or S(south) schedule?: ");
		scanf(" %c", &answer);
		rewind(stdin);

		if (toupper(answer) == 'N')
		{
			printf("Enter the destination you wish to delete: ");
			scanf("%[^\n]", deleteDestination);
			rewind(stdin);

			for (int i = 0; i < MAX_TRAIN; i++) {
				if (strcmp(northScheduleData[i - 1].destination, deleteDestination) == 0) {
					strcpy(northScheduleData[i - 1].destination, "");
					for (int j = 0; j < MAX_TIME; j++) {
						strcpy(northScheduleData[i - 1].time[j - 1].time, "");
					}
					found = 1;
				}
			}
			displayNorthSchedule(northScheduleData);

		}
		else if (toupper(answer) == 'S') {
			printf("You can only delete 1 schedule per time \n");
			printf("Enter the destination to delete: ");
			scanf("%[^\n]", deleteDestination);
			rewind(stdin);

			for (int i = 0; i < MAX_TRAIN; i++) {
				if (strcmp(southScheduleData[i - 1].destination, deleteDestination) == 0) {
					strcpy(southScheduleData[i - 1].destination, "");
					for (int j = 0; j < MAX_TIME; j++) {
						strcpy(southScheduleData[i - 1].time[j - 1].time, "");
					}
					found = 1;
				}
			}
			displaySouthSchedule(southScheduleData);
		}
		else
		{
			printf("Invalid input. Enter N or S only.\n");
		}

		if (found) {
			FILE* NSFile;
			NSFile = fopen("NSFile.bin", "wb");
			if (NSFile == NULL) {
				printf("Error opening file.\n");
				exit(-1);
			}

			for (int i = 0; i < MAX_TRAIN; i++) {
				fwrite(&northScheduleData[i], sizeof(scheduleInfo), 1, NSFile);
			}
			for (int i = 0; i < MAX_TRAIN; i++) {
				fwrite(&southScheduleData[i], sizeof(scheduleInfo), 1, NSFile);
			}

			fclose(NSFile);
			printf("Schedule deleted successfully.\n");
		}
		else {
			printf("Destination not found in the schedule.\n");
		}

		printf("Do you want to delete another schedule? (Y/N): ");
		scanf(" %c", &answer);
		rewind(stdin);

	} while (toupper(answer) != 'N');
}

int findValue(const char(*arr)[MAX_SEATROW], int size, const char* value) {
	for (int i = 0; i < size; i++)
	{
		if (strcmp(arr[i], value) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int validateTrainID(const char* trainID) {

	if (strlen(trainID) != 6 || strncmp(trainID, "TN10", 4) != 0 && strncmp(trainID, "TS10", 4) != 0)
		return 0;

	for (int i = 4; i < 6; i++)
	{
		if (!isdigit(trainID[i]))
			return 0;
	}
	return 1;
}

void checkSeatAvailability_n() {

	char answer;
	char trainID[7];
	int found = 0;
	int availableSeats = 0;

	char seat_n[][MAX_SEATCOL][MAX_SEATROW] = {
		{"1-1", "2-5", "5-5", "4-1", "0-0"},
		{"1-1", "2-5", "5-5", "4-1", "0-0", "1-2", "1-3", "6-1"},
		{"2-0", "1-2", "5-6", "6-0", "6-9", "7-6"},
		{"0-1", "0-2", "0-6", "1-0", "1-9", "5-6", "6-8"},
		{"3-2", "3-0", "3-6", "4-0", "4-1", "5-6", "6-0", "7-1", "7-5"},
		{"0-1", "0-2", "0-6", "2-0", "2-9", "5-6", "6-7"},
		{"0-4", "1-2", "2-3", "3-6", "4-0", "4-9", "5-6", "5-7"},
		{"6-1", "0-2", "0-6", "1-0", "1-9", "5-6", "6-7"},
		{"0-8", "0-2", "0-6", "1-0", "1-9", "5-6", "7-0"},
		{"0-9", "0-2", "0-6", "1-0", "1-9", "5-6", "7-7", "7-8"}
	};

	printf("Enter the train ID to check your seats: ");
	scanf("%s", trainID);
	rewind(stdin);

	if (!validateTrainID(trainID))
	{
		printf("Invalid train ID format. Please enter a valid train ID in the format 'TN10XX'.\n");
		return;
	}

	printf("\n+--------SEATS-------+\t\n");

	for (int i = 0; i < MAX_SEATCOL; i++)
	{
		for (int j = 0; j < MAX_SEATROW; j++)
		{
			for (int index = 1; index <= MAX_SEATCOL; index++)
			{
				char formatted_train_id[MAX_SEATROW];
				sprintf(formatted_train_id, "TN10%02d", index);

				if (strcmp(trainID, formatted_train_id) == 0)
				{
					char(*seats_in_train)[MAX_SEATROW] = seat_n[index - 1];
					char search_seat[MAX_SEATROW];
					sprintf(search_seat, "%d-%d", i, j);
					if (findValue(seats_in_train, MAX_SEATCOL, search_seat) == 0)
					{
						printf("0  "); // seat available
						availableSeats++;
					}
					else {
						printf("1  "); //seat booked
					}
				}
			}
		}
		printf("\n");
	}
	printf("\nNOTE:\n");
	printf("1 = seat is booked\n");
	printf("0 = seat available\n");
	printf("Total available seats: %d\n\n", availableSeats);
}

void checkSeatAvailability_s() {
	char answer;
	char trainID[7];
	int found = 0;
	int availableSeats = 1;

	char seat_s[][MAX_SEATCOL][MAX_SEATROW] = {
		{"1-1", "2-5", "5-5", "4-4", "2-0"},
		{"2-1", "2-5", "5-5", "4-1", "0-0", "1-2", "1-3", "6-1"},
		{"2-0", "1-2", "5-6", "6-0", "6-9", "7-6"},
		{"0-1", "3-2", "0-6", "1-0", "1-9", "5-6", "6-8"},
		{"3-2", "3-0", "3-6", "6-0", "4-1", "5-6", "7-0", "7-1", "7-5"},
		{"0-1", "0-2", "0-6", "2-0", "2-9", "5-6", "6-7"},
		{"0-4", "1-2", "2-3", "4-6", "4-0", "4-9", "5-6", "5-7"},
		{"6-1", "0-2", "0-6", "1-0", "1-9", "5-6", "6-7"},
		{"1-8", "0-2", "0-6", "1-0", "1-9", "5-6", "6-0"},
		{"2-9", "0-2", "0-6", "1-0", "1-9", "5-6", "7-7", "7-8"}
	};

	printf("Enter the train ID to check your seats: ");
	scanf("%s", trainID);
	rewind(stdin);

	if (!validateTrainID(trainID))
	{
		printf("Invalid train ID format. Please enter a valid train ID in the format 'TN10XX'.\n");
		return;
	}

	printf("\n+--------SEATS-------+\t\n");

	for (int i = 0; i < MAX_SEATCOL; i++)
	{
		for (int j = 0; j < MAX_SEATROW; j++)
		{
			for (int index = 1; index <= MAX_SEATCOL; index++)
			{
				char formatted_train_id[MAX_SEATROW];
				sprintf(formatted_train_id, "TS10%02d", index);

				if (strcmp(trainID, formatted_train_id) == 0)
				{
					char(*seats_in_train)[MAX_SEATROW] = seat_s[index - 1];
					char search_seat[MAX_SEATROW];
					sprintf(search_seat, "%d-%d", i, j);
					if (findValue(seats_in_train, MAX_SEATCOL, search_seat) == 0)
					{
						printf("0  "); // seat available
						availableSeats++;
					}
					else {
						printf("1  "); //seat booked
					}
				}
			}
		}
		printf("\n");
	}
	printf("\nNOTE:\n");
	printf("1 = seat is booked\n");
	printf("0 = seat available\n");
	printf("Total available seats: %d\n\n", availableSeats);
}

// booking module

void mainMenu(char memberID[]) {
	//char memberID[10] = "";
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

	do {
		found = false;
		rewind(stdin);

		for (int j = 0; j < i; j++) {
			if (strcmp(memberID, member[j].memberId) == 0) {
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
						return bookandtrain(memberID);
					default:
						printf("%33sInvalid choice. Please enter again.", " ");
					}

				} while (choice != 5);
			}
		}

		if (!found) {
			printf("%33sMember ID %s not found.\n", " ", memberID);
			printf("[ENTER to continue]");
			scanf("%[^\n]");
		}
	} while (!found);

}

//Function to generate a random booking number between min and max
int generateRandom(int min, int max) {
	return min + rand() % (max - min + 1);
}

char* PaymentStatus(int choicePaymentMethod) {
	static char paymentStatus[15]; // Changed to a simple character array
	char inputCardNo[30] = "", inputCardHolderName[50] = "";
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

void BookingTicket(char memberID[]) {
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
	displayNorthSchedule1();
	displaySouthSchedule1();

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
		displayNorthSchedule1();
		displaySouthSchedule1();
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
			displaySouthSchedule1();
			for (int j = 0; j < 9; j++) {
				printf("%34s%d. %s\n", " ", j + 1, southScheduleData[j].destination);
			}
		}
		else if (toupper(SorN) == 'N') {
			system("cls");
			Logo();
			displayNorthSchedule1();
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
			mainMenu(memberID);
		}

		while (i > 29) {
			printf("%34s%s\n", " ", "Booking cannot be added due to Booking restrictions.");
		}
		fclose(readRecord);


	} while (toupper(continueBooking) == 'Y' || countFileRow1 > 29);

}

void SearchBookedTicket(char memberID[]) {
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

			if (strcmp(memberID, searchBooking[i].MemberID) == 0) {
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
			printf("%33sThe member ID %s did not make any reservations.\n", " ", memberID);
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

void displayE_Ticket(char memberID[]) {
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

			if (strcmp(memberID, searchBooking[i].MemberID) == 0) {
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

void CancelBooking(char memberID[], char bookingID[]) {

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

		if (strcmp(memberID, searchBooking[i].MemberID) == 0) {
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
							found = true;
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

		fscanf(originalHistory, "%s %s %d-%d-%d %d:%d:%d %s %c %d %d %d %d %d %d %5s %5s %f %s %s", searchBooking[i].MemberID, searchBooking[i].BookingID,
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


		if (strcmp(memberID, searchBooking[i].MemberID) == 0) {

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
			fprintf(temphistory, "%s ", searchBooking[i].paymentStatus);
			fprintf(temphistory, "%s ", searchBooking[i].ticketStatus);
			k = 0;
			do {
				fprintf(temphistory, "%d ", searchBooking[i].seatNo[k]);
				k++;
			} while (k < searchBooking[i].quantity);
			fprintf(temphistory, "\n");
		}
	}

	if (!found) {
		int j = 0;
		while ((fscanf(originalCheckSeat, "%6s %d %d %d %d",
			readRecord[j].TrainID,
			&readRecord[j].departureDate.day, &readRecord[j].departureDate.month, &readRecord[j].departureDate.year,
			&readRecord[j].quantity) == 5)) {
			int k = 0;
			while (k < readRecord[j].quantity && fscanf(originalCheckSeat, " %d", &readRecord[j].seatNo[k]) == 1) {
				k++;
			}
			fprintf(tempCheckSeat, "%s %d %d %d %d ", readRecord[j].TrainID,
				readRecord[j].departureDate.day, readRecord[j].departureDate.month, readRecord[j].departureDate.year, readRecord[j].quantity);
			k = 0;
			do {
				k++;
				fprintf(tempCheckSeat, "%d ", readRecord[j].seatNo[k - 1]);
			} while (k < readRecord[j].quantity);
			fprintf(tempCheckSeat, "\n");

			j++;
		}
		printf("%33sBooking ID %s not found!\n", " ", bookingID);
		found = false;
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

	remove("ForSearchPurpose.txt");
	rename("temp.txt", "ForSearchPurpose.txt");
	remove("BookingHistory.txt");
	rename("temphistory.txt", "BookingHistory.txt");
	remove("checkSeatAvailable.txt");
	rename("tempCheckSeat.txt", "checkSeatAvailable.txt");
}

void ModifyFunction(char memberID[], char bookingID[]) {
	int k, j, h;
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
		fscanf(modify, "%s %s %d-%d-%d %d:%d:%d %s %c %d %d %d %d %d %d %5s %5s %f %s %s", modifyBooking[i].MemberID, modifyBooking[i].BookingID,
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


		if (strcmp(memberID, modifyBooking[i].MemberID) == 0) {
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
		else {
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

	if (!memberIdFound) {
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

void BookingHistory(char memberID[]) {
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

		fscanf(history, "%s %s %d-%d-%d %d:%d:%d %s %c %d %d %d %d %d %d %5s %5s %f %s %s", searchBooking[i].MemberID, searchBooking[i].BookingID,
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
		if (strcmp(memberID, searchBooking[i].MemberID) == 0) {
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
			printf("%33sDeparture station : %s\n", " ", destinationD);
			printf("%33sArrival station : %s\n", " ", destinationA);
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

char* returnDepartTime(char direction, char trainID[], int departStation) {
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

char* returnArriveTime(char direction, char trainID[], int arriveStation) {
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

void Logo() {
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

void MenuDesign() {


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
	printf("%34s%s%20s\n", " ", " ####|       5. Back                          |#### ", " ");
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

void displayNorthSchedule1() {
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

void displaySouthSchedule1() {
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

void readBinFile(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]) {
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