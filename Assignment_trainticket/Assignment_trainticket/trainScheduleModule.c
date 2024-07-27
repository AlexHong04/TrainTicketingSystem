#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#pragma warning (disable:4996)

//define maximum amount
#define MAX_TRAIN 30
#define MAX_TIME 10
#define MAX_SEATCOL 10
#define MAX_SEATROW 8

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

//function declaration for validation check;
bool isValidTimeFormat(const char *time);
int validateStations(const char* departure, const char* arrival, const scheduleInfo* scheduleData);
int findValue(const char (*arr)[MAX_SEATROW], int size, const char* value);
int validateTrainID(const char *trainID);
int isValidDestination(const char *destination);
bool isSameDestination(const scheduleInfo scheduleData[], int scheduleCount, const char* destination);

//function declaration for write and read file
void writeData();
void readData(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]);

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
void checkSeatAvailability_n ();
void checkSeatAvailability_s ();

//for member and staff function

int main(int argc, char const *argv[])
{
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

        } else if (choice < 1 || choice > 5) 
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
                    printf("Exiting the program. Goodbye!\n");
                    break;
                default:
                    printf("Invalid number. Please enter again.\n");
                    break;
            }
        }
	} while (choice != 5);
    return 0;
}

bool isValidTimeFormat(const char *time) {
    if (strlen(time) == 5) 
    {
        if (time[2] != ':')
            return false;

        int hours = (time[0] - '0') * 10 + (time[1] - '0');
        int minutes = (time[3] - '0') * 10 + (time[4] - '0');
        
        if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
            return false;
    } else if (strcmp(time, "-") != 0 && strcmp(time, "TD") != 0 && strcmp(time, "TM") != 0) 
    {
        return false;
    }
    return true;
}

bool isSameDestination(const scheduleInfo scheduleData[], int scheduleCount, const char* destination) {
    for (int i = 0; i < scheduleCount; i++)
    {
        if (strcmp(scheduleData[i].destination, destination) == 0)
        {
            return true;
        }
    }
    return false;
}

int isValidDestination(const char *destination) {
    while (*destination) {
        if (!isalpha(*destination) && !isspace(*destination) && !ispunct(*destination)) {
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

void writeData () {
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

void readData(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]) {
    FILE* NSFile;
    NSFile = fopen("NSFile.bin", "rb");
    if (NSFile == NULL)
    {
        printf("Error opening file.\n");
        exit(-1);
    }
    for (int i = 0; i < MAX_TRAIN; i++)
    {
        fread(&northScheduleData[i], sizeof(scheduleInfo), 1, NSFile);
    }
    for (int i = 0; i < MAX_TRAIN; i++)
    {
        fread(&southScheduleData[i], sizeof(scheduleInfo), 1, NSFile);
    }

}

void viewNorthSouthSchedule(scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]) {
    
    char confirm;
    int answer;

        do {
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

            if (answer < 1 || answer > 4) 
            {
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
            } 
            else 
            {
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
                        printf("Proceeding without viewing schedule.\n");
                        break;
                    default:
                        printf("Invalid choice. Please enter a number between 1 and 4.\n");
                        break;
                }
            }
        } 
        else if (toupper(confirm) == 'N') {
            printf("Proceeding without viewing schedule.\n");
        } 
        else {
            printf("Invalid input. Enter Y or N only.\n");
        }
    } while (toupper(confirm) != 'Y' && toupper(confirm) != 'N');

    printf("\n");
}

