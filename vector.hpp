#include <iostream>
#include <cmath>

#ifndef VECTORS_HPP
#define VECTORS_HPP

template <typename T>
struct vec2 {
    T x, y;

    vec2<T>(T x, T y) : x(x), y(y){};
    vec2<T>(T w) : x(w), y(w){};

    template <typename O>
    vec2<T>& operator=(vec2<O> &v)
    {
        x = (T)v.x; y = (T)v.y;
        return *this;
    };

    vec2<double> normalize() const {
        double length = sqrt(x*x + y*y);
        return vec2<double>(x/length, y/length);
    }

    vec2<T> abs() const {
        return vec2<T>(std::abs(x), std::abs(y));
    }

    T length() const {
        return sqrt(x*x + y*y);
    }

    T max() const {
        return std::max(x, y);
    }

    T min() const {
        return std::min(x, y);
    }

    vec2<T> max(vec2<T>& v) const {
        return vec2<T>(std::max(x, v.x), std::max(y, v.y));
    }

    vec2<T> min(vec2<T>& v) const {
        return vec2<T>(std::min(x, v.x), std::min(y, v.y));
    }

    vec2<T> mix(vec2<T>& v, T a) const {
        return vec2<T>(x*(1-a) + v.x*a, y*(1-a) + v.y*a);
    }

    operator vec2<double>() const {
        return vec2<double>((double)x, (double)y);
    }

    operator vec2<float>() const {
        return vec2<float>((float)x, (float)y);
    }

    operator vec2<int>() const {
        return vec2<int>((int)x, (int)y);
    }
};

typedef vec2<float> float2;

template <typename T>
std::ostream& operator<<(std::ostream& os, const vec2<T>& u)
{
    os << "vec2(" << u.x << ", " << u.y << ")";
    return os;
};

template <typename T, typename O>
vec2<T> operator+(vec2<T> u, const vec2<O> &v)
{
    u.x += (T)v.x; u.y += (T)v.y; return u;
}

template <typename T, typename O>
vec2<T> operator-(vec2<T> u, const vec2<O> &v)
{
    u.x -= (T)v.x; u.y -= (T)v.y; return u;
};

template <typename T, typename O>
vec2<T> operator*(vec2<T> u, const vec2<O> &v)
{
    u.x *= (T)v.x; u.y *= (T)v.y; return u;
};

template <typename T, typename O>
vec2<T> operator/(vec2<T> u, const vec2<O> &v)
{
    u.x /= (T)v.x; u.y /= (T)v.y; return u;
};

template <typename T, typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
vec2<T> operator+(vec2<T> u, O s)
{
    u.x += (T)s; u.y += (T)s; return u;
}

template <typename T, typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
vec2<T> operator-(vec2<T> u, O s)
{
    u.x -= (T)s; u.y -= (T)s; return u;
}

template <typename T, typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
vec2<T> operator*(vec2<T> u, O s)
{
    u.x *= (T)s; u.y *= (T)s; return u;
}

template <typename T, typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
vec2<T> operator/(vec2<T> u, O s)
{
    u.x /= (T)s; u.y /= (T)s; return u;
}

template <typename T>
struct vec3
{
    T x, y, z;

    vec3<T>() : x(0), y(0), z(0){};
    vec3<T>(T x, T y, T z) : x(x), y(y), z(z){};
    vec3<T>(T w) : x(w), y(w), z(w){};

    vec2<T> xy() const {
        return vec2<T>(x, y);
    }

    vec2<T> xz() const {
        return vec2<T>(x, z);
    }

    vec2<T> yz() const {
        return vec2<T>(y, z);
    }

    void xy(vec2<T> v) {
        x = v.x; y = v.y;
    }

    void xz(vec2<T> v) {
        x = v.x; z = v.y;
    }

    void yz(vec2<T> v) {
        y = v.x; z = v.y;
    }

    template <typename O>
    vec3<T>& operator=(vec3<O> &v)
    {
        x = (T)v.x; y = (T)v.y; z = (T)v.z;
        return *this;
    };

    vec3<double> normalize() const {
        std::cerr << "x: " << x << " y: " << y << " z: " << z << std::endl;
        double length = sqrt(x*x + y*y + z*z);
        std::cerr << "length: " << length << std::endl;
        std::cerr << "x: " << x << " y: " << y << " z: " << z << std::endl;
        return vec3<double>(x/length, y/length, z/length);
    }

