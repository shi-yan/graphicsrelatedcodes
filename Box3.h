#pragma once

#include "Point3.h"
#include "Matrix33.h"
#include "Line3.h"
#include "Plane3.h"

namespace GGL 
{

	/** \addtogroup space */
	/*@{*/
	/** 
	Templated class for 3D boxes.
	This is the class for definition of a axis aligned bounding box in 3D space. It is stored just as two Point3
		@param BoxScalarType (template parameter) Specifies the type of scalar used to represent coords.
	*/

	template <class BoxScalarType>
	class Box3
	{
	public:

		/// The scalar type
		typedef BoxScalarType ScalarType;

		/// min coordinate point
		Point3<BoxScalarType> min;
		/// max coordinate point
		Point3<BoxScalarType> max;
		/// The bounding box constructor
		inline  Box3() 
		{
			min.X()= 1;
			max.X()= -1;
			min.Y()= 1;
			max.Y()= -1;
			min.Z()= 1;
			max.Z()= -1;
		}
		
		/// Copy constructor
		inline  Box3( const Box3 & b ) 
		{
			min=b.min; 
			max=b.max; 
		}
		
		/// Min Max constructor
		inline  Box3( const Point3<BoxScalarType> & mi, const Point3<BoxScalarType> & ma ) 
		{
			min = mi; 
			max = ma; 
		}
		
		/// Point Radius Constructor
		inline Box3(const Point3<BoxScalarType> & center, const BoxScalarType & radius) 
		{
			min = center-Point3<BoxScalarType>(radius,radius,radius);
			max = center+Point3<BoxScalarType>(radius,radius,radius);
		}
		
		/// The bounding box distructor
		inline ~Box3() 
		{
		}

		/// Operator to compare two bounding box
		inline bool operator == ( Box3<BoxScalarType> const & p ) const
		{
			return min==p.min && max==p.max;
		}

                inline bool operator> (Box3<BoxScalarType> const & p) const
                {
                    GGL::Point3f dis=(max-min);
                    GGL::Point3f dis2=(p.max-p.min);

                    return abs(dis.X()*dis.Y()*dis.Z())>abs(dis2.X()*dis2.Y()*dis2.Z());
                }
		
		/// Operator to dispare two bounding box
		inline bool operator != ( Box3<BoxScalarType> const & p ) const
		{
			return min!=p.min || max!=p.max;
		}

		/** Varia le dimensioni del bounding box scalandole rispetto al parametro scalare.
			@param s Valore scalare che indica di quanto deve variare il bounding box
		*/
		void Offset( const BoxScalarType s )
		{
			Offset( Point3<BoxScalarType> (s,s,s));
		}
		
		/** Varia le dimensioni del bounding box del valore fornito attraverso il parametro.
			@param delta Point in 3D space
		*/
		void Offset( const Point3<BoxScalarType> & delta )
		{
			min -= delta;
			max += delta;
		}
		
		/// Initializing the bounding box
		void Set( const Point3<BoxScalarType> & p )
		{
			min = max = p;
		}

		/// Set the bounding box to a null value
		void SetNull()
		{
			min.X()= 1; max.X()= -1;
			min.Y()= 1; max.Y()= -1;
			min.Z()= 1; max.Z()= -1;
		}

		/** Function to add two bounding box
			@param b Il bounding box che si vuole aggiungere
		*/
		void Add( Box3<BoxScalarType> const & b )
		{
			if(b.IsNull()) return; // Adding a null bbox should do nothing
			if(IsNull()) *this=b;
			else
			{
				if(min.X() > b.min.X()) min.X() = b.min.X();
				if(min.Y() > b.min.Y()) min.Y() = b.min.Y();
				if(min.Z() > b.min.Z()) min.Z() = b.min.Z();

				if(max.X() < b.max.X()) max.X() = b.max.X();
				if(max.Y() < b.max.Y()) max.Y() = b.max.Y();
				if(max.Z() < b.max.Z()) max.Z() = b.max.Z();
			}
		}
		