void search( scheduleInfo northScheduleData[], scheduleInfo southScheduleData[]) {
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
        if (strcmp(northScheduleData[i].trainID.trainId, "") !=0 )
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

void displaySouthSchedule (scheduleInfo southScheduleData[]){

    printf("\n\nSouth Way Train Schedule:\n\n");
    printf("| %-20s |", "DESTINATION");
    for (int i = 0; i < MAX_TRAIN; i++) {
        if (strcmp(southScheduleData[i].trainID.trainId, "") !=0 ){
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
                if (!isValidDestination(northScheduleData[scheduleCount].destination)) {
                    printf("Invalid destination format.\n");
                    printf("\n");
                }
                if (isSameDestination(northScheduleData, scheduleCount, northScheduleData[scheduleCount].destination)) {
                    printf("Destination already exists. Please enter a different destination.\n");
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
                    printf("Invalid format. Enter time in HH:MM format or '-' only: ");
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
                if (!isValidDestination(southScheduleData[scheduleCount].destination)) {
                    printf("Invalid destination format.\n");
                }
                if (isSameDestination(southScheduleData, scheduleCount, southScheduleData[scheduleCount].destination)) {
                    printf("Destination already exists. Please enter a different destination.\n");
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
            printf("Invalid input. Enter N or S only.\n");
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
        rewind(stdin);
        scanf(" %c", &option);
        printf("\n");

        if (toupper(option) == 'N')
        {

            printf("Enter destination you want edit\n");
            printf("Destination: ");
            rewind(stdin);
            scanf("%[^\n]", editDestination);

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
            } else
            {
                printf("Record found:\n");
                printf("Enter Info to Update: \n\n");

                do {
                        printf("Enter new destination: ");
                        scanf(" %[^\n]", temp.destination);
                        rewind(stdin);

                        if (strcmp(temp.destination, editDestination) != 0 && isSameDestination(northScheduleData, MAX_TRAIN, temp.destination)) 
                        {
                            printf("Destination name already exists. Please enter a different destination.\n");
                            printf("\n");
                        } 
                        else if (!isValidDestination(temp.destination)) 
                        {
                            printf("Invalid destination.\n");
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
                    rewind(stdin);
                    scanf("%s", temp.time[i].time);

                    if (!isValidTimeFormat(temp.time[i].time)) 
                    {
                        printf("Invalid time format.\n");
                        printf("Enter time in HH:MM format or '-', TD or TM only.\n");
                        i--;
                    }
                }

                printf("\nAnswer to update? (Y=Yes): ");
                rewind(stdin);
                scanf(" %c", &answer);

                if (toupper(answer) == 'Y')
                {
                    northScheduleData[index] = temp;
                    displayNorthSchedule(northScheduleData);
                }
                else {
                    printf("No changes made.\n");
                }
            }

        } else if (toupper(option) == 'S')
        {

            printf("Enter destination you want edit\n");
            printf("Destination: ");
            rewind(stdin);
            scanf("%[^\n]", editDestination);

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
            } else
            {
                printf("Record found. \n\n");
                printf("Enter Info to Update: \n");

                do {
                        printf("\n");
                        printf("Enter new destination: ");
                        scanf(" %[^\n]", temp.destination);
                        rewind(stdin);

                        if (strcmp(temp.destination, editDestination) != 0 && isSameDestination(southScheduleData, MAX_TRAIN, temp.destination)) 
                        {
                            printf("Destination name already exists. Please enter a different destination.\n");
                            printf("\n");
                        } 
                        else if (!isValidDestination(temp.destination)) 
                        {
                            printf("Invalid destination.\n");
                            printf("\n");
                        }
                    } while ((strcmp(temp.destination, editDestination) != 0 && isSameDestination(southScheduleData, MAX_TRAIN, temp.destination)) || !isValidDestination(temp.destination));

                printf("\n");
                printf("The time can be '-' and each time entered must contained ':' \n");
                printf("If there are any train issues: \n");
                printf("TD = train delayed\n");
                printf("TM = train maintenance\n");
                printf("Enter departure time (up to 10 times): \n");
                for (int i = 0; i < MAX_TIME; i++) 
                {
                    char time[6];
                    printf("Time %d: ", i + 1);
                    rewind(stdin);
                    scanf("%s", temp.time[i].time);

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
                }
                else {
                    printf("No changes made.\n");
                }
            }
            displaySouthSchedule(southScheduleData);
        } else
        {
            printf("Invalid choice. Enter N or S only.\n");
        }

        printf("Do you want to continue modifying the schedule? (Y/N): ");
        rewind(stdin);
        scanf(" %c", &answer);
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

        } else if (toupper(answer) == 'S') {
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
        } else {
            printf("Destination not found in the schedule.\n");
        }

        printf("Do you want to delete another schedule? (Y/N): ");
        scanf(" %c", &answer);
        rewind(stdin);

    } while (toupper(answer) != 'N');
}

int findValue(const char (*arr)[MAX_SEATROW], int size, const char* value) {
    for (int i = 0; i < size; i++) 
    {
        if (strcmp(arr[i], value) == 0) 
        {
            return 1;
        }
    }
    return 0;
}

int validateTrainID(const char *trainID) {

    if (strlen(trainID) != 6 || strncmp(trainID, "TN10", 4) != 0 && strncmp(trainID, "TS10", 4) != 0)
        return 0;

    for (int i = 4; i < 6; i++) 
	{
        if (!isdigit(trainID[i]))
            return 0;
    }
    return 1;
}

void checkSeatAvailability_n () {

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
                    char (*seats_in_train)[MAX_SEATROW] = seat_n[index-1];
                    char search_seat[MAX_SEATROW];
                    sprintf(search_seat, "%d-%d", i, j);
                    if (findValue(seats_in_train, MAX_SEATCOL, search_seat) == 0) 
                    {
                        printf("0  "); // seat available
                        availableSeats++;
                    } else {
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

void checkSeatAvailability_s () {
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
                    char (*seats_in_train)[MAX_SEATROW] = seat_s[index-1];
                    char search_seat[MAX_SEATROW];
                    sprintf(search_seat, "%d-%d", i, j);
                    if (findValue(seats_in_train, MAX_SEATCOL, search_seat) == 0) 
                    {
                        printf("0  "); // seat available
                        availableSeats++;
                    } else {
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
