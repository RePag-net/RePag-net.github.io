// ab Dateiversion 1.2.2.101
#ifndef GULH
#define GULH
//---------------------------------------------------------------------------
#define GP_GEZEICHNET 0
#define GP_GEPUFFERT 1
#define GPUNKTE char*
const short sHalbKreis = 180;
//---------------------------------------------------------------------------
typedef struct STWPunkt2D{
  float fx;
  float fy;
} STWPunkt2D;
//---------------------------------------------------------------------------
typedef struct STWPunkt3D{
  float fx;
  float fy;
  float fz;
} STWPunkt3D;
//---------------------------------------------------------------------------
typedef struct STWeltBildKoordinaten{
  float fx_max;
  float fy_max;
  float fu_max;
  float fv_max;
  float fx_min;
  float fy_min;
  float fu_min;
  float fv_min;
  float fxu_Faktor;
  float fyv_Faktor;
} STWeltBildKoordinaten;
//---------------------------------------------------------------------------
typedef struct STPerspektivKoordinaten{
  float fvrp_x;
  float fvrp_y;
  float fvrp_z;
  float fvpn_x;
  float fvpn_y;
  float fvpn_z;
  float fprp_x;
  float fprp_y;
  float fprp_z;
  float fvup_x;
  float fvup_y;
  float fd;
  float fB;
  float fF;
  float fz_max;
  float fPersPar;
  float fPers_x;
  float fPers_y;
  float fPers_z;
} STPerspektivKoordinaten;
//---------------------------------------------------------------------------
typedef struct STBPunkte{
  int ix_1;
  int ix_2;
  int ix_3;
  int ix_4;
  int iy_1;
  int iy_2;
  int iy_3;
  int iy_4;
} STBPunkte;
//---------------------------------------------------------------------------
#ifndef HGUL
class __declspec(dllimport) COPunkt2D
{
private:
  GPUNKTE vgpPunkte_X;
  GPUNKTE vgpPunkte_Y;
  VMEMORY vmSpeicher;
  CRITICAL_SECTION* vcsZeichnen;

public:
  void __vectorcall COPunkt2DV(ULONG ulAnzahl);
  void __vectorcall COPunkt2DV(VMEMORY vmSpeicherA, ULONG ulAnzahl);
  VMEMORY __vectorcall COFreiV(void);
  void __vectorcall SetzPunkt(ULONG ulIndex, float fx, float fy);
  void __vectorcall SetzPunkt(ULONG& ulIndex, float& fx, float& fy);
  void __vectorcall SetzPunkt(ULONG ulIndex, STWPunkt2D& wp2Punkt);
  void __vectorcall Translation(STWPunkt2D& wp2_t);
  void __vectorcall Skalierung(STWPunkt2D& wp2_s);
  void __vectorcall Scherung_X_Achse(STWPunkt2D& wp2_Sch);
  void __vectorcall Scherung_Y_Achse(STWPunkt2D& wp2_Sch);
  void __vectorcall Spiegelung_X_Achse(void);
  void __vectorcall Spiegelung_Y_Achse(void);
  void __vectorcall Rotation(short sGrad);
  STBPunkte* __vectorcall bp_XY(ULONG ulIndex, STBPunkte& bpPunkte);
	STWPunkt2D* __vectorcall wp_XY(ULONG ulIndex, STWPunkt2D& wp2Punkt);
  void __vectorcall WeltBildKoordinaten(STWeltBildKoordinaten* pstWBK);
};
__declspec(dllimport) COPunkt2D* __vectorcall COPunkt2DV(ULONG ulAnzahl);
__declspec(dllimport) COPunkt2D* __vectorcall COPunkt2DV(VMEMORY vmSpeicher, ULONG ulAnzahl);
//---------------------------------------------------------------------------
class __declspec(dllimport) COPunkt3D
{
private:

protected:
	GPUNKTE vgpPunkte_X;
	GPUNKTE vgpPunkte_Y;
	GPUNKTE vgpPunkte_Z;
	VMEMORY vmSpeicher;
	CRITICAL_SECTION* vcsZeichnen;

public:
	void __vectorcall COPunkt3DV(ULONG ulAnzahl);
  void __vectorcall COPunkt3DV(VMEMORY vmSpeicherA, ULONG ulAnzahl);
	VMEMORY __vectorcall COFreiV(void);
	void __vectorcall SetzPunkt(ULONG ulIndex, float fx, float fy, float fz);
	void __vectorcall SetzPunkt(ULONG& ulIndex, float& fx, float& fy, float& fz);
	void __vectorcall SetzPunkt(ULONG ulIndex, STWPunkt3D& wp3Punkt);
  void __vectorcall Translation(STWPunkt3D& wp3_t);
 	void __vectorcall Skalierung(STWPunkt3D& wp3_s);
	void __vectorcall Scherung(STWPunkt3D& wp3_Sch_A, STWPunkt3D& wp3_Sch_B);
  void __vectorcall Rotation_X_Achse(short sGrad);
  void __vectorcall Rotation_Y_Achse(short sGrad);
  void __vectorcall Rotation_Z_Achse(short sGrad);
	STBPunkte* __vectorcall bp_XY(ULONG ulIndex, STBPunkte& bpPunkte);
	STWPunkt3D* __vectorcall wp_XYZ(ULONG ulIndex, STWPunkt3D& wp3Punkt);
	void __vectorcall WeltBildKoordinaten(STWeltBildKoordinaten* pstWBK);
	void __vectorcall PerspektivKoordinaten(STPerspektivKoordinaten* pstPersK);

};
__declspec(dllimport) COPunkt3D* __vectorcall COPunkt3DV(ULONG ulAnzahl);
__declspec(dllimport) COPunkt3D* __vectorcall COPunkt3DV(VMEMORY vmSpeicher, ULONG ulAnzahl);
//---------------------------------------------------------------------------
class __declspec(dllimport) COTextur
{
private:
	VMEMORY vmSpeicher;
	BITMAPINFOHEADER bmih;
	BYTE* pBits;
	HBITMAP hBitmap;
	inline void __vectorcall ErstellTextur(long lHohe, long lBreite);

protected:

public:
	void __vectorcall COTexturV(long lHohe, long lBreite);
  void __vectorcall COTexturV(VMEMORY vmSpeicherA, long lHohe, long lBreite);
	VMEMORY __vectorcall COFreiV(void);
	void __vectorcall SetzPixel(int ix, int iy, COLORREF crColor);
	inline COLORREF __vectorcall Pixel(int ix, int iy);
	long __vectorcall Hohe(void);
	long __vectorcall Breite(void);
	void (__vectorcall *pfnZeichnen_Text)(COTextur*, HDC);
	void __vectorcall Zeichnen_Text(HDC hdc);
	LOGFONT lfSchrift;

};
__declspec(dllimport) COTextur* __vectorcall COTexturV(long lHohe, long lBreite);
__declspec(dllimport) COTextur* __vectorcall COTexturV(VMEMORY vmSpeicher, long lHohe, long lBreite);
//---------------------------------------------------------------------------
class __declspec(dllimport) COKorper : public COPunkt3D
{
private:
	ULONG ulFlachen;
  typedef struct STFlache{
    ULONG ulPunkt_1;
    ULONG ulPunkt_2;
    ULONG ulPunkt_3;
		COTextur* vTextur;
  } STFlache;
	STFlache* vFlachen;
	int (*vBildpunkte)[2];
	inline void __vectorcall SetzPixel(BITMAPINFOHEADER& bmih, BYTE*& pBits, int ix, int iy, COLORREF crColor);
	void __vectorcall BildpunkteBerechnen(void);

protected:

public:
	void __vectorcall COKorperV(ULONG ulPunkte, ULONG ulFlachenA);
  void __vectorcall COKorperV(VMEMORY vmSpeicherA, ULONG ulPunkte, ULONG ulFlachen);
	VMEMORY __vectorcall COFreiV(void);
	void __vectorcall SetzFlache(ULONG ulIndex, ULONG ulPunkt_1, ULONG ulPunkt_2, ULONG ulPunkt_3, COTextur* vTextur);
	void __vectorcall SetzFlache(ULONG& ulIndex, ULONG& ulPunkt_1, ULONG& ulPunkt_2, ULONG& ulPunkt_3, COTextur* vTextur);
	void __vectorcall Zeichnen_Drahtmodel(HDC hdc);
	//void __vectorcall Zeichnen_Bild(PAINTSTRUCT& lpPaint);

};
//---------------------------------------------------------------------------
class __declspec(dllimport) COQuader : public COKorper
{
private:
	void __vectorcall Zeichnen_Gitter(HDC hdc, STBPunkte& bpQuaderVorn, STBPunkte& bpQuaderHinten);
	void __vectorcall Zeichnen_Textur(HDC hdc, STBPunkte& bpQuaderVorn, STBPunkte& bpQuaderHinten);

public:
	void __vectorcall COQuaderV(void);
  void __vectorcall COQuaderV(VMEMORY vmSpeicherA);
	void __vectorcall SetzPunkte(float fA_x, float fA_y, float fA_z, float fB_x, float fB_y, float fB_z, float fC_x, float fC_y, float fC_z,
														float fD_x, float fD_y, float fD_z, float fE_x, float fE_y, float fE_z, float fF_x, float fF_y, float fF_z, 
														float fG_x, float fG_y, float fG_z, float fH_x, float fH_y, float fH_z);
	void __vectorcall SetzPunkte(STWPunkt3D& wp3_A, STWPunkt3D& wp3_B, STWPunkt3D& wp3_C, STWPunkt3D& wp3_D,
														STWPunkt3D& wp3_E, STWPunkt3D& wp3_F, STWPunkt3D& wp3_G, STWPunkt3D& wp3_H);
	void __vectorcall Zeichnen(HDC hdc, BYTE ucArt);

};
__declspec(dllimport) COQuader* __vectorcall COQuaderV(void);
__declspec(dllimport) COQuader* __vectorcall COQuaderV(VMEMORY vmSpeicher);
//---------------------------------------------------------------------------
class __declspec(dllimport) COViereck
{
private:
  VMEMORY vmSpeicher;
  COPunkt2D* vgp2Viereck;

public:
  void __vectorcall COViereckV(void);
  void __vectorcall COViereckV(VMEMORY vmSpeicherA);
  VMEMORY __vectorcall COFreiV(void);
  void __vectorcall SetzPunkte(float fA_x, float fA_y, float fB_x, float fB_y, float fC_x, float fC_y, float fD_x, float fD_y);
  void __vectorcall SetzPunkte(STWPunkt2D& wp2_A, STWPunkt2D& wp2_B, STWPunkt2D& wp2_C, STWPunkt2D& wp2_D);
  void __vectorcall WeltBildKoordinaten(STWeltBildKoordinaten& stWBK);
  void __vectorcall Translation(STWPunkt2D& wp2_t);
  void __vectorcall Skalierung(STWPunkt2D& wp2_s);
  void __vectorcall Scherung_X_Achse(STWPunkt2D& wp2_Sch);
  void __vectorcall Scherung_Y_Achse(STWPunkt2D& wp2_Sch);
  void __vectorcall Spiegelung_X_Achse(void);
  void __vectorcall Spiegelung_Y_Achse(void);
  void __vectorcall Rotation(short sGrad);
  void __vectorcall Zeichnen(HDC hdc);
};
__declspec(dllimport) COViereck* __vectorcall COViereckV(void);
__declspec(dllimport) COViereck* __vectorcall COViereckV(VMEMORY vmSpeicher);
//---------------------------------------------------------------------------
__declspec(dllimport) void __vectorcall WeltBildKoordinaten(STWeltBildKoordinaten& stWBK);
__declspec(dllimport) void __vectorcall PerspektivKoordinaten(STPerspektivKoordinaten& stPersK);
__declspec(dllimport) void __vectorcall Linie(HDC hdc, int ix_1, int iy_1, int ix_2, int iy_2, COLORREF color);
__declspec(dllimport) void __vectorcall Rechteck_Fullen(HDC hdc, int ix_1, int iy_1, int ix_2, int iy_2, COLORREF color);
__declspec(dllimport) void __vectorcall SetzPixelDIB(BITMAPINFOHEADER& bmih, BYTE*& pBits, long ly, long lx, COLORREF color);
__declspec(dllimport) int __vectorcall MMzuPixel(HWND hWnd, int iIndex, int iMillimeter);
//---------------------------------------------------------------------------
#endif
#endif