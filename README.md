# Sufier
A contact book with basic hash table functionality, and file management.

## Compiling 
In Sufier there are no external extension source files compilation. However users trying to compile Sufier, using latest GCC version may encounter a certain bug regarding array limits (this error occured during the development, while using GCC 13.0). If you encounter this error pleace downgrade your GCC version to at least 10.5.
In order to compile this program, the user shall type `make` while being inside `application` directory.
```/Sufier/application/make```

## Usage
Sufier can be launched only with integrated simple UI. In order to launch the program, the user must only launch binary executable after successful compilation.

### Contacts & Hash table
Contact inside `Sufier` are stored inside a hash table that consists of linked list. Hash key in this implementation is `contact_t` attribute - name. The user may:
- Add new contacts
- Delete existing contacts
- Edit current contact
    - This does not change given `contact_t` position inside hash table or linked list.
- Erase the entire hash table from contacts.
- Save or load current hash_table.

There can be only one hash table during program run-time. The user cannot change the capacity of max count of linked lists or linked lists contents. However it can be changed inside `limits.h`.

### Loading & Saving
Sufier can save or load your hash table inside a given file in `.csv` format. By default, tables are being saved inside: `../tables`. Loading table will firstly parse the file in order to count the ammount of `good` lines. They are later verified inside a separate function in order to check if they are written in a valid `contact_t` format.

## Bugs & Troubleshooting
If you encounter any bugs while using this software, please contact: janbielaw00@gmail.com.

## Thanks for choosing Sufier!