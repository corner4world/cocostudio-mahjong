//
// Created by farmer on 2018/7/5.
// 工具类

#ifndef COCOSTUDIO_MAHJONG_UTILITY_H
#define COCOSTUDIO_MAHJONG_UTILITY_H

#include <iostream>

namespace utility {

    template <typename T>
    inline std::string toString (const T arg)
    {
        std::ostringstream stream;
        stream << arg;
        return stream.str();
    }
    template<>
    inline std::string toString<bool>(const bool arg) {
        return arg ? "true" : "false";
    }
    template <typename T, typename... Types>
    inline std::string toString (const T firstArg, const Types... args) {
        std::ostringstream stream;
        stream << toString(firstArg) << toString(args...);
        return stream.str();
    }

    template<typename T>
    inline T parseValue( const std::string& _value )
    {
        std::istringstream stream(_value);
        T result;
        stream >> result;
        if (stream.fail())
            return T();
        else
        {
            int item = stream.get();
            while (item != -1)
            {
                if (item != ' ' && item != '\t')
                    return T();
                item = stream.get();
            }
        }
        return result;
    }

    template<>
    inline bool parseValue(const std::string& _value)
    {
        if (_value == "True" || _value == "true" || _value == "1")
            return true;
        return false;
    }

    template<>
    inline char parseValue(const std::string& _value)
    {
        return (char)parseValue<short>(_value);
    }

    template<>
    inline unsigned char parseValue(const std::string& _value)
    {
        return (unsigned char)parseValue<unsigned short>(_value);
    }


    inline short parseShort(const std::string& _value)
    {
        return parseValue<short>(_value);
    }

    inline unsigned short parseUShort(const std::string& _value)
    {
        return parseValue<unsigned short>(_value);
    }

    inline int parseInt(const std::string& _value)
    {
        return parseValue<int>(_value);
    }

    inline unsigned int parseUInt(const std::string& _value)
    {
        return parseValue<unsigned int>(_value);
    }

    inline size_t parseSizeT(const std::string& _value)
    {
        return parseValue<size_t>(_value);
    }

    inline float parseFloat(const std::string& _value)
    {
        return parseValue<float>(_value);
    }

    inline double parseDouble(const std::string& _value)
    {
        return parseValue<double>(_value);
    }

    inline bool parseBool(const std::string& _value)
    {
        return parseValue<bool>(_value);
    }

    inline char parseChar(const std::string& _value)
    {
        return parseValue<char>(_value);
    }

    inline unsigned char parseUChar(const std::string& _value)
    {
        return parseValue<unsigned char>(_value);
    }
}

#endif //COCOSTUDIO_MAHJONG_UTILITY_H
