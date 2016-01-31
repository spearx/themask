#pragma once

#include "abathur.h"
#include "utils/compileTime/compile_time_utils.h"

namespace Menu
{
	class CPopup
	{
  public:

  private:
   static CPopup*     m_pInstance;
   static CPopup& CreateInstance() { m_pInstance = new CPopup(); return *m_pInstance; }

   Vector4 mPopupSize;
   unsigned mBGColor;
   unsigned mFontColor;
   Vector2  mOffsetText;
   float    mLineEnter;
   typedef std::vector<std::string> VStrings;
   VStrings vTexts;

   Matrix44 mtx_ortho;
   Abathur::TAbathurFont *mFont;
   Abathur::TAbathurTexture *mTextureBG;
   
   void SetRectangle(float x, float y, float width, float height, unsigned color);

	public:

    CPopup();

    void Init(Abathur::TAbathurFont *font);
    void AddTextLine(const std::string &text);
    void Render();
    void ApplyOrthoMatrix();

    static CPopup& Get() { return m_pInstance ? *m_pInstance : CreateInstance(); }
  };
}