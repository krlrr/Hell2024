#pragma once
#include "../Common.h"
#include "../Game/WeaponManager.h"
#include "../Game/AnimatedGameObject.h"
#include "../Input/keycodes.h"
#include "../Physics/Physics.h"

#define GLOCK_CLIP_SIZE 12
#define GLOCK_MAX_AMMO_SIZE 200
#define AKS74U_MAG_SIZE 30
#define AKS74U_MAX_AMMO_SIZE 9999
#define SHOTGUN_AMMO_SIZE 8
#define SHOTGUN_MAX_AMMO_SIZE 9999

struct Ammo {
	int clip = 0;
	int total = 0;
};

struct Inventory {
    Ammo glockAmmo;
    Ammo aks74uAmmo;
    Ammo shotgunAmmo;
};

enum InputType {
    KEYBOARD_AND_MOUSE,
    CONTROLLER
};

enum CrosshairType {
    NONE,
    REGULAR,
    INTERACT
};

struct PickUpText {
    std::string text;
    float lifetime;
    int count = 1;
};


enum class ShellEjectionState {
    IDLE, AWAITING_SHELL_EJECTION
};

struct PlayerControls {
    unsigned int WALK_FORWARD = HELL_KEY_W;
    unsigned int WALK_BACKWARD = HELL_KEY_S;
    unsigned int WALK_LEFT = HELL_KEY_A;
    unsigned int WALK_RIGHT = HELL_KEY_D;
    unsigned int INTERACT = HELL_KEY_E;
    unsigned int RELOAD = HELL_KEY_R;
    unsigned int FIRE = HELL_MOUSE_LEFT;
    unsigned int ADS = HELL_MOUSE_RIGHT;
    unsigned int JUMP = HELL_KEY_SPACE;
    unsigned int CROUCH = HELL_KEY_WIN_CONTROL; // different mapping to the standard glfw HELL_KEY_LEFT_CONTROL
    unsigned int NEXT_WEAPON = HELL_KEY_Q;
    unsigned int ESCAPE = HELL_KEY_WIN_ESCAPE;
    unsigned int DEBUG_FULLSCREEN = HELL_KEY_G;
    unsigned int DEBUG_ONE = HELL_KEY_1;
    unsigned int DEBUG_TWO = HELL_KEY_2;
    unsigned int DEBUG_THREE = HELL_KEY_3;
    unsigned int DEBUG_FOUR = HELL_KEY_4;
    unsigned int MELEE = HELL_KEY_F;
};

struct WeaponState {
    bool has = false;
    bool useSlideOffset = false;
    bool hasScope = false;
    bool hasSilencer = false;
    int ammoInMag = 0;
    std::string name = UNDEFINED_STRING;
};

struct AmmoState {
    std::string name = UNDEFINED_STRING;
    int ammoOnHand = 0;
};

class Player {

private:
    int32_t m_viewWeaponAnimatedGameObjectIndex = -1;
    int32_t m_characterModelAnimatedGameObjectIndex = -1;
    int32_t m_playerIndex = -1;
    std::vector<PickUpText> m_pickUpTexts;
    glm::vec2 m_headBob;
    glm::vec2 m_breatheBob;
    Transform m_weaponSwayTransform;
    bool m_crouching = false;
    bool m_moving = false;
    float m_headBobTimer = 0;
    float m_breatheBobTimer = 0;
    bool m_ignoreControl = false;
    int m_killCount = 0;
    int m_mouseIndex = -1;
    int m_keyboardIndex = -1;
    float m_capsuleRadius = 0.1f;
    ShellEjectionState m_shellEjectionState;
    glm::mat4 m_weaponSwayMatrix = glm::mat4(1);
    glm::mat4 m_casingSpawnMatrix = glm::mat4(1);
    glm::mat4 m_muzzleFlashMatrix = glm::mat4(1);


public:
    bool m_pickUpInteractable = false;
    bool g_awaitingRespawn = true;

    Player() = default;
    Player(int playerIndex);

    // Updates
    void Update(float deltaTime);
    void UpdateRagdoll();
    void UpdateMouseLook(float deltaTime);
    void UpdateViewMatrix(float deltaTime);
    void UpdateMovement(float deltaTime);
    void UpdatePickupText(float deltaTime);
    void UpdateCharacterModelAnimation(float deltaTime);
    void UpdateTimers(float deltaTime);
    void UpdateHeadBob(float deltaTime);
    void UpdateAudio(float deltaTime);

