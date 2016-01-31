#pragma once

#define COLOR_ARGB(a,r,g,b) a << 24 | r << 16 | g << 8 | b
#define ALPHA_COMPONENT(color) ((color & 0xff000000) >> 24)
#define RED_COMPONENT(color) ((color & 0x00ff0000) >> 16)
#define GREEN_COMPONENT(color) ((color & 0x0000ff00) >> 8)
#define BLUE_COMPONENT(color) (color & 0x000000ff )

class ColorF 
{
public:
	ColorF(const MathUtils::Vector4f& input):data(input){}
	ColorF(const f32 r, const f32 g, const f32 b, const f32 a = 1.0f){ data(r,g,b,a); }
	ColorF(unsigned value) { data(RED_COMPONENT(value)/255.0f, GREEN_COMPONENT(value) / 255.0f, BLUE_COMPONENT(value) / 255.0f, ALPHA_COMPONENT(value) / 255.0f); }
	
	const MathUtils::Vector4f& GetVector4() const { return data; }
	const MathUtils::Vector3f GetVector3() const { return MathUtils::Vector3f(data.x,data.y,data.z); }
	
private:
	MathUtils::Vector4f data; 
};

#define Col_Black                   ColorF (0.0f, 0.0f, 0.0f)
#define Col_White                   ColorF (1.0f, 1.0f, 1.0f)
#define Col_Aquamarine              ColorF (0.439216f, 0.858824f, 0.576471f)
#define Col_Blue                    ColorF (0.0f, 0.0f, 1.0f)
#define Col_BlueViolet              ColorF (0.623529f, 0.372549f, 0.623529f)
#define Col_Brown                   ColorF (0.647059f, 0.164706f, 0.164706f)
#define Col_CadetBlue               ColorF (0.372549f, 0.623529f, 0.623529f)
#define Col_Coral                   ColorF (1.0f, 0.498039f, 0.0f)
#define Col_CornflowerBlue          ColorF (0.258824f, 0.258824f, 0.435294f)
#define Col_Cyan                    ColorF (0.0f, 1.0f, 1.0f)
#define Col_DarkGray                ColorF (0.5f, 0.5f, 0.5f)
#define Col_DarkGreen               ColorF (0.184314f, 0.309804f, 0.184314f)
#define Col_DarkOliveGreen          ColorF (0.309804f, 0.309804f, 0.184314f)
#define Col_DarkOrchild             ColorF (0.6f, 0.196078f, 0.8f)
#define Col_DarkSlateBlue           ColorF (0.419608f, 0.137255f, 0.556863f)
#define Col_DarkSlateGray           ColorF (0.184314f, 0.309804f, 0.309804f)
#define Col_DarkSlateGrey           ColorF (0.184314f, 0.309804f, 0.309804f)
#define Col_DarkTurquoise           ColorF (0.439216f, 0.576471f, 0.858824f)
#define Col_DarkWood                ColorF (0.05f, 0.01f, 0.005f)
#define Col_DimGray                 ColorF (0.329412f, 0.329412f, 0.329412f)
#define Col_DimGrey                 ColorF (0.329412f, 0.329412f, 0.329412f)
#define Col_FireBrick               ColorF (0.9f, 0.4f, 0.3f)
#define Col_ForestGreen             ColorF (0.137255f, 0.556863f, 0.137255f)
#define Col_Gold                    ColorF (0.8f, 0.498039f, 0.196078f)
#define Col_Goldenrod               ColorF (0.858824f, 0.858824f, 0.439216f)
#define Col_Gray                    ColorF (0.752941f, 0.752941f, 0.752941f)
#define Col_Green                   ColorF (0.0f, 1.0f, 0.0f)
#define Col_GreenYellow             ColorF (0.576471f, 0.858824f, 0.439216f)
#define Col_Grey                    ColorF (0.752941f, 0.752941f, 0.752941f)
#define Col_IndianRed               ColorF (0.309804f, 0.184314f, 0.184314f)
#define Col_Khaki                   ColorF (0.623529f, 0.623529f, 0.372549f)
#define Col_LightBlue               ColorF (0.74902f, 0.847059f, 0.847059f)
#define Col_LightGray               ColorF (0.658824f, 0.658824f, 0.658824f)
#define Col_LightGrey               ColorF (0.658824f, 0.658824f, 0.658824f)
#define Col_LightSteelBlue          ColorF (0.560784f, 0.560784f, 0.737255f)
#define Col_LightWood               ColorF (0.6f, 0.24f, 0.1f)
#define Col_LimeGreen               ColorF (0.196078f, 0.8f, 0.196078f)
#define Col_Magenta                 ColorF (1.0f, 0.0f, 1.0f)
#define Col_Maroon                  ColorF (0.556863f, 0.137255f, 0.419608f)
#define Col_MedianWood              ColorF (0.3f, 0.12f, 0.03f)
#define Col_MediumAquamarine        ColorF (0.196078f, 0.8f, 0.6f)
#define Col_MediumBlue              ColorF (0.196078f, 0.196078f, 0.8f)
#define Col_MediumForestGreen       ColorF (0.419608f, 0.556863f, 0.137255f)
#define Col_MediumGoldenrod         ColorF (0.917647f, 0.917647f, 0.678431f)
#define Col_MediumOrchid            ColorF (0.576471f, 0.439216f, 0.858824f)
#define Col_MediumSeaGreen          ColorF (0.258824f, 0.435294f, 0.258824f)
#define Col_MediumSlateBlue         ColorF (0.498039f, 0.0f, 1.0f)
#define Col_MediumSpringGreen       ColorF (0.498039f, 1.0f, 0.0f)
#define Col_MediumTurquoise         ColorF (0.439216f, 0.858824f, 0.858824f)
#define Col_MediumVioletRed         ColorF (0.858824f, 0.439216f, 0.576471f)
#define Col_MidnightBlue            ColorF (0.184314f, 0.184314f, 0.309804f)
#define Col_Navy                    ColorF (0.137255f, 0.137255f, 0.556863f)
#define Col_NavyBlue                ColorF (0.137255f, 0.137255f, 0.556863f)
#define Col_Orange                  ColorF (0.8f, 0.196078f, 0.196078f)
#define Col_OrangeRed               ColorF (0.0f, 0.0f, 0.498039f)
#define Col_Orchid                  ColorF (0.858824f, 0.439216f, 0.858824f)
#define Col_PaleGreen               ColorF (0.560784f, 0.737255f, 0.560784f)
#define Col_Pink                    ColorF (0.737255f, 0.560784f, 0.560784f)
#define Col_Plum                    ColorF (0.917647f, 0.678431f, 0.917647f)
#define Col_Red                     ColorF (1.0f, 0.0f, 0.0f)
#define Col_Salmon                  ColorF (0.435294f, 0.258824f, 0.258824f)
#define Col_SeaGreen                ColorF (0.137255f, 0.556863f, 0.419608f)
#define Col_Sienna                  ColorF (0.556863f, 0.419608f, 0.137255f)
#define Col_SkyBlue                 ColorF (0.196078f, 0.6f, 0.8f)
#define Col_SlateBlue               ColorF (0.0f, 0.498039f, 1.0f)
#define Col_SpringGreen             ColorF (0.0f, 1.0f, 0.498039f)
#define Col_SteelBlue               ColorF (0.137255f, 0.419608f, 0.556863f)
#define Col_Tan                     ColorF (0.858824f, 0.576471f, 0.439216f)
#define Col_Thistle                 ColorF (0.847059f, 0.74902f, 0.847059f)
#define Col_Transparent             ColorF (0.0f, 0.0f, 0.0f, 0.0f)
#define Col_Turquoise               ColorF (0.678431f, 0.917647f, 0.917647f)
#define Col_Violet                  ColorF (0.309804f, 0.184314f, 0.309804f)
#define Col_VioletRed               ColorF (0.8f, 0.196078f, 0.6f)
#define Col_Wheat                   ColorF (0.847059f, 0.847059f, 0.74902f)
#define Col_Yellow                  ColorF (1.0f, 1.0f, 0.0f)
#define Col_YellowGreen             ColorF (0.6f, 0.8f, 0.196078f)


