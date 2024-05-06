// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
    public class PythonToolbox : ModuleRules
    {
#if WITH_FORWARDED_MODULE_RULES_CTOR
        public PythonToolbox(ReadOnlyTargetRules Target) : base(Target)
#else
        public PythonToolbox(TargetInfo Target)
#endif
        {

            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
            string enableUnityBuild = System.Environment.GetEnvironmentVariable("UEP_ENABLE_UNITY_BUILD");
            bFasterWithoutUnity = string.IsNullOrEmpty(enableUnityBuild);

            PrivateIncludePaths.AddRange(
                new string[] {
                    "PythonToolbox/Private",
                    "PythonEditor/Private",
                }
                );

            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "SlateCore",
                    "Slate",
                    "AssetTools",
                    "UnrealEd",
                    "EditorStyle",
                    "PropertyEditor",
                    "Kismet",  // for FWorkflowCentricApplication
					"InputCore",
                    "DirectoryWatcher",
                    "LevelEditor",
                    "Projects",
                    "UnrealEnginePython",
                    "PythonEditor",
                    "XmlParser"
                }
                );
        }
    }
}