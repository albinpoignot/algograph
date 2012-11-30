#ifndef FRAMECOUNTER_H_
#define FRAMECOUNTER_H_

/** @internal Classe utilitaire permettant de compter le nombre de fen�tre ouverte
 * et de terminer l'application si toutes les fen�tres sont ferm�es
 * @ingroup widgets */
class FrameCounter
{
private:
	/** @internal Le compteur de fen�tre */
	static int frameCount;
public:
	/** @internal Incr�mente le compteur de fen�tre */
	static void IncFrameCount();
	/** @internal D�cr�mente le comtpeur de fen�tre */
	static void DecFrameCount();
};

#endif /*FRAMECOUNTER_H_*/
