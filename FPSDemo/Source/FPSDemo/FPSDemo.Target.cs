using UnrealBuildTool;
using System.Collections.Generic;

public class FPSDemoTarget : TargetRules
{
    public FPSDemoTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V6;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("FPSDemo");
    }
}
