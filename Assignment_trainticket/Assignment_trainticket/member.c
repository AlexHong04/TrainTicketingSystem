//// 0 for exit program
////记得把test debug删掉
////staff 看
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<time.h>
//#include<math.h>
//#include<ctype.h>
//#include<stdbool.h>
//#pragma warning (disable : 4996)
////MEMBER INFORMATION MODULE START
//
////define
//#define IC_LENGTH 12
//#define HP_LENGTH 10
//#define MAX_MEMBER 100
//#define MEMBER_ID 7
//#define MAX_MEMBER 100
//#define CAPTCHA_LENGTH 4
//
////member information 
//typedef struct
//{
//	char memberId[20];
//	char name[30];
//	char password[20];
//	char rePassword[20];
//	char gender;
//	char IC[13];
//	char contact_number[11];
//	char email[30];
//
//}Member;
//
//void toUpperCase(char* str);
//void loadMembers(Member members[], int* memberCount);
//void saveMembers(Member members[], int* memberCount);
//void appendMember(Member newMember);
//int allDigit(const char* str);
//void getEmail(const char* email);
//int validEmail(const char* email);
//void modifyPassword(Member members[], int memberCount);
//void forgotandFind(Member members[], int memberCount);
//void deleteAccount(Member members[], int* memberCount);
//void memberRegister(Member members[], int* memberCount);
//void staff_maintain_member(Member members[], int memberCount);
//void searchMember(Member member[], int memberCount);
//void staff_maintain_menu(Member members[]);
//void bookandtrain();
//void memberLogin(Member members[], int memberCount);
//void memberMenu(Member members[], int memberCount);
//void member();
//
//void main()
//{
//	
//	member();
//
//
//	system("pause");
//}
//
////转string大写
//void toUpperCase(char* str)
//{
//	while (*str)
//	{
//		*str = toupper((unsigned char)*str);
//		str++;
//	}
//}
//
////read file array
//void loadMembers(Member members[], int* memberCount)
//{
//
//	FILE* loadFile = fopen("final.dat", "rb");
//	if (loadFile == NULL) {
//		printf("\t\t\t\033[0;32mNo member registered, please ask user to register an account\033[0m\n\n");
//		return;
//	}
//
//	(*memberCount) = 0;
//
//	while (fread(&members[*memberCount], sizeof(Member), 1, loadFile))
//	{
//		(*memberCount)++;
//
//	}
//	fclose(loadFile);
//}
//
//void saveMembers(Member members[], int* memberCount)
//{
//
//	FILE  *saveFile = fopen("final.dat", "wb");
//	if (saveFile == NULL)
//	{
//		printf("\t\tError opening file");
//		return;
//	}
//
//	for (int i = 0; i < memberCount; i++)
//	{
//		fwrite(&members[i], sizeof(Member), 1, saveFile);
//	}
//
//	fclose(saveFile);
//}
//
////ADD new member(add)
//void appendMember(Member newMember)
//{
//	FILE* appendFile = fopen("final.dat", "ab");
//	if (appendFile == NULL)
//	{
//		printf("\t\tError opening file");
//		return;
//	}
//
//	fwrite(&newMember, sizeof(Member), 1, appendFile);
//
//	fclose(appendFile);
//}
//
////check the string is all number
//int allDigit(const char* str)
//{
//	for (int i = 0; str[i] != '\0'; i++)
//	{
//		if (!isdigit(str[i]))
//		{
//			return 0;
//		}
//	}
//
//	return 1;
//}
////get user email
//void getEmail(const char* email)
//{
//	int valid = 0;
//
//	while (!valid)
//	{
//		printf("\t\tEnter your email:");
//		scanf("\t\t%29s", email);
//		rewind(stdin);
//
//		if (validEmail(email))
//		{
//			valid = 1;
//		}
//		else
//		{
//			printf("\t\tInvalid Email Format, Please Try Again (Invalid Format: \033[0;33mXXX@gmail.com)\033[0m\n");
//		}
//
//	}
//}
//
////email format check
//int validEmail(const char* email)
//{
//	int atCount = 0;//@
//	int dotCount = 0;//.
//	int lenEmail = strlen(email);
//
//	if (!isalpha(email[0]))
//	{
//		printf("\t\tFirst character should be letter\n");
//		return 0;
//	}
//
//	for (int i = 0; i < lenEmail; i++)
//	{
//		char c = email[i];
//
//		if (c == '@')
//		{
//			atCount++;
//		}
//		else if (c == '.')
//		{
//			dotCount++;
//		}
//
//		if (!isalnum(c) && c != '.' && c != '@')
//		{
//			return 0;
//		}
//
//	}
//
//	if (atCount != 1 || dotCount < 1 || email[lenEmail - 1] == '.' || email[lenEmail - 1] == '@')
//	{
//		return 0;
//	}
//
//	const char* gmailCheck = "@gmail.com";
//	const char* emailCheck = email + lenEmail - strlen(gmailCheck);
//
//	if (strcmp(emailCheck, gmailCheck) != 0)
//	{
//		return 0;
//	}
//
//	return 1;
//}
//
////reset password(modify)
//void modifyPassword(Member members[], int memberCount)//会中毒
//{
//	Member input_reset_password;
//	int found = 0;
//	char newPassword[20] = {0};
//
//	printf("\t\tPlease enter your Member ID:");
//	scanf("%19s", input_reset_password.memberId);
//	toUpperCase(input_reset_password.memberId);
//	rewind(stdin);
//
//	printf("\t\tPlease enter your IC Number:");
//	scanf("%13s", input_reset_password.IC);
//	rewind(stdin);
//
//	for (int i = 0; i < memberCount; i++)
//	{
//		if (strcmp(members[i].memberId, input_reset_password.memberId) == 0 && strcmp(members[i].IC, input_reset_password.IC) == 0)
//		{
//			printf("\t\tMember ID and IC Number verified. You can enter your new password now\n");
//			printf("\t\tPlease enter your new password:");
//			scanf("%20s", newPassword);
//
//			strcpy(members[i].password, newPassword);
//			printf("\t\tYour Account Password reset successfully!\n");
//			found = 1;
//
//		}
//	}
//
//	if (!found)
//	{
//		printf("\t\tMember not exists, please try again\n");
//	}
//	else
//	{
//		saveMembers(members, memberCount);
//	}
//	
//
//}
//
//void forgotandFind(Member members[], int memberCount) 
//{
//	Member forgot;
//	int found = 0;
//	char verifEmail[30] = {0};
//	int attemp = 0;
//
//	while (attemp < 3 && !found) {
//		printf("\t\tEnter Your IC Number:");
//		scanf("%13s", forgot.IC);
//		rewind(stdin);
//
//		for (int i = 0; i < memberCount; i++) {
//			if (strcmp(members[i].IC, forgot.IC) == 0) {
//				found = 1;
//				printf("\n\t\tMember found! Please enter your binding email to get back your password\n");
//				printf("\t\tYour binding email:");
//				scanf("%29s", verifEmail);
//				rewind(stdin);
//
//				if (strcmp(members[i].email, verifEmail) == 0) {
//					char randomCaptcha[CAPTCHA_LENGTH + 1];
//					const char* captchaChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
//
//					srand(time(NULL));  // Ensure random seed for captcha generation
//					for (int j = 0; j < CAPTCHA_LENGTH; j++) {
//						int numC = rand() % 62;
//						randomCaptcha[j] = captchaChars[numC];
//					}
//					randomCaptcha[CAPTCHA_LENGTH] = '\0';
//
//					char userCaptcha[CAPTCHA_LENGTH + 1] = {0};
//					printf("\t\tPlease enter the captcha code to complete the progress: \033[0;33m%s\033[0m\n", randomCaptcha);
//					printf("\t\tPlease enter the generated captcha:");
//					do {
//						scanf("%4s", userCaptcha);
//						rewind(stdin);
//
//						if (strcmp(randomCaptcha, userCaptcha) == 0) {
//							printf("\t\tCaptcha verified successfully!\n");
//							printf("\t\tOur HONORABLE Member, your account password is \033[0;33m%s\033[0m\n", members[i].password);
//							return;  // End function after successful password recovery
//						}
//						else {
//							printf("\t\tIncorrect Captcha, please try again\n");
//						}
//					} while (strcmp(randomCaptcha, userCaptcha) != 0);
//				}
//				else {
//					printf("\t\tEmail not correct! Security system active\n");
//					exit(0);
//				}
//			}
//		}
//
//		if (!found) {
//			printf("\t\tInvalid IC, Member not found!\n");
//			attemp++;
//		}
//	}
//
//	if (attemp >= 3 && !found) {
//		printf("\t\tTry Attempt exceed limit. Please try later\n");
//		exit(0);
//	}
//}
//
//
//void deleteAccount(Member members[], int* memberCount)
//{
//	Member inputDelete;
//	int deleteConfirm;
//	int found = 0;
//	
//	printf("\t\tEnter the Member ID of the account you want to delete:");
//	scanf("%19s", inputDelete.memberId);
//	toUpperCase(inputDelete.memberId);
//	rewind(stdin);
//
//	printf("\t\tEnter the password of the account you want to delete\033[0;33m(Please check if the letter is in uppercase or lowercase):\033[0m");
//	scanf("%19s", inputDelete.password);
//	rewind(stdin);
//
//
//	int index = 0;
//	int memCount = memberCount;
//	for (int i = 0; i < memCount; i++)
//	{
//		if (strcmp(members[i].memberId, inputDelete.memberId) == 0 && strcmp(members[i].password, inputDelete.password) == 0) {
//			index = i;
//			found = 1;
//			memCount--;
//			
//		}
//	}
//
//	for (int i = index; i < memCount; i++)
//	{
//		members[i] = members[i + 1];
//	}
//	
//	if (index == memCount - 1)
//	{
//		strcpy(members[memCount - 1].memberId, "DUMMY");
//		strcpy(members[memCount - 1].name, "DUMMY");
//		strcpy(members[memCount - 1].password, "DUMMY");
//		strcpy(members[memCount - 1].gender, 'D');
//		strcpy(members[memCount - 1].IC, "DUMMY");
//		strcpy(members[memCount - 1].contact_number, "DUMMY");
//		strcpy(members[memCount - 1].email, "DUMMY@gmail.com");
//	}
//
//	memberCount = memCount;
//	
//	if (!found)
//	{
//		printf("\t\tAccount not found or incorrect password.\n");
//	}
//	else 
//	{
//		
//
//		do
//		{
//			printf("\t\t\033[0;31mConfirm to delete your account? This will eliminate all your data!!\033[0m\n");
//			printf("\t\tConfirm enter 1\n");
//			printf("\t\tEXIT enter 2\n");
//			printf("\t\tPlease enter your option:");
//			scanf("%d", &deleteConfirm);
//			rewind(stdin);
//
//			switch (deleteConfirm)
//			{
//			case 1:
//
//				saveMembers(members, memberCount);
//				printf("\t\tYour account has been deleted\n");
//
//			case 2:
//				exit(0);
//				break;
//			default:
//				printf("\t\tInvalid option, please try again");
//				break;
//			}
//			
//		} while(deleteConfirm < 1 || deleteConfirm > 2);
//		
//		
//	}
//}
//
////this is whole member register program (SYSTEM 1)
//void memberRegister(Member members[], int* memberCount)
//{
//	printf("\t\t\t\t=======================================\n");
//	printf("\t\t\t\t||                                   ||\n");
//	printf("\t\t\t\t||        MEMBER REGISTATION         ||\n");
//	printf("\t\t\t\t||                                   ||\n");
//	printf("\t\t\t\t=======================================\n\n");
//
//
//	if (*memberCount > MAX_MEMBER)
//	{
//		printf("\t\t\tMember limit reached, cannot register more members.\n");
//		return;
//	}
//
//	Member* newMember = &members[*memberCount];
//
//	int validName;
//	do
//	{
//		validName = 1;
//		int i = 0;
//
//		printf("\t\tEnter Your Account Username\033[0;34m(name do not be space)\033[0m:");
//		scanf("%49s", newMember->name);
//		rewind(stdin);
//
//		while (newMember->name[i] != '\0' && validName)
//		{
//			if (!isalpha(newMember->name[i]))
//			{
//				validName = 0;
//				system("cls");
//				printf("\t\tInvalid Symbol Exist, Please try again\n");
//
//			}
//			i++;
//		}
//
//
//
//	} while (validName == 0);
//
//	int passwordMatch = 0;
//	while (!passwordMatch)
//	{
//		char tempPassword[15] = {0};
//		printf("\t\tEnter Your Password (min 8 character):");
//		scanf("%19s", tempPassword);
//		rewind(stdin);
//
//		if (strlen(tempPassword) >= 8)
//		{
//			printf("\t\t\033[0;33mRe-Enter Your Password:\033[0m");
//			scanf("%19s", newMember->rePassword);
//			rewind(stdin);
//
//			if (strcmp(tempPassword, newMember->rePassword) == 0)
//			{
//				strcpy(newMember->password, tempPassword);
//				passwordMatch = 1;
//			}
//			else
//			{
//				printf("\t\tThe Password not match, Please enter again!\n");
//			}
//		}
//		else
//		{
//			printf("\t\tYour password too short, please enter at least 8 character\n");
//		}
//
//
//
//	}
//
//	int validGender = 0;
//	while (!validGender)
//	{
//		printf("\t\tEnter Your Gender(F/M/O):");
//		scanf(" %c", &newMember->gender);
//		rewind(stdin);
//		newMember->gender = toupper(newMember->gender);
//
//		if (newMember->gender == 'F' || newMember->gender == 'M' || newMember->gender == 'O')
//		{
//			validGender = 1;
//		}
//		else
//		{
//			printf("\t\tInvalid Gender, Please Enter M(Male) or F(Female) or O(Other)\n");
//		}
//	}
//
//	int validIC = 0;
//	while (!validIC)
//	{
//		printf("\t\tEnter Your IC/MyKad Number:");
//		scanf("%13s", newMember->IC);
//		rewind(stdin);
//
//		int uniIC = 1;
//	
//		for (int i = 0; i < *memberCount; i++)
//		{
//			if (strcmp(members[i].IC, newMember->IC) == 0)
//			{
//				uniIC = 0;
//				
//			}
//		}
//
//		if (uniIC && (strlen(newMember->IC) == IC_LENGTH && allDigit(newMember->IC)))
//		{
//			validIC = 1;
//		}
//		else
//		{
//			if (!uniIC)
//			{
//				printf("\t\tThis IC Number has been registered, please try another IC Number");
//			}
//			else
//			{
//				printf("\t\tInvalid IC/MyKad Number. It should be 12 digits longs and does not contain symbol\n");
//			}
//			
//
//		}
//	}
//
//	int validHP = 0;
//	while (!validHP)
//	{
//		printf("\t\tEnter Contact/HP Number:");
//		scanf("%10s", newMember->contact_number);
//		rewind(stdin);
//
//		if (strlen(newMember->contact_number) == HP_LENGTH && allDigit(newMember->contact_number))
//		{
//			if (newMember->contact_number[0] == '0' && newMember->contact_number[1] == '1')
//			{
//				validHP = 1;
//			}
//			else
//			{
//				printf("\t\tInvalid Contact Number format. It should start with '01'\n");
//			}
//		}
//		else
//		{
//			printf("\t\tInvalid Hand-Phone Number. It should be 10 digits longs and does not contain symbol\n");
//		}
//	}
//
//	getEmail(newMember->email);
//
//
//	//generate ID
//	const char* prefix = "M";
//	char randomNumber[MEMBER_ID + 1];
//
//	int num = rand() % 100000;
//	int i = MEMBER_ID - 2;
//	for (;i >= 0; i--)
//	{
//		randomNumber[i] = '0' + num % 10;
//		num = num / 10;
//	}
//
//	randomNumber[MEMBER_ID - 1] = '\0';
//
//	strcpy(newMember->memberId, prefix);
//	strcat(newMember->memberId, randomNumber);
//
//	
//	char randomCaptcha[CAPTCHA_LENGTH + 1];
//	const char* captchaChar = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyxz0123456789";
//	
//	for (int i = 0; i < CAPTCHA_LENGTH; i++)
//	{
//		int numC = rand() % 62;
//		randomCaptcha[i] = captchaChar[numC];
//	}
//	randomCaptcha[CAPTCHA_LENGTH] = '\0';
//	
//	char userCaptcha[CAPTCHA_LENGTH + 1] = {0};
//	int validCaptcha = 0;
//	printf("\n\t\tPlease enter the captcha code to complete the registration: \033[0;33m%s\033[0m\n\n", randomCaptcha);
//	printf("\t\tPlease enter the generated captcha:");
//	while (!validCaptcha)
//	{
//		if (scanf("%4s", userCaptcha) != 1)
//		{
//			rewind(stdin);
//			printf("\t\tInvalid input, please try again");
//		}
//		else
//		{
//			if (strcmp(randomCaptcha, userCaptcha) == 0)
//			{
//				validCaptcha = 1;
//				system("cls");
//				printf("\t\tCaptcha verificate successfully!\n");
//			}
//			else
//			{
//				printf("\t\tIncorrect Captcha, please try again\n");
//			}
//		}
//		
//	}
//
//	if (validCaptcha)
//	{
//		printf("\t\tRegistration Completed. Welcome, %s. Your member ID is \033[38;5;46m%s\033[0m\n", newMember->name,newMember->memberId);
//		appendMember(*newMember);
//		(*memberCount)++;
//
//	}
//	
//	
//	
//
//}
//
//// display member information
//void staff_maintain_member(Member members[], int memberCount)
//{
//	
//	if (memberCount == 0)
//	{
//		printf("\n\t\tNo Member Registered\n");
//		return;
//
//	}
//
//
//	printf("\n");
//	printf("\n\t---------------------------------------| Registered Member |---------------------------------------\n\n");
//	printf("\t%-20s %-20s %-10s %-20s %-15s\n", "Member ID", "Member Name", "Gender", "Contact Number", "Email");
//	printf("\t---------------------------------------------------------------------------------------------------\n\n");
//
//	for (int i = 0; i < memberCount; i++)
//	{
//		printf("\t%-20s %-20s %-10c %-20s %-15s\n\n\n", members[i].memberId, members[i].name, members[i].gender, members[i].contact_number, members[i].email);
//	}
//
//}
//
//void searchMember(Member members[], int memberCount)
//{
//
//	char searchName[30];
//	int found = 0;
//
//	printf("\t\tEnter a user name: ");
//	scanf("%29s", searchName);
//
//	for (int i = 0; i < memberCount; i++)
//	{
//		if (strcmp(members[i].name, searchName) == 0)
//		{
//			if (!found)
//			{
//				printf("\t\tMembers found:\n");
//				found = 1;
//			}
//			printf("\t\t-----------------------------\n");
//			printf("\t\tMember ID: %s\n", members[i].memberId);
//			printf("\t\tName: %s\n", members[i].name);
//			printf("\t\tGender: %c\n", members[i].gender);
//			printf("\t\tContact Number: %s\n", members[i].contact_number);
//			printf("\t\tEmail: %s\n\n", members[i].email);
//		}
//	}
//
//	if (!found)
//	{
//		printf("\t\tNo members found with the name '%s'.\n", searchName);
//	}
//}
//
//void staff_maintain_menu(Member members[])//这个是用来check 注册过的member的信息的
//{
//	int memberCount = 0;
//	loadMembers(members, &memberCount);
//	int staff_maintain_option;
//
//	do
//	{
//		printf("\t\t\t\t==========================================\n");
//		printf("\t\t\t\t||                                      ||\n");
//		printf("\t\t\t\t||      Staff Maintain Member Menu      ||\n");
//		printf("\t\t\t\t||                                      ||\n");
//		printf("\t\t\t\t==========================================\n");
//		printf("\t\t\t\t||                                      ||\n");
//		printf("\t\t\t\t||  1.Display Member information        ||\n");
//		printf("\t\t\t\t||  2.Search Member                     ||\n");
//		printf("\t\t\t\t||  3.Back To Menu                      ||\n");
//		printf("\t\t\t\t||                                      ||\n");
//		printf("\t\t\t\t==========================================\n\n");
//		printf("\t\tEnter you choice:");
//		if (scanf("%d", &staff_maintain_option) != 1)
//		{
//			rewind(stdin);
//			printf("\t\tInvalid Option, Please enter again\n");
//			staff_maintain_option = -1;
//		}
//		else
//		{
//			rewind(stdin);
//			switch (staff_maintain_option)
//			{
//			case 1:
//				staff_maintain_member(members, memberCount);
//				break;
//			case 2:
//				searchMember(members, memberCount);
//				break;
//			case 3:
//				memberMenu(members, memberCount);
//			default:
//				printf("\t\tInvalid Option, Please enter again\n");
//			}
//
//
//		}
//
//	} while (staff_maintain_option != 0);
//}
//
//void bookandtrain()
//{
//	int bookAndTrain;
//	do
//	{
//		printf("\t\t\t\t===================================================\n");
//		printf("\t\t\t\t||                                               ||\n");
//		printf("\t\t\t\t||         1.Book Your Favourite Ticket Now      ||\n");
//		printf("\t\t\t\t||         2.Train Schedule                      ||\n");
//		printf("\t\t\t\t||         0.Exit                                ||\n");
//		printf("\t\t\t\t||                                               ||\n");
//		printf("\t\t\t\t===================================================\n\n");
//
//		printf("\t\tEnter Your Option:");
//		if (scanf("%d", &bookAndTrain) != 1)
//		{
//			rewind(stdin);
//			printf("\t\tInvalid Option, Please enter again\n");
//			bookAndTrain = -1;
//		}
//		else
//		{
//			rewind(stdin);
//		}
//
//		switch (bookAndTrain)
//		{
//		case 1:
//			//go to booking
//			break;
//		case 2:
//			//train sch
//			break;
//		case 0:
//			exit(0);
//		default:
//			printf("\t\tInvalid Option, please enter again\n");
//
//		}bookAndTrain = 0;
//
//		
//
//
//		//go to book\schedule section
//	} while (bookAndTrain < 1 || bookAndTrain > 2);
//}
//
////void staffManage(Member members[])
////{
////	int memberCount = 0;
////	loadMembers(members, memberCount);
////	int staffOption;
////	do
////	{
////		printf("\t\t\t\t==========================================\n");
////		printf("\t\t\t\t||                                      ||\n");
////		printf("\t\t\t\t||  1.Member Information                ||\n");
////		printf("\t\t\t\t||  2.Schedule Information              ||\n");
////		printf("\t\t\t\t||  3.Back                              ||\n");
////		printf("\t\t\t\t||                                      ||\n");
////		printf("\t\t\t\t==========================================\n\n");
////		printf("\t\tEnter your option:");
////		scanf("%d", &staffOption);
////		rewind(stdin);
////
////		switch (staffOption)
////		{
////		case 1:
////			staff_maintain_menu(members, memberCount);
////			break;
////		case 2:
////			//yl schedule
////			break;
////		case 3:
////			memberMenu(members, memberCount);
////			break;
////		}
////
////
////	} while (staffOption < 1 || staffOption > 3);
////	
////}
//
////this is whole login part(search)
//void memberLogin(Member members[], int memberCount)
//{
//	Member inputLogin;
//	int foundPassword = 0;
//	int foundMember = 0;
//	int attempMember = 0;
//	int attempPassword = 0;
//	
//
//	printf("\t\t\t\t===========================================================================\n");
//	printf("\t\t\t\t||                                                                       ||\n");
//	printf("\t\t\t\t||                  Login to Your Registered Account                     ||\n");
//	printf("\t\t\t\t||                                                                       ||\n");
//	printf("\t\t\t\t===========================================================================\n\n");
//
//	while (attempMember < 3 && !foundMember)
//	{
//		printf("\t\tEnter your Account Member ID:");
//		if (scanf("%20s", inputLogin.memberId) != 1)
//		{
//			rewind(stdin);
//			printf("\t\tInvalid input, please try again\n");
//		}
//		else
//		{
//			rewind(stdin);
//			toUpperCase(inputLogin.memberId);
//
//
//			foundMember = 0;
//			for (int i = 0; i < memberCount; i++)
//			{
//				if (strcmp(members[i].memberId, inputLogin.memberId) == 0)
//				{
//					foundMember = 1;
//					printf("\n\t\tMember Found!\n\n");
//
//					while (true)
//					{
//						if (attempPassword < 3 && !foundPassword)
//						{
//							printf("\t\tEnter your account Password \033[0;33m(Please check if the letter is in uppercase or lowercase):\033[0m");
//							if (scanf("%20s", inputLogin.password) != 1)
//							{
//								rewind(stdin);
//								printf("\t\tInvalid input, please try again\n");
//								attempMember++;
//								attempPassword++;
//
//							}
//							else
//							{
//								rewind(stdin);
//
//								if (strcmp(members[i].password, inputLogin.password) == 0)
//								{
//									printf("\t\tLogin Successfully.Welcome, Our HONORABLE member, %s!\n", members[i].name);
//									foundPassword = 1;
//									bookandtrain();
//								}
//								else
//								{
//									printf("\t\tInvalid Password, please enter again\n");
//									attempPassword++;
//
//
//								}
//
//								if (attempPassword >= 3)
//								{
//									printf("\n\t\tAttempt Limit exceed, please try later\n");
//									exit(0);
//								}
//							}
//
//
//						}
//					}
//
//					return -1;
//				}
//			}
//		}
//		
//			
//
//		if (!foundMember)
//		{
//			printf("\t\tInvalid Member, please try again\n");
//			attempMember++;
//
//		}
//
//		if (attempMember >= 3)
//		{
//			printf("\n\t\tAttempt Limit exceed, please try later\n");
//			exit(0);
//		}
//
//
//
//
//	}
//
//
//}
//
////this is home page for member information module(主页)
//void memberMenu(Member members[], int memberCount)
//{
//	int memberOption;
//
//	do
//	{
//		printf("\t\t\t\t================================================\n");
//		printf("\t\t\t\t||                                            ||\n");
//		printf("\t\t\t\t||            MEMBER INFORMATION              ||\n");
//		printf("\t\t\t\t||                                            ||\n");
//		printf("\t\t\t\t================================================\n");
//		printf("\t\t\t\t||                                            ||\n");
//		printf("\t\t\t\t||  1.Register an new account                 ||\n");//add
//		printf("\t\t\t\t||  2.Login Account                           ||\n");//search
//		printf("\t\t\t\t||  3.Forgot and Find password                ||\n");//search
//		printf("\t\t\t\t||  4.Modify Password                         ||\n");// modify
//		printf("\t\t\t\t||  5.Delete your account                     ||\n");// modify
//		printf("\t\t\t\t||  6.Back                                    ||\n");
//		printf("\t\t\t\t||                                            ||\n");
//		printf("\t\t\t\t================================================\n");
//		printf("\n");
//		printf("\t\tEnter your option(1-6)\n");
//		printf("\t\tYour Option:");
//		if (scanf("%d", &memberOption) != 1)
//		{
//			rewind(stdin);
//			system("cls");
//			printf("\t\t\t\t\033[38;5;196mInvalid Option, Please try Again\033[0m\n\n");
//			memberOption = -1;
//		}
//		else
//		{
//			rewind(stdin);
//
//
//
//			switch (memberOption)
//			{
//			case 1:
//				memberRegister(members, &memberCount);
//				break;
//			case 2:
//				memberLogin(members, memberCount);
//				break;
//			case 3:
//				forgotandFind(members, memberCount);
//				break;
//			case 4:
//				modifyPassword(members, memberCount);
//				break;
//			case 5:
//				deleteAccount(members, memberCount);
//				break;
//			case 6:
//				//home page;
//				break;
//			default:
//				system("cls");
//				printf("\t\t\t\t\033[38;5;196mInvalid Option, Please try Again\033[0m\n\n");
//				break;
//			}
//
//		}memberOption = 0;
//		
//	} while (memberOption < 1 || memberOption > 5);
//
//}
//
//void member()
//{
//	Member member[MAX_MEMBER];
//	int memberCount = 0;
//	srand(time(NULL));
//
//	loadMembers(member, &memberCount);
//
//	memberMenu(member, memberCount);
//}
//
//
//
//
//
//
//
//
