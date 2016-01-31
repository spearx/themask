// Abathur SDK  
#ifndef INC_ABATHUR_RENDER_
#define INC_ABATHUR_RENDER_

#include <string>
#include "utils/math/Math.h"

namespace Abathur {

  //world view and projection
  enum EMatrixType {
    MATRIX_WORLD,
    MATRIX_VIEW,
    MATRIX_PROJECTION
  };

  // setMatrix render
  void setMatrix(EMatrixType type, Matrix44 *mtx);
  const Matrix44 &getMatrix(EMatrixType type);

  //Textures
  struct TAbathurTexture;
  TAbathurTexture *loadTexture(const char *filename);
  void unloadTexture(TAbathurTexture *texture);
  TAbathurTexture *getTexture(const char *name);
  void queryTexture(TAbathurTexture *texture, int *w, int *h, int *bits);

  //RenderTargets
  TAbathurTexture *createRenderTarget(int width, int height);
  void beginRenderTarget(TAbathurTexture *rt);
  void endRenderTarget();

  //Mesh
  struct TAbathurMesh;
  TAbathurMesh *loadMesh(const char *filename);
  void unloadMesh(TAbathurMesh *mesh);
  TAbathurMesh *getMesh(const char *name);
  unsigned int getMeshFrames(TAbathurMesh *mesh, int nSubMeshIdx);
  void setMeshFrame(TAbathurMesh *mesh, int nSubMeshIdx, int nFrame);

  //Material
  struct TAbathurMaterial;
  void loadMaterials(const char *filename);
  void unloadMaterial(TAbathurMaterial *material);
  void reloadMaterial(TAbathurMaterial *material);
  TAbathurMaterial *getMaterial(const char *name);
  template<typename T>
  void setMaterialParam(TAbathurMaterial *material, const char *name, T *value);
  template<typename T>
  void setMaterialParam(TAbathurMaterial *material, const char *name, T &value);
  
  //Font
  struct TAbathurFont;
  TAbathurFont *loadFont(const char *filename_def, const char *filename_tex);
  void unloadFont(TAbathurFont *font);

  //Render States
  struct TDepthState {
    bool enable_z_test;
    bool enable_z_write;
    bool enable_culling;
    
    TDepthState();
    void apply();
  };

  extern TDepthState DisableDepthState;
  extern TDepthState DisableZTestDepthState;
  extern TDepthState DisableZWriteDepthState;
  extern TDepthState DefaultDepthState;

  struct TBlendState {

    enum class EBlendType {
      BLEND_ZERO,
      BLEND_ONE,
      BLEND_SRC_COLOR,
      BLEND_INV_SRC_COLOR,
      BLEND_SRC_ALPHA,
      BLEND_INV_SRC_ALPHA,
      BLEND_DEST_COLOR,
      BLEND_INV_DEST_COLOR,
      BLEND_DEST_ALPHA,
      BLEND_INV_DEST_ALPHA,
      BLEND_SRC_ALPHA_SAT,
      BLEND_SRC1_COLOR,
      BLEND_INV_SRC1_COLOR,
      BLEND_SRC1_ALPHA,
      BLEND_INV_SRC1_ALPHA
    };
    
    bool        enable;
    //color
    EBlendType  src_blend;
    EBlendType  dst_blend;

    TBlendState();
    void apply();
  };

  extern TBlendState NoneBlendState;
  extern TBlendState AlphaBlendState;
  extern TBlendState AdditiveBlendState;

  //Draw primitives
  void clearBackground(unsigned color);
  //XY planes
  void renderTriangle2D(float x, float y, float w, float h);
  void renderQuad2D(float x, float y, float width, float height, unsigned color, TAbathurTexture *texture, float u0 = 0.0f, float v0 = 0.0f, float u1 = 1.0f, float v1 = 1.0f);
  void renderAxis(float size);
  void renderGrid(int ncells, int sub_divisions, float cell_size, unsigned color, unsigned subcolor);
  void drawBox(const Vector3 &half_size, unsigned color);
  void drawBoxWired(const Vector3 &half_size, unsigned color);
  void drawCapsuleWired(float radius, float length, unsigned color);
  void drawSphereWired(float radius, unsigned color);
  void drawLine(const Vector3 &p0, const Vector3 &p1, unsigned color);

  void renderMesh(TAbathurMesh *mesh, MathUtils::Vector3f &light_pos);
  void renderText(TAbathurFont *font, float x, float y, unsigned color, const char *msg, ...);
  void renderText(TBlendState *blend, TAbathurFont *font, float x, float y, unsigned color, const char *msg, ...);
};

#endif