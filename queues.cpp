//Operating and maintaining a queue
#include<iostream>

//Structure to define a queue
//Node contains a character and a pointer to the previous node
struct node
{
	char data;
	node* prevPtr;
};

void enqueue(node**, node**, char);	//insert an item to the back of the queue
void dequeue(node**, node**);		//delete an item from the front of the queue
int isEmpty(node*);					//check if the queue if empty
void printQueue(node*);				//print the queue
void instructions();				//show the user menu

int main()
{
	int choice;					//Stores the choice from the user
	char item;					//Stores the data the user enters

	node* headPtr = NULL;		//Points to front of the queue
	node* tailPtr = NULL;		//Points to the back of the queue

	instructions();				//Prints the instructions
	std::cin >> choice;			//Gets the user choice

	while (choice != 3)			//Loop as long as choice is not 3
	{
		//The switch statement allows us to easily work with the user choices
		switch (choice)
		{
			//The user wants to enter an item on back of the queue
		case 1:
			std::cout << "Enter a character: " << std::endl;
			std::cin >> item;
			enqueue(&headPtr, &tailPtr, item);
			printQueue(headPtr);
			break;

			//The user wants to delete an item from the front of the queue
		case 2:
			//Check if the queue is not empty
			if (!isEmpty(headPtr))
			{
				dequeue(&headPtr, &tailPtr);
				printQueue(headPtr);
			}
			//The queue is empty, tell the user the queue is empty
			else
			{
				std::cout << "The queue is empty." << std::endl;
			}
			break;
			//User choice is invalid, display error and show menu again
		default:
			std::cout << "Invalid choice." << std::endl;
			instructions();
			break;
		}

		//Get choice from the user again
		instructions();
		std::cin >> choice;
	}

	std::cout << "Program terminated." << std::endl;
	return 0;
}

//Function: enqueue
//Inputs: pointer to front and back of the queue and item to insert
//Outputs: insert item to the back of the queue
//Errors: none
void enqueue(node** headPtr, node** tailPtr, char item)
{
	node* newPtr;				//newPtr - our new location
	newPtr = new node;			//allocate memory for the new location

	//check to see if newPtr is NULL, it will be NULL if we could not allocate memory to it
	if (newPtr != NULL)
	{
		newPtr->data = item;			//Set data to the value provided by the data provided by the user
		newPtr->prevPtr = NULL;			//Set prevPtr of the newly created node to NULL so we set the end of the queue		

		//Check if the front of the queue is currently pointing to NULL, if it is then the queue is empty
		if (isEmpty(*headPtr))
		{
			*headPtr = newPtr;			//Set headPtr to the newly created node
		}
		//The queue is not empty set the previous of tailPtr to the newly created node so the tail moves back one spot
		else
		{
			(*tailPtr)->prevPtr = newPtr;
		}

		*tailPtr = newPtr;				//Set tailPtr to newly created node
	}
	else
	{
		//Print error message is we cannot allocate memory
		std::cout << "Could not insert " << item << ". No memory available." << std::endl;
	}
}

//Function: dequeue
//Inputs: pointer to front and back of the queue
//Outputs: removes item from the front of the queue
//Errors: none
void dequeue(node** headPtr, node** tailPtr)
{
	node* tempPtr;
	tempPtr = *headPtr;					//Save the location of headPtr to a temporary location
	*headPtr = (*headPtr)->prevPtr;		//Set headPtr to the location of prevPtr
	free(tempPtr);						//Free the temporary location to clear up memory

	//Check if headPtr is now empty, indicating that the queue is empty
	if (isEmpty(*headPtr))
	{
		tailPtr = NULL;				//Set tailPtr to NULL
	}
}

//Function: instructions
//Inputs: none
//Ouputs: shows the user menu on the screen
//Errors: none
void instructions()
{
	std::cout << "Enter your choice: " << std::endl;
	std::cout << "1 to insert an item into the back of the queue." << std::endl;
	std::cout << "2 to remove an item from the front of the queue." << std::endl;
	std::cout << "3 to end" << std::endl;
}

//Function: isEmpty
//Inputs: pointer to front of queue
//Outputs: returns 1 if the queue is empty, otherwise returns 0
//Errors: none
int isEmpty(node* sPtr)
{
	//Checks if sPtr is equal to NULL, if it is then it returns 1
	return sPtr == NULL;
}

//Function printQueue
//Inputs: pointer to front of queue
//Outputs: prints the elements of the queue to the screen
//Errors: none
void printQueue(node* currentPtr)
{
	//Check if currentPtr is NULL, if it is NULL then the queue is empty
	if (!currentPtr)
	{
		std::cout << "Queue is empty." << std::endl;
	}

	//Queue is not empty, begin printing it
	else
	{
		std::cout << "The queue is: " << std::endl;
		//Loop until we reach the back of the queue
		while (currentPtr)
		{
			printf("%c --> ", currentPtr->data);	//Print the content
			currentPtr = currentPtr->prevPtr;		//Update currentPtr to move to previous item
		}

		std::cout << "NULL" << std::endl;
	}
}