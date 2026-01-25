#include "BitArray.hpp"

BitArray::BitArray() {
    m_size = 8;
    m_bits = new bool[8];
    m_good = true;
    for(intmax_t i = 0; i < m_size; i++){
        m_bits[i] = false;
    }
}

BitArray::BitArray(intmax_t size) {
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

BitArray::BitArray(const std::string & value) {
    // TODO
}

BitArray::~BitArray() {
    // TODO
}

// TODO: other methods
