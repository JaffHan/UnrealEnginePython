// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "UnrealEd.h"
#include "SlateExtras.h"
#include "Editor/LevelEditor/Public/LevelEditor.h"
#include "IPythonToolboxInterface.h"

class FPythonToolbox : public IPythonToolboxInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void AddModuleListeners() override;

	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline FPythonToolbox& Get()
	{
		return FModuleManager::LoadModuleChecked< FPythonToolbox >("PythonToolbox");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("PythonToolbox");
	}

	void AddMenuExtension(const FMenuExtensionDelegate &ExtensionDelegate, FName ExtensionHook, const TSharedPtr<FUICommandList> &CommandList = nullptr, EExtensionHook::Position Position = EExtensionHook::After);
	static TSharedRef<FWorkspaceItem> GetMenuRoot() { return MenuRoot; };
	bool ExistCategory(const FString Category) { return Categories.Contains(Category); };
	void AddCategory(const FString Category) {  Categories.Add(Category); };
	
protected:
	TSharedPtr<FExtensibilityManager> LevelEditorMenuExtensibilityManager;
	TSharedPtr<FExtender> MenuExtender;
	static TSharedRef<FWorkspaceItem> MenuRoot;
	TArray<FString> Categories;
	void ExtendMenu(FMenuBuilder &MenuBuilder);
};