    vec3<double> abs() const {
        return vec3<double>(std::abs(x), std::abs(y), std::abs(z));
    }

    double length() const {
        return sqrt(x*x + y*y + z*z);
    }

    double max() const {
        return std::max(std::max(x, y), z);
    }

    double min() const {
        return std::min(std::min(x, y), z);
    }

    vec3<T> max(vec3<T>& v) const {
        return vec3<T>(std::max(x, v.x), std::max(y, v.y), std::max(z, v.z));
    }

    vec3<T> min(vec3<T>& v) const {
        return vec3<T>(std::min(x, v.x), std::min(y, v.y), std::min(z, v.z));
    }

    vec3<T> mix(vec3<T>& v, T a) const {
        return vec3<T>(x*(1-a) + v.x*a, y*(1-a) + v.y*a, z*(1-a) + v.z*a);
    }

    operator vec3<double>() const {
        return vec3<double>((double)x, (double)y, (double)z);
    }

    operator vec3<float>() const {
        return vec3<float>((float)x, (float)y, (float)z);
    }

    operator vec3<int>() const {
        return vec3<int>((int)x, (int)y, (int)z);
    }
};

typedef vec3<float> float3;
typedef vec3<unsigned char>  byte3;

struct mat3 {
    float3 x, y, z;
    mat3(float3 x, float3 y, float3 z) : x(x), y(y), z(z) {};
    mat3(float x, float y, float z) : x(float3(x)), y(float3(y)), z(float3(z)) {};
    mat3(float w) : x(float3(w)), y(float3(w)), z(float3(w)) {};
    mat3() : x(float3(0)), y(float3(0)), z(float3(0)) {};

    float3 operator[](int i) const {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const vec3<T>& u)
{
    os << "vec3(" << u.x << ", " << u.y << ", " << u.z << ")";
    return os;
};

template <typename T, typename O>
vec3<T> operator+(vec3<T> u, const vec3<O> &v)
{
    u.x += (T)v.x; u.y += (T)v.y; u.z += (T)v.z; return u;
}

template <typename T, typename O>
vec3<T> operator-(vec3<T> u, const vec3<O> &v)
{
    u.x -= (T)v.x; u.y -= (T)v.y; u.z -= (T)v.z; return u;
};

template <typename T, typename O>
vec3<T> operator*(vec3<T> u, const vec3<O> &v)
{
    u.x *= (T)v.x; u.y *= (T)v.y; u.z *= (T)v.z; return u;
};

float3 operator*(const mat3& u, const float3& v) {
    return float3(u.x.x*v.x + u.y.x*v.y + u.z.x*v.z,
                  u.x.y*v.x + u.y.y*v.y + u.z.y*v.z,
                  u.x.z*v.x + u.y.z*v.y + u.z.z*v.z);
}

template <typename T, typename O>
vec3<T> operator/(vec3<T> u, const vec3<O> &v)
{
    u.x /= (T)v.x; u.y /= (T)v.y; u.z /= (T)v.z; return u;
};


template <typename T, typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
vec3<T> operator+(vec3<T> u, O s)
{
    u.x += (T)s; u.y += (T)s; u.z += (T)s; return u;
}

template <typename T, typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
vec3<T> operator-(vec3<T> u, O s)
{
    u.x -= (T)s; u.y -= (T)s; u.z -= (T)s; return u;
}

template <typename T, typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
vec3<T> operator*(vec3<T> u, O s)
{
    u.x *= (T)s; u.y *= (T)s; u.z *= (T)s; return u;
}

template <typename T, typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
vec3<T> operator/(vec3<T> u, O s)
{
    u.x /= (T)s; u.y /= (T)s; u.z /= (T)s; return u;
}

template <typename T>
struct vec4 {
    T x, y, z, w;

    vec4<T>(T x, T y, T z, T w) {
        this->x = x; this->y = y; this->z = z; this->w = w;
    };
    vec4<T>(T w) {
        this->x = w; this->y = w; this->z = w; this->w = w;
    };
    vec4<T>(vec3<T> xyz, T w) {
        this->xyz = xyz; this->w = w;
    };

    vec3<T> xyz() const {
        return vec3<T>(x, y, z);
    }

    vec3<T> xzw() const {
        return vec3<T>(x, z, w);
    }

    vec3<T> xyw() const {
        return vec3<T>(x, y, w);
    }

