#ifndef CAMERA_H_
#define CAMERA_H_

#include <Coord3D.h>
#include <Rotation.h>
#include <Drawable.h>
#include <wx/wx.h>

/** Une classe contenant toutes les informations li�es � la cam�ra.
 * @verbatim
Convention utilis�e pour la cam�ra :
Y
 ^
 |
 |   / X
 |  /
 | /
 |/
 *---------> Z
(X,Y,Z) orthonorm� direct
X est la direction vers laquelle la cam�ra regarde
Y est la direction vers le haut
Z est la direction vers la droite
@endverbatim
@ingroup dessin
 */
class Camera
{
public:
	Coord3D positionInWorld; /**< position de la camera dans le rep�re du monde */
	Rotation orientationInWorld; /**< rotation de la camera dans le rep�re du monde */
	Rotation orientation; /**< rotation du rep�re du monde dans le rep�re cam�ra */
	Coord3D position; /**< position du monde dans le rep�re camera */
	double nearplan; /**< la position du plan near sur l'axe X */
	double farplan; /**< la position du plan far sur l'axe X */
	double aspectRatio; /**< aspect ratio horizontal/vertical Z = ratio * Y */
	int upwardAngle; /**< demi angle vertical du champ de vision en degr� */
public:
	/** Calcule les donn�es cam�ra en fonction de la position et de l'orientation de la cam�ra dans le rep�re global */
	void Set(const Coord3D & _positionInWorld,
			const Rotation & _orientationInWorld);
	/** Calcul la position et l'orientation de la cam�ra pour que l'objet drawable exprim� dans le rep�re global soit enti�rement visible */
	void SetFromDrawable(const Drawable & drawable, const double scale = 1.2,
			const int _upwardAngle = 40);
};

#endif /*CAMERA_H_*/
