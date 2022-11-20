// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BibleXDialogueOriginComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BIBLEXDIALOGUE_API UBibleXDialogueOriginComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBibleXDialogueOriginComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Traces out and tries to start dialogue if hits actor with "TraceTargetComponent" component, returns true if hit
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool TryStartDialogue(FVector TraceOriginLocation, FVector TraceEndLocation, bool bDebugLineTrace);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void DecreaseDifficulty(float DecreaseAmount);
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void IncreaseDifficulty(float IncreaseAmount);
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void ResetDifficulty();

public:
	UPROPERTY(BlueprintReadOnly)
	float CurrentDifficultyScore = 0.5f;

protected:
	bool bDrawDebugTraceInteract;

private:
	AActor* OwningActor;
	float DefaultDifficultyScore;
};
