// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectShooterBlank : ModuleRules
{
	public ProjectShooterBlank(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{
				"Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore", 
				"EnhancedInput"
			}
		);
		
		PrivateIncludePaths.AddRange(new string[] 
		{
			"ProjectShooterBlank/Public"
		});
	}
}
