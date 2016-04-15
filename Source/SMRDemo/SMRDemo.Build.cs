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
    public string ProjectRoot
    {
        get
        {
            return System.IO.Path.GetFullPath(System.IO.Path.Combine(ModuleDirectory, "../../"));
        }
    }
    public bool LoadSmr(TargetInfo Target)
    {
        bool isLibrarySupported = false;

        //Path to the SMR root directory
        string SmrRootDirectory = Path.GetFullPath(Path.Combine(ProjectRoot, "SMR/"));
		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32)) {            
			isLibrarySupported = true;
			//This hardcoded path obviously needs to be replaced with something that isn't so brittle
			//The likely solution will be to copy the entire SMR directory into the Unreal plugins directory
			//Then use a built in engine function to get the location of that directory
			string LibraryDirectory = Path.Combine (SmrRootDirectory, "win32Build/lib/Release/");
			Console.WriteLine (LibraryDirectory);
			Console.WriteLine (Path.Combine (LibraryDirectory, "math.lib"));

			//Link static library
			PublicAdditionalLibraries.Add (Path.Combine (LibraryDirectory, "math.lib"));             
			PublicAdditionalLibraries.Add (Path.Combine (LibraryDirectory, "newmat.lib"));           
			PublicAdditionalLibraries.Add (Path.Combine (LibraryDirectory, "common.lib"));           
			PublicAdditionalLibraries.Add (Path.Combine (LibraryDirectory, "core.lib"));                    
			PublicAdditionalLibraries.Add (Path.Combine (LibraryDirectory, "log4cplusS.lib"));
			PublicAdditionalLibraries.Add (Path.Combine (LibraryDirectory, "io.lib"));

            //Add any necessary include directories
            //Using all include directories from the CMake file for the UnrealAPI project
            //I don't know where the opengl, glfw and horde include directories are but this should be fine
            PublicIncludePaths.Add(Path.Combine(SmrRootDirectory, "Smr/thirdParty/Universal/log4cplus-1.2.0/include/"));
            PublicIncludePaths.Add (Path.Combine (SmrRootDirectory, "Smr/SRC/common/"));
			PublicIncludePaths.Add (Path.Combine (SmrRootDirectory, "Smr/SRC/SmrMath/"));
			PublicIncludePaths.Add (Path.Combine (SmrRootDirectory, "Smr/SRC/SmrCore/"));
			PublicIncludePaths.Add (Path.Combine (SmrRootDirectory, "Smr/SRC/SmrIO/"));
			PublicIncludePaths.Add (Path.Combine (SmrRootDirectory, "Smr/SRC/SmrUtils/"));
			PublicIncludePaths.Add (Path.Combine (SmrRootDirectory, "Smr/thirdParty/Universal/newmat/"));

		} 
		else if (Target.Platform == UnrealTargetPlatform.Mac) 
		{
			isLibrarySupported = true;
			string LibraryDirectory = Path.Combine (SmrRootDirectory, "macBuild/lib/Release/");

			//Link static libraries
			PublicAdditionalLibraries.Add (Path.Combine (LibraryDirectory, "libmath.a"));             
			PublicAdditionalLibraries.Add (Path.Combine (LibraryDirectory, "libnewmat.a"));           
			PublicAdditionalLibraries.Add (Path.Combine (LibraryDirectory, "libcommon.a"));           
			PublicAdditionalLibraries.Add (Path.Combine (LibraryDirectory, "libcore.a"));                    
			PublicAdditionalLibraries.Add (Path.Combine (LibraryDirectory, "liblog4cplusS.a"));
			PublicAdditionalLibraries.Add (Path.Combine (LibraryDirectory, "libio.a"));

			//Include header directories
			PublicIncludePaths.Add (Path.Combine (SmrRootDirectory, "Smr/SRC/common/"));
			PublicIncludePaths.Add (Path.Combine (SmrRootDirectory, "Smr/SRC/SmrMath/"));
			PublicIncludePaths.Add (Path.Combine (SmrRootDirectory, "Smr/SRC/SmrCore/"));
			PublicIncludePaths.Add (Path.Combine (SmrRootDirectory, "Smr/SRC/SmrIO/"));
			PublicIncludePaths.Add (Path.Combine (SmrRootDirectory, "Smr/SRC/SmrUtils/"));
			PublicIncludePaths.Add (Path.Combine (SmrRootDirectory, "Smr/thirdParty/Universal/log4cplus-1.2.0/include/"));
			PublicIncludePaths.Add (Path.Combine (SmrRootDirectory, "Smr/thirdParty/Universal/newmat/"));

			//These must be defined on OSX so that the config.hxx does not try to include defines.hxx
			Definitions.Add ("__MWERKS__");
			Definitions.Add ("__MACOS__");

		}
        if (isLibrarySupported)
            Definitions.Add("UNREAL_SMR_BINDING");
        return isLibrarySupported;
    }
}
