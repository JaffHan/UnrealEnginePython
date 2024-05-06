#include "SDockableTab.h"
#include "SlateApplication.h"
#include "TabTool.h"

class PythonToolboxPanel : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(PythonToolboxPanel)
	{}
	SLATE_ARGUMENT(TWeakPtr<class TabTool>, Tool)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

protected:
	TWeakPtr<TabTool> tool;
};