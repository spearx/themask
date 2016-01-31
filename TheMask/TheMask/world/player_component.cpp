#include "player_component.h"

#include "world/world.h"
#include "world/triggers.h"
#include "abathur_gui.h"
#include "utils/math/Angle3.h"
#include "menu/menu.h"
#include "menu/popup.h"

namespace World
{
	float gAmplitude = 0.236f; 
	float gFrequency = 0.315f;
	float gOffset = 0.47f;

	CPlayerComponent::CPlayerComponent()
		: m_inputDirection(MathUtils::ZERO)
		, m_alignment(Vector3(0.0f,0.0f,1.0f))
		, m_speed(5.0f)
    , m_yaw(0.0f)
    , m_playerChangeRoom(false)
	, m_totalTime(0.0f)
	, m_showItemDialog(false)
	{
    m_matrix_original.SetIdentity();
    m_viewMatrix.SetIdentity();
  }

	void CPlayerComponent::Load(Json::Value &json_data)
	{
		//TODO ~ ramonv ~ 

	}

	void CPlayerComponent::Destroy()
	{
		//TODO ~ ramonv ~ 
	}

	void CPlayerComponent::Start()
	{
		//TODO ~ ramonv ~ 
		m_state = EState::Active;
		m_update.SetPriority(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PrePhysics, Abathur::EUpdateStage::Default));
		m_update.SetCallback(Abathur::TUpdateCallback::SetMethod<CPlayerComponent, &CPlayerComponent::Update>(this));
		m_update.Register();

    m_update_post_physx.SetPriority(Abathur::GetUpdatePriority(Abathur::EUpdateTier::PostPhysics, Abathur::EUpdateStage::Default));
    m_update_post_physx.SetCallback(Abathur::TUpdateCallback::SetMethod<CPlayerComponent, &CPlayerComponent::UpdatePostPhysX>(this));
    m_update_post_physx.Register();

