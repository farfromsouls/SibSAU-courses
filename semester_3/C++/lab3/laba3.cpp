#include <iostream>
#include <stdexcept>
#include <memory>
#include <cmath>
#include <cstddef>
#include <locale.h>
#include <windows.h>

using namespace std;

template <typename T>
class Point
{
public:
    virtual ~Point() = default;
    virtual bool inQuadrant(int quadrant) const = 0;
    virtual void print(std::ostream &os) const = 0;
    virtual void read(std::istream &is) = 0;
    virtual Point<T> *clone() const = 0;
};

template <typename T>
class Point2D : public Point<T>
{
    T x, y;

public:
    Point2D() : x(0), y(0) {}
    Point2D(T x, T y) : x(x), y(y) {}

    bool inQuadrant(int quadrant) const override
    {
        if (quadrant < 1 || quadrant > 4)
        {
            throw std::invalid_argument("Четверть должна быть от 1 до 4");
        }
        switch (quadrant)
        {
        case 1:
            return x > 0 && y > 0;
        case 2:
            return x < 0 && y > 0;
        case 3:
            return x < 0 && y < 0;
        case 4:
            return x > 0 && y < 0;
        }
        return false;
    }

    void print(std::ostream &os) const override
    {
        os << "(" << x << ", " << y << ")";
    }

    void read(std::istream &is) override
    {
        is >> x >> y;
        if (!is)
            throw std::runtime_error("Ошибка чтения данных точки");
    }

    Point<T> *clone() const override
    {
        return new Point2D(*this);
    }
};

template <typename T>
class Point3D : public Point<T>
{
    T x, y, z;

public:
    Point3D() : x(0), y(0), z(0) {}
    Point3D(T x, T y, T z) : x(x), y(y), z(z) {}

    bool inQuadrant(int quadrant) const override
    {
        if (quadrant < 1 || quadrant > 4)
            throw std::invalid_argument("Четверть должна быть от 1 до 4");

        switch (quadrant)
        {
        case 1: return x > 0 && y > 0;
        case 2: return x < 0 && y > 0;
        case 3: return x < 0 && y < 0;
        case 4: return x > 0 && y < 0;
        }
        return false;
    }

    void print(std::ostream &os) const override
    {
        os << "(" << x << ", " << y << ", " << z << ")";
    }

    void read(std::istream &is) override
    {
        is >> x >> y >> z;
        if (!is)
            throw std::runtime_error("Ошибка чтения данных точки");
    }

    Point<T> *clone() const override
    {
        return new Point3D(*this);
    }
};

template <typename T>
class TPointMatrix
{
    std::size_t rows_, cols_;
    Point<T> ***data_;

    void clear() noexcept
    {
        if (data_)
        {
            for (std::size_t i = 0; i < rows_; ++i)
            {
                if (data_[i])
                {
                    for (std::size_t j = 0; j < cols_; ++j)
                    {
                        delete data_[i][j];
                    }
                    delete[] data_[i];
                }
            }
            delete[] data_;
            data_ = nullptr;
        }
        rows_ = cols_ = 0;
    }

    void copyFrom(const TPointMatrix &other)
    {
        rows_ = other.rows_;
        cols_ = other.cols_;

        data_ = new Point<T> **[rows_];

        try
        {
            for (std::size_t i = 0; i < rows_; ++i)
            {
                data_[i] = new Point<T> *[cols_];

                for (std::size_t j = 0; j < cols_; ++j)
                {
                    data_[i][j] = nullptr;
                }

                for (std::size_t j = 0; j < cols_; ++j)
                {
                    if (other.data_[i][j] != nullptr)
                    {
                        data_[i][j] = other.data_[i][j]->clone();
                    }
                }
            }
        }
        catch (...)
        {
            clear();
            throw;
        }
    }

public:
    TPointMatrix() noexcept : rows_(0), cols_(0), data_(nullptr) {}

    TPointMatrix(std::size_t rows, std::size_t cols) : rows_(rows), cols_(cols), data_(nullptr)
    {
        if (rows == 0 || cols == 0)
        {
            return;
        }

        data_ = new Point<T> **[rows_];
        for (std::size_t i = 0; i < rows_; ++i)
        {
            data_[i] = nullptr;
        }

        try
        {
            for (std::size_t i = 0; i < rows_; ++i)
            {
                data_[i] = new Point<T> *[cols_];
                for (std::size_t j = 0; j < cols_; ++j)
                {
                    data_[i][j] = nullptr;
                }
            }
        }
        catch (...)
        {
            clear();
            throw;
        }
    }

    TPointMatrix(const TPointMatrix &other) : rows_(0), cols_(0), data_(nullptr)
    {
        if (other.data_)
        {
            copyFrom(other);
        }
    }

    TPointMatrix(TPointMatrix &&other) noexcept
        : rows_(other.rows_), cols_(other.cols_), data_(other.data_)
    {
        other.rows_ = other.cols_ = 0;
        other.data_ = nullptr;
    }

    TPointMatrix &operator=(const TPointMatrix &other)
    {
        if (this != &other)
        {
            TPointMatrix temp(other);
            swap(*this, temp);
        }
        return *this;
    }

