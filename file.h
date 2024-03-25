#pragma once

#include <string>
#include <cstdint>

enum ItemType {
	File,
	Directory,
	Symlink
};

class BaseItem {
private:
	std::string name;
	ItemType type;
public:
	BaseItem(std::string name, ItemType type)
		: name(name), type(type) {};
	~BaseItem() = default;
};

class File : BaseItem {
private:
	char *content;
	uint64_t size;
public:
	File(std::string name, char* content, uint64_t size) : BaseItem(name, ItemType::File) {
		this->content = content;
		this->size = size;
	}
};

class Symlink : BaseItem {
private:
	std::string address;
public:
	Symlink
};