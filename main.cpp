//  for running this in terminal - clang++ -std=c++17 main.cpp -o task_tracker
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <filesystem>
#include "json.hpp"


using json = nlohmann::json;
namespace fs = std::filesystem;

const std::string FILE_NAME = "tasks.json";

struct Task {
    int id;
    std::string description;
    std::string status; // todo, in-progress, done
    std::string createdAt;
    std::string updatedAt;
};

std::string currentTime() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buf);
}

std::vector<Task> loadTasks() {
    std::vector<Task> tasks;
    if (fs::exists(FILE_NAME)) {
        std::ifstream file(FILE_NAME);
        json j;
        file >> j;
        for (auto& item : j) {
            tasks.push_back({
                item["id"],
                item["description"],
                item["status"],
                item["createdAt"],
                item["updatedAt"]
            });
        }
    }
    return tasks;
}

void saveTasks(const std::vector<Task>& tasks) {
    json j;
    for (const auto& task : tasks) {
        j.push_back({
            {"id", task.id},
            {"description", task.description},
            {"status", task.status},
            {"createdAt", task.createdAt},
            {"updatedAt", task.updatedAt}
        });
    }
    std::ofstream file(FILE_NAME);
    file << j.dump(4);
}

int getNextId(const std::vector<Task>& tasks) {
    int maxId = 0;
    for (const auto& task : tasks) {
        if (task.id > maxId) maxId = task.id;
    }
    return maxId + 1;
}

void addTask(const std::string& desc) {
    auto tasks = loadTasks();
    int id = getNextId(tasks);
    std::string now = currentTime();
    tasks.push_back({id, desc, "todo", now, now});
    saveTasks(tasks);
    std::cout << "Task added successfully (ID: " << id << ")\n";
}

void updateTask(int id, const std::string& newDesc) {
    auto tasks = loadTasks();
    for (auto& task : tasks) {
        if (task.id == id) {
            task.description = newDesc;
            task.updatedAt = currentTime();
            saveTasks(tasks);
            std::cout << "Task updated successfully\n";
            return;
        }
    }
    std::cout << "Task not found\n";
}

void deleteTask(int id) {
    auto tasks = loadTasks();
    auto it = std::remove_if(tasks.begin(), tasks.end(), [&](const Task& t){ return t.id == id; });
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        saveTasks(tasks);
        std::cout << "Task deleted successfully\n";
    } else {
        std::cout << "Task not found\n";
    }
}

void markStatus(int id, const std::string& status) {
    auto tasks = loadTasks();
    for (auto& task : tasks) {
        if (task.id == id) {
            task.status = status;
            task.updatedAt = currentTime();
            saveTasks(tasks);
            std::cout << "Task marked as " << status << "\n";
            return;
        }
    }
    std::cout << "Task not found\n";
}

void listTasks(const std::string& filter = "") {
    auto tasks = loadTasks();
    for (const auto& task : tasks) {
        if (filter.empty() || task.status == filter) {
            std::cout << "[" << task.id << "] " << task.description << " (" << task.status << ")\n";
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: task-cli <command> [arguments...]\n";
        return 1;
    }
    std::string command = argv[1];

    if (command == "add" && argc >= 3) {
        addTask(argv[2]);
    } else if (command == "update" && argc >= 4) {
        updateTask(std::stoi(argv[2]), argv[3]);
    } else if (command == "delete" && argc >= 3) {
        deleteTask(std::stoi(argv[2]));
    } else if (command == "mark-in-progress" && argc >= 3) {
        markStatus(std::stoi(argv[2]), "in-progress");
    } else if (command == "mark-done" && argc >= 3) {
        markStatus(std::stoi(argv[2]), "done");
    } else if (command == "list") {
        if (argc == 3) listTasks(argv[2]);
        else listTasks();
    } else {
        std::cerr << "Invalid command or arguments\n";
        return 1;
    }
    return 0;
}
