#ifndef slot_map_hpp__
#define slot_map_hpp__

/// \file slot_map.hpp
/// <summary>
/// File containing implementation of the slot map data structure and helper functionality.
///
/// \author Nicholaus Clark
/// \copyright Copyright 2021 Nicholaus Clark
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
/// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
/// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
/// permit persons to whom the Software is furnished to do so, subject to the following conditions: <br />
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
/// Software. <br />
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
/// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
/// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
/// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
/// </summary>

#include "stdint.hpp"
#include "utility.hpp"

namespace containers
{
    /// <summary>
    /// Data structure that has a guaranteed constant time insertion, erasure, and retrieval.  Insertion is performed
    /// in constant time if and only if the backing buffer is large enough.  The values in the data structure are
    /// unordered.  Values stored are guaranteed to be sequential in memory.
    ///
    /// The slot map data structure is a variable sized structure.  The memory footprint of the structure consists
    /// of three buffers, a value buffer, a buffer storing all keys, and a buffer storing pointers from values to keys.
    /// Through these buffers, the slot map provides constant time lookup of a value provided a key and constant time
    /// erasure of a value given a key, however, there are multiple levels of indirection to achieve this.  For a small
    /// number of elements, the lack of indirection in a vector makes it a cheaper alternative to the slot map.  As the
    /// number of elements grows, the cost of erasure and search provided a key becomes cheaper than erasing a value
    /// from a vector and searching a vector for a value.  With the current implementation of the data structure, it
    /// is not possible to sort the values.
    /// </summary>
    /// <typeparam name="Value">
    /// Type of value stored in the slot map.
    /// </typeparam>
    /// <typeparam name="Index">
    /// Type of value to be used as an index into the map.
    /// </typeparam>
    /// <typeparam name="Generation">
    /// Type of value to be used as a generation counter for the map.
    /// </typeparam>
    template <typename Value, typename Index = u32, typename Generation = u32>
    class slot_map
    {
    public:
        /// <summary>
        /// Type alias for map indices.
        /// </summary>
        using index_type = Index;

        /// <summary>
        /// Type alias for generation counter in the map.
        /// </summary>
        using generation_type = Generation;

        /// <summary>
        /// Type alias for the value type stored in the map.
        /// </summary>
        using value_type = Value;

        /// <summary>
        /// Type alias of the value iterator for the map.
        /// </summary>
        using iterator = Value*;

        /// <summary>
        /// Type alias of the const value iterator for the map.
        /// </summary>
        using const_iterator = const Value*;

        /// <summary>
        /// Type alias of the reference of the value type stored in the map.
        /// </summary>
        using reference = Value&;

        /// <summary>
        /// Type alias of the const reference of the value type stored in the map.
        /// </summary>
        using const_reference = const Value&;

        /// <summary>
        /// Type alias of the pointer of the value type stored in the map.
        /// </summary>
        using pointer = Value*;

        /// <summary>
        /// Type alias of the const pointer of the value type stored in the map.
        /// </summary>
        using const_pointer = const Value*;

        /// <summary>
        /// Structure defining a key providing constant look up and erasure from the map.
        /// </summary>
        struct key
        {
            /// <summary>
            /// Index of the key in the map.
            /// </summary>
            index_type index;

            /// <summary>
            /// Generation of the key stored at the index in the map.
            /// </summary>
            generation_type generation;
        };

        /// <summary>
        /// Constructs a new, empty map.  The size and capacity of the map is guaranteed to be zero.
        /// </summary>
        slot_map();

        /// <summary>
        /// Constructs a copy of the empty map.  Keys fetched from <paramref name="other" /> are legal to use in this
        /// slot map and will point to an equivalent value.
        /// </summary>
        /// <param name="other">
        /// Slot map to copy from.
        /// </param>
        slot_map(const slot_map& other);

        /// <summary>
        /// Moves the contents of <paramref name="other" /> into this slot map, removing all values from
        /// <paramref name="other" />.  Keys fetched from <paramref name="other" /> are legal to use in this slot map
        /// and will point to an equivalent value.
        /// </summary>
        slot_map(slot_map&& other) noexcept;

        /// <summary>
        /// Deallocates all heap memory associated with the slot map and resets the size and capacity of the buffer.
        /// </summary>
        ~slot_map();

