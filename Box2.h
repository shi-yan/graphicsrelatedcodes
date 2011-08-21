#pragma once

#include <assert.h>
#include "base.h"
#include "point2.h"
namespace GGL 
{

	/** \addtogroup space */
	/*@{*/

	/**
		Templated class for a 2D bounding box. It is stored just as two Point2	
		@param BoxScalarType (Template Parameter) Specifies the scalar field.
	*/
	template <class BoxScalarType>
	class Box2
	{
	public:
		/// The scalar type
		typedef BoxScalarType ScalarType;

		/// min coordinate point
		Point2<BoxScalarType> min;
		/// max coordinate point
		Point2<BoxScalarType> max;
		/// Standard constructor
		inline  Box2() 
		{
			min.X()= 1; 
			max.X()= -1; 
			min.Y()= 1; 
			max.Y()= -1; 
		}
		/// Copy constructor
		inline  Box2( const Box2 & b ) 
		{
			min=b.min; 
			max=b.max; 
		}
		/// Distructor
		inline ~Box2() 
		{
		}
		/// Operator to compare two bounding box
		inline bool operator == ( Box2 const & p ) const
		{
			return min==p.min && max==p.max;
		}
		/// Initializing the bounding box with a point
		void Set( const Point2<BoxScalarType> & p )
		{
			min = max = p;
		}
		// Initializing with the values
		inline void Set( BoxScalarType minx, BoxScalarType miny, BoxScalarType maxx, BoxScalarType maxy )
		{
			min[0] = minx;
			min[1] = miny;
			max[0] = maxx;
			max[1] = maxy;
		}
		/// Set the bounding box to a null value
		void SetNull()
		{
			min.X()= 1; max.X()= -1; min.Y()= 1; max.Y()= -1;
		}
		/** Function to add two bounding box
			@param b Il bounding box che si vuole aggiungere
		*/
		void Add( Box2 const & b )
		{
			if(IsNull())
			{
				min=b.min;
				max=b.max;
			}
			else
			{
				if(min.X() > b.min.X()) min.X() = b.min.X();
				if(min.Y() > b.min.Y()) min.Y() = b.min.Y();

				if(max.X() < b.max.X()) max.X() = b.max.X();
				if(max.Y() < b.max.Y()) max.Y() = b.max.Y();
			}
		}
		/** Funzione per aggiungere un punto al bounding box. Il bounding box viene modificato se il punto
			cade fuori da esso.
			@param p The point 2D
		*/
		void Add( const Point2<BoxScalarType> & p )
		{
			if(IsNull()) 
				Set(p);
			else 
			{
				if(min.X() > p.X()) min.X() = p.X();
				if(min.Y() > p.Y()) min.Y() = p.Y();

				if(max.X() < p.X()) max.X() = p.X();
				if(max.Y() < p.Y()) max.Y() = p.Y();
			}
		}
		/** Calcola l'intersezione tra due bounding box. Al bounding box viene assegnato il valore risultante.
			@param b Il bounding box con il quale si vuole effettuare l'intersezione
		*/
		void Intersect( const Box2 & b )
		{
			if(min.X() < b.min.X()) min.X() = b.min.X();
			if(min.Y() < b.min.Y()) min.Y() = b.min.Y();

			if(max.X() > b.max.X()) max.X() = b.max.X();
			if(max.Y() > b.max.Y()) max.Y() = b.max.Y();

			if(min.X()>max.X() || min.Y()>max.Y()) SetNull();
		}

