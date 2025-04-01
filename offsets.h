
namespace Offsets
{
	constexpr int32 GObjects          = 0x091EDDD8;
	constexpr int32 AppendString      = 0x03543C80;
	constexpr int32 GNames            = 0x091D5140;
	constexpr int32 GWorld            = 0x09328900;
	constexpr int32 ProcessEvent      = 0x0374BDD0;
	constexpr int32 ProcessEventIdx   = 0x00000043;
}
bHasStartedFloating;                               // 0x1434
struct FVector                                RelativeScale3D;                                   // 0x0134
class UAnimMontage*                           EquipAnimation;                                    // 0x0B00
class UCharacterMovementComponent*            CharacterMovement;                                 // 0x0288
EMovementMode                                 MovementMode;                                      // 0x0168
struct FVector                                PendingLaunchVelocity;                             // 0x03C4
float                                         ViewYawMax;                                        // 0x2790(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
float                                         ViewRollMin;                                       // 0x2794(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
TWeakObjectPtr<class AActor>                  CurrentVehicle;                                    // 0x0300
float                                         EmoteToFireCooldownTime;                           // 0x0974
float                                         ChargeTime;                                        // 0x0968
bool                                          bIgnoreTryToFireSlotCooldownRestriction;           // 0x0C79
class UFortWeaponItemDefinition*              WeaponData;                                        // 0x0378
float                                         ReviveFromDBNOTime;                                // 0x2DF8
float                                         DBNOStartTime;                                     // 0x2DFC
float                                         DBNOInvulnerableTime;                              // 0x2E00
bool                                          bADSWhileNotOnGround;                              // 0x3331
class ULevel*                                 PersistentLevel;                                   // 0x0030
class AGameStateBase*                         GameState;                                         // 0x0120
class UGameInstance*                          OwningGameInstance;                                // 0x0180
TArray<class ULocalPlayer*>                   LocalPlayers;                                      // 0x0038
class APlayerState*                           PlayerState;                                       // 0x0228
class USceneComponent*                        RootComponent;                                     // 0x0130
struct FVector                                ComponentVelocity;                                 // 0x0140
struct FVector                                RelativeLocation;                                  // 0x011C
struct FRotator                               RelativeRotation;                                  // 0x0128
bool                                          bHasWonAGame;                                      // 0x0DE0
int32                                         KillScore;                                         // 0x0E9C
uint8                                         bIsVisible : 1;                                    // 0x01F4


// WORLD ESP
TArray<class ULevel*>                         Levels;                                            // 0x0138
class UFortItemDefinition*                    ItemDefinition;                                    // 0x0018
class UWorld*                                 OwningWorld;                                       // 0x00B8
