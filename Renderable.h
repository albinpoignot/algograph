#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include <DrawableInCameraCoordinates.h>

/** Classe contenant toutes les donn�es sp�cifiques � l'objet  pour une zone de dessin
 * @ingroup data */
class Renderable
{
public:
	/** Les points 2D (x,y,profondeur) des sommets de l'objet par rapport � la zone de dessin */
	Array<Coord2D> points2D;
public:
	/** Calcule des informations sp�cifiques � une zone de dessin � partir des informations de l'objet dans le rep�re cam�ra */
	void ComputeRenderable(const DrawableInCameraCoordinates & drawable,
			const wxSize & screen);
};

#endif /*RENDERABLE_H_*/
