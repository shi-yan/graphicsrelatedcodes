#pragma once
#include <cstdlib>
#include <assert.h>
#include "base.h"

namespace GGL
{
	template <class T> class Box3;

	template <class P3ScalarType> class Point3
	{
	public:
		  static const size_t size_ = 3;
		typedef P3ScalarType value_type;

		typedef Point3<P3ScalarType>  vector_type;
	protected:
		/// The only data member. Hidden to user.
		P3ScalarType _v[3];

	public:
		typedef P3ScalarType ScalarType;
		enum {Dimension = 3};
	
	
	//@{
	
	/** @name Standard Constructors and Initializers 
	No casting operators have been introduced to avoid automatic unattended (and costly) conversion between different point types
	**/

	inline Point3 () 
	{

	}

	inline Point3 ( const P3ScalarType nx, const P3ScalarType ny, const P3ScalarType nz )
	{
		_v[0] = nx;
		_v[1] = ny;
		_v[2] = nz;
	}

	inline vector_type & vectorize(const P3ScalarType v)
	{
		_v[0]=_v[1]=_v[2]=v;

		return *this;
	}

		inline void vec ( const P3ScalarType nx, const P3ScalarType ny, const P3ScalarType nz )
	{
		_v[0] = nx;
		_v[1] = ny;
		_v[2] = nz;
	}

	inline Point3 ( Point3 const & p )
	{   
		_v[0]= p._v[0];
		_v[1]= p._v[1];
		_v[2]= p._v[2];
	}

	inline Point3 ( const P3ScalarType nv[3] )
	{
		_v[0] = nv[0];
		_v[1] = nv[1];
		_v[2] = nv[2];
	}

	inline Point3 & operator =( Point3 const & p )
	{
			_v[0]= p._v[0]; _v[1]= p._v[1]; _v[2]= p._v[2];
			return *this;
	}

	inline void Zero()
	{
		_v[0] = 0;
		_v[1] = 0;
		_v[2] = 0;
	}

	inline bool isZero()
	{
		return (_v[0]==0 && _v[1]==0 && _v[2]==0);
	}
  
	 /// Padding function: give a default 0 value to all the elements that are not in the [0..2] range. 
	/// Useful for managing in a consistent way object that could have point2 / point3 / point4
	inline P3ScalarType Ext( const int i ) const
	{
		if(i>=0 && i<=2) return _v[i];
		else             return 0;
	}

	template <class Q>
	inline void Import( const Point3<Q> & b )
	{
		_v[0] = P3ScalarType(b[0]);
		_v[1] = P3ScalarType(b[1]);
		_v[2] = P3ScalarType(b[2]);
	}

	template <class Q> 
	static inline Point3 Construct( const Point3<Q> & b )
	{
		return Point3(P3ScalarType(b[0]),P3ScalarType(b[1]),P3ScalarType(b[2]));
	}

	template <class Q> 
	static inline Point3 Construct( const Q & P0, const Q & P1, const Q & P2)
	{
		return Point3(P3ScalarType(P0),P3ScalarType(P1),P3ScalarType(P2));
	}

	static inline Point3 Construct( const Point3<ScalarType> & b )
	{
		return b;
	}

//@}

//@{

  /** @name Data Access. 
   access to data is done by overloading of [] or explicit naming of coords (x,y,z)**/

	inline P3ScalarType & operator [] ( const int i )
	{
		assert(i>=0 && i<3);
		return _v[i];
	}
	
	inline const P3ScalarType & operator [] ( const int i ) const
	{
		assert(i>=0 && i<3);
		return _v[i];
	}
	
	inline const P3ScalarType &X() const 
	{
		return _v[0]; 
	} 
	
	inline const P3ScalarType &Y() const 
	{
		return _v[1]; 
	}

	inline const P3ScalarType &Z() const 
	{
		return _v[2]; 
	}

	inline P3ScalarType &X() 
	{
		return _v[0]; 
	}

	inline P3ScalarType &Y() 
	{
		return _v[1]; 
	}

	inline P3ScalarType &Z() 
	{
		return _v[2]; 
	}

	inline const P3ScalarType * V() const
	{
		return _v;
	}
	inline P3ScalarType * V()
	{
		return _v;
	}
	inline P3ScalarType & V( const int i )
	{
		assert(i>=0 && i<3);
		return _v[i];
	}
	inline const P3ScalarType & V( const int i ) const
	{
		assert(i>=0 && i<3);
		return _v[i];
	}
//@}
//@{

  /** @name Classical overloading of operators 
  Note   
  **/

	inline Point3 operator + ( Point3 const & p) const
	{
		return Point3<P3ScalarType>( _v[0]+p._v[0], _v[1]+p._v[1], _v[2]+p._v[2] );
	}
	inline Point3 operator - ( Point3 const & p) const
	{
		return Point3<P3ScalarType>( _v[0]-p._v[0], _v[1]-p._v[1], _v[2]-p._v[2] );
	}
	inline Point3 operator * ( const P3ScalarType s ) const
	{
		return Point3<P3ScalarType>( _v[0]*s, _v[1]*s, _v[2]*s );
	}
	inline Point3 operator / ( const P3ScalarType s ) const
	{
		return Point3<P3ScalarType>( _v[0]/s, _v[1]/s, _v[2]/s );
	}
		/// Dot product
	inline P3ScalarType operator * ( Point3 const & p ) const
	{
		return ( _v[0]*p._v[0] + _v[1]*p._v[1] + _v[2]*p._v[2] );
	}
		/// Cross product
	inline Point3 operator ^ ( Point3 const & p ) const
	{
		return Point3 <P3ScalarType>
		(
			_v[1]*p._v[2] - _v[2]*p._v[1],
			_v[2]*p._v[0] - _v[0]*p._v[2],
			_v[0]*p._v[1] - _v[1]*p._v[0]
		);
	}

	inline Point3 & operator += ( Point3 const & p)
	{
		_v[0] += p._v[0];
		_v[1] += p._v[1];
		_v[2] += p._v[2];
		return *this;
	}
	inline Point3 & operator -= ( Point3 const & p)
	{
		_v[0] -= p._v[0];
		_v[1] -= p._v[1];
		_v[2] -= p._v[2];
		return *this;
	}
	inline Point3 & operator *= ( const P3ScalarType s )
	{
		_v[0] *= s;
		_v[1] *= s;
		_v[2] *= s;
		return *this;
	}
	inline Point3 & operator /= ( const P3ScalarType s )
	{
		_v[0] /= s;
		_v[1] /= s;
		_v[2] /= s;
		return *this;
	}
		// Norme
	inline P3ScalarType Norm() const
	{
    return Math::Sqrt( _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] );
	}

