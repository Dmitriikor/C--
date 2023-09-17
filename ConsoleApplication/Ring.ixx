export module Ring;

import <iostream>;
import <cassert>;
import <stack>;
import <vector>;

import CarnifexModule;
import Node;


export template <typename T>
class Ring
{
private:
	Carnifex<Node<T>> tail_ = nullptr;

public:
	void push_back(const T& value)
	{
		if (tail_ == nullptr)
		{
			Carnifex<Node<T>> current(new(std::nothrow) Node<T>(value));
			tail_ = current;
			tail_->next = tail_;
			return;
		}

		Carnifex<Node<T>> current(new(std::nothrow) Node<T>(value));
		tail_ = current;
		tail_->next = tail_;
	}


};