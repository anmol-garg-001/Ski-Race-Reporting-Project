/* DIGITAL SIGNATURE(S):
   ====================

   List the student author(s) of this code below:

   Fullname                    Seneca Email Address
   --------------------------- ----------------------------
   1) Anmol Garg			   agarg15@myseneca.ca
   2) Anmol Deep Kaur		   adk1@myseneca.ca
   3) Harmanjit Kaur Badwal    hkbadwal1@myseneca.ca

   +--------------------------------------------------------+
   |                FILE: file_helper.c                     |
   +--------------------------------------------------------+
   |           2  0  2  0  ~  S  U  M  M  E  R              |
   |                 I  P  C  :  B  T  P                    |
   |                 1  4  4  :  1  0  0                    |
   |              FINAL ASSESSMENT PART - 2                 |
   |                                                        |
   |     S  E  N  E  C  A            C  O  L  L  E  G  E    |
   |                                                        |
   |  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  |
   |  !!!      DO NOT ALTER THE CONTENTS BELOW         !!!  |
   |  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  |
   +--------------------------------------------------------+ */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <cstdlib>
#include <string.h>
#include "file_helper.h"

   /********************************************************/
   /* Read from the opened file the time (HH:MM) parts of  */
   /* the record and return the time as decimal hours      */
   /********************************************************/
double readTime(FILE* fp)
{
	int hour, min;

	fscanf(fp, "%d%*c", &hour);
	fscanf(fp, "%d", &min);

	return hour + (min / 60.0);
}

/********************************************************/
/* Read all the information on one skier from the valid */
/* (pre-opened) file and store it in the struct.        */
/* Return true when end of file has been reached.       */
/********************************************************/
int readFileRecord(FILE* fp, struct SkierInfo* info)
{
	int result = 1, ch;

	if (!feof(fp))
	{
		result = 0;

		// read from file and assign to data structure
		fscanf(fp, "%[^,]%*c", info->name);
		fscanf(fp, "%d", &info->age);
		fscanf(fp, " %c", &info->raceLength);
		info->startTime = readTime(fp);
		info->midwayTime = readTime(fp);
		info->finishTime = readTime(fp);

		// Last Field (withdrawn: may not be present)
		ch = fgetc(fp);
		info->withdrawn = 0;

		if (ch == ' ')
		{
			ch = fgetc(fp);
			info->withdrawn = ch == 'W';
			ch = fgetc(fp);
		}

		// clear input file buffer until end of line (record):
		while (!feof(fp) && ch != '\n')
		{
			ch = fgetc(fp);
		}
	}

	return result;
}

int getAlldata(struct SkierInfo skiers[], int size)
{
	int i, isSuccess = 0, isEof = 0;
	const char filename[] = "data.txt";

	FILE* fp = fopen(filename, "r");

	if (fp != NULL)
	{
		isSuccess = 1;

		for (i = 0; i < size && !isEof; i++)
		{
			isEof = readFileRecord(fp, &skiers[i]);
		}

		fclose(fp);
		fp = NULL;
	}
	else
	{
		isSuccess = 0;
	}

	return isSuccess;
}

// Clear the standard input buffer
void clearKeyboard(void)
{
	while (getchar() != '\n'); // empty execution code block on purpose
}

// pause: Function definition goes here:
void pause(void)
{
	printf("\n(Press Enter to Continue)");
	clearKeyboard();
}

char getCategory(void)
{
	char category, newLine = 'x';
	int flag = 1;

	do
	{
		printf("Which category (S, M, L): ");
		scanf("%c%c", &category, &newLine);

		if (newLine != '\n')
		{
			flag = 1;
			clearKeyboard();
		}

		else
		{
			switch (category)
			{
			case 's':case 'S':
			case 'm':case 'M':
			case 'l':case 'L':
				flag = 0;
				break;

			default:
				flag = 1;
				break;
			}
		}

	} while (flag); // Do-while loop will not end until the user selects a valid category
	//category.toUpper();

	if (category == 's' || category == 'S')
	{
		category = 'S';
	}
	else if (category == 'm' || category == 'M')
	{
		category = 'M';
	}
	else if (category == 'l' || category == 'L')
	{
		category = 'L';
	}

	return category;
}

