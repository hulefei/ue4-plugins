using UnrealBuildTool;

public class UltimateSkillEditor : ModuleRules
{
	public UltimateSkillEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		DynamicallyLoadedModuleNames.AddRange(
			new string[] {
				"AssetTools",
				"MainFrame",
//				"WorkspaceMenuStructure",
			});
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"Private",
				"UltimateSkillEditor/Private"
			});
		
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"ContentBrowser",
				"Core",
				"CoreUObject",
				"DesktopWidgets",
				"EditorStyle",
				"Engine",
				"InputCore",
				"Projects",
				"Slate",
				"SlateCore",
				"UnrealEd",
				"UltimateSkill",
			});
		
		PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"AssetTools",
				"UnrealEd",
//				"WorkspaceMenuStructure",
			});
	}
}