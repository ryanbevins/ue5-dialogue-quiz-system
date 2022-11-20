// Fill out your copyright notice in the Description page of Project Settings.


#include "BibleXDialogueOriginComponent.h"
#include "BibleXDialogueTargetComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UBibleXDialogueOriginComponent::UBibleXDialogueOriginComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBibleXDialogueOriginComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningActor = GetOwner();
	DefaultDifficultyScore = CurrentDifficultyScore;
}

void UBibleXDialogueOriginComponent::DecreaseDifficulty(float DecreaseAmount)
{
	CurrentDifficultyScore -= DecreaseAmount;
}

void UBibleXDialogueOriginComponent::IncreaseDifficulty(float IncreaseAmount)
{
	CurrentDifficultyScore += IncreaseAmount;
}

void UBibleXDialogueOriginComponent::ResetDifficulty()
{
	CurrentDifficultyScore = DefaultDifficultyScore;
}

bool UBibleXDialogueOriginComponent::TryStartDialogue(FVector TraceOriginLocation, FVector TraceEndLocation, bool bDebugLineTrace)
{
	AActor* HitActor;

	TArray<AActor*> ActorsToIgnore;
	FHitResult Hit;

	UKismetSystemLibrary::LineTraceSingle(this,
		TraceOriginLocation,
		TraceEndLocation,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		true,
		ActorsToIgnore,
		bDebugLineTrace ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		Hit,
		true
	);

	HitActor = Hit.GetActor();

	if (!HitActor) return false;

	UActorComponent* HitActorComponent = HitActor->GetComponentByClass(UBibleXDialogueTargetComponent::StaticClass());
	if (HitActorComponent) {
		UBibleXDialogueTargetComponent* HitActorInteractionComponent = Cast<UBibleXDialogueTargetComponent>(HitActorComponent);
		HitActorInteractionComponent->SetOriginComponent(this);
		HitActorInteractionComponent->OnBeginDialogue.Broadcast();
	}
	return true;
}

