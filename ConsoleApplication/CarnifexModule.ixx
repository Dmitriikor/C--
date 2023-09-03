export module CarnifexModule;
import <cassert>;


export template<typename T>
class Carnifex
{
private:
	struct Block
	{
		size_t counter_ = 0;
		T* object_;

		Block(T* pointer) : object_(pointer)
		{

		}

		~Block()
		{
			delete object_;
		}
	};

private:
public:
	Block* block_;

	void destruct()
	{
		assert(block_->counter_ != 0);

		--(block_->counter_);

		if (block_->counter_ == 0)
		{
			delete block_;
		}

		block_ = nullptr;
	}

public:

	Carnifex() : Carnifex(nullptr)
	{
	}

	explicit Carnifex(T* data) : block_(new Block(data))
	{
		++(block_->counter_);
	}

	Carnifex(const Carnifex& other) : block_(other.block_)
	{
		++(block_->counter_);
	}

	~Carnifex()
	{
		destruct();
	}

	Carnifex<T>& operator = (const Carnifex& other)
	{
		if (this != &other)
		{
			destruct();
			block_ = other.block_;

			++(block_->counter_);

		}
		return *this;
	}

	Carnifex<T> operator = (T* data)
	{
		destruct();

		block_ = new Block(data);
		++(block_->counter_);

		return *this;
	}

	T* operator->() const
	{
		return block_->object_;
	}

	T& operator*() const
	{
		return *(block_->object_);
	}

	bool operator==(const Carnifex<T>& other)
	{
		return this->block_ == other.block_;
	}
	bool operator==(const Carnifex<T>& const other) const
	{
		return this->block_ == other.block_;
	}
};