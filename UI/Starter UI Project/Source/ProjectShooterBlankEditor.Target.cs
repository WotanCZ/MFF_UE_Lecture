// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectShooterBlankEditorTarget : TargetRules
{
	public ProjectShooterBlankEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		
		ExtraModuleNames.Add("ProjectShooterBlank");
		ExtraModuleNames.Add("UserInterface");
	}
}
