#ifndef PANEL3D_H_
#define PANEL3D_H_

#include <wx/wx.h>
#include <wx/panel.h>
#include <Renderer.h>
#include <Engine.h>

/**Un widget graphique permettant d'afficher une zone de dessin
 * @ingroup widgets */
class Panel3D : public wxPanel
{
public:
	/** Le constructeur */
	Panel3D(wxWindow* parent, Engine * engine, Renderer::EMode mode);
	/** @internal Gestion des �v�nements */
	DECLARE_EVENT_TABLE();
private:
	/** @internal M�thode appell�e lorsque le widget est redimensionn� */
	void OnSize(wxSizeEvent& event);
	/** @internal M�thode appell�e lorsque le widget doit �tre redessin� */
	void OnPaint(wxPaintEvent& event);
	/** @internal M�thode appell�e lorsque le fond de la zone de dessin du widget doit �tre effac� */
	void OnEraseBackGround(wxEraseEvent& event);
public:
	/** Le renderer associ� au widget et s'occupant de dessiner */
	Renderer renderer;
};

#endif /*PANEL3D_H_*/
