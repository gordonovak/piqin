#pragma once
#include <string>

namespace geng {
    /**
     * @brief The Vertex is the fundamental coordinate system of the engine. @code x@endcode and @code y@endcode
     * determine position on the screen, and @code z@endcode determines rendering order.
     * @details The Vertex has many nice features that makes it easy to work with.
     * It has all the standard operator overloads you would expect, and some nice ones like @code %@endcode and @code %=@endcode.
     * Vertex also has a plethora of convenient utility functions:
     * - @code set(x,y,z)@endcode › Sets the coordinates of the vertex
     * - @code unit()@endcode › Returns the unit vector of this veretx
     * - @code mag()@endcode › Returns the absolute magnitude of the vertex
     * - @code xy_mag()@endcode › Returns the magnitude of the x-y coordinates of the vertex
     * - @code dist(Vertex v)@endcode › Returns the distance from one Vertex to another.
     * - @code to_zero()@endcode › Turns all entries in the Vertex to zero
     * - @code is_zero()@endcode › Returns true if the vertex's magnitude is zero
     * - @code randomize(std::pair range)@endcode › Randomizes all elements in teh vertex in accordance with the range
     * @note There exists three to_string functions. Two are overloads for @code +@endcode and @code <<@endcode, and there also exists a generic @code to_string()@endcode.
     * @warning The == comparison for Vertexes only compares to the fourth decimal place.
     */
    struct Vertex {
        float x = 0;
        float y = 0;
        float z = 0;

        // Constructor for position
        Vertex() = default;
        /// Z Defaults to 0 in this constructor
        Vertex(const float x, const float y) : x(x), y(y), z(0) {}
        Vertex(const float x, const float y, const float z) : x(x), y(y), z(z) {}

        // Member functions
        /// Sets each coordinate of the vector
        void set(int xpos, int ypos, int zpos);
        /// Calculates the unit vector of this vertex
        [[nodiscard]] Vertex unit() const;
        /// Finds the magnitude of this Vertex
        [[nodiscard]] float mag() const;
        /// Finds the magnitude of the x and y coordinates together
        [[nodiscard]] float xy_mag() const;
        /// Finds the distance of this Vertex to another
        [[nodiscard]] float dist(Vertex v) const;
        /// Turns all values in the vertex to 0.f
        void to_zero();
        /// Resturns true if a Vertex is zero
        [[nodiscard]] bool is_zero() const;
        /// Randomizes the values in a vertex. Specify a range from low to high. If no range is specified, randomness will be from -1 to 1.
        void randomize(std::pair<float, float> range = std::make_pair(0, 0));

        // Operator overloads for Vertexes
        // Operations with other Vertexes
        Vertex operator+(Vertex other) const;
        Vertex operator-(Vertex other) const;
        Vertex operator*(float scalar) const;
        Vertex operator/(float scalar) const;
        Vertex operator%(int scalar) const;
        // Self operations
        void operator+=(Vertex other);
        void operator-=(Vertex other);
        void operator*=(float scalar);
        void operator%=(int scalar);

        float operator*(Vertex other);

        void operator/=(float scalar);
        float& operator[](int index);
        void operator=(Vertex other); // NOLINT(*-unconventional-assign-operator)

        // To string methods below
        /// Add a vertex to a string
        std::string operator+(std::string s) const;
        /// Pipe a vertex with a string
        std::string operator<<(std::string s) const;
        /// Converts a vertex to a string.
        [[nodiscard]] std::string to_string() const;
        /// Checks to the fourth decimal if two Vertexes are equal.
        bool operator==(Vertex other) const;
    };
}