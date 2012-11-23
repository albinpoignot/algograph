#ifndef RENDERER_H_
#define RENDERER_H_

#include <Buffer.h>
#include <Renderable.h>
#include <wx/wx.h>
#include <wx/image.h>
#include <Light.h>
#include <ZBuffer.h>

class Panel3D;
class Engine;

/** Une classe dessinant une sc�ne sur un buffer de pixel
 * @ingroup dessin */
class Renderer
{
private:
	/** @internal Les deux buffers permettant de g�rer un double buffering */
	Buffer buffers[2];
	/** @internal Le buffer sur lequel on peut dessiner */
	int currentBuffer;
	/** @internal Le dernier buffer qui a �t� dessin� et que l'on peut afficher � tous moments */
	int lastBufferAvailiable;
	/** @internal L'objet widget propri�taire */
	Panel3D * owner;
	/** Le moteur de rendu associ� */
	Engine * engine;
	/** @internal La taille en pixel de la zone de dessin */
	wxSize size;
public:
	/** La largeur en pixel de la zone de dessin */
	int width;
	/** La hauteur en pixel de la zone de dessin */
	int height;

	/** Le renderable � dessiner */
	Renderable renderable;
	/** Le drawable � dessiner */
	Drawable * drawable; // pointe vers le Drawable de l'engine associ�
	/** Le drawable dans le rep�re cam�ra � dessiner */
	DrawableInCameraCoordinates * effectiveDrawable; // pointe vers le DrawableInCameraCoordinates de l'engine associ�
	/** Le buffer sur lequel on doit dessiner */
	Buffer * buffer;
public:
	/** Les type de rendu */
	enum EMode
	{
		Filaire,
		FilaireCache,
		FacePleine,
		Lambert,
		Gouraud,
		Phong,
		FacePleineZBuffer,
		LambertZBuffer,
		GouraudZBuffer,
		PhongZBuffer
	};
public:
	EMode mode; /**< Le mode de rendu � effectuer */
	AmbientLight ambientLight; /**< La lumi�re ambiante */
	PointLight pointLight; /**< Le point lumineux */
	bool current; /**< @internal Bool�en indiquant si le mode courant de rendu est le rendu principale et donc dessine une croix verte */
public:
public:
	/** Le constructeur */
	Renderer(Panel3D * _owner, Engine * _engine);
	/** Le destructeur */
	~Renderer();
	/** @internal Dessine le dernier buffer disponible sur le DC (Device context) */
	void DrawBufferOnDC(wxDC & dc);
	/** @internal D�finit les dimension des buffers */
	void SetSize(wxSize _size);
	/** Effectue les calculs n�cessaire au dessin de la sc�ne puis appele la m�thode Draw pour dessiner */
	void ReDraw();

	/** Dessine la sc�ne en appellant une des m�thodes DrawXX */
	void Draw();
	/** Dessine la sc�ne en mode filaire */
	void DrawFilaire();
	/** Dessine la sc�ne en mode filaire mais en �liminant les faces cach�es */
	void DrawFilaireCache();
	/** Dessine la sc�ne en remplissant les triangles en ayant �limin� les faces cach�es mais en ne tenant pas compte de l'�clairage */
	void DrawFacePleine();
	/** Idem DrawFacePleine sauf que l'on consid�re maintenant le mod�le d'illumination simple
	 * @see light
	 * @ingroup light */
	void DrawLambert();
	/** Idem DrawFacePleine sauf que l'on consid�re maintenant le mod�le d'illumination de Gouraud
	 * @see light
	 * @ingroup light */
	void DrawGouraud();
	/** Idem DrawFacePleine sauf que l'on consid�re maintenant le mod�le d'illumination de Phong
	 * @see light
	 * @ingroup light */
	void DrawPhong();
};

#endif /*RENDERER_H_*/
