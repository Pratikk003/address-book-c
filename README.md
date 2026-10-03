# Address Book (C)

A command-line contact management system written in C, with input validation, sorting, and file-based persistence.

## Features

- **Create, search, edit, and delete** contacts
- **Search by name, phone, or email** (case-insensitive)
- **Sort contacts** by name, phone, or email before listing
- **Input validation:**
  - Phone numbers must be exactly 10 digits
  - Emails are checked for a valid `@` structure (text before/after, no spaces, no duplicate `@`)
- **Persistent storage** — contacts are saved to a CSV file on exit and reloaded automatically on the next run
- Confirmation prompt before deleting a contact

## Project Structure

```
address-book-c/
├── src/
│   ├── main.c        # Menu loop and program entry point
│   ├── contact.c      # Create/search/edit/delete/list/sort logic + validation
│   ├── file.c         # Save/load contacts to/from CSV
│   └── populate.c     # Optional dummy data for testing
├── include/
│   ├── contact.h
│   └── file.h
├── data/
│   └── sample-contacts.csv   # Example data you can try the app with
├── Makefile
└── README.md
```

## Build & Run

Requires `gcc` (or any C compiler) and `make`.

```bash
make        # builds the 'addressbook' binary
make run    # builds and runs it
make clean  # removes the compiled binary
```

Or compile manually:

```bash
gcc -Wall -Iinclude -o addressbook src/main.c src/contact.c src/file.c src/populate.c
./addressbook
```

### Trying it with sample data

The program reads/writes `contacts.csv` in the directory you run it from. To start with some example contacts instead of an empty address book:

```bash
cp data/sample-contacts.csv contacts.csv
./addressbook
```

## Example

```
==============================
:::: ADDRESS BOOK MENU ::::
==============================
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save and Exit
Enter your choice:
```

## Notes

- `MAX_CONTACTS` is fixed at 100 (see `include/contact.h`) since contacts are stored in a static array rather than a dynamic structure.
- This was built as a learning project to practice C fundamentals: structs, file I/O, string handling, and basic sorting/searching algorithms (bubble sort, linear search).

## License

MIT — see [LICENSE](LICENSE)
