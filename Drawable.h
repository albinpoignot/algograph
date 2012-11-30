#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <Array.h>
#include <Coord2D.h>
#include <Coord3D.h>
#include <Color.h>
#include <Face.h>
#include <Rotation.h>

/** @defgroup data Les donn�es de l'objet � dessiner */

/** Une classe stockant les donn�es de l'objet � dessiner dans le rep�re globale
 * @ingroup data */
class Drawable
{
public:
	/** les coordonn�es des points 3D de l'objet */
	Array<Coord3D> points;
	/** les couleurs des points 3D de l'objet */
	Array<Color> pointColors;

	/** Les faces/triangles composant l'objet */
	Array<Face> faces;
	/** La couleur des faces */
	Array<Color> faceColors;
	/** Bool�en � vrai si les couleurs de l'objet sont donn�s par face ou par point */
	bool colorOnFace; // vrai si les couleurs sont sur les faces, faux si les couleurs sont sur les sommets

	/** Le rayon minimale de la sph�re englobant l'objet */
	double radius; // rayon de la bounding sph�re enveloppant le drawable

	/** @internal Fonction permettant de charger un fichier de mod�le O3D (ancien format) */
	bool LoadFromO3DFile(char *FileName);
private:
	/** @internal Centre l'objet au centre du repr�re lobale i.e. aux coordonn�es (0,0,0) */
	void CenterObjectToOrigin();
public:
	/** Charge l'objet comprim� */
	void LoadPredefinedComprime();
	/** Charge l'objet canard */
	void LoadPredefinedDuck();
	/** Charge l'objet �toile */
	void LoadPredefinedEtoile();
	/** Charge l'objet noeud */
	void LoadPredefinedNoeud();
	/** Charge l'objet sph�re */
	void LoadPredefinedSphere();
	/** Charge l'objet teilleire */
	void LoadPredefinedTeapot();
	/** Chare l'objet tore */
	void LoadPredefinedTore();

	/** @internal Fonction utile pour la conversion d'un mod�le O3D en code C int�grable au programme.
	 * Utile pour �liminer les d�pendances � des fichiers de donn�es externes.  */
	void SaveAsCode(char * FileName);
};

#endif /*DRAWABLE_H_*/

