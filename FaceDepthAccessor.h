#ifndef FACEDEPTHACCESSOR_H_
#define FACEDEPTHACCESSOR_H_

class DrawableInCameraCoordinates;

/** Classe permettant de r�cup�rer la valeur de profondeur associ�e � une face.
 * Cette classe est utilis�e pour le tri des faces visibles.
 * @ingroup util */
class FaceDepthAccessor
{
public:
	/** L'indice de la face par rapport � un Drawable ou DrawableInCameraCoordinates */
	int index;
public:
	/** Le constructeur */
	FaceDepthAccessor();
	/** Le constructeur */
	FaceDepthAccessor(int _index);
	/** Permet d'obtenir la profondeur associ�e � la face index dans le rep�re cam�ra */
	double GetValue(const DrawableInCameraCoordinates & drawable);
};

#endif /*FACEDEPTHACCESSOR_H_*/
