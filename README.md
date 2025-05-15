# 📝 Task Tracker CLI (C++)

A simple **Command Line Interface (CLI)** application written in **C++** to help you track and manage your tasks. This project is great for practicing core programming skills such as file handling, working with JSON, user input via command-line arguments, and building CLI tools — all without using any external libraries or frameworks.

---

## 🚀 Features

- ➕ Add, ✏️ update, and 🗑️ delete tasks
- 🔁 Mark tasks as `todo`, `in-progress`, or `done`
- 📋 List all tasks or filter by status
- 💾 Tasks are saved in a JSON file (`task_tracker.json`)
- 📂 Uses C++17 filesystem and native JSON header (`json.hpp`)

---

## 🛠️ Requirements

- C++17 or later
- `json.hpp` header file (from [nlohmann/json](https://github.com/nlohmann/json))
- Terminal or command line

---

## ⚙️ How to Compile

```bash
g++ -std=c++17 -o task_tracker newindex.cpp
```

Make sure `json.hpp` is in the same directory as your source file.

---

## 🔧 Command Usage

```bash
# Add a new task
./task_tracker add "Buy groceries"

# Update an existing task
./task_tracker update 1 "Buy groceries and cook dinner"

# Delete a task
./task_tracker delete 1

# Mark task as in progress
./task_tracker mark-in-progress 1

# Mark task as done
./task_tracker mark-done 1

# List all tasks
./task_tracker list

# List tasks by status
./task_tracker list todo
./task_tracker list in-progress
./task_tracker list done
```

---

## 📁 Project Files

```
.
├── newindex.cpp        # Main source file
├── json.hpp            # JSON library header (nlohmann)
├── task_tracker        # Compiled binary
└── task_tracker.json   # JSON file storing your tasks
```

---

## ⚠️ Notes

- JSON file (`task_tracker.json`) is auto-created on first use.
- Input validation and error handling included.
- All functionality is done using standard C++ — no external libraries required.

---

## 📌 Future Ideas

- [ ] Add support for task deadlines or priority
- [ ] Add interactive CLI (menu-based)
- [ ] Add `export` option to CSV
- [ ] Integrate colored CLI output for readability

---

## 👨‍💻 Author

Made with ❤️ in C++ by [Your Name]  
Feel free to fork, use, and improve it!
