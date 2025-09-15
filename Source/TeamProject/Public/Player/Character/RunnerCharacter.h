// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Character/BaseCharacter.h"
#include "InputActionValue.h"
#include "GameFrameWork/MainMap/MainMapGameMode.h"
#include "GameFrameWork/MainMap/StaticMeshManager/StaticMeshManageList.h"
#include "RunnerCharacter.generated.h"


class USTInputConfig;
class UCameraComponent;
class USpringArmComponent;
class URunnerRepelComponent;
class URunnerInterActiveComponent;

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ARunnerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	ARunnerCharacter();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTexture2D* RunnerAimImg;
	
	UTexture2D* GetAimImg() const override {return RunnerAimImg;}

	UFUNCTION(Server, Reliable)
	void SetCurrentObjectType(EStaticMeshType MeshType);

	UFUNCTION()
	void OnRep_ObjectType();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void SetGhostMode();

	UFUNCTION(Client, Reliable)
	void SetOutLine(const TArray<ARunnerCharacter*> & OutlineTargets, bool Active);

public:
	virtual void SetBaseCharacterActive(bool Active) override;

	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	//Input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Jump(const FInputActionValue& InputActionValue);
	void Input_StopJump(const FInputActionValue& InputActionValue);


	// RepelComponent
	virtual URepelComponent* GetRepelComponent() const override;

	// InterActiveComponent
	virtual UPawnInterActiveComponent* GetInterActiveComponent() const override;

private:
	void SetObjectMode(EStaticMeshType MeshType);

	UFUNCTION()
	void InitializeCharacter(EGameMode GameMode);

	UFUNCTION()
	void ResetCharacter();
	
private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ObjectType, meta = (AllowPrivateAccess = true))
	EStaticMeshType CurrentObjectType = EStaticMeshType::None;

	int32 InitCapsuleHalfHeight;
	int32 InitCapsuleRadius;
	
	
private:
#pragma region component
	
	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta =(AllowPrivateAccess = true))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta =(AllowPrivateAccess = true))
	// UCameraComponent* FollowCamera;

	// RepelComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Repel", meta = (AllowPrivateAccess = true))
	URunnerRepelComponent* RunnerRepelComponent;

	// InteractiveComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InterActive", meta =(AllowPrivateAccess = true))
	URunnerInterActiveComponent* RunnerInterActiveComponent;

	//StaticMeshComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticMesh", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* StaticMesh;


public:
	FORCEINLINE URunnerRepelComponent* GetRunnerRepelComponent() const { return RunnerRepelComponent; }
	FORCEINLINE URunnerInterActiveComponent* GetRunnerInterActiveComponent() const { return RunnerInterActiveComponent; }
#pragma endregion

public:
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Test();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UInputMappingContext* ObjectInputMappingContext;

	FORCEINLINE UInputMappingContext* GetObjectInputMappingContext() const { return ObjectInputMappingContext; }

	UFUNCTION(BlueprintCallable)
	void SetObjectInputMappingContext(UInputMappingContext* ItemInputMappingContext);
};
