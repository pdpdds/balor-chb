#pragma once


namespace balor {
	namespace graphics {



/**
 * 色を表す。
 */
class Color {
public:
	typedef unsigned long COLORREF;

public:
	/// 初期化せずに作成。
	Color() {}
	/// rgba から作成。
	Color(int r, int g, int b, int a = 255);

public:
	/// COLORREF型からの変換。
	static Color fromCOLORREF(COLORREF colorref);
	/// COLORREF型への変換。
	COLORREF toCOLORREF() const;

public:
	bool operator==(const Color& rhs) const;
	bool operator!=(const Color& rhs) const;

public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

public: // システムカラー一覧
	static Color activeBorder();
	static Color activeCaption();
	static Color activeCaptionText();
	static Color appWorkspace();
	static Color control();
	static Color controlShadow();
	static Color controlDarkShadow();
	static Color controlLight();
	static Color controlHighlight();
	static Color controlText();
	static Color desktop();
	static Color gradientActiveCaption();
	static Color gradientInactiveCaption();
	static Color grayText();
	static Color hotTrack();
	static Color inactiveBorder();
	static Color inactiveCaption();
	static Color inactiveCaptionText();
	static Color menu();
	static Color menuBar();
	static Color menuHighlight();
	static Color menuText();
	static Color scrollbar();
	static Color selectedControl();
	static Color selectedControlText();
	static Color toolTip();
	static Color toolTipText();
	static Color window();
	static Color windowFrame();
	static Color windowText();

public: // web 色名一覧
	static Color aliceBlue();
	static Color antiqueWhite();
	static Color aqua();
	static Color aquamarine();
	static Color azure();
	static Color beige();
	static Color bisque();
	static Color black();
	static Color blanchedAlmond();
	static Color blue();
	static Color blueViolet();
	static Color brown();
	static Color burlyWood();
	static Color cadetBlue();
	static Color chartreuse();
	static Color chocolate();
	static Color coral();
	static Color cornflowerBlue();
	static Color cornsilk();
	static Color crimson();
	static Color cyan();
	static Color darkBlue();
	static Color darkCyan();
	static Color darkGoldenrod();
	static Color darkGray();
	static Color darkGreen();
	static Color darkKhaki();
	static Color darkMagenta();
	static Color darkOliveGreen();
	static Color darkOrange();
	static Color darkOrchid();
	static Color darkRed();
	static Color darkSalmon();
	static Color darkSeaGreen();
	static Color darkSlateBlue();
	static Color darkSlateGray();
	static Color darkTurquoise();
	static Color darkViolet();
	static Color deepPink();
	static Color deepSkyBlue();
	static Color dimGray();
	static Color dodgerBlue();
	static Color fireBrick();
	static Color floralWhite();
	static Color forestGreen();
	static Color fuchsia();
	static Color gainsboro();
	static Color ghostWhite();
	static Color gold();
	static Color goldenrod();
	static Color gray();
	static Color green();
	static Color greenYellow();
	static Color honeydew();
	static Color hotPink();
	static Color indianRed();
	static Color indigo();
	static Color ivory();
	static Color khaki();
	static Color lavender();
	static Color lavenderBlush();
	static Color lawnGreen();
	static Color lemonChiffon();
	static Color lightBlue();
	static Color lightCoral();
	static Color lightCyan();
	static Color lightGoldenrodYellow();
	static Color lightGreen();
	static Color lightGray();
	static Color lightPink();
	static Color lightSalmon();
	static Color lightSeaGreen();
	static Color lightSkyBlue();
	static Color lightSlateGray();
	static Color lightSteelBlue();
	static Color lightYellow();
	static Color lime();
	static Color limeGreen();
	static Color linen();
	static Color magenta();
	static Color maroon();
	static Color mediumAquamarine();
	static Color mediumBlue();
	static Color mediumOrchid();
	static Color mediumPurple();
	static Color mediumSeaGreen();
	static Color mediumSlateBlue();
	static Color mediumSpringGreen();
	static Color mediumTurquoise();
	static Color mediumVioletRed();
	static Color midnightBlue();
	static Color mintCream();
	static Color mistyRose();
	static Color moccasin();
	static Color navajoWhite();
	static Color navy();
	static Color oldLace();
	static Color olive();
	static Color oliveDrab();
	static Color orange();
	static Color orangeRed();
	static Color orchid();
	static Color paleGoldenrod();
	static Color paleGreen();
	static Color paleTurquoise();
	static Color paleVioletRed();
	static Color papayaWhip();
	static Color peachPuff();
	static Color peru();
	static Color pink();
	static Color plum();
	static Color powderBlue();
	static Color purple();
	static Color red();
	static Color rosyBrown();
	static Color royalBlue();
	static Color saddleBrown();
	static Color salmon();
	static Color sandyBrown();
	static Color seaGreen();
	static Color seashell();
	static Color sienna();
	static Color silver();
	static Color skyBlue();
	static Color slateBlue();
	static Color slateGray();
	static Color snow();
	static Color springGreen();
	static Color steelBlue();
	static Color tan();
	static Color teal();
	static Color thistle();
	static Color tomato();
	static Color turquoise();
	static Color violet();
	static Color wheat();
	static Color white();
	static Color whiteSmoke();
	static Color yellow();
	static Color yellowGreen();
};



	}
}