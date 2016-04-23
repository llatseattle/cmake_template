#ifndef _POINT_H_
#define _POINT_H_

#include "static_include.h"

/******************************************************************************
 * Light weight point class
 * Support: point of arbitrary size, 
            distance and squared distance between points
 *****************************************************************************/


template <typename T>
class Point {
    
public:
    Point(const size_t n = 3) : size_(n) { data_.resize(size_);}
    ~Point() {}
    const T& operator[](size_t i) const { return data_.at(i); }
    T&       operator[](size_t i) { return data_.at(i); }
    Point(const Point<T>& v)
    {
        if (this != &v) {
            size_ = v.size();
            data_.resize(size_);
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = v[i];
            }
        }
    }
    
    Point<T>& operator = (const Point<T>& v)
    {
        if (this != &v) {
            size_ = v.size();
            data_.resize(size_);
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = v[i];
            }
        }
        return *this;
    }
    bool operator == (const Point<T>& v)
    {
        for (size_t i = 0; i < size_; ++i) {
            if (!(data_[i]== v[i])) {
                return false;
            }
        }
        return true;
    }
    
    /*
     * Initialize point from vector of input data
     * Input: data, vector of input data
     */
    void        initialize(std::vector<T>& data)
    {
        if(size_ != data.size())
            throw ERR(ErrorMsg() << "Point(), " << "input data size mismatch.");
        data.resize(size_);
        std::copy(data.begin(), data.end(), data_.begin());
        return;
    }
    
    /*
     * Get the distance between two points
     * Input: v, input point
     * Output: long double type squared distance
     */
    T           dis(Point& v)
    {
        long double r = squareDis(v);
        r = sqrt(r);
        if (typeid(T) == typeid(int)) {
            assert(r < std::numeric_limits<int>::max()
                   && r > std::numeric_limits<int>::min());
        } else if (typeid(T) == typeid(double)) {
            assert(r < std::numeric_limits<int>::max()
                   && r > std::numeric_limits<int>::min());
        } else if (typeid(T) == typeid(float)) {
            assert(r < std::numeric_limits<int>::max()
                   && r > std::numeric_limits<int>::min());
        }
        return (T)r;
    }
    
    /*
     * Get the squared distance between two points
     * Input: v, input point
     * Output: long double type squared distance
     */
    long double squareDis(const Point<T>& v)
    {
        if(size_ != v.size())
            throw ERR(ErrorMsg() << "squareDis(), " << "mismatch point size");
        long double r = 0.0;
        for (size_t i = 0; i < size_; ++i) {
            r += (data_[i] - v[i]) * (data_[i] - v[i]);
        }
        return r;
    }
    
    size_t      size() const { return size_; }
    void        resize(const size_t size) { size_ = size; data_.resize(size_);}
    
    friend std::ostream& operator << (std::ostream& ofs, const Point<T>& pt)
    {
        for (auto i = 0; i < pt.size(); ++i) {
            ofs << pt[i] << std::scientific <<"\t";
        }
        ofs << "\n";
        return ofs;
    }
    friend std::istream& operator >> (std::istream& ifs, Point<T>& pt)
    {
        for (auto i = 0; i < pt.size(); ++i) {
            ifs >> pt[i];
        }
        return ifs;
    }

protected:
    
private:
    
    size_t          size_;
    std::vector<T>  data_;
};

#endif
