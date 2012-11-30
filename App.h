#ifndef APP_H_
#define APP_H_

#include <wx/wx.h>
#include <wx/app.h>

/** @defgroup widgets Les objets wxWidgets */

/**
 *  La classe par o� tout commence
 * @ingroup widgets
 */
class App : public wxApp
{
	public:
		/** La m�thode o� tout commence. c'est l'�quivalent de la fonction main */
		virtual bool OnInit();
};

DECLARE_APP(App)

#endif /*APP_H_*/