		/** Funzione per aggiungere un punto al bounding box. Il bounding box viene modificato se il punto
			cade fuori da esso.
			@param p The point 3D
		*/
		void Add( const Point3<BoxScalarType> & p )
		{
			if(IsNull()) Set(p);
			else 
			{
				if(min.X() > p.X()) min.X() = p.X();
				if(min.Y() > p.Y()) min.Y() = p.Y();
				if(min.Z() > p.Z()) min.Z() = p.Z();

				if(max.X() < p.X()) max.X() = p.X();
				if(max.Y() < p.Y()) max.Y() = p.Y();
				if(max.Z() < p.Z()) max.Z() = p.Z();
			}
		}
	
		// Aggiunge ad un box un altro box trasformato secondo la matrice m
		void Add( const Matrix44<BoxScalarType> &m, const Box3<BoxScalarType> & b )
		{
			const Point3<BoxScalarType> &mn= b.min;
			const Point3<BoxScalarType> &mx= b.max;
			Add(m*(Point3<BoxScalarType>(mn[0],mn[1],mn[2])));
			Add(m*(Point3<BoxScalarType>(mx[0],mn[1],mn[2])));
			Add(m*(Point3<BoxScalarType>(mn[0],mx[1],mn[2])));
			Add(m*(Point3<BoxScalarType>(mx[0],mx[1],mn[2])));
			Add(m*(Point3<BoxScalarType>(mn[0],mn[1],mx[2])));
			Add(m*(Point3<BoxScalarType>(mx[0],mn[1],mx[2])));
			Add(m*(Point3<BoxScalarType>(mn[0],mx[1],mx[2])));
			Add(m*(Point3<BoxScalarType>(mx[0],mx[1],mx[2])));
		}
		
		/** Calcola l'intersezione tra due bounding box. Al bounding box viene assegnato il valore risultante.
			@param b Il bounding box con il quale si vuole effettuare l'intersezione
		*/
		void Intersect( const Box3<BoxScalarType> & b )
		{
			if(min.X() < b.min.X()) min.X() = b.min.X();
			if(min.Y() < b.min.Y()) min.Y() = b.min.Y();
			if(min.Z() < b.min.Z()) min.Z() = b.min.Z();

			if(max.X() > b.max.X()) max.X() = b.max.X();
			if(max.Y() > b.max.Y()) max.Y() = b.max.Y();
			if(max.Z() > b.max.Z()) max.Z() = b.max.Z();

			if(min.X()>max.X() || min.Y()>max.Y() || min.Z()>max.Z()) SetNull();
		}

		/** Trasla il bounding box di un valore definito dal parametro.
			@param p Il bounding box trasla sulla x e sulla y in base alle coordinate del parametro
		*/
		void Translate( const Point3<BoxScalarType> & p )
		{
			min += p;
			max += p;
		}

		/** Verifica se un punto appartiene ad un bounding box.
			@param p The point 3D
	
		@return True se p appartiene al bounding box, false altrimenti
		*/
		bool IsIn( Point3<BoxScalarType> const & p ) const
		{
			return (	min.X() <= p.X() && p.X() <= max.X() &&		min.Y() <= p.Y() && p.Y() <= max.Y() &&			min.Z() <= p.Z() && p.Z() <= max.Z()		);
		}
		
		/** Verifica se un punto appartiene ad un bounding box aperto sul max.
			@param p The point 3D
			@return True se p appartiene al bounding box, false altrimenti
		*/
		bool IsInEx( Point3<BoxScalarType> const & p ) const
		{
			return (		min.X() <= p.X() && p.X() < max.X() &&	min.Y() <= p.Y() && p.Y() < max.Y() &&		min.Z() <= p.Z() && p.Z() < max.Z()	);
		}
		
		/** Verifica se due bounding box collidono cioe' se hanno una intersezione non vuota. Per esempio
			due bounding box adiacenti non collidono.
			@param b A bounding box
			@return True se collidoo, false altrimenti
		*/

		bool Collide(Box3<BoxScalarType> const &b) const
		{
			return b.min.X()<max.X() && b.max.X()>min.X() &&   b.min.Y()<max.Y() && b.max.Y()>min.Y() &&   b.min.Z()<max.Z() && b.max.Z()>min.Z() ;
		}

