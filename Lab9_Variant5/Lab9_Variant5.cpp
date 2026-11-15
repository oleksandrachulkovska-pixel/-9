#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

// Абстрактний базовий клас «Геометрична фігура»
class GeometricFigure
{
private:
    // Закриті властивості класу
    double x;
    double y;
    double angle;
    double scale;
    bool visible;

protected:
    // Зміна стану видимості фігури
    void setVisible(bool value)
    {
        visible = value;
    }

public:
    // Конструктор базового класу
    GeometricFigure(double x, double y, double angle, double scale)
    {
        if (scale <= 0)
        {
            throw invalid_argument("Scale must be greater than zero!");
        }

        this->x = x;
        this->y = y;
        this->angle = angle;
        this->scale = scale;
        this->visible = false;
    }

    // Чисто віртуальні функції
    virtual void show() = 0;
    virtual void hide() = 0;

    // Віртуальна функція повороту фігури
    virtual void rotate(double degrees)
    {
        angle += degrees;
        angle = fmod(angle, 360.0);

        if (angle < 0)
        {
            angle += 360.0;
        }
    }

    // Віртуальна функція переміщення фігури
    virtual void move(double dx, double dy)
    {
        x += dx;
        y += dy;
    }

    // Зміна масштабного фактора
    void setScale(double newScale)
    {
        if (newScale <= 0)
        {
            throw invalid_argument("Scale must be greater than zero!");
        }

        scale = newScale;
    }

    // Отримання координати X
    double getX() const
    {
        return x;
    }

    // Отримання координати Y
    double getY() const
    {
        return y;
    }

    // Отримання кута повороту
    double getAngle() const
    {
        return angle;
    }

    // Отримання масштабного фактора
    double getScale() const
    {
        return scale;
    }

    // Перевірка видимості фігури
    bool isVisible() const
    {
        return visible;
    }

    // Віртуальний деструктор
    virtual ~GeometricFigure()
    {
    }
};


// Похідний клас «Прямокутник»
class Rectangle : public GeometricFigure
{
private:
    // Закриті властивості прямокутника
    double width;
    double height;

public:
    // Конструктор класу Rectangle
    Rectangle(double x, double y, double angle,
        double scale, double width, double height)
        : GeometricFigure(x, y, angle, scale)
    {
        if (width <= 0 || height <= 0)
        {
            throw invalid_argument(
                "Width and height must be greater than zero!");
        }

        this->width = width;
        this->height = height;
    }

    // Перевизначення функції показу фігури
    void show() override
    {
        setVisible(true);

        cout << "\nПрямокутник показано на екрані." << endl;

        cout << "Координати центра: ("
            << getX() << ", " << getY() << ")" << endl;

        cout << "Кут повороту: "
            << getAngle() << " градусів" << endl;

        cout << "Масштабний фактор: "
            << getScale() << endl;

        cout << "Ширина: "
            << width * getScale() << endl;

        cout << "Висота: "
            << height * getScale() << endl;
    }

    // Перевизначення функції приховування фігури
    void hide() override
    {
        setVisible(false);

        cout << "\nПрямокутник приховано." << endl;
    }

    // Зміна ширини прямокутника
    void setWidth(double newWidth)
    {
        if (newWidth <= 0)
        {
            throw invalid_argument(
                "Width must be greater than zero!");
        }

        width = newWidth;
    }

    // Зміна висоти прямокутника
    void setHeight(double newHeight)
    {
        if (newHeight <= 0)
        {
            throw invalid_argument(
                "Height must be greater than zero!");
        }

        height = newHeight;
    }

    // Отримання ширини
    double getWidth() const
    {
        return width;
    }

    // Отримання висоти
    double getHeight() const
    {
        return height;
    }
};


// Головна функція програми
int main()
{
    try
    {
        // Створення об'єкта класу Rectangle
        Rectangle rectangle(10, 20, 0, 1.0, 8, 5);

        // Покажчик на базовий клас
        GeometricFigure* figure = &rectangle;

        // Показ прямокутника
        figure->show();

        // Переміщення прямокутника
        cout << "\nПереміщення прямокутника:" << endl;

        figure->move(5, 3);

        cout << "Нова координата X: "
            << figure->getX() << endl;

        cout << "Нова координата Y: "
            << figure->getY() << endl;

        // Поворот прямокутника
        cout << "\nПоворот прямокутника:" << endl;

        figure->rotate(45);

        cout << "Новий кут повороту: "
            << figure->getAngle() << " градусів" << endl;

        // Зміна масштабного фактора
        cout << "\nЗміна масштабного фактора:" << endl;

        figure->setScale(1.5);

        cout << "Новий масштабний фактор: "
            << figure->getScale() << endl;

        // Зміна розмірів прямокутника
        cout << "\nЗміна розмірів прямокутника:" << endl;

        rectangle.setWidth(10);
        rectangle.setHeight(6);

        cout << "Нова ширина: "
            << rectangle.getWidth() << endl;

        cout << "Нова висота: "
            << rectangle.getHeight() << endl;

        // Повторний показ прямокутника
        cout << "\nОновлений стан прямокутника:" << endl;

        figure->show();

        // Приховування прямокутника
        figure->hide();

        // Перевірка стану видимості
        cout << "\nПеревірка видимості:" << endl;

        if (figure->isVisible())
        {
            cout << "Прямокутник видимий." << endl;
        }
        else
        {
            cout << "Прямокутник невидимий." << endl;
        }
    }
    catch (const exception& error)
    {
        cout << "Помилка: " << error.what() << endl;
        return 1;
    }

    return 0;
}