	inline P3ScalarType length() const
	{
	    return Math::Sqrt( _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] );

	}

	inline P3ScalarType SquaredNorm() const
	{
		return ( _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] );
	}
		// Scalatura differenziata
	inline Point3 & Scale( const P3ScalarType sx, const P3ScalarType sy, const P3ScalarType sz )
	{
		_v[0] *= sx;
		_v[1] *= sy;
		_v[2] *= sz;
		return *this;
	}
	inline Point3 & Scale( const Point3 & p )
	{
		_v[0] *= p._v[0];
		_v[1] *= p._v[1];
		_v[2] *= p._v[2];
		return *this;
	}

	// Normalizzazione
	inline Point3 & Normalize()
	{
		P3ScalarType n = Math::Sqrt(_v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2]);
		if(n>0.0) 
		{	
			_v[0] /= n;
			_v[1] /= n;
			_v[2] /= n;  
		}
		return *this;
	}
	
	/** 
	 * Convert to polar coordinates from cartesian coordinates.
	 *
	 * Theta is the azimuth angle and ranges between [0, 360) degrees.
	 * Phi is the elevation angle (not the polar angle) and ranges between [-90, 90] degrees.
	 *
	 * /note Note that instead of the classical polar angle, which ranges between 
	 *       0 and 180 degrees we opt for the elevation angle to obtain a more 
	 *       intuitive spherical coordinate system.
	 */
	void ToPolar(P3ScalarType &ro, P3ScalarType &theta, P3ScalarType &phi) const
	{
		ro = Norm();
		theta = (P3ScalarType)atan2(_v[2], _v[0]);
		phi   = (P3ScalarType)asin(_v[1]/ro);
	}

	/**
	 * Convert from polar coordinates to cartesian coordinates.
	 *
	 * Theta is the azimuth angle and ranges between [0, 360) degrees.
	 * Phi is the elevation angle (not the polar angle) and ranges between [-90, 90] degrees.
	 *
	 * \note Note that instead of the classical polar angle, which ranges between 
	 *       0 and 180 degrees, we opt for the elevation angle to obtain a more 
	 *       intuitive spherical coordinate system.
	 */
	void FromPolar(const P3ScalarType &ro, const P3ScalarType &theta, const P3ScalarType &phi)
	{
		_v[0]= ro*cos(theta)*cos(phi);
		_v[1]= ro*sin(phi);
		_v[2]= ro*sin(theta)*cos(phi);
	}
	
	Box3<P3ScalarType> GetBBox(Box3<P3ScalarType> &bb) const;
