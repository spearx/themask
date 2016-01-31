#pragma once

namespace Abathur
{
	/////////////
	// FACTORY //
	/////////////

	class CEntityComponentFactory
	{
	private:
		typedef CFunctionCaller0<TComponent*> TFactoryCallback;
		struct SFactory
		{
			SFactory() {}
			SFactory(const TAbathurEntity::TComponentId _componentId, TFactoryCallback _callback) :componentId(_componentId), callback(_callback) {}

			TAbathurEntity::TComponentId componentId;
			TFactoryCallback             callback;
		};
		typedef std::unordered_map<std::string, SFactory> TFactories; //TODO ~ ramonv ~ convert strings to Ids

	public:
		static CEntityComponentFactory& Get() { return m_pInstance ? *m_pInstance : CreateInstance(); }

		template<typename TYPE > void Register(const char* szName);

		TAbathurEntity::TComponentId GetComponentId(const char* szName) const;
		TComponent* CreateComponentByName(const char* szName) const;

	private:
		static CEntityComponentFactory& CreateInstance() { m_pInstance = new CEntityComponentFactory(); return *m_pInstance; }

		CEntityComponentFactory() {}

		template<typename COMPONENT_TYPE> static inline TComponent* Create() { return new COMPONENT_TYPE(); }

	private:
		static CEntityComponentFactory* m_pInstance;
		TFactories m_factories;
	};

	// ------------------------------------------------------------------------------

	template<typename TYPE> void RegisterEntityComponent(const char* szName)
	{ 
		CEntityComponentFactory::Get().Register<TYPE>(szName); 
	}
	
	template<typename TYPE> inline TYPE* TAbathurEntity::AddComponent()
	{
		typedef SConversion<TYPE*, TComponent*> ConversionChecker;
		STATIC_ASSERT(ConversionChecker::Exists && !ConversionChecker::SameType);
		const TComponentId componentID = GetTypeCRC<TYPE>();
		TComponentContainer::iterator found = m_components.find(componentID);
		TYPE* pOutComponent = nullptr;
		if (found == m_components.end())
		{
			pOutComponent = new TYPE();
      pOutComponent->entity = this;
      m_components[componentID] = pOutComponent;
		}
		else
		{
			pOutComponent = static_cast<TYPE*>(found->second);
		}
		return pOutComponent;
	}

	template<typename TYPE> inline void TAbathurEntity::RemoveComponent()
	{
		typedef SConversion<TYPE*, TComponent*> ConversionChecker;
		STATIC_ASSERT(ConversionChecker::Exists && !ConversionChecker::SameType);
		const TComponentId componentID = GetTypeCRC<TYPE>();
		TComponentContainer::iterator found = m_components.find(componentID);
		if (found != m_components.end() && found->second)
		{
			delete found->second;
			m_components.erase(found);
		}
	}

	template<typename TYPE> inline TYPE* TAbathurEntity::QueryComponent()
	{
		return const_cast<TYPE*>(static_cast<const TAbathurEntity*>(this)->QueryComponent<TYPE>());
	}

	template<typename TYPE> inline const TYPE* TAbathurEntity::QueryComponent() const
	{
		typedef SConversion<TYPE*, TComponent*> ConversionChecker;
		STATIC_ASSERT(ConversionChecker::Exists && !ConversionChecker::SameType);
		const TComponentId componentID = GetTypeCRC<TYPE>();
		TComponentContainer::const_iterator found = m_components.find(componentID);
		if (found != m_components.end() && found->second)
		{
			return static_cast<const TYPE*>(found->second);
		}
		return nullptr;
	}

	template<typename TYPE > void CEntityComponentFactory::Register(const char* szName)
	{
		typedef SConversion<TYPE*, TComponent*> ConversionChecker;
		STATIC_ASSERT(ConversionChecker::Exists && !ConversionChecker::SameType);

		TFactories::iterator found = m_factories.find(szName);
		if (found == m_factories.end())
		{
			m_factories[szName] = SFactory(GetTypeCRC<TYPE>(), TFactoryCallback::SetFunction< &CEntityComponentFactory::Create<TYPE> >());
		}
		else
		{
			ASSERT(found->first == szName);
		}
	}
}