    // Checks
    void CheckForAndEvaluateInteract();
    void CheckForAndEvaluateRespawnPress();
    void CheckForAndEvaluateNextWeaponPress();
    void CheckForEnviromentalDamage(float deltaTime);
    void CheckForDeath();
    void CheckForDebugKeyPresses();

    // State queries
    bool IsMoving();
    bool IsCrouching();
    bool IsDead();
    bool IsAlive();
    bool HasControl();

    // Weapon shit
    void UpdateViewWeaponLogic(float deltaTime);
    void GiveDefaultLoadout();
    WeaponInfo* GetCurrentWeaponInfo();
    WeaponState* GetWeaponStateByName(std::string name);
    WeaponState* GetCurrentWeaponState();
    AmmoState* GetAmmoStateByName(std::string name);
    void GiveWeapon(std::string name);
    void GiveAmmo(std::string name, int amount);
    void SwitchWeapon(std::string name, WeaponAction weaponAction);
    void GiveRedDotToWeapon(std::string name);
    void GiveSilencerToWeapon(std::string name);
    void DropWeapons();
    void UpdateWeaponSway(float deltaTime);
    RenderItem3D CreateAttachmentRenderItem(WeaponAttachmentInfo* weaponAttachmentInfo, const char* boneName);
    bool CanMelee();
    void CheckForMeleeHits();

    // Rando
    void Respawn();
    void EnableControl();
    void DisableControl();

private:
    std::vector<RenderItem3D> m_attachmentRenderItems;
    std::vector<RenderItem3D> m_attachmentGlassRenderItems;
public:
    void UpdateAttachmentRenderItems();
    void UpdateAttachmentGlassRenderItems();
    std::vector<RenderItem3D>& GetAttachmentRenderItems();
    std::vector<RenderItem3D>& GetAttachmentGlassRenderItems();

    // Input
    int32_t GetKeyboardIndex();
    int32_t GetMouseIndex();
    void SetKeyboardIndex(int32_t index);
    void SetMouseIndex(int32_t index);
    bool PressingWalkForward();
    bool PressingWalkBackward();
    bool PressingWalkLeft();
    bool PressingWalkRight();
    bool PressingCrouch();
    bool PressedWalkForward();
    bool PressedWalkBackward();
    bool PressedWalkLeft();
    bool PressedWalkRight();
    bool PressedInteract();
    bool PressedReload();
    bool PressedFire();
    bool PressingFire();
    bool PresingJump();
    bool PressedCrouch();
    bool PressedNextWeapon();
    bool PressingADS();
    bool PressedADS();
    bool PressedEscape();
    bool PressedMelee();

    // Misc gameplay shit
    int32_t GetKillCount();
    void IncrementKillCount();

    // Misc getters
    int32_t GetViewWeaponAnimatedGameObjectIndex();
    int32_t GetCharacterModelAnimatedGameObjectIndex();
    int32_t GetPlayerIndex();
    glm::vec3 GetMuzzleFlashPosition();
    glm::vec3 GetPistolCasingSpawnPostion();
    AnimatedGameObject* GetCharacterAnimatedGameObject();
    AnimatedGameObject* GetViewWeaponAnimatedGameObject();


    std::vector<WeaponState> m_weaponStates;
    std::vector<AmmoState> m_ammoStates;
    int m_currentWeaponIndex = 0;

    void CreateCharacterModel();
    void CreateViewModel();

public:


    InputType _inputType = KEYBOARD_AND_MOUSE;
    PlayerControls _controls;

	PhysXRayResult _cameraRayResult;

	//RayCastResult _cameraRayData;
	PxController* _characterController = NULL;

    PxShape* _itemPickupOverlapShape = NULL;
    PxShape* _meleeHitCheckOverlapShape = NULL;
	//PxRigidStatic* _itemPickupOverlapDebugBody = NULL;
    float _yVelocity = 0;

	//Inventory _inventory;


	int GetCurrentWeaponMagAmmo();
	int GetCurrentWeaponTotalAmmo();
    void SetPosition(glm::vec3 position);

    bool _glockSlideNeedsToBeOut = false;
    bool _needsShotgunFirstShellAdded = false;
    bool _needsShotgunSecondShellAdded = false;

    int _health = 100;
    float _damageColorTimer = 1.0f;
    float _outsideDamageTimer = 0;
    float _outsideDamageAudioTimer = 0;

    void GiveDamageColor();

	//void Init(glm::vec3 position);


	void SetRotation(glm::vec3 rotation);
	//void SetWeapon(Weapon weapon);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetInverseViewMatrix();
	glm::vec3 GetViewPos();
	glm::vec3 GetViewRotation();
	glm::vec3 GetFeetPosition();
	glm::vec3 GetCameraRight();
	glm::vec3 GetCameraForward();
	glm::vec3 GetCameraUp();
    //int GetCurrentWeaponIndex();

