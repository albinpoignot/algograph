#ifndef ENGINE_H_
#define ENGINE_H_

#include <Drawable.h>
#include <Rotation.h>
#include <DrawableInCameraCoordinates.h>
#include <Camera.h>
#include <Renderer.h>
#include <FastMath.h>

class Panel3D;
class Piloter;

/** La classe principale s'occupant de g�rer le dessin d'une sc�ne
 * @ingroup dessin */
class Engine
{
private:
	/** @internal indique qu'il est n�cessaire de rafraichir la sc�ne.
	 * Ce bool�en est utilis� pour �viter de recalculer la sc�ne en permanance lorsque ce n'est pas n�cessaire. */
	bool needUpdates;
public:
	/** L'objet � dessiner dans le rep�re global */
	Drawable drawable;
	/** La rotation � appliquer � l'objet avant de le dessiner */
	Rotation rot;
	/** L'objet � dessiner dans le rep�re cam�ra */
	DrawableInCameraCoordinates effectiveDrawable;
	/** La cam�ra */
	Camera camera;
	/** @internal Les objets dessinants l'objet. Il peut y en avoir plusieurs.
	 * C'est le cas dans ce programme car on souhaite dessiner plusieurs fois la m�me sc�ne mais avec des techniques de rendu diff�rentes. */
	Array<Renderer*> renderers;
	/** @internal L'objet charg� de piloter l'�volution de la sc�ne (d�placements, ...) */
	Piloter * piloter;
private:
	/** @internal On interdit l'op�rateur d'affectation */
	Engine & operator=( const Engine & e );
	/** @internal on interdit l'op�rateur de recopie */
	Engine( const Engine & e );
public:
	/** le constructeur */
	Engine();
	/** le destructeur */
	~Engine();
	/** @internal Permet d'enregistrer un renderer aurp�s de l'objet Engine */
	void addRenderer(Renderer * renderer);
	/** Permet d'indiquer au moteur que la sc�ne � changer et qu'il faut donc la recalculer */
	void SetNeedUpdates();

	/** Rafraichit la sc�ne si c'est n�cessaire */
	void Refresh();
	/** @internal Calcule la nouvelle sc�ne et demande aux renderers de dessiner la sc�ne */
	void ReDraw();
};

#endif /*ENGINE_H_*/
