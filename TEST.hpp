#pragma once


template<typename T>
class __TESTS__
{
private:
    T data;
public:
    explicit __TESTS__(T data) : data(data) {}  
    ~__TESTS__() = default;
    
};


template<typename T>
class carnifex
{
    public: //private:
        T* object_;
        size_t* counter_;
        void destruct()
        {
            if (object_ == nullptr)
                return;

            --(*counter_);

            if (*counter_ == 0)
            {
                delete object_;
            }
            object_ = nullptr;
            counter_ = nullptr;
        }

    public:

        carnifex() 
        {
            object_ = nullptr;
            counter_= new size_t(0);
        }

        explicit carnifex (T* data) : object_(data), counter_(new size_t(0))
        {
            ++(*counter_);
        }

        carnifex (const carnifex& other) : object_(other.object_), counter_(other.counter_) 
        {
            ++(*counter_);
        }

        ~carnifex()
        {
           destruct();
        }

        carnifex<T>& operator = (const carnifex& other)
       {
            if (this != &other) 
                {
                    destruct();
                    object_ = other.object_;
                    counter_ = other.counter_;

                    //++(*counter_);
                    
                }
            return *this;
       }
       carnifex<T> operator = (T* data)
       {
           if (*counter_ == 0)
           {
               object_ = data;
               ++(*counter_);
               return *this;
           }
           object_ = nullptr;
           delete object_;

           *counter_ = 0;

           object_ = data;
           ++(*counter_);

           return *this;
       }

        T* operator->() const 
        {
            return object_;
        }

        T& operator*() const 
        {
            return *object_;
        }
};