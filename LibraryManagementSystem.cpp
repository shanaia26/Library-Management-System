#define _CRT_SECURE_NO_WARNINGS
#define bool int
#define false 0
#define true (!false)

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Preprocessor Variable
#define SIZE 10

//Stucture for data part of a LinearNode
struct data {
	int bookIdentifier; //8-digit number in the form xxxx-xxxx
	char title[50];
	char author[50];
	int year; //Cannot be older than 2008
	bool borrowed; //If book is borrowed or not
	char customerName; //If its loaned to customer
	int loanedBook; //amount of times book has been loaned	
};

//Stucture for node
struct LinearNode {
	struct data *element;
	struct LinearNode *next;
};

// Function prototypes
void displayMenu(FILE *);
void addBook();  //adding book to end of the list
bool checkId(char*); //checks ID format
void borrowBook(int);
void returnBook(int);
void deleteBook(int); // delete a specific book
void displayAllBooks();
void displaySpecificBook(int);
//File Handling
void writeToFile(FILE *); //writes list of books to file
void readFromFile(FILE *); //reads in list of books from file
bool isEmpty(); //checks if list has any books


// Global Variables
struct LinearNode *front = NULL;
struct LinearNode *last = NULL;
bool read = false;

/**************MAIN FUNCTION*******************/
int main() {

	FILE *filePointer;
	
	//If file does not exist get user to input books to the library
	if((filePointer = fopen("book.dat", "rb")) == NULL){
	printf("There are no books stored in the library, you need to add books \n");
	addBook();
    }
    else if(read == false){
    	read = true;
    	readFromFile(fp);
    	displayAllBooks();
    	printf("Books have been populated \n");
	}
	
	input(fp);
	
	getchar();
	getchar();
}

void displayMenu(File *filePointer){

		
	do{
		printf("1. Add a new book to the library \n");
		printf("2. Allow customer to take out a book \n");
		printf("3. Allow customer to return a book \n");
		printf("4. Delete an old book from stock \n");
		printf("5. View all books \n");
		printf("6. View a specific book \n");
		printf("7. Exit the system \n");
		scanf("%d", &choice);	
		
		if (choice == 1) {
			//Add book to library
			addBook();
		}
		else if (choice == 2) {
			//Take out a book
			printf("Please enter the id of the book you wish to borrow : ");
			scanf("%d", &bookIdentifier);
			borrowBook(bookIdentifier);
		}
		else if (choice == 3) {
			//Return a book
			printf("Please enter the id of the book you wish to return : ");
			scanf("%d", &bookIdentifier);
			returnBook(bookIdentifier);
		}
		else if (choice == 4) {
			//Delete an old book from stock
			printf("Please enter the identifier of the book you wish to delete from the library : ");
			scanf("%d", &bookIdentifier);
			deleteBook(bookIdentifier);
		}
		else if (choice == 5) {
			//View all books
			displayAllBooks();
		}
		else if (choice == 6) {
			//View a specific book
			printf("Please enter the identifier of the book you wish to view : ");
			scanf("%d", &bookIdentifier);
			displaySpecificBook(bookIdentifier);
		}
		else if(choice == 7){
			printf("All books will be copied to books.dat\n");
			writeToFile(filePointer);
		}
	} while (choice != 7);//End of loop
}

//Add a book to the library
void addBook() {

	struct LinearNode *aNode;
	struct data *anElement;

		//Create space for data part of node
		 anElement = (struct data *)malloc(sizeof(struct data));
		
		if (anElement == NULL)
			printf("Error - no space for the new book\n");
		else
		{
			//Input details of the book into the data part
			printf("Enter book identifier: \n");
			scanf("%d", &anElement->bookIdentifier );
				
			printf("Enter the name of the book: \n");
			scanf("%s", &anElement->title);
		
			printf("Enter the author of the book: \n");
			scanf("%s", &anElement->author);
		
			do{
			printf("Enter the year of publication: \n");
			scanf("%d", &anElement->year);
			if(anElement->year < 2008){
				printf("Book must be older than 2008 \n");
			}
			}while(anElement->year < 2008);
			
			printf("\n");
			
			//Book has not been borrowed as it is a new book
			anElement->borrowed = false;
			//Set to 0 as it has not been borrowed
			anElement->loanedBook = 0;
		
			// create space for new node that will contain data
			aNode = (struct LinearNode *)malloc(sizeof(struct LinearNode));

			if (aNode == NULL)
				printf("Error - no space for the new book\n");
			else { // add data part to the node
				aNode->element = anElement;
				aNode->next = NULL;

				//add node to end of the list
				if (isEmpty())
				{
					front = aNode;
					last = aNode;
				}
				else {
					last->next = aNode;
					last = aNode;
				} 
			}
		}
} 

bool checkId(char *id){
	bool error = false;
	if (strlen(id) < 9) {
				error = true;
			}
			else{
				for (int i = 0; id[i] != '\0'; i++) {
					if (i < 4 || i >4) {
					if (!isdigit(id[i]))
						error = true;}
	 				else {
					if (!ispunct(id[i]))
						error = true;}
				}
			}			
	return error;		
}

//Display books in list
void displayAllBooks() {
	struct LinearNode *current;

	printf("\n");
	if (isEmpty())
		//If library is empty
		printf("Error - there are no books in the library\n");
	else {
		current = front;
		while (current != NULL) {
			//If library has books
			printf("Book ID is %d \n", current->element->bookIdentifier);
			printf("Book title is %s \n", current->element->title);
			printf("Book author is %s \n", current->element->author);
			printf("Book was published in the year %d \n", current->element->year);
			if(current->element->borrowed){
				printf("Book is borrowed \n");
			}
			else{
				printf("Book is not borrowed \n");
			}
			printf("This book has been borrowed %d times \n", current->element->loanedBook);
			current = current->next;
		} 
	}
}

