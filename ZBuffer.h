#ifndef ZBUFFER_H_
#define ZBUFFER_H_

#include <Array.h>
#include <Coord2D.h>
#include <wx/wx.h>
#include <float.h>

/** Classe impl�mentant un Z-buffer
 * @ingroup dessin*/
class ZBuffer
{
private:
	/** Le tableau des profondeurs associ�s � chaque pixel de la zone de dessin */
	Array< Array<double> > depths;
	/** Bool�en indiquant si  la gestion du Z-buffer est active */
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
	/** Initialise le Z-Buffer (les pixels sont � une profondeur infinie initialement) */
	void Init()
	{
        for(int i = 0 ; i < depths.size ; ++i )
        {
            for(int j = 0 ; j < depths.data[i].size ; ++j)
            {
                depths.data[i].data[j] = DBL_MAX ;
            }
        }
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
	/** Fonction permettant de d�terminer si le pixel (p.x,p.y) peut �tre remplac� par le point p.
	 * @return true si p doit remplacer le point de m�me coordonn�es (p.x,p.y) selon la r�gle du Z-buffer
	 * i.e. si p est plus proche de la cam�ra que le m�me pixel mais de profondeur depths[x][y]. */
	inline bool ReplaceCurrent(const Coord2D p)
	{
        if( enabled )
        {
            if( p.depth <= depths.data[p.y].data[p.x] )
            {
                depths.data[p.y].data[p.x] = p.depth ;
                return true ;
            }
            else
            {
                depths.data[p.y].data[p.x] = p.depth ;
                return false ;
            }
        }
        else
        {
            return true ;
        }

	}
};

#endif /*ZBUFFER_H_*/
