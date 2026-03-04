# 📝 C Command-Line To-Do Application

A dynamic command-line To-Do list application written in pure C.

This project demonstrates practical systems programming concepts including:

* Dynamic memory allocation (`malloc`, `realloc`, `free`)
* Struct composition
* Manual memory ownership
* File persistence
* Vector-style resizing strategy
* Basic command-line interface design

---

## 🚀 Features

* Add tasks
* Delete tasks
* Mark tasks as complete
* Persistent storage (saved to file)
* Dynamic resizing (no fixed-size arrays)

---

## 🧠 Technical Overview

The application uses a custom dynamic array implementation similar to a simplified `std::vector` in C++.

### Data Structures

```c
typedef struct {
    char *description;
    int completed;
} Task;

typedef struct {
    Task *tasks;
    int size;
    int capacity;
} TodoList;
```

### Memory Strategy

* Initial capacity is allocated on startup.
* When the array is full, capacity is doubled using `realloc`.
* Each task description is individually heap-allocated.
* All memory is explicitly freed before program termination.

This ensures:

* No static buffers
* No arbitrary limits
* Proper memory ownership

---

## 📁 File Storage

Tasks are stored in:

```
tasks.txt
```

Format per line:

```
<completed_flag>|<task_description>
```

Example:

```
0|Learn C pointers
1|Build that useless application
```

---

## 🛠 Compilation

### Linux / macOS

```bash
gcc -Wall -Wextra -o todo todo.c
./todo
```

### Windows (MinGW)

```bash
gcc -Wall -Wextra -o todo.exe todo.c
todo.exe
```

---

## 📋 Usage

```
1. Add Task
2. Delete Task
3. Mark Complete
4. Show Tasks
5. Exit
```

Tasks persist automatically when exiting the program.

---

## 🧪 Concepts Practiced

* Heap allocation and resizing
* Pointer manipulation
* File I/O parsing
* Struct-based design
* Manual memory lifecycle management
* Defensive error handling

---

## 📈 Possible Improvements

* Shrinking capacity when many tasks are deleted
* Sorting (by completion status or alphabetically)
* Task priorities
* Due dates
* Timestamps
* Multi-file modularization (.c/.h separation)
* Unit testing framework integration
* Ncurses-based terminal UI
* Thread-safe implementation

---

## 📜 License

MIT License

---
