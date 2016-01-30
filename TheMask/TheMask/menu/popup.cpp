#include "popup.h"
#include "utils/math/matrix_operations.h"

namespace Menu
{
  CPopup* CPopup::m_pInstance = nullptr;

  CPopup::CPopup() 
    : mFont(nullptr)
    , mTextureBG(nullptr)
  {
  }

  void CPopup::Init(Abathur::TAbathurFont *font)
  {
    mTextureBG = Abathur::loadTexture("data/textures/popup_bg.tga");
    ASSERT(mTextureBG);

    mFont = font;
    mOffsetText.Set(-0.14f, 0.5f);
    mLineEnter = 0.05f;
    MathUtils::MatrixOrthoOffCenterTpl(&mtx_ortho, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    SetRectangle(0.4f, 0.2f, 0.28f, 0.5f, 0xffffffff);
    mFontColor = 0xff000000;
  }
  
  void CPopup::SetRectangle(float x, float y, float width, float height, unsigned color)
  {
    mPopupSize.Set(x, y, width, height);
    mBGColor = color;
  }

  void CPopup::AddTextLine(const std::string &text)
  {
    vTexts.push_back(text);
  }

  void CPopup::Render()
  {
    if (vTexts.size() > 0) {
      Matrix44 mtx_identity;
      mtx_identity.SetIdentity();
      Abathur::setMatrix(Abathur::MATRIX_PROJECTION, &mtx_ortho);
      Abathur::setMatrix(Abathur::MATRIX_VIEW, &mtx_identity);
      Abathur::setMatrix(Abathur::MATRIX_WORLD, &mtx_identity);

      Abathur::DisableDepthState.apply();
      Abathur::AlphaBlendState.apply();
      Abathur::renderQuad2D(mPopupSize.x, mPopupSize.y, mPopupSize.z, mPopupSize.w, mBGColor, mTextureBG);
      ASSERT(mFont);
      float x = mPopupSize.x + mOffsetText.x;
      float y = mPopupSize.y + mOffsetText.y;
      int screen_w = Abathur::GetWidthApp();
      int screen_h = Abathur::GetHeightApp();
      for( auto &t: vTexts) 
      { 
        Abathur::renderText(mFont, x*screen_w, y*screen_h, mFontColor, t.c_str());
        y += mLineEnter;
      }
      vTexts.clear();
      Abathur::NoneBlendState.apply();
      Abathur::DefaultDepthState.apply();
    }
  }

}
