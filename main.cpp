#include <iostream>


template<typename T>
class MyVector{
    private:
        T* data_ = nullptr;
        size_t size_ = 0;
        size_t capacity_ = 0;

        void reallocate();
    public:
        MyVector() = default;

        MyVector(MyVector&& other) noexcept; 
        MyVector& operator=(MyVector&& other) noexcept; 
        MyVector(const MyVector&) = delete; 
        MyVector& operator=(const MyVector&) = delete;

        ~MyVector();    
        void push_back(const T& value);
        size_t size() const {return size_;}
        size_t capacity() const {return capacity_;}

        T& operator[](size_t index);
};



template <typename T>
MyVector<T>::~MyVector(){
    if(data_ != nullptr){
        delete[] data_;
        data_ = nullptr;
    }
}

template <typename T>
void MyVector<T>::reallocate(){
    size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    T* new_data = new T[new_capacity];

    for (size_t i = 0; i < size_; i++){
        new_data[i] = data_[i];
    }
    
    if (data_ != nullptr){
        delete[] data_;
    }

    data_ = new_data;
    capacity_ = new_capacity;
}

template <typename T>
void MyVector<T>::push_back(const T& value){
    if (size_ == capacity_){
        reallocate();
    }

    data_[size_] = value;

    size_++;
}


template <typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept :
    data_(other.data_),
    size_(other.size_),
    capacity_(other.capacity_) 
{
    
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        delete[] data_;

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}


template <typename T>
T& MyVector<T>::operator[](size_t index){
    return data_[index];
}

int main(){

    MyVector<int> vec;
    std::cout << "Начальный размер: " << vec.size() << "б Вместимость: " << vec.capacity() << std::endl;
    for (int i = 1; i <= 5; i++){
        vec.push_back(i * 10);
        std::cout << "Добавлен " << i*10 << ". Размер: " << vec.size() << ", Вместимость: " << vec.capacity() << "\n";
    }
    std::cout << "\nЭлементы контейнера:\n";
    for (size_t i = 0; i < vec.size(); i++){
        std::cout << "Элемент "<< i << ": " << vec[i] << "\n";   
    }
    vec[0] = 99;
    std::cout << "Элемент 0 изменен на: " << vec[0] << "\n";
    return 0;
}