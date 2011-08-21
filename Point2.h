#pragma once

#include <assert.h>
#include "base.h"

namespace GGL {

/** \addtogroup space */
/*@{*/
    /**
        The templated class for representing a point in 2D space.
        The class is templated over the ScalarType class that is used to represent coordinates. 
				All the usual operator overloading (* + - ...) is present. 
     */
template <class P2ScalarType> class Point2
{
protected:
  /// The only data member. Hidden to user.
	P2ScalarType _v[2];
public:
	  /// the scalar type 
	typedef P2ScalarType ScalarType;
	enum {Dimension = 2};

//@{

  /** @name Access to Coords. 
   access to coords is done by overloading of [] or explicit naming of coords (X,Y,)
	 ("p[0]" or "p.X()" are equivalent) **/
	inline const ScalarType &X() const {return _v[0];} 
	inline const ScalarType &Y() const {return _v[1];}
	inline ScalarType &X() {return _v[0];}
	inline ScalarType &Y() {return _v[1];}
  inline const ScalarType * V() const
	{
		return _v;
	}
	inline ScalarType & V( const int i )
	{
		assert(i>=0 && i<2);
		return _v[i];
	}
	inline const ScalarType & V( const int i ) const
	{
		assert(i>=0 && i<2);
		return _v[i];
	}
	inline const ScalarType & operator [] ( const int i ) const
	{
		assert(i>=0 && i<2);
		return _v[i];
	}
	inline ScalarType & operator [] ( const int i )
	{
		assert(i>=0 && i<2);
		return _v[i];
	}
//@}
	  /// empty constructor (does nothing)
	inline Point2 () { }
	  /// x,y constructor
	inline Point2 ( const ScalarType nx, const ScalarType ny )
	{
			_v[0] = nx; _v[1] = ny;
	}
	  /// copy constructor
	inline Point2 ( Point2 const & p)
	{   
			_v[0]= p._v[0];    _v[1]= p._v[1];
	}
	  /// copy
	inline Point2 & operator =( Point2 const & p)
	{
			_v[0]= p._v[0]; _v[1]= p._v[1];
			return *this;
	}
	  /// sets the point to (0,0)
	inline void Zero()
	{ _v[0] = 0;_v[1] = 0;}
	  /// dot product
	inline ScalarType operator * ( Point2 const & p ) const
	{
			return ( _v[0]*p._v[0] + _v[1]*p._v[1] );
	}
	  /// cross product
	inline ScalarType operator ^ ( Point2 const & p ) const
	{
			return _v[0]*p._v[1] - _v[1]*p._v[0];
	} 
//@{
	 /** @name Linearity for 2d points (operators +, -, *, /, *= ...) **/
	inline Point2 operator + ( Point2 const & p) const
	{ 
			return Point2<ScalarType>( _v[0]+p._v[0], _v[1]+p._v[1] );
	}
	inline Point2 operator - ( Point2 const & p) const
	{
			return Point2<ScalarType>( _v[0]-p._v[0], _v[1]-p._v[1] );
	}
	inline Point2 operator * ( const ScalarType s ) const
	{
			return Point2<ScalarType>( _v[0] * s, _v[1] * s );
	}
	inline Point2 operator / ( const ScalarType s ) const
	{
			return Point2<ScalarType>( _v[0] / s, _v[1] / s );
	}
	inline Point2 & operator += ( Point2 const & p)
	{
			_v[0] += p._v[0];    _v[1] += p._v[1];
			return *this;
	}
	inline Point2 & operator -= ( Point2 const & p)
	{
			_v[0] -= p._v[0];    _v[1] -= p._v[1];
			return *this;
	}
	inline Point2 & operator *= ( const ScalarType s )
	{
			_v[0] *= s;    _v[1] *= s;
			return *this;
	}
	inline Point2 & operator /= ( const ScalarType s )
	{
			_v[0] /= s;    _v[1] /= s;
			return *this;
	}
 //@}
	  /// returns the norm (Euclidian)
	inline ScalarType Norm( void ) const
	{
		return Math::Sqrt( _v[0]*_v[0] + _v[1]*_v[1] );
	}
	  /// returns the squared norm (Euclidian)
	inline ScalarType SquaredNorm( void ) const
	{
			return ( _v[0]*_v[0] + _v[1]*_v[1] );
	}
	inline Point2 & Scale( const ScalarType sx, const ScalarType sy )
	{
		_v[0] *= sx;
		_v[1] *= sy;
		return * this;
	}
	  /// normalizes, and returns itself as result
	inline Point2 & Normalize( void )
	{
			ScalarType n = Math::Sqrt(_v[0]*_v[0] + _v[1]*_v[1]);
			if(n>0.0) {	_v[0] /= n;	_v[1] /= n; }
			return *this;
	}
	  /// points equality
	inline bool operator == ( Point2 const & p ) const
	{
			return (_v[0]==p._v[0] && _v[1]==p._v[1]);
	} 
	  /// disparity between points
	inline bool operator != ( Point2 const & p ) const
	{
			return ( (_v[0]!=p._v[0]) || (_v[1]!=p._v[1]) );
	}
	  /// lexical ordering
	inline bool operator <  ( Point2 const & p ) const
	{
			return	(_v[1]!=p._v[1])?(_v[1]<p._v[1]):
							(_v[0]<p._v[0]);
	}
	  /// lexical ordering
	inline bool operator >  ( Point2 const & p ) const
	{
			return	(_v[1]!=p._v[1])?(_v[1]>p._v[1]):
							(_v[0]>p._v[0]);
	}
	  /// lexical ordering
	inline bool operator <= ( Point2 const & p ) const
	{
			return	(_v[1]!=p._v[1])?(_v[1]< p._v[1]):
							(_v[0]<=p._v[0]);
	}
	  /// lexical ordering
	inline bool operator >= ( Point2 const & p ) const
	{
			return	(_v[1]!=p._v[1])?(_v[1]> p._v[1]):
							(_v[0]>=p._v[0]);
	}
	  /// returns the distance to another point p
	inline ScalarType Distance( Point2 const & p ) const
	{
			return Norm(*this-p);
	}
	  /// returns the suqared distance to another point p
	inline ScalarType SquaredDistance( Point2 const & p ) const
	{
			return Norm2(*this-p);
	}	
	  /// returns the angle with X axis (radiants, in [-PI, +PI] )
	inline ScalarType Angle() const {
		return Math::Atan2(_v[1],_v[0]);
	}
		/// transform the point in cartesian coords into polar coords
	inline Point2 & Cartesian2Polar()
	{
		ScalarType t = Angle();
		_v[0] = Norm();
		_v[1] = t;
		return *this;
	}
		/// transform the point in polar coords into cartesian coords
	inline Point2 & Polar2Cartesian()
	{
		ScalarType l = _v[0];
		_v[0] = (ScalarType)(l*Math::Cos(_v[1]));
		_v[1] = (ScalarType)(l*Math::Sin(_v[1]));
		return *this;
	}
		/// rotates the point of an angle (radiants, counterclockwise)
	inline Point2 & Rotate( const ScalarType rad )
	{
		ScalarType t = _v[0];
		ScalarType s = Math::Sin(rad);
		ScalarType c = Math::Cos(rad);

		_v[0] = _v[0]*c - _v[1]*s;
		_v[1] =   t *s + _v[1]*c;

		return *this;
	}

	/// Questa funzione estende il vettore ad un qualsiasi numero di dimensioni
	/// paddando gli elementi estesi con zeri
	inline ScalarType Ext( const int i ) const
	{
		if(i>=0 && i<2) return _v[i];
		else            return 0;
	}
		/// imports from 2D points of different types
	template <class T>
	inline void Import( const Point2<T> & b )
	{
		_v[0] = b.X(); _v[1] = b.Y();
	}
		/// constructs a 2D points from an existing one of different type
	template <class T>
	static Point2 Construct( const Point2<T> & b )
	{
    return Point2(b.X(),b.Y());
	}


}; // end class definition


template <class T>
inline T Angle( Point2<T> const & p0, Point2<T> const & p1 )
{
	return p1.Angle() - p0.Angle();
}

template <class T>
inline Point2<T> operator - ( Point2<T> const & p ){
    return Point2<T>( -p[0], -p[1] );
}

template <class T>
inline Point2<T> operator * ( const T s, Point2<T> const & p ){
    return Point2<T>( p[0] * s, p[1] * s  );
}

template <class T>
inline T Norm( Point2<T> const & p ){
		return p.Norm();
}

template <class T>
inline T SquaredNorm( Point2<T> const & p ){
    return p.SquaredNorm();
}

template <class T>
inline Point2<T> & Normalize( Point2<T> & p ){
    return p.Normalize();
}

template <class T>
inline T Distance( Point2<T> const & p1,Point2<T> const & p2 ){
    return Norm(p1-p2);
}

template <class T>
inline T SquaredDistance( Point2<T> const & p1,Point2<T> const & p2 ){
    return SquaredNorm(p1-p2);
}

typedef Point2<short>  Point2s;
typedef Point2<int>	   Point2i;
typedef Point2<float>  Point2f;
typedef Point2<double> Point2d;

/*@}*/
} // end namespace