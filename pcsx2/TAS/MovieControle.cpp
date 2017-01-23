#include "PrecompiledHeader.h"

#include "App.h"	// use "CoreThread"
#include "Counters.h"	// use"g_FrameCount"

#include "MovieControle.h"


MovieControle g_MovieControle;


//-----------------------------------------------
// �Q�[����CoreThread�œ����Ă���A�����Ă���Ԃ�GSFrame(wxFrame)�̏������󂯕t���Ȃ�
// (�L�[���͂̎󂯕t����CoreThread����GSFrame����2�ӏ����ݒ肳��Ă���ۂ�)
// CoreThread����~���Ă���Ԃ�wxFrame�̓��͂������d�g�݂��ۂ�
//-----------------------------------------------

bool MovieControle::isStop()
{
	return (fPauseState && CoreThread.IsOpen() && CoreThread.IsPaused());
}
//-----------------------------------------------
// Counters(CoreThread)���̒�~����p
//-----------------------------------------------
void MovieControle::StartCheck()
{
	if (fStart && CoreThread.IsOpen() && CoreThread.IsPaused()) {
		CoreThread.Resume();
		fStart = false;
		fPauseState = false;
	}
}

void MovieControle::StopCheck()
{
	if (fFrameAdvance) {
		if (stopFrameCount < g_FrameCount) {
			fFrameAdvance = false;
			fStop = true;
		}
	}
	if (fStop && CoreThread.IsOpen() && CoreThread.IsRunning()) {
		CoreThread.PauseSelf();	//self����Ȃ��Ǝ~�܂�Ȃ�
		stopFrameCount = g_FrameCount;
		fPauseState = true;
	}
}



//----------------------------------
// shortcut key
//----------------------------------
void MovieControle::FrameAdvance()
{
	fFrameAdvance = true;
	fStop = false;
	fStart = true;
}
void MovieControle::TogglePause()
{
	fStop = !fStop;
	if (fStop == false) {
		fStart = true;
	}
}
void MovieControle::Pause()
{
	fStop = true;
	fFrameAdvance = false;
}
void MovieControle::UnPause()
{
	fStop = false;
	fStart = true;
	fFrameAdvance = false;
}







