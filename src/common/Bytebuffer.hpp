//
//  Bytebuffer.hpp
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

class ByteBuffer {
public:
private:
    static constexpr size_t kDefaultBufferSize = 512;
    
    bool _owned{false};
    uint8_t* _data{nullptr};
    size_t _capacity{0};
    size_t _size{0};
    size_t _wpos{0};
    size_t _rpos{0};
    
public:
    ByteBuffer(size_t len = kDefaultBufferSize);    
    ~ByteBuffer();
    
    void resize(size_t bytes);
    
    template <class T>
    ByteBuffer& operator<<(const T& rhs);
    ByteBuffer& operator<<(const std::string& rhs);
    
    template <class T>
    ByteBuffer& operator>>(T& rhs);
    ByteBuffer& operator>>(std::string& rhs);
    
    void read(size_t len, uint8_t* data);
    void write(const void* data, size_t size);
    
    template <class T>
    T read();
    
    void reset();
    
    uint8_t* data();
    const uint8_t* data() const;
    size_t readPos() const;
    size_t writePos() const;
    
    // negative bytes should be supported
    void writeSkip(size_t bytes);
    
    size_t capacity() const;
    bool isWithinRange(uint8_t* ptr) const;
};


template <class T>
ByteBuffer& ByteBuffer::operator<<(const T& rhs)
{
    write(&rhs, sizeof(T));
    return *this;
}

template <class T>
ByteBuffer& ByteBuffer::operator>>(T& rhs)
{
    rhs = read<T>();
    return *this;
}

template <class T>
T ByteBuffer::read()
{
    T val;
    read(sizeof(T), reinterpret_cast<uint8_t*>(&val));
    return val;
}
