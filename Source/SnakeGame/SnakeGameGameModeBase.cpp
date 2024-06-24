// Copyright Epic Games, Inc. All Rights Reserved.


#include "SnakeGameGameModeBase.h"

ASnakeGameGameModeBase::ASnakeGameGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASnakeGameGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASnakeGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	bool bSpawnTimer = false;
	if (bSpawnTimer)
	{
		FTimerHandle SpawnTimer;
	}
}


