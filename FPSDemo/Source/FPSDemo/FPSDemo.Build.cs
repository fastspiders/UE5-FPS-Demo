using UnrealBuildTool;

public class FPSDemo : ModuleRules
{
    public FPSDemo(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayTasks", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Projects" });

        // 启用C++20标准
        CppStandard = CppStandardVersion.Cpp20;
    }
}