//@}
//@{

  /** @name Comparison Operators. 
   Note that the reverse z prioritized ordering, useful in many situations.
   **/

	inline bool operator == ( Point3 const & p ) const
	{
		return _v[0]==p._v[0] && _v[1]==p._v[1] && _v[2]==p._v[2];
	}
	inline bool operator != ( Point3 const & p ) const
	{
		return _v[0]!=p._v[0] || _v[1]!=p._v[1] || _v[2]!=p._v[2];
	}
	inline bool operator <  ( Point3 const & p ) const
	{
		return	(_v[2]!=p._v[2])?(_v[2]<p._v[2]):
				(_v[1]!=p._v[1])?(_v[1]<p._v[1]):
						       (_v[0]<p._v[0]);
	}
	inline bool operator >  ( Point3 const & p ) const
	{
		return	(_v[2]!=p._v[2])?(_v[2]>p._v[2]):
				(_v[1]!=p._v[1])?(_v[1]>p._v[1]):
							   (_v[0]>p._v[0]);
	}
	inline bool operator <= ( Point3 const & p ) const
	{
		return	(_v[2]!=p._v[2])?(_v[2]< p._v[2]):
				(_v[1]!=p._v[1])?(_v[1]< p._v[1]):
							   (_v[0]<=p._v[0]);
	}
	inline bool operator >= ( Point3 const & p ) const
	{
		return	(_v[2]!=p._v[2])?(_v[2]> p._v[2]):
				(_v[1]!=p._v[1])?(_v[1]> p._v[1]):
							   (_v[0]>=p._v[0]);
	}

	
	inline Point3 operator - () const
	{
		return Point3<P3ScalarType> ( -_v[0], -_v[1], -_v[2] );
	}
 //@}

}; // end class definition


	template <class P3ScalarType>
inline P3ScalarType Angle( Point3<P3ScalarType> const & p1, Point3<P3ScalarType> const & p2 )
{
	P3ScalarType w = p1.Norm()*p2.Norm();
	if(w==0) return -1;
	P3ScalarType t = (p1*p2)/w;
	if(t>1) t = 1;
	else if(t<-1) t = -1;
    return (P3ScalarType) acos(t);
}

// versione uguale alla precedente ma che assume che i due vettori sono unitari
template <class P3ScalarType>
inline P3ScalarType AngleN( Point3<P3ScalarType> const & p1, Point3<P3ScalarType> const & p2 )
{
	P3ScalarType w = p1*p2;
	if(w>1) 
		w = 1;
	else if(w<-1) 
		w=-1;
  return (P3ScalarType) acos(w);
}


template <class P3ScalarType>
inline P3ScalarType Norm( Point3<P3ScalarType> const & p )
{
	return p.Norm();
}

template <class P3ScalarType>
inline P3ScalarType SquaredNorm( Point3<P3ScalarType> const & p )
{
    return p.SquaredNorm();
}

template <class P3ScalarType>
inline Point3<P3ScalarType> & Normalize( Point3<P3ScalarType> & p )
{
    p.Normalize();
    return p;
}

template <class P3ScalarType>
inline P3ScalarType Distance( Point3<P3ScalarType> const & p1,Point3<P3ScalarType> const & p2 )
{
    return (p1-p2).Norm();
}