		/** Controlla se il bounding box e' nullo.
			@return True se il bounding box e' nullo, false altrimenti
		*/
	
		bool IsNull() const 
		{
			return min.X()>max.X() || min.Y()>max.Y() || min.Z()>max.Z(); 
		}
		
		/** Controlla se il bounding box e' vuoto.
			@return True se il bounding box e' vuoto, false altrimenti
		*/
		bool IsEmpty() const 
		{
			return min==max; 
		}
		
		/// Restituisce la lunghezza della diagonale del bounding box.
		BoxScalarType Diag() const
		{
			return Distance(min,max);
		}
		
		/// Calcola il quadrato della diagonale del bounding box.
		BoxScalarType SquaredDiag() const
		{
			return SquaredDistance(min,max);
		}
		
		/// Calcola il centro del bounding box.
		Point3<BoxScalarType> Center() const
		{
			return (min+max)/2;
		}
		
		/// Compute bounding box size.
		Point3<BoxScalarType> Dim() const
		{
			return (max-min);
		}
	  
		/// Returns global coords of a local point expressed in [0..1]^3
		Point3<BoxScalarType> LocalToGlobal(Point3<BoxScalarType> const & p) const
		{
			return Point3<BoxScalarType>( 		min[0] + p[0]*(max[0]-min[0]), 		min[1] + p[1]*(max[1]-min[1]),		min[2] + p[2]*(max[2]-min[2]));
		}
	  
		/// Returns local coords expressed in [0..1]^3 of a point in 3D
		Point3<BoxScalarType> GlobalToLocal(Point3<BoxScalarType> const & p) const
		{
			return Point3<BoxScalarType>( 	  (p[0]-min[0])/(max[0]-min[0]), 	  (p[1]-min[1])/(max[1]-min[1]), 	  (p[2]-min[2])/(max[2]-min[2])		);
		}
		
		/// Calcola il volume del bounding box.
		BoxScalarType Volume() const
		{
			return (max.X()-min.X())*(max.Y()-min.Y())*(max.Z()-min.Z());
		}

		/// Calcola la dimensione del bounding box sulla x.
		inline BoxScalarType DimX() const 
		{
			return max.X()-min.X();
		}
		
		/// Calcola la dimensione del bounding box sulla y.
		inline BoxScalarType DimY() const 
		{
			return max.Y()-min.Y();
		}
		
		/// Calcola la dimensione del bounding box sulla z.
		inline BoxScalarType DimZ() const 
		{
			return max.Z()-min.Z();
		}
		
		/// Calcola il lato di lunghezza maggiore  
		inline unsigned char MaxDim() const 
		{ 
			int i;
			Point3<BoxScalarType> diag = max-min;
			if(diag[0]>diag[1]) i=0; else i=1;
			return (diag[i]>diag[2])? i: 2;
		}
		
		/// Calcola il lato di lunghezza minore  
		inline unsigned char MinDim() const 
		{ 
			int i;
			Point3<BoxScalarType> diag =  max-min;
			if(diag[0]<diag[1]) i=0; else i=1;
			return (diag[i]<diag[2])? i: 2;
		}

		template <class Q>
		inline void Import( const Box3<Q> & b )
		{
			min.Import(b.min);
			max.Import(b.max);
		}

		template <class Q>
		static inline Box3 Construct( const Box3<Q> & b )
		{
			return Box3(Point3<BoxScalarType>::Construct(b.min),Point3<BoxScalarType>::Construct(b.max));
		}
		
		/// gives the ith box vertex in order: (x,y,z),(X,y,z),(x,Y,z),(X,Y,z),(x,y,Z),(X,y,Z),(x,Y,Z),(X,Y,Z)
		Point3<BoxScalarType> P(const int & i) const 
		{
			return Point3<BoxScalarType>(		min[0]+ (i%2) * DimX(),				min[1]+ ((i / 2)%2) * DimY(),				min[2]+ (i>3)* DimZ());
		}
	}; // end class definition

	template <class T> Box3<T> Point3<T>::GetBBox(Box3<T> &bb) const 
	{
		bb.Set( *this );
	}
 

