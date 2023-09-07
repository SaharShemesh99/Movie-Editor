/********************************************************************\
* It is an editing Project!											 *
* Our program shows to the user the following menu:					 *
* [0] Exit														 	 *
* [1] Add new item													 *
* [2] Remove a item												 *
* [3] change item index											 *
* [4] Change item duration											 *
* [5] Change duration of all items									 *
* [6] List items													 *
* [7] Play movie													 *
* [8] Save my movie												   	 *
* [9] Open saved movie												 *
* [10] Print the names of all my movies								 *
* [11] Show all the saved movies									 *
* [12] Delete all the items										 *
* [13] Change the color of the background and the foreground		 *
* The user decides and the program operates according to his choice. *
\********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <opencv2\highgui\highgui_c.h>

struct item
{
	char *name;
	unsigned int duration;
	char *path;
}typedef item_t;

struct Link
{
	item_t	*item;
	struct Link	*next;
}typedef link_t;

#define MAX_PATH_SIZE 256 //Setting variables
#define MAX_NAME_SIZE 50 //Setting variables
#define MAX_DUR_SIZE 10 //Setting variables
#define ZERO 0 //Setting variables
#define ONE 1 //Setting variables

void menu(void); //Definition of functions
void startFun(void); //Definition of functions
void endFun(void); //Definition of functions
link_t* inputForLink(link_t* first); //Definition of functions
int checkOfName(link_t* first, char nameForitem[]); //Definition of functions
link_t* deleteSquad(link_t* curr, char name[]); //Definition of functions
link_t* changePosition(link_t* first, char name[], int position);
void changeitemDuration(link_t* link); //Definition of functions
void changeAllTheDurations(link_t* first); //Definition of functions
void printitems(link_t* link); //Definition of functions
void freeFun(link_t* link); //Definition of functions
void play(link_t *list); //Definition of functions
int saveFun(link_t* first); //Definition of functions
link_t* OpenSavedMovie(void); //Definition of functions
link_t* addToEnd(link_t* first, link_t* lastitem); //Definition of functions
void namesOfTheMovies(void); //Definition of functions
int showAllTheSavedMovies(void); //Definition of functions
void colorFun(void); //Definition of functions
int checkInputOfColor(char choiseOfUser); //Definition of functions

int main(void)
{
	menu(); //Function call

	return 0;
}

/*
The purpose of the function is to print the menu.
The function gets nothing, and returns nothing.
*/
void menu(void)
{
	int ans = 1, saveOrNot = 0, position = 0, wholeOrNot = 0, count = 0, whereToStart = 0, flag = 0, answer = 0; //Setting variables
	link_t* first = NULL; //Setting variables
	link_t* temp = NULL; //Setting variables
	char nameForitem[MAX_NAME_SIZE] = { 0 }; //Setting variables

	startFun();
	system("start /MIN options.m4a"); //This command causes for playing music file

	while (ans) //While the user didn't press 0.
	{	
		printf("Editing Project! what would you like to do?\n"); //Output
		printf("[0] Exit\n"); //Output
		printf("[1] Add new item\n"); //Output
		printf("[2] Remove a item\n"); //Output
		printf("[3] change item index\n"); //Output
		printf("[4] Change item duration\n"); //Output
		printf("[5] Change duration of all items\n"); //Output
		printf("[6] List items\n"); //Output
		printf("[7] Play movie\n"); //Output
		printf("[8] Save my movie\n"); //Output
		printf("[9] Open saved movie\n"); //Output
		printf("[10] Print the names of all my movies\n"); //Output
		printf("[11] Show all the saved movies\n"); //Output
		printf("[12] Delete all the items\n"); //Output
		printf("[13] Change the color of the background and the foreground\n"); //Output
		scanf("%d", &ans); //Input
		getchar(); //Remove '\n'
		switch (ans)
		{
		case 0:
			//exit
			if (first) //Checking if the list isn't empty
			{
				do
				{
					printf("Do you want to save your work before you finish the program? (1 = Yes, 0 = No)\n"); //Output
					scanf("%d", &saveOrNot); //Input
					getchar(); //Remove '\n'
				} while (saveOrNot != 0 && saveOrNot != 1); //Checking the input
				if (saveOrNot)
				{
					if (saveFun(first)) //Function call
					{
						printf("There was an error in the function.\n"); //Output
					}
				}
			}
			endFun(); //Function call
			freeFun(first); //Function call
			break;
		case 1:
			//Add new item
			first = addToEnd(first, inputForLink(first)); //Function call
			break;
		case 2:
			//Remove a item
			if (first) //Checking if the list isn't empty
			{
				printf("Enter the name of the item:"); //Output
				fgets(nameForitem, MAX_NAME_SIZE, stdin); //Input
				nameForitem[strcspn(nameForitem, "\n")] = ZERO; //Remove '\n'
				answer = checkOfName(first, nameForitem);
				if (answer == 1)
				{
					first = deleteSquad(first, nameForitem); //Function call
				}
				else
				{
					printf("The item was not found\n");
				}
			}
			else
			{
				printf("The list is empty, there is no point in removing a item.\n"); //Output
			}
			break;
		case 3:
			//change items index
			if (first) //Checking if the list isn't empty
			{
				printf("Enter the name of the item: "); //Output
				fgets(nameForitem, MAX_NAME_SIZE, stdin); //Input
				nameForitem[strcspn(nameForitem, "\n")] = ZERO; //Remove '\n'
				answer = checkOfName(first, nameForitem);
				if (answer == 1)
				{
					printf("Enter the new index in the movie you wish to place the item: "); //Output
					scanf("%d", &position); //Input
					getchar(); //Remove '\n'
					first = changePosition(first, nameForitem, position); //Function call
				}
				else
				{
					printf("This item does not exist\n");
				}
			}
			else
			{
				printf("The list is empty, you can't change items index.\n"); //Output
			}
			break;
		case 4:
			//Change item duration
			if (first) //Checking if the list isn't empty
			{
				changeitemDuration(first); //Function call
			}
			else
			{
				printf("The list is empty, you can't change a duration.\n"); //Output
			}
			break;
		case 5:
			//Change duration of all items
			if (first) //Checking if the list isn't empty
			{
				changeAllTheDurations(first); //Function call
			}
			else
			{
				printf("The list is empty, you can't change the durations.\n"); //Output
			}
			break;
		case 6:
			//List items
			if (first) //Checking if the list isn't empty
			{
				printitems(first); //Function call
			}
			else
			{
				printf("The list is empty, there is no point in printing it.\n"); //Output
			}
			break;
		case 7:
			//Play movie
			if (first)
			{
				do
				{
					printf("If you wish to play the whole movie press 1\n"); //Output
					printf("If you want to play the movie from a certain point press 2\n"); //Output
					scanf("%d", &wholeOrNot); //Input
					getchar(); //Remove '\n'
				} while (wholeOrNot != 1 && wholeOrNot != 2); //Checking the input
				if (wholeOrNot == 1)
				{
					play(first); //Function call
					system("start /MIN Great_video.m4a"); //This command causes for playing music file
				}
				else
				{
					printf("Where do you wish to start playing the movie from? (number of item)\n"); //Output
					scanf("%d", &whereToStart); //Input
					getchar(); //Remove '\n'
					temp = first;
					count = ZERO; //Reset the counter
					flag = ZERO; //Reset the flag
					while (temp) //While it isn't the end of the list
					{
						count++;
						if (whereToStart == count)
						{
							play(temp); //Function call
							system("start /MIN Great_video.m4a"); //This command causes for playing music file
							flag = ONE; //it is a flag to show that the video was played
							break;
						}
						temp = temp->next;
					}
					if (!flag) //Checking if the video was played
					{
						printf("The movie has only %d items!\n", count); //Output
					}
				}
			}
			break;
		case 8:
			//Save my movie
			if (first) //Checking if the list is empty
			{
				if (saveFun(first)) //Function call
				{
					printf("There was an error in the function.\n"); //Output
				}
			}
			else
			{
				printf("The list is empty, there is no point in saving it.\n"); //Output
			}
			break;
		case 9:
			//Open saved movie
			if (first) //Checking if the list isn't empty
			{
				do
				{
					printf("Do you want to save your work before you open an old one? (1 = Yes, 0 = No)\n"); //Output
					scanf("%d", &saveOrNot); //Input
					getchar(); //Remove '\n'
				} while (saveOrNot != 0 && saveOrNot != 1); //Checking the input
				if (saveOrNot)
				{
					if (saveFun(first)) //Function call
					{
						printf("There was an error in the function.\n"); //Output
					}
				}
				else
				{
					freeFun(first); //Function call
					first = NULL; //Reset the pointer to the first item
				}
			}
			first = OpenSavedMovie(); //Function call
			break;
		case 10:
			//Print the names of all my movies
			namesOfTheMovies(); //Function call
			break;
		case 11:
			//Show all the saved movies
			if (showAllTheSavedMovies()) //Function call
			{
				printf("There was an error in the function.\n"); //Output
			}
			break;
		case 12:
			//Delete all the items
			if (first) //Checking if the list isn't empty
			{
				freeFun(first); //Function call
			}
			else
			{
				printf("The list is empty, there is no point in deleting it.\n"); //Output
			}
			first = NULL;
			break;
		case 13:
			//Change the color of the background and the foreground.
			colorFun();
			break;
		default:
			printf("You should type one of the options - 0-13!\n\n"); //Output
			break;
		}

		printf("\n--------------------------------------------------------------------------------\n\n"); //Output
	}
}

