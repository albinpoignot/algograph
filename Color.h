#ifndef COLOR_H_
#define COLOR_H_

#include <FastMath.h>

/** Une classe stockant une couleur RVB
 * @ingroup dessin */
class Color
{
public:
  unsigned char red; /**< la couleur rouge cod�e sur [0;255] */
  unsigned char green; /**< la couleur verte cod�e sur [0;255] */
  unsigned char blue; /**< la couleur bleue cod�e sur [0;255] */
public:
  /** le constructeur */
  Color() :
    red(0), green(0), blue(0)
  {
    ;
  }
  /** le constructeur */
  Color(unsigned char _red, unsigned char _green, unsigned char _blue) :
    red(_red), green(_green), blue(_blue)
  {
    ;
  }
  /** op�rateur d'addition de couleur */
  Color operator+(const Color & c) const
  {
    return Color((unsigned char)FastMath::min(255, red+c.red), (unsigned char)FastMath::min(255, green+c.green),
            (unsigned char)FastMath::min(255, blue+c.blue));
  }
  /** op�rateur de multiplication par un scalaire */
  Color operator*(const double c) const
  {
    return Color((unsigned char)FastMath::min(255, FastMath::Round(c*red)), (unsigned char)FastMath::min(255,
        FastMath::Round(c*green)), (unsigned char)FastMath::min(255, FastMath::Round(c*blue)) );

  }
  /** op�rateur de composition de deux couleurs */
  Color operator*(const Color & c) const
  {
    return Color((unsigned char)FastMath::min(255, (red * c.red)/255), (unsigned char)FastMath::min(255, (green
        *c.green)/255), (unsigned char)FastMath::min(255, (blue * c.blue)/255) );
  }
  /** op�rateur de test d'�galit� */
  bool operator==(const Color & c) const
  {
    return (red == c.red) && (blue == c.blue)&& (green == c.green);
  }
};

#endif /*COLOR_H_*/
