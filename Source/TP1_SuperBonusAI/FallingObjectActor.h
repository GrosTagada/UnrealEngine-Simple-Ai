// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingObjectActor.generated.h"

UCLASS()
class TP1_SUPERBONUSAI_API AFallingObjectActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* SpriteComponent;
	
public:	
	// Sets default values for this actor's properties
	AFallingObjectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
