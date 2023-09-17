export module Node;
import CarnifexModule;

export template <typename T>
struct Node
{
	T data;

	Carnifex<Node<T>> next = nullptr;

	explicit Node(const T& value) : data(value)
	{
	}
	~Node() = default;
};