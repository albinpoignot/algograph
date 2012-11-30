#ifndef LIGHT_H_
#define LIGHT_H_

#include <FastMath.h>
#include <Color.h>
#include <Coord3D.h>

/** @defgroup light La gestion de la lumi�re : le mod�le d'�clairage.
 *
 * On trouve habituellement quatre types de sources lumineuses : les lumi�res directionnelles, les points lumineux, les spots lumineux et la lumi�re ambiante.
 * On se restreint ici � deux types de sources : le point lumineux et la lumi�re ambiante.
 *
 * Une source lumineuse est caract�ris�e par diff�rentes composantes de couleurs interagissant diff�remment avec les objets touch�s par les rayons lumineux :
 * ce sont les composantes ambiante, diffuse et sp�culaire. Pour simplifier, on va consid�rer que les objets n'�mettent pas de lumi�re et qu'ils sont mattes.
 * Dans ce cas, seule les composantes ambiantes et diffuses sont n�cessaires. De plus, on va supposer que l'on a une unique source de lumi�re ambiante
 * n'ayant qu'une composante ambiante et que l'on a un unique point lumineux n'ayant qu'une composante diffuse.
 * Toujours pour simplifier, on ne consid�re pas que la lumi�re s'att�nue en fonction des distances.
 *
 * @remark Il ne faut pas confondre mod�le d'�clairage et mod�le d'illumination. Le mod�le d'�clairage ne se pr�occupe que des sources lumineuses alors
 * que le mod�le d'illumination prend en compte l'effet d'un rayon lumineux sur une surface et son impact sur le reste de la suface (Mod�le simple, Gouraud ou Phong).
 * Par exemple, prenons le mod�le simple d'illumination. Dans ce mod�le, pour chaque triangle, on calcule via le mod�le d'�clairage la quantit� et la couleur de la lumi�re
 * touchant le triangle. Le mod�le simple d'illumination dit alors que la quantit� et la couleur de la lumi�re touchant chaque point du triangle est �gale � la valeur obtenue pr�c�demment.
 * Dans le mod�le de Gouraud, le mod�le d'�clairage fournit une quantit�/couleur de lumi�re par sommet du triangle et ces informations sont interpoll�s pour les autres points du triangle.
 * Dans le mod�le de Phong, le mod�le d'�clairage fournit une quantit�/couleur de lumi�re pour chaque point du triangle.
 *
 * Dans le mod�le d'�clairage, deux rayons lumineux qui touchent une surface s'ajoute i.e. les composantes des couleurs s'ajoutent.
 * Lorsqu'un rayon lumineux touche une surface alors les deux couleurs se composent (multiplicaton composante par composante).
 *
 * L'impact d'une source limineuse ambiante est identique quelque soit l'objet : tout point de l'espace re�oit la m�me quantit�/couleur de lumi�re ambiante.
 *
 * L'impact d'un point lumineux (�clairage omnidirectionnel) sur un point de l'espace (de couleur matte) est r�gi par la loi de Lambert "Pour une surface matte, l'intensit� de la lumi�re r�fl�chie est
 * d�termin�e par le cosinus de l'angle form� par la normale � la surface N et par le vecteur de direction de la lumi�re D. De plus, l'intensit� est nulle lorsque l'angle
 * entre N et D est inf�rieur ou �gale � PI/2". Si S est la position du point lumineux et C la couleur du point lumineux, alors la quantit�/couleur de re�ue par le point P est
 * m*C avec m=max{ -<N|D>, 0 } et D=(P-S)/||P-S||.
 *
 * @ingroup dessin
 * */

/** Une source de lumi�re ponctuelle omnidirectionnelle (soleil, ampoule de plafonier, ...)
 * @ingroup light */
class PointLight
{
public:
  /** La position de la source lumineuse dans l'espace */
  Coord3D position;
  /** La couleur diffuse de la source lumineuse */
  Color diffuseColor; // composante diffuse de la source lumineuse
public:
  /** Le constructeur */
  PointLight(const Coord3D & _position, const Color & _diffuseColor) :
    position(_position), diffuseColor(_diffuseColor)
  {
    ;
  }
  /** On calcule la couleur de la lumi�re re�ue par le point p de normal sp�cifi�e */
  Color GetColor(const Coord3D p, const Coord3D normal) const
  {
    Coord3D d = p - position;
    double n = d.Norm();
    double mu = FastMath::max( -normal * d / n, 0.0);
    Color c = Color((unsigned char)(FastMath::Round(diffuseColor.red*mu)),
            (unsigned char)(FastMath::Round(diffuseColor.green*mu)),
                    (unsigned char)(FastMath::Round(diffuseColor.blue*mu)) );
    return c;
  }
};

/** Une source de lumi�re ambiante
 * @ingroup light  */
class AmbientLight
{
public:
  /** La couleur de la lumi�re ambiante */
  Color ambientColor;
public:
  /** Le constructeur */
  AmbientLight(const Color & _ambientColor) :
    ambientColor(_ambientColor)
  {
    ;
  }
};

#endif /*LIGHT_H_*/
