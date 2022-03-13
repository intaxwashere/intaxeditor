// Copyright INTAX Interactive, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "IntaxEditorDeveloperSettings.generated.h"

UCLASS(Config="Editor", DisplayName="Intax Editor Settings")
class INTAXEDITOR_API UIntaxEditorDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	
	UPROPERTY(Config, EditAnywhere, Category="Intax Editor")
	TMap<TSubclassOf<AActor>, FName> ActorFolderPathMap;
};
