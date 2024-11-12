#pragma once

#include <exception>

class IndexOutOfRange : public std::exception
{
    public:
        IndexOutOfRange(const char* msg) : std::exception(){
            this->msg = msg;
        }
        const char* what() const noexcept override{
            return msg;
        }
    private:
        const char* msg;
};

template <class T> class DynamicArray
{
    private:
        UnqPtr<T> data;     // Элементы (ссылка на первый)
        int size;           // Количество элементов
        int capacity;       // Количество зарезервированных ячеек памяти
    
    public:
    //конструкторы

        DynamicArray(int const & count) :   
            size(count), 
            capacity(count*2), 
            data(UnqPtr(nullptr, capacity)) 
        { }

        DynamicArray(T* const & items, int const & count) : 
            size(count), 
            capacity(count*2), 
            data(UnqPtr(items, capacity))
        { }

        DynamicArray(DynamicArray const & dynamicArray) : 
            size(dynamicArray.size), 
            capacity(dynamicArray.capacity), 
            data(UnqPtr(nullptr, capacity))
        {
            for (int i = 0; i < size; i++)
                data[i] = dynamicArray.data[i];
        }

        DynamicArray(): 
            size(0), 
            capacity(0), 
            data(UnqPtr())            
        { }
        
    //декомпозиция

        DynamicArray<T> GetSubsequence(size_t const & startIndex, size_t const & endIndex) const
        {
            if (startIndex < 0)
                throw IndexOutOfRange("Function 'GetSubsequence': Negative startIndex.");
            if (startIndex > endIndex)
                throw IndexOutOfRange("Function 'GetSubsequence': startIndex is greater than endIndex.");
            if (endIndex >= this->GetSize())
                throw IndexOutOfRange("Function 'GetSubsequence': endIndex is equal or greater than size.");
            
            return DynamicArray<T>(data.ptr + startIndex, endIndex - startIndex + 1);
        }

        int GetSize() const       //Получить size 
        {
            return size;
        }

    //операции

        void Resize(int newSize)        
        {
            if (newSize < 0)
                throw IndexOutOfRange("Function 'Resize': Negative size.");
            if (capacity >= newSize && newSize >= this->capacity/4)
                this->size = newSize;
            else
            {
                size = newSize;
                capacity = newSize*2;
                data = UnqPtr(data.ptr, newSize * 2);
            }
        }

        void Insert(size_t index, T item)
        {
            if (index < 0) 
                throw IndexOutOfRange("Function 'InsertAt': Negative index.");
            if (index > size) 
                throw IndexOutOfRange("Function 'InsertAt': Index is greater than size.");
            if (this->capacity > this->size)
            {
                T temp;
                this->size += 1;
                for (int i = this->size - 1; i > index; i -= 1)
                {
                    *(data + i) = *(data + i - 1);
                }
                *(data + index) = item;
            }
            else
            {
                this->size += 1;
                this->capacity = 2 * this->size;
                T* data_temp = new T [this->capacity];
                for (int i = 0; i < index; i++)
                {
                    *(data_temp + i) = *(this->data + i);
                }
                *(data_temp + index) = item;
                for (int i = index + 1; i < this->size; i++)
                {
                    *(data_temp + i) = *(this->data + i - 1);
                }
                delete[] this->data;
                this->data = data_temp;                
            }   
        }

        void Append(T item)
        {
            this->Insert(this->size, item);
        }

        void Prepend(T item)
        {
            this->Insert(0, item);
        }

        DynamicArray<T>* Concat(DynamicArray<T> & array)
        {
            DynamicArray<T> * output = new DynamicArray<T>(*this);
            (*output).Resize(this->GetSize() + array.GetSize());
            for (int i = this->GetSize(); i < output->GetSize(); i++)
            {
                (*output).Set(i, array.Get(i-this->GetSize()));
            }
            return output; 
        }
    
    // перегрузка операторов
        T & operator[] (size_t index) { 
            if (index < 0) 
                throw IndexOutOfRange("Operator '[]': Negative index.");
            if (index >= size) 
                throw IndexOutOfRange("Operator '[]': Index is greater than size.");
            return data[index];    
        }

        T const & operator[] (size_t index) const { 
            if (index < 0) 
                throw IndexOutOfRange("Const operator '[]': Negative index.");
            if (index >= size) 
                throw IndexOutOfRange("Const operator '[]': Index is greater than size.");
            return data[index];    
        }
};