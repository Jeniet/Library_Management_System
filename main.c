#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 10

typedef struct Book {
    int book_id;
    char title[100];
    char author[100];
    int is_lent;
    time_t due_date;
    struct Book* next;
} Book;

typedef struct Borrower {
    int borrower_id;
    char name[100];
    struct BorrowedBook* borrowed_books;
    struct Borrower* next;
} Borrower;

typedef struct BorrowedBook {
    int book_id;
    struct BorrowedBook* next;
} BorrowedBook;

typedef struct HashTable {
    Book* books[TABLE_SIZE];
    Borrower* borrowers[TABLE_SIZE]; 
} HashTable;

unsigned int hash(int key) {
    return key % TABLE_SIZE;
}

Book* create_book(int book_id, char* title, char* author) {
    Book* new_book = (Book*)malloc(sizeof(Book));
    new_book->book_id = book_id;
    strcpy(new_book->title, title);
    strcpy(new_book->author, author);
    new_book->is_lent = 0;
    new_book->due_date = 0;
    new_book->next = NULL;
    return new_book;
}

Borrower* create_borrower(int borrower_id, char* name) {
    Borrower* new_borrower = (Borrower*)malloc(sizeof(Borrower));
    new_borrower->borrower_id = borrower_id;
    strcpy(new_borrower->name, name);
    new_borrower->borrowed_books = NULL;
    new_borrower->next = NULL;
    return new_borrower;
}

void insert_book(HashTable* table, Book* book) {
    unsigned int index = hash(book->book_id);
    book->next = table->books[index];
    table->books[index] = book;
}

void insert_borrower(HashTable* table, Borrower* borrower) {
    unsigned int index = hash(borrower->borrower_id);
    borrower->next = table->borrowers[index];
    table->borrowers[index] = borrower;
}

Book* find_book(HashTable* table, int book_id) {
    unsigned int index = hash(book_id);
    Book* current = table->books[index];
    while (current != NULL && current->book_id != book_id) {
        current = current->next;
    }
    return current;
}

Borrower* find_borrower(HashTable* table, int borrower_id) {
    unsigned int index = hash(borrower_id);
    Borrower* current = table->borrowers[index];
    while (current != NULL && current->borrower_id != borrower_id) {
        current = current->next;
    }
    return current;
}

void remove_book(HashTable* table, int book_id) {
    unsigned int index = hash(book_id);
    Book* current = table->books[index];
    Book* prev = NULL;
    while (current != NULL && current->book_id != book_id) {
        prev = current;
        current = current->next;
    }
    if (current != NULL) {
        if (prev == NULL) {
            table->books[index] = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
        printf("Book ID %d is removed from the library.\n", book_id);
    } else {
        printf("Book ID %d not found in the library.\n", book_id);
    }
}

void remove_borrower(HashTable* table, int borrower_id) {
    unsigned int index = hash(borrower_id);
    Borrower* current = table->borrowers[index];
    Borrower* prev = NULL;
    while (current != NULL && current->borrower_id != borrower_id) {
        prev = current;
        current = current->next;
    }
    if (current != NULL) {
        if (prev == NULL) {
            table->borrowers[index] = current->next;
        } else {
            prev->next = current->next;
        }
        BorrowedBook* bb = current->borrowed_books;
        while (bb != NULL) {
            BorrowedBook* temp = bb;
            bb = bb->next;
            free(temp);
        }
        free(current);
    }
}

void lend_book(HashTable* table, int borrower_id) {
    printf("Available Books:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Book* current = table->books[i];
        while (current != NULL) {
            if (!current->is_lent) {
                printf("Book ID: %d, Title: %s, Author: %s\n",
                       current->book_id, current->title, current->author);
            }
            current = current->next;
        }
    }
    int book_id;
    printf("Enter Book ID to Borrow: ");
    scanf("%d", &book_id);

    Book* book = find_book(table, book_id);
    Borrower* borrower = find_borrower(table, borrower_id);
    if (book != NULL && borrower != NULL && !book->is_lent) {
        book->is_lent = 1;
        book->due_date = time(NULL) + 7 * 24 * 60 * 60; 

        BorrowedBook* new_borrowed_book = (BorrowedBook*)malloc(sizeof(BorrowedBook));
        new_borrowed_book->book_id = book_id;
        new_borrowed_book->next = borrower->borrowed_books;
        borrower->borrowed_books = new_borrowed_book;

        printf("Book ID %d borrowed by Borrower ID %d\n", book_id, borrower_id);
    } else {
        printf("Error: Book not available or invalid borrower ID.\n");
    }
}

void return_book(HashTable* table, int book_id, int borrower_id) {
    Borrower* borrower = find_borrower(table, borrower_id);
    if (borrower != NULL) {
        BorrowedBook* bb = borrower->borrowed_books;
        BorrowedBook* prev = NULL;
        while (bb != NULL && bb->book_id != book_id) {
            prev = bb;
            bb = bb->next;
        }
        if (bb != NULL) {
            if (prev == NULL) {
                borrower->borrowed_books = bb->next;
            } else {
                prev->next = bb->next;
            }
            free(bb);

            Book* book = find_book(table, book_id);
            if (book != NULL) {
                book->is_lent = 0;
                book->due_date = 0;
                printf("Book ID %d returned by Borrower ID %d\n", book_id, borrower_id);
            }
        }
    }
}

void track_overdue_books(HashTable* table) {
    time_t now = time(NULL);
    int found_overdue = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Book* current = table->books[i];
        while (current != NULL) {
            if (current->is_lent && current->due_date < now) {
                printf("Overdue Book: %s (ID: %d), Due Date: %s",
                       current->title, current->book_id, ctime(&current->due_date));
                found_overdue = 1;
            }
            current = current->next;
        }
    }
    if (!found_overdue) {
        printf("No overdue books found.\n");
    }
}

