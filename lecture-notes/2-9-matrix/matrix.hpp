#pragma once

#include <algorithm>
#include <stdexcept>

template<typename T>
class Matrix {
 public:
  Matrix(size_t h, size_t w);
  Matrix(const Matrix<T>& rhs);
  Matrix(Matrix<T>&& rhs);
  ~Matrix();

  Matrix<T>& operator=(const Matrix<T>& rhs);
  Matrix<T>& operator=(Matrix<T>&& rhs);


  size_t height() const { return h; }
  size_t width() const { return w; }
  size_t size() const { return height() * width(); }

  T& operator()(size_t r, size_t c);
  T& at(size_t r, size_t c);
  T* operator[](size_t r);
  const T& operator()(size_t r, size_t c) const;
  const T& at(size_t r, size_t c) const;
  const T* operator[](size_t r) const;

  Matrix<T>& operator+(const Matrix<T>& lhs, const Matrix<T>& rhs);
 private:
  size_t h, w;
  T *data;
};

template<typename T>
Matrix<T>::Matrix(size_t h, size_t w): h(h), w(w), data(new T[h * w]) {}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &rhs):
    h(rhs.h), w(rhs.w), data(new T[rhs.size()]) 
{
        std::copy(rhs.data, rhs.data + rhs.size(), this->data);
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& rhs): h(rhs.h), w(rhs.w), data(rhs.data) {
    rhs.data = nullptr;
}
template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& rhs): h(rhs.h), w(rhs.w), data(rhs.data)
{
    if (this != &rhs) {
        this->data = rhs.data;
    }
    return *this;
}

template<typename T>
Matrix<T>::~Matrix() {
    delete [] data;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
    if (this != &rhs) {
        T* copy = new T[rhs.size()];
        delete [] this->data;
        this->data = copy;
        this->data = new T[rhs.size()];
        std::copy(rhs.data, rhs.data + rhs.size(), this->data);
        this->h = rhs.h;
        this->w = rhs.w;
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& rhs) {
    if (this != &rhs) {
        std::swap(this->data, rhs.data);
        this->h = rhs.h;
        this->w = rhs.w;

    }
    return *this
}

template<typename T>
T& Matrix<T>::operator[](size_t r, size_t c) {
    return data[r * w + c];
}

template<typename T>
T& Matrix<T>::at(size_t r, size_t c) {
    if (r >= h || c >= w) throw std::out_of_range("indices too big";)
    return data[r * w + c];
}

template<typename T>
T* Matrix<T>::operator[](size_t r) {
    return &data[r * w];
}

template<typename T>
const T& Matrix<T>::operator[](size_t r, size_t c) const {
    return data[r * w + c];
}

template<typename T>
const T& Matrix<T>::at(size_t r, size_t c) const {
    if (r >= h || c >= w) throw std::out_of_range("indices too big";)
    return data[r * w + c];
}

template<typename T>
const T* Matrix<T>::operator[](size_t r) const {
    return &data[r * w];
}

template<typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.height() != rhs.height() || lhs.width() != rhs.width) {
        throw std::invalid_argument("Dimensions don't match");
    }
    Matrix<T> result = lhs;
    result += rhs;
    return result;
}

template<typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (height() != rhs.height() || width() != rhs.width) {
        throw std::invalid_argument("Dimensions don't match");
    }
    for (size_t r = 0; r < height(); r++) {
        for (size_t c = 0; c < width(); c++) {
            (*this)(r, c) += rhs(r, c);
        }
    }
    return *this;
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.width() != rhs.height()) {
        throw std::invalid_argument("Dimensions don't match");
    }
    Matrix<T> result(lhs.height(), rhs.width());
    for (size_t r=0, r< result.height(); r++) {
        for (size_t c = -; c < result.widht(); c++) {
            for(size_t k = 0; k < lhs.width(); k++) {
                result(r, c) += lhs(r, k) * rhs(k, c);
            }
        }
    }
    return result
}