/*
The purpose of the function is to play the words of the beginning of the program and creating the photo of
"Welcome" and show it. The function returns nothing.
*/
void startFun(void)
{
	link_t* startLink = NULL; //Setting variables
	item_t* startitem = NULL; //Setting variables

	system("start /MIN For_the_beginning.m4a"); //This command causes for playing music file

	startitem = (item_t*)malloc(sizeof(item_t)); //Dynamic memory allocation
	if (!startitem) //Checking if the dynamic memory allocation succeeded
	{
		printf("Dynamic memory allocation failed\n"); //Output
	}
	startLink = (link_t*)malloc(sizeof(link_t)); //Dynamic memory allocation
	if (!startLink) //Checking if the dynamic memory allocation succeeded
	{
		printf("Dynamic memory allocation failed\n"); //Output
	}

	startLink->item = startitem;
	startLink->item->duration = 2000;
	startLink->item->name = "start";
	startLink->item->path = "Welcome.jpg";
	startLink->next = NULL;
	play(startLink); //Function call
	free(startitem);
	free(startLink);
}

/*
The purpose of the function is to play the words of the ending of the program and creating the photo of 
"Time to say goodbye" and show it. The function returns nothing.
*/
void endFun(void)
{
	link_t* startLink = NULL; //Setting variables
	item_t* startitem = NULL; //Setting variables

	system("start /MIN For_the_end.m4a"); //This command causes for playing music file

	startitem = (item_t*)malloc(sizeof(item_t)); //Dynamic memory allocation
	if (!startitem) //Checking if the dynamic memory allocation succeeded
	{
		printf("Dynamic memory allocation failed\n"); //Output
	}
	startLink = (link_t*)malloc(sizeof(link_t)); //Dynamic memory allocation
	if (!startLink) //Checking if the dynamic memory allocation succeeded
	{
		printf("Dynamic memory allocation failed\n"); //Output
	}

	startLink->item = startitem;
	startLink->item->duration = 6000;
	startLink->item->name = "end";
	startLink->item->path = "Goodbye.jpg";
	startLink->next = NULL;
	play(startLink); //Function call
	free(startitem);
	free(startLink);
}

