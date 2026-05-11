
template<typename T>
class Vector
{
private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

    void ReAlloc(size_t newCapacity)
    {

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

public:
    //numatytasis konstruktorius
    Vector() = default;
    //destruktorius
    ~Vector() 
    {
        delete[] data_;
    }

    //OPERATORS
    //copy assignment operator
    Vector& operator=(const Vector& other)
    {
        if(this == &other)
        {
            return *this;
        }

        T* newBlock = new T[other.capacity_];

        for(size_t i = 0; i < other.size_; i++)
        {
            newBlock[i] = other.data_[i];
        }

        delete[] data_;
        data_ = newBlock;
        size_ = other.size_;
        capacity_ = other.capacity_;

        return *this;
    }

    //negalima keisti elemento
    const T& operator[](size_t index) const
    {
        return data_[index];
    }
    //galima keisti elementa
    T& operator[](size_t index)
    {
        return data_[index];
    }
    

    void push_back(const T& value)
    {
        
        if(size_ >= capacity_)
        {
            //jei capacity 0, priskiriam 2, jei ne tada padvigubinam capacity
            ReAlloc(capacity_ == 0 ? 2 : capacity_ * 2);
        }
        //i tuscia vieta priskiriam elementa
        data_[size_] = value;
        size_++;
    }

    //grazina elemnentu kieki
    size_t size() const { return size_; }
    //grazina talpa
    size_t capacity() const { return capacity_; }

};