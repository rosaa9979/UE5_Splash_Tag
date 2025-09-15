// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "SpawnerManagerSubsystem.generated.h"

struct FSpawnRequest;
class UObjectSpawnMappingData;
class ABaseObjectSpawner;
class ABaseObject;
class UObjectSpawnRequestData;
struct FObjectClassMapping;

/**
 * 하이브리드 할당 알고리즘을 사용하여 스포너들에게 태그를 할당하고
 * 중앙에서 클래스 선택까지 처리하는 스폰 관리 서브시스템
 */
UCLASS()
class TEAMPROJECT_API USpawnerManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// 서브시스템 라이프사이클
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// 스포너 등록/해제
	UFUNCTION(BlueprintCallable, Category = "Spawner Manager")
	void RegisterSpawner(ABaseObjectSpawner* Spawner);
	
	UFUNCTION(BlueprintCallable, Category = "Spawner Manager")
	void UnregisterSpawner(ABaseObjectSpawner* Spawner);

	// 메인 스폰 실행 (하이브리드 알고리즘 사용)
	UFUNCTION(BlueprintCallable, Category = "Spawner Manager")
	void ExecuteSpawnRequests();

	// 스포너 정보 조회
	UFUNCTION(BlueprintCallable, Category = "Spawner Manager")
	FGameplayTagContainer GetSpawnerSupportedTypes(ABaseObjectSpawner* Spawner) const;
	
	UFUNCTION(BlueprintCallable, Category = "Spawner Manager")
	TArray<ABaseObjectSpawner*> GetSpawnersByType(FGameplayTag ObjectTypeTag) const;

	int32 GetSpawnerCount(FGameplayTag ObjectTypeTag) const;
	
	// 스폰 설정 관리
	UFUNCTION(BlueprintCallable, Category = "Spawner Manager")
	bool LoadSpawnConfiguration(const FString& RequestDataAssetPath, const FString& MappingDataAssetPath);
	
	UFUNCTION(BlueprintCallable, Category = "Spawner Manager")
	void ClearAllSpawners();

	// 유틸리티
	UFUNCTION(BlueprintCallable, Category = "Spawner Manager")
	TArray<TSubclassOf<ABaseObject>> GetAvailableClassesForType(FGameplayTag ObjectTypeTag) const;

protected:
	// 기본 스폰 데이터 경로
	static const FString DefaultSpawnRequestDataPath;
	static const FString DefaultSpawnMappingDataPath;

	// 등록된 스포너들
	UPROPERTY()
	TArray<ABaseObjectSpawner*> RegisteredSpawners;

	// 스폰 설정 데이터
	UPROPERTY()
	TObjectPtr<UObjectSpawnRequestData> SpawnRequestConfiguration;

	UPROPERTY()
	TObjectPtr<UObjectSpawnMappingData> SpawnMappingConfiguration;

	// 캐시된 오브젝트 매핑 정보
	UPROPERTY()
	TArray<FObjectClassMapping> CachedObjectMappings;

private:
	int MaxAttempts = 100;
	// === 하이브리드 할당 알고리즘 ===
	
	/** 스폰 요청들을 개별 태그 배열로 확장 */
	TArray<FGameplayTag> ExpandSpawnRequests() const;
	
	/** 주어진 태그들을 모든 스포너에 할당 가능한지 사전 체크 */
	bool IsAssignmentPossible(const TArray<FGameplayTag>& TagsToAssign) const;
	
	/** 탐욕 재시작 알고리즘으로 태그 할당 시도 */
	bool TryGreedyTagAssignment(
		const TArray<FGameplayTag>& TagsToAssign, 
		TMap<ABaseObjectSpawner*, FGameplayTag>& OutAssignment) const;
	
	/** 백트래킹 알고리즘으로 태그 할당 (완전 보장) */
	bool BacktrackAssignment(
		const TArray<FGameplayTag>& TagsToAssign,
		TMap<ABaseObjectSpawner*, FGameplayTag>& OutAssignment,
		int32 TagIndex = 0) const;
	
	/** 할당 계획에 따라 실제 스폰 실행 */
	void ExecuteTagAssignment(const TMap<ABaseObjectSpawner*, FGameplayTag>& Assignment);

	// === 스포너 선택 전략 ===
	
	/** 무작위로 스포너 선택 */
	ABaseObjectSpawner* SelectSpawnerForTag(
		const TArray<ABaseObjectSpawner*>& Candidates,
		const TArray<FGameplayTag>& RemainingTags,
		const TArray<ABaseObjectSpawner*>& AvailableSpawners) const;

	// === 중앙 집중식 클래스 선택 ===
	
	/** 주어진 태그에 대해 사용 가능한 클래스들 중 하나를 랜덤 선택 */
	TSubclassOf<ABaseObject> SelectRandomClassForTag(FGameplayTag ObjectTypeTag) const;

	// === 유틸리티 ===
	
	/** 특정 태그를 처리할 수 있는 아직 사용되지 않은 스포너들 반환 */
	TArray<ABaseObjectSpawner*> GetUnusedSpawnersForTag(
		FGameplayTag Tag,
		const TMap<ABaseObjectSpawner*, FGameplayTag>& CurrentAssignment) const;

	// === 설정 관리 ===
	
	void LoadDefaultSpawnConfiguration();
	void CacheObjectMappings();
	bool ValidateSpawnConfiguration() const;

public:
	// === 스폰 데이터 관리 ===
	UFUNCTION(BlueprintCallable, Category = "Spawner Manager")
	bool AddSpawnRequestData(const FGameplayTag& Tag, const int& Quantity);
	UFUNCTION(BlueprintCallable, Category = "Spawner Manager")
	void ClearSpawnRequestData();
	UFUNCTION(BlueprintCallable, Category = "Spawner Manager")
	void ClearAllSpawnedObjects();
};