/*
The purpose of the function is to get an item from the user.
The function gets pointer to the first item.
The function returns pointer to the first item because the pointer to the first item might be changed.
*/
link_t* inputForLink(link_t* first)
{
	link_t* tempForLink = NULL; //Setting variables
	item_t* tempForitem = NULL; //Setting variables
	char* nameForitem = NULL; //Setting variables
	char* pathForitem = NULL; //Setting variables
	int i = 0; //Setting variables

	printf("			*** Creating new item ***			\n"); //Output

	nameForitem = (char*)calloc(MAX_NAME_SIZE, sizeof(char)); //Dynamic memory allocation
	if (!nameForitem) //Checking if the dynamic memory allocation succeeded
	{
		printf("Dynamic memory allocation failed\n"); //Output
		return NULL;
	}

	pathForitem = (char*)calloc(MAX_PATH_SIZE, sizeof(char)); //Dynamic memory allocation
	if (!pathForitem) //Checking if the dynamic memory allocation succeeded
	{
		printf("Dynamic memory allocation failed\n"); //Output
		return NULL;
	}

	tempForitem = (item_t*)malloc(sizeof(item_t)); //Dynamic memory allocation
	if (!tempForitem) //Checking if the dynamic memory allocation succeeded
	{
		printf("Dynamic memory allocation failed\n"); //Output
		return NULL;
	}
	tempForLink = (link_t*)malloc(sizeof(link_t)); //Dynamic memory allocation
	if (!tempForLink) //Checking if the dynamic memory allocation succeeded
	{
		printf("Dynamic memory allocation failed\n"); //Output
		return NULL;
	}

	printf("Please insert item path: "); //Output
	fgets(pathForitem, MAX_PATH_SIZE, stdin); //Input
	pathForitem[strlen(pathForitem) - ONE] = ZERO; //Remove '\n'
	printf("Please insert item duration(in miliseconds) :"); //Output
	scanf("%d", &(tempForitem->duration)); //Input
	getchar(); //Remove '\n'
	printf("Please choose a name for that item :"); //Output
	fgets(nameForitem, MAX_NAME_SIZE, stdin); //Input
	nameForitem[strlen(nameForitem) - ONE] = ZERO; //Remove '\n'
	while (checkOfName(first, nameForitem)) //Function call
	{
		printf("That name already exists , please choose a different name!\n"); //Output
		for (i = 0; i < strlen(nameForitem); i++)
		{
			nameForitem[i] = 0; //Reset the string
		}
		fgets(nameForitem, MAX_NAME_SIZE, stdin); //Input
		nameForitem[strlen(nameForitem) - ONE] = 0; //Remove '\n'
	}

	tempForitem->name = nameForitem;
	tempForitem->path = pathForitem;
	tempForLink->item = tempForitem;
	tempForLink->next = NULL;
	return tempForLink;
}

/*
The purpose of the function is to check if the name that it gets exist in the linke list.
The function gets pointer to the first item, and the name of the item that would be checked.
The function returns 1 if the item exists and 0 if it doesn't exists.
*/
int checkOfName(link_t* first, char nameForitem[])
{
	int ans = 0; //Setting variables
	link_t* temp = first; //Setting variables

	while (temp)
	{
		if (!strcmp(temp->item->name, nameForitem)) //Checking if this name already exist
		{
			ans = 1; //This name already exist
			break;
		}
		temp = temp->next; //Moving to the next item
	}
	return ans;
}

