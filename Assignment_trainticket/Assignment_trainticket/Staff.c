//#include <stdlib.h>
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//#include <windows.h>
//#pragma warning (disable : 4996)
//#pragma warning (disable : 6031)
//#define MAX_MANAGER 3
//#define MAX_ADMIN 100
//#define AC_RED "\x1b[31m"
//#define AC_GREEN "\x1b[32m"
//#define AC_YELLOW "\x1b[33m"
//#define AC_BLUE "\x1b[34m"
//#define AC_NORMAL "\033[0m"
//struct Date
//{
//	int day;
//	int month;
//	int year;
//};
//
//typedef struct {
//	char id[7];
//	char username[51];
//	char iC[51];
//	char email[51];
//	char gender;
//	char contactNumber[51];
//	char position[31];
//	char password[51];
//	struct Date birth;
//}staffdetail;
//
//int menu();
//int staffMenu();
//int signinManagerMenu();
//int signinAdminMenu();
//int managerMenu(staffdetail admin[]);
//int adminMenu(staffdetail admin[]);
//void managersignIn(staffdetail admin[]);
//void adminsignin(staffdetail admin[]);
//int logOut(staffdetail admin[]);
//int readFile(staffdetail admin[]);
//
//int viewAdmin(staffdetail admin[]);
//int searchAdmin(staffdetail admin[]);
//int addAdmin(staffdetail admin[]);
//int editAdmin(staffdetail admin[]);
//int deleteAdmin(staffdetail admin[]);
//int resetPw(staffdetail admin[], int* password);
//
//int validationName(int* error, char username[]);
//int validationIC(int* error, char ic[]);
//int validationEmail(int* error, char email[]);
//int validationGender(int* error, char gender[]);
//int validationContactNumber(int* error, char cNumber[]);
//int validationPosition(int* error, char position[]);
//int validationPw(int* error, char pw[]);
//int validationbirthdate(int* error, int day[], int month[], int year[]);
//int validationID(int* error, char id[]);
//int validationselect(int* error, char ans);
//void errorMessage(int e);
//
//void main() {
//	menu();
//	system("pause");
//}
//
////menu
//int menu() {
//	int mode;
//	do {
//		system("cls");
//		printf("*******************************************************************************************\n");
//		printf("*Choose mode:\n");
//		printf("*1. Staff\n");
//		printf("*2. member\n");
//		printf("*3. schudule\n");
//		printf("*4. Booking\n");
//		printf("*5. Exit\n");
//		printf("*******************************************************************************************\n");
//
//		printf("Enter your mode number:");
//		rewind(stdin);
//		scanf("%d", &mode);
//
//		switch (mode)
//		{
//		case 1:
//			staffMenu();
//			break;
//		case 2:
//			break;
//		case 3:
//			break;
//		case 4:
//			break;
//		case 5:
//			printf("Exiting the system. Goodbye!\n");
//			exit(0);
//			break;
//		default:
//			printf("Invalid choice. Please select (1-5).\n");
//			break;
//		}
//	} while (mode != 5);
//}
//
//int staffMenu() {
//	int choose;
//	do {
//		system("cls");
//		printf("\t\t\t\t============================================\n");
//		printf("\t\t\t\t=                                          =\n");
//		printf("\t\t\t\t=              1. Manager                  =\n");
//		printf("\t\t\t\t=              2. Admin                    =\n");
//		printf("\t\t\t\t=              3. back                     =\n");
//		printf("\t\t\t\t=                                          =\n");
//		printf("\t\t\t\t============================================\n");
//
//		printf("\t\tEnter your mode number:");
//		rewind(stdin);
//		scanf("%d", &choose);
//
//		switch (choose)
//		{
//		case 1:
//			signinManagerMenu();
//			break;
//		case 2:
//			signinAdminMenu();
//			break;
//		case 3:
//			return menu();
//			break;
//		default:
//			printf("\t\t\t\t%sInvalid choice. Please select (1-3).%s\n", AC_RED, AC_NORMAL);
//			break;
//		}
//	} while (choose != 3);
//}
//
//int signinManagerMenu() {
//	staffdetail admin[MAX_ADMIN];
//	int choose, password;
//	do {
//		system("cls");
//		printf("\t\t\t\t============================================\n");
//		printf("\t\t\t\t=                                          =\n");
//		printf("\t\t\t\t=              1. Login                    =\n");
//		printf("\t\t\t\t=              2. back                     =\n");
//		printf("\t\t\t\t=                                          =\n");
//		printf("\t\t\t\t============================================\n");
//
//		printf("\t\tEnter your mode number:");
//		rewind(stdin);
//		scanf("%d", &choose);
//
//		switch (choose)
//		{
//		case 1:
//			managersignIn(admin);
//			break;
//		case 2:
//			staffMenu();
//			break;
//		default:
//			printf("\t\t\t\t%sInvalid choice. Please select (1-2).%s\n", AC_RED, AC_NORMAL);
//			break;
//		}
//	} while (choose != 3);
//}
//
//int signinAdminMenu() {
//	staffdetail admin[MAX_ADMIN];
//	int choose, password;
//	do {
//		system("cls");
//		printf("\t\t\t\t============================================\n");
//		printf("\t\t\t\t=                                          =\n");
//		printf("\t\t\t\t=              1. Login                    =\n");
//		printf("\t\t\t\t=              2. forgot password          =\n");
//		printf("\t\t\t\t=              3. back                     =\n");
//		printf("\t\t\t\t=                                          =\n");
//		printf("\t\t\t\t============================================\n");
//
//		printf("\t\tEnter your mode number:");
//		rewind(stdin);
//		scanf("%d", &choose);
//
//		switch (choose)
//		{
//		case 1:
//			adminsignin(admin);
//			break;
//		case 2:
//			resetPw(admin, &password);
//			break;
//		case 3:
//			staffMenu();
//			break;
//		default:
//			printf("\t\tInvalid choice. Please select (1-3).\n");
//			break;
//		}
//	} while (choose != 3);
//}
//
//int managerMenu(staffdetail admin[]) {
//	int select;
//	do {
//		printf("\t\t\t\t============================================\n");
//		printf("\t\t\t\t=          StaffAdmin Information          =\n");
//		printf("\t\t\t\t============================================\n");
//		printf("\t\t\t\t=                                          =\n");
//		printf("\t\t\t\t=            1.View Admin                  =\n");
//		printf("\t\t\t\t=            2.Searh Admin                 =\n");
//		printf("\t\t\t\t=            3.Add Admin                   =\n");
//		printf("\t\t\t\t=            4.Modify Admin                =\n");
//		printf("\t\t\t\t=            5.Delete Admin                =\n");
//		printf("\t\t\t\t=            6.LogOut                      =\n");
//		printf("\t\t\t\t=                                          =\n");
//		printf("\t\t\t\t============================================\n\n");
//
//
//		printf("\t\t Enter your Selection: ");
//		rewind(stdin);
//		scanf("%d", &select);
//
//		switch (select)
//		{
//		case 1:
//			viewAdmin(admin);
//			break;
//		case 2:
//			searchAdmin(admin);
//			break;
//		case 3:
//			addAdmin(admin);
//			break;
//		case 4:
//			editAdmin(admin);
//			break;
//		case 5:
//			deleteAdmin(admin);
//			break;
//		case 6:
//			logOut(admin);
//			break;
//		default:
//			printf("\t\t\t\t%s Invalid choice. Please select (1-5).%s\n", AC_RED, AC_NORMAL);
//			break;
//		}
//	} while (select != 1 && select != 2 && select != 3 && select != 4 && select != 5 && select != 6);
//}
//
//int adminMenu(staffdetail admin[]) {
//	int select;
//	do {
//		printf("\t\t\t\t============================================\n");
//		printf("\t\t\t\t=                    =\n");
//		printf("\t\t\t\t============================================\n");
//		printf("\t\t\t\t=                                          =\n");
//		printf("\t\t\t\t=            1.Display Member information  =\n");
//		printf("\t\t\t\t=            2.View North & South Schedule =\n");
//		printf("\t\t\t\t=            3.Add Schedule                =\n");
//		printf("\t\t\t\t=            4.Modify Schedule             =\n");
//		printf("\t\t\t\t=            5.Delete Schedule             =\n");
//		printf("\t\t\t\t=            6.LogOut                      =\n");
//		printf("\t\t\t\t=                                          =\n");
//		printf("\t\t\t\t============================================\n\n");
//
//
//		printf("\t\t Enter your Selection: ");
//		rewind(stdin);
//		scanf("%d", &select);
//
//		switch (select)
//		{
//		case 1:
//			break;
//		case 2:
//			break;
//		case 3:
//			break;
//		case 4:
//			break;
//		case 5:
//			break;
//		case 6:
//			logOut(admin);
//			break;
//		default:
//			printf("\t\t\t\t%s Invalid choice. Please select (1-6).%s\n", AC_RED, AC_NORMAL);
//			break;
//		}
//	} while (select != 1 && select != 2 && select != 3 && select != 4 && select != 5 && select != 6);
//}
//
//// manager signin
//void managersignIn(staffdetail admin[]) {
//	int lastIndex = readFile(admin);
//	staffdetail manager[MAX_MANAGER];
//	FILE* fstaffdetail;
//	char id[51];
//	int error, found = 0;
//	char password[51];
//	int validOption, loginSuccess = 0;
//	fstaffdetail = fopen("staffmanager.txt", "r");
//	if (fstaffdetail == NULL) {
//		printf("\t\tUnable to open file");
//		exit(-1);
//	}
//	while (fscanf(fstaffdetail, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%02d-%02d-%04d\n", &manager[lastIndex].id, &manager[lastIndex].username, &manager[lastIndex].iC, &manager[lastIndex].email, &manager[lastIndex].gender, &manager[lastIndex].contactNumber, &manager[lastIndex].position, &manager[lastIndex].password, &manager[lastIndex].birth.day, &manager[lastIndex].birth.month, &manager[lastIndex].birth.year) != EOF) {
//		lastIndex++;
//	}
//	fclose(fstaffdetail);
//
//	printf("\t\t\t\t========================================================\n");
//	printf("\t\t\t\t=                       LOGIN                          =\n");
//	printf("\t\t\t\t========================================================\n\n");
//	do {
//		error = 0;
//		printf("\t\tEnter Manager ID:");
//		rewind(stdin);
//		scanf("%[^\n]", &id);
//		validationID(&error, id);
//
//	} while (error == 1);
//
//	do {
//		error = 0;
//		printf("\t\tEnter Password:");
//		rewind(stdin);
//		scanf("%[^\n]", &password);
//		validationPw(&error, password);
//
//	} while (error == 1);
//
//	for (int i = 0;i < lastIndex;i++) {
//		//check validation
//		if (strcmp(id, manager[i].id) == 0) {
//			if (strcmp(password, manager[i].password) == 0) {
//				system("cls");
//				printf("\n\t\t\t\t\t\t%sLogin successfuly !!!%s", AC_GREEN, AC_NORMAL);
//				printf("\n\t\t\t\t\t\t%sWelcome!%s%s\n\n", AC_BLUE, manager[i].username, AC_NORMAL);
//				found = 1;
//				managerMenu(admin);
//			}
//		}
//	}
//	if (found == 0) {
//		errorMessage(16);
//	}
//
//}
//
// // admin signin
//void adminsignin(staffdetail admin[]) {
//	FILE* fstaffdetail;
//	int error, loginCount = 0, pw;
//	int validOption, loginSuccess = 0;
//	char id[51];
//	char password[51];
//	char option;
//	int lastIndex = readFile(admin);
//	printf("\t\t\t\t========================================================\n");
//	printf("\t\t\t\t=                       LOGIN                          =\n");
//	printf("\t\t\t\t========================================================\n\n");
//	do {
//		do {
//			error = 0;
//			printf("\t\tEnter Admin ID:");
//			rewind(stdin);
//			scanf("%[^\n]", &id);
//			validationID(&error, id);
//
//		} while (error == 1);
//
//		do {
//			error = 0;
//			printf("\t\tEnter Password:");
//			rewind(stdin);
//			scanf("%[^\n]", &password);
//			validationPw(&error, password);
//
//		} while (error == 1);
//
//		for (int i = 0;i < lastIndex;i++) {
//			//check validation
//			if (strcmp(id, admin[i].id) == 0) {
//				if (strcmp(password, admin[i].password) == 0) {
//					printf("\n\t\t\t\t\t\t%sLogin successfuly !!!%s", AC_GREEN, AC_NORMAL);
//					printf("\n\t\t\t\t\t\t%sWelcome!%s%s\n", AC_BLUE, admin[i].username, AC_NORMAL);
//					loginSuccess = 1;
//					adminMenu(admin);
//				}
//			}
//		}
//		if (loginSuccess == 0) {
//			printf("\n\t\t\t\t Your ID or password is wrong, try again!\n\n");
//			loginCount++;
//		}
//
//		if (loginCount >= 2) {
//			do {
//				printf("\n\t\t Forgot password ? (Y/N) >");
//				rewind(stdin);
//				scanf("%c", &option);
//				option = toupper(option);
//
//				if (option == 'Y') {
//					resetPw(admin, &pw);
//					if (pw == 1) {
//						loginCount = 0;
//					}
//					validOption = 0;
//				}
//				else {
//					validOption = 2;
//				}
//			} while (validOption == -1);
//		}
//	} while (loginSuccess != 1);
//}
//
// //logout
//int logOut(staffdetail admin[]) {
//	printf("\n\n");
//	printf("\t\t\t\t============================================\n");
//	printf("\t\t\t\t=          LogOut Staff                    =\n");
//	printf("\t\t\t\t============================================\n");
//
//	printf("\n\t\t\t\t\t\t%sLogOut successfuly !!!%s", AC_GREEN, AC_NORMAL);
//	return signinManagerMenu();
//}
//
//// readfile admin
//int readFile(staffdetail admin[]) {
//	FILE* fstaffdetail;
//	int lastIndex = 0, current;
//	fstaffdetail = fopen("staffadmin.txt", "r");
//	staffdetail edit;
//	if (fstaffdetail == NULL)
//	{
//		printf("\t\tUnable to open the file\n");
//		exit(-1);
//	}
//	while (fscanf(fstaffdetail, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%02d-%02d-%04d\n", &admin[lastIndex].id, &admin[lastIndex].username, &admin[lastIndex].iC, &admin[lastIndex].email, &admin[lastIndex].gender, &admin[lastIndex].contactNumber, &admin[lastIndex].position, &admin[lastIndex].password, &admin[lastIndex].birth.day, &admin[lastIndex].birth.month, &admin[lastIndex].birth.year) != EOF) {
//		lastIndex++;
//	}
//	fclose(fstaffdetail);
//
//	return lastIndex;
//}
//
//// forgot password
//int resetPw(staffdetail admin[], int* password) {
//	FILE* fstaffdetail;
//	int lastIndex, current;
//	lastIndex = readFile(admin);
//	staffdetail change;
//	int error, found;
//	char newPw[21], confirm[21], changePw, email[51];
//
//	printf("\t\t\t\t============================================\n");
//	printf("\t\t\t\t=                CHANGE PASSWORD           =\n");
//	printf("\t\t\t\t============================================\n\n");
//	do {
//		error = 0;
//		printf("\t\t Enter Admin ID:");
//		rewind(stdin);
//		scanf("%[^\n]", &change.id);
//		validationID(&error, change.id);
//
//	} while (error == 1);
//	found = 0;
//	for (int i = 0;i < lastIndex; i++) {
//		if (strcmp(change.id, admin[i].id) == 0) {
//			current = i;
//			found = 1;
//			do {
//				error = 0;
//				printf("\t\t Do you want change password? (Y/N): ");
//				rewind(stdin);
//				scanf("%c", &changePw);
//				changePw = toupper(changePw);
//
//				if (changePw != 'Y' && changePw != 'N') {
//					error = 1;
//				}
//			} while (error == 1);
//
//			if (changePw == 'Y') {
//				printf("%65s\n", "Security Question");
//				printf("\t\t\t\t============================================\n");
//				do {
//					error = 0;
//					printf("\t\t Enter Staff E-mail:");
//					rewind(stdin);
//					scanf("%s", &email);
//					validationEmail(&error, email);
//
//					if (strcmp(email, admin[current].email) == 0) {
//						do {
//							error = 0;
//							printf("\t\t Enter new password:");
//							rewind(stdin);
//							scanf("%[^\n]", &newPw);
//							validationPw(&error, newPw);
//
//						} while (error == 1);
//
//						do {
//							error = 0;
//							printf("\t\t Enter confirm password:");
//							rewind(stdin);
//							scanf("%[^\n]", &confirm);
//							validationPw(&error, confirm);
//
//						} while (error == 1);
//
//						if (strcmp(newPw, confirm) == 0) {
//							strcpy(admin[current].id, admin[current].id);
//							strcpy(admin[current].username, admin[current].username);
//							strcpy(admin[current].iC, admin[current].iC);
//							strcpy(admin[current].email, admin[current].email);
//							admin[current].gender = admin[current].gender;
//							strcpy(admin[current].contactNumber, admin[current].contactNumber);
//							strcpy(admin[current].position, admin[current].position);
//							strcpy(admin[current].password, newPw);
//							admin[current].birth.day = admin[current].birth.day;
//							admin[current].birth.month = admin[current].birth.month;
//							admin[current].birth.year = admin[current].birth.year;
//							*password = 1;
//						}
//						else {
//							errorMessage(15);
//							error = 1;
//						}
//					}
//					else {
//						printf("\t\t\t%sEmail invalid,please enter valid email%s\n", AC_RED, AC_NORMAL);
//						error = 1;
//					}
//				} while (error == 1);
//			}
//			else {
//				*password = 0;
//				found = 0;
//			}
//		}
//	}
//	if (found != 1) {
//		printf("\t\t\t\t\t\t%sdata not found%s\n", AC_RED, AC_NORMAL);
//	}
//	else if (found == 1) {
//		printf("\n\t\t\t\t\t%sPassword Changed successfuly !!!%s\n", AC_GREEN, AC_NORMAL);
//		printf("\n\t\t\t\t\t%sPlease Log in Again%s\n", AC_BLUE, AC_NORMAL);
//
//		fstaffdetail = fopen("staffadmin.txt", "w");
//		if (fstaffdetail == NULL) {
//			printf("\t\tUnable to open file");
//			exit(-1);
//		}
//
//		for (int i = 0;i < lastIndex;i++) {
//			fprintf(fstaffdetail, "%s|%s|%s|%s|%c|%s|%s|%s|%02d-%02d-%04d\n", admin[i].id, admin[i].username, admin[i].iC, admin[i].email, admin[i].gender, admin[i].contactNumber, admin[i].position, admin[i].password, admin[i].birth.day, admin[i].birth.month, admin[i].birth.year);
//		}
//		fclose(fstaffdetail);
//	}
//}
//
// // view admin
//int viewAdmin(staffdetail admin[]) {
//	FILE* fstaffdetail;
//	int lastIndex = readFile(admin);
//	int count = 0;
//
//	system("cls");
//	printf("%65s\n", "View Admin Information");
//	printf("%s\n", "========================================================================================================================");
//	printf("%-7s %-15s %-15s %-25s %-7s %-13s %-20s %s\n", "StaffID", "Name", "IC", "Email", "Gender", "Position", "ContactNumber", "Birthdate");
//	printf("%s\n", "========================================================================================================================");
//
//	for (int i = 0;i < lastIndex;i++) {
//		printf("%-7s %-15s %-15s %-25s %-7c %-13s %-20s %02d-%02d-%04d\n", admin[i].id, admin[i].username, admin[i].iC, admin[i].email, admin[i].gender, admin[i].position, admin[i].contactNumber, admin[i].birth.day, admin[i].birth.month, admin[i].birth.year);
//		count++;
//	}
//	printf("%s\n", "========================================================================================================================");
//	printf("\n%65s %d\n\n", "Total admin is", count);
//	return managerMenu(admin);
//}
//
// // search admin
//int searchAdmin(staffdetail admin[]) {
//	FILE* fstaffdetail;
//	char name[51];
//	char gender;
//	int lastIndex = readFile(admin);
//	int count = 0;
//	int error, found;
//	printf("\t\t\t\t============================================\n");
//	printf("\t\t\t\t=        Search Admin Information          =\n");
//	printf("\t\t\t\t============================================\n");
//
//	do {
//		error = 0;
//		printf("\t\t Enter Admin name:");
//		rewind(stdin);
//		scanf("%[^\n]", &name);
//		validationName(&error, name);
//
//	} while (error == 1);
//
//	do {
//		error = 0;
//		printf("\t\t Enter Admin Gender:");
//		rewind(stdin);
//		scanf("%c", &gender);
//		validationGender(&error, gender);
//
//	} while (error == 1);
//	system("cls");
//	printf("%65s\n", "Search Admin Information");
//	printf("%s\n", "========================================================================================================================");
//	printf("%-7s %-15s %-15s %-25s %-7s %-13s %-20s %s\n", "staffID", "Name", "IC", "Email", "Gender", "Position", "ContactNumber", "Birthdate");
//	printf("%s\n", "========================================================================================================================");
//	found = 0;
//	for (int i = 0;i < lastIndex;i++) {
//		if (strcmp(name, admin[i].username) == 0) {
//			if (gender == admin[i].gender) {
//				printf("%-7s %-15s %-15s %-25s %-7c %-13s %-20s %02d-%02d-%04d\n", admin[i].id, admin[i].username, admin[i].iC, admin[i].email, admin[i].gender, admin[i].position, admin[i].contactNumber, admin[i].birth.day, admin[i].birth.month, admin[i].birth.year);
//				count++;
//				found = 1;
//			}
//		}
//	}
//	if (found == 1) {
//		printf("%s\n", "========================================================================================================================");
//		printf("\n%65s %d\n\n", "Total record is", count);
//	}
//	else {
//		errorMessage(17);
//	}
//	return managerMenu(admin);
//}
//
//// add admin
//int addAdmin(staffdetail admin[]) {
//	FILE* fstaffdetail;
//	int lastIndex = readFile(admin);
//	int count = 0;
//	int id;
//	char idNo[7], ans;
//	int error;
//	int index;
//	staffdetail add;
//	system("cls");
//	printf("\t\t\t\t============================================\n");
//	printf("\t\t\t\t=          Add Admin Information           =\n");
//	printf("\t\t\t\t============================================\n");
//	count += lastIndex;
//	printf("\n\t\t\t\t%sNow Admin Information record have %d !!!%s\n\n", AC_YELLOW, count, AC_NORMAL);
//	do {
//		do {
//			error = 0;
//			if (count < MAX_ADMIN) {
//				printf("\t\t Add Admin ? (Y = Yes)(N = No):");
//				rewind(stdin);
//				scanf("%c", &ans);
//				validationselect(&error, ans);
//			}
//			else {
//				printf("\n\t\t\t\t%sAdmin record is maximum,record must be 100 only%s\n\n", AC_RED, AC_NORMAL);
//				return managerMenu(admin);
//			}
//		} while (error == 1);
//		if (toupper(ans) == 'Y') {
//			// Name
//			do {
//				error = 0;
//				printf("\t\t Enter Staff Username:");
//				rewind(stdin);
//				scanf("%[^\n]", &add.username);
//				validationName(&error, add.username);
//
//			} while (error == 1);
//
//			// IC
//			do {
//				error = 0;
//				printf("\t\t Enter Staff IC:");
//				rewind(stdin);
//				scanf("%s", &add.iC);
//				validationIC(&error, add.iC);
//
//			} while (error == 1);
//
//			// Email
//			do {
//				error = 0;
//				printf("\t\t Enter Staff E-mail:");
//				rewind(stdin);
//				scanf("%s", &add.email);
//				validationEmail(&error, add.email);
//
//			} while (error == 1);
//
//			// Gender
//			do {
//				error = 0;
//				printf("\t\t Enter Staff Gender[F/M]:");
//				rewind(stdin);
//				scanf("%c", &add.gender);
//				validationGender(&error, add.gender);
//
//			} while (error == 1);
//
//			// contact number
//			do {
//				error = 0;
//				printf("\t\t Enter Staff Contact Number[012-3456789]:");
//				rewind(stdin);
//				scanf("%s", &add.contactNumber);
//				validationContactNumber(&error, add.contactNumber);
//
//			} while (error == 1);
//
//			 // position
//			do {
//				error = 0;
//				printf("\t\t Enter Staff position:");
//				rewind(stdin);
//				scanf("%[^\n]", &add.position);
//				validationPosition(&error, add.position);
//
//			} while (error == 1);
//
//			 // password
//			do {
//				error = 0;
//				printf("\t\t Enter Staff Password[8-15 alphabets or numbers]:");
//				rewind(stdin);
//				scanf("%s", &add.password);
//				validationPw(&error, add.password);
//
//			} while (error == 1);
//
//			 // Date
//			do {
//				error = 0;
//				printf("\t\t Enter birthday[dd-mm-yyyy] :");
//				rewind(stdin);
//				scanf(" %02d-%02d-%04d", &add.birth.day, &add.birth.month, &add.birth.year);
//				validationbirthdate(&error, add.birth.day, add.birth.month, add.birth.year);
//
//			} while (error == 1);
//
//			//generate id
//			index = lastIndex - 1;
//			sscanf(admin[index].id, "%[^0-9]%d", &admin[lastIndex].id, &id);
//			id++;
//
//			// turn idNo from integer to string
//			itoa(id, idNo, 10);
//			strcat(admin[lastIndex].id, idNo);
//			printf("\n\t\t\t\t\t%sNew id is %s%s\n", AC_YELLOW, strcat(admin[lastIndex].id, idNo), AC_NORMAL);
//
//			strcpy(admin[lastIndex].id , admin[lastIndex].id);
//			strcpy(admin[lastIndex].username, add.username);
//			strcpy(admin[lastIndex].iC, add.iC);
//			strcpy(admin[lastIndex].email, add.email);
//			admin[lastIndex].gender = add.gender;
//			strcpy(admin[lastIndex].contactNumber, add.contactNumber);
//			strcpy(admin[lastIndex].position, add.position);
//			strcpy(admin[lastIndex].password, add.password);
//			admin[lastIndex].birth.day = add.birth.day;
//			admin[lastIndex].birth.month = add.birth.month;
//			admin[lastIndex].birth.year = add.birth.year;
//			fstaffdetail = fopen("staffadmin.txt", "a");
//			fprintf(fstaffdetail, "%s|%s|%s|%s|%c|%s|%s|%s|%02d-%02d-%04d\n", admin[lastIndex].id, admin[lastIndex].username, admin[lastIndex].iC, admin[lastIndex].email, admin[lastIndex].gender, admin[lastIndex].contactNumber, admin[lastIndex].position, admin[lastIndex].password, admin[lastIndex].birth.day, admin[lastIndex].birth.month, admin[lastIndex].birth.year);
//			lastIndex++;
//			fclose(fstaffdetail);
//
//			system("cls");
//			printf("\t\t\t\t\t%sAdd in successfully !%s\n", AC_GREEN, AC_NORMAL);
//			printf("\t\t\t\t\t%sPlease go to sign in !%s\n\n", AC_BLUE, AC_NORMAL);
//		}
//		else {
//
//			return managerMenu(admin);
//		}
//	} while (toupper(ans) == 'Y');
//	return managerMenu(admin);
//}
//
//// modify admin
//int editAdmin(staffdetail admin[]) {
//	FILE* fstaffdetail;
//	int lastIndex = readFile(admin);
//	int current;
//	int found;
//	char editId[7], ans;
//	int error;
//	staffdetail edit;
//	int check;
//	system("cls");
//	printf("\t\t\t\t============================================\n");
//	printf("\t\t\t\t=          Modify Admin Information        =\n");
//	printf("\t\t\t\t============================================\n");
//	do {
//		do {
//			check = 0;
//			do {
//				error = 0;
//				printf("\t\tEnter Admin ID:");
//				rewind(stdin);
//				scanf("%[^\n]", &editId);
//				validationID(&error, editId);
//			} while (error == 1);
//
//			printf("%65s\n", "Modify Admin Information");
//			printf("%s\n", "========================================================================================================================");
//			printf("%-7s %-15s %-15s %-25s %-7s %-13s %-20s %s\n", "StaffID", "Name", "IC", "Email", "Gender", "Position", "ContactNumber", "Birthdate");
//			printf("%s\n", "========================================================================================================================");
//
//			for (current = 0;current < lastIndex;current++) {
//				if (strcmp(editId, admin[current].id) == 0) {
//					printf("%-7s %-15s %-15s %-25s %-7c %-13s %-20s %02d-%02d-%04d\n", admin[current].id, admin[current].username, admin[current].iC, admin[current].email, admin[current].gender, admin[current].position, admin[current].contactNumber, admin[current].birth.day, admin[current].birth.month, admin[current].birth.year);
//
//					do {
//						error = 0;
//						printf("\n\t\t Enter Staff Username:");
//						rewind(stdin);
//						scanf("%[^\n]", &edit.username);
//						validationName(&error, edit.username);
//
//					} while (error == 1);
//
//					do {
//						error = 0;
//						printf("\t\t Enter Staff IC:");
//						rewind(stdin);
//						scanf("%s", &edit.iC);
//						validationIC(&error, edit.iC);
//
//					} while (error == 1);
//
//					do {
//						error = 0;
//						printf("\t\t Enter Staff E-mail:");
//						rewind(stdin);
//						scanf("%s", &edit.email);
//						validationEmail(&error, edit.email);
//
//					} while (error == 1);
//
//					do {
//						error = 0;
//						printf("\t\t Enter Staff Gender[F/M]:");
//						rewind(stdin);
//						scanf("%c", &edit.gender);
//						validationGender(&error, edit.gender);
//
//					} while (error == 1);
//
//					do {
//						error = 0;
//						printf("\t\t Enter Staff Contact Number[012-3456789]:");
//						rewind(stdin);
//						scanf("%s", &edit.contactNumber);
//						validationContactNumber(&error, edit.contactNumber);
//
//					} while (error == 1);
//
//					do {
//						error = 0;
//						printf("\t\t Enter Staff position:");
//						rewind(stdin);
//						scanf("%[^\n]", &edit.position);
//						validationPosition(&error, edit.position);
//
//					} while (error == 1);
//
//					do {
//						error = 0;
//						printf("\t\t Enter birthday[dd-mm-yyyy] :");
//						rewind(stdin);
//						scanf(" %02d-%02d-%04d", &edit.birth.day, &edit.birth.month, &edit.birth.year);
//						validationbirthdate(&error, edit.birth.day, edit.birth.month, edit.birth.year);
//
//					} while (error == 1);
//
//					strcpy(admin[current].id, editId);
//					strcpy(admin[current].username, edit.username);
//					strcpy(admin[current].iC, edit.iC);
//					strcpy(admin[current].email, edit.email);
//					admin[current].gender = edit.gender;
//					strcpy(admin[current].contactNumber, edit.contactNumber);
//					strcpy(admin[current].position, edit.position);
//					admin[current].birth.day = edit.birth.day;
//					admin[current].birth.month = edit.birth.month;
//					admin[current].birth.year = edit.birth.year;
//
//					printf("\n");
//					printf("%s\n", "========================================================================================================================");
//					printf("%-7s %-15s %-15s %-25s %-7s %-13s %-20s %s\n", "StaffID", "Name", "IC", "Email", "Gender", "Position", "ContactNumber", "Birthdate");
//					printf("%s\n", "========================================================================================================================");
//
//					printf("%-7s %-15s %-15s %-25s %-7c %-13s %-20s %02d-%02d-%04d\n", admin[current].id, admin[current].username, admin[current].iC, admin[current].email, admin[current].gender, admin[current].position, admin[current].contactNumber, admin[current].birth.day, admin[current].birth.month, admin[current].birth.year);
//					check++;
//				}
//			}
//			if (check != 1) {
//				printf("\n%s %65s %s\n", AC_RED, "Invalid Id,No record found", AC_NORMAL);
//			}
//			do {
//				error = 0;
//				printf("\n\t\t Any more record to modify ? (Y = Yes)(N = No):");
//				rewind(stdin);
//				scanf("%c", &ans);
//				validationselect(&error, ans);
//				system("cls");
//			} while (error == 1);
//		} while (toupper(ans) == 'Y');
//	} while (check == 0);
//
//
//	fstaffdetail = fopen("staffadmin.txt", "w");
//	if (fstaffdetail == NULL)
//	{
//		printf("\t\tUnable to open the file\n");
//		exit(-1);
//	}
//	for (int i = 0;i < lastIndex;i++) {
//		fprintf(fstaffdetail, "%s|%s|%s|%s|%c|%s|%s|%s|%02d-%02d-%04d\n", admin[i].id, admin[i].username, admin[i].iC, admin[i].email, admin[i].gender, admin[i].contactNumber, admin[i].position, admin[i].password, admin[i].birth.day, admin[i].birth.month, admin[i].birth.year);
//	}
//	fclose(fstaffdetail);
//	printf("\t\t\t\t\t\t%sEdit in successfully !%s\n\n", AC_GREEN, AC_NORMAL);
//	return managerMenu(admin);
//}
//
//// delete admin
//int deleteAdmin(staffdetail admin[]) {
//	int lastIndex = readFile(admin);
//	int error, check, current;
//	char confirmYesNo;
//	staffdetail deleteData;
//	FILE* fstaffdetail;
//
//	check = 0;
//	do {
//		do {
//			error = 0;
//			printf("\t\tEnter Admin ID:");
//			rewind(stdin);
//			scanf("%[^\n]", &deleteData.id);
//			validationID(&error, deleteData.id);
//
//		} while (error == 1);
//
//		for (int i = 0;i < lastIndex;i++) {
//			if (strcmp(deleteData.id, admin[i].id) == 0) {
//				printf("\t\t----------------------------------------------------------------------\n");
//				printf("\t\t-                             Confirmation:                          -\n");
//				printf("\t\t----------------------------------------------------------------------\n");
//
//				printf("%s\n", "========================================================================================================================");
//				printf("%-7s %-15s %-15s %-25s %-7s %-13s %-20s %s\n", "StaffID", "Name", "IC", "Email", "Gender", "Position", "ContactNumber", "Birthdate");
//				printf("%s\n", "========================================================================================================================");
//
//				printf("%-7s %-15s %-15s %-25s %-7c %-13s %-20s %02d-%02d-%04d\n", admin[i].id, admin[i].username, admin[i].iC, admin[i].email, admin[i].gender, admin[i].position, admin[i].contactNumber, admin[i].birth.day, admin[i].birth.month, admin[i].birth.year);
//				current = i;
//				check = 1;
//			}
//		}
//		if (check != 1) {
//			printf("\t\t\t\t\t\t%sInvalid ID %s", AC_RED, AC_NORMAL);
//		}
//		else {
//			do {
//				error = 0;
//				printf("\t\tConfirm Delete? (Y/N): ");
//				rewind(stdin);
//				scanf("%c", &confirmYesNo);
//				confirmYesNo = toupper(confirmYesNo);
//
//				if (confirmYesNo != 'Y' && confirmYesNo != 'N') {
//					error = 1;
//				}
//				if (confirmYesNo == 'Y') {
//					for (int i = current;i < lastIndex - 1;i++) {
//						admin[i] = admin[i + 1];
//					}
//					lastIndex--;
//				}
//				else {
//					managerMenu(admin);
//				}
//				if (error == 1) {
//					errorMessage(1);
//				}
//			} while (error == 1);
//		}
//
//	} while (check == 0);
//	FILE* deleteAdmin;
//	deleteAdmin = fopen("staffadmin.txt", "w");
//	if (deleteAdmin == NULL) {
//		printf("\t\tUnable to open file");
//		exit(-1);
//	}
//	for (int i = 0;i < lastIndex;i++) {
//		fprintf(deleteAdmin, "%s|%s|%s|%s|%c|%s|%s|%s|%02d-%02d-%04d\n", admin[i].id, admin[i].username, admin[i].iC, admin[i].email, admin[i].gender, admin[i].contactNumber, admin[i].position, admin[i].password, admin[i].birth.day, admin[i].birth.month, admin[i].birth.year);
//	}
//	fclose(deleteAdmin);
//	return managerMenu(admin);
//}
//
// // validation check  Name
//int validationName(int* error, char username[]) {
//	int countlength = strlen(username);
//	*error = 0;
//	for (int i = 0;i < countlength;i++) {
//		if (!isalpha(username[i]) && !isspace(username[i])) {
//			*error = 1;
//		}
//	}
//	if (*error != 0) {
//		errorMessage(1);
//	}
//	return *error;
//}
//
//// validation check ic
//int validationIC(int* error, char ic[]) {
//	*error = 0;
//	int countlength = strlen(ic);
//	for (int i = 0;i < countlength;i++) {
//		if (!isdigit(ic[i])) {
//			*error = 1;
//		}
//	}
//	if (*error != 0) {
//		errorMessage(2);
//	}
//	return *error;
//}
//
//// validation check email
//int validationEmail(int* error, char email[]) {
//	int at_count = 0, dot_count = 0;
//	*error = 0;
//	// validation check of '@' and '.'
//	int countlength = strlen(email);
//	for (int i = 0; i < countlength; i++) {
//		if (email[i] == '@') {
//			at_count++;
//		}
//		else if (email[i] == '.') {
//			dot_count++;;
//		}
//	}
//	if (at_count != 1 || dot_count != 1) {
//		*error = 1;
//	}
//	if (*error != 0) {
//		errorMessage(3);
//	}
//	return *error;
//}
//
//// validation check Gender
//int validationGender(int* error, char gender[]) {
//	*error = 0;
//	if (toupper(gender != 'F') && toupper(gender != 'M')) {
//		*error = 1;
//	}
//	if (*error != 0) {
//		errorMessage(4);
//	}
//	return *error;
//}
//
//// validation check contact number
//int validationContactNumber(int* error, char cNumber[]) {
//	*error = 0;
//	int i;
//	int countlength = strlen(cNumber);
//	if (countlength < 11 || countlength > 12) {
//		errorMessage(5);
//		*error = 1;
//	}
//	if (cNumber[3] != '-') {
//		errorMessage(6);
//		*error = 1;
//	}
//
//	for (i = 0;i < 3;i++) {
//		if (!isdigit(cNumber[i])) {
//			*error = 1;
//		}
//	}
//
//	for (i = 4;i < countlength;i++) {
//		if (!isdigit(cNumber[i])) {
//			*error = 1;
//		}
//	}
//	for (i = 0;i < countlength;i++) {
//		if (isspace(cNumber[i])) {
//			*error = 1;
//		}
//	}
//	if (*error != 0) {
//		errorMessage(7);
//	}
//	return *error;
//}
//
//// validation check position 
//int validationPosition(int* error, char position[]) {
//	*error = 0;
//	int countlength = strlen(position);
//	for (int i = 0;i < countlength; i++) {
//		if (!isalpha(position[i])) {
//			*error = 1;
//		}
//	}
//	if (*error != 0) {
//		errorMessage(8);
//	}
//	return *error;
//}
//
//// validation check password
//int validationPw(int* error, char pw[]) {
//	*error = 0;
//	int countlength = strlen(pw);
//	if (countlength < 8 || countlength > 15) {
//		*error = 1;
//	}
//	if (*error != 0) {
//		errorMessage(9);
//	}
//	return *error;
//}
//
//// validation check birthdate
//int validationbirthdate(int* error, int day[], int month[], int year[]) {
//
//	time_t seconds = time(NULL);
//	struct Date* current_time = localtime(&seconds);
//
//	SYSTEMTIME t;
//	GetLocalTime(&t);
//
//	*error = 0;
//	if (day <= 0 || day > 31) {
//		errorMessage(12);
//		*error = 1;
//	}
//
//	if (month <= 0 || month > 12) {
//		errorMessage(13);
//		*error = 1;
//	}
//
//	int currentYear = t.wYear;
//	int y = year;
//	int age = currentYear - y;
//
//	if (age < 18 || age > 60) {
//		errorMessage(14);
//		*error = 1;
//	}
//	return *error;
//}
//
// // validation check ID
//int validationID(int* error, char id[]) {
//	*error = 0;
//	for (int i = 0;i < 2;i++) {
//		if (!isalpha(id[i]) || !isupper(id[i])) {
//			*error = 1;
//			errorMessage(10);
//		}
//	}
//
//	int countlength = strlen(id);
//	for (int i = 2;i < countlength;i++) {
//		if (!isdigit(id[i]) && isspace(id[i])) {
//			*error = 1;
//		}
//	}
//	if (*error == 1) {
//		errorMessage(11);
//	}
//	return *error;
//}
//
//int validationselect(int* error, char ans) {
//	*error = 0;
//	if (toupper(ans != 'Y') && toupper(ans != 'N')) {
//		*error = 1;
//	}
//	if (*error == 1) {
//		errorMessage(18);
//	}
//	return *error;
//}
//
//// error msg for validation check 
//void errorMessage(int e) {
//	int error = e;
//	switch (error)
//	{
//	case 1:
//		printf("\t\t%s Invalid Name,Name must be in character.%s\n", AC_RED, AC_NORMAL);
//		break;
//	case 2:
//		printf("\t\t%s Invalid IC,IC number must be digit.%s\n", AC_RED, AC_NORMAL);
//		break;
//	case 3:
//		printf("\t\t%s Invalid Email,Email must be between '@' and '.'.%s\n", AC_RED, AC_NORMAL);
//		break;
//	case 4:
//		printf("\t\t%s Invalid Gender,Gender must be 'F' or 'M'.%s\n", AC_RED, AC_NORMAL);
//		break;
//	case 5:
//		printf("\t\t%s Contact number must be in 11 t0 12 numbers.%s\n", AC_RED, AC_NORMAL);
//		break;
//	case 6:
//		printf("\t\t%s Missing character '-'.%s\n", AC_RED, AC_NORMAL);
//		break;
//	case 7:
//		printf("\t\t%s Contact number must be in format '012-3456789'.%s\n", AC_RED, AC_NORMAL);
//		break;
//	case 8:
//		printf("\t\t%s Invalid position,Position must be in character\n %s", AC_RED, AC_NORMAL);
//		break;
//	case 9:
//		printf("\t\t%s Invalid Password,Password must be consist of 8 to 12 alphabets and numbers.%s\n", AC_RED, AC_NORMAL);
//		break;
//	case 10:
//		printf("\t\t%s Invalid ID,First character of ID must be uppercase alphabet %s.\n", AC_RED, AC_NORMAL);
//		break;
//	case 11:
//		printf("\t\t%s StaffAdmin ID must be in format 'AD1001'%s\n", AC_RED, AC_NORMAL);
//		break;
//	case 12:
//		printf("\t\t%s Invalid day. Day must be 1 to 31.%s\n", AC_RED, AC_NORMAL);
//		break;
//	case 13:
//		printf("\t\t%s Invalid month. Month must be 1 to 12.%s\n", AC_RED, AC_NORMAL);
//		break;
//	case 14:
//		printf("\t\t%s Invalid year.%s\n", AC_RED, AC_NORMAL);
//		break;
//	case 15:
//		printf("\t\t%s Password are not same.%s\n", AC_RED, AC_NORMAL);
//		break;
//	case 16:
//		printf("\n\t\t\t\t%sYour ID or password is wrong, try again!%s\n\n", AC_RED, AC_NORMAL);
//		break;
//	case 17:
//		printf("\n\t\t\t\t\t\t%sNo record !!!%s\n\n", AC_RED, AC_NORMAL);
//		break;
//	case 18:
//		printf("\n\t\t\t\t%sInvalid,please select Y = (Yes) or N = (No)%s\n", AC_RED, AC_NORMAL);
//		break;
//	default:
//		break;
//	}
//}
