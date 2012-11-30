#ifndef WXID_H_
#define WXID_H_

#include <wx/wx.h>

/** @internal Des identiants uniques pour g�rer les �v�nements de wxWidgets
 * @ingroup widgets */
enum
{
	wx_XP = wxID_HIGHEST,
	wx_XM,
	wx_YP,
	wx_YM,
	wx_ZP,
	wx_ZM,
	wx_CENTER,
	wx_AUTOCENTER,
	wx_AUTOROTATE,
	wx_ROTATEXP,
	wx_ROTATEXM,
	wx_ROTATEYP,
	wx_ROTATEYM,
	wx_ROTATEZP,
	wx_ROTATEZM,

	wx_NEXTMODEL,
	wx_NEXTMETHOD,
	wx_KALEIDOSCOPE,
	wx_SAVE
};

#endif /*WXID_H_*/