	template <class ScalarType> 
	ScalarType DistancePoint3Box3(const Point3<ScalarType> &test,  const Box3<ScalarType> &bbox)
	{
		///if fall inside return distance to a face
		if (bbox.IsIn(test))
		{
			ScalarType dx=std::min<ScalarType>(bbox.max.X()-test.X(),test.X()-bbox.min.X());
			ScalarType dy=std::min<ScalarType>(bbox.max.Y()-test.Y(),test.Y()-bbox.min.Y());
			ScalarType dz=std::min<ScalarType>(bbox.max.Z()-test.Z(),test.Z()-bbox.min.Z());
			return std::min<ScalarType>(dx,std::min<ScalarType>(dy,dz));
		}

		///find the right quandrant 
		bool XM=(test.X()>=bbox.max.X());
		bool Xm=(test.X()<=bbox.min.X());
		bool YM=(test.Y()>=bbox.max.Y());
		bool Ym=(test.Y()<=bbox.min.Y());
		bool ZM=(test.Z()>=bbox.max.Z());
		bool Zm=(test.Z()<=bbox.min.Z());
	

		///VERTICES CASES
		if ((Xm)&&(Ym)&&(Zm))
			return ((test-bbox.P(0)).Norm());
		if ((Ym)&&(Zm)&&(XM))
			return ((test-bbox.P(1)).Norm());
		if ((Xm)&&(Zm)&&(YM))
			return ((test-bbox.P(2)).Norm());
		if ((XM)&&(YM)&&(Zm))
			return ((test-bbox.P(3)).Norm());
		if ((Xm)&&(Ym)&&(ZM))
			return ((test-bbox.P(4)).Norm());
		if ((XM)&&(ZM)&&(Ym))
			return ((test-bbox.P(5)).Norm());
		if ((YM)&&(ZM)&&(Xm))
			return ((test-bbox.P(6)).Norm());
		if ((XM)&&(YM)&&(ZM))
			return ((test-bbox.P(7)).Norm());
	
		bool Xin=((test.X()>=bbox.min.X())&&(test.X()<=bbox.max.X()));
		bool Yin=((test.Y()>=bbox.min.Y())&&(test.Y()<=bbox.max.Y()));
		bool Zin=((test.Z()>=bbox.min.Z())&&(test.Z()<=bbox.max.Z()));
	

		///EDGES CASES
		///edge case 0
		if ((Xin) &&(Ym)&&(Zm))
		{
			Line3<ScalarType> edge;
			Point3<ScalarType> dir=bbox.P(1)-bbox.P(0);
			dir.Normalize();
			edge.Set(bbox.P(0),dir);
			Point3<ScalarType> clos=ClosestPoint<ScalarType,true>(edge,test);
			return ((test-clos).Norm());
		}
		///edge case 1
		if ((Zin)&&(XM)&&(Ym))
		{
			Line3<ScalarType> edge;
			Point3<ScalarType> dir=bbox.P(5)-bbox.P(1);
			dir.Normalize();
			edge.Set(bbox.P(1),dir);
			Point3<ScalarType> clos=ClosestPoint<ScalarType,true>(edge,test);
			return ((test-clos).Norm());
		}
		///edge case 2
		if ((Xin)&&(Ym)&&(ZM))
		{
			Line3<ScalarType> edge;
			Point3<ScalarType> dir=bbox.P(5)-bbox.P(4);
			dir.Normalize();
			edge.Set(bbox.P(4),dir);
			Point3<ScalarType> clos=ClosestPoint<ScalarType,true>(edge,test);
			return ((test-clos).Norm());
		}
		///edge case 3
		if ((Zin)&&(Xm)&&(Ym))
		{
			Line3<ScalarType> edge;
			Point3<ScalarType> dir=bbox.P(4)-bbox.P(0);
			dir.Normalize();
			edge.Set(bbox.P(0),dir);
			Point3<ScalarType> clos=ClosestPoint<ScalarType,true>(edge,test);
			return ((test-clos).Norm());
		}
		///edge case 4
		if ((Xin)&&(YM)&&(Zm))
		{
			Line3<ScalarType> edge;
			Point3<ScalarType> dir=bbox.P(3)-bbox.P(2);
			dir.Normalize();
			edge.Set(bbox.P(2),dir);
			Point3<ScalarType> clos=ClosestPoint<ScalarType,true>(edge,test);
			return ((test-clos).Norm());
		}
		///edge case 5
		if ((Zin)&&(XM)&&(YM))
		{
			Line3<ScalarType> edge;
			Point3<ScalarType> dir=bbox.P(7)-bbox.P(3);
			dir.Normalize();
			edge.Set(bbox.P(3),dir);
			Point3<ScalarType> clos=ClosestPoint<ScalarType,true>(edge,test);
			return ((test-clos).Norm());
		}
		///edge case 6
		if ((Xin)&&(ZM)&&(YM))
		{
			Line3<ScalarType> edge;
			Point3<ScalarType> dir=bbox.P(7)-bbox.P(6);
			dir.Normalize();
			edge.Set(bbox.P(6),dir);
			Point3<ScalarType> clos=ClosestPoint<ScalarType,true>(edge,test);
			return ((test-clos).Norm());
		}
		///edge case 7
		if ((Zin)&&(Xm)&&(YM))
		{
			Line3<ScalarType> edge;
			Point3<ScalarType> dir=bbox.P(6)-bbox.P(2);
			dir.Normalize();
			edge.Set(bbox.P(2),dir);
			Point3<ScalarType> clos=ClosestPoint<ScalarType,true>(edge,test);
			return ((test-clos).Norm());
		}
		///edge case 8
		if ((Yin)&&(Xm)&&(Zm))
		{
			Line3<ScalarType> edge;
			Point3<ScalarType> dir=bbox.P(2)-bbox.P(0);
			dir.Normalize();
			edge.Set(bbox.P(0),dir);
			Point3<ScalarType> clos=ClosestPoint<ScalarType,true>(edge,test);
			return ((test-clos).Norm());
		}
		///edge case 9
		if ((Yin)&&(XM)&&(Zm))
		{
			Line3<ScalarType> edge;
			Point3<ScalarType> dir=bbox.P(3)-bbox.P(1);
			dir.Normalize();
			edge.Set(bbox.P(1),dir);
			Point3<ScalarType> clos=ClosestPoint<ScalarType,true>(edge,test);
			return ((test-clos).Norm());
		}
		///edge case 10
		if ((Yin)&&(XM)&&(ZM))
		{
			Line3<ScalarType> edge;
			Point3<ScalarType> dir=bbox.P(7)-bbox.P(5);
			dir.Normalize();
			edge.Set(bbox.P(5),dir);
			Point3<ScalarType> clos=ClosestPoint<ScalarType,true>(edge,test);
			return ((test-clos).Norm());
		}
		///edge case 11
		if ((Yin)&&(Xm)&&(ZM))
		{
			Line3<ScalarType> edge;
			Point3<ScalarType> dir=bbox.P(6)-bbox.P(4);
			dir.Normalize();
			edge.Set(bbox.P(4),dir);
			Point3<ScalarType> clos=ClosestPoint<ScalarType,true>(edge,test);
			return ((test-clos).Norm());
		}

		///FACES CASES
		//face 0
		if ((Xin)&&(Zin)&&(Ym))
			return (fabs(bbox.min.Y()-test.Y()));
		//face 1
		if ((Xin)&&(Zin)&&(YM))
			return (fabs(bbox.min.Y()-test.Y()));
		//face 2
		if ((Xin)&&(Yin)&&(Zm))
			return (fabs(bbox.min.Z()-test.Z()));
		//face 3
		if ((Xin)&&(Yin)&&(ZM))
			return (fabs(bbox.min.Z()-test.Z()));
		//face 4
		if ((Yin)&&(Zin)&&(Xm))
			return (fabs(bbox.min.X()-test.X()));
		//face 5
		if ((Yin)&&(Zin)&&(XM))
			return (fabs(bbox.min.X()-test.X()));

		//no more cases
		assert(0);
	}


	typedef Box3<short>  Box3s;
	typedef Box3<int>	 Box3i;
	typedef Box3<float>  Box3f;
	typedef Box3<double> Box3d;
} 
