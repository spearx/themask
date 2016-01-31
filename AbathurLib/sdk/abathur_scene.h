// Abathur SDK  
#pragma once 

#include "abathur_entity.h"
#include "utils/compileTime/compile_time_utils.h"
#include <string>

namespace Abathur 
{
	typedef bool(*renderCallback)(float);
	class  TAbathurEntity;
	struct TAbathurTexture;

	WRAP_TYPE(uint8, TSceneId, 0u);
	
	TSceneId CreateScene();
	TSceneId LoadScene(const char *filename);
	void AppendScene(const TSceneId sceneId, const char *filename);
	void UnloadScene(const TSceneId sceneId);

	void StartScene(const TSceneId sceneId);
	void StopScene(const TSceneId sceneId);

	TAbathurEntity* SpawnEnitity(const char* szName, const TSceneId sceneId); 
	TAbathurEntity* GetEntity(const TEntityId entityId);
	TAbathurEntity* GetEntityByName(const char* szName, const TSceneId sceneId); //TODO ~ ramonv ~ Check unique name inside the scene
	TEntityId       GetEntityIdByName(const char* szName, const TSceneId sceneId);
	void RemoveEntity(const TEntityId entityId);

	///////////
	// Views //
	///////////

	class CViewParameters;
		
	WRAP_TYPE(uint8, TViewId,       0u);
	WRAP_TYPE(uint8, TViewPriority, 255u);

	typedef CFunctionCaller2<const TViewId, const CViewParameters&> TViewCallback;

	TViewId AddSceneView(const TSceneId sceneId);
	void RemoveSceneView(const TViewId sceneId);
	void SetViewParameters(const TViewId, const CViewParameters& parameters);

	class CViewParameters
	{
	private:
		enum class EMode
		{
			Perspective,
			Orthogonal,
		};

	public:
		CViewParameters();

		void SetPriority(const TViewPriority priority);
		TViewPriority GetPriority() const;

		void SetRenderTarget(TAbathurTexture* renderTarget);
		TAbathurTexture* GetRenderTarget();

		Vector3 Unproject(const Vector2& normalizedInput); 

		void SetBeforeCallback(TViewCallback callback);
		void SetAfterCallback(TViewCallback callback);
		TViewCallback GetBeforeCallback();
		TViewCallback GetAfterCallback();

		void SetTransform(const QuatT& transform);
		void SetLookAt(const Vector3& position, const Vector3& target, const float roll = 0.0f);

		const QuatT& GetTransform() const;
		float GetAspectRatio() const;

		void SetFov(const float input);
		void SetZNear(const float input);
		void SetZFar(const float input);
		void SetProjection(const float fov, const float zNear, const float zFar);

		void SetOrthogonal(const Vector2& x, const Vector2& y, const Vector2& z);

		void GetViewMatrix(Matrix34& output);
		void GetViewMatrix(Matrix44& output);
		void GetProjectionMatrix(Matrix44& output);

	private:
		QuatT            m_transform;
		Vector2          m_projectionData[3];
		EMode            m_mode;
		TViewPriority    m_priority;
		TAbathurTexture* m_pRenderTarget;
		TViewCallback    m_beforeCallback;
		TViewCallback    m_afterCallback;
	};
};

/*
//samples...
void init() {

  SceneDesc;


  loadScene("level");
  loadScene("monitors_ui");

  //first
  addSceneCamera("level", "camera01", &rt0);
  addSceneCamera("level", "camera02", &rt1);
  //monitors
  addSceneCamera("monitors_ui", "camera_ui"); //render to screen (backbuffer)

  e = getEntityName("monitor_up");
  e->setTexture(&rt0); //material
  e = getEntityName("monitor_down");
  e->setTexture(&rt1); //material

}

void udpate() {

}
*/
