// Fill out your copyright notice in the Description page of Project Settings.

#include "PythonToolbox.h"

#include "FileManagerGeneric.h"
#include "TabTool.h"
#include "PythonEditor/Private/PythonProjectItem.h"

IMPLEMENT_GAME_MODULE(FPythonToolbox, PythonToolbox)

#define LOCTEXT_NAMESPACE "PythonToolbox"

TSharedRef<FWorkspaceItem> FPythonToolbox::MenuRoot = FWorkspaceItem::NewGroup(FText::FromString("Menu Root"));

void FPythonToolbox::AddModuleListeners()
{
	//jaff han 20240419
	TArray<FString> FileNames;
	FFileManagerGeneric FileMgr;
	FileMgr.SetSandboxEnabled(true);
	const FString Wildcard("*.xml"); 
	const FString SearchPath(FPaths::Combine(*FPaths::ProjectContentDir(), TEXT("Scripts"), *Wildcard));

	FileMgr.FindFiles(FileNames, *SearchPath, true,  false);
	
	UE_LOG(LogTemp, Warning,TEXT("Python Files Num : %d"), FileNames.Num());
	
	for (FString f : FileNames)
	{
		UE_LOG(LogTemp, Warning,TEXT("Python File : %s"), *f);
		FString FilePath(FPaths::Combine(*FPaths::ProjectContentDir(), TEXT("Scripts"), *f));
		ModuleListeners.Add(MakeShared<TabTool>(FilePath));
	}
}

void FPythonToolbox::StartupModule()
{
	if (!IsRunningCommandlet())
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditorMenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
		MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuExtension("Developer", EExtensionHook::Before, TSharedPtr<FUICommandList>(), FMenuExtensionDelegate::CreateRaw(this,&FPythonToolbox::ExtendMenu));
		LevelEditorMenuExtensibilityManager->AddExtender(MenuExtender);
	}
	IPythonToolboxInterface::StartupModule();
}

void FPythonToolbox::ShutdownModule()
{	
	IPythonToolboxInterface::ShutdownModule();
}

void FPythonToolbox::AddMenuExtension(const FMenuExtensionDelegate &ExtensionDelegate, FName ExtensionHook, const TSharedPtr<FUICommandList> &CommandList, EExtensionHook::Position Position)
{
	MenuExtender->AddMenuExtension(ExtensionHook, Position, CommandList, ExtensionDelegate);
}

void FPythonToolbox::ExtendMenu(FMenuBuilder &MenuBuilder)
{
	MenuBuilder.BeginSection("Tools",FText::FromString("Tools"));
	//MenuBuilder.AddMenuSeparator(FName("ToolsDoc"));
	MenuBuilder.EndSection();
}