    void UpdateViewWeaponLogicAndAnimations(float deltaTime);
	void SpawnMuzzleFlash();
    void SpawnCasing(AmmoInfo* ammoInfo);
    void SpawnAKS74UCasing();
    void SpawnShotgunShell();
	float GetMuzzleFlashTime();
	float GetMuzzleFlashRotation();
	float GetRadius();
	void CreateCharacterController(glm::vec3 position);
	//void WipeYVelocityToZeroIfHeadHitCeiling();
	PxShape* GetCharacterControllerShape();
	PxRigidDynamic* GetCharacterControllerActor();
	void CreateItemPickupOverlapShape();
	PxShape* GetItemPickupOverlapShape();

	void AddPickUpText(std::string text, int count);
    //void PickUpAKS74U();
    //void PickUpAKS74UAmmo();
    //void PickUpShotgunAmmo();
    //void PickUpGlockAmmo();
	//void CastMouseRay();
	//void DropAKS7UMag();
    void CheckForMeleeHit();

    void SetGlockAnimatedModelSettings();

	//ShadowMap _shadowMap;
	float _muzzleFlashCounter = 0;

	bool MuzzleFlashIsRequired();
	glm::mat4 GetWeaponSwayMatrix();
    WeaponAction& GetWeaponAction();

    glm::vec3 GetGlockBarrelPosition();

	bool _isGrounded = true;

    void PickUpShotgun();



    glm::mat4 GetProjectionMatrix();

    bool CanEnterADS();
    bool InADS();


	//std::string _pickUpText = "";
	//float _pickUpTextTimer = 0;
    float _zoom = 1.0f;


    //void LoadWeaponInfo(std::string name, WeaponAction weaponAction);

    float finalImageContrast = 1.0f;
    glm::vec3 finalImageColorTint = glm::vec3(0);



    // Dev keys
    bool PressedFullscreen();
    bool PressedOne();
    bool PressedTwo();
    bool PressedThree();
    bool PressedFour();

    glm::vec3 GetCameraRotation();

    void HideKnifeMesh();
    void HideGlockMesh();
    void HideShotgunMesh();
    void HideAKS74UMesh();
    void Kill();
    PxU32 _interactFlags;
    PxU32 _bulletFlags;
    std::string _playerName;
    bool _isDead = false;
    glm::vec3 _movementVector = glm::vec3(0);
    float _timeSinceDeath = 0;
    bool _isOutside = false;

    float _currentSpeed = 0.0f;

    void ForceSetViewMatrix(glm::mat4 viewMatrix);
    std::vector<RenderItem2D> GetHudRenderItems(hell::ivec2 presentSize);
    std::vector<RenderItem2D> GetHudRenderItemsHiRes(hell::ivec2 gBufferSize);
    CrosshairType GetCrosshairType();


    bool RespawnAllowed();

private:

    glm::vec3 _displacement;

	void SpawnBullet(float variance, Weapon type);
	bool CanFire();
	bool CanReload();
	void CheckForItemPickOverlaps();

	bool _needsToDropAKMag = false;

    float _footstepAudioTimer = 0;
    float _footstepAudioLoopLength = 0.5;

	glm::vec3 _position = glm::vec3(0);
	glm::vec3 _rotation = glm::vec3(-0.1f, -HELL_PI * 0.5f, 0);
	float _viewHeightStanding = 1.65f;
	float _viewHeightCrouching = 1.15f;
	float _crouchDownSpeed = 17.5f;
	float _currentViewHeight = _viewHeightStanding;
	float _walkingSpeed = 4.85f;
	float _crouchingSpeed = 2.325f;
	glm::mat4 _viewMatrix = glm::mat4(1);
	glm::mat4 _inverseViewMatrix = glm::mat4(1);
	glm::vec3 _viewPos = glm::vec3(0);
	glm::vec3 _forward = glm::vec3(0);
	glm::vec3 _up = glm::vec3(0);
	glm::vec3 _right = glm::vec3(0);

	float _muzzleFlashTimer = 0;
	float _muzzleFlashRotation = 0;
	//int _currentWeaponIndex = 0;
	WeaponAction _weaponAction = DRAW_BEGIN;
	bool _needsRespawning = true;
	glm::vec2 _weaponSwayFactor = glm::vec2(0);
	glm::vec3 _weaponSwayTargetPos = glm::vec3(0);
	bool _needsAmmoReloaded = false;

};