    if (Abathur::TLocationComponent* pLocComponent = entity->QueryComponent<Abathur::TLocationComponent>())
    {
      m_matrix_original = Matrix33(pLocComponent->mtx);
    }
	}

	void CPlayerComponent::Stop()
	{
		//TODO ~ ramonv ~ 
		m_state = EState::Inactive; 
		m_inputDirection = MathUtils::ZERO;
		m_update.Unregister();
	}

	bool CPlayerComponent::OnButton(const Abathur::Input::EButton button, const Abathur::Input::EButtonEvent buttonEvent)
	{
		if (m_state != EState::Inactive && button == Abathur::Input::EButton::GamepadA)
		{
			if (m_currentInteraction == "Unlock_Totem" && !Menu::CMenu::Get().IsButtonEnabled(Menu::CMenu::Totem))
			{
        Abathur::playAudio("data/audio/magic_spell1.wav", false);
        Menu::CMenu::Get().EnableButton(Menu::CMenu::Totem);
			}
			else if (m_currentInteraction == "Unlock_Laser_1" && !Menu::CMenu::Get().IsButtonEnabled(Menu::CMenu::Laser1))
			{
        Abathur::playAudio("data/audio/magic_spell1.wav", false);
				Menu::CMenu::Get().EnableButton(Menu::CMenu::Laser1);
			}
			else if (m_currentInteraction == "Unlock_Laser_2" && !Menu::CMenu::Get().IsButtonEnabled(Menu::CMenu::Laser2))
			{
        Abathur::playAudio("data/audio/magic_spell1.wav", false);
        Menu::CMenu::Get().EnableButton(Menu::CMenu::Laser2);
			}
			
			if (m_currentInteraction == "Interact_Item_1" || m_currentInteraction == "Interact_Item_2" || m_currentInteraction == "Interact_Item_3" 
			|| m_currentInteraction == "Interact_Item_4" || m_currentInteraction == "Interact_Item_5" || m_currentInteraction == "Interact_Item_6")
			{
				m_showItemDialog = buttonEvent == Abathur::Input::EButtonEvent::Press ? true : false;
			}
			
		}

    if (m_state != EState::Inactive && button == Abathur::Input::EButton::GamepadB)
    {
      if (buttonEvent == Abathur::Input::EButtonEvent::Press) {
        Abathur::TEntityId entityId = CWorld::Get().GetRoomEntityId();
        std::string room_name = "";
        if (entityId.IsValid())
        {
          room_name = Abathur::GetEntity(entityId)->GetName();
        }
        printf("Player is in Room: '%s'\n", room_name.c_str());
      }
    }
		return false; 
	}

	bool CPlayerComponent::OnDirection(const Abathur::Input::EDirection direction, const Vector2& value)
	{
		if (m_state != EState::Inactive && direction == Abathur::Input::EDirection::GamepadLeft)
		{
		  Abathur::CViewParameters& cameraParameters = CWorld::Get().GetPlayerCamera().GetViewParameters();

		  m_inputDirection = value;
		}
		return false; 
	}

	void CPlayerComponent::Update(const Abathur::SUpdateContext& context)
	{
		ImGui::SliderFloat("Amplitude", &gAmplitude, 0.0f, 10.0f);
		ImGui::SliderFloat("Frequency", &gFrequency, 0.0f, 10.0f);
		ImGui::SliderFloat("Offset",    &gOffset,    -10.0f, 10.0f);
		

		ShowDialogs();

    Abathur::CViewParameters& cameraParameters = CWorld::Get().GetPlayerCamera().GetViewParameters();
    cameraParameters.GetViewMatrix(m_viewMatrix);

    const Vector3 forward = m_viewMatrix.GetFront();
    const Vector3 left = m_viewMatrix.GetLeft();
    const float inputMagnitude = m_inputDirection.GetLength();
    Vector3 moveDir = left*m_inputDirection.x + forward*m_inputDirection.y;
    moveDir.y = 0.0f;
    moveDir.GetNormalizedSafe(MathUtils::ZERO);
    moveDir *= inputMagnitude;

	m_totalTime += context.frameTime;

    if (Abathur::TPhysXComponent* pPhysicsComponent = entity->QueryComponent<Abathur::TPhysXComponent>())
    {
      //m_inputDirection
      pPhysicsComponent->MoveActor(moveDir*m_speed*context.frameTime, context.frameTime);
    }

    //alignment

    if (moveDir.GetLengthSquared() > 0.0f)
    {
      m_yaw = atan2f(moveDir.z, -moveDir.x);
      if (Abathur::TLocationComponent* pLocComponent = entity->QueryComponent<Abathur::TLocationComponent>())
      {
        Matrix33 mtx;
        mtx.SetIdentity();
        Vector3 t = pLocComponent->mtx.GetTranslation();
        mtx.SetRotationY(m_yaw);
        pLocComponent->mtx = mtx * m_matrix_original;
        pLocComponent->mtx.SetTranslation(t);
      }
    }
	}


	void CPlayerComponent::CreateChildEntities(const Abathur::TSceneId sceneId)
	{
		Abathur::TAbathurEntity* pChildEntity = Abathur::SpawnEnitity("DummyPlayer", sceneId);
		ASSERT(pChildEntity);

		{
			Abathur::TLocationComponent* pComponent = pChildEntity->AddComponent<Abathur::TLocationComponent>();
			pComponent->mtx.SetIdentity();
			pComponent->mtx = entity->QueryComponent<Abathur::TLocationComponent>()->mtx;
		}

		{
			Abathur::TVisualComponent* pComponent = pChildEntity->AddComponent<Abathur::TVisualComponent>();
			Abathur::loadTexture("data/textures/Mask_Diffuse.tga");
			Abathur::loadMaterials("data/scenes/mask.mat");
			pComponent->mesh     = Abathur::loadMesh("data/meshes/Mask.mesh");
			pComponent->material = Abathur::getMaterial("Material_Mask");
			ASSERT(pComponent->material);
		}
		
		m_childId = pChildEntity->GetId();

	}

  void CPlayerComponent::UpdatePostPhysX(const Abathur::SUpdateContext& context)
  {    
    if (IsMoving())
    {
       if (Abathur::TLocationComponent* pLocComponent = entity->QueryComponent<Abathur::TLocationComponent>())
       {
         Vector3 pos = pLocComponent->mtx.GetTranslation();
         //printf("Set Player pos %1.3f,%1.3f,%1.3f\n", pos.x, pos.y, pos.z);
         CTriggers::Get().SetPlayerPosition(pos);
       }
     }

	if (Abathur::TLocationComponent* pLocComponent = entity->QueryComponent<Abathur::TLocationComponent>())
	{
		if (Abathur::TLocationComponent* pChildLocComponent = Abathur::GetEntity(m_childId)->QueryComponent<Abathur::TLocationComponent>())
		{
			pChildLocComponent->mtx = pLocComponent->mtx;
			pChildLocComponent->mtx.SetTranslation(pChildLocComponent->mtx.GetTranslation() + Vector3(0.0f, sinf(m_totalTime*gFrequency*gfPI2)*gAmplitude + gOffset, 0.0f));
		}
	}
  }

  bool CPlayerComponent::IsInteractionTrigger(const std::string& event_name) const
  {
	  return event_name == "Interact_Item_1" || event_name == "Interact_Item_2" || event_name == "Interact_Item_3"
		  || event_name == "Interact_Item_4" || event_name == "Interact_Item_5" || event_name == "Interact_Item_6"
		  || event_name == "Unlock_Totem" || event_name == "Unlock_Laser_1" || event_name == "Unlock_Laser_2" || event_name == "Interact_Cauldron";
  }

  void CPlayerComponent::OnTriggerEvent(const std::string &event_name, CTriggers::ETriggerEvent event_type)
  {
    if (!IsInteractionTrigger(event_name))
      return;

	  if (event_type == CTriggers::ETriggerEvent::ON_ENTER )
	  {
		  //printf("On Trigger Event %s ON ENTER\n", event_name.c_str());

		  if (event_name == "Interact_Cauldron")
		  {
			printf("Enable Offline\n");
			Menu::CMenu::Get().GetOfflineGame().Enable();
		  }
		  m_currentInteraction = event_name;
	  }
	  else if (event_type == CTriggers::ETriggerEvent::ON_EXIT)
	  {
		  //printf("On Trigger Event %s ON EXIT\n", event_name.c_str());

		  if (event_name == "Interact_Cauldron")
		  {
			  printf("Disable Offline\n");
			  Menu::CMenu::Get().GetOfflineGame().Disable();
		  }
		  m_currentInteraction = "";
		  m_showItemDialog = false;
	  }
  }

  void CPlayerComponent::ShowDialogs()
  {
	  if (m_showItemDialog)
	  {
		  if (m_currentInteraction == "Interact_Item_1")
		  {
			  Menu::CPopup::Get().AddTextLine("This is Sandro's spiritual");
			  Menu::CPopup::Get().AddTextLine("hideout.");
		  }
		  else if (m_currentInteraction == "Interact_Item_2")
		  { 
			  Menu::CPopup::Get().AddTextLine("Sandro has always been a");
			  Menu::CPopup::Get().AddTextLine("kind person, and never used");
			  Menu::CPopup::Get().AddTextLine("slaves as work assets.");
		  }
		  else if (m_currentInteraction == "Interact_Item_3")
		  {
			  Menu::CPopup::Get().AddTextLine("Sandro always put more");
			  Menu::CPopup::Get().AddTextLine("more snake poison to his");
			  Menu::CPopup::Get().AddTextLine("food after crafting potions.");
		  }
		  else if (m_currentInteraction == "Interact_Item_4")
		  {
			  Menu::CPopup::Get().AddTextLine("All the traped souls");
			  Menu::CPopup::Get().AddTextLine("here, are a sign of");
			  Menu::CPopup::Get().AddTextLine("really bad JuJu.");
		  }
		  else if (m_currentInteraction == "Interact_Item_5")
		  {
			  Menu::CPopup::Get().AddTextLine("Mambo usally eats");
			  Menu::CPopup::Get().AddTextLine("Voodoo Flamme");
			  Menu::CPopup::Get().AddTextLine("after creating dolls.");
		  }
		  else if (m_currentInteraction == "Interact_Item_6")
		  {
			  Menu::CPopup::Get().AddTextLine("The spirits around");
			  Menu::CPopup::Get().AddTextLine("this hideout are");
			  Menu::CPopup::Get().AddTextLine("Rada.");
		  }
	  }
  }

  bool CPlayerComponent::IsMoving() const {
    float len = m_inputDirection.GetLengthSquared();
    return (len > 0.01f);
  }


}