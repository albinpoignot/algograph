#ifndef SCANLINECOMPUTER_H_
#define SCANLINECOMPUTER_H_

#include <Coord2D.h>
#include <Array.h>
#include <wx/wx.h>

/** Cette classe a pour bu de stocker toutes les informations sp�cifiques au scan line
 * @ingroup dessin */
class ScanLineComputer
{
public:
	/** Le pixel le plus � gauche sur les lignes */
	Array<int> left;
	/** Le pixel le plus � droite sur les lignes */
	Array<int> right;
	/** les trois poids associ�s au pixel le plus � gauche sur une ligne
	 *
	 * leftweight.data[ligne] est un tableau de 3 �l�ments/poids indiquant la contribution relative (somme=1) des trois sommets du triangle � ce point
	 * */
	Array< Array<double> > leftweight;
	/** les trois poids associ�s au pixel le plus � droite sur une ligne
	 *
	 * rightweight.data[ligne] est un tableau de 3 �l�ments/poids indiquant la contribution relative (somme=1) des trois sommets du triangle � ce point
	 * */
	Array< Array<double> > rightweight;
	/** L'ordonn�es minimales de la zone du triangle */
	int ymin;
	/** L'ordonn�es maximales de la zone du triangle */
	int ymax;
private:
	/** La hauteur en pixel de la zone de dessin */
	int height;
	/** La largeur en pixel de la zone de dessin */
	int width;
public:
	/** Le constructeur */
	ScanLineComputer();
	/** @internal Dimensionne la zone de dessin et donc les structures de donn�es du scanline */
	void SetSize(wxSize size);
	/** Initialise les structures de donn�es du scanline */
	void Init();
	/** Calcule les limites du triangle (p1,p2,p3) selon la m�thode scanline */
	void Compute(const Coord2D p1, const Coord2D p2, const Coord2D p3);
private:
	/** Ajoute le point (x,y) aux scanlines sachant que ce point est sur le segment p1 et p2 et
	 * que les index1 et index2 indique les indices des points correspondant aux sommets du triangle */
	void AddPoint(const int x, const int y, const Coord2D p1, const Coord2D p2,
			const int index1, const int index2);
	/** Ajoute les points du segment [p1;p2] au scanline */
	void AddEdge(const Coord2D p1, const Coord2D p2, const int index1,
			const int index2);
};

#endif /*SCANLINECOMPUTER_H_*/
