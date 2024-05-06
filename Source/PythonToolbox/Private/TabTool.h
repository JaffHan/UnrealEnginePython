#pragma once

#include "IPythonToolboxInterface.h"
#include "TabManager.h"
#include "SDockTab.h"

class TabTool : public IPythonToolboxListenerInterface, public TSharedFromThis< TabTool >
{
public:
	TabTool(const FString FilePath)
	{
		this->FilePath=FilePath;
	}
	virtual ~TabTool() {}
	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;
	virtual void Initialize() ;
	void RunPy();
	void MakeMenuEntryRoot(FMenuBuilder &MenuBuilder);
	void MakeMenuEntryCategory(FMenuBuilder &MenuBuilder);
	void MakeMenuEntryWithSection(FMenuBuilder &MenuBuilder);

protected:
	FString FilePath;
	FString Category;
//protected:
	FName TabName;
	FText TabDisplayName;
	FText ToolTipText;
	FString ToolPath;
};
