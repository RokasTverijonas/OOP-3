#include <iostream>
#include <cstddef>
#include <iterator>

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
            newBlock[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = newBlock;
        capacity_ = newCapacity;

    }

public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;

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
        data_ = new value_type[capacity_];
        for(std::size_t i = 0; i < size_; i++)
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
    //List constructor
    Vector(std::initializer_list<value_type> init)
    {
        size_ = init.size();
        capacity_ = size_;
        data_ = new T[capacity_];

        std::size_t i = 0;
        for(const T& value : init) {
            data_[i] = value;
            i++;
        }
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

        T* newBlock = new value_type[other.capacity_];

        for(std::size_t i = 0; i < other.size_; i++)
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
    const_reference operator[](size_type index) const
    {
        return data_[index];
    }
    //galima keisti elementa
    reference operator[](size_type index)
    {
        return data_[index];
    }
    
    void resize(size_type newSize)
    {
        if(newSize > capacity_)
        {
            ReAlloc(newSize);
        }
        for(std::size_t i = size_; i < newSize; i++)
        {
            data_[i] = T{};
        }
        
        size_ = newSize;
    }

    void assign(size_type count, const_reference value)
    {
        delete[] data_;
        data_ = new value_type[count];

        for(std::size_t i = 0; i < count; i++)
        {
            data_[i] = value;
        }
        size_ = count;
        capacity_ = count;
    }
    

    void push_back(const_reference value)
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

    void pop_back()
    {
        if(size_ > 0)
        {
            --size_;
        }
    }

    void shrink_to_fit()
    {
        if(capacity_ > size_)
        {
            ReAlloc(size_);
        }
    }

    void clear()
    {
        size_ = 0;
        capacity_ = 0;
        delete[] data_;
        data_ = nullptr;
    }

    iterator insert(const_iterator pos, const_reference value)
    {
        std::size_t index = pos - begin();

        if(size_ >= capacity_)
        {
            ReAlloc(capacity_ == 0 ? 2 : capacity_ * 2);
        }
        for(std::size_t i = size_; i > index; --i)
        {
            data_[i] = data_[i - 1];
        }

        data_[index] = value;
        size_++;

        return begin() + index;
    }

    iterator erase(const_iterator pos)
    {
        size_type index = pos - begin();

        for(std::size_t i = index; i < size_ - 1; i++)
        {
            data_[i] = data_[i + 1];
        }
        --size_;

        return begin() + index;
    }

    void swap(Vector& other)
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }


    
    //grazina rodykle i masyva
    pointer data() { return data_; }
    const_pointer data() const { return data_; }

    //grazina elementa is duotos pozicijos
    reference at(size_type index) 
    {
        if(index >= size_)
        {
            throw std::out_of_range("Indeksas už vektoriaus ribų!");
        }
        return data_[index];
    }
    //negalima keisti reiksmiu
    const_reference at(size_type index) const
    {
        if(index >= size_)
        {
            throw std::out_of_range("Indeksas už vektoriaus ribų!");
        }
        return data_[index];
    }
    //pirmas elementas
    reference front() { return data_[0]; }
    const_reference front() const { return data_[0]; }

    //paskutinis elementas
    reference back() { return data_[size_ - 1]; }
    const_reference back() const { return data_[size_ -1]; }

    //ar tuscias
    bool empty() const { return size_ == 0; }

    //grazina elemnentu kieki
    size_type size() const { return size_; }

    //grazina talpa
    size_type capacity() const { return capacity_; }

    //rezervuoja vieta
    void reserve(size_type new_cap)
    {
        if(new_cap > capacity_)
        {
            ReAlloc(new_cap);
        }
    }

    //iteratoriai:
    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }

    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }

    //kai tikrai norime tik skaityti
    const_iterator cbegin() const noexcept { return data_; }
    const_iterator cend() const noexcept { return data_ + size_; }

};

    //non-member functions
    template<typename T>
    bool operator==(const Vector<T>& lhs, const Vector<T>& rhs)
    {
        if(lhs.size() != rhs.size())
        {
            return false;
        }
        for(std::size_t i = 0; i < lhs.size(); i++)
        {
            if(lhs.at(i) != rhs.at(i))
            {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs)
    {
        if(lhs.size() != rhs.size())
        {
            return true;
        }
        for(std::size_t i = 0; i < lhs.size(); i++)
        {
            if(lhs.at(i) != rhs.at(i))
            {
                return true;
            }
        }
        return false;
    }