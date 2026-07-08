# Inverted-Search-Using--C
A C-based Inverted Search implementation using hash tables and linked lists to efficiently index, search, update, display, and save words across multiple text files.
# Inverted Search Using C

An efficient **Inverted Search** implementation in C that indexes words from multiple text files using **hash tables** and **linked lists**. The project enables fast word searching by storing each unique word along with the list of files in which it appears and its occurrence count.

---

## Overview

Inverted Search is a fundamental data structure used in search engines to quickly locate documents containing a specific word. Instead of scanning every file during each search, the project builds an **inverted index** that maps each word to the files where it occurs.

This implementation supports creating an index, searching words, displaying the database, updating from backup files, and saving the index for future use.

---

## Features

- Create an inverted index from multiple text files
- Fast word searching
- Display indexed database
- Save database to a backup file
- Update database from an existing backup
- Handles duplicate words efficiently
- Stores word frequency for each file
- Hash table-based indexing
- Linked list implementation
- Command-line interface

---

## 🛠 Technologies Used

- C Programming
- Data Structures
- Hash Tables
- Linked Lists
- File Handling
- GCC Compiler
- Linux / Ubuntu

---

## Working

1. Read multiple text files.
2. Validate input files.
3. Create an inverted index using a hash table.
4. Store each unique word with:
   - File name
   - Frequency count
5. Search any word instantly.
6. Display the complete database.
7. Save the database to a backup file.
8. Reload the database from the backup when required.

---

## Functionalities

- Create Database
- Display Database
- Search Word
- Save Database
- Update Database
- File Validation

---

## Concepts Used

- Hash Tables
- Linked Lists
- File Handling
- Dynamic Memory Allocation
- String Manipulation
- Searching Algorithms
- Modular Programming

---


## Learning Outcomes

- Hash table implementation
- Linked list manipulation
- File processing in C
- Efficient text searching
- Dynamic memory management
- Modular programming
- Search engine indexing concepts

---

## Future Enhancements

- Case-insensitive searching
- Phrase search support
- Wildcard search
- Delete indexed files
- Ranking search results
- Support for large datasets
- Graphical User Interface (GUI)

---
