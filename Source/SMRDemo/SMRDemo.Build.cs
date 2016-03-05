// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
using System;

public class SMRDemo : ModuleRules
{
	public SMRDemo(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UnrealEd", "AnimGraph", "AnimGraphRuntime", "BlueprintGraph" });

        PrivateDependencyModuleNames.AddRange(new string[] {  });

        LoadSmr(Target);
    }
    public bool LoadSmr(TargetInfo Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;
            //This hardcoded path obviously needs to be replaced with something that isn't so brittle
            //The likely solution will be to copy the entire SMR directory into the Unreal plugins directory
            //Then use a built in engine function to get the location of that directory
            string SmrRootDirectory = "C:/Git/SMRFork/";
            string LibraryDirectory = Path.Combine(SmrRootDirectory, "win32Build/lib/Release/");
            Console.WriteLine(LibraryDirectory);
            Console.WriteLine(Path.Combine(LibraryDirectory, "math.lib"));

            //Link static library
            PublicAdditionalLibraries.Add(Path.Combine(LibraryDirectory, "math.lib"));             
            PublicAdditionalLibraries.Add(Path.Combine(LibraryDirectory, "newmat.lib"));           
            PublicAdditionalLibraries.Add(Path.Combine(LibraryDirectory, "common.lib"));           
            PublicAdditionalLibraries.Add(Path.Combine(LibraryDirectory, "core.lib"));                    
            PublicAdditionalLibraries.Add(Path.Combine(LibraryDirectory, "log4cplus.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibraryDirectory, "io.lib"));

            //Add any necessary include directories
            //Using all include directories from the CMake file for the UnrealAPI project
            //I don't know where the opengl, glfw and horde include directories are but this should be fine
            PublicIncludePaths.Add(Path.Combine(SmrRootDirectory, "Smr/SRC/common/"));
            PublicIncludePaths.Add(Path.Combine(SmrRootDirectory, "Smr/SRC/SmrMath/"));
            PublicIncludePaths.Add(Path.Combine(SmrRootDirectory, "Smr/SRC/SmrCore/"));
            PublicIncludePaths.Add(Path.Combine(SmrRootDirectory, "Smr/SRC/SmrIO/"));
            PublicIncludePaths.Add(Path.Combine(SmrRootDirectory, "Smr/SRC/SmrUtils/"));
            PublicIncludePaths.Add(Path.Combine(SmrRootDirectory, "Smr/thirdParty/Universal/log4cplus-1.1.1-rc3/include/"));
            PublicIncludePaths.Add(Path.Combine(SmrRootDirectory, "Smr/thirdParty/Universal/newmat/"));

        }
        if (isLibrarySupported)
            Definitions.Add("UNREAL_SMR_BINDING");
        return isLibrarySupported;
    }
}
