// Copyright INTAX Interactive, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "IntaxEditorSubsystem.generated.h"

UCLASS()
class INTAXEDITOR_API UIntaxEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:

	/** WARNING! DO NOT CALL THIS FUNCTION IN BLUEPRINTS OUTSIDE OF BLUTILITY FRAMEWORK.
	 * EDITOR SUBSYSTEMS DOES NOT EXIST IN SHIPPING BUILDS. */
	UFUNCTION(BlueprintCallable)
	void OrganizeWorldOutliner();

protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void OnActorsDropped(const TArray<UObject*>& Objects, const TArray<AActor*>& Actors);

	virtual void OnRuntimeActorSpawned(AActor* SpawnedActor);

private:

	void SetFolderPathForActor(AActor* Actor) const;

	FOnActorSpawned::FDelegate OnActorSpawnedHandler;

};
