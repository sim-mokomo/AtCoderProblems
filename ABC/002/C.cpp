#include <iostream>

struct Vector2 {
    int x;
    int y;

    Vector2()
            : x(0), y(0) {

    }

    Vector2(int x, int y)
            : x(x), y(y) {

    }

    const Vector2 operator-(const Vector2 &other) const {
        return Vector2(x - other.x, y - other.y);
    }
};

int main(){
    Vector2 a, b ,c;

    std::cin
            >> a.x >> a.y
            >> b.x >> b.y
            >> c.x >> c.y;

    const Vector2 abVector = b - a;
    const Vector2 acVector = c - a;

    const double area = std::abs( (abVector.x * acVector.y) - (abVector.y * acVector.x) ) * 0.5;
    printf("%f\n", area);

    return 0;
}