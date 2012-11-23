
#ifndef FASTMATH_H__
#define FASTMATH_H__

#include <math.h>

/** Le nombre PI
 * @ingroup util */
#define PI 3.141592653589

/** Classe statique regroupant des fonctions math�matiques "rapides"
 * @ingroup util */
class FastMath
{
public:
	/** @internal Pr�-calcule un certain nombre de valeurs */
		static void Initialize();
private:
	/** @internal Classe pour forcer l'initialisation statique */
	class StaticInitializer
	{
	public:
		/** @ internal Constructeur */
		StaticInitializer()
		{
			FastMath::Initialize();
		}
	};
	/** @internal Pour forcer l'initialisation statique de la classe */
	static StaticInitializer staticInitializer;

	/** @internal Les sinus des angles de 0� � 359� */
	static double sinVal[360];
	/** @internal Les cosinus des angles de 0� � 359� */
	static double cosVal[360];
	/** @internal Les tangente des angles de 0� � 359� */
	static double tanVal[360];
public:
	/** Calcule le sinus d'un angle en degr�e (pr�cision de l'angle = 1 degr�) */
	static inline double fastSin(int angleDegree)
	{
		if (angleDegree < 0)
			return -sinVal[ ( -angleDegree) % 360 ];
		else
			return sinVal[ angleDegree % 360];
	}
	/** Calcule le cosinus d'un angle en degr�e (pr�cision de l'angle = 1 degr�) */
	static inline double fastCos(int angleDegree)
	{
		if (angleDegree < 0)
			return cosVal[ ( -angleDegree) % 360];
		else
			return cosVal[ angleDegree % 360];
	}
	/** Calcule le tangente d'un angle en degr�e (pr�cision de l'angle = 1 degr�) */
	static inline double fastTan(int angleDegree)
	{
		if (angleDegree < 0)
			return tanVal[ ( -angleDegree) % 360];
		else
			return tanVal[ angleDegree % 360];
	}
	/** Retourne le minimum de a et b
	 * @remark Si les types de donn�es de a et b sont diff�rents alors il y aura une erreur.
	 * Pour la r�soudre, il suffit de pr�ciser le type des arguments (ex: min<int>(1,0.5)) */
	template<class TData> static TData min(TData a, TData b)
	{
		if (a < b)
			return a;
		else
			return b;
	}
	/** Retourne le maximum de a et b
		 * @remark Si les types de donn�es de a et b sont diff�rents alors il y aura une erreur.
		 * Pour la r�soudre, il suffit de pr�ciser le type des arguments (ex: max<int>(1,0.5)) */
	template<class TData> static TData max(TData a, TData b)
	{
		if (a < b)
			return b;
		else
			return a;
	}
	/** Retourne l'entier le plus proche */
	static inline int Round(double d)
	{
		return (int) (d + 0.5);
	}
	/** Retourne la racine car�e du nombre */
	static inline double Sqrt(double d)
	{
		return sqrt((double)d);
	}
};

#endif /*MATH_H_*/
