#pragma once

#include <exception>
#include "SmartPointers.h"

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

    //деструктор

        ~DynamicArray()
        {
            delete[] data; 
        }
        
    //декомпозиция

        T GetFirst()        //Получить первый элемент
        {
            return Get(0);
        }

        T GetLast()         //Получить последний элемент
        {
            return Get(GetSize()-1);
        }

        T* GetData()
        {
            return this->data;
        }

        T Get(int index)    //Получить элемент по индексу
        {
            if (this->GetSize() == 0)
                throw IndexOutOfRange("Function 'Get': List is empty.");
            if (index < 0) 
                throw IndexOutOfRange("Function 'Get': Negative index.");
            if (index >= this->size) 
                throw IndexOutOfRange("Function 'Get': Index is greater than size.");
            return *(this->data + index);
        }

        DynamicArray<T>* GetSubsequence(int startIndex, int endIndex)
        {
            if (startIndex < 0)
                throw IndexOutOfRange("Function 'GetSubsequence': Negative startIndex.");
            if (startIndex > endIndex)
                throw IndexOutOfRange("Function 'GetSubsequence': startIndex is greater than endIndex.");
            if (endIndex >= this->GetSize())
                throw IndexOutOfRange("Function 'GetSubsequence': endIndex is equal or greater than size.");
            
            DynamicArray<T>* output = new DynamicArray<T>(endIndex - startIndex + 1);
            for (int i = startIndex; i <= endIndex; i++)
            {
                (*output).Set(i - startIndex, this->Get(i));
            }
            return output;
        }

        int GetSize()       //Получить size 
        {
            return this->size;
        }

        int GetCapacity()   //Получить capacity
        {
            return this->capacity;
        }

    //операции

        void Set(int index, T value)    //Присвоить значение по индексу
        {
            if (index < 0) 
                throw IndexOutOfRange("Function 'Set': Negative index.");
            if (index >= this->size) 
                throw IndexOutOfRange("Function 'Set': Index is greater than size.");
            *(this->data + index) = value;
        }

        void SetData(T* newdata)
        {
            this->data = newdata;
        }

        void Resize(int newSize)        
        {
            if (newSize < 0)
                throw IndexOutOfRange("Function 'Resize': Negative size.");
            if ((this->capacity >= newSize) && (newSize >= this->capacity/4))
            {
                this->size = newSize;
            }
            else
            {
                T* data_temp = new T [newSize * 2];
                for (int i = 0; i < std::min(this->size, newSize); i++)
                {
                    *(data_temp + i) = *(this->data + i);
                }
                delete[] this->data;
                this->size = newSize;
                this->capacity = newSize*2;
                this->data = data_temp;
            }
        }

        void Insert(int index, T item)
        {
            if (index < 0) 
                throw IndexOutOfRange("Function 'InsertAt': Negative index.");
            if (index > this->size) 
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
        T &operator[] (int index) { 
        if (this->GetSize() == 0)
            throw IndexOutOfRange("Operator '[]': Array is empty.");
        if (index < 0) 
            throw IndexOutOfRange("Operator '[]': Negative index.");
        if (index >= this->size) 
            throw IndexOutOfRange("Operator '[]': Index is greater than size.");
        return this->data[index];    
    }

    //вспомогательное
        void printall()
        {
            std::cout << "Size: " << this->GetSize();
            std::cout << "\nCapacity: " << this->GetCapacity() << " (" << this->GetCapacity() * sizeof(T) << " bytes)";
            std::cout << "\nData: \n";
            for (int i = 0; i < this->size; i++)
                std::cout << this->Get(i) << ' ';
            std::cout << "\n";
        }
};