// getInt: Function definition goes here:
int getInt(void)
{
	int inputValue;
	char newLine = 'x';

	// The do-while loop will not let the user exit the loop until a valid input is entered
	do
	{
		scanf("%d%c", &inputValue, &newLine);

		if (newLine != '\n')
		{
			clearKeyboard();
			printf("*** INVALID INTEGER *** <Please enter an integer>: ");
		}
	} while (newLine != '\n');

	return inputValue;
}

// getIntInRange: Function definition goes here:
int getIntInRange(int min, int max)
{
	int inputValue;

	// The do-while loop will not let the user exit the loop until a valid input is entered b/w min & max
	do
	{
		inputValue = getInt();// It will return a valid integer value

		if (inputValue < min || inputValue > max)
		{
			printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
		}

	} while (inputValue < min || inputValue > max);

	return inputValue;
}

// yes: Function definition goes here:
int yes(void)
{
	int isYes;
	char inputValue, newLine = 'x';

	// The do-while loop will not let the user exit the loop until a valid input is entered
	do
	{
		scanf("%c%c", &inputValue, &newLine);

		if (newLine != '\n' || (inputValue != 'Y' && inputValue != 'y' && inputValue != 'N' && inputValue != 'n'))
		{
			if (newLine != '\n')
				clearKeyboard();
			printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
		}

	} while (newLine != '\n' || (inputValue != 'Y' && inputValue != 'y' && inputValue != 'N' && inputValue != 'n'));

	if (inputValue == 'Y' || inputValue == 'y')
		isYes = 1;
	else
		isYes = 0;

	return isYes;
}

// menu: Function definition goes here:
int menu(void)
{
	printf("************** X-Country Ski Race Reporting **************\n");
	printf("----------------------------------------------------------\n");
	printf("1. Print top 3 skiers in a category\n");
	printf("2. Print all skiers in a category\n");
	printf("3. Print last 3 skiers in a category\n");
	printf("4. Print winners in all categories\n");
	printf("0. Exit\n");
	printf("\n");
	printf("Select an option:> ");

	return getIntInRange(0, 4);// It will return a valid integer value b/w 0 and 4
}

void raceManagerSystem(void)
{
	int choice, exit = 0;

	struct SkierInfo skiers[MAX_PARTICIPANTS] = { { { '\0' } } };

	int isSuccess = getAlldata(skiers, MAX_PARTICIPANTS);

	if (!isSuccess)
	{
		printf("ERROR: Cannot find the file\n");
	}
	else
	{
		do
		{
			choice = menu();// It will return the valid choice entered by the user

			switch (choice)
			{
			case 1:  //<---Print top 3 skiers in a category
				printf("\n");
				printTopThreeSkiers(skiers, MAX_PARTICIPANTS);
				pause();
				printf("\n");
				break;

			case 2:  //<---Print all skiers in a category
				printf("\n");
				print_All_In_Category(skiers, MAX_PARTICIPANTS);
				pause();
				printf("\n");
				break;

			case 3:  //<---Print last 3 skiers in a category
				printf("\n");
				printLastThreeSkiers(skiers, MAX_PARTICIPANTS);
				pause();
				printf("\n");
				break;

			case 4: //<---Print winners in all categories
				printf("\n");
				print_Winners_In_category(skiers, MAX_PARTICIPANTS);
				pause();
				printf("\n");
				break;

			case 0:  //<--Exit the application
				printf("\nExit the program? (Y)es/(N)o: ");

				if (yes())
				{
					exit = 1;
					printf("\nSystem: terminated, Keep on Skiing!");
				}

				printf("\n");
				break;

			default:
				break;
			}
		} while (!exit);
	}
}

int createArrayOfCategory(char category, struct SkierInfo skiers[], struct SkierInfo category_skiers[], int size)
{
	int i, size_of_array = 0;

	for (i = 0; i < size; i++)
	{
		if (skiers[i].raceLength == category && skiers[i].name[0] != '\0')
		{
			category_skiers[size_of_array++] = skiers[i];
		}
	}

	return size_of_array;
}

void sortSkiers(struct SkierInfo category_skiers[], int size)
{
	int i, j, swapIndex;
	struct SkierInfo tempSkier = { { { '\0' } } };

	for (i = 0; i < size - 1; i++) // Used i < size - 1 because it will end the loop after comparing the 2nd last skier with the last skier
	{
		swapIndex = i;
		for (j = i + 1; j < size; j++)
		{
			if ((category_skiers[j].finishTime - category_skiers[j].startTime) < (category_skiers[swapIndex].finishTime - category_skiers[swapIndex].startTime))
			{
				swapIndex = j;
			}
		}
		if (swapIndex != i)
		{
			//swapping the skiers
			tempSkier = category_skiers[i];
			category_skiers[i] = category_skiers[swapIndex];
			category_skiers[swapIndex] = tempSkier;
		}
	}
}

void sort_descending_Skiers(struct SkierInfo category_skiers[], int size)
{
	int i, j, swapIndex;
	struct SkierInfo tempSkier = { { { '\0' } } };

	for (i = 0; i < size - 1; i++) // Used i < size - 1 because it will end the loop after comparing the 2nd last skier with the last skier
	{
		swapIndex = i;
		for (j = i + 1; j < size; j++)
		{
			if ((category_skiers[j].finishTime - category_skiers[j].startTime) > (category_skiers[swapIndex].finishTime - category_skiers[swapIndex].startTime))
			{
				swapIndex = j;
			}
		}
		if (swapIndex != i)
		{
			//swapping the skiers
			tempSkier = category_skiers[i];
			category_skiers[i] = category_skiers[swapIndex];
			category_skiers[swapIndex] = tempSkier;
		}
	}
}

void displaySkier(const struct SkierInfo* skier)
{
	char time[6] = { '\0' };
	int hours = 0, mins = 0;
	char ageGroup[20] = { '\0' };

	if (skier->age >= 16 && skier->age <= 20)
	{
		strcpy(ageGroup, "Junior");
	}
	else if (skier->age > 20 && skier->age <= 34)
	{
		strcpy(ageGroup, "Adult");
	}
	else if (skier->age > 34)
	{
		strcpy(ageGroup, "Senior");
	}

	hours = (int)(skier->finishTime - skier->startTime);
	mins = (int)(skier->finishTime - skier->startTime - hours) * 60 + 0.5;
	sprintf(time, "%2d:%02d", hours, mins);

	printf("%-25s%-11s%5s", skier->name, ageGroup, time);
}

void displaySkierWithWithdraw(const struct SkierInfo* skier)
{
	char isWithdrawn[4] = { '\0' };
	char time[6] = { '\0' };
	int hours = 0, mins = 0;
	char ageGroup[10] = { '\0' };

	if (skier->age >= 16 && skier->age <= 20)
	{
		strcpy(ageGroup, "Junior");
	}
	else if (skier->age > 20 && skier->age <= 34)
	{
		strcpy(ageGroup, "Adult");
	}
	else if (skier->age > 34)
	{
		strcpy(ageGroup, "Senior");
	}

	if (skier->withdrawn == 1)
	{
		strcpy(isWithdrawn, "Yes");
		strcpy(time, "N/A");
	}
	else
	{
		hours = (int)(skier->finishTime - skier->startTime);
		mins = (int)(skier->finishTime - skier->startTime - hours) * 60 + 0.5;
		sprintf(time, "%2d:%02d", hours, mins);
		strcpy(isWithdrawn, "No");
	}

	printf("%-25s%-11s%5s%11s", skier->name, ageGroup, time, isWithdrawn);
}