    TPointMatrix &operator=(TPointMatrix &&other) noexcept
    {
        if (this != &other)
        {
            clear();
            rows_ = other.rows_;
            cols_ = other.cols_;
            data_ = other.data_;
            other.rows_ = other.cols_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    ~TPointMatrix()
    {
        clear();
    }

    friend void swap(TPointMatrix &a, TPointMatrix &b) noexcept
    {
        using std::swap;
        swap(a.rows_, b.rows_);
        swap(a.cols_, b.cols_);
        swap(a.data_, b.data_);
    }

    Point<T> &at(std::size_t row, std::size_t col) const
    {
        if (row >= rows_ || col >= cols_)
        {
            throw std::out_of_range("Индекс матрицы вне диапазона");
        }
        if (data_[row][col] == nullptr)
        {
            throw std::runtime_error("Элемент матрицы равен null");
        }
        return *data_[row][col];
    }

    void setPoint(std::size_t row, std::size_t col, Point<T> *point)
    {
        if (row >= rows_ || col >= cols_)
        {
            throw std::out_of_range("Индекс матрицы вне диапазона");
        }
        delete data_[row][col];
        data_[row][col] = point;
    }

    std::size_t rows() const noexcept { return rows_; }
    std::size_t cols() const noexcept { return cols_; }

    std::size_t findPointsInQuadrant(int quadrant, Point<T> **result, std::size_t maxSize) const
    {
        if (!result || maxSize == 0)
        {
            throw std::invalid_argument("неверный буфер результата");
        }

        std::size_t count = 0;
        for (std::size_t i = 0; i < rows_ && count < maxSize; ++i)
        {
            for (std::size_t j = 0; j < cols_ && count < maxSize; ++j)
            {
                if (data_[i][j] != nullptr && data_[i][j]->inQuadrant(quadrant))
                {
                    result[count] = data_[i][j]->clone();
                    ++count;
                }
            }
        }
        return count;
    }

    void read(std::istream &is)
    {
        std::size_t rows, cols;
        if (!(is >> rows >> cols))
        {
            throw std::runtime_error("Ошибка чтения размеров матрицы");
        }

        TPointMatrix temp(rows, cols);

        for (std::size_t i = 0; i < rows; ++i)
        {
            for (std::size_t j = 0; j < cols; ++j)
            {
                auto point = new Point2D<T>();
                try
                {
                    point->read(is);
                    temp.setPoint(i, j, point);
                }
                catch (...)
                {
                    delete point;
                    throw;
                }
            }
        }

        swap(*this, temp);
    }

    void print(std::ostream &os) const
    {
        os << "Матрица " << rows_ << " на " << cols_ << ":\n";
        for (std::size_t i = 0; i < rows_; ++i)
        {
            for (std::size_t j = 0; j < cols_; ++j)
            {
                if (data_[i][j] != nullptr)
                {
                    data_[i][j]->print(os);
                }
                else
                {
                    os << "(null)";
                }
                os << " ";
            }
            os << "\n";
        }
    }
};

int main()
{
    try
    {
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
        setlocale(LC_ALL, "ru_RU.UTF-8");
        
        cout << " Тест с двумерными точками \n";
        TPointMatrix<int> matrix2D(2, 3);
        matrix2D.setPoint(0, 0, new Point2D<int>(1, 2));
        matrix2D.setPoint(0, 1, new Point2D<int>(-3, 4));
        matrix2D.setPoint(0, 2, new Point2D<int>(5, -6));
        matrix2D.setPoint(1, 0, new Point2D<int>(-1, -2));
        matrix2D.setPoint(1, 1, new Point2D<int>(3, -4));
        matrix2D.setPoint(1, 2, new Point2D<int>(-5, 6));
        matrix2D.print(std::cout);

        cout << "\nВведите номер четверти (1-4): ";
        int quadrant;
        cin >> quadrant;

        const size_t maxPoints = 10;
        Point<int> *points[maxPoints];
        size_t count = matrix2D.findPointsInQuadrant(quadrant, points, maxPoints);
        cout << "Найдено " << count << " точек:\n";
        for (size_t i = 0; i < count; ++i)
        {
            points[i]->print(cout);
            cout << " ";
            delete points[i];
        }
        cout << "\n";

        cout << "\nТест с трёхмерными точками\n";
        TPointMatrix<int> matrix3D(2, 2);
        matrix3D.setPoint(0, 0, new Point3D<int>(1, 2, 3));
        matrix3D.setPoint(0, 1, new Point3D<int>(-3, 4, 5));
        matrix3D.setPoint(1, 0, new Point3D<int>(-1, -2, -3));
        matrix3D.setPoint(1, 1, new Point3D<int>(3, -4, 0));
        matrix3D.print(cout);

        cout << "\nВведите номер четверти (1-4): ";
        cin >> quadrant;

        Point<int> *points3D[maxPoints];
        count = matrix3D.findPointsInQuadrant(quadrant, points3D, maxPoints);
        cout << "Найдено " << count << " точек:\n";
        for (size_t i = 0; i < count; ++i)
        {
            points3D[i]->print(cout);
            cout << " ";
            delete points3D[i];
        }
        cout << "\n";

        cout << "\nПроверка исключений \n";
        try
        {
            matrix2D.at(10, 0);
        }
        catch (const std::out_of_range &e)
        {
            cout << "out_of_range: " << e.what() << "\n";
        }

        try
        {
            matrix2D.at(0, 0).inQuadrant(5);
        }
        catch (const std::invalid_argument &e)
        {
            cout << "invalid_argument: " << e.what() << "\n";
        }

        cout << "\nТест конструкторов \n";
        TPointMatrix<int> copyMatrix = matrix2D;
        cout << "Скопированная матрица (2D):\n";
        copyMatrix.print(cout);
    }
    catch (const std::exception &e)
    {
        cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    return 0;
}