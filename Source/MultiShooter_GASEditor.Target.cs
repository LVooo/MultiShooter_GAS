// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MultiShooter_GASEditorTarget : TargetRules
{
	public MultiShooter_GASEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("MultiShooter_GAS");
	}
}