		/** Trasla il bounding box di un valore definito dal parametro.
			@param p Il bounding box trasla sulla x e sulla y in base alle coordinate del parametro
		*/
		void Translate( const Point2<BoxScalarType> & p )
		{
			min += p;
			max += p;
		}
		/** Verifica se un punto appartiene ad un bounding box.
			@param p The point 2D
			@return True se p appartiene al bounding box, false altrimenti
		*/
		bool IsIn( Point2<BoxScalarType> const & p ) const
		{
			return (min.X() <= p.X() && p.X() <= max.X() &&		min.Y() <= p.Y() && p.Y() <= max.Y());
		}
		/** Verifica se un punto appartiene ad un bounding box aperto sul max.
			@param p The point 2D
			@return True se p appartiene al bounding box, false altrimenti
		*/
		bool IsInEx( Point2<BoxScalarType> const & p ) const
		{
			return  (	min.X() <= p.X() && p.X() < max.X() &&	min.Y() <= p.Y() && p.Y() < max.Y() 	);
		}
		/** Verifica se due bounding box collidono cioe' se hanno una intersezione non vuota. Per esempio
			due bounding box adiacenti non collidono.
			@param b A bounding box
			@return True se collidoo, false altrimenti
		*/
		bool Collide( Box2 const &b )
		{
			Box2 bb=*this;
			bb.Intersect(b);
			return bb.IsValid();
		}
		/** Controlla se il bounding box e' nullo.
			@return True se il bounding box e' nullo, false altrimenti
		*/
		inline bool IsNull() const 
		{
			return min.X()>max.X() || min.Y()>max.Y(); 
		}
		/** Controlla se il bounding box e' consistente.
			@return True se il bounding box e' consistente, false altrimenti
		*/
		inline bool IsValid() const 
		{ 
			return min.X()<max.X() && min.Y()<max.Y(); 
		}
		/** Controlla se il bounding box e' vuoto.
			@return True se il bounding box e' vuoto, false altrimenti
		*/
		inline bool IsEmpty() const 
		{
			return min==max; 
		}
		/// Restituisce la lunghezza della diagonale del bounding box.
		BoxScalarType Diag() const
		{
			return Distance(min,max);
		}
		/// Calcola il centro del bounding box.
		Point2<BoxScalarType> Center() const
		{
			return (min+max)/2;
		}
		/// Calcola l'area del Bounding box.
		inline BoxScalarType Area() const
		{
			return (max[0]-min[0])*(max[1]-min[1]);
		}
		///Calcola la dimensione del bounding box sulla x.
		inline BoxScalarType DimX() const 
		{
			return max.X()-min.X(); 
		}
		/// Calcola la dimensione del bounding box sulla y.
		inline BoxScalarType DimY() const 
		{
			return max.Y()-min.Y(); 
		}

		/// Calcola la dimensione del bounding box.
		inline Point2<BoxScalarType> Dim() const 
		{
			return max-min; 
		}

		inline void Normalize( Point2<BoxScalarType> & p )
		{
			p -= min;
			p[0] /= max[0]-min[0];
			p[1] /= max[1]-min[1];
		}
	}; // end class definition

	template <class ScalarType> 
	ScalarType DistancePoint2Box2(const Point2<ScalarType> &test,  const Box2<ScalarType> &bbox)
	{
		///test possible position respect to bounding box
		if (!bbox.IsIN(test))
		{
			if ((test.X()<=bbox.min.X())&&(test.Y()<=bbox.min.Y()))
				return ((test-bbox.min).Norm());
			else if ((test.X()>=bbox.min.X())&&(test.X()<=bbox.max.X())&&	(test.Y()<=bbox.min.Y()))
				return (bbox.min.Y()-test.Y());
			else if ((test.X()>=bbox.max.X())&&		(test.Y()<=bbox.min.Y()))
				return ((test-Point2<ScalarType>(bbox.max.X(),bbox.min.Y())).Norm());
			else if ((test.Y()>=bbox.min.Y())&&		(test.Y()<=bbox.max.Y())&&			(test.X()>=bbox.max.X()))
				return (test.X()-bbox.max.X());
			else if ((test.X()>=bbox.max.X())&&(test.Y()>=bbox.max.Y()))
				return ((test-bbox.max).Norm());
			else if ((test.X()>=bbox.min.X())&&	(test.X()<=bbox.max.X())&&	(test.Y()>=bbox.max.Y()))
				return (test.Y()-bbox.max.Y());
			else if ((test.X()<=bbox.min.X())&&	(test.Y()>=bbox.max.Y()))
				return ((test-Point2<ScalarType>(bbox.min.X(),bbox.max.Y())).Norm());
			else if ((test.X()<=bbox.min.X())&&	(test.Y()<=bbox.max.Y())&&	(test.Y()>=bbox.min.Y()))
				return (bbox.min.X()-test.X());
		}
		else
		{			//return minimum distance
			ScalarType dx=std::min<ScalarType>(fabs(test.X()-bbox.min.X()),fabs(bbox.max.X()-test.X()));
			ScalarType dy=std::min<ScalarType>(fabs(test.Y()-bbox.min.Y()),fabs(bbox.max.Y()-test.Y()));
			return(std::min<ScalarType>(dx,dy));
		}
	}

	/// Specificazione di box of short
	typedef Box2<short>  Box2s;
	/// Specificazione di box of int
	typedef Box2<int>	 Box2i;
	/// Specificazione di box of float
	typedef Box2<float>  Box2f;
	/// Specificazione di box of double
	typedef Box2<double> Box2d;

	/*@}*/
} // end namespace