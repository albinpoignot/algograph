#ifndef DRAWABLEINCAMERACOORDINATES_H_
#define DRAWABLEINCAMERACOORDINATES_H_

#include <Array.h>
#include <Coord3D.h>
#include <Camera.h>
#include <Rotation.h>
#include <Drawable.h>
#include <FaceDepthAccessor.h>

/** Une classe stockant les informations d'un objet dans le rep�re cam�ra
 * @ingroup data */
class DrawableInCameraCoordinates
{
public:
	/** Les points 3D de l'objet dans le rep�re cam�ra. <br>
	 * @remark <br>
	 * 		p.x correspond � l'axe de la direction de la cam�ra <br>
	 *		p.y correspond � la direction vers le haut/dessus de la cam�ra<br>
	 *		p.z correspond � la direction vers la droite de la cam�ra */
	Array<Coord3D> points;
	/** Les normales associ�es � chaque point de l'objet exprim�es dans le rep�re cam�ra */
	Array<Coord3D> pointNormals;
	/** Les normales aux faces exprim�es dans le rep�re cam�ra */
	Array<Coord3D> faceNormals;
	/** La profondeur des faces exprim�e par rapport � l'axe dans lequel regarde la cam�ra i.e. 10 est plus loin de la cam�ra que 5. */
	Array<double> faceDepths;
	/** @internal Les coordonn�es des points de l'objet exprim�es dans le rep�re cam�ra mais sous une forme normalis�es. <br>
	 * La profondeur du points est normalis�e sur [0;1] si elle est dans [nearplan;farplan] : dmax*(p.x - nearplan) / (deltaX*p.x) avec deltaX=farplan-nearplan. <br>
	 *
	 * Coordonn�es 3D	=> Coordonn�es 3D normalis�es : <br>
	 * x	=> depth	: dans [0;1] <br>
	 * y	=> y		: dans [0;1] <br>
	 * z	=> x		: dans [0;1] <br>
	 */
	Array<Coord3D> pointsNormalized;
	/** Bool�en indiquant si une face est visible */
	Array<bool> faceVisibles;
	/** Liste des faces visibles tri�es par ordre de profondeur croissante (de la plus proche � la plus �loign�e) */
	Array<FaceDepthAccessor> sortedVisibleFaces;
private:
	/** @internal Calcule les informations de l'objet drawable dans le rep�re cam�ra d�finit par camera et en appliquant
	 * la rotation drawableRotation � l'objet avant le changement de rep�re du rep�re globale vers le rep�re cam�ra.
	 *
	 * drawable ===== drawableRotation ====> drawable avec rotation ===== camera ====> drawable dans le rep�re cam�ra */
	void ComputeInCameraCoordinates(const Drawable & drawable,
			const Camera & camera, const Rotation & drawableRotation);
	/** @internal Calcule la visibilit� des faces */
	void ComputeVisibilityOfFaces(const Drawable & drawable);
	/** @internal D�termine si une face est visible o� non par rapport � la cam�ra (orientation de sa normale par rapport � l'axe de la cam�ra) */
	bool IsFaceVisible(const Drawable & drawable, const int face);
	/** @internal Trie les faces visibles */
	void SortVisibleFaces(const Drawable & drawable);
public:
	/** Calcule les informations de l'objet drawable dans le rep�re cam�ra d�finit par camera et en appliquant
	 * la rotation drawableRotation � l'objet avant le changement de rep�re du rep�re globale vers le rep�re cam�ra.
	 *
	 * drawable ===== drawableRotation ====> drawable avec rotation ===== camera ====> drawable dans le rep�re cam�ra
	 *
	 * Les normales et la visibilit� des faces sont calcul�es. */
	void Compute(const Drawable & drawable, const Camera & camera,
			const Rotation & drawableRotation);
};

#endif /*DRAWABLEINCAMERACOORDINATES_H_*/
