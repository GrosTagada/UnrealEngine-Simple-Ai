// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "Components/SteeringBehaviorComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperFlipbookComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowerActor.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectSpawn,AActor*,SpawnedActor);

UCLASS()
class TP1_SUPERBONUSAI_API AThrowerActor : public APawn
{
	GENERATED_BODY()
	
	
	//J'aurai pu faire un héritage ...
	
	UPROPERTY(VisibleAnywhere)
	class UPaperFlipbookComponent* PaperSpriteComponent;
	
	UPROPERTY(VisibleAnywhere)
	class USteeringBehaviorComponent* SteeringBehaviorComponent;
	
	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* FloatingPawnMovement;
	
	//il me faut une range pour le déplacement aléatoire
	//coté droit, coté gauche
	
	UPROPERTY(EditAnywhere)
	int MaxRange = 10;
	UPROPERTY(EditAnywhere)
	int MinRange = 10;
	
	UPROPERTY(EditAnywhere)
	float MinDistanceBeetweenLaunch = 1;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorToSpawn;
	
	FVector TargetPos;
	
	void LaunchObject();
	void SelectNewPos();
	void ChangeSpriteRotation(float velocity);
public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnObjectSpawn OnObjectSpawn;

public:	
	// Sets default values for this actor's properties
	AThrowerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