template <class P3ScalarType>
inline P3ScalarType SquaredDistance( Point3<P3ScalarType> const & p1,Point3<P3ScalarType> const & p2 )
{
    return (p1-p2).SquaredNorm();
}

	// Dot product preciso numericamente (solo double!!)
	// Implementazione: si sommano i prodotti per ordine di esponente
	// (prima le piu' grandi)
template<class P3ScalarType>
double stable_dot ( Point3<P3ScalarType> const & p0, Point3<P3ScalarType> const & p1 )
{
	P3ScalarType k0 = p0._v[0]*p1._v[0];
	P3ScalarType k1 = p0._v[1]*p1._v[1];
	P3ScalarType k2 = p0._v[2]*p1._v[2];

	int exp0,exp1,exp2;

	frexp( double(k0), &exp0 );
	frexp( double(k1), &exp1 );
	frexp( double(k2), &exp2 );

	if( exp0<exp1 )
	{
		if(exp0<exp2)
			return (k1+k2)+k0;
		else
			return (k0+k1)+k2;
	}
	else
	{
		if(exp1<exp2)
			return(k0+k2)+k1;
		else
			return (k0+k1)+k2;
	}
}  



/// Point(p) Edge(v1-v2) dist, q is the point in v1-v2 with min dist
template<class P3ScalarType>
P3ScalarType PSDist( const Point3<P3ScalarType> & p,
			         const Point3<P3ScalarType> & v1,
					 const Point3<P3ScalarType> & v2,
			         Point3<P3ScalarType> & q )
{
    Point3<P3ScalarType> e = v2-v1;
    P3ScalarType  t = ((p-v1)*e)/e.SquaredNorm();
    if(t<0)      t = 0;
	else if(t>1) t = 1;
	q = v1+e*t;
    return Distance(p,q);
}


template <class P3ScalarType>
void GetUV( Point3<P3ScalarType> &n,Point3<P3ScalarType> &u, Point3<P3ScalarType> &v, Point3<P3ScalarType> up=(Point3<P3ScalarType>(0,1,0)) )
{
	n.Normalize();
	const double LocEps=double(1e-7);
	u=n^up;
  double len = u.Norm();
 	if(len < LocEps)
	{
		if(fabs(n[0])<fabs(n[1])){
			if(fabs(n[0])<fabs(n[2])) up=Point3<P3ScalarType>(1,0,0); // x is the min 
			                         else up=Point3<P3ScalarType>(0,0,1); // z is the min 
		}else {
			if(fabs(n[1])<fabs(n[2])) up=Point3<P3ScalarType>(0,1,0); // y is the min 
			                         else up=Point3<P3ScalarType>(0,0,1); // z is the min 
		}
		u=n^up;
	}
	u.Normalize();
	v=n^u;
	v.Normalize();
	Point3<P3ScalarType> uv=u^v;
}


template <class SCALARTYPE>
inline Point3<SCALARTYPE> Abs(const Point3<SCALARTYPE> & p) {
	return (Point3<SCALARTYPE>(Math::Abs(p[0]), Math::Abs(p[1]), Math::Abs(p[2])));
}
// probably a more uniform naming should be defined...
template <class SCALARTYPE>
inline Point3<SCALARTYPE> LowClampToZero(const Point3<SCALARTYPE> & p) {
	return (Point3<SCALARTYPE>(Math::Max(p[0], (SCALARTYPE)0), Math::Max(p[1], (SCALARTYPE)0), Math::Max(p[2], (SCALARTYPE)0)));
}

template <class SCALARTYPE>
inline Point3<SCALARTYPE> cross(const Point3<SCALARTYPE> &a, const Point3<SCALARTYPE> &p)
{
	//printf("cross product of a(%f,%f,%f),b(%f,%f,%f)\n",a[0],a[1],a[2],p[0],p[1],p[2]);
		return Point3 <SCALARTYPE>
		(
			a[1]*p[2] - a[2]*p[1],
			a[2]*p[0] - a[0]*p[2],
			a[0]*p[1] - a[1]*p[0]
		);
}

typedef Point3<short>  Point3s;
typedef Point3<int>	   Point3i;
typedef Point3<float>  Point3f;
typedef Point3<double> Point3d;

/*@}*/

} 

