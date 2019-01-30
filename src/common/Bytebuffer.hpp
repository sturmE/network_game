//
//  ByteStream.hpp
//  dirtycommon
//
//  Created by Eugene Sturm on 1/29/19.
//

#pragma once

#include <stdint.h>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

class ByteStream {
public:
private:    
    std::vector<uint8_t> _data;
    size_t _wpos{0};
    size_t _rpos{0};
    
public:
    ByteStream();
    ~ByteStream();
    
    template <class T>
    ByteStream& operator<<(const T& rhs);
    ByteStream& operator<<(const std::string& rhs);
    
    template <class T>
    ByteStream& operator>>(T& rhs);
    ByteStream& operator>>(std::string& rhs);
    
    void read(size_t len, uint8_t* data);
    void write(const void* data, size_t size);
    
    template <class T>
    T read();
    
    void reset();
    
    uint8_t* data();
    const uint8_t* data() const;
    size_t size() const;
    size_t readPos() const;
    size_t writePos() const;    
    size_t capacity() const;
private:
    void grow();
};


template <class T>
ByteStream& ByteStream::operator<<(const T& rhs)
{
    write(&rhs, sizeof(T));
    return *this;
}

template <class T>
ByteStream& ByteStream::operator>>(T& rhs)
{
    rhs = read<T>();
    return *this;
}

template <class T>
T ByteStream::read()
{
    T val;
    read(sizeof(T), reinterpret_cast<uint8_t*>(&val));
    return val;
}
