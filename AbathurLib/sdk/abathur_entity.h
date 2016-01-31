#pragma once

#include "abathur_render.h"
#include "abathur_update.h"
#include "utils/Callbacks.h"
#include "utils/compileTime/compile_time_utils.h"
#include "utils/json/json.h"

#include <string>
#include <unordered_map>

namespace Abathur
{
	class TAbathurEntity;

	WRAP_TYPE(uint32, TEntityId, 0u);

	struct TComponent
	{
		TAbathurEntity *entity;

		virtual void Load(Json::Value &json_data);
		virtual void Destroy();

		virtual void Start();
		virtual void Stop();
	};

	struct TLocationComponent : public TComponent
	{
		Matrix44 mtx;

		TLocationComponent();
		void Load(Json::Value &json_data) override;
	};

	struct TAbathurMesh;

	struct TVisualComponent : public TComponent
	{
		TAbathurMesh *mesh;
		TAbathurMaterial *material;
		bool visible;

		TVisualComponent();
		void Load(Json::Value &json_data) override;
		void Destroy() override;
	};

  struct TPhysXData;
  struct TPhysXComponent : public TComponent
  {
  private:
    Abathur::CScopedUpdate mUpdateCall;
    Abathur::CScopedUpdate mUpdateLocCall;
    Abathur::CScopedUpdate mRenderCall;

    void UpdateLoc(const Abathur::SUpdateContext& context);
    void Update(const Abathur::SUpdateContext& context);
    void Render(const Abathur::SUpdateContext& context);

  public:
    enum class EShape {
      Box,
      Sphere,
      Capsule,
      BoundingBox,
      BoundingSphere,
      Mesh,
    };

    enum class EBodyType {
      RigitStatic,
      RigitDynamic,
      CharacterController,
      Unknown,
    };

    EShape mShape;
    EBodyType mBodyType;
    std::string mesh_name;
    float mDensity;
    float mContactOffset;
    float mSlopeLimit;
    float mStepOffset;
    float mMinDistance;
    bool  mRenderDebug;
    bool  mEnabled;

    //material info
    float mStaticFriction;
    float mDynamicFriction;
    float mRestitution;

    bool mHasTrigger;
    float mRadius; //sphere and capsule
    float mHeight; //capsule
    Vector3 mHalfSize; //box
    Vector3 mOffsetLoc;
    
    TPhysXData *p_mPhysXData;

    TPhysXComponent();
    ~TPhysXComponent();
    void Load(Json::Value &json_data) override;
    void Destroy() override;

    void Start() override;
    void Stop() override;
    void SetEnabled(bool e);

    void SetRenderDebug(bool enabled);

    void MoveActor(const Vector3 &displacement, float elapsed);
  };

	// ------------------------------------------------------------------------------
	class TAbathurEntity
	{
	public:
		enum { InvalidComponentId = 0u };
		typedef uint32 TComponentId;

	private:
		typedef std::unordered_map<TComponentId, TComponent*> TComponentContainer;

	public:
		TAbathurEntity();
		TAbathurEntity(const std::string &name, const TEntityId entityId);

		void Load(Json::Value &json_data);
		void Destroy();
		void Start();
		void Stop();

		inline const char* GetName() const { return m_name.c_str(); }
		inline TEntityId GetId() const { return m_entityId; }

		template<typename TYPE> TYPE* AddComponent();
		template<typename TYPE> void  RemoveComponent();
		template<typename TYPE> TYPE* QueryComponent();
		template<typename TYPE> const TYPE* QueryComponent() const;
	
	private:
		TComponent* AddComponentByName(const char* szName);

	private:
		TEntityId           m_entityId;
		std::string         m_name;
		TComponentContainer m_components;
	};

	// ------------------------------------------------------------------------------

	template<typename TYPE> void RegisterEntityComponent(const char* szName);
}

#include "abathur_entity.inl"
