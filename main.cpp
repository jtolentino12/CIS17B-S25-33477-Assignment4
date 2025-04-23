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
        if (itemById.find(item->getId()) != itemById.end()) { // not found
            throw DuplicateItemException("Item with ID " + item->getId() + " already exists.");
        }
        // add
        itemById[item->getId()] = item; 
        itemByDescription[item->getDescription()] = item;
    }

    std::shared_ptr<StoredItem> findById(const std::string& id) const {
        // TODO: Return item if found or throw ItemNotFoundException
        auto it = itemById.find(id);
        if (it == itemById.end()) { // not found
            throw ItemNotFoundException("Item with ID " + id + " not found.");
        }
        // found
        return it->second; 
    }

    void removeItem(const std::string& id) {
        // TODO: Remove from both maps, throw if not found
        auto it = itemById.find(id);
        if (it == itemById.end()) { // not found
            throw ItemNotFoundException("Cannot remove. Item with ID " + id + " not found.");
        }
        // remove
        itemByDescription.erase(it->second->getDescription());
        itemById.erase(it);
    }

    void listItemsByDescription() const {
        // TODO: Iterate over itemByDescription and print info
        for (const auto& pair : itemByDescription) {
            const auto& item = pair.second;
            std::cout << "ID: " << item->getId()
                      << ", Description: " << item->getDescription()
                      << ", Location: " << item->getLocation() << "\n";
        }
    }
};

void testDuplicateAddition() { // tests adding duplicate item
    StorageManager sm;
    auto item = std::make_shared<StoredItem>("ITEM001", "LED Light", "Aisle 1, Shelf 1");
    sm.addItem(item);
    try {
        sm.addItem(item);
    } catch (const DuplicateItemException& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void testItemNotFound() { // tests invalid itemid
    StorageManager sm;
    try {
        sm.findById("ITEM003");
    } catch (const ItemNotFoundException& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

int main() {
    // TODO: Create StorageManager and test functionality
    StorageManager manager;
    // create
    auto item1 = std::make_shared<StoredItem>("ITEM001", "LED Light", "Aisle 3, Shelf 1");
    auto item2 = std::make_shared<StoredItem>("ITEM002", "Fan Motor", "Aisle 2, Shelf 5");
    // add items
    std::cout << "Adding item: ITEM001 - LED Light" << std::endl;
    manager.addItem(item1);
    std::cout << "Adding item: ITEM002 - Fan Motor" << std::endl;
    manager.addItem(item2);
    std::cout << "Attempting to add IteM001 again..." << std::endl;
    testDuplicateAddition(); // helper function
    std::cout << "Retrieving ITEM002..." << std::endl;
    try {
        auto found = manager.findById("ITEM002");
        std::cout << "Found: " << found->getDescription()
                  << " at " << found->getLocation() << "\n";
    } catch (const ItemNotFoundException& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    std::cout << "Removing ITEM003..." << std::endl;
    testItemNotFound(); // helper function
    std::cout << "Items in Description Order:" << std::endl;
    manager.listItemsByDescription();

    return 0;

}