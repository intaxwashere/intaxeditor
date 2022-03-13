// Copyright INTAX Interactive, all rights reserved.

#include "IntaxEditorSubsystem.h"
#include "Editor.h"
#include "IntaxEditorDeveloperSettings.h"

void UIntaxEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// This delegate getting called whenever we drop an actor to 'current' level.
	FEditorDelegates::OnNewActorsDropped.AddUObject(this, &ThisClass::OnActorsDropped);

	// Bind another delegate for runtime spawned actors.
	if (UWorld* World = GetWorld())
	{
		OnActorSpawnedHandler.BindUObject(this, &ThisClass::OnRuntimeActorSpawned);
		
		World->AddOnActorSpawnedHandler(OnActorSpawnedHandler);
	}
}

void UIntaxEditorSubsystem::OnRuntimeActorSpawned(AActor* SpawnedActor)
{
#if WITH_EDITOR // paranoid sanity check. this subsystem does not exist outside of PIE but I'm a very paranoid person.
	SetFolderPathForActor(SpawnedActor);
#endif
}

void UIntaxEditorSubsystem::SetFolderPathForActor(AActor* Actor) const
{
	if (IsValid(Actor))
	{
		const TSubclassOf<AActor> Class = Actor->GetClass();
		const UIntaxEditorDeveloperSettings* DeveloperSettings = GetDefault<UIntaxEditorDeveloperSettings>();
		const FName* FoundPathName = DeveloperSettings->ActorFolderPathMap.Find(Class);
		if (FoundPathName && !FoundPathName->IsNone())
		{
			Actor->SetFolderPath(*FoundPathName);
		}
	}
}

void UIntaxEditorSubsystem::OnActorsDropped(const TArray<UObject*>& Objects, const TArray<AActor*>& Actors)
{
	for (AActor* Actor : Actors)
	{
		SetFolderPathForActor(Actor);
	}
}

void UIntaxEditorSubsystem::OrganizeWorldOutliner()
{
	const uint64 S = FPlatformTime::Cycles64();
	
	const UWorld* World = GWorld;
	ULevel* Level = World ? World->GetCurrentLevel() : nullptr;
	if (World && Level)
	{
		for (AActor* Actor : Level->Actors)
		{
			SetFolderPathForActor(Actor);
		}
	}

	const uint64 E = FPlatformTime::Cycles64();
	const float MS = static_cast<float>(FPlatformTime::ToMilliseconds64(E - S));
	UE_LOG(LogTemp, Log, TEXT("Organizing World Outliner took %f milliseconds."), MS);
}
