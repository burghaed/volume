//
//  Vector4.h
//  SubVoxeling
//
//  Created by Burghardt, Eduard on 10.10.12.
//
//

#ifndef SubVoxeling_Vector4_h
#define SubVoxeling_Vector4_h

template <class T = double>
class Vector4 {
public:
    /*! Initializes the Vector to zeroes (not that it makes sense) */
    Vector4(void) {
        c[0] = c[1] = c[2] = T();
        c[3] = T( static_cast< T >( 1.0 ) );
    };
    
    /*! Initializes the Vector to the given T */
    Vector4( T s) {
        c[0] = c[1] = c[2] = c[3] = s;
    };
    
    /*! Initializes the Vector with the supplied components */
    Vector4(T v0, T v1, T v2) {
        c[0] = v0; c[1] = v1; c[2] = v2; c[3] = static_cast< T >( 1 );
    };
    
    /*! Initializes the Vector with the supplied components */
    Vector4(T v0, T v1, T v2, T v3) {
        c[0] = v0; c[1] = v1; c[2] = v2; c[3] = v3;
    };
    
    /*! Initiliazes the Vector  the supplied components */
    Vector4(T v[4]) {
        c[0] = v[0]; c[1] = v[1]; c[2] = v[2]; c[3] = v[3];
    };

    Vector4<T> operator - () const {
        return Vector4<T> (-c[0], -c[1], -c[2], -c[3]);
    };
    
    /*! Adds up this Vector and the supplied one componentwise.  Returns a
     newly created Vector. */
    Vector4<T> operator + (const Vector4<T> &v) const {
        return Vector4<T> (c[0] + v.c[0],
                                c[1] + v.c[1],
                                c[2] + v.c[2],
                                c[3] + v.c[3]);
    };
    
    /*! Substracts the given Vector \e from this Vector.  Returns a newly
     created Vector. */
    Vector4<T> operator - (const Vector4<T> &v) const {
        return Vector4<T> (c[0] - v.c[0],
                                c[1] - v.c[1],
                                c[2] - v.c[2],
                                c[3] - v.c[3]);
    };
    
    /*! Multiplies this Vector with the given T componentwise.
     Returns a newly created Vector. */
    Vector4<T> operator * (const T s) const {
        return T4<T> (c[0]*s, c[1]*s, c[2]*s, c[3]*s);
    };
    
    /*! Multiplies this T with the T componentwise (T
     product). */
    T operator * (const T4<T> &v) const {
        return c[0]*v.c[0] + c[1]*v.c[1] + c[2]*v.c[2] + c[3]*v.c[3];
    };
    
    /*! Returns a reference to the given component */
    T & operator[] (unsigned int i) {
        assert(i < 4);
        return c[i];
    };
    
    /*! Returns a constant reference to the given component */
    const T & operator[] (unsigned int i) const {
        assert(i < 4);
        return c[i];
    };
    
    /*! Computes the normal of the T. */
    T normal(void) {
        return sqrt(c[0]*c[0] + c[1]*c[1] + c[2]*c[2] + c[3]*c[3]);
    };
    
    /*! Normalizes \e this Vector and returns the normal. */
    T normalize(void) {
        T n = sqrt(c[0]*c[0] + c[1]*c[1] + c[2]*c[2] + c[3]*c[3]);
        if (n > 0)
            c[0] /= n; c[1] /= n; c[2] /= n; c[3] /= n;
        return n;
    };
    
private:
    /*! Components */
    T c[4];
};



#endif