    vec3<T> yzw() const {
        return vec3<T>(y, z, w);
    }

    void xyz(vec3<T> v) {
        x = v.x; y = v.y; z = v.z;
    }

    void xzw(vec3<T> v) {
        x = v.x; z = v.y; w = v.z;
    }

    void xyw(vec3<T> v) {
        x = v.x; y = v.y; w = v.z;
    }

    void yzw(vec3<T> v) {
        y = v.x; z = v.y; w = v.z;
    }


    template <typename O>
    vec4<T>& operator=(vec4<O> &v)
    {
        x = (T)v.x; y = (T)v.y; z = (T)v.z; w = (T)v.w;
        return *this;
    };

    operator vec4<double>() const {
        return vec4<double>((double)x, (double)y, (double)z, (double)w);
    }

    operator vec4<float>() const {
        return vec4<float>((float)x, (float)y, (float)z, (float)w);
    }

    operator vec4<int>() const {
        return vec4<int>((int)x, (int)y, (int)z, (int)w);
    }

    template <typename O>
    operator vec4<vec4<O>>() const {
        return vec4<vec4<O>>((vec4<O>)x, (vec4<O>)y, (vec4<O>)z, (vec4<O>)w);
    }

    vec4<double> normalize() const {
        double length = sqrt(x*x + y*y + z*z + w*w);
        return vec4<double>(x/length, y/length, z/length, w/length);
    }

    vec4<double> abs() const {
        return vec4<double>(std::abs(x), std::abs(y), std::abs(z), std::abs(w));
    }

    double min() const {
        return std::min(std::min(std::min(x, y), z), w);
    }

    double max() const {
        return std::max(std::max(std::max(x, y), z), w);
    }

    double length() const {
        return sqrt(x*x + y*y + z*z + w*w);
    }

    vec4<T> max(const vec4<T> &v) const {
        return vec4<T>(std::max(x, v.x), std::max(y, v.y), std::max(z, v.z), std::max(w, v.w));
    }

    vec4<T> min(const vec4<T> &v) const {
        return vec4<T>(std::min(x, v.x), std::min(y, v.y), std::min(z, v.z), std::min(w, v.w));
    }

    vec4<T> mix(const vec4<T> &v, double a) const {
        return vec4<T>(x*(1-a) + v.x*a, y*(1-a) + v.y*a, z*(1-a) + v.z*a, w*(1-a) + v.w*a);
    }

    template <typename O>
    vec4 operator+=(const vec4<O> &v)
    {
        x += (T)v.x; y += (T)v.y; z += (T)v.z; w += (T)v.w; return *this;
    }

    template <typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
    vec4 operator+=(O s)
    {
        x += (T)s; y += (T)s; z += (T)s; w += (T)s; return *this;
    }

    template <typename O>
    vec4 operator-=(const vec4<O> &v)
    {
        x -= (T)v.x; y -= (T)v.y; z -= (T)v.z; w -= (T)v.w; return *this;
    }

    template <typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
    vec4 operator-=(O s)
    {
        x -= (T)s; y -= (T)s; z -= (T)s; w -= (T)s; return *this;
    }

    template <typename O>
    vec4 operator*=(const vec4<O> &v)
    {
        x *= (T)v.x; y *= (T)v.y; z *= (T)v.z; w *= (T)v.w; return *this;
    }

    template <typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
    vec4 operator*=(O s)
    {
        x *= (T)s; y *= (T)s; z *= (T)s; w *= (T)s; return *this;
    }

    template <typename O>
    vec4 operator/=(const vec4<O> &v)
    {
        x /= (T)v.x; y /= (T)v.y; z /= (T)v.z; w /= (T)v.w; return *this;
    }

    template <typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
    vec4 operator/=(O s)
    {
        x /= (T)s; y /= (T)s; z /= (T)s; w /= (T)s; return *this;
    }
};

typedef vec4<float> float4;
struct mat4 {
    float4 rows[4];



