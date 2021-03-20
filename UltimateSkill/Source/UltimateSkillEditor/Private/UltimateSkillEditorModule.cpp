#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "IAssetTypeActions.h"
#include "AssetTools/UltimateSkillAssetActions.h"
#include "Modules/ModuleInterface.h"
#include "Templates/SharedPointer.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FUltimateSkillEditorModule"

class FUltimateSkillEditorModule
// : public IHasMenuExtensibility
// , public IHasToolBarExtensibility
 : public IModuleInterface
{
	virtual void StartupModule() override
	{
		RegisterAssetTools();
	}
	virtual void ShutdownModule() override
	{
		UnregisterAssetTools();
	}
	virtual bool SupportsDynamicReloading() override
	{
		return true;
	}
protected:

	/** Registers asset tool actions. */
	void RegisterAssetTools()
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		RegisterAssetTypeAction(AssetTools, MakeShareable(new FUltimateSkillAssetActions()));
	}

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
	{
		AssetTools.RegisterAssetTypeActions(Action);
		RegisteredAssetTypeActions.Add(Action);
	}

	void UnregisterAssetTools()
	{
		FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");
	
		if (AssetToolsModule != nullptr)
		{
			IAssetTools& AssetTools = AssetToolsModule->Get();
	
			for (auto Action : RegisteredAssetTypeActions)
			{
				AssetTools.UnregisterAssetTypeActions(Action);
			}
		}
	}
	
private:
	// /** The collection of registered asset type actions. */
	TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;
};

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUltimateSkillEditorModule, UltimateSkillEditor);
