// Copyright Madmer

using UnrealBuildTool;

public class Aura : ModuleRules
{
	public Aura(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange([
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"GameplayAbilities",
		]);

		PrivateDependencyModuleNames.AddRange([
			"EnhancedInput",
			"GameplayTags",
			"GameplayTasks",
		]);
	}
}