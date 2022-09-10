/*
 * Copyright (c) 2022 Pavel I. Kryukov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef VECTOR_VOID_H
#define VECTOR_VOID_H

#include <cstddef>
#include <stdexcept>

struct Void
{
    const auto operator<=>(const Void&) const = default;
};

class VectorVoid : private Void
{
public:
    /*
     * Member types
     */
    using value_type      = Void;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = Void&;
    using const_reference = const Void&;

    /*
     * Constructors, destructors, assignments
     */
    VectorVoid() noexcept = default;
    explicit VectorVoid(size_type v) noexcept : s(v) { }
    VectorVoid(size_type v, Void) noexcept : VectorVoid(v) { }

    VectorVoid(const VectorVoid&) noexcept = default;

    VectorVoid(VectorVoid&& src) noexcept : VectorVoid(src.size())
    {
        src.clear();
    }

    /*
     * Element access
     */
    Void& at(size_type idx)
    {
        if (idx >= size())
            throw std::out_of_range("Invalid VectorVoid access");

        return *this;
    }

    const Void& at(size_type idx) const
    {
        if (idx >= size())
            throw std::out_of_range("Invalid VectorVoid access");

        return *this;
    }

    Void& operator[](size_type) noexcept
    {
        return *this;
    }

    const Void& operator[](size_type) const noexcept
    {
        return *this;
    }

    Void& front() noexcept
    {
        return *this;
    }

    const Void& front() const noexcept
    {
        return *this;
    }

    Void& back() noexcept
    {
        return *this;
    }

    const Void& back() const noexcept
    {
        return *this;
    }

    // Void* data() noexcept;
    // const Void* data() noexcept;

    /*
     * Capacity
     */
    bool empty() const noexcept
    {
        return s == 0;
    }

    size_type size() const noexcept
    {
        return s;
    }

    size_type max_size() const noexcept
    {
        return SIZE_MAX;
    }

    void reserve() const {}

    size_type capacity() const
    {
        return size();
    }

    void shrink_to_fit() const {}

    /*
     * Modifiers
     */
    void clear() noexcept
    {
        s = 0;
    }

    void push_back(const Void&) noexcept
    {
        ++s;
    }

    void push_back(Void&&) noexcept
    {
        ++s;
    }

    Void& emplace_back() noexcept
    {
        ++s;
        return *this;
    }

    Void& emplace_back(Void&&) noexcept
    {
        ++s;
        return *this;
    }

    void pop_back() noexcept
    {
        --s;
    }

    void resize(size_type count) noexcept
    {
        s = count;
    }

    void resize(size_type count, const Void&) noexcept
    {
        resize(count);
    }

    void swap(VectorVoid& other)
    {
        std::swap(other.s, s);
    }

private:
    size_type s = 0;
};

#endif
