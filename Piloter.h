#ifndef PILOTER_H_
#define PILOTER_H_

#include <wx/wx.h>
#include <wx/panel.h>
#include <Engine.h>

/** Un widget d'affichage g�rant la manipulation de la sc�ne (d�placement, rotation, ...)
 * @ingroup widgets */
class Piloter : public wxPanel
{
public:
	/** Le constructeur */
	Piloter(wxWindow* parent, Engine * engine);

	/** @internal Fonction callback utilis�e pour l'animation de la rotation. Cela permet de n'appliquer la rotation
	 * �ventuelle de l'objet que si l'objet � pu d�j� �tre dessin� une fois depuis le dernier mouvement. */
	void AutoRotateCallBack();

	/** @internal Gestion des �v�nements */
	DECLARE_EVENT_TABLE();
public:
	/** Le moteur de rendu que l'objet doit piloter */
	Engine * engine;
	/** Des variables de r�glage d�finissant les pas de d�placements */
	double positionStep;
	/** Des variables de r�glage d�finissant les pas de d�placements */
	int rotationStep;
	/** Variable indiquant si on est en mode rotation automatique */
	bool autorotate;
private:
	/** @internal une zone de texte */
	wxStaticText *modele;
	/** @internal une zone de texte */
	wxStaticText *status;
	/** @internal une zone de texte */
	wxStaticText *methode;
	/** @internal le num�ro du mod�le en cours  */
	int idmodel;
	/** @internal l'heure de la derni�re demande de redessin de la sc�ne  */
	wxDateTime lastTime;
private:
	void OnXP(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnXM(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnYP(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnYM(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnZP(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnZM(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnCenter(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnAutoCenter(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnAutoRotate(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnRotateXP(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnRotateXM(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnRotateYP(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnRotateYM(wxCommandEvent & event);/**< @internal M�thode r�pondant � un �v�nement */
	void OnRotateZP(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnRotateZM(wxCommandEvent & event); /**<@internal M�thode r�pondant � un �v�nement */
	void OnNextModel(wxCommandEvent &event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnNextMethod(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnKaleidoscope(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void OnSave(wxCommandEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
	void Update(); /**< @internal M�thode r�pondant � un �v�nement */
	void OnIdle(wxIdleEvent & event); /**< @internal M�thode r�pondant � un �v�nement */
};

#endif /*PILOTER_H_*/
