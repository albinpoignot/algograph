#ifndef IndexOutOfBoundsException_h
#define IndexOutOfBoundsException_h

#include <Exception.h>

/** Une classe lev�e lorsqu'un param�tre est hors de son domaine valide de valeur
 * @ingroup exception  */
class IndexOutOfBoundsException : public Exception
{
private:
	/** L'index qui a lev�e une exception */
	int index;
	/** La valeur minimum que peut prendre l'index */
	int min;
	/** La valeur maximum que peut prendre l'index */
	int max;
public:
	/** Le constructeur */
	IndexOutOfBoundsException(int index, int min, int max);
	/** Accesseur */
	int getIndex() const;
	/** Accesseur */
	int getMin() const;
	/** Accesseur */
	int getMax() const;
};

/** @def CheckBounds_Always(index,min,max) V�rifie que index in [min;max] et l�ve une exception IndexOutOfBoundsException en cas d'�chec */
#define CheckBounds_Always( Index, Min, Max ) \
	if (((Index) < (Min)) || ((Max) < (Index))) \
	{ \
		IndexOutOfBoundsException __e((Index), (Min), (Max)); \
		RaiseException(__e); \
	}


#ifdef DEBUG
#define CheckBounds_Debug( Index, Min, Max ) \
		if (((Index) < (Min)) || ((Max) < (Index))) \
		{ \
			IndexOutOfBoundsException __e((Index), (Min), (Max)); \
			RaiseException(__e); \
		}
#else
/** @def CheckBounds_Debut(index,min,max) Idem que CheckBounds_Always mais ne s'applique qu'en mode DEBUG */
#define CheckBounds_Debug( Index, Min, Max )
#endif

#endif
