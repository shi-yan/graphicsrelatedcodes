#pragma once
#include <assert.h>

#include "base.h"

namespace GGL {
/** \addtogroup space */
/*@{*/
    /**
        The templated class for representing a point in 4D space.
        The class is templated over the ScalarType class that is used to represent coordinates. 
				All the usual operator (* + - ...) are defined. 
     */

template <class T> class Point4
{
public:
  /// The only data member. Hidden to user.
        T _mV[4];

public:
	typedef T ScalarType;
	enum {Dimension = 4};

//@{

  /** @name Standard Constructors and Initializers 
   No casting operators have been introduced to avoid automatic unattended (and costly) conversion between different point types
   **/

	inline Point4 () { }
	inline Point4 ( const T nx, const T ny, const T nz , const T nw )
	{
                _mV[0] = nx; _mV[1] = ny; _mV[2] = nz; _mV[3] = nw;
	}
	inline Point4 ( const T  p[4] )
	{   
                _mV[0] = p[0]; _mV[1]= p[1]; _mV[2] = p[2]; _mV[3]= p[3];
	}
	inline Point4 ( const Point4 & p )
	{   
                _mV[0]= p._mV[0]; _mV[1]= p._mV[1]; _mV[2]= p._mV[2]; _mV[3]= p._mV[3];
	}
	inline void Zero()
	{   
                _mV[0] = _mV[1] = _mV[2] = _mV[3]= 0;
	}
	template <class Q>
	/// importer from different Point4 types
	inline void Import( const Point4<Q> & b )
	{
                _mV[0] = T(b[0]);		_mV[1] = T(b[1]);
                _mV[2] = T(b[2]);
                _mV[3] = T(b[3]);
	}
	/// constuctor that imports from different Point4 types
  template <class Q> 
  static inline Point4 Construct( const Point4<Q> & b )
  {
    return Point4(T(b[0]),T(b[1]),T(b[2]),T(b[3]));
  }

//@}

//@{

  /** @name Data Access. 
   access to data is done by overloading of [] or explicit naming of coords (x,y,z,w)
	**/
	inline const T & operator [] ( const int i ) const
	{
		assert(i>=0 && i<4);
                return _mV[i];
	}
	inline T & operator [] ( const int i )
	{
		assert(i>=0 && i<4);
                return _mV[i];
	}
        inline T &X() {return _mV[0];}
        inline T &Y() {return _mV[1];}
        inline T &Z() {return _mV[2];}
        inline T &W() {return _mV[3];}
	inline T const * V() const
	{
                return _mV;
	}
	inline const T & V ( const int i ) const
	{
		assert(i>=0 && i<4);
                return _mV[i];
	}
	inline T & V ( const int i )
	{
		assert(i>=0 && i<4);
                return _mV[i];
	}
		/// Padding function: give a default 0 value to all the elements that are not in the [0..2] range. 
		/// Useful for managing in a consistent way object that could have point2 / point3 / point4
	inline T Ext( const int i ) const
	{
                if(i>=0 && i<=3) return _mV[i];
		else             return 0;
	}
//@}
	
//@{
  /** @name Linear operators and the likes
  **/
	inline Point4 operator + ( const Point4 & p) const
	{ 
                return Point4( _mV[0]+p._mV[0], _mV[1]+p._mV[1], _mV[2]+p._mV[2], _mV[3]+p._mV[3] );
	}
	inline Point4 operator - ( const Point4 & p) const
	{
                return Point4( _mV[0]-p._mV[0], _mV[1]-p._mV[1], _mV[2]-p._mV[2], _mV[3]-p._mV[3] );
	}
	inline Point4 operator * ( const T s ) const
	{
                return Point4( _mV[0]*s, _mV[1]*s, _mV[2]*s, _mV[3]*s );
	}
	inline Point4 operator / ( const T s ) const
	{
                return Point4( _mV[0]/s, _mV[1]/s, _mV[2]/s, _mV[3]/s );
	}
	inline Point4 & operator += ( const Point4 & p)
	{
                _mV[0] += p._mV[0]; _mV[1] += p._mV[1]; _mV[2] += p._mV[2]; _mV[3] += p._mV[3];
		return *this;
	}
	inline Point4 & operator -= ( const Point4 & p )
	{
                _mV[0] -= p._mV[0]; _mV[1] -= p._mV[1]; _mV[2] -= p._mV[2]; _mV[3] -= p._mV[3];
		return *this;
	}
	inline Point4 & operator *= ( const T s )
	{
                _mV[0] *= s; _mV[1] *= s; _mV[2] *= s; _mV[3] *= s;
		return *this;
	}
	inline Point4 & operator /= ( const T s )
	{
                _mV[0] /= s; _mV[1] /= s; _mV[2] /= s; _mV[3] /= s;
		return *this;
	}
	inline Point4 operator - () const
	{
                return Point4( -_mV[0], -_mV[1], -_mV[2], -_mV[3] );
	}
	inline Point4 VectProd ( const Point4 &x, const Point4 &z ) const
	{	
		Point4 res;
		const Point4 &y = *this;

		res[0] = y[1]*x[2]*z[3]-y[1]*x[3]*z[2]-x[1]*y[2]*z[3]+
		         x[1]*y[3]*z[2]+z[1]*y[2]*x[3]-z[1]*y[3]*x[2];
		res[1] = y[0]*x[3]*z[2]-z[0]*y[2]*x[3]-y[0]*x[2]*
		         z[3]+z[0]*y[3]*x[2]+x[0]*y[2]*z[3]-x[0]*y[3]*z[2];
		res[2] = -y[0]*z[1]*x[3]+x[0]*z[1]*y[3]+y[0]*x[1]*
  		         z[3]-x[0]*y[1]*z[3]-z[0]*x[1]*y[3]+z[0]*y[1]*x[3];
		res[3] = -z[0]*y[1]*x[2]-y[0]*x[1]*z[2]+x[0]*y[1]*
		         z[2]+y[0]*z[1]*x[2]-x[0]*z[1]*y[2]+z[0]*x[1]*y[2];
		return res;
	}
//@}
	
//@{
  /** @name Norms and normalizations
  **/
	/// Euclidian normal
	inline T Norm() const
	{
                return Math::Sqrt( _mV[0]*_mV[0] + _mV[1]*_mV[1] + _mV[2]*_mV[2] + _mV[3]*_mV[3] );
	}
	/// Squared euclidian normal
	inline T SquaredNorm() const
	{
                return _mV[0]*_mV[0] + _mV[1]*_mV[1] + _mV[2]*_mV[2] + _mV[3]*_mV[3];
	}
	/// Euclidian normalization 

        inline Point4 & Normalize()
	{
            T kn=Math::Sqrt(_mV[0]*_mV[0]+_mV[1]*_mV[1]+_mV[2]*_mV[2]+_mV[3]*_mV[3]);
            if(kn>0.0)
            {
                _mV[0]/=kn;
                _mV[1]/=kn;
                _mV[2]/=kn;
                _mV[3]/=kn;
            }

           return *this;
	}
	/// Homogeneous normalization (division by W)
	inline Point4 & HomoNormalize(){
                if (_mV[3]!=0.0) {	_mV[0] /= _mV[3];	_mV[1] /= _mV[3];	_mV[2] /= _mV[3]; _mV[3]=1.0; }
		return *this;
	};

//@}
	
//@{
  /** @name Comparison operators (lexicographical order)
  **/
	inline bool operator == (  const Point4& p ) const
	{
                return _mV[0]==p._mV[0] && _mV[1]==p._mV[1] && _mV[2]==p._mV[2] && _mV[3]==p._mV[3];
	} 
	inline bool operator != ( const Point4 & p ) const
	{
                return _mV[0]!=p._mV[0] || _mV[1]!=p._mV[1] || _mV[2]!=p._mV[2] || _mV[3]!=p._mV[3];
	}
	inline bool operator <  ( Point4 const & p ) const
	{
                return	(_mV[3]!=p._mV[3])?(_mV[3]<p._mV[3]):
                                (_mV[2]!=p._mV[2])?(_mV[2]<p._mV[2]):
                                (_mV[1]!=p._mV[1])?(_mV[1]<p._mV[1]):
                                (_mV[0]<p._mV[0]);
	}
	inline bool operator >  ( const Point4 & p ) const
	{
                return	(_mV[3]!=p._mV[3])?(_mV[3]>p._mV[3]):
                                (_mV[2]!=p._mV[2])?(_mV[2]>p._mV[2]):
                                (_mV[1]!=p._mV[1])?(_mV[1]>p._mV[1]):
                                (_mV[0]>p._mV[0]);
	}
	inline bool operator <= ( const Point4 & p ) const
	{
                return	(_mV[3]!=p._mV[3])?(_mV[3]< p._mV[3]):
                                (_mV[2]!=p._mV[2])?(_mV[2]< p._mV[2]):
                                (_mV[1]!=p._mV[1])?(_mV[1]< p._mV[1]):
                                (_mV[0]<=p._mV[0]);
	}
	inline bool operator >= ( const Point4 & p ) const
	{
                return	(_mV[3]!=p._mV[3])?(_mV[3]> p._mV[3]):
                                (_mV[2]!=p._mV[2])?(_mV[2]> p._mV[2]):
                                (_mV[1]!=p._mV[1])?(_mV[1]> p._mV[1]):
                                (_mV[0]>=p._mV[0]);
	}
//@}
	
//@{
  /** @name Dot products
  **/

	// dot product
	inline T operator * ( const Point4 & p ) const
	{
                return _mV[0]*p._mV[0] + _mV[1]*p._mV[1] + _mV[2]*p._mV[2] + _mV[3]*p._mV[3];
	} 
	inline Point4 operator ^ (  const Point4& p ) const
	{
		assert(0);// not defined by two vectors (only put for metaprogramming)
		return Point4();
	}

	/// slower version, more stable (double precision only)
	T StableDot ( const Point4<T> & p ) const
	{

                T k0=_mV[0]*p._mV[0],	k1=_mV[1]*p._mV[1], k2=_mV[2]*p._mV[2], k3=_mV[3]*p._mV[3];
		int exp0,exp1,exp2,exp3;

		frexp( double(k0), &exp0 );frexp( double(k1), &exp1 );
		frexp( double(k2), &exp2 );frexp( double(k3), &exp3 );

		if (exp0>exp1) { Math::Swap(k0,k1); Math::Swap(exp0,exp1); }
		if (exp2>exp3) { Math::Swap(k2,k3); Math::Swap(exp2,exp3); }
		if (exp0>exp2) { Math::Swap(k0,k2); Math::Swap(exp0,exp2); }
		if (exp1>exp3) { Math::Swap(k1,k3); Math::Swap(exp1,exp3); }
		if (exp2>exp3) { Math::Swap(k2,k3); Math::Swap(exp2,exp3); }

		return ( (k0 + k1) + k2 ) +k3;
	}  
//@}


}; // end class definition

template <class T>
T Angle( const Point4<T>& p1, const Point4<T>  & p2 )
{
	T w = p1.Norm()*p2.Norm();
	if(w==0) return -1;
	T t = (p1*p2)/w;
	if(t>1) t=1;
	return T( Math::Acos(t) );
}

template <class T>
inline T Norm( const Point4<T> & p )
{
	return p.Norm();
}

template <class T>
inline T SquaredNorm( const Point4<T> & p )
{
    return p.SquaredNorm();
}

template <class T>
inline T Distance( const Point4<T> & p1, const Point4<T> & p2 )
{
    return Norm(p1-p2);
}

template <class T>
inline T SquaredDistance( const Point4<T> & p1, const Point4<T> & p2 )
{
    return SquaredNorm(p1-p2);
}

	/// slower version of dot product, more stable (double precision only)
template<class T>
double StableDot ( Point4<T> const & p0, Point4<T> const & p1 )
{
	return p0.StableDot(p1);
}  

typedef Point4<short>  Point4s;
typedef Point4<int>	   Point4i;
typedef Point4<float>  Point4f;
typedef Point4<double> Point4d;



} 
