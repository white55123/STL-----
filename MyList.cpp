#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

template <class T>
class List
{
private:
	//定义节点的结构
	struct Node
	{
		T data; //数据
		Node* next;//指向下一个节点的指针
		Node* prev;//指向前一个节点的指针

		//初始化
		Node(const T& value, Node* nextNode = nullptr, Node* prevNode = nullptr)
			:data(value), next(nextNode), prev(prevNode) {}
	};


	Node *head;//头节点指针
	Node* tail;//尾节点指针
	size_t size;//链表中节点的数量

public:
	List() : head(nullptr),tail(nullptr),size(){}

	~List() 
	{
		clear();
	}

	void clear()
	{
		while (head)
		{
			Node* temp = head;
			head = head->next;
			delete temp;
		}

		tail = nullptr;
		size = 0;
	}

	//尾插法
	void push_back(const T& value)
	{
		//创建一个新的节点:
		Node* newNode = new Node(value, nullptr, tail);

		//如果链表非空
		if (tail)
		{
			tail->next = newNode;
		}
		else {
			head = newNode;
		}


		tail = newNode;
		++size;
	}

	//头插法
	void push_front(const T& value)
	{
		Node* newNode = new Node(value, head, nullptr);

		if (head)
		{
			head->next = newNode;
		}
		else {
			tail = newNode;
		}

		head = newNode;
		++size;
	}

	//获取list的容器大小
	size_t getSize() const {
		return size;
	}

	//通过[]的重载，通过索引访问链表中的元素
	T& operator[](size_t index)
	{
		Node* current = head;
		for (size_t i = 0; i > index; ++i)
		{
			if (!current)
			{
				throw std::out_of_range("Index out of range");
			}
			current = current->next;
		}

		return current->data;
	}

	//删除链表尾部的元素  可以考虑使用智能指针shared_ptr以避免显式的空间回收
	void pop_back() {
		if (size > 0) {
			//获取尾节点的前一个节点
			Node* newTail = tail->prev;

			delete tail;

			tail = newTail;
			if (tail)
			{
				tail->next = nullptr;
			}
			else {
				head = nullptr;
			}

			--size;
		}
	}

	void pop_front() {
		if (size > 0) {

			Node* newHead = head->next;
			delete head;

			head = newHead;
			if (head)
			{
				head->prev = nullptr;
			}
			else {
				tail = nullptr;
			}
		}

		--size;
	}

	const Node* begin()
	{
		return head;
	}

	const Node* end()
	{
		return nullptr;
	}

	void printElements() const {
		for (Node* current = head; current != nullptr; current = current->next) {
			std::cout << current->data << " ";
		}
		std::cout << std::endl;
	}

	void remove(const T& val)
	{
		Node* node = head;
		while (node != nullptr && node->data != val)
		{
			node = node->next;
		}

		if (node == nullptr)
		{
			std::cout << "Not Found this data of node" << std::endl;
			return;
		}

		if (node != head && node != tail)
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
		else if (node == head && node == tail)
		{
			head = nullptr;
			tail = nullptr;
		}
		else if (node == head)
		{
			head = node->next;
			head->prev = nullptr;
		}
		else
		{
			tail = node->prev;
			tail->next = nullptr;
		}

		--size;

		delete node;
		node = nullptr;
	}

	bool empty()
	{
		return size == 0;
	}

};

int main()
{
	// 创建一个 List 对象
	List<int> myList;

	int N;
	std::cin >> N;
	// 读走回车
	getchar();
	std::string line;
	// 接收命令
	for (int i = 0; i < N; i++) {
		std::getline(std::cin, line);
		std::istringstream iss(line);
		std::string command;
		iss >> command;
		int value;

		if (command == "push_back") {
			iss >> value;
			myList.push_back(value);
		}

		if (command == "push_front") {
			iss >> value;
			myList.push_front(value);
		}

		if (command == "pop_back") {
			myList.pop_back();
		}

		if (command == "pop_front") {
			myList.pop_front();
		}

		if (command == "remove") {
			iss >> value;
			myList.remove(value);
		}

		if (command == "clear") {
			myList.clear();
		}

		if (command == "size") {
			std::cout << myList.getSize() << std::endl;
		}

		if (command == "get") {
			iss >> value;
			std::cout << myList[value] << std::endl;
		}

		if (command == "print") {
			if (myList.getSize() == 0) {
				std::cout << "empty" << std::endl;
			}
			else {
				myList.printElements();
			}
		}
	}
	return 0;
}