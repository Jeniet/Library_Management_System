================================================
         Library Management System README
================================================

Welcome to the Library Management System! This command-line application allows you to manage books and borrowers efficiently.

------------------------------------------------
Overview
------------------------------------------------
The Library Management System enables users to:
- Register new borrower accounts
- Add, remove, and manage books in the library
- Borrow and return books
- Track overdue books
- Print lists of books and borrowers

------------------------------------------------
User Interface
------------------------------------------------
Upon starting the program, you'll see a menu with options:

Library Management System Menu:
1. Register Account
2. Add Book
3. Remove Book
4. Borrow Book
5. Return Book
6. Track Overdue Books
7. Print All Books
8. Print All Borrowers
9. Exit

Enter your choice:

------------------------------------------------
Usage Instructions
------------------------------------------------
- **Register Account**: Register a new borrower by entering their name.
- **Add Book**: Add a new book to the library by entering its ID, title, and author.
- **Remove Book**: Remove a book from the library by entering its ID.
- **Borrow Book**: Allow borrowers to borrow available books by entering their ID and selecting a book.
- **Return Book**: Enable borrowers to return a borrowed book by entering its ID and their borrower ID.
- **Track Overdue Books**: Display books that are overdue (not returned within the due date). Note: This feature may not work as expected due to the absence of a Database Management System (DBMS).
- **Print All Books**: Print a list of all books in the library, including their ID, title, author, and status (available or lent).
- **Print All Borrowers**: Print a list of all registered borrowers, including their ID, name, and borrowed book IDs.
- **Exit**: Terminate the program.

------------------------------------------------
Tips for Usage
------------------------------------------------
- Ensure to enter valid IDs and inputs as prompted by the system.
- Error messages will guide you through operations that fail (e.g., book not found, borrower not found, book already lent).
- Note: Error handling in this system may have some limitations and may not cover all edge cases. Use with caution and report any issues for future improvements.
- Due to the absence of a DBMS, the "Track Overdue Books" feature may not accurately reflect overdue statuses. It relies on system time and does not persist data between sessions.

------------------------------------------------
Example Workflow
------------------------------------------------
1. Register an account with your name.
2. Add several books to the library.
3. Borrow books using your borrower ID.
4. Return borrowed books when done.
5. Check for overdue books to manage returns promptly.
6. Print lists to review library contents and borrower details.

------------------------------------------------
Exiting the Program
------------------------------------------------
- To exit, select option 9 (Exit) from the main menu. This will terminate the application.

================================================

