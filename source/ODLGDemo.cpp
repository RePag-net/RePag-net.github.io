#include "HDemo.h"
#include "ODLGDemo.h"
//-----------------------------------------------------------------------------------------------------------------------------------------
CODLGDemo* dlgDemo;
#define _dlgDemo ((CODLGDemo*)pDialog)
//-----------------------------------------------------------------------------------------------------------------------------------------
typedef struct STSeite
{
 HDC hdcEmf;
 LOGFONT lfSchrift;
 unsigned long ulx;
 unsigned long uly;
 unsigned long ulx_Max;
 unsigned long uly_Max;
 unsigned long ulZeile;
 unsigned long ulSeitenzahl;
 int iLOGPIXELSX;
 int iLOGPIXELSY;
} STSeite;
//-----------------------------------------------------------------------------------------------------------------------------------------
typedef struct STSpalten
{
 unsigned long ulDatum;
 unsigned long ulListe;
 unsigned long ulFloat;
 unsigned long ulKomma4;
 unsigned long ulFloat_Komma4;
 unsigned long ulBool;
} STSpalten;
//-----------------------------------------------------------------------------------------------------------------------------------------
void __vectorcall fnDrucken_Kopf(STSeite& stSeite, STSpalten& stSpalten)
{
 RECT rcText;
 stSeite.lfSchrift.lfWeight = FW_BOLD;
 HFONT hFont = CreateFontIndirect(&stSeite.lfSchrift);
 SelectObject(stSeite.hdcEmf, hFont);

 rcText.top = stSeite.uly + 2; rcText.bottom = stSeite.uly + stSeite.ulZeile; rcText.left = stSpalten.ulDatum; rcText.right = stSpalten.ulListe;
 TextMitte(stSeite.hdcEmf, stSeite.uly , rcText, "Datum");

 rcText.top = stSeite.uly + 2; rcText.bottom = stSeite.uly + stSeite.ulZeile; rcText.left = stSpalten.ulListe; rcText.right = stSpalten.ulFloat;
 TextMitte(stSeite.hdcEmf, stSeite.uly , rcText, "Liste");

 rcText.top = stSeite.uly + 2; rcText.bottom = stSeite.uly + stSeite.ulZeile; rcText.left = stSpalten.ulFloat; rcText.right = stSpalten.ulKomma4;
 TextMitte(stSeite.hdcEmf, stSeite.uly, rcText, "Float");

 rcText.top = stSeite.uly + 2; rcText.bottom = stSeite.uly + stSeite.ulZeile; rcText.left = stSpalten.ulKomma4; rcText.right = stSpalten.ulFloat_Komma4;
 TextMitte(stSeite.hdcEmf, stSeite.uly, rcText, "Komma4");

 rcText.top = stSeite.uly + 2; rcText.bottom = stSeite.uly + stSeite.ulZeile; rcText.left = stSpalten.ulFloat_Komma4; rcText.right = stSpalten.ulBool;
 TextMitte(stSeite.hdcEmf, stSeite.uly, rcText, "Float + Komma4");

 rcText.top = stSeite.uly + 2; rcText.bottom = stSeite.uly + stSeite.ulZeile; rcText.left = stSpalten.ulBool; rcText.right = stSeite.ulx_Max;
 TextMitte(stSeite.hdcEmf, stSeite.uly, rcText, "Bool");
 DeleteObject(hFont);
 stSeite.lfSchrift.lfWeight = FW_DONTCARE;

 MoveToEx(stSeite.hdcEmf, stSpalten.ulListe - 2, stSeite.uly, NULL);
 LineTo(stSeite.hdcEmf, stSpalten.ulListe - 2, stSeite.uly + stSeite.ulZeile);
 MoveToEx(stSeite.hdcEmf, stSpalten.ulFloat - 2, stSeite.uly, NULL);
 LineTo(stSeite.hdcEmf, stSpalten.ulFloat - 2, stSeite.uly + stSeite.ulZeile);
 MoveToEx(stSeite.hdcEmf, stSpalten.ulKomma4 - 2, stSeite.uly, NULL);
 LineTo(stSeite.hdcEmf, stSpalten.ulKomma4 - 2, stSeite.uly + stSeite.ulZeile);
 MoveToEx(stSeite.hdcEmf, stSpalten.ulFloat_Komma4 - 2, stSeite.uly, NULL);
 LineTo(stSeite.hdcEmf, stSpalten.ulFloat_Komma4 - 2, stSeite.uly + stSeite.ulZeile);
 MoveToEx(stSeite.hdcEmf, stSpalten.ulBool - 2, stSeite.uly, NULL);
 LineTo(stSeite.hdcEmf, stSpalten.ulBool - 2, stSeite.uly + stSeite.ulZeile);

 stSeite.uly += _MMzuPixel(stSeite.iLOGPIXELSY, 4);
 MoveToEx(stSeite.hdcEmf, stSeite.ulx, stSeite.uly, NULL);
 LineTo(stSeite.hdcEmf, stSeite.ulx_Max, stSeite.uly);
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void __vectorcall fnDrucken_Fuss(STSeite& stSeite, STSpalten& stSpalten)
{
 HFONT hFont = CreateFontIndirect(&stSeite.lfSchrift);
 SelectObject(stSeite.hdcEmf, hFont);

 char c20Zahl[20]; COTime zZeit; zZeit.Now(); zZeit.CHARDateTime(c20Zahl);
 TextOut(stSeite.hdcEmf, stSpalten.ulDatum, stSeite.uly_Max + stSeite.ulZeile, c20Zahl, 19);
 COStringA asSeitenNummer("Seite "); asSeitenNummer += ULONGtoCHAR(c20Zahl, ++stSeite.ulSeitenzahl);
 TextOut(stSeite.hdcEmf, stSpalten.ulBool + _MMzuPixel(stSeite.iLOGPIXELSX, 15), stSeite.uly_Max + stSeite.ulZeile, asSeitenNummer.c_Str(), asSeitenNummer.Length());
 DeleteObject(hFont);

 MoveToEx(stSeite.hdcEmf, stSeite.ulx, stSeite.uly_Max + stSeite.ulZeile, NULL);
 LineTo(stSeite.hdcEmf, stSeite.ulx_Max, stSeite.uly_Max + stSeite.ulZeile);
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void __vectorcall fnDrucken(CODrucken* pDrucken)
{
 STSeite stSeite; STSpalten stSpalten;
 stSeite.hdcEmf = vDrucken->NeueSeite();
 SetBkMode(stSeite.hdcEmf, TRANSPARENT); SetTextColor(stSeite.hdcEmf, RGB(0, 0, 0));

 stSeite.iLOGPIXELSX = GetDeviceCaps(stSeite.hdcEmf, LOGPIXELSX);
 stSeite.iLOGPIXELSY = GetDeviceCaps(stSeite.hdcEmf, LOGPIXELSY);

 stSeite.lfSchrift.lfWidth = 0;
 stSeite.lfSchrift.lfEscapement = GM_COMPATIBLE;
 stSeite.lfSchrift.lfOrientation = GM_COMPATIBLE;
 stSeite.lfSchrift.lfWeight = FW_DONTCARE;
 stSeite.lfSchrift.lfItalic = FALSE;
 stSeite.lfSchrift.lfUnderline = FALSE;
 stSeite.lfSchrift.lfStrikeOut = FALSE;
 stSeite.lfSchrift.lfCharSet = DEFAULT_CHARSET;
 stSeite.lfSchrift.lfOutPrecision = OUT_DEVICE_PRECIS;
 stSeite.lfSchrift.lfClipPrecision = CLIP_DEFAULT_PRECIS;
 stSeite.lfSchrift.lfQuality = DEFAULT_QUALITY;
 stSeite.lfSchrift.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

 stSeite.ulx = _MMzuPixel(stSeite.iLOGPIXELSX, 20);
 stSeite.uly = _MMzuPixel(stSeite.iLOGPIXELSY, 10);
 stSeite.ulx_Max = stSeite.ulx + _MMzuPixel(stSeite.iLOGPIXELSX, 180);
 stSeite.uly_Max = _MMzuPixel(stSeite.iLOGPIXELSY, 275);
 stSeite.ulZeile = _MMzuPixel(stSeite.iLOGPIXELSY, 4);

 stSpalten.ulDatum = stSeite.ulx;
 stSpalten.ulListe = stSpalten.ulDatum + _MMzuPixel(stSeite.iLOGPIXELSX, 35);
 stSpalten.ulFloat = stSpalten.ulListe + _MMzuPixel(stSeite.iLOGPIXELSX, 30);
 stSpalten.ulKomma4 = stSpalten.ulFloat + _MMzuPixel(stSeite.iLOGPIXELSX, 30);
 stSpalten.ulFloat_Komma4 = stSpalten.ulKomma4 + _MMzuPixel(stSeite.iLOGPIXELSX, 30);
 stSpalten.ulBool = stSpalten.ulFloat_Komma4 + _MMzuPixel(stSeite.iLOGPIXELSX, 30);

 MemCopy(stSeite.lfSchrift.lfFaceName, "Times New Roman", 16);
 stSeite.lfSchrift.lfHeight = _Schrifthohe(stSeite.hdcEmf, 17, 96);
 HFONT hFont = CreateFontIndirect(&stSeite.lfSchrift);	 
 SelectObject(stSeite.hdcEmf, hFont);
 TextOut(stSeite.hdcEmf, stSpalten.ulDatum, stSeite.uly, "Demodruck", 9);
 DeleteObject(hFont);

 MemCopy(stSeite.lfSchrift.lfFaceName, "Arial Standart", 15);
 stSeite.lfSchrift.lfHeight = _Schrifthohe(stSeite.hdcEmf, 12, 96);
 stSeite.uly += _MMzuPixel(stSeite.iLOGPIXELSY, 7);
 stSeite.ulSeitenzahl = 0;
 vDrucken->vsmDaten->SetPosition(0, STM_POS_ANFANG);
 if(vDrucken->vsmDaten->End()){
   fnDrucken_Kopf(stSeite, stSpalten);
   fnDrucken_Fuss(stSeite, stSpalten);
   vDrucken->EndeSeite(stSeite.hdcEmf);
 }
 else{ RECT rcText; char c20Zahl[20]; float fTemp; USHORT usTemp; bool bTemp; COTime zTemp; COStringA asTemp; COComma4 k4Temp;
	 while(!vDrucken->vsmDaten->End()){
		 if(stSeite.ulSeitenzahl){ stSeite.hdcEmf = vDrucken->NeueSeite(); SetBkMode(stSeite.hdcEmf, TRANSPARENT); SetTextColor(stSeite.hdcEmf, RGB(0, 0, 0)); stSeite.uly = _MMzuPixel(stSeite.iLOGPIXELSY, 10); }
		 fnDrucken_Kopf(stSeite, stSpalten);
		 hFont = CreateFontIndirect(&stSeite.lfSchrift);	 
		 SelectObject(stSeite.hdcEmf, hFont);
		 do{
			 vDrucken->vsmDaten->ReadTime(&zTemp);
			 if(!zTemp.IsZero()){
				 rcText.top = stSeite.uly + 2; rcText.bottom = stSeite.uly + stSeite.ulZeile; rcText.left = stSpalten.ulDatum; rcText.right = stSpalten.ulListe;
				 TextMitte(stSeite.hdcEmf, stSeite.uly, rcText, zTemp.CHARDateTime(c20Zahl));
			 }

			 vDrucken->vsmDaten->ReadStringA(&asTemp, FT_SHORTSTR);
			 rcText.top = stSeite.uly + 2; rcText.bottom = stSeite.uly + stSeite.ulZeile; rcText.left = stSpalten.ulListe; rcText.right = stSpalten.ulFloat;
			 _TextLinks(stSeite.hdcEmf, stSpalten.ulListe, stSeite.uly, asTemp.c_Str(), asTemp.Length());

			 vDrucken->vsmDaten->Read(&fTemp, BY_FLOAT);
			 rcText.top = stSeite.uly + 2; rcText.bottom = stSeite.uly + stSeite.ulZeile; rcText.left = stSpalten.ulFloat; rcText.right = stSpalten.ulKomma4 - 3;
			 TextRechts(stSeite.hdcEmf, stSeite.uly, rcText, FLOAT_B10toCHAR(c20Zahl, fTemp, 7));

			 vDrucken->vsmDaten->ReadComma4(&k4Temp); 
			 rcText.top = stSeite.uly + 2; rcText.bottom = stSeite.uly + stSeite.ulZeile; rcText.left = stSpalten.ulKomma4; rcText.right = stSpalten.ulFloat_Komma4 - 3;
			 TextRechts(stSeite.hdcEmf, stSeite.uly, rcText, Comma4toCHAR(c20Zahl, &k4Temp, 2));		 

			 vDrucken->vsmDaten->ReadStringA(&asTemp, FT_SHORTSTR);
			 rcText.top = stSeite.uly + 2; rcText.bottom = stSeite.uly + stSeite.ulZeile; rcText.left = stSpalten.ulFloat_Komma4; rcText.right = stSpalten.ulBool - 3;
			 TextRechts(stSeite.hdcEmf, stSeite.uly, rcText, &asTemp);

			 vDrucken->vsmDaten->Read(&usTemp, BY_USHORT); vDrucken->vsmDaten->SetPosition(usTemp, STM_POS_AKTUELL);

			 vDrucken->vsmDaten->Read(&bTemp, BY_BOOL);
			 (bTemp ? asTemp = "Ja" : asTemp = "Nein");
			 rcText.top = stSeite.uly + 2; rcText.bottom = stSeite.uly + stSeite.ulZeile; rcText.left = stSpalten.ulBool; rcText.right = stSeite.ulx_Max;
			 TextMitte(stSeite.hdcEmf, stSeite.uly, rcText, &asTemp);

			 MoveToEx(stSeite.hdcEmf, stSpalten.ulListe - 2, stSeite.uly, NULL);
			 LineTo(stSeite.hdcEmf, stSpalten.ulListe - 2, stSeite.uly + stSeite.ulZeile);
			 MoveToEx(stSeite.hdcEmf, stSpalten.ulFloat - 2, stSeite.uly, NULL);
			 LineTo(stSeite.hdcEmf, stSpalten.ulFloat - 2, stSeite.uly + stSeite.ulZeile);
			 MoveToEx(stSeite.hdcEmf, stSpalten.ulKomma4 - 2, stSeite.uly, NULL);
			 LineTo(stSeite.hdcEmf, stSpalten.ulKomma4 - 2, stSeite.uly + stSeite.ulZeile);
			 MoveToEx(stSeite.hdcEmf, stSpalten.ulFloat_Komma4 - 2, stSeite.uly, NULL);
			 LineTo(stSeite.hdcEmf, stSpalten.ulFloat_Komma4 - 2, stSeite.uly + stSeite.ulZeile);
			 MoveToEx(stSeite.hdcEmf, stSpalten.ulBool - 2, stSeite.uly, NULL);
			 LineTo(stSeite.hdcEmf, stSpalten.ulBool - 2, stSeite.uly + stSeite.ulZeile);

			 stSeite.uly += stSeite.ulZeile;
		 }
		 while(stSeite.uly < stSeite.uly_Max && !vDrucken->vsmDaten->End());

		 DeleteObject(hFont);
		 fnDrucken_Fuss(stSeite, stSpalten);
		 vDrucken->EndeSeite(stSeite.hdcEmf);
	 }
 }
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void __vectorcall fnEingabeMaske(COTabBasis* pTabelle)
{
 switch(pTabelle->SelectedSpalte()){
		 case  6 : pTabelle->EingabeBild_Berechtigungen(ZR_OFFNEN); break;
		 case  7 : pTabelle->EingabeDokument_Berechtigungen(ZR_LADEN | ZR_OFFNEN | ZR_LOSCHEN); break;
		 case  5 : pTabelle->EingabeText_SetzZeichen_Max(20);
		 default : pTabelle->EingabeZeile_Zeichenvorgabe(ZV_ALLE); pTabelle->EingabeZeile_Zeichenmaske(NULL);
 }
}
//-----------------------------------------------------------------------------------------------------------------------------------------
bool __vectorcall fnPrufenWert(COTabBasis* pTabelle, COStringA* vasFehlermeldung)
{
 if(pTabelle->SelectedSpalte() == 3){ COStringA asWert; COComma4 k4Zahl;
   if(pTabelle->Prufwert(&asWert)->COMMA4(&k4Zahl)->FLOAT() > 12.0){ *vasFehlermeldung = "Der Wert ist zu gross. Er muss kleiner 12,0 sein."; return false; }
 }
 return true;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void __vectorcall fnLeerFeld(COTabBasis* pTabelle)
{
 char c20Zahl[20]; COFeld* vfwk4Zahl = COFeldV(FT_COMMA4); COFeld* vfwfZahl = COFeldV(FT_FLOAT); COComma4 k4Zahl_1; COComma4 k4Zahl_2;
 long lTest; short sTest;
 switch(pTabelle->SelectedSpalte()){
		 case  2 :
		 case  3 :
		 case  4 : k4Zahl_2 = *(PFLOAT)pTabelle->FeldWert(vfwfZahl, pTabelle->SelectedZeile(), 2)->Wert();
							 *(COComma4*)pTabelle->FeldWert(vfwk4Zahl, pTabelle->SelectedZeile(), 3)->KOMMA4(&k4Zahl_1) += k4Zahl_2;
							 pTabelle->LeerFeld(Comma4toCHAR(c20Zahl, &k4Zahl_1, 4), pTabelle->SelectedZeile(), 4);
 }
 VMFreiV(vfwk4Zahl); VMFreiV(vfwfZahl);
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void __vectorcall fnEingabeListe(COTabBasis* pTabelle)
{
 if(pTabelle->SelectedSpalte() == 1){ BYTE ucIndex; COFeld* vfwasFeld = COFeldV(FT_SHORTSTR);
	 pTabelle->EingabeListe_Grosse(75, 80);
   pTabelle->EingabeListe_Text("Eintrag A\nEintrag B\nEintrag C\nEintrag D\nEintrag E\nEintrag F\nEintrag G\nEintrag H\n"); 
   COStringA* vasEintrag = COStringAV(pTabelle->FeldWert(vfwasFeld, pTabelle->SelectedZeile(), 1)->Wert());
   pTabelle->EingabeListe_SuchUndSetzEintrag(vasEintrag, ucIndex);
	 VMFreiV(vasEintrag); VMFreiV(vfwasFeld); 
 }
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void __vectorcall fnDatumZeitFormat(unsigned char ucSpalte, COStringA* vasDatumformat, COStringA* vasZeitformat)
{
 if(ucSpalte == 0){
	 *vasDatumformat = "ddd' 'dd'. 'MMM' 'yyyy"; *vasZeitformat = "' 'HH':'mm";
 }
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void CALLBACK fnEffekt_Timer(COElement* pElement, bool bTimerOrWaitFired)
{
 static bool bFarbwechsel;
 if(bFarbwechsel){ bFarbwechsel = false; ((COLeuchte*)pElement)->Leuchtfarbe(255, 120, 0); }
 else{ bFarbwechsel = true; ((COLeuchte*)pElement)->Leuchtfarbe(130, 50, 25); }
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void __vectorcall fnDemo_WM_Paint(CODialog* pDialog, PAINTSTRUCT& stPaint)
{
 HFONT hFont = CreateFontIndirect(&pDialog->lfSchrift);	
 SelectObject(stPaint.hdc, hFont);
 SetBkMode(stPaint.hdc, TRANSPARENT); 
 SetTextColor(stPaint.hdc, RGB(230, 230, 230));
 TextOut(stPaint.hdc, 30, 430, "Bool-Spalte nur umschaltbar durch drücken der Leertaste", 54);
 DeleteObject(hFont);
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void __vectorcall frDemo_WM_Command(HWND hWndDlg, unsigned int uiMessage, WPARAM wParam, LPARAM lParam)
{
 switch(LOWORD(wParam)){
		 case IDE_DLG_SICHTBAR      : dlgDemo->leLeuchte->Effekt_Timer(true, 1000, fnEffekt_Timer);
			                            break;
		 case IDE_KDRUCKEN          : dlgDemo->Drucken();
															    break;
     case IDM_INFO_INSTRUCTIONS : CPUInstructions(hWndDlg);
                                  break;
		 case IDM_EXIT              : dlgDemo->Schliessen();
															    break;
										    default : DefWindowProc(hWndDlg, uiMessage, wParam, lParam);
 }
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void __vectorcall CODLGDemo::CODLGDemoV(void)
{
 CODialogV("DLGDemo", false, WndProc_DLGDemo); FensterStil(WS_OVERLAPPEDWINDOW | WS_VISIBLE); ErweitertStil(WS_EX_CONTROLPARENT); FensterTitel("RePag-Demo");
 Menu(IDC_DEMO); Icon(IDI_DEMO); IconSm(IDI_SMALL);
 stHintergrundfarbe.ucRot = 80; stHintergrundfarbe.ucGrun = 80; stHintergrundfarbe.ucBlau = 80;
 pfnWM_Paint = fnDemo_WM_Paint;
 pfnWM_Command = frDemo_WM_Command;

 Hintergrundeffekt(HGE_HINTERGRUND | HGE_BELEUCHTUNG_V | HGE_BELEUCHTUNG_H);
 Hintergrundeffektfarbe(100, 200, 100);
 Hintergrundeffektrand(20, 20, 20, 20);

 taTabelle = COTabelleV("taTabelle_DLGDemo", IDE_TATABELLE, 5, 9);
 taTabelle->Hintergrundfarbe(100, 100, 100);
 taTabelle->Berechtigungen(ZR_EINFUGEN | ZR_ANDERN | ZR_LOSCHEN | ZR_SENDEN | ZR_OFFNEN | ZR_SPEICHERN);
 taTabelle->pfnEingabeMaske = fnEingabeMaske;
 taTabelle->pfnPrufenWert = fnPrufenWert;
 taTabelle->pfnLeerFeld = fnLeerFeld;
 taTabelle->pfnEingabeListe = fnEingabeListe;

 taTabelle->pfnDatumZeitFormat = fnDatumZeitFormat;
 taTabelle->EingabeText_Grosse(150, 150);
 taTabelle->BoolWertText("Ja", "Nein");

 taTabelle->Spalte(0, "Datum", 130, TXA_LINKS | TXA_UNTEN | TXF_DATUMZEITEXTERN, FT_DATE); 
 taTabelle->Spalte(1, "Liste", 80, TXA_MITTEHORIZONTAL | TXA_UNTEN, FT_LISTSTR);
 taTabelle->Spalte(2, "Float Basis 10", 110, TXA_RECHTS | TXA_UNTEN | TXF_KOMMA_7, FT_FLOAT);
 taTabelle->Spalte(3, "Komma4", 90, TXA_RECHTS | TXA_UNTEN | TXF_KOMMA_2, FT_COMMA4);
 taTabelle->Spalte(4, "Float + Komma4", 100, TXA_RECHTS | TXA_UNTEN | TX_UNANDERBAR, FT_EMPTY);
 taTabelle->Spalte(5, "Memo", 80, TXA_MITTEHORIZONTAL | TXA_UNTEN, FT_MEMOSTR);
 taTabelle->Spalte(6, "Bild", 80, TXA_MITTEHORIZONTAL | TXA_UNTEN, FT_SMALLIMAGE);
 taTabelle->Spalte(7, "Dokument", 80, TXA_MITTEHORIZONTAL | TXA_UNTEN, FT_DOCUMENT);
 taTabelle->Spalte(8, "Bool", 40, TXA_RECHTS | TXA_UNTEN, FT_BOOL);
 taTabelle->EingabeDatum_DatumZeitFormat("ddd' 'dd'. 'MMM' 'yyyy", "' 'HH':'mm", true);

 ezEditZeile = COEditZeileV("ezEditZeile_DLGDemo", IDE_EZEDITZEILE); /*!!! IDE_IDE_EZEDITZEILE >= IDE_TATABELLE + Spaltenanzahl + 18 !!!*/
 ezEditZeile->Hintergrundfarbe(100, 100, 100);
 ezEditZeile->Schriftfarbe(255, 255, 255);
 ezEditZeile->Zeichenvorgabe(ZV_ALLE | ZV_UBERLANGE);
 ezEditZeile->Schriftausrichtung(TXA_MITTEVERTICAL | TXA_LINKS);
 ezEditZeile->Hintergrundeffekt(HGE_BELEUCHTUNG_H);
 ezEditZeile->Hintergrundeffektfarbe(130, 130, 130);
 ezEditZeile->Hintergrundeffektrand(10, 10, 0, 0);
 ezEditZeile->Text("Hallo EditText");

 kDrucken = COKnopfV("kDrucken_DLGDemo", IDE_KDRUCKEN); kDrucken->Beschriftung("Drucken");

 leLeuchte = COLeuchteV("leLeuchte_DLGDemo", IDE_LELEUCHTE);
 leLeuchte->Hintergrundfarbe(80, 80, 80);
}
//-----------------------------------------------------------------------------------------------------------------------------------------
VMEMORY __vectorcall CODLGDemo::COFreiV(void) // wenn benötigt, in diesem Fall nicht
{


 return ((CODialog*)this)->COFreiV(); 
}
//-----------------------------------------------------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc_DLGDemo(HWND hWndDlg, unsigned int uiMessage, WPARAM wParam, LPARAM lParam)
{ 
 switch(uiMessage){
		case WM_CREATE      : dlgDemo->WM_Create(hWndDlg);
											    return NULL;
		//case WM_SIZE        : falsch, stattdessen pfnWM_Size() verwenden - Threadsicher 
		//case WM_MOVE        : falsch, stattdessen pfnWM_Move() verwenden - Threadsicher 
	  //case WM_COMMAND     : falsch, stattdessen pfnWM_Command() verwenden - Threadsicher 
	  //case WM_PAINT       : falsch, stattdessen pfnWM_Paint() verwenden - Threadsicher 
	 	case WM_NCDESTROY   : VMFreiV(dlgDemo); //richtig, stattdessen nicht WM_DESTROY in Verbindung mit VMFreiV(pDialog) verwenden
												  return NULL;
 }
 return CallWindowProc(dlgDemo->pfnWndProc_Dialog, hWndDlg, uiMessage, wParam, lParam); 
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void __vectorcall CODLGDemo::WM_Create(HWND hWndDlg)
{
 taTabelle->ErstellFenster(hWndDlg, 350, 720, 30, 70);
 ezEditZeile->ErstellFenster(hWndDlg, 20, 150, 30, 30);
 kDrucken->ErstellFenster(hWndDlg, 25, 75, 200, 30);
 leLeuchte->ErstellFenster(hWndDlg, 15, 15, 295, 35);
 SetFocus(taTabelle->HWND_Element());
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void __vectorcall CODLGDemo::Drucken(void)
{
 vDrucken = CODruckenV(hWndElement, "Demodruck", 297, 210);
 if(vDrucken){
	 vDrucken->pfnDrucken = fnDrucken;
	 taTabelle->DruckDaten(vDrucken->vsmDaten);
	 vDrucken->SetzSichtbar();
	 VMFreiV(vDrucken);
 }
}
//-----------------------------------------------------------------------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
 ACCEL acTasten6[6];
 acTasten6[0].fVirt = FVIRTKEY | FCONTROL;
 acTasten6[0].key = VK_DELETE;
 acTasten6[0].cmd = IDM_DS_LOSCHEN;

 acTasten6[1].fVirt = FVIRTKEY;
 acTasten6[1].key = VK_INSERT;
 acTasten6[1].cmd = IDM_DS_EINFUGEN;

 acTasten6[2].fVirt = FVIRTKEY;
 acTasten6[2].key = VK_F2;
 acTasten6[2].cmd = IDM_DS_ANDERN;

 acTasten6[3].fVirt = FVIRTKEY;
 acTasten6[3].key = VK_F3;
 acTasten6[3].cmd = IDM_DS_SENDEN;

 acTasten6[4].fVirt = FVIRTKEY;
 acTasten6[4].key = VK_F4;
 acTasten6[4].cmd = IDM_DF_ANSEHEN;

 acTasten6[5].fVirt = FVIRTKEY | FCONTROL;
 acTasten6[5].key = 0x4b;
 acTasten6[5].cmd = IDM_DATUM;

 EinfugenKurzTasten(acTasten6, 6);

 dlgDemo = VMBlock(VMDialog(), dlgDemo); dlgDemo->CODLGDemoV();
 dlgDemo->ErstellFenster(NULL, 520, 800, CW_USEDEFAULT, CW_USEDEFAULT);
 return dlgDemo->SetzSichtbar(true, NULL, NULL);
}
//-----------------------------------------------------------------------------------------------------------------------------------------