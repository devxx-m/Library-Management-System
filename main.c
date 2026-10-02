#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addBook();
void displayBook();
void listAuthorBooks();
void totalBooks();
void clearInputBuffer();

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

struct books{
    char title[50];
    char AuthorName[50];
    int bookID;
    float price;
};

struct books bk[100];
int count = 0;

int main(){

    int choice = 0;
    printf("*** LIBRARY MANAGEMENT SYSTEM ***\n");

    do{
        printf("\n1. Add book information\n");
        printf("2. Display book information\n");
        printf("3. List all books of a given author\n");
        printf("4. List of the count of books in the library\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        if(scanf("%d", &choice) != 1){
            clearInputBuffer();
            printf("\nInvalid input! Please enter a number.\n");
            continue;
        }

        clearInputBuffer();

        switch(choice){
            case 1:
                addBook();
                break;
            case 2:
                displayBook();
                break;
            case 3:
                listAuthorBooks();
                break;
            case 4:
                totalBooks();
                break;
            case 5:
                printf("\nThanks for using our system! See you soon.\n");
                break;
            default:
                printf("\nInvalid choice! Please select 1 - 5.\n");
        }

    }while(choice != 5);

    return 0;
}

void addBook(){
    if(count >= 100){
        printf("The library is full!\n");
        return;
    }

    printf("\n *** ADD BOOK INFORMATION ****\n");

    printf("Enter book title: ");
    fgets(bk[count].title, 50, stdin);
    bk[count].title[strcspn(bk[count].title, "\n")] = 0;

    printf("Enter Author name: ");
    fgets(bk[count].AuthorName, 50, stdin);
    bk[count].AuthorName[strcspn(bk[count].AuthorName, "\n")] = 0;

    do {
        printf("Enter book id: ");
        if(scanf("%d", &bk[count].bookID) != 1){
            printf("[ERROR] Invalid input! ID must be a number.\n");
            clearInputBuffer();
        } else if(bk[count].bookID <= 0){
            printf("[ERROR] Book ID must be greater than 0.\n");
            clearInputBuffer();
        } else {
            break;
        }
    } while(1);

    do {
        printf("Enter the price ($): ");
        if(scanf("%f", &bk[count].price) != 1){
            printf("[ERROR] Invalid input! Price must be a number.\n");
            clearInputBuffer();
        } else if(bk[count].price <= 0){
            printf("[ERROR] Price must be greater than 0.\n");
            clearInputBuffer();
        } else {
            break;
        }
    } while(1);

    printf("\n[SUCCESS] Book \"%s\" added successfully!\n", bk[count].title);

    count++;

    clearInputBuffer();
}

void displayBook(){
    if(count == 0){
        printf("No books available in the library.\n");
        return;
    }

    printf("=== Display All Books ===\n");

    for(int i = 0; i < count; i++){
        printf("Book %d: \n", i+1);
        printf("ID: %d\n", bk[i].bookID);
        printf("Title: %s\n", bk[i].title);
        printf("Author: %s\n", bk[i].AuthorName);
        printf("Price: %.2f\n", bk[i].price);
        printf("--------------\n");
    }
}

void listAuthorBooks(){
    if(count == 0){
        printf("No books available in the library.\n");
        return;
    }

    char name[50];
    int found = 0;

    printf("\n=== LIST OF BOOKS BY AUTHOR ====\n");
    printf("Enter Author Name: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;

    for(int i = 0; i < count; i++){
        if(strcmp(bk[i].AuthorName, name) == 0){
            if(found == 0){
                printf("\nBooks found for \"%s\":\n", name);
            }
            printf("\nBook #%d:\n", i + 1);
            printf("  ID     : %d\n", bk[i].bookID);
            printf("  Title  : %s\n", bk[i].title);
            printf("  Price  : $%.2f\n", bk[i].price);
            printf("-------------------------\n");
            found = 1;
        }
    }

    if(!found){
        printf("\n[INFO] No books found for author \"%s\".\n", name);
    }
}

void totalBooks(){
    printf("\n=== TOTAL BOOKS ===\n");
    printf("Total number of books in the library: %d\n", count);
}