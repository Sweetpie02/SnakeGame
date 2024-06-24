// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameGameModeBase.generated.h"


UCLASS()
class SNAKEGAME_API ASnakeGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASnakeGameGameModeBase();

	//UPROPERTY(EditDefaultsOnly)
	//TArray<TSubClassOf<ABonusBase>> SpawnActorArray;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

//public:
//	void SpawnSomething;
};
