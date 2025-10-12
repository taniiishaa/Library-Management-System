# 📚 C++ Library Management System (LMS)

A complete console-based application built with **C++** and **Object-Oriented Programming (OOP)** principles. This system is designed to manage the core operations of a small library, demonstrating strong concepts in data modeling, persistent storage, and command-line interface design.

## 🌟 Project Highlights & Technical Focus

This project serves as a strong portfolio piece, showcasing competency in the following areas:

| Feature | C++ Concept Demonstrated |
| :--- | :--- |
| **Data Persistence** | Implements **Binary File Handling (`fstream`)** to permanently save and load `Book` records, ensuring data integrity across sessions. |
| **Object-Oriented Design**| Utilizes a robust `Book` class with **Encapsulation** (private members), clear accessors, and mutator methods. |
| **Core Functionality** | Full implementation of **CRUD** (Create, Read, Update, Delete - *conceptually via Issue/Return*) operations. |
| **User Interface** | Menu-driven console interface for easy navigation and distinct user roles (Admin vs. Public Viewer). |
| **Efficient Updates** | Uses C++ stream manipulation (`seekg` and `seekp`) to efficiently modify records (Issue/Return status) directly within the binary file. |

---

## 💻 How to Build and Run the Project

### Prerequisites

You need a C++ compiler that supports the C++11 standard or later (e.g., GCC, g++, Clang, or MSVC).

### Compilation

1.  Navigate to the project directory in your terminal.
2.  Compile the single source file using `g++`:

    ```bash
    g++ LMS.cpp -o LMS
    ```

### Execution

Run the compiled executable from the same directory:

| Operating System | Command |
| :--- | :--- |
| **Windows Command Prompt** | `LMS` or `.\LMS` |
| **Linux/macOS (Bash/Zsh)** | `./LMS` |

---

## 🔑 Admin Credentials

To access the full suite of management features, use the following default credentials:

| Role | Password |
| :--- | :--- |
| **Admin** | `admin123` |

---

## ✨ Features

The system offers a primary menu with two distinct access points:

### 1. Administrator Menu (Password Protected)

* **Add New Book:** Create and save a new book record (ID, Title, Author) to the data file.
* **Display All Books:** View the complete inventory, including the current Issue/Available status.
* **Issue Book:** Mark a book as `Issued` based on its Book ID, updating the record in the binary file.
* **Return Book:** Mark an `Issued` book as `Available`, updating the record in the binary file.

### 2. Student/User View (Public Access)

* **Browse Books:** Allows any user to view the full list of available and issued books without requiring a password.
