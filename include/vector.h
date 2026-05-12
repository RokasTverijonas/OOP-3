
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
    
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    //numatytasis konstruktorius
    Vector() = default;
    //copy constructor
    Vector(const Vector& other)
        :size_(other.size_),
        capacity_(other.capacity_)
    {
        data_ = new T[capacity_];
        for(size_t i = 0; i < size_; i++)
        {
            data_[i] = other.data_[i];
        }
    }
    //move constructor
    Vector(Vector&& other) noexcept
        :data_(other.data_),
        size_(other.size_),
        capacity_(other.capacity_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
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
    //move assignment operator
    Vector& operator=(Vector&& other) noexcept
    {
        if(this == &other) return *this;
        size_ = other.size_;
        capacity_ = other.capacity_;
        delete[] data_;
        data_ = other.data_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

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
    
    void resize(size_t newSize)
    {
        if(newSize > capacity_)
        {
            ReAlloc(newSize);
        }
        for(size_t i = size_; i < newSize; i++)
        {
            data_[i] = T{};
        }
        
        size_ = newSize;
    }

    void assign(size_t count, const T& value)
    {
        delete[] data_;
        data_ = new T[count];

        for(size_t i = 0; i < count; i++)
        {
            data_[i] = value;
        }
        size_ = count;
        capacity_ = count;
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
    //GRAZINAMOS REIKSMES

    //grazina elemnentu kieki
    size_t size() const { return size_; }
    //grazina talpa
    size_t capacity() const { return capacity_; }

    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }

    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }

    //kai tikrai norime tik skaityti
    const_iterator cbegin() const noexcept { return data_; }
    const_iterator cend() const noexcept { return data_ + size_; }




};