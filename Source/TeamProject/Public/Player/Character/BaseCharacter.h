

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "BaseType/BaseStructType.h"
#include "GameFramework/Character.h"
#include "Interface/InterActiveInterface.h"
#include "Interface/RepelInterface.h"
#include "UI/MainHUD/StaminaBar.h"
#include "BaseCharacter.generated.h"


class USTInputConfig;
struct FInputActionValue;
struct FInitEffectActorInfo;
class ANiagaraEffectActor;
struct FInitEffectActorInfo;
class ANiagaraEffectActor;
class UHealthBar;
class ABaseEffectActor;
class UPawnInterActiveComponent;
class USTAbilitySystemComponent;
class USTAttributeSet;
class USTExtensionComponent;

UCLASS()
class TEAMPROJECT_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public IRepelInterface, public IInterActiveInterface
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();

	virtual  UTexture2D* GetAimImg() const { return nullptr; }

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	// 캐릭터 Ability System 관련 함수
	void InitAbilityActorInfo();
	void InitClassDefaults();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual USTAttributeSet* GetAttributeSet() const;

	virtual USTExtensionComponent* GetExtensionComponent() const {return ExtensionComponent;}
	
	// AttributeSet Hud 등록
	UFUNCTION()
	void RegisterAttributeSetInHUD();

	virtual void Destroyed() override;

public:
	UFUNCTION(NetMulticast,Reliable, BlueprintCallable)
	virtual void SetBaseCharacterActive(bool Active);

	FGameplayTag GetBaseCharacterTag() const { return CharacterTag; }
	
	// AttachToComponent
	UFUNCTION(BlueprintCallable)
	void AttachActorToComponent_Replicated(AActor* TargetActor, USceneComponent* InParentComponent, FName SocketName);

	UFUNCTION()
	void OnRep_AttachData();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;


	// 죽음관련 로직
public:
		
	void OnHealthChanged (const FOnAttributeChangeData& Data);
	
	UPROPERTY(ReplicatedUsing=OnRep_IsDead)
	bool bIsDead = false;

	UPROPERTY(ReplicatedUsing=OnRep_IsGhost)
	bool bIsGhost = false;

	UPROPERTY(Replicated, BlueprintReadWrite)
	bool bIsRunnerCrouch = false;

	UPROPERTY(Replicated, BlueprintReadWrite)
	bool bIsTaggerCrouch = false;
	
	UFUNCTION()
	void OnRep_IsGhost();

	UFUNCTION()
	void OnRep_IsDead();
	
	UFUNCTION(Server, Reliable)
	void OnDied_Server();

	UFUNCTION(Server,Reliable)
	void OnGhost_Server();

// 사운드관련 로직

public:
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlayerFootStep(USoundBase* Sound, FVector Location, float Volume, float Pitch);

	UFUNCTION(Server, Reliable)
	void CallFootStepEffect(const FVector Location);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_FootStepEffect(const FVector Location);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	USTInputConfig* InputConfigDataAsset;

private:
	UPROPERTY(EditAnywhere, Category = "VFX")
	TSubclassOf<ABaseEffectActor> FootStepEffect;

protected:

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void Input_CameraMode(const FInputActionValue& InputActionValue);

	bool bIsCameraModeYawEnabled = false;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetUseControllerRotationYaw(bool bNewValue);

	UFUNCTION(Server, Reliable)
	void Server_SetCameraModeYaw(bool bNewValue);
	
	virtual void BeginPlay() override;

	virtual URepelComponent* GetRepelComponent() const override;
	virtual UPawnInterActiveComponent* GetInterActiveComponent() const override;

	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = true))
	TObjectPtr<USTExtensionComponent> ExtensionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = true))
	TObjectPtr<URepelComponent> RepelComponent;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USTAbilitySystemComponent> STAbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USTAttributeSet> STAttributes;

	UPROPERTY(EditAnywhere, Category = "Custom Values|Character Info")
	FGameplayTag CharacterTag;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaminaBar> StaminaWidget;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UHealthBar> HealthWidget;

	UPROPERTY(ReplicatedUsing = OnRep_AttachData)
	FAttachRepData AttachData;
		
	

};
