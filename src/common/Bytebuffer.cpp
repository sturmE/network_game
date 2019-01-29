//
//  Bytebuffer.cpp
//  dirtycommon
//
//  Created by Eugene Sturm on 1/29/19.
//

#include "Bytebuffer.hpp"

ByteBuffer::ByteBuffer(size_t len)
: ByteBuffer((len > 0 ? new uint8_t[len] : nullptr), std::max<size_t>(0, len))
{ _owned = true; }

ByteBuffer::ByteBuffer(uint8_t* buffer, size_t len)
: _data(buffer)
, _capacity(len)
, _wpos(0)
, _rpos(0)
{
    assert(_data);
    assert(_capacity);
}

ByteBuffer::~ByteBuffer()
{
    if (_owned && _data) {
        delete[] _data;
        _data = nullptr;
    }
}

void ByteBuffer::resize(size_t bytes)
{
    assert(_owned);
    assert(bytes + 1 > _wpos);
    assert(bytes >= _rpos);
    assert(bytes > _capacity);
    
    uint8_t* newData = new uint8_t[bytes];
    memcpy(newData, _data, _capacity);
    delete[] _data;
    _data     = newData;
    _capacity = bytes;
}

ByteBuffer& ByteBuffer::operator>>(std::string& rhs)
{
    rhs.clear();
    while (_rpos < _wpos) {
        char c = read<char>();
        if (c == 0) {
            break;
        }
        rhs += c;
    }
    return *this;
}

ByteBuffer& ByteBuffer::operator<<(const std::string& rhs)
{
    write(rhs.data(), rhs.length());
    (*this) << static_cast<char>(0);
    return *this;
}

void ByteBuffer::read(size_t len, uint8_t* data) {
    assert(_rpos + len <= _wpos);
    assert(data);
    memcpy(data, _data + _rpos, len);
    _rpos += len;
}

void ByteBuffer::write(const void* data, size_t size)
{
    assert(_wpos + size <= _capacity);
    assert(data);
    memcpy(_data + _wpos, data, size);
    _wpos += size;
    _
}

void ByteBuffer::reset()
{
    _wpos = 0;
    _rpos = 0;
}

const uint8_t* ByteBuffer::data() const { return _data; }
uint8_t* ByteBuffer::data() { return _data; };

size_t ByteBuffer::readPos() const { return _rpos; }

size_t ByteBuffer::writePos() const { return _wpos; }

// negative bytes should be supported
void ByteBuffer::writeSkip(size_t bytes)
{
    assert(_wpos + bytes < _capacity && _wpos + bytes >= _rpos);
    _wpos += bytes;
}

size_t ByteBuffer::capacity() const { return _capacity; }

bool ByteBuffer::isWithinRange(uint8_t* ptr) const
{
    return ptr >= _data && ptr < _data + _capacity;
    
}

