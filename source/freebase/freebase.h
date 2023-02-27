#define COLOR_ORANGE					0
#define COLOR_RED						1
#define COLOR_GREEN						2
#define COLOR_WHITE						3
#define COLOR_BLUE						4
#define COLOR_YELLOW					5
#define COLOR_PINK						6
#define COLOR_BLACK						7
#define COLOR_PURPLE					8
#define INERTIALESSDRIVE1				0x00474893
#define INERTIALESSDRIVE2				0x004748A3
#define INFINITEBLOCK					0x00481AFD
#define LEAVERETN						0x005702D2
#define MULTICLIENT						0x00496A04
#define NAMEESP							0x0040A04B
#define NINJAJUMP						0x00483118
#define PAPERWALLS						0x0049A259
#define SMOKETRAIL						0x00486920
#define SERIALKEY						0x004972A7
#define SUICIDE							0x004A0B5B
#define SWEARING						0x0049155C
#define SWORDCROSSHAIR					0x0040607D
#define VERSION_FILE					2,3,30,5420
#define VERSION_FILESTR					"2.3.30.5420"
#define VERSION_FILESTRL				L"2.3.30.5420"
#define WALLHACK						0x00501A63
#define ZCHARACTER_GETAP				0x00473740
#define ZCHARACTER_GETHP				0x00473730
#define ZCHARACTER_LEVELDOWN			0x00473980
#define ZCHARACTER_LEVELUP				0x00473970
#define ZCHARACTER_SETAP				0x00473760
#define ZCHARACTER_SETHP				0x00473750
#define ZCHARACTERMANAGER_FIND			0x0047A660
#define ZGETCHARACTERMANAGER			0x0049E870
#define ZGETGAME						0x004ABDD0
#define ZGETGAMECLIENT					0x004ABCC0
#define ZGETGAMEINTERFACE				0x004ABCE0
#define ZMYCHARACTER_GETGRAVITYCONST	0x0047DB30
#define ZMYCHARACTER_SETDIRECTION		0x0047D980
#define ZPOSTCHANNELCHAT				0x004298D0
#define ZPOSTCHANNELREQUESTJOIN			0x004C4010
#define ZPOSTCHATROOMCHAT				0x00429550
#define ZPOSTCREATEMYCHAR				0x00448730
#define ZPOSTDASH						0x0047C6F0
#define ZPOSTFRIENDADD					0x00424460
#define ZPOSTFRIENDREMOVE				0x004244E0
#define ZPOSTGAMEKILL					0x004A07E0
#define ZPOSTPEERCHAT					0x004297F0
#define ZPOSTPEERCHATICON				0x004015F0
#define ZPOSTREACTION					0x0047E1D0
#define ZPOSTRELOAD						0x00432590
#define ZPOSTREQUESTEXPELCLANMEMBER		0x00424F90
#define ZPOSTREQUESTSPAWN				0x004B26C0
#define ZPOSTREQUESTSPAWN_PACKET		0x004B26DC
#define ZPOSTREQUESTSPAWNWORLDITEM		0x004B4640
#define ZPOSTREQUESTSTAGEJOIN			0x004257E0
#define ZPOSTSHOT						0x0047DF30
#define ZPOSTSHOTMELEE					0x0047E020
#define ZPOSTSHOTSP						0x00475C80
#define ZPOSTSKILL						0x0047DDA0
#define ZPOSTSTAGECREATE				0x00448230
#define ZPOSTSTAGEENTERBATTLE			0x004A05C0
#define ZPOSTSTAGELEAVEBATTLE			0x00433480
#define ZPOSTSTAGESETTING				0x0045BE00
#define ZPOSTSTAGESTART					0x00448E30
#define ZPOSTSTAGETEAM					0x00448480
#define ZPOSTWHERE						0x00424560

bool aimbot = false;
bool anchor = false;
bool antiKick = false;
bool bot = false;
bool botRoom = false;
bool bubbleAura = false;
bool chams = false;
bool circleFastestVortex = false;
bool circleMediumVortex = false;
bool circleSlowestVortex = false;
bool coloredTextures = false;
bool dashVortex = false;
bool exitStatus = false;
bool flame = false;
bool flashbangSpam = false;
bool flipmower = false;
bool fragmentationGrenadeSpam = false;
bool godmode = false;
bool hideConsole = false;
bool hideIRC = false;
bool hooked = false;
bool hurricane = false;
bool inertialessDrive = false;
bool infiniteBlock = false;
bool insaneMassives = false;
bool instantMassives = false;
bool lastAttacker = false;
bool lawnmower = false;
bool lungemower = false;
bool medicateLastAttacker = false;
bool medicateRoom = false;
bool medicator = false;
bool medicineHat = false;
bool medicineHatLastAttacker = false;
bool medicineHatRoom = false;
bool nameEsp = false;
bool ninjaJump = false;
bool noFog = false;
bool noMassives = false;
bool paperWalls = false;
bool petMode = false;
bool powerLevel = false;
bool reloadSpam = false;
bool rocketSpam = false;
bool roomRape = false;
bool safeguard = false;
bool shotSpam = false;
bool smokeGrenadeSpam = false;
bool smokeTrail = false;
bool speedHack = false;
bool sunMassives = false;
bool swordCrosshair = false;
bool wallHack = false;
bool wheelVortex = false;
bool wings = false;
bool wireframe = false;
bool xray = false;