void print_borrowed_books(BorrowedBook* borrowed_books) {
    if (borrowed_books == NULL) {
        printf("None");
    } else {
        while (borrowed_books != NULL) {
            printf("%d", borrowed_books->book_id);
            borrowed_books = borrowed_books->next;
            if (borrowed_books != NULL) {
                printf(", ");
            }
        }
    }
}

void print_borrowers(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Borrower* current = table->borrowers[i];
        while (current != NULL) {
            printf("Borrower ID: %d, Name: %s, Borrowed Book ID's: ",
                   current->borrower_id, current->name);
            if (current->borrowed_books) {
                print_borrowed_books(current->borrowed_books);
            } else {
                printf("None");
            }
            printf("\n");
            current = current->next;
        }
    }
}

void print_books(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Book* current = table->books[i];
        while (current != NULL) {
            printf("Book ID: %d, Title: %s, Author: %s, Status: %s\n",
                   current->book_id, current->title, current->author,
                   current->is_lent ? "Lent" : "Available");
            current = current->next;
        }
    }
}

void menu(HashTable* table) {
    int choice;
    char name[100];
    int id_counter = 1;
    int book_id, borrower_id;
    char title[100], author[100];

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Register Account\n");
        printf("2. Add Book\n");
        printf("3. Remove Book\n");
        printf("4. Borrow Book\n");
        printf("5. Return Book\n");
        printf("6. Track Overdue Books\n");
        printf("7. Print All Books\n");
        printf("8. Print All Borrowers\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Your Name: ");
                scanf("%s", name);
                insert_borrower(table, create_borrower(id_counter, name));
                printf("Account '%s' registered successfully. Your ID is %d.\n", name, id_counter++);
                break;

            case 2:
                printf("Enter Book ID: ");
                scanf("%d", &book_id);
                printf("Enter Title: ");
                scanf("%s", title);
                printf("Enter Author: ");
                scanf("%s", author);
                insert_book(table, create_book(book_id, title, author));
                break;

            case 3:
                printf("Enter Book ID to Remove: ");
                scanf("%d", &book_id);
                remove_book(table,book_id);                
                break;

            case 4:
                printf("Enter Your ID: ");
                scanf("%d", &borrower_id);
                lend_book(table, borrower_id);
                break;

            case 5:
                printf("Enter Book ID to Return: ");
                scanf("%d", &book_id);
                printf("Enter Your ID: ");
                scanf("%d", &borrower_id);
                return_book(table, book_id, borrower_id);
                break;

            case 6:
                track_overdue_books(table);
                break;

            case 7:
                print_books(table);
                break;

            case 8:
                print_borrowers(table);
                break;

            case 9:
                exit(0);
                break;

            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

int main() {
    HashTable table = { {NULL}, {NULL} };

    // Sample data
    insert_book(&table, create_book(1, "1984", "George Orwell"));
    insert_book(&table, create_book(2, "To Kill a Mockingbird", "Harper Lee"));
    insert_book(&table, create_book(3, "The Great Gatsby", "F. Scott Fitzgerald"));
    insert_book(&table, create_book(4, "Brave New World", "Aldous Huxley"));
    insert_book(&table, create_book(5, "Pride and Prejudice", "Jane Austen"));

    // Interactive menu
    menu(&table);

    return 0;
}
