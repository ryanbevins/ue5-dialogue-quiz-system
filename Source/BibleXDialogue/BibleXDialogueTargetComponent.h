// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BibleXDialogueDialogueStructs.h"
#include "BibleXDialogueTargetComponent.generated.h"

class UDataTable;
class UBibleXDialogueOriginComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeginDialogue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnswer, const bool, IsTrue);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BIBLEXDIALOGUE_API UBibleXDialogueTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBibleXDialogueTargetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets required origin component(This should be originating from player!)
	void SetOriginComponent(UBibleXDialogueOriginComponent* NewOriginComponent);

public:
	// OnBeginDialogue delegate. Called when dialogue starts
	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FOnBeginDialogue OnBeginDialogue;
	// OnAnswer delegate. Called when user selects answer
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Dialogue")
	FOnAnswer OnAnswer;

protected:
	// DialogueTable asset to take dialogues from, must be FDialogue type.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	UDataTable* DialogueTable;
	// What amount to multiply difficulty score of question by before adding/subtracting onto player score
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	float DifficultyGain = 5;
	// DialogueOriginComponent(Likely originating from player)
	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	UBibleXDialogueOriginComponent* OriginComponent;
	// Current dialogue being displayed on screen
	UPROPERTY(BlueprintReadWrite, Category = "Dialogue")
	FDialogue CurrentDialogue;
	// Assigned to be the DialogueTable row names, for easy access and being able to remove rows without editing dialoguetable asset.
	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	TArray<FName> LocalDataTableNames;

protected:
	// Get Dialogue from components dialogue datatable within specified difficulty limit
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	FDialogue GetDialogueWithinDifficultyLimit(float DifficultyLimit, bool bRemoveDialogueFromTable);
	// Returns true if current dialogue instance has one or more elements left
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool HasDialogueRemaining();
	// Resets dialogue state
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void ResetDialogueState();

private:
};
