#pragma once
#define NOMINMAX
#undef min 
#undef max
#include <assert.h>
#include "Point3.h"

namespace GGL {

/** \addtogroup space */
/*@{*/
/** 
Templated class for 3D sphere.
  This is the class for definition of a sphere in 3D space. It is stored just as a Point3 and a radius
	@param T (template parameter) Specifies the type of scalar used to represent coords.
  Various policy could be added to improve efficience (keeping square of radius for instance).
*/

template <class T> class Sphere3 {
protected:
  Point3<T> _center;
  T _radius;
 public:
	typedef T ScalarType;
  Sphere3(): _radius(-1) {}
  Sphere3(const Point3<T> &center, T radius): _center(center), _radius(radius) {}
  
  T &Radius() { return _radius; }
  const T &Radius() const { return _radius; }
  Point3<T> &Center() { return _center; }
  const Point3<T> &Center() const { return _center; }

	bool IsEmpty() const { return _radius < 0; }
  ///return true if @param p - Center() <= Radius() 
  bool IsIn(const Point3<T> &p) const;

  void Add(const Point3<T> &p);
  void Add(const Sphere3 &sphere);
  void Intersect(const Sphere3 &sphere);
  	

  int CreateFromBox(int n, const Point3<T> *points);
  //makes 36 iterations over the data... but get good results.
  int CreateTight(int n, const Point3<T> *points, 
		  T threshold = 1.01, T speed = 0.6);
};

template <class T> T Distance(const Sphere3<T> &sphere, 
			      const Point3<T> &point) {
  T dist = Distance(point, sphere.Center()) - sphere.Radius();
  if(dist < 0) dist = 0;
  return dist;
}

template <class T> T Distance(const Sphere3<T> &sphere, 
			      const Sphere3<T> &s) {
  T dist = Distance(s.Center(), sphere.Center()) 
                    - sphere.Radius() - s.Radius();
  if(dist < 0) dist = 0;
  return dist;
}

typedef Sphere3<float> Sphere3f;
typedef Sphere3<double> Sphere3d;

template <class T> void Sphere3<T>::Add(const Sphere3<T> &sphere) {
  if(IsEmpty()) {
			*this = sphere;
			return;
		}
		Point3<T> dist = sphere.Center() - _center;
    float distance = dist.Norm();
		float fartest = distance + sphere.Radius();

		if(fartest <= _radius) 
      return;
    if(distance == 0) 
      _radius = sphere.Radius();
    else {
	    _center += dist * ((fartest - _radius) / (dist.Norm() * 2));
		  _radius = (_radius + fartest)/2;
    }
}

template <class T> void Sphere3<T>::Add(const Point3<T> &p) {
	if(IsEmpty()) {
		_center = p;
		_radius = 0;
	}
	Point3<T> dist = p - _center;
	float fartest = dist.Norm();
	if(fartest <= _radius) return;
	_center += dist * ((fartest - _radius) / (fartest*2));
	_radius = (_radius + fartest)/2;
}  

template <class T> bool Sphere3<T>::IsIn(const Point3<T> &p) const {
  if(IsEmpty()) return false;
  Point3<T> dist = p - _center;
  return dist.SquaredNorm() <= _radius*_radius;
}

template <class T> void Sphere3<T>::Intersect(const Sphere3<T> &s) {
  float dist = Distance(_center, s.Center());
  float r = 0.5 * (_radius + s.Radius() - dist);
  if(r < 0) {
    _radius = -1;
    return;
  }
  _center = (s.Center()*(_radius - r) + _center*(s.Radius() - r))/dist;
  _radius = r;
}

 template <class T> int Sphere3<T>::CreateFromBox(int n,  const Point3<T> *points) {
   Point3f max(-1e100, -1e100, -1e100);
   Point3f min(1e100, 1e100, 1e100);
   for(int i = 0; i < n; i++) {
     for(int k = 0; k < 3; k++) {
       if(max[k] < points[i][k]) max[k] = points[i][k];
       if(min[k] > points[i][k]) min[k] = points[i][k];
     }
   }
   Center() = (min + max)/2;
   Radius() = (min - max).Norm()/2;
   return 0;
 }

 template <class T> int Sphere3<T>::CreateTight(int n, const Point3<T> *points, 
						T threshold, T speed) { 
   //This is quantized gradient descent... really ugly. But simple :P
   //TODO step should adapt to terrain...
   for(int i = 0; i < n; i++)
     Add(points[i]);
   Radius() *= 1.0001;

   Point3<T> center;
   T radius;
   //Test with 6 directions

   Point3f pert[6];
   T step = Radius()/8;
   int count = 0;
   while(1) {
     count++;
     T radius = Radius();
     pert[0] = Point3f(step, 0, 0);
     pert[1] = -pert[0];
     pert[2] = Point3f(0, step, 0);
     pert[3] = -pert[2];
     pert[4] = Point3f(0, 0, step);
     pert[5] = -pert[4];

     unsigned int best = 6;
     T best_radius = Radius()/threshold;

     for(unsigned int k = 0; k < 6; k++) {
       center = Center() + pert[k];
       radius = 0;
       for(unsigned int i = 0; i < n; i++) {
	 float r = Distance(center, points[i]);
	 if(r > radius)
	   radius = r;
       }
       if(radius < best_radius) {
	 best = k;
	 best_radius = radius;
       }
     }
     if(best != 6) {
       Center() = Center() + pert[best];
       Radius() = best_radius;
     }
     step *= speed; 
     if(step < Radius() * (threshold - 1))
       break;
   }
   Radius() *= 1.01;
   
   //Test we did it correctly.
   for(int i = 0; i < n; i++) 
     assert(IsIn(points[i]));
   
   return count;
 }

} 
