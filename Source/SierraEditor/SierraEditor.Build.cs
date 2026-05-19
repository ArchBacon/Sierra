// Copyright (c) 2026, Christian Delicaat. All rights reserved.

using UnrealBuildTool;

public class SierraEditor : ModuleRules
{
	public SierraEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Sierra",
			"UnrealEd",
			"AssetTools",
			"XmlParser",
			"DesktopPlatform",
			"Slate",
			"SlateCore",
			"ToolMenus",
		});
	}
}