/*
The purpose of the function is to delete an item.
The function gets pointer to the first item, and the name of the item that should be deleted,
the function returns pointer to the first item because the pointer to the first item might be changed.
*/
link_t* deleteSquad(link_t* curr, char name[])
{
	link_t* priv = curr; //Setting variables
	//If we are at the end
	if (!curr)
	{
		return curr;
	}
	//if we found the name
	if (strcmp(curr->item->name, name) == 0)
	{
		//if the node is last
		if (!curr->next)
		{
			printf("The name has been found and the item has been deleted.\n"); //Output
			free(priv);
			return NULL;
		}
		curr = curr->next; //Moving to the next item
		printf("The name has been found and the item has been deleted.\n"); //Output
		free(priv);

		return curr;
	}
	else
	{
		curr->next = deleteSquad(curr->next, name);
	}
	return curr;
}

/*
The purpose of the function is to change position of an item.
The function gets pointer to the first item, the name of the item that should be changed and the position.
The function returns pointer to the first item because the pointer to the first item might be changed.
*/
link_t* changePosition(link_t* curr, char name[], int position)
{
	int findPosition = 0; //Setting variables
	link_t* first = curr; //Setting variables
	link_t* node = NULL; //Setting variables
	link_t* beforeNode = NULL; //Setting variables
	link_t* priv = NULL; //Setting variables
	link_t* tmp = NULL; //Setting variables
	int length = 0;

	//checking the length of the list
	while (curr)
	{
		length++;
		curr = curr->next;
	}
	if (position <= 0 || position > length)
	{
		printf("The movie contains only %d items!\n", length);
		return first;
	}

	//Finding the position of the node with the name, making her first in the list.
	//The nodes after this node aren't changing in order.
	while (curr->next)
	{
		if (curr == first && strcmp(curr->item->name, name) == 0)
		{
			break;
		}
		if (strcmp(curr->next->item->name, name) == 0)
		{
			node = curr->next;
			beforeNode = curr;
			beforeNode->next = node->next;
			node->next = first;
			first = node;
			break;
		}
		curr = curr->next;
	}

	//Starting from the first node again.
	curr = first;

	//Changing positions until we are at the right spot.
	while (findPosition != position && curr)
	{
		findPosition++;
		if (findPosition != position && curr != first)
		{
			priv->next = curr->next;
			tmp = curr->next;
			curr->next = tmp->next;
			tmp->next = curr;
			curr = tmp;
		}
		else if (curr == first && findPosition != position)
		{
			first = curr->next;
			tmp = curr->next;
			curr->next = tmp->next;
			tmp->next = curr;
			curr = tmp;
		}
		priv = curr;
		curr = curr->next;
	}

	return first; // returning head of list.
}

/*
The purpose of the function is to change a specific duration in the linked list.
The function gets pointer to the first item of the list, and returns nothing.
*/
void changeitemDuration(link_t* link)
{
	char name[MAX_NAME_SIZE] = { 0 }; //Setting variables
	int newDuration = 0; //Setting variables
	int isName = 0; //Setting variables

	printf("Write the name of the item which you want to change the duration in: "); //Output
	fgets(name, MAX_NAME_SIZE, stdin); //Input
	name[strlen(name) - ONE] = ZERO; //Remove '\n'

	while (link) //while the current item isn't NULL.
	{
		if (!strcmp(link->item->name, name)) //checking if it is the right item
		{
			printf("Write the new duration: "); //Output
			scanf("%d", &newDuration); //Input

			link->item->duration = newDuration;

			isName = 1; //The item was found
		}
		link = link->next;
	}

	if (!isName) //Checking if the item was found
	{
		printf("The item does not exist.\n"); //Output
	}

}

/*
The purpose of the function is to change all the durations in the linked list.
The function gets pointer to the first item of the list, and returns nothing.
*/
void changeAllTheDurations(link_t* first)
{
	int durationForitem = 0; //Setting variables
	link_t* temp = first; //Setting variables

	printf("Please insert item duration(in miliseconds) :"); //Output
	scanf("%d", &durationForitem); //Input

	while (temp) //while the current item isn't NULL.
	{
		temp->item->duration = durationForitem; //Changing the duration
		temp = temp->next; //Moving to the next item
	}
}

/*
The purpose of the function is to print the linked list.
The function gets pointer to the first item of the list, and returns nothing.
*/
void printitems(link_t* link)
{
	printf("\tName\t\tDuration\tPath\n"); //Output
	while (link) //while the current item isn't NULL.
	{
		printf("\t%s\t\t%d ms\t\t%s\n", link->item->name, link->item->duration, link->item->path); //Output
		link = link->next;
	}
}

/*
The purpose of the function is to free the linked list.
The function gets pointer to the first item of the list, and returns nothing.
*/
void freeFun(link_t* first)
{
	link_t* temp = first; //Setting variables

	while (first) //while the current item isn't NULL.
	{
		free(first->item);
		temp = first->next;
		free(first);
		first = temp;
	}
}

