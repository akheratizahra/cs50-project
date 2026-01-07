# TODO List Application

## Demo
**Video demo:** <URL>

## Overview
This is a simple command-line TODO list application written in C. The application features a colorful terminal interface, persistent storage using JSON, and efficient data management through a doubly linked list structure.

### Key Highlights
- **Colorful terminal UI** with ANSI color codes and emoji
- **Persistent storage** using JSON format (cJSON library)
- **Doubly linked list** for efficient task operations
- **Flexible file management** with custom filenames or defaults
- **Complete CRUD operations** for task management
- **Input validation** and error handling

## Technology Stack

| Component | Technology | Rationale |
|-----------|-----------|-----------|
| **Language** | C | Performance, low-level control, educational value |
| **Data Structure** | Doubly Linked List | O(1) insertion/deletion at ends, bidirectional traversal |
| **Serialization** | JSON (cJSON) | Human-readable, widely supported, easy to debug |
| **Build System** | GCC | Standard C compiler with comprehensive warnings |

### Why Doubly Linked List?

- **Efficient insertion/deletion**: O(1) at both ends
- **Bidirectional traversal**: Navigate forward and backward
- **Dynamic memory**: Grows/shrinks as needed
- **No fixed size limit**: Unlike arrays

## Features

### Implemented

- [x] Add new tasks with custom names
- [x] View all tasks with colorful formatting (Green ✓ for done, Red ○ for pending)
- [x] Mark tasks as completed
- [x] Delete tasks by number
- [x] Save tasks to custom or default JSON file
- [x] Load tasks from custom or default JSON file
- [x] Auto-save prompt on exit
- [x] Input validation for menu options
- [x] Default filename support (press Enter for `todo.json`)

### Future Enhancements

- [ ] Task priorities (high, medium, low)
- [ ] Due dates and reminders
- [ ] Task categories/tags
- [ ] Search and filter functionality
- [ ] Task editing capabilities
- [ ] Statistics (completion rate, total tasks)

## Getting Started

### Prerequisites

- GCC compiler
- Standard C library
- Terminal with ANSI color support

### Build Instructions

**Compile the program:**

```bash
gcc -Wall -Wextra -g3 todo.c utils/cJSON.c -o todo
```

**Compiler flags explained:**

- `-Wall`: Enable all warnings
- `-Wextra`: Enable extra warnings
- `-g3`: Include debugging information
- `-o todo`: Output executable named `todo`

**Run the application:**

```bash
./todo
```

## Usage Guide

### Main Menu Operations

1. **Show todo list** - View all tasks with colorful status indicators (✓ Green for done, ○ Red for pending)
2. **Add new item** - Enter task name (up to 19 characters)
3. **Remove item** - View tasks and enter number to delete
4. **Mark as done** - View tasks and enter number to mark complete
5. **Save to file** - Enter custom filename or press Enter for `todo.json`
6. **Load from file** - Enter filename or press Enter for default
0. **Exit** - Optionally save before quitting

## Project Structure

```
todo/
├── todo.c           # Main implementation
├── todo.h           # Header file with declarations
├── todo             # Compiled executable
├── utils/
│   ├── cJSON.c      # JSON parser implementation
│   └── cJSON.h      # JSON parser header
├── todo.json        # Default save file (created on save)
└── README.md        # Documentation
```

## Color Scheme

The application uses ANSI color codes for a vibrant terminal experience:

- **Cyan borders** and title with 📝 emoji
- **Green ✓** for completed tasks
- **Red ○** for pending tasks
- **Color-coded status badges** [DONE] / [TODO]

## File Format

Tasks are saved in JSON format:

```json
[
  {
    "name": "Buy groceries",
    "is_done": false
  },
  {
    "name": "Write README",
    "is_done": true
  }
]
```

## Example Session

```
Todo List Menu
1. Show todo list
2. Add the new item to todo list
3. Remove an item from todo list
4. Done an item from todo list
5. Save todo list to file
6. Load todo list from file
0. Exit
Enter your choice: 2
Enter the name of the new task: buy bread

Todo List Menu
1. Show todo list
2. Add the new item to todo list
3. Remove an item from todo list
4. Done an item from todo list
5. Save todo list to file
6. Load todo list from file
0. Exit
Enter your choice: 2
Enter the name of the new task: walking

Todo List Menu
1. Show todo list
2. Add the new item to todo list
3. Remove an item from todo list
4. Done an item from todo list
5. Save todo list to file
6. Load todo list from file
0. Exit
Enter your choice: 1

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           📝 TODO LIST 📝
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
○ 1. buy bread [TODO]
○ 2. walking [TODO]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Todo List Menu
1. Show todo list
2. Add the new item to todo list
3. Remove an item from todo list
4. Done an item from todo list
5. Save todo list to file
6. Load todo list from file
0. Exit
Enter your choice: 5
Enter filename or press Enter for default (todo.json):
Saving tasks to file: todo.json

Todo List Menu
1. Show todo list
2. Add the new item to todo list
3. Remove an item from todo list
4. Done an item from todo list
5. Save todo list to file
6. Load todo list from file
0. Exit
Enter your choice: 0
Do you want to save your todo list before exiting? (y/n): n
Exit
➜  todo ./todo

Todo List Menu
1. Show todo list
2. Add the new item to todo list
3. Remove an item from todo list
4. Done an item from todo list
5. Save todo list to file
6. Load todo list from file
0. Exit
Enter your choice: 6
Enter filename or press Enter for default (todo.json):
Loading tasks from file: todo.json

Todo List Menu
1. Show todo list
2. Add the new item to todo list
3. Remove an item from todo list
4. Done an item from todo list
5. Save todo list to file
6. Load todo list from file
0. Exit
Enter your choice: 4

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           📝 TODO LIST 📝
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
○ 1. buy bread [TODO]
○ 2. walking [TODO]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Enter the number of the task to mark as done: 1
Task 'buy bread' marked as done.

Todo List Menu
1. Show todo list
2. Add the new item to todo list
3. Remove an item from todo list
4. Done an item from todo list
5. Save todo list to file
6. Load todo list from file
0. Exit
Enter your choice: 1

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           📝 TODO LIST 📝
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✓ 1. buy bread [DONE]
○ 2. walking [TODO]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Todo List Menu
1. Show todo list
2. Add the new item to todo list
3. Remove an item from todo list
4. Done an item from todo list
5. Save todo list to file
6. Load todo list from file
0. Exit
Enter your choice: 0
Do you want to save your todo list before exiting? (y/n): y
Enter filename or press Enter for default (todo.json):
Saving tasks to file: todo.json
Exit
```