        /// <summary>
        /// Copies the values of <paramref name="rhs" /> into this.  If this map is not empty, all values stored in
        /// this map are released.  Keys fetched from <paramref name="rhs" /> are legal to use in this slot map and
        /// will point to an equivalent value.
        /// </summary>
        /// <param name="rhs">
        /// Slot map to copy contents from.
        /// </param>
        /// <returns>
        /// Reference to <c>this</c>.
        /// </returns>
        slot_map& operator=(const slot_map& rhs);

        /// <summary>
        /// Moves the values of <paramref name="rhs" /> into this.  If this map is not empty, all values stored in
        /// this map are released.  Keys fetched from <paramref name="rhs" /> are legal to use in this slot map and
        /// will point to an equivalent value.
        /// </summary>
        /// <param name="rhs">
        /// Slot map to move contents from.
        /// </param>
        /// <returns>
        /// Reference to <c>this</c>.
        /// </returns>
        slot_map& operator=(slot_map&& rhs);

        /// <summary>
        /// Gets if the slot map contains no values.  Equivalent to <c>size() == 0</c>.
        /// </summary>
        /// <returns>
        /// Is the map empty
        /// </returns>
        bool empty() const noexcept;

        /// <summary>
        /// Gets the number of values in the map.
        /// </summary>
        /// <returns>
        /// Number of values in the map.
        /// </returns>
        size_t size() const noexcept;

        /// <summary>
        /// Gets the number of values that the map can store without resizing its internal buffers.
        /// </summary>
        /// <returns>
        /// Number of values the map can store without resizing.
        /// </returns>
        size_t capacity() const noexcept;

        /// <summary>
        /// Gets the maximum number of values that can be stored in the map.
        /// </summary>
        /// <returns>
        /// Maximum number of values that can be stored in the map.
        /// </returns>
        size_t max_capacity() const noexcept;

        /// <summary>
        /// Ensures that the map can hold at least <paramref name="requested" /> values without requiring the backing
        /// buffers to resize.  If <paramref name="requested" /> is less than the capacity of the map, no action is
        /// performed.
        /// </summary>
        /// <param name="requested">
        /// Minimum capacity to reserve in the map.
        /// </param>
        void reserve(size_t requested);

        /// <summary>
        /// Gets an iterator to the first value in the slot map.  This is not guaranteed to be the first value
        /// inserted into the map.
        /// </summary>
        /// <returns>
        /// Iterator to the first value in the slot map.
        /// </returns>
        iterator begin() noexcept;

        //! @copydoc slot_map<Value,Index,Generation>::begin()
        const_iterator begin() const noexcept;

        /// <summary>
        /// Gets an iterator to the end of the slot map.  Dereferencing this iterator is undefined behavior.
        /// </summary>
        /// <returns>
        /// Iterator to the end of the slot map.
        /// </returns>
        iterator end() noexcept;

        //! @copydoc slot_map<Value,Index,Generation>::end()
        const_iterator end() const noexcept;

        //! @copydoc slot_map<Value,Index,Generation>::begin()
        const_iterator cbegin() const noexcept;

        //! @copydoc slot_map<Value,Index,Generation>::end()
        const_iterator cend() const noexcept;

        /// <summary>
        /// Gets a reference to the first value in the slot map.  This is not guaranteed to be the first value
        /// inserted into the map.  Results in undefined behavior if the map is empty.
        /// </summary>
        /// <returns>
        /// Reference to the first value.
        /// </returns>
        reference front();

        //! @copydoc slot_map<Value,Index,Generation>::front()
        const_reference front() const;

        /// <summary>
        /// Gets a reference to the last value in the slot map.  This is not guaranteed to be the last value
        /// inserted into the map.  Results in undefined behavior if the map is empty.
        /// </summary>
        /// <returns>
        /// Reference to the last value.
        /// </returns>
        /// \pre Map is not empty.
        reference back();

        //! @copydoc slot_map<Value,Index,Generation>::back()
        const_reference back() const;

        /// <summary>
        /// Gets a pointer to the buffer storing the values.
        /// </summary>
        /// <returns>
        /// Pointer to value buffer.
        /// </returns>
        pointer data() noexcept;
        
        //! @copydoc slot_map<Value,Index,Generation>::data()
        const_pointer data() const noexcept;

        /// <summary>
        /// Removes all values from the map.  All keys created from this map are now invalid for this instance of the
        /// map.
        /// </summary>
        /// \post Map size is zero.
        void clear();

