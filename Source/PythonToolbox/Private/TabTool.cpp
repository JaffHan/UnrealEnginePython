#include "TabTool.h"
#include "PythonToolbox.h"
#include "Runtime/XmlParser/Public/XmlFile.h"
#include "UnrealEnginePython.h"

#define LOCTEXT_NAMESPACE "Toolbox"

void TabTool::OnStartupModule()
{
	Initialize();
	//FPythonToolboxBase::OnStartupModule();
	//FPythonToolbox::Get().AddMenuExtension(FMenuExtensionDelegate::CreateRaw(this, &TabTool::MakeMenuEntry), FName("Tools"));
}

void TabTool::OnShutdownModule()
{
	//FPythonToolboxBase::OnShutdownModule();
}

void TabTool::MakeMenuEntryRoot(FMenuBuilder &MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
					 FText::FromName(TabName),
					ToolTipText,
					FSlateIcon(),
					FUIAction
					(
						FExecuteAction::CreateRaw(this,&TabTool::RunPy)
					)
					);

}
void TabTool::MakeMenuEntryWithSection(FMenuBuilder &MenuBuilder)
{
	MenuBuilder.BeginSection(*Category);
	MenuBuilder.AddMenuEntry(
	FText::FromName(TabName),
   ToolTipText,
					FSlateIcon(),
					FUIAction
					(
						FExecuteAction::CreateRaw(this,&TabTool::RunPy)
					)
					);
	MenuBuilder.EndSection();
}
void TabTool::MakeMenuEntryCategory(FMenuBuilder &MenuBuilder)
{
		MenuBuilder.AddSubMenu(
	FText::FromString(Category),
	FText::FromString("This is example sub menu"),
	FNewMenuDelegate::CreateSP(this, &TabTool::MakeMenuEntryWithSection)
);
}

void TabTool::Initialize()
{
	FXmlFile Xml(FilePath, EConstructMethod::ConstructFromFile);
	if (Xml.GetRootNode())
	{
		const FXmlNode* RootNode = Xml.GetRootNode();
		TabName = FName(*RootNode->GetAttribute(TEXT("Name")));
		TabDisplayName = FText::FromString(RootNode->FindChildNode(TEXT("DisplayName"))->GetContent());
		ToolTipText = FText::FromString(RootNode->FindChildNode(TEXT("Tooltip"))->GetContent());
		ToolPath = RootNode->FindChildNode(TEXT("Entry"))->GetContent();
		Category = RootNode->FindChildNode(TEXT("Category"))->GetContent();

		//root
		if(Category.IsEmpty())
		{
			FPythonToolbox::Get().AddMenuExtension(
				FMenuExtensionDelegate::CreateRaw(this, &TabTool::MakeMenuEntryRoot),
				FName("Tools"));
		}
		else //sub menu
			{
			if(FPythonToolbox::Get().ExistCategory(Category))
			{
				FPythonToolbox::Get().AddMenuExtension(
					FMenuExtensionDelegate::CreateRaw(this, &TabTool::MakeMenuEntryRoot),
					FName(*Category));
			}
			else
			{
				FPythonToolbox::Get().AddMenuExtension(
					FMenuExtensionDelegate::CreateRaw(this, &TabTool::MakeMenuEntryCategory),
					FName("Tools"));
				FPythonToolbox::Get().AddCategory(Category);
			}}
	}
	else
	{
		UE_LOG(LogTemp, Warning,TEXT("Xml Error"));
	}
}
/*
TSharedRef<SDockTab> TabTool::SpawnTab(const FSpawnTabArgs& TabSpawnArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(PythonToolboxPanel)
			.Tool(SharedThis(this))
		];

	return SpawnedTab;
}
*/
void TabTool::RunPy()
{
	FUnrealEnginePythonModule &PythonModule = FModuleManager::GetModuleChecked<FUnrealEnginePythonModule>("UnrealEnginePython");
	PythonModule.RunFile(TCHAR_TO_ANSI(*ToolPath));
}
