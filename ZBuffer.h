#ifndef ZBUFFER_H_
#define ZBUFFER_H_

#include <Array.h>
#include <Coord2D.h>
#include <wx/wx.h>
#include <float.h>

/** Classe implémentant un Z-buffer
 * @ingroup dessin*/
class ZBuffer
{
private:
	/** Le tableau des profondeurs associés à chaque pixel de la zone de dessin */
	Array< Array<double> > depths;
	/** Booléen indiquant si  la gestion du Z-buffer est active */
	bool enabled;
public:
	/** Le constructeur */
	ZBuffer()
	{
		enabled = false;
	}
	/** @internal Dimensionnement de la zone de dessin et donc du Z-buffer */
	void SetSize(wxSize size)
	{
		int height = size.GetHeight();
		int width = size.GetWidth();
		depths.Resize(height);
		for (int i = 0; i < height; ++i )
			depths.data[i].Resize(width);
	}
	/** Initialise le Z-Buffer (les pixels sont à une profondeur infinie initialement) */
	void Init()
	{
		// completer ici : initialisation du buffer des profondeurs
	}
	/** Permet d'activer la gestion du Z-buffer */
	void Enable()
	{
		enabled = true;
	}
	/** Permet d'activer la gestion du Z-buffer */
	void Disable()
	{
		enabled = false;
	}
	/** Fonction permettant de déterminer si le pixel (p.x,p.y) peut être remplacé par le point p.
	 * @return true si p doit remplacer le point de même coordonnées (p.x,p.y) selon la règle du Z-buffer
	 * i.e. si p est plus proche de la caméra que le même pixel mais de profondeur depths[x][y]. */
	inline bool ReplaceCurrent(const Coord2D p)
	{
		// completer ici : retourne true si p doit remplacer le point de même coordonnées (p.x,p.y) selon les règles du Z-buffer
		// par defaut, on remplace toujours
		return true;
	}
};

#endif /*ZBUFFER_H_*/