/*
play the movie!!
input: a linked list of items to display
display the images each for the duration of the item one by one and close the window.
*/
void play(link_t *list)
{
	cvNamedWindow("Display window", CV_WINDOW_AUTOSIZE); //create a window
	int counter = 1, ans = 0;
	IplImage* image;

	while (list != 0)
	{
		image = cvLoadImage(list->item->path, 1);
		if (!image)//The image is empty.
		{
			printf("could not open or find image number %d\n", counter);
			list = list->next; //I added this line because without it if the picture can't be opened this line will be printed again and again
		}
		else
		{
			cvShowImage("Display window", image);//display the image
			cvWaitKey(list->item->duration);//wait
			list = list->next;
			cvReleaseImage(&image);
		}
		counter++;
	}
	cvDestroyWindow("Display window");
	return;
}

/*
The purpose of the function is to save a video.
The function receives the name of the video from the user and check if this name already exists.
The function gets pointer to the first item of the list and returns 0 if everything worked fine, and 1 if there was a problem.
*/
int saveFun(link_t* first)
{
	char name[MAX_NAME_SIZE] = { 0 }; //Setting variables
	char nameAndPath[MAX_NAME_SIZE] = "savedVideos\\"; //Setting variables
	FILE* myFile = NULL; //Setting variables
	HANDLE myFolder; //Setting variables
	WIN32_FIND_DATA dataInFile; //Setting variables
	char strFilePath[MAX_PATH_SIZE] = { 0 }; //Setting variables
	FILE* savedFile = NULL; //Setting variables
	link_t* curr = first; //Setting variables
	int ans = 0, temp = 0, flag = 0, place = 0; //Setting variables
	char reversedDur[MAX_DUR_SIZE] = { 0 }; //Setting variables
	char tempDur = ' '; //Setting variables

	do
	{
		printf("What is the name of the video that you want to save? "); //Output
		fgets(name, MAX_PATH_SIZE, stdin); //Input
		name[strlen(name) - ONE] = ZERO; //Remove '\n'
		flag = 0; flag = 0; //If the flagis 0 it means that this name wasn't found.
		strncat(name, ".txt", strlen(".txt"));
		sprintf(strFilePath, "savedVideos\\*.*"); //Creating the name, to open the file with this name in the next command
		if ((myFolder = FindFirstFile(strFilePath, &dataInFile)) != INVALID_HANDLE_VALUE) //Opening the folder
		{
			do
			{
				if ((strcmp(dataInFile.cFileName, ".") != ZERO) && (strcmp(dataInFile.cFileName, "..") != ZERO))
				{//Every folder begins with one point and later to points,
				//so this condition check if the file is desirable or it is just points.
					if (!strcmp(dataInFile.cFileName, name)) //Checking if this file is equal to users input of the file name.
					{
						do
						{
							printf("Do you want to overwrite the file? (1 = Yes, 0 = No)\n"); //Output
							scanf("%d", &ans); //Input
							getchar(); //Remove '\n'
						} while (ans != 0 && ans != 1); //Checking the input
						if (!ans)
						{
							flag = 1; //This name exists.
						}
						break;
					}
					if (flag) //Checking if this name exists
					{
						printf("This name already exists, please choose a new one.\n"); //Output
					}
				}
			} while (FindNextFile(myFolder, &dataInFile)); //Moving to the next file
		}
	} while (flag); //Checking if this name exists
	
	if (!FindClose(myFolder)) //Closing the folder
	{
		printf("There was a prblem in closing the folder.\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	strncat(nameAndPath, name, strlen(name));//Adding to the nameAndPath (that is "savedVideos\\") the name of the film that the user wants to open.
	savedFile = fopen(nameAndPath, "w"); //Opening file

	if (!savedFile)//Checking if the opening succeeded 
	{
		//Testing if the opening of the file has been done successfully
		printf("Error opening the file\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	while (curr) //while the current item isn't NULL.
	{
		fprintf(savedFile, "%s\n", curr->item->name); //Writing in to the file
		
		fprintf(savedFile, "%d\n", curr->item->duration); //Writing in to the file
		
		fprintf(savedFile, "%s\n", curr->item->path); //Writing in to the file
		
		curr = curr->next; //moving to the next element
	}

	fprintf(savedFile, "end_of_list-Video_editing_program"); //Writing in to the file, it is a flag to the ending of the file.

	if (fclose(savedFile) == EOF) //Closing file
	{
		//Testing if the closing of the file has been done successfully
		printf("Error closing the file\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	return 0;
}

/*
The purpose of the function is to open a saved video.
The function receives the name of the video from the user and transmits it to a linked list.
The function gets nothing and returns pointer to the first item of the list.
*/
link_t* OpenSavedMovie(void)
{
	char name[MAX_NAME_SIZE] = { 0 }; //Setting variables
	int flag = 0, flagFirstTime = 1, place = 0; //Setting variables
	FILE* myFile = NULL; //Setting variables
	HANDLE myFolder; //Setting variables
	WIN32_FIND_DATA dataInFile; //Setting variables
	char strFilePath[MAX_PATH_SIZE] = { 0 }; //Setting variables
	char nameAndPath[MAX_NAME_SIZE] = "savedVideos\\"; //Setting variables
	FILE* savedFile = NULL; //Setting variables
	link_t* tempForLink = NULL; //Setting variables
	link_t* curr = NULL; //Setting variables
	link_t* first = NULL; //Setting variables
	item_t* tempForitem = NULL; //Setting variables
	char* nameForitem = NULL; //Setting variables
	char* pathForitem = NULL; //Setting variables
	char letter = 0; //Setting variables

	do
	{
		printf("What is the name of the video that you want to open? "); //Output
		fgets(name, MAX_PATH_SIZE, stdin); //Input
		name[strlen(name) - ONE] = ZERO; //Remove '\n'
		flag = 0; //If the flagis 0 it means that this name wasn't found yet.
		strncat(name, ".txt", strlen(".txt")); //adding the ending of ".txt" to the name, so the loop would be able to find it.
		sprintf(strFilePath, "savedVideos\\*.*"); //Creating the name, to open the file with this name in the next command
		if ((myFolder = FindFirstFile(strFilePath, &dataInFile)) != INVALID_HANDLE_VALUE) //Opening the folder
		{
			do
			{
				if ((strcmp(dataInFile.cFileName, ".") != ZERO) && (strcmp(dataInFile.cFileName, "..") != ZERO))
				{ //Every folder begins with one point and later to points,
				//so this condition check if the file is desirable or it is just points.
					if (!strcmp(dataInFile.cFileName, name)) //Checking if this file is equal to users input of the file name.
					{
						flag = 1; //The file is found.
						break;
					}
				}
			} while (FindNextFile(myFolder, &dataInFile)); //Moving to the next file
		}

		if (!flag) //Checking if the file was found
		{
			printf("This name doesn't exists, please check your input!\n"); //Output
		}

	} while (!flag); //Checking if the file was found, if it wasn't the loop would ask the use for new input.

	if (!FindClose(myFolder)) //Closing the folder
	{
		printf("There was a prblem in closing the folder.\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	strncat(nameAndPath, name, strlen(name)); //Adding to the nameAndPath (that is "savedVideos\\") the name of the film that the user wants to open.
	savedFile = fopen(nameAndPath, "r"); //Opening the file

	if (!savedFile) //Checking if the opening succeeded
	{
		//Testing if the opening of the file has been done successfully
		printf("Error opening the file\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	flag = 0; //Reset the flag for a new use.
	//The new use of the flag is if the file has reached the end(There aren't more items).
	while (!flag) //Checking if the file has reached the end.
	{
		nameForitem = (char*)calloc(MAX_NAME_SIZE, sizeof(char)); //Dynamic memory allocation
		if (!nameForitem) //Checking if the dynamic memory allocation succeeded
		{
			printf("Dynamic memory allocation failed\n"); //Output
			return NULL;
		}

		pathForitem = (char*)calloc(MAX_PATH_SIZE, sizeof(char)); //Dynamic memory allocation
		if (!pathForitem) //Checking if the dynamic memory allocation succeeded
		{
			printf("Dynamic memory allocation failed\n"); //Output
			return NULL;
		}

		tempForitem = (item_t*)malloc(sizeof(item_t)); //Dynamic memory allocation
		if (!tempForitem) //Checking if the dynamic memory allocation succeeded
		{
			printf("Dynamic memory allocation failed\n"); //Output
			return NULL;
		}
		tempForLink = (link_t*)malloc(sizeof(link_t)); //Dynamic memory allocation
		if (!tempForLink) //Checking if the dynamic memory allocation succeeded
		{
			printf("Dynamic memory allocation failed\n"); //Output
			return NULL;
		}

		tempForitem->name = nameForitem;
		tempForitem->path = pathForitem;
		tempForLink->item = tempForitem;
		tempForLink->next = NULL;
		if (flagFirstTime)
		{
			fseek(savedFile, ZERO, SEEK_SET); //Bringing the pointer to the beggining
		}
		place = 0; //Reset the place.
		letter = (char)fgetc(savedFile); //reading from the file.
		while (letter != '\n'  && letter != EOF) //While it isn't the end of the line and it isn't the end of the file
		{
			tempForLink->item->name[place] = letter;
			place++;
			letter = fgetc(savedFile); //reading from the file.
		}
		if (!strcmp(tempForLink->item->name, "end_of_list-Video_editing_program")) //Checking if it is the end of the file.
		{
			flag = 1; //It is the end of the file
		}
		else
		{
			if (flagFirstTime) //Checking if it is the first time
			{
				first = tempForLink;
				letter = fgetc(savedFile); //reading from the file.
				place = 0; //Reset the place.
				tempForLink->item->duration = 0;
				while (letter != '\n'  && letter != EOF) //While it isn't the end of the line and it isn't the end of the file
				{
					tempForLink->item->duration = tempForLink->item->duration * 10 + (letter - '0'); //Reading a letter from the file and adding it to the duration
					place++;
					letter = fgetc(savedFile); //reading from the file.
				}
				letter = fgetc(savedFile); //reading from the file.
				place = 0; //Reset the place.
				while (letter != '\n'  && letter != EOF) //While it isn't the end of the line and it isn't the end of the file
				{
					tempForLink->item->path[place] = letter;
					place++;
					letter = (char)fgetc(savedFile); //reading from the file.
				}
				flagFirstTime = 0; //From not it isn't the first time
			}
			else
			{
				letter = (char)fgetc(savedFile); //reading from the file.
				place = 0; //Reset the place.
				tempForLink->item->duration = 0;
				while (letter != '\n'  && letter != EOF) //While it isn't the end of the line and it isn't the end of the file
				{
					tempForLink->item->duration = tempForLink->item->duration * 10 + (letter - '0');
					place++;
					letter = (char)fgetc(savedFile); //reading from the file.
				}
				letter = (char)fgetc(savedFile); //reading from the file.
				place = 0;
				while (letter != '\n'  && letter != EOF) //While it isn't the end of the line and it isn't the end of the file
				{
					tempForLink->item->path[place] = letter;
					place++;
					letter = (char)fgetc(savedFile); //reading from the file.
				}
				addToEnd(first, tempForLink); //This function will add this link to the end of the file.
			}
			
		}
	}
	return first;
}

/*
The purpose of the function is to add an item to the end.
The function gets pointer to the first item, and the new item and returns pointer to the first item, 
because if the first item that it gets is NULL, the pointer to the first item would be changed.
*/
link_t* addToEnd(link_t* first, link_t* lastitem)
{
	if (!first) //Checking if the first item is NULL.
	{
		first = lastitem;
	}
	else
	{
		if (first->next) //Checking if the next item is NULL.
		{
			addToEnd(first->next, lastitem);
		}
		else
		{
			first->next = lastitem;
		}
	}
	return first;
}

/*
The purpose of the function is to print the names of all the saved videos.
The function gets nothing and returns nothing.
*/
void namesOfTheMovies(void)
{
	FILE* myFile = NULL; //Setting variables
	HANDLE myFolder; //Setting variables
	WIN32_FIND_DATA dataInFile; //Setting variables
	char strFilePath[] = "savedVideos\\*.*"; //Setting variables
	int i = 0; //Setting variables

	if ((myFolder = FindFirstFile(strFilePath, &dataInFile)) != INVALID_HANDLE_VALUE) //Opening the folder
	{
		do
		{
			if ((strcmp(dataInFile.cFileName, ".") != ZERO) && (strcmp(dataInFile.cFileName, "..") != ZERO))
			{ //Every folder begins with one point and later to points,
				//so this condition check if the file is desirable or it is just points.
				printf("* "); //Output
				for (i = 0; i < (strlen(dataInFile.cFileName) - strlen(".txt")); i++) //I want to print the name without the ".txt"
				{
					printf("%c", dataInFile.cFileName[i]); //Output
				}
				printf("\n"); //Output
			}
		} while (FindNextFile(myFolder, &dataInFile)); //Moving to the next file

	}
	if (!FindClose(myFolder)) //Closing the folder
	{
		printf("There was a prblem in closing the folder.\n\n"); //Output
	}
}

/*
The purpose of the function is to display all the saved videos.
The function gets nothing and returns 1 if there was a problen, else it returns 0.
*/
int showAllTheSavedMovies(void)
{
	FILE* myFile = NULL; //Setting variables
	HANDLE myFolder; //Setting variables
	WIN32_FIND_DATA dataInFile; //Setting variables
	char strFilePath[] = "savedVideos\\*.*"; //Setting variables
	char nameAndPath[MAX_NAME_SIZE] = { 0 }; //Setting variables
	link_t* tempForLink = NULL; //Setting variables
	item_t* tempForitem = NULL; //Setting variables
	link_t* first = NULL; //Setting variables
	int flag = 0, place = 0, flagFirstTime = 0; //Setting variables
	char* nameForitem = NULL; //Setting variables
	char* pathForitem = NULL; //Setting variables
	char letter = 0; //Setting variables
	FILE* savedFile = NULL; //Setting variables

	if ((myFolder = FindFirstFile(strFilePath, &dataInFile)) != INVALID_HANDLE_VALUE) //Opening the folder
	{
		do
		{
			if ((strcmp(dataInFile.cFileName, ".") != ZERO) && (strcmp(dataInFile.cFileName, "..") != ZERO))
			{ //Every folder begins with one point and later to points,
				//so this condition check if the file is desirable or it is just points.
				sprintf(nameAndPath, "savedVideos\\%s", dataInFile.cFileName); //Creating the name, to open the file with this name in the next command
				savedFile = fopen(nameAndPath, "r"); //Opening file
				if (!savedFile) //Checking if the dynamic memory allocation succeeded
				{
					//Testing if the opening of the file has been done successfully
					printf("Error opening the file\n\n"); //Output
				}

				flag = 0;//Reset the flag for a new use.
				//The new use of the flag is if the file has reached the end(There aren't more items).
				while (!flag) //Checking if the file has reached the end.
				{
					nameForitem = (char*)calloc(MAX_NAME_SIZE, sizeof(char)); //Dynamic memory allocation
					if (!nameForitem) //Checking if the dynamic memory allocation succeeded
					{
						printf("Dynamic memory allocation failed\n"); //Output
						return 1;
					}

					pathForitem = (char*)calloc(MAX_PATH_SIZE, sizeof(char)); //Dynamic memory allocation
					if (!pathForitem) //Checking if the dynamic memory allocation succeeded
					{
						printf("Dynamic memory allocation failed\n"); //Output
						return 1;
					}

					tempForitem = (item_t*)malloc(sizeof(item_t)); //Dynamic memory allocation
					if (!tempForitem) //Checking if the dynamic memory allocation succeeded
					{
						printf("Dynamic memory allocation failed\n"); //Output
						return 1;
					}
					tempForLink = (link_t*)malloc(sizeof(link_t)); //Dynamic memory allocation
					if (!tempForLink) //Checking if the dynamic memory allocation succeeded
					{
						printf("Dynamic memory allocation failed\n"); //Output
						return 1;
					}

					tempForitem->name = nameForitem;
					tempForitem->path = pathForitem;
					tempForLink->item = tempForitem;
					tempForLink->next = NULL;
					if (flagFirstTime)
					{
						fseek(savedFile, ZERO, SEEK_SET); //Bringing the pointer to the beggining
					}
					place = 0; //Reset the place
					letter = fgetc(savedFile); //reading from the file.
					while (letter != '\n'  && letter != EOF) //While it isn't the end of the line and it isn't the end of the file
					{
						tempForLink->item->name[place] = letter;
						place++;
						letter = fgetc(savedFile); //reading from the file.
					}

					if (!strcmp(tempForLink->item->name, "end_of_list-Video_editing_program")) //Checking if it is the end of the file.
					{
						flag = 1; //It is the end of the file
					}
					else
					{
						letter = fgetc(savedFile); //reading from the file.
						place = 0; //Reset the place
						tempForLink->item->duration = 0; //Reset the duration
						while (letter != '\n'  && letter != EOF) //While it isn't the end of the line and it isn't the end of the file
						{
							tempForLink->item->duration = tempForLink->item->duration * 10 + (letter - '0'); //Reading a letter from the file and adding it to the duration
							place++;
							letter = fgetc(savedFile); //reading from the file.
						}
						letter = fgetc(savedFile); //reading from the file.
						place = 0; //Reset the place
						while (letter != '\n'  && letter != EOF) //While it isn't the end of the line and it isn't the end of the file
						{
							tempForLink->item->path[place] = letter;
							place++;
							letter = fgetc(savedFile); //reading from the file.
						}
						first = addToEnd(first, tempForLink); //This function will add this link to the end of the file.
					}
				}
				play(first); //Function call
				Sleep(200); //To separate between the videos
				freeFun(first); //Function call
				first = NULL; //Reset the pointer to the first item
				fclose(savedFile);
			}
		} while (FindNextFile(myFolder, &dataInFile)); //Moving to the next file

	}
	if (!FindClose(myFolder)) //Closing the folder
	{
		printf("There was a prblem in closing the folder.\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	return 0;
}

/*
The purpose of the function is to let the user to change the color of the background and the foreground.
The function gets nothing and returns nothing.
*/
void colorFun(void)
{
	char background = ' ', foreground = ' '; //Setting variables
	char command[9] = { 0 }; //Setting variables
	int flag = 0; //Setting variables

	do
	{
		printf("* * * * * * * * * * * * * * * * * * *\n"); //Output
		printf("*                                   *\n"); //Output
		printf("* 0 = Black       8 = Gray          *\n"); //Output
		printf("* 1 = Blue        9 = Light Blue    *\n"); //Output
		printf("* 2 = Green       A = Light Green   *\n"); //Output
		printf("* 3 = Aqua        B = Light Aqua    *\n"); //Output
		printf("* 4 = Red         C = Light Red     *\n"); //Output
		printf("* 5 = Purple      D = Light Purple  *\n"); //Output
		printf("* 6 = Yellow      E = Light Yellow  *\n"); //Output
		printf("* 7 = White       F = Bright White  *\n"); //Output
		printf("*                                   *\n"); //Output
		printf("* * * * * * * * * * * * * * * * * * *\n"); //Output

		printf("Choose a color for the background: "); //Output
		scanf("%c", &background); //Input
		getchar(); //Remove '\n'
		printf("Choose a color for the foreground: "); //Output
		scanf("%c", &foreground); //Input
		getchar(); //Remove '\n'

		if (!(checkInputOfColor(background) && checkInputOfColor(foreground))) //function call
		{
			printf("Please check your input!\n"); //Output
		}
		else
		{
			flag = 1; //The input is right
		}
	} while (!flag);

	if (background == foreground) //Checking if the colors are the same
	{
		printf("The colors can't be the same!\n"); //Output
	}
	else
	{
		sprintf(command, "COLOR %c%c", background, foreground); //Creating the command for the system
		system(command); //Changing the color
	}
}

/*
The purpose of the function is to check the input of the user (for the color function).
The function gets the choise of the user and returns 1 if it is OK and 0 if the input is wrong.
*/
int checkInputOfColor(char choiseOfUser)
{
	int ans = 0; //Setting variables

	if (((int)choiseOfUser >= 48 && (int)choiseOfUser <= 57) ||  //Check if it is a number
		(choiseOfUser >= 'A' && choiseOfUser <= 'F') || //Check if it is a big digit
		(choiseOfUser >= 'a' && choiseOfUser <= 'f')) //Check if it is a small digit
	{
		ans = 1; //The input is right
	}

	return ans;
}