char *ircNick = new char[1024];

struct MUID
{
	unsigned long zero;
	unsigned long id;
} peers[1500000];

DETOUR_TRAMPOLINE_EMPTY(bool OriginalTerminateProcess(void *process, unsigned int code));
DETOUR_TRAMPOLINE_EMPTY(float GetGravityConst()); 
DETOUR_TRAMPOLINE_EMPTY(void OriginalExitProcess(unsigned int code));
DETOUR_TRAMPOLINE_EMPTY(void ZPostChatRoomChat(char *chatRoom));

float gravity = 1.0f;
float savedPosition[3];

CD3DFont *font;

IDirect3DTexture9 *textures[9];

int currentMedicine = 111;
int color = COLOR_ORANGE;
int consolePosition = 0;
int dllSpeed = 10;
int r = 0;
int stride = 0;
int totalPeers = 0;

RECT rect;

SIRC *irc;

struct STAGE
{
	int x1;
	int x2;

	char mapName[32];

	int x3;

	unsigned int type;
	unsigned int rounds;
	unsigned int minutes;
	unsigned int gap;

	char players;

	bool mode1;
	bool mode2;
	bool mode3;
	bool friendlyFire;
	bool mode4;
	bool lateJoin;
	bool teamBalance;
};

typedef unsigned long (*ZGetGameFunction)();
typedef unsigned long (*ZGetGameClientFunction)();
typedef unsigned long (*ZGetGameInterfaceFunction)();

unsigned long MyChannelId();
unsigned long MyId();
unsigned long MyStageId();
unsigned long MyZCharacter();

void ConsoleOutput(char *message);
void ExitFreebase();
void HookedZPostChatRoomChat(char *chatRoom);
void SetAP(int nAP, unsigned long ulZChar);
void SetDirection(float *direction, unsigned long zcharacter);
void SetHP(int nHP, unsigned long ulZChar);
void SetPosition(float *pPosition);
void ZPostChannelChat(MUID *charId, MUID *channelId, char *message);
void ZPostChannelRequestJoin(MUID *charId, MUID *channelId);void ZPostCreateMyChar(MUID *charId, int index, char *name, int sex, int hair, int face, int costume);
void ZPostDash(float *position, float *direction, unsigned char selectType);
void ZPostFriendAdd(char *name);
void ZPostFriendRemove(char *name);
void ZPostGameKill(MUID *charId);
void ZPostPeerChat(char *message, int team);
void ZPostPeerChatIcon(bool show);
void ZPostReaction(float *position, int id);
void ZPostReload();
void ZPostRequestExpelClanMember(MUID *charId, char *name);
void ZPostRequestSpawn(unsigned long zero, unsigned long id, float *position, float *direction);
void ZPostRequestSpawnWorldItem(MUID *charId, int itemId, float *position);
void ZPostShot(float *position, float *direction, int weaponType, int selectType);
void ZPostShotMelee(float *position, int shot);
void ZPostShotSp(float *position, float *direction, int weaponType, int selectType);
void ZPostSkill(int skill, int selectType);
void ZPostStageCreate(MUID *charId, char *title, bool privateRoom, char *password);
void ZPostStageEnterBattle(MUID *charId, MUID *stageId);
void ZPostStageLeaveBattle(MUID *charId, MUID *stageId);
void ZPostStageStart(MUID *charId, MUID *stageId);
void ZPostWhere(char *name);

wchar_t *consoleText[120];
wchar_t info2[] = L"Freebase " VERSION_FILESTRL;
wchar_t *message2 = new wchar_t[1024 * 64];

ZGetGameFunction			ZGetGame			= (ZGetGameFunction)ZGETGAME;
ZGetGameClientFunction		ZGetGameClient		= (ZGetGameClientFunction)ZGETGAMECLIENT;
ZGetGameInterfaceFunction	ZGetGameInterface	= (ZGetGameInterfaceFunction)ZGETGAMEINTERFACE;