        /// <summary>
        /// Inserts a value into map, returning a key for constant time lookup.
        /// </summary>
        /// <param name="value">
        /// Value to insert into the map.
        /// </param>
        /// <returns>
        /// Key that references the inserted value in the map.
        /// </returns>
        /// \post Map contains <paramref name="value" />
        /// \post Size of the map is increased by one.
        key insert(const value_type& value);

        //! @copydoc slot_map<Value,Index,Generation>::insert()
        key insert(value_type&& value);

        /// <summary>
        /// Removes a value from the map given its key.
        /// </summary>
        /// <param name="k">
        /// Key of the value to remove from the map.
        /// </param>
        /// <returns>
        /// <c>true</c> if the value of the key is removed, else <c>false</c>.
        /// </returns>
        /// \post Map does not contain the value referenced by <paramref name="k" />
        /// \post If the value was removed, the size of the map is decreased by one.
        bool erase(const key& k);

        /// <summary>
        /// Gets a reference to the value referenced by the key in the map.
        /// </summary>
        /// <param name="k">
        /// Key to fetch the value of.
        /// </param>
        /// <returns>
        /// Value referenced by the key.
        /// </returns>
        /// \pre The map contains <paramref name="k" />.
        reference get(const key& k) noexcept;

        /// <summary>
        /// Gets a pointer to the value referenced by the key in the map.
        /// </summary>
        /// <param name="k">
        /// Key to fetch the value of.
        /// </param>
        /// <returns>
        /// Pointer to the value in the map if the value exists, else <c>nullptr</c>.
        /// </returns>
        pointer try_get(const key& k) noexcept;

    private:
        key* m_slots;
        pointer m_data;
        size_t m_capacity;
        size_t m_size;
        Index m_free_slot_head;
        size_t* m_erase;

        key* allocate_slots(size_t count);
        void deallocate_slots(key* slots);
        pointer allocate_data_region(size_t count);
        void deallocate_data_region(pointer values);
        void destruct_data_region(pointer values);
        key create_new_key();
        key pop_free_key();

        void release();

        template <typename T>
        void copy(T* source, T* destination, size_t count);

        template <typename T>
        void move(T* source, T* destination, size_t count);

        static constexpr size_t implicit_list_stop = ~Index(0);
    }; // class slot_map

    template <typename Value, typename Index, typename Generation>
    inline slot_map<Value, Index, Generation>::slot_map()
        : m_slots(nullptr), m_data(nullptr), m_capacity(0), m_size(0), m_free_slot_head(implicit_list_stop),
          m_erase(nullptr)
    {
    }

    template <typename Value, typename Index, typename Generation>
    inline slot_map<Value, Index, Generation>::slot_map(const slot_map& other) : slot_map()
    {
        m_slots = allocate_slots(other.m_capacity);
        m_data = allocate_data(other.m_capacity);
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_free_slot_head = other.m_free_slot_head;
        m_erase = new size_t[m_capacity];

        copy(other.m_slots, m_slots, m_capacity);
        copy(other.m_data, m_data, m_size);
        copy(other.m_erase, m_erase, m_capacity);
    }

    template <typename Value, typename Index, typename Generation>
    inline slot_map<Value, Index, Generation>::slot_map(slot_map&& other) noexcept : slot_map()
    {
        m_slots = other.m_slots;
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_free_slot_head = other.m_free_slot_head;
        m_erase = other.m_erase;

        other.m_slots = nullptr;
        other.m_data = nullptr;
        other.m_erase = nullptr;
    }

    template <typename Value, typename Index, typename Generation>
    inline slot_map<Value, Index, Generation>::~slot_map()
    {
        release();
    }

    template <typename Value, typename Index, typename Generation>
    inline slot_map<Value, Index, Generation>& slot_map<Value, Index, Generation>::operator=(const slot_map& rhs)
    {
        release();

        m_slots = allocate_slots(rhs.m_capacity);
        m_data = allocate_data(rhs.m_capacity);
        m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;
        m_free_slot_head = rhs.m_free_slot_head;
        m_erase = new size_t[m_capacity];

        copy(rhs.m_slots, m_slots, m_capacity);
        copy(rhs.m_data, m_data, m_size);
        copy(rhs.m_erase, m_erase, m_capacity);

        return *this;
    }

    template <typename Value, typename Index, typename Generation>
    inline slot_map<Value, Index, Generation>& slot_map<Value, Index, Generation>::operator=(slot_map&& rhs)
    {
        release();

        m_slots = rhs.m_slots;
        m_data = rhs.m_data;
        m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;
        m_free_slot_head = rhs.m_free_slot_head;
        m_erase = rhs.m_erase;

        rhs.m_slots = nullptr;
        rhs.m_data = nullptr;
        rhs.m_erase = nullptr;

        return *this;
    }

