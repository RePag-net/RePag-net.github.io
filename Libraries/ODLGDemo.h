#pragma once
//---------------------------------------------------------------------------
class CODLGDemo : public CODialog
{
	friend LRESULT CALLBACK WndProc_DLGDemo(HWND hWndDlg, unsigned int uiMessage, WPARAM wParam, LPARAM lParam);
	friend void CALLBACK frDemo_WM_Command(HWND hWndDlg, unsigned int uiMessage, WPARAM wParam, LPARAM lParam);

private:
	COEditZeile* ezEditZeile;
	COTabelle* taTabelle;
	COKnopf* kDrucken;
	COLeuchte* leLeuchte;
	void __vectorcall WM_Create(HWND hWndDlg);

protected:

public:
	void __vectorcall CODLGDemoV(void);
	VMEMORY __vectorcall COFreiV(void);
	void __vectorcall Drucken(void);

};
//---------------------------------------------------------------------------