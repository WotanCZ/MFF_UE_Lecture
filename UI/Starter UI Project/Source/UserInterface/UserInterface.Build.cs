using UnrealBuildTool;

public class UserInterface : ModuleRules
{
	public UserInterface(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"UMG",
			"ProjectShooterBlank",
			"EnhancedInput"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore",
		});

		PrivateIncludePaths.AddRange(new string[] 
		{
			// Gameplay
			"ProjectShooterBlank/Public",
			// Base
			"UserInterface/Public",
			"UserInterface/Public/Core",
			// Views
			"UserInterface/Public/Views",
		});
	}
}