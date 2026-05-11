
template<typename T>
class Vector
{
private:
        T* data_ = nullptr;
        size_t size_ = 0;
        size_t capacity_ = 0;

public:
    Vector()
    {
        // allocate 2 elements
        ReAlloc(2);
    }

    void ReAlloc(size_t newCapacity)
    {
        //allocate a new block of memory
        //Copy/move ols elemenets ono new block
        //delete

        T* newBlock = new T[newCapacity];
        
        if(newCapacity < size_)
        {
            size_ = newCapacity;
        }

        for(size_t i = 0; i < size_; i++)
        {
            newBlock[i] = data_[i];
        }
        delete[] data_;
        data_ = newBlock;
        capacity_ = newCapacity;

    }

    void PushBack(const T& value)
    {
        
        if(size_ >= capacity_)
        {
            //jei capacity 0, priskiriam 2, jei ne tada padvigubinam capacity
            ReAlloc(capacity == 0 ? 2 : capacity_ * 2);
        }
        //i tuscia vieta priskiriam elementa
        data_[size_] = value;
        size_++;
    }

    size_t Size() const { return size_; }


};