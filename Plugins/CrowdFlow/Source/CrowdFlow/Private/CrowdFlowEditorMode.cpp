// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrowdFlowEditorMode.h"
#include "CrowdFlowEditorModeToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "CrowdFlowEditorModeCommands.h"


//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
// AddYourTool Step 1 - include the header file for your Tools here
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
#include "Tools/CrowdFlowSimpleTool.h"
#include "Tools/CrowdFlowInteractiveTool.h"

// step 2: register a ToolBuilder in FCrowdFlowEditorMode::Enter() below


#define LOCTEXT_NAMESPACE "CrowdFlowEditorMode"

const FEditorModeID UCrowdFlowEditorMode::EM_CrowdFlowEditorModeId = TEXT("EM_CrowdFlowEditorMode");

FString UCrowdFlowEditorMode::SimpleToolName = TEXT("CrowdFlow_ActorInfoTool");
FString UCrowdFlowEditorMode::InteractiveToolName = TEXT("CrowdFlow_MeasureDistanceTool");


UCrowdFlowEditorMode::UCrowdFlowEditorMode()
{
	FModuleManager::Get().LoadModule("EditorStyle");

	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(UCrowdFlowEditorMode::EM_CrowdFlowEditorModeId,
		LOCTEXT("ModeName", "CrowdFlow"),
		FSlateIcon(),
		true);
}


UCrowdFlowEditorMode::~UCrowdFlowEditorMode()
{
}


void UCrowdFlowEditorMode::ActorSelectionChangeNotify()
{
}

void UCrowdFlowEditorMode::Enter()
{
	UEdMode::Enter();

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// AddYourTool Step 2 - register the ToolBuilders for your Tools here.
	// The string name you pass to the ToolManager is used to select/activate your ToolBuilder later.
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////// 
	const FCrowdFlowEditorModeCommands& SampleToolCommands = FCrowdFlowEditorModeCommands::Get();

	RegisterTool(SampleToolCommands.SimpleTool, SimpleToolName, NewObject<UCrowdFlowSimpleToolBuilder>(this));
	RegisterTool(SampleToolCommands.InteractiveTool, InteractiveToolName, NewObject<UCrowdFlowInteractiveToolBuilder>(this));

	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, SimpleToolName);
}

void UCrowdFlowEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FCrowdFlowEditorModeToolkit);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UCrowdFlowEditorMode::GetModeCommands() const
{
	return FCrowdFlowEditorModeCommands::Get().GetCommands();
}

#undef LOCTEXT_NAMESPACE
