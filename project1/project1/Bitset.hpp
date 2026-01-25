#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h>
#include <string>

class Bitset{
  public:

    virtual ~Bitset(){};
    
    /**
     * Returns the number of bits in the bitset.
     * 
     * @return the size of the bitset
     */
    virtual intmax_t size() const = 0;
    
    /**
     * Returns whether the bitset is in a valid state.
     * 
     * @return true if the bitset is valid, otherwise false
     */
    virtual bool good() const = 0;
    
    /**
     * Sets the bit at the given index to 1.
     * If index is out of range, bitset becomes invalid.
     * 
     * @param index the index of the bit to set
     */
    virtual void set(intmax_t index) = 0;
    
    /**
     * Resets the bit at the given index to 0.
     * If index is out of range, bitset becomes invalid.
     * 
     * @param index the index of the bit to reset
     */
    virtual void reset(intmax_t index) = 0;
    
    /**
     * Toggles the bit at the given index.
     * If index is out of range, bitset becomes invalid.
     * 
     * @param index the index of the bit to toggle
     */
    virtual void toggle(intmax_t index) = 0;

    /**
     * Tests whether the bit at the given index is set.
     * Returns false if the bit is not set or index is out of range.
     * If index is out of range, bitset becomes invalid.
     * 
     * @param index the index of the bit to test
     * @return true if the bit is set, otherwise false
     */
    virtual bool test(intmax_t index) = 0;

    /**
     * Returns a string representation of the bitset.
     * String is ordered from most significant bit to least significant bit.
     * Uses characters '1' and '0'.
     * 
     * @return a string representation of the bitset
     */
    virtual std::string asString() const = 0;

};

#endif