//Delete book from library
void deleteBook(int bookIdentifier) {
	struct LinearNode *current, *previous;
	bool notFound = true;

	printf("\n");
	if (isEmpty())
		printf("Error - there are no books in the library \n");
	else {
		current = previous = front;

		while (notFound && current != NULL) {
			//If bookIdentifier user inputted matches a book in the library
			if (bookIdentifier == current->element->bookIdentifier)
				notFound = false;
			else {
				previous = current;
				current = current->next;
			}
		}

		if (notFound)
			printf("Error - this identifier cannot be found %d \n", bookIdentifier);
		else {
			printf("Book with identifier %d \n", current->element->bookIdentifier );
			if (current == front) { //delete front node
				front = front->next;
				free(current);
			} 
			else if (current == last) {//delete last node
				free(current);
				previous->next = NULL;
				last = previous;
			}
			else {//delete node in middle of list
				previous->next = current->next;
				free(current);
			} 
			
			printf("Book with identifier %d has been deleted \n", bookIdentifier);
		}
	}
}

void borrowBook(int bookIdentifier) {
	struct LinearNode *current, *previous;
	bool notFound = true;

	printf("\n");
	if (isEmpty())
		printf("Error - there are no books in the library\n");
	else {
		current = previous = front;

		while (notFound && current != NULL) {
			if (bookIdentifier == current->element->bookIdentifier)
				notFound = false;
			else {
				previous = current;
				current = current->next;
			}//end else
		} //end while

		if (notFound)
			printf("Error - Book with this identifier cannot be found %d \n", bookIdentifier);
		else {
			printf("Book with identifier %d has been borrowed \n", current->element->bookIdentifier );
			current->element->borrowed = true;
			current->element->loanedBook ++;
		}
	}
}

void returnBook(int bookIdentifier) {
	struct LinearNode *current, *previous;
	bool notFound = true;

	printf("\n");
	if (isEmpty())
		printf("Error - there are no books in the library\n");
	else {
		current = previous = front;

		while (notFound && current != NULL) {
			if (bookIdentifier == current->element->bookIdentifier)
				notFound = false;
			else {
				previous = current;
				current = current->next;
			}//end else
		} //end while

		if (notFound)
			printf("Error - Book with this identifier cannot be found %d \n", bookIdentifier);
		else {
			printf("Book with identifier %d has been returned \n", current->element->bookIdentifier );
			current->element->borrowed = false;
		}
	}
}

//Display books in list
void displaySpecificBook(int bookIdentifier) {
	struct LinearNode *current, *previous;
	bool notFound = true;
	
	printf("\n");
	if (isEmpty())
		printf("Error - there are no books in the library\n");
	else {
		current = previous = front;

		while (notFound && current != NULL) {
			if (bookIdentifier == current->element->bookIdentifier)
				notFound = false;
			else {
				previous = current;
				current = current->next;
			}//end else
		} //end while

		if (notFound)
			printf("Error - this identifier cannot be found %d \n", bookIdentifier);
		else {
				printf("Book ID is %d \n", current->element->bookIdentifier);
			printf("Book title is %s \n", current->element->title);
			if(current->element->borrowed){
				printf("Book is borrowed \n");
			}
			else{
				printf("Book is not borrowed \n");
			}
			printf("This book has been borrowed %d times \n", current->element->loanedBook);
			current = current->next;
		}
	}
}

//Checks if library is empty
bool isEmpty() {
	if (front == NULL)
		return true;
	else
		return false;
}

//Write books to file
void writeToFile(FILE *filePointer) {
	struct LinearNode *current;
	current = front;
	filePointer = fopen("book.dat", "wb");
	if (filePointer != NULL) {
		while ( current != NULL) {
			fwrite(current->element, sizeof(struct book), 1, filePointer);
			printf("Writing:%s to file\n", current->element->id);
			current = current->next;
		}
	}
	else
		printf("Error opening file\n");
	fclose(filePointer);

}


void readFromFile(FILE *filePointer) {
	struct LinearNode *node;
	struct book *element;
	element = (struct book *)malloc(sizeof(struct book));
	//Try casting to book or linear node
	node = NULL;
	filePointer = fopen("book.dat", "rb");
	if (filePointer != NULL) {
		fseek(fp, 0, SEEK_END);
		long fileSize = ftell(filePointer);
		rewind(filePointer);
		int numEntries = (int)(fileSize / sizeof(struct book));
		printf("numEntries: %d\n", numEntries);

		
		while (fread(element, sizeof(struct book), 1, fp) != NULL) {
			node = (struct LinearNode *)malloc(sizeof(struct LinearNode));
			if (node == NULL)
				printf("Error - no space for the new node\n");
			else { // add book part to the node
				node->element = element;
				node->next = NULL;
				
				//add node to end of the list
				if (isEmpty())
				{
					front = node;
					last = node;
					printf("in if(isEmpty())\n");
				}
				else {
					last->next = node;
					last = node;
					printf("in else\n");
				} //end else
				printf("Book ID: %s\n", node->element->id);
			}//end else
			
		}
	}
	else
		printf("File open error");
	fclose(filePointer);
}





