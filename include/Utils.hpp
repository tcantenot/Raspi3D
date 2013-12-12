#ifndef RPI_UTILS_HPP
#define RPI_UTILS_HPP

#include <sstream>
#include <typeinfo>
#include <memory>

namespace RPi {

namespace Utils {

    // -------------------------------------------------------------------------
    //  Cast a string into a number of type T
    //
    //   - s : string to cast
    //   
    //   returns the equivalent type T number of the string s
    //
    //   /!\ throw a std::bad_cast exception if fails
    // -------------------------------------------------------------------------
    template <typename T>
    T Number(std::string const & s) throw(std::bad_cast)
    {
        static_assert(std::is_scalar<T>::value, "T must be a number type");

        T value;
        std::stringstream ss(s);
        if(ss >> value) return value;
        throw std::bad_cast();
    }

    // -------------------------------------------------------------------------
    //  Cast a T object into std::string
    //
    //   - value : value to cast
    //  
    //   returns the std::string equivalent of the T <value>
    //
    //  /!\ throw a std::bad_cast exception if fails
    // -------------------------------------------------------------------------
    template <typename T>
    std::string String(T const & value) throw(std::bad_cast)
    {
        std::stringstream ss;
        if(ss << value) return ss.str();
        throw std::bad_cast();
    }


}

}

#endif //RPI_UTILS_HPP
