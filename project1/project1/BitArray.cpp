#include "BitArray.hpp"

// Default Constructor
BitArray::BitArray(){
    m_size = 8;
    m_bits = new bool[8];
    m_good = true;
    for(intmax_t i = 0; i < m_size; i++){
        m_bits[i] = false;
    }
}

// Integer Constructor
BitArray::BitArray(intmax_t size){
    m_size = size;
    m_bits = nullptr;
    m_good = true;
    
    if (size <= 0){
        m_good = false;
        m_size = 0;
        return;
    }

    m_bits = new bool[m_size];
    for (intmax_t i = 0; i < m_size; i++){
        m_bits[i] = false;
    }
}

// String Constructor
BitArray::BitArray(const std::string & value){
    m_size = 0;
    m_bits = nullptr;
    m_good = true;

    if (value.empty()){
        m_good = false;
        return;
    }

    m_size = static_cast<intmax_t>(value.size());
    m_bits = new bool[m_size];

    for (intmax_t i = 0; i < m_size; i++){
        char c = value[m_size - i - 1];
        if (c == '0')
            m_bits[i] = false;
        else if (c == '1')
            m_bits[i] = true;
        else
            m_good = false;
            return;
    }
}

// Destructor
BitArray::~BitArray(){
    delete[] m_bits;
}


// Added Methods

// Size
intmax_t BitArray::size() const{
    return m_size;
}

// Good
bool BitArray::good() const{
    return m_good;
}

// Set
void BitArray::set(intmax_t index){
    if (index < 0 || index >= m_size){
        m_good = false;
        return;
    }
    m_bits[index] = true;
}

// Reset
void BitArray::reset(intmax_t index){
    if (index < 0 || index >= m_size){
        m_good = false;
        return;
    }
    m_bits[index] = false;
}

// Toggle
void BitArray::toggle(intmax_t index){
    if (index < 0 || index >= m_size){
        m_good = false;
        return;
    }
    m_bits[index] = !m_bits[index];
}

