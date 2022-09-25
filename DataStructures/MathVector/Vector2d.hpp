#ifndef __Vector2D_HPP__
#define __Vector2D_HPP__

#include <cmath>
#include <iostream>

template<typename T>
struct Vector2D {
  T x;
  T y;
  //  constructors
  Vector2D() : x(0), y(0) {}
  Vector2D(T nx, T ny) : x(nx), y(ny) {}
  // copy constructors
  Vector2D(const Vector2D& other) : x(other.x), y(other.y) {}
  Vector2D& operator=(const Vector2D& other) { x = other.x; y = other.y; return *this; }

  //  operations
  Vector2D& Add(const Vector2D& other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  Vector2D& Sub(const Vector2D& other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  Vector2D& Mul(T scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }
  Vector2D& Div(T scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  //  vector specific operations
  T Magnitude() const { return sqrt( (pow(x, 2) + pow(y, 2)) ); }
  T Dot(const Vector2D& other) const { return x * other.x + y * other.y;}
  Vector2D& Unit() { return this->Div(this->Magnitude()); }
  const Vector2D<T> Distance(const Vector2D& other) {
    T nx = other.x - x;
    T ny = other.y - y;
    return Vector2D<T>(nx, ny);
  }

  //  operator overloading to be able to add and sub without changing the original variables
  bool operator==(const Vector2D& other) { return (x == other.x && y == other.y ); }
  Vector2D<T> operator+(const Vector2D& other) {
    T nx = x + other.x;
    T ny = y + other.y;
    return Vector2D<T>(nx, ny);
  }
  Vector2D<T> operator-(const Vector2D& other) {
    T nx = x - other.x;
    T ny = y - other.y;
    return Vector2D<T>(nx, ny);
  }

  Vector2D<T> operator*(T scalar) {
    T nx = x * scalar;
    T ny = y * scalar;
    return Vector2D<T>(nx, ny);
  }
  const Vector2D<T> operator*(T scalar) const {
    T nx = x * scalar;
    T ny = y * scalar;
    return Vector2D<T>(nx, ny);
  }

  //  print statment
  void print() const {
    std::cout << '[' << x << ", " << y << ']' << std::endl;
  }
};
const Vector2D<float> VECTOR2D_RIGHT(1, 0);
const Vector2D<float> VECTOR2D_LEFT(-1, 0);
const Vector2D<float> VECTOR2D_UP(0, -1);
const Vector2D<float> VECTOR2D_DOWN(0, 1);
#endif
