/* DIGITAL SIGNATURE(S):
   ====================

   List the student author(s) of this code below:

   Fullname                    Seneca Email Address
   --------------------------- ----------------------------
   1) Anmol Garg			   agarg15@myseneca.ca
   2) Anmol Deep Kaur		   adk1@myseneca.ca
   3) Harmanjit Kaur Badwal    hkbadwal1@myseneca.ca

   +--------------------------------------------------------+
   |                FILE: file_helper.h                     |
   +--------------------------------------------------------+
   |           2  0  2  0  ~  S  U  M  M  E  R              |
   |                 I  P  C  :  B  T  P                    |
   |                 1  4  4  :  1  0  0                    |
   |              FINAL ASSESSMENT PART - 2                 |
   |                                                        |
   |     S  E  N  E  C  A            C  O  L  L  E  G  E    |
   +--------------------------------------------------------+ */

#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#define NAME_LEN 50

#define MAX_PARTICIPANTS 2000

#include <stdio.h>

/********************************************************/
/* Define the missing members for the SkierInfo data    */
/* used to store Skier information read from a file     */
/********************************************************/
struct SkierInfo
{
	// TODO:  Fill in the missing members:
	char name[NAME_LEN + 1];
	int age;
	char raceLength;
	double startTime;
	double midwayTime;
	double finishTime;
	int withdrawn;
};

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!        DO NOT ALTER THE CONTENTS BELOW       !!!*/
/*!!!             ( function prototype )           !!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

/********************************************************/
/* Read all the information on one skier from the       */
/* file and store it in the struct. Return true         */
/* when end of file has been reached.                   */
/********************************************************/
int readFileRecord(FILE* fp, struct SkierInfo* info);

//Reads the time
double readTime(FILE* fp);

// Get data from the file and put in struct
int getAlldata(struct SkierInfo skiers[], int size);

// Clear the standard input buffer
void clearKeyboard(void);

// pause:
// Put function prototype below:
void pause(void);

// Get a category b/w S,M,L
char getCategory(void);

// getInt:
// Put function prototype below:
int getInt(void);

// getIntInRange:
// Put function prototype below:
int getIntInRange(int min, int max);

// yes:
// Put function prototype below:
int yes(void);

// menu:
// Put function prototype below:
int menu(void);

// raceManagerSystem:
void raceManagerSystem(void);

// Receives a empty array and a specific category, then creates the array for that category
int createArrayOfCategory(char category, struct SkierInfo skiers[], struct SkierInfo category_skiers[], int size);

// Sorts the array in ascending order
void sortSkiers(struct SkierInfo category_skiers[], int size);

// Sorts the array in ascending order
void sort_descending_Skiers(struct SkierInfo category_skiers[], int size);

// Display a skier
void displaySkier(const struct SkierInfo* skier);

// Display a skier with the withdrawn field
void displaySkierWithWithdraw(const struct SkierInfo* skier);

// Display top 3 skiers
void printTopThreeSkiers(struct SkierInfo skiers[], int size);

// Display All in a category
void print_All_In_Category(struct SkierInfo skiers[], int size);

// Display last three skiers in a category
void printLastThreeSkiers(struct SkierInfo skiers[], int size);

// Print all the winners in a category
void print_Winners_In_category(struct SkierInfo skiers[], int size);

#endif
