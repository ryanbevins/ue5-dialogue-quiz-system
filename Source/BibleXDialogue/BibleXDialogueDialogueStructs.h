// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/UnrealString.h"
#include "Engine/DataTable.h"
#include "BibleXDialogueDialogueStructs.generated.h"

// Structure used for answer instances
USTRUCT(BlueprintType)
struct FAnswer {
	GENERATED_BODY()
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString AnswerText = "Default";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsTrue = false;
};

// Structure used for dialogue instances
USTRUCT(BlueprintType)
struct FDialogue : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DialogueSpeakerName = "Default";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString QuestionText = "Default";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAnswer> Answers;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DifficultyRating;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* AnimMontage;
};