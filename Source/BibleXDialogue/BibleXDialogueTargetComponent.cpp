// Fill out your copyright notice in the Description page of Project Settings.


#include "BibleXDialogueTargetComponent.h"
#include "BibleXDialogueOriginComponent.h"
#include "Engine/DataTable.h"

// Sets default values for this component's properties
UBibleXDialogueTargetComponent::UBibleXDialogueTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBibleXDialogueTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	ResetDialogueState();
}

void UBibleXDialogueTargetComponent::SetOriginComponent(UBibleXDialogueOriginComponent* NewOriginComponent)
{
	if (NewOriginComponent) 
	{
		OriginComponent = NewOriginComponent;
	}
}

FDialogue UBibleXDialogueTargetComponent::GetDialogueWithinDifficultyLimit(float DifficultyLimit, bool bRemoveDialogueFromTable)
{
	FDialogue Dialogue;
	for (int i = 0; i < LocalDataTableNames.Num(); i++)
	{
		FDialogue NewDialogue = *DialogueTable->FindRow<FDialogue>(LocalDataTableNames[i], FString(""));
		if (NewDialogue.DifficultyRating <= DifficultyLimit)
		{
			Dialogue = NewDialogue;
			if (bRemoveDialogueFromTable) LocalDataTableNames.RemoveAt(i, 1, true);
			return Dialogue;
		}
	}
	return Dialogue;
}

bool UBibleXDialogueTargetComponent::HasDialogueRemaining() 
{
	return LocalDataTableNames.Num() > 0;
}

void UBibleXDialogueTargetComponent::ResetDialogueState()
{
	if (OriginComponent) OriginComponent->ResetDifficulty();
	LocalDataTableNames = DialogueTable->GetRowNames();
}

