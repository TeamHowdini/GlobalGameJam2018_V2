// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class GlobalGameJam2018EditorTarget : TargetRules
{
	public GlobalGameJam2018EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "GlobalGameJam2018" } );
	}
}
