#include <FrameCounter.h>
#include <wx/wx.h>

int FrameCounter::frameCount = 0;

void FrameCounter::IncFrameCount()
{
	frameCount++; // une fen�tre de plus
}

void FrameCounter::DecFrameCount()
{
	// s'il n'y a plus de fen�tre ouverte, on termine le programme proprement
	frameCount--;
	if (frameCount == 0)
		wxTheApp->ExitMainLoop();
}