void printTopThreeSkiers(struct SkierInfo skiers[], int size)
{
	int i, no_of_printed_records = 0;
	char category = getCategory();

	struct SkierInfo category_skiers[MAX_PARTICIPANTS] = { { { '\0' } } };

	int size_of_array = createArrayOfCategory(category, skiers, category_skiers, size);

	if (size_of_array == 0)
	{
		printf("\nNo skiers in this category\n");
	}
	else
	{
		sortSkiers(category_skiers, size_of_array);

		printf("\nSkier                    Age Group   Time\n");
		printf("-----------------------------------------\n");
		for (i = 0; i < size_of_array && no_of_printed_records < 3; i++)
		{
			if (category_skiers[i].withdrawn != 1)
			{
				displaySkier(&category_skiers[i]);
				printf("\n");
				no_of_printed_records++;
			}
		}
	}
}

void print_All_In_Category(struct SkierInfo skiers[], int size)
{
	int i;
	char category = getCategory();

	struct SkierInfo category_skiers[MAX_PARTICIPANTS] = { { { '\0' } } };

	int size_of_array = createArrayOfCategory(category, skiers, category_skiers, size);

	sortSkiers(category_skiers, size_of_array);

	printf("\nSkier                    Age Group   Time  Withdrawn\n");
	printf("----------------------------------------------------\n");
	for (i = 0; i < size_of_array; i++)
	{
		displaySkierWithWithdraw(&category_skiers[i]);
		printf("\n");
	}
}

void printLastThreeSkiers(struct SkierInfo skiers[], int size)
{
	int i, no_of_printed_records = 0;
	char category = getCategory();

	struct SkierInfo category_skiers[MAX_PARTICIPANTS] = { { { '\0' } } };

	int size_of_array = createArrayOfCategory(category, skiers, category_skiers, size);

	if (size_of_array == 0)
	{
		printf("\nNo skiers in this category\n");
	}
	else
	{
		sort_descending_Skiers(category_skiers, size_of_array);

		printf("\nSkier                    Age Group   Time\n");
		printf("-----------------------------------------\n");
		for (i = 0; i < size_of_array && no_of_printed_records < 3; i++)
		{
			if (category_skiers[i].withdrawn != 1)
			{
				displaySkier(&category_skiers[i]);
				printf("\n");
				no_of_printed_records++;
			}
		}
	}
}

void print_Winners_In_category(struct SkierInfo skiers[], int size)
{
	int i, flag = 1;

	struct SkierInfo s_skiers[MAX_PARTICIPANTS] = { { { '\0' } } };
	struct SkierInfo m_skiers[MAX_PARTICIPANTS] = { { { '\0' } } };
	struct SkierInfo l_skiers[MAX_PARTICIPANTS] = { { { '\0' } } };

	int s_skiers_size = createArrayOfCategory('S', skiers, s_skiers, size);
	int m_skiers_size = createArrayOfCategory('M', skiers, m_skiers, size);
	int l_skiers_size = createArrayOfCategory('L', skiers, l_skiers, size);

	sortSkiers(s_skiers, s_skiers_size);
	sortSkiers(m_skiers, m_skiers_size);
	sortSkiers(l_skiers, l_skiers_size);

	printf("Skier                    Age Group   Time  Category\n");
	printf("---------------------------------------------------\n");

	flag = 1;
	for (i = 0; i < s_skiers_size && flag; i++)
	{
		if (s_skiers[i].withdrawn != 1)
		{
			displaySkier(&s_skiers[i]);
			printf("     10 km\n");
			flag = 0;
		}
	}
	if (flag == 1)
	{
		printf("Not awarded                                10 km\n");
	}

	flag = 1;
	for (i = 0; i < m_skiers_size && flag; i++)
	{
		if (m_skiers[i].withdrawn != 1)
		{
			displaySkier(&m_skiers[i]);
			printf("     25 km\n");
			flag = 0;
		}
	}
	if (flag == 1)
	{
		printf("Not awarded                                25 km\n");
	}

	flag = 1;
	for (i = 0; i < l_skiers_size && flag; i++)
	{
		if (l_skiers[i].withdrawn != 1)
		{
			displaySkier(&l_skiers[i]);
			printf("     50 km\n");
			flag = 0;
		}
	}
	if (flag == 1)
	{
		printf("Not awarded                                50 km\n");
	}
}
