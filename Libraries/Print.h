// ab Dateiversion 2.1.2.101
#ifndef DruckenH
#define DruckenH
//---------------------------------------------------------------------------
class CODLGDruckVorschau : public CODialog
{
	friend LRESULT CALLBACK WndProc_DLGDruckVorschau(HWND hWndDlg, unsigned int uiMessage, WPARAM wParam, LPARAM lParam);
	friend void CALLBACK frDruckVorschau_WM_Command(HWND hWndDlg, unsigned int uiMessage, WPARAM wParam, LPARAM lParam);

private:
	COKnopf* kErsteSeite;
	COKnopf* kVorherigeSeite;
	COKnopf* kNachsteSeite;
	COKnopf* kLetzteSeite;
	COKnopf* kKleiner;
	COKnopf* kGrosser;
	COKnopf* kDrucker;
	COKnopf* kDrucken;
	COKnopf* kSchliessen;
	COBildBox* bibSeite;
	char cZoom;
  COStringA* vasSchlussel;
  void __vectorcall WM_Create(HWND hWnd);
	void __vectorcall ErsteSeite(void);
	void __vectorcall LetzteSeite(void);
	void __vectorcall VorherigeSeite(void);
	void __vectorcall NachsteSeite(void);
	void __vectorcall Verkleinern(void);
	void __vectorcall Vergrossern(void);

protected:

public:
	void __vectorcall CODLGDruckVorschauV(const char* pcTitel);

};
//---------------------------------------------------------------------------
class CODLGMDruckEinstellung : public CODialog
{
	friend LRESULT CALLBACK WndProc_DLGMDruckEinstellung(HWND hWndDlg, unsigned int uiMessage, WPARAM wParam, LPARAM lParam);
  friend void CALLBACK frDruckEinstellung_WM_Paint(CODialog* pDialog, PAINTSTRUCT& stPaint);
	friend void CALLBACK frDruckEinstellung_WM_Command(HWND hWndDlg, unsigned int uiMessage, WPARAM wParam, LPARAM lParam);

private:
	COKlappBox* kbDrucker;
	COEditZeile* ezVon;
	COEditZeile* ezBis;
	COEditZeile* ezKopien;
	COSchalterGruppe* sgSeiten;
	COKnopf* kDrucker;
	COKnopf* kDrucken;
	COKnopf* kVorschau;
	COKnopf* kSchliessen;
	unsigned long ulVonSeite;
	unsigned long ulBisSeite;
	unsigned long ulKopien;
  void __vectorcall WM_Create(HWND hWnd);
	void __vectorcall Text_Von(void);
	void __vectorcall Text_Bis(void);
	void __vectorcall Text_Kopien(void);

protected:

public:
	void __vectorcall CODLGMDruckEinstellungV(const char* pcTitel);
	unsigned long __vectorcall VonSeite(void); 
	unsigned long __vectorcall BisSeite(void); 
	unsigned long __vectorcall Kopien(void); 
	void __vectorcall SetzKopien(unsigned long ulKopienA); 
	void __vectorcall Drucker(COStringA* vasName);

};
//---------------------------------------------------------------------------
class __declspec(dllimport) CODrucken
{
private:
	DEVMODE* vstDevMode;
	RECT rcSeite;
	unsigned long ulSeite;
	COList* vlSeiten;
	COStringA* vasDokument;
	CODLGMDruckEinstellung* dlgmDruckEinstellung;

protected:

public:
  void __vectorcall CODruckenV(HWND hWndHaupt, const char* pcTitel, unsigned long ulSeitenhohe, unsigned long ulSeitenbreite);
	VMEMORY __vectorcall COFreiV(void);
	void __vectorcall SeitenGrosse_mm(SIZE& stGrosse);
	HDC __vectorcall NeueSeite(void);
	void __vectorcall EndeSeite(HDC hdcEnh);
	void __vectorcall LoschSeiten(void);
	HENHMETAFILE __vectorcall Seite(void);
	void __vectorcall SetzSichtbar(void);
	void __vectorcall SetzSeitenNummer(unsigned long ulNummer);
	unsigned long __vectorcall SeitenNummer(void);
	void __vectorcall Drucken(void);
	void __vectorcall Drucker(HWND hWndDlg);
	void (CALLBACK *pfnDrucken)(CODrucken*);
	CODLGDruckVorschau* dlgDruckVorschau;
	COStream* vsmDaten; 

};
__declspec(dllimport) CODrucken* __vectorcall CODruckenV(HWND hWndHaupt, const char* pcTitel, unsigned long ulSeitenhoehe_mm, unsigned long ulSeitenbreite_mm);
__declspec(dllimport) CODrucken* vDrucken;
//---------------------------------------------------------------------------
#define _TextLinks(hdcEmf, ulx, uly, pcText, uiZeichen) (TextOut(hdcEmf, ulx, uly, pcText, uiZeichen))
#define _MMzuPixel_HDC(hdc, iIndex, iMillimeter) (GetDeviceCaps(hdc, iIndex) * iMillimeter / 25.4)
#define _MMzuPixel(idpi, iMillimeter) (idpi * iMillimeter / 25.4)
#define _Schrifthohe(hdc, iPixel, idpi) (-MulDiv(iPixel, GetDeviceCaps(hdc, LOGPIXELSY), idpi))
//---------------------------------------------------------------------------
__declspec(dllimport) void __vectorcall TextMitte(HDC hdcEmf, unsigned long& uly, RECT& rcText, char* pcText);
__declspec(dllimport) void __vectorcall TextMitte(HDC hdcEmf, unsigned long& uly, RECT& rcText, COStringA* vasText);
__declspec(dllimport) void __vectorcall TextRechts(HDC hdcEmf, unsigned long& uly, RECT& rcText, char* pcText);
__declspec(dllimport) void __vectorcall TextRechts(HDC hdcEmf, unsigned long& uly, RECT& rcText, COStringA* vasText);
//---------------------------------------------------------------------------
#endif