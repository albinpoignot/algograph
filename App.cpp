#include <App.h>
#include <MainFrame.h>
#include <wx/image.h>
#include <locale.h>

#include <Drawable.h>

IMPLEMENT_APP(App);

bool App::OnInit()
{
	//Exception::activateDebugHelper();

	// on initialise les gestionnaire de format d'images
	wxInitAllImageHandlers();
	// on initialise le g�n�rateur de nombre al�atoire
	srand( (unsigned) time(NULL));
	// on force la locale � "C" (anglais ansi)
	setlocale(LC_NUMERIC, "C");

	// on cr�e la fen�tre principale
	MainFrame * mf = new MainFrame(false);
	// on affiche la fen�tre principale
	mf->Show();
	// on retourne true pour indiquer que tout c'est bien d�roul�
	return true;
}
