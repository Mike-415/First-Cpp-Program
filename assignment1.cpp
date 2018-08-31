
/*
 Description:

 	The main objective of this program is to see if the user's birthday is 
 	'magical' by determining if the birth year is a product of 
 	the birth day times the birth month.

    The program first starts with the user entering their birthday in the 
    following format: mm/dd/yy .  

	If the input is not valid, the program accumulates the warnings 
	of the user input and displays them onto the screen. The user has to
	repeat the process until they have inserted their birthday correctly.

    If the input is valid, the program determines if the birth year is 
    the product of the birth day times the birth month 
    and displays the results. 

*/
#include<iostream>
using namespace std;
  
enum MaxTimeValue{ DAYS = 31, MONTHS = 12, YEARS = 99 };
enum TimeUnit{ DAY, MONTH, YEAR };

const string INVALID_TIME_VALUE_WARNINGS[] = {
	"\t-You must enter a day between 1 and 31\n",                       /* DAY   */
	"\t-You must enter a month between 1(January) and 12(December)\n",  /* MONTH */
	"\t-You must enter a two-digit year, between 1 and 99\n"            /* YEAR  */
};
const char FORWARD_SLASH = '/';
const string EMPTY_STRING = "";
const string INVALID_CHAR_SEQUENCE_ERROR = "Invalid sequence of characters";
const string INVALID_DELIMITER_WARNING = "\t-You must use the forward slash ('/') inbetween each group of numbers\n";
const string IS_PRODUCT_MESSAGE = "\nYour birthday is magical!\n";
const string NOT_PRODUCT_MESSAGE = "\nYour birthday is not magical\n";

void checkForNullPointers(int month, char delimiter1, int day, char delimiter2, int year);
bool validateInput(int month, char char1, int day, char char2, int year);
bool validateTimeValue(TimeUnit unitOfTime, int units);
bool areForwardSlashes(char ch1, char ch2);
string calculateBirthday(int month, int day, int year);


/* This function determines if any variable contains a null value to 
 * prevent the occurence of an infinite loop within main.  
 * If any value is null this function throws an exception and terminates.
 * 
 * @param month    the birth month
 * @param char1    the first delimiting character
 * @param day      the the birth day
 * @param char2    the second delimiting character
 * @param year     the birth year
 */
void checkForNullPointers(int month, char delimiter1, int day, char delimiter2, int year) {
	if(month == NULL || delimiter1 == NULL || day == NULL || delimiter2 == NULL || year == NULL )
		throw invalid_argument(INVALID_CHAR_SEQUENCE_ERROR);
}


/* This function validates the user's input
 * 
 * @param month    the birth month
 * @param char1    the first delimiting character
 * @param day      the the birth day
 * @param char2    the second delimiting character
 * @param year     the birth year
 * @return true if the format and values of the user's input are valid
 */
bool validateInput( int month, char delimiter1, int day, char delimiter2, int year ) {
	string invalidResults = "Warning:\n";
	int initialInvalidResultsLength = invalidResults.length();

	invalidResults += ( validateTimeValue(DAY, day) )     ? EMPTY_STRING : INVALID_TIME_VALUE_WARNINGS[TimeUnit::DAY];
	invalidResults += ( validateTimeValue(MONTH, month) ) ? EMPTY_STRING : INVALID_TIME_VALUE_WARNINGS[TimeUnit::MONTH];
	invalidResults += ( validateTimeValue(YEAR, year) )   ? EMPTY_STRING : INVALID_TIME_VALUE_WARNINGS[TimeUnit::YEAR];
	invalidResults += ( areForwardSlashes(delimiter1, delimiter2) )? EMPTY_STRING : INVALID_DELIMITER_WARNING; 

	bool validInput = (invalidResults.length() == initialInvalidResultsLength);
	cout << ( (validInput) ? calculateBirthday(month, day, year) : invalidResults ) << endl;
	return validInput;
}


/* This function determines if the values of a particular unit of time are valid
 * @param  unitOfTime   the type of time unit
 * @param  timeValue    the number of time units
 * @return true if the number of units is 
 *         between 1 and the maximum number of time units 
 */
bool validateTimeValue(TimeUnit unitOfTime, int timeValue) {
	int maxTimeValue;
	switch(unitOfTime){
		case DAY:
			maxTimeValue = MaxTimeValue::DAYS;
			break;
		case MONTH:
			maxTimeValue = MaxTimeValue::MONTHS;
			break;
		case YEAR:
			maxTimeValue = MaxTimeValue::YEARS;
			break;
	}
	return timeValue <= maxTimeValue && timeValue > 0;
}


/* This function checks the delimiting characters 
 * inbetween the numeric values
 *
 * @param ch1   the first delimiting value
 * @param ch2   the second delimiting value
 * @return true if both characters are forward slashes
 */
bool areForwardSlashes(char ch1, char ch2) {
	return ch1 == FORWARD_SLASH && ch2 == FORWARD_SLASH ;
} 


 /* This function determines if the birth year 
 * is a product of the birth month and birth day
 *
 * @param month   the birth month
 * @param day     the birth day
 * @param year    the birth year
 * @return a string of the results
 */
string calculateBirthday( int month, int day, int year ) {
	return ((month * day) == year) ? IS_PRODUCT_MESSAGE : NOT_PRODUCT_MESSAGE ;
}






int main() {
    bool validInput;
	do {
		int month, day, year;
		char delimiter1, delimiter2;
		cout << "\nEnter your birthday ( mm/dd/yy ): ";
		cin >> month; cin >> delimiter1; cin >> day; cin >> delimiter2; cin >> year;
		checkForNullPointers(month, delimiter1, day, delimiter2, year);
		validInput = validateInput( month, delimiter1,  day, delimiter2,  year );
	} while ( !validInput );
}

/* OUTPUT: 

Enter your birthday ( mm/dd/yy ): 13/1/13
Warning:
	-You must enter a month between 1(January) and 12(December)


Enter your birthday ( mm/dd/yy ): 12-2-24
Warning:
	-You must use the forward slash ('/') inbetween each group of numbers


Enter your birthday ( mm/dd/yy ): 1/32/32
Warning:
	-You must enter a day between 1 and 31


Enter your birthday ( mm/dd/yy ): 10/10/100
Warning:
	-You must enter a two-digit year, between 1 and 99


Enter your birthday ( mm/dd/yy ): NO!!
libc++abi.dylib: terminating with uncaught exception of type std::invalid_argument: Invalid sequence of characters
Abort trap: 6

Mike-2:$ ./a.out

Enter your birthday ( mm/dd/yy ): 12/1/12

Your birthday is magical!

*/