    template <typename Value, typename Index, typename Generation>
    inline bool slot_map<Value, Index, Generation>::empty() const noexcept
    {
        return m_size == 0;
    }

    template <typename Value, typename Index, typename Generation>
    inline size_t slot_map<Value, Index, Generation>::size() const noexcept
    {
        return m_size;
    }

    template <typename Value, typename Index, typename Generation>
    inline size_t slot_map<Value, Index, Generation>::capacity() const noexcept
    {
        return m_capacity;
    }

    template <typename Value, typename Index, typename Generation>
    inline size_t slot_map<Value, Index, Generation>::max_capacity() const noexcept
    {
        return ~size_t(0);
    }

    template <typename Value, typename Index, typename Generation>
    inline void slot_map<Value, Index, Generation>::reserve(size_t sz)
    {
        // short circuit if trying to reserve smaller than currently allocated memory
        if (sz < m_capacity)
        {
            return;
        }

        key* new_slots = allocate_slots(sz);
        pointer new_payload_region = allocate_data_region(sz);
        size_t* new_erase = new size_t[sz];

        for (size_t i = m_capacity; i < sz; ++i)
        {
            new_slots[i].index = static_cast<Index>(i) + 1;
            new_slots[i].generation = 0;
        }

        if (m_capacity > 0)
        {
            copy(m_slots, new_slots, m_capacity);
            move(m_data, new_payload_region, m_size);
            copy(m_erase, new_erase, m_capacity);

            destruct_data_region(m_data);
            deallocate_data_region(m_data);
            deallocate_slots(m_slots);

            delete[] m_erase;
        }

        m_data = new_payload_region;
        m_slots = new_slots;
        m_erase = new_erase;

        // link the back of the new slot region to the front of the current linked free list
        m_slots[sz - 1].index = m_free_slot_head;
        m_free_slot_head = static_cast<Index>(m_capacity);

        m_capacity = sz;
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::iterator slot_map<Value, Index, Generation>::begin() noexcept
    {
        return m_data;
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::const_iterator slot_map<Value, Index, Generation>::begin()
        const noexcept
    {
        return m_data;
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::iterator slot_map<Value, Index, Generation>::end() noexcept
    {
        return m_data + m_size;
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::const_iterator slot_map<Value, Index, Generation>::end()
        const noexcept
    {
        return m_data + m_size;
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::const_iterator slot_map<Value, Index, Generation>::cbegin()
        const noexcept
    {
        return m_data;
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::const_iterator slot_map<Value, Index, Generation>::cend()
        const noexcept
    {
        return m_data + m_size;
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::reference slot_map<Value, Index, Generation>::front()
    {
        return *begin();
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::const_reference slot_map<Value, Index, Generation>::front()
        const
    {
        return *cbegin();
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::reference slot_map<Value, Index, Generation>::back()
    {
        return *(end() - 1);
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::const_reference slot_map<Value, Index, Generation>::back() const
    {
        return *(end() - 1);
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::pointer slot_map<Value, Index, Generation>::data() noexcept
    {
        return m_data;
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::const_pointer slot_map<Value, Index, Generation>::data()
        const noexcept
    {
        return m_data;
    }

    template <typename Value, typename Index, typename Generation>
    inline void slot_map<Value, Index, Generation>::clear()
    {
        destruct_data_region(m_data);

        for (size_t i = 0; i < capacity(); ++i)
        {
            const Generation current_generation = m_slots[i].generation;
            m_slots[i].generation += 1;
        }
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::key slot_map<Value, Index, Generation>::insert(
        const slot_map<Value, Index, Generation>::value_type& value)
    {
        key k = m_free_slot_head == implicit_list_stop ? create_new_key() : pop_free_key();
        m_slots[k.index].index = static_cast<Index>(size());
        const Index idx = m_slots[k.index].index;
        m_data[idx] = value;
        m_erase[m_size] = k.index;
        ++m_size;
        return k;
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::key slot_map<Value, Index, Generation>::insert(
        slot_map<Value, Index, Generation>::value_type&& value)
    {
        key k = m_free_slot_head == implicit_list_stop ? create_new_key() : pop_free_key();
        const Index idx = m_slots[k.index].index;
        m_data[idx] = move(value);
        m_erase[m_size] = k.index;
        ++m_size;
        return k;
    }

    template <typename Value, typename Index, typename Generation>
    inline bool slot_map<Value, Index, Generation>::erase(const key& k)
    {
        const Index idx = k.index;
        const Generation gen = k.generation;

        if (idx < capacity())
        {
            const key slot_key = m_slots[idx];
            if (gen == slot_key.generation)
            {
                const Index data_index = slot_key.index;
                (data() + data_index)->~Value();
                m_slots[idx].generation += 1;
                m_slots[idx].index = m_free_slot_head;
                m_free_slot_head = idx;

                m_erase[data_index] = m_erase[m_size - 1];

                if (data_index != size() - 1)
                {
                    *(data() + data_index) = containers::move(*(data() + size() - 1));
                    (data() + size() - 1)->~Value();
                    m_slots[m_erase[data_index]].index = data_index;
                }

                --m_size;

                return true;
            }
        }
        return false;
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::reference slot_map<Value, Index, Generation>::get(
        const key& k) noexcept
    {
        return *try_get(k);
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::pointer slot_map<Value, Index, Generation>::try_get(
        const key& k) noexcept
    {
        const Index idx = k.index;
        const Generation gen = k.generation;

        if (idx < capacity())
        {
            const key slot_key = m_slots[idx];
            if (gen == slot_key.generation)
            {
                return m_data + slot_key.index;
            }
        }
        return nullptr;
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::key* slot_map<Value, Index, Generation>::allocate_slots(
        size_t count)
    {
        static constexpr size_t key_size = sizeof(key);
        char* buffer = new char[key_size * count];
        return reinterpret_cast<key*>(buffer);
    }

    template <typename Value, typename Index, typename Generation>
    inline void slot_map<Value, Index, Generation>::deallocate_slots(key* slots)
    {
        char* buffer = reinterpret_cast<char*>(slots);
        delete[] buffer;
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::pointer slot_map<Value, Index,
                                                                         Generation>::allocate_data_region(size_t count)
    {
        static constexpr size_t data_size = sizeof(Value);
        char* buffer = new char[data_size * count];
        return reinterpret_cast<pointer>(buffer);
    }

    template <typename Value, typename Index, typename Generation>
    inline void slot_map<Value, Index, Generation>::deallocate_data_region(pointer values)
    {
        char* data = reinterpret_cast<char*>(values);
        delete[] data;
    }

    template <typename Value, typename Index, typename Generation>
    inline void slot_map<Value, Index, Generation>::destruct_data_region(pointer values)
    {
        for (size_t i = 0; i < size(); ++i)
        {
            (data() + i)->~Value();
        }
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::key slot_map<Value, Index, Generation>::create_new_key()
    {
        reserve(m_capacity + 1);
        const key k = pop_free_key();
        m_slots[k.index].index = static_cast<Index>(size());
        return k;
    }

    template <typename Value, typename Index, typename Generation>
    inline typename slot_map<Value, Index, Generation>::key slot_map<Value, Index, Generation>::pop_free_key()
    {
        key k;
        k.index = m_free_slot_head;
        k.generation = m_slots[m_free_slot_head].generation;
        m_free_slot_head = m_slots[m_free_slot_head].index;
        return k;
    }

    template <typename Value, typename Index, typename Generation>
    inline void slot_map<Value, Index, Generation>::release()
    {
        if (m_data != nullptr)
        {
            destruct_data_region(m_data);
            deallocate_data_region(m_data);
            m_data = nullptr;
        }

        if (m_slots != nullptr)
        {
            deallocate_slots(m_slots);
            m_slots = nullptr;
        }

        if (m_erase != nullptr)
        {
            delete[] m_erase;
            m_erase = nullptr;
        }

        m_size = 0;
        m_capacity = 0;
        m_free_slot_head = implicit_list_stop;
    }

    template <typename Value, typename Index, typename Generation>
    template <typename T>
    inline void slot_map<Value, Index, Generation>::copy(T* source, T* destination, size_t count)
    {
        for (size_t i = 0; i < count; ++i)
        {
            destination[i] = source[i];
        }
    }

    template <typename Value, typename Index, typename Generation>
    template <typename T>
    inline void slot_map<Value, Index, Generation>::move(T* source, T* destination, size_t count)
    {
        for (size_t i = 0; i < count; ++i)
        {
            destination[i] = containers::move(source[i]);
        }
    }
} // namespace containers

#endif // slot_map_hpp__