    mat4(float4 row1, float4 row2, float4 row3, float4 row4) : rows{row1, row2, row3, row4} {}


    
    float4 operator[](int i) const {
        return rows[i];
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const vec4<T>& u)
{
    os << "vec4(" << u.x << ", " << u.y << ", " << u.z << ", " << u.w << ")";
    return os;
};

template <typename T, typename O>
vec4<T> operator+(vec4<T> u, const vec4<O> &v)
{
    u.x += (T)v.x; u.y += (T)v.y; u.z += (T)v.z; u.w += (T)v.w; return u;
}

template <typename T, typename O>
vec4<T> operator-(vec4<T> u, const vec4<O> &v)
{
    u.x -= (T)v.x; u.y -= (T)v.y; u.z -= (T)v.z; u.w -= (T)v.w; return u;
};


float4 operator*(mat4 u, float4 v) {
    float4 ret(0);
    ret.x = u[0].x * v.x + u[1].x * v.y + u[2].x * v.z + u[3].x * v.w;
    ret.y = u[0].y * v.x + u[1].y * v.y + u[2].y * v.z + u[3].y * v.w;
    ret.z = u[0].z * v.x + u[1].z * v.y + u[2].z * v.z + u[3].z * v.w;
    ret.w = u[0].w * v.x + u[1].w * v.y + u[2].w * v.z + u[3].w * v.w;
    return ret;
}

template <typename T, typename O>
vec4<T> operator*(vec4<T> u, const vec4<O> &v)
{
    u.x *= (T)v.x; u.y *= (T)v.y; u.z *= (T)v.z; u.w *= (T)v.w; return u;
};


template <typename T, typename O>
vec4<T> operator/(vec4<T> u, const vec4<O> &v)
{
    u.x /= (T)v.x; u.y /= (T)v.y; u.z /= (T)v.z; u.w /= (T)v.w; return u;
};

template <typename T, typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
vec4<T> operator+(vec4<T> u, O s)
{
    u.x += (T)s; u.y += (T)s; u.z += (T)s; u.w += (T)s; return u;
}

template <typename T, typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
vec4<T> operator-(vec4<T> u, O s)
{
    u.x -= (T)s; u.y -= (T)s; u.z -= (T)s; u.w -= (T)s; return u;
}

template <typename T, typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
vec4<T> operator*(vec4<T> u, O s)
{
    u.x *= (T)s; u.y *= (T)s; u.z *= (T)s; u.w *= (T)s; return u;
}

template <typename T, typename O, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
vec4<T> operator/(vec4<T> u, O s)
{
    u.x /= (T)s; u.y /= (T)s; u.z /= (T)s; u.w /= (T)s; return u;
}


template <typename T>
T length(vec2<T> v) {
    return v.length();
}

template <typename T>
T length(vec3<T> v) {
    return v.length();
}

template <typename T>
T length(vec4<T> v) {
    return v.length();
}

template <typename T>
T abs(vec2<T> v) {
    return v.abs();
}

template <typename T>
T abs(vec3<T> v) {
    return v.abs();
}

template <typename T>
T abs(vec4<T> v) {
    return v.abs();
}

template <typename T>
T max(vec2<T> v) {
    return v.max();
}

template <typename T>
T max(vec3<T> v) {
    return v.max();
}

template <typename T>
T max(vec4<T> v) {
    return v.max();
}

template <typename T>
T min(vec2<T> v) {
    return v.min();
}

template <typename T>
T min(vec3<T> v) {
    return v.min();
}

template <typename T>
T min(vec4<T> v) {
    return v.min();
}

template <typename T>
vec2<T> max(vec2<T> v1, vec2<T> v2) {
    return v1.max(v2);
}

template <typename T>
vec3<T> max(vec3<T> v1, vec3<T> v2) {
    return v1.max(v2);
}

template <typename T>
vec4<T> max(vec4<T> v1, vec4<T> v2) {
    return v1.max(v2);
}

template <typename T>
vec2<T> mix(vec2<T> v1, vec2<T> v2, T a) {
    return v1.mix(v2, a);
}

template <typename T>
vec3<T> mix(vec3<T> v1, vec3<T> v2, T a) {
    return v1.mix(v2, a);
}

template <typename T>
vec4<T> mix(vec4<T> v1, vec4<T> v2, T a) {
    return v1.mix(v2, a);
}

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
T step(T edge, T x) {
    return x < edge ? 0 : 1;
}

vec3<float> rgb(int r, int g, int b) {
    return vec3<float>(r / 255.0f, g / 255.0f, b / 255.0f);
}

template <typename T, typename O, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type, typename = typename std::enable_if<std::is_arithmetic<O>::value>::type>
T clamp(T x, O min, O max) {
    return x < (T)min ? (T)min : x >(T) max ? (T)max : x;
}

#endif