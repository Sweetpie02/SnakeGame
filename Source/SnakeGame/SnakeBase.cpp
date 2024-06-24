// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 10.f;
	LastMoveDirection = EMovementDirection::DOWN;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(5);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);

		if (SnakeElements.Num() > 0)
		{
			NewLocation = SnakeElements[SnakeElements.Num() - 1]->GetActorLocation();
		}

		FTransform NewTrnsform(NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTrnsform);
		NewSnakeElem->SnakeOwner = this;
		int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
		if (ElemIndex == 0)
		{
			NewSnakeElem->SetFirstElementType();
			
		}
	}
	
}

void ASnakeBase::Move()
{
	FVector MovementVector(ForceInitToZero);

		switch (LastMoveDirection)
		{
		case EMovementDirection::UP:
			MovementVector.X += ElementSize;
			break;
		case EMovementDirection::DOWN:
			MovementVector.X -= ElementSize;
			break;
		case EMovementDirection::LEFT:
			MovementVector.Y += ElementSize;
			break;
		case EMovementDirection::RIGHT:
			MovementVector.Y -= ElementSize;
			break;
		}
		
		//AddActorWorldOffset(MovementVector);
		SnakeElements[0]->ToggleCollision();


		for (int i = SnakeElements.Num() - 1; i > 0; i--)
		{
			auto CurrentElement = SnakeElements[i];
			auto PrevElement = SnakeElements[i - 1];
			FVector PrevLocation = PrevElement->GetActorLocation();
			CurrentElement->SetActorLocation(PrevLocation);
		}
		
		SnakeElements[0]->AddActorWorldOffset(MovementVector);
		SnakeElements[0]->ToggleCollision();

		Moving = false;
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlapeedElement, AActor* Other)
{
	if (IsValid(OverlapeedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlapeedElement, ElemIndex);
		bool  bIsFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst);
		}
	}
}

//void ASnakeBase::ChangeLife(int32 Amount)
//{
//	Life += Amount;
//
//	if (Life <= 0)
//	{
//		DestroySnake();
//	}
//}

//void ASnakeBase::ChangeSpeed(float Amount)
//{
//	SetActorTickInterval(MovementSpeed += Amount);
//}
//
//void ASnakeBase::DestroySnake()
//{
//	for (int i = SnakeElements.Num() - 1; i >= 0; i--)
//	{
//		SnakeElements[i]->Destroy();
//	}
//
//	this->Destroy();
//}