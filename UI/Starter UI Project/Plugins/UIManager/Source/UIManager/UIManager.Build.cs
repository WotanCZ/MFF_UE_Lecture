// Virtuos Labs Prague. All Rights Reserved.

using UnrealBuildTool;

public class UIManager : ModuleRules
{
	public UIManager(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"UMG",
			"CommonUI",
			"EnhancedInput",
			"CommonInput",
			"GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore",
		});

		PrivateIncludePaths.AddRange(new string[] 
		{
			// Base
			"UIManager/Public",
			"UIManager/Public/Core",
		});
	}
}
