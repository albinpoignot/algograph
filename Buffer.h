#ifndef BUFFER_H_
#define BUFFER_H_

#include <wx/wx.h>
#include <wx/image.h>
#include <Color.h>
#include <Coord2D.h>
#include <ScanLineComputer.h>
#include <ZBuffer.h>
#include <Light.h>

/** @defgroup dessin Les objets pour le dessin */

/** Une classe repr�sentant une zone de dessin/matrice de pixels
 * @ingroup dessin */
class Buffer
{
private:
	/** @internal Constructeur de recopie interdit */
	Buffer(const Buffer & b);
	/** @internal Affectation interdite */
	Buffer & operator=(const Buffer & b);
private:
	/** @internal la zone de dessin native */
	wxImage data;
public:
	/** La largeur en pixel de la zone de dessin */
	int width;
	/** La hauteur en pixel de la zone de dessin */
	int height;
	/** Un objet contenant toutes les informations utiles du scan line (limites, poids, ...) */
	ScanLineComputer scanLineComputer;
	/** Un objet qui g�re le Z-buffer */
	ZBuffer zbuffer;
public:
	/** constructeur */
	Buffer();
	/** @internal Permet d'acc�der � l'objet dessin natif */
	wxImage & GetImage();
	/** @internal d�finit la taille de la zone de dessin */
	void SetSize(wxSize size);
	/** Allume le pixel de coordonn�es pos avec la couleur c.
	 * la gestion du Z-buffer peut faire que la couleur d'un pixel n'est pas r�ellemen chang� */
	void SetPoint(const Coord2D & pos, const Color & c);
	/** Efface la zone de dessin */
	void ClearBuffer();
	/** Enregistre la zone de dessin dans un fichier : utile pour faire des captures d'�cran */
	bool SaveToFile(const wxString& name) const;

	/** Dessine une ligne de p1 � p2 selon la m�thode de Bresenheim en tenant compte de la progression de la couleur.
	 * p1 doit �tre de couleur c1, p2 de couleur c2.
	 * Les points interm�diaires correspondent � une interpolation lin�aire entre ces deux couleurs. */
	void DrawLine(const Coord2D p1, const Coord2D p2, const Color c1,
			const Color c2);
	/** Dessine un triangle dont les sommets sont p1,p2,p3 et dont les couleurs de sommets sont respectivement c1,c2,c3.
	 * L'objet scanLineComputer doit �tre utilis� pour calculer les limites "scanline" du triangle et pour calculer les poids des trois
	 * points associ�s � chaque point de la bordure du triangle.
	 * L'interpollation des couleurs se fait horizontalement. */
	void DrawFilledTriangle(const Coord2D p1, const Coord2D p2,
			const Coord2D p3, const Color c1, const Color c2, const Color c3);
	/** Dessine un triangle dont les sommets sont p1,p2,p3 et dont les couleurs de sommets sont c1,c2,c3.
	 * posi1,posi2,posi3 sont les coordonn�es 3D dans le rep�re cam�rades sommets du triangle.
	 * normal1, normal2,normal3 sont les trois normales associ�es.
	 * ambientLight donne les composantes de la lumi�re ambiente.
	 * pointLight donne les composantes du point lumineux. */
	void DrawPhongTriangle(const Coord2D p1, const Coord2D p2,
			const Coord2D p3, const Color c1, const Color c2, const Color c3,
			const Coord3D posi1, const Coord3D posi2, const Coord3D posi3,
			const Coord3D normal1, const Coord3D normal2,
			const Coord3D normal3, const AmbientLight & ambientLight,
			const PointLight & pointLight);

    private:

    bool isInside( Coord2D a, Coord2D b, Coord2D c, Coord2D point );
    bool isRight( Coord2D a, Coord2D b, Coord2D point );
};

#endif /*BUFFER_H_*/
