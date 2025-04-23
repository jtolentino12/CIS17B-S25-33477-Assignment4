#include <iostream>
#include <unordered_map>
#include <map>
#include <memory>
#include <stdexcept>

class DuplicateItemException : public std::runtime_error {
public:
    DuplicateItemException(const std::string& msg) : std::runtime_error(msg) {}
};

class ItemNotFoundException : public std::runtime_error {
public:
    ItemNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

class StoredItem {
private:
    std::string id;
    std::string description;
    std::string location;

public:
    StoredItem(std::string id, std::string desc, std::string loc)
        : id(id), description(desc), location(loc) {}

    std::string getId() const { return id; }
    std::string getDescription() const { return description; }
    std::string getLocation() const { return location; }
};

class StorageManager {
private:
    std::unordered_map<std::string, std::shared_ptr<StoredItem>> itemById;
    std::map<std::string, std::shared_ptr<StoredItem>> itemByDescription;

public:
    void addItem(const std::shared_ptr<StoredItem>& item) {
        // TODO: Add item to both maps, throw if ID already exists
        if (itemById.find(item->getId()) != itemById.end()) {
            throw DuplicateItemException("Item with ID " + item->getId() + " already exists.");
        }
        itemById[item->getId()] = item;
        itemByDescription[item->getDescription()] = item;
    }

    std::shared_ptr<StoredItem> findById(const std::string& id) const {
        // TODO: Return item if found or throw ItemNotFoundException
        auto it = itemById.find(id);
        if (it == itemById.end()) {
            throw ItemNotFoundException("Item with ID '" + id + "' not found.");
        }
        return it->second;
    }

    void removeItem(const std::string& id) {
        // TODO: Remove from both maps, throw if not found

    }

    void listItemsByDescription() const {
        // TODO: Iterate over itemByDescription and print info

    }
};

void testDuplicateAddition() {
    //
}

void testItemNotFound() {
    // 
}

int main() {
    // TODO: Create StorageManager and test functionality
}