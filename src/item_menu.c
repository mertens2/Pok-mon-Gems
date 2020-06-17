#include "global.h"
#include "item_menu.h"
#include "battle.h"
#include "battle_controllers.h"
#include "battle_pyramid.h"
#include "frontier_util.h"
#include "battle_pyramid_bag.h"
#include "berry_tag_screen.h"
#include "bg.h"
#include "constants/items.h"
#include "constants/songs.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "field_specials.h"
#include "graphics.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "item.h"
#include "item_menu_icons.h"
#include "item_use.h"
#include "lilycove_lady.h"
#include "list_menu.h"
#include "link.h"
#include "mail.h"
#include "main.h"
#include "malloc.h"
#include "map_name_popup.h"
#include "menu.h"
#include "money.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "player_pc.h"
#include "pokemon.h"
#include "pokemon_summary_screen.h"
#include "scanline_effect.h"
#include "script.h"
#include "shop.h"
#include "sound.h"
#include "sprite.h"
#include "string.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text_window.h"
#include "menu_helpers.h"
#include "window.h"
#include "apprentice.h"
#include "battle_pike.h"
#include "constants/rgb.h"

enum MenuActions
{
    MENU_ACTION_USE,
    MENU_ACTION_TOSS,
    MENU_ACTION_REGISTER,
    MENU_ACTION_GIVE,
    MENU_ACTION_CANCEL,
    MENU_ACTION_USE_2,
    MENU_ACTION_CHECK,
    MENU_ACTION_WALK,
    MENU_ACTION_DESELECT,
    MENU_ACTION_CHECK_TAG,
    MENU_ACTION_CONFIRM,
    MENU_ACTION_SHOW,
    MENU_ACTION_GIVE_2,
    MENU_ACTION_CONFIRM_2,
    MENU_ACTION_SELECT_BUTTON,
    MENU_ACTION_L_BUTTON,
    MENU_ACTION_R_BUTTON,
    MENU_ACTION_BY_NAME,
    MENU_ACTION_BY_TYPE,
    MENU_ACTION_BY_AMOUNT,
    MENU_ACTION_COUNT,
};


void GoToBagMenu(u8 bagMenuType, u8 pocketId, void ( *postExitMenuMainCallback2)());
void CB2_Bag(void);
bool8 SetupBagMenu(void);
void BagMenu_InitBGs(void);
bool8 LoadBagMenu_Graphics(void);
void SetupBagMenu_Textboxes(void);
void AllocateBagItemListBuffers(void);
void LoadBagItemListBuffers(u8);
void BagMenu_PrintPocketNames(const u8*, const u8*);
void BagMenu_CopyPocketNameToWindow(u32);
void BagMenu_DrawPocketIndicatorSquare(u8, u8);
void bag_menu_add_pocket_scroll_arrow_indicators_maybe(void);
void bag_menu_add_list_scroll_arrow_indicators_maybe(void);
void BagMenu_PrepareTMHMMoveWindow(void);
bool8 IsWallysBag(void);
void Task_WallyTutorialBagMenu(u8);
void Task_BagMenu(u8);
void GetItemName(s8*, u16);
u16 ItemIdToBattleMoveId(u16);
u16 BagGetItemIdByPocketPosition(u8, u16);
void BagMenu_PrintDescription(int);
void BagMenu_PrintCursor(u8, u8);
void BagMenu_Print(u8, u8, const u8*, u8, u8, u8, u8, u8, u8);
bool8 ItemId_GetImportance(u16);
u16 BagGetQuantityByPocketPosition(u8, u16);
void sub_81AB89C(void);
void TaskCloseBagMenu_2(u8);
u8 AddItemMessageWindow(u8);
void bag_menu_RemoveBagItem_message_window(u8);
void set_callback3_to_bag(u8);
void PrintItemDepositAmount(u8, s16);
u8 BagMenu_AddWindow(u8);
u8 GetSwitchBagPocketDirection(void);
void SwitchBagPocket(u8, s16, u16);
bool8 sub_81AC2C0(void);
void BagMenu_SwapItems(u8);
void sub_81AC10C(u8);
void sub_81AC3C0(u8);
void sub_81AC498(u8);
void sub_81AC590(u8);
void PrintTMHMMoveData(u16);
void sub_81ACAF8(u8);
void sub_81ACB54(u8, u8, u8);
void Task_HandleInBattleItemMenuInput(u8);
void Task_HandleOutOfBattleItemMenuInput(u8);
bool8 sub_81ACDFC(s8);
void BagMenu_RemoveWindow(u8);
void BagMenu_PrintThereIsNoPokemon(u8);
void Task_ChooseHowManyToToss(u8);
void BagMenu_TossItems(u8);
void BagMenu_YesNo(u8, u8, const struct YesNoFuncTable*);
void Task_ActuallyToss(u8);
void ItemMenu_Cancel(u8);
void sub_81AD350(u8);
void BagMenu_PrintItemCantBeHeld(u8);
void bag_menu_AddMoney_window(void);
void sub_81AD680(u8);
void sub_81AD730(u8);
void sub_81AD6E4(u8);
void bag_menu_remove_money_window(void);
void bag_menu_RemoveBagItem_message_window(u8);
void sub_81AD794(u8);
void sub_81AD8C8(u8);
void sub_81AD9C0(u8);
void sub_81ADB14(u8);
void sub_81ADA7C(u8);
void sub_81ADC0C(u8);
void CB2_ApprenticeExitBagMenu(void);
void CB2_FavorLadyExitBagMenu(void);
void CB2_QuizLadyExitBagMenu(void);
void sub_81ABA6C(void);
static void SetPocketListPositions(void);
void sub_81ABAE0(void);
u8 sub_81AB1F0(u8);
void sub_81AC23C(u8);
void BagMenu_MoveCursorCallback(s32 a, bool8 b, struct ListMenu*);
void PrintItemQuantityPlusGFX(u8 rboxId, s32 item_index_in_pocket, u8 a);
void ItemMenu_UseOutOfBattle(u8 taskId);
void ItemMenu_Toss(u8 taskId);
static void ItemMenu_Register(u8 taskId);
void ItemMenu_Give(u8 taskId);
void ItemMenu_Cancel(u8 taskId);
void ItemMenu_UseInBattle(u8 taskId);
void ItemMenu_CheckTag(u8 taskId);
void Task_FadeAndCloseBagMenu(u8 taskId);
void unknown_ItemMenu_Show(u8 taskId);
void unknown_ItemMenu_Give2(u8 taskId);
void unknown_ItemMenu_Confirm2(u8 taskId);
void unknown_item_menu_type(u8 taskId);
void item_menu_type_2(u8 taskId);
void DisplaySellItemAskString(u8 taskId);
void DisplayDepositItemAskString(u8 taskId);
void item_menu_type_b(u8 taskId);
void BagMenu_ConfirmToss(u8 taskId);
void BagMenu_CancelToss(u8 taskId);
void BagMenu_ConfirmSell(u8 taskId);
void BagMenu_CancelSell(u8 taskId);
static void ItemMenu_RegisterSelect(u8 taskId);
static void ItemMenu_RegisterL(u8 taskId);
static void ItemMenu_RegisterR(u8 taskId);
static void ItemMenu_Deselect(u8 taskId);
static const u8 sMenuText_Select[] = _("Select");
static const u8 sMenuText_L[] = _("L Button");
static const u8 sMenuText_R[] = _("R Button");
//bag sort
static void Task_LoadBagSortOptions(u8 taskId);
static void ItemMenu_SortByName(u8 taskId);
static void ItemMenu_SortByType(u8 taskId);
static void ItemMenu_SortByAmount(u8 taskId);
static void SortBagItems(u8 taskId);
static void Task_SortFinish(u8 taskId);
static void SortItemsInBag(u8 pocket, u8 type);
static void MergeSort(struct ItemSlot* array, u32 low, u32 high, s8 (*comparator)(struct ItemSlot*, struct ItemSlot*));
static void Merge(struct ItemSlot* array, u32 low, u32 mid, u32 high, s8 (*comparator)(struct ItemSlot*, struct ItemSlot*));
static s8 CompareItemsAlphabetically(struct ItemSlot* itemSlot1, struct ItemSlot* itemSlot2);
static s8 CompareItemsByMost(struct ItemSlot* itemSlot1, struct ItemSlot* itemSlot2);
static s8 CompareItemsByType(struct ItemSlot* itemSlot1, struct ItemSlot* itemSlot2);
// .rodata

static const struct BgTemplate sBgTemplates_ItemMenu[3] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
    {
        .bg = 2,
        .charBaseIndex = 3,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0,
    },
};

static const struct ListMenuTemplate sItemListMenu =
{
    .items = NULL,
    .moveCursorFunc = BagMenu_MoveCursorCallback,
    .itemPrintFunc = PrintItemQuantityPlusGFX,
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 1,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = 7,
    .cursorKind = 0
};
static const u8 sMenuText_ByName[] = _("Name");
static const u8 sMenuText_ByType[] = _("Type");
static const u8 sMenuText_ByAmount[] = _("Amount");
const struct MenuAction sItemMenuActions[] = {
    [MENU_ACTION_USE]           = {gMenuText_Use, ItemMenu_UseOutOfBattle},
    [MENU_ACTION_TOSS]          = {gMenuText_Toss, ItemMenu_Toss},
    [MENU_ACTION_REGISTER]      = {gMenuText_Register, ItemMenu_Register},
    [MENU_ACTION_GIVE]          = {gMenuText_Give, ItemMenu_Give},
    [MENU_ACTION_CANCEL]        = {gText_Cancel2, ItemMenu_Cancel},
    [MENU_ACTION_USE_2]         = {gMenuText_Use, ItemMenu_UseInBattle},
    [MENU_ACTION_CHECK]         = {gMenuText_Check, ItemMenu_UseOutOfBattle},
    [MENU_ACTION_WALK]          = {gMenuText_Walk, ItemMenu_UseOutOfBattle},
    [MENU_ACTION_DESELECT]      = {gMenuText_Deselect, ItemMenu_Deselect},
    [MENU_ACTION_CHECK_TAG]     = {gMenuText_CheckTag, ItemMenu_CheckTag},
    [MENU_ACTION_CONFIRM]       = {gMenuText_Confirm, Task_FadeAndCloseBagMenu},
    [MENU_ACTION_SHOW]          = {gMenuText_Show, unknown_ItemMenu_Show},
    [MENU_ACTION_GIVE_2]        = {gMenuText_Give2, unknown_ItemMenu_Give2},
    [MENU_ACTION_CONFIRM_2]     = {gMenuText_Confirm, unknown_ItemMenu_Confirm2},
    [MENU_ACTION_SELECT_BUTTON] = {sMenuText_Select, ItemMenu_RegisterSelect},
    [MENU_ACTION_L_BUTTON]      = {sMenuText_L, ItemMenu_RegisterL},
    [MENU_ACTION_R_BUTTON]      = {sMenuText_R, ItemMenu_RegisterR},
    [MENU_ACTION_BY_NAME]       = {sMenuText_ByName, ItemMenu_SortByName},
    [MENU_ACTION_BY_TYPE]       = {sMenuText_ByType, ItemMenu_SortByType},
    [MENU_ACTION_BY_AMOUNT]     = {sMenuText_ByAmount, ItemMenu_SortByAmount},
    [MENU_ACTION_COUNT]         = {gText_EmptyString2, NULL}
};

static const u8 sItemPocketMenuActions[] = {MENU_ACTION_USE, MENU_ACTION_GIVE, MENU_ACTION_TOSS, MENU_ACTION_CANCEL};
static const u8 sKeyItemMenuActions[] = {MENU_ACTION_USE, MENU_ACTION_REGISTER, MENU_ACTION_COUNT, MENU_ACTION_CANCEL};
static const u8 sPokeBallMenuActions[] = {MENU_ACTION_GIVE, MENU_ACTION_COUNT, MENU_ACTION_TOSS, MENU_ACTION_CANCEL};
static const u8 sTmHmMenuActions[] = {MENU_ACTION_USE, MENU_ACTION_GIVE, MENU_ACTION_COUNT, MENU_ACTION_CANCEL};
static const u8 sBerriesMenuActions[] = {MENU_ACTION_CHECK_TAG, MENU_ACTION_COUNT, MENU_ACTION_USE, MENU_ACTION_GIVE, MENU_ACTION_TOSS, MENU_ACTION_CANCEL};
static const u8 sInBattleItemMenuActions[] = {MENU_ACTION_USE_2, MENU_ACTION_CANCEL};
static const u8 gUnknown_08614044[] = {MENU_ACTION_GIVE, MENU_ACTION_CANCEL};
static const u8 sInBattleNullUsageMenuActions = MENU_ACTION_CANCEL;
static const u8 gUnknown_08614047[] = {MENU_ACTION_CONFIRM, MENU_ACTION_CHECK_TAG, MENU_ACTION_COUNT, MENU_ACTION_CANCEL};
static const u8 gUnknown_0861404B[] = {MENU_ACTION_SHOW, MENU_ACTION_CANCEL};
static const u8 gUnknown_0861404D[] = {MENU_ACTION_GIVE_2, MENU_ACTION_CANCEL};
static const u8 sInBattleBerryActions[] = {MENU_ACTION_CONFIRM_2, MENU_ACTION_CANCEL};
static const u8 sRegisterMenuActions[] = {MENU_ACTION_SELECT_BUTTON, MENU_ACTION_L_BUTTON, MENU_ACTION_COUNT, MENU_ACTION_R_BUTTON};

const TaskFunc sBagMenuTasks[] = {
    unknown_item_menu_type,
    unknown_item_menu_type,
    item_menu_type_2,
    DisplaySellItemAskString,
    Task_FadeAndCloseBagMenu,
    unknown_item_menu_type,
    DisplayDepositItemAskString,
    unknown_item_menu_type,
    unknown_item_menu_type,
    unknown_item_menu_type,
    NULL,
    item_menu_type_b,
};

const struct YesNoFuncTable sYesNoTossFunctions = {BagMenu_ConfirmToss, BagMenu_CancelToss};

const struct YesNoFuncTable sYesNoSellItemFunctions = {BagMenu_ConfirmSell, BagMenu_CancelSell};

const struct ScrollArrowsTemplate gBagScrollArrowsTemplate = {SCROLL_ARROW_LEFT, 0x1C, 16, SCROLL_ARROW_RIGHT, 100, 16, -1, -1, 0x6F, 0x6F, 0};

static const u8 sSelectButtonGfx[] = INCBIN_U8("graphics/interface/select_button.4bpp");
static const u8 sLButtonGfx[] = INCBIN_U8("graphics/interface/L_button.4bpp");
static const u8 sRButtonGfx[] = INCBIN_U8("graphics/interface/R_button.4bpp");

static const u8 sFontColorTable[][3] = {
// bgColor, textColor, shadowColor
    {0, 1, 3},
    {0, 1, 4},
    {0, 3, 6},
    {2, 1, 3},
    {0, 14, 10}
};

const struct WindowTemplate gUnknown_08614174[] =
{
    { // Item names
        .bg = 0,
        .tilemapLeft = 14,
        .tilemapTop = 2,
        .width = 15,
        .height = 16,
        .paletteNum = 1,
        .baseBlock = 0x27,
    },
    { // Description
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 13,
        .width = 14,
        .height = 6,
        .paletteNum = 1,
        .baseBlock = 0x117,
    },
    { // Pocket name
        .bg = 0,
        .tilemapLeft = 4,
        .tilemapTop = 1,
        .width = 8,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 0x1A1,
    },
    { // TM/HM info icons
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 13,
        .width = 5,
        .height = 6,
        .paletteNum = 12,
        .baseBlock = 0x16B,
    },
    {// TM/HM info
        .bg = 0,
        .tilemapLeft = 7,
        .tilemapTop = 13,
        .width = 4,
        .height = 6,
        .paletteNum = 12,
        .baseBlock = 0x189,
    },
    { // Field message box
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x1B1,
    },
    DUMMY_WIN_TEMPLATE,
};

const struct WindowTemplate gUnknown_086141AC[] =
{
    {
        .bg = 1,
        .tilemapLeft = 22,
        .tilemapTop = 17,
        .width = 7,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x21D,
    },
    {
        .bg = 1,
        .tilemapLeft = 22,
        .tilemapTop = 15,
        .width = 7,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x21D,
    },
    {
        .bg = 1,
        .tilemapLeft = 15,
        .tilemapTop = 15,
        .width = 14,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x21D,
    },
    {
        .bg = 1,
        .tilemapLeft = 15,
        .tilemapTop = 13,
        .width = 14,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 0x21D,
    },
    {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x1B1,
    },
    {
        .bg = 1,
        .tilemapLeft = 24,
        .tilemapTop = 15,
        .width = 5,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x21D,
    },
    {
        .bg = 1,
        .tilemapLeft = 21,
        .tilemapTop = 9,
        .width = 5,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x21D,
    },
    {
        .bg = 1,
        .tilemapLeft = 24,
        .tilemapTop = 17,
        .width = 5,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x21D,
    },
    {
        .bg = 1,
        .tilemapLeft = 18,
        .tilemapTop = 11,
        .width = 10,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x245,
    },
    {
        .bg = 1,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 10,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x231,
    },
};

// .text

struct ListBuffer1 {
    struct ListMenuItem subBuffers[65];
};

struct ListBuffer2 {
    s8 name[65][24];
};

struct TempWallyStruct {
    struct ItemSlot bagPocket_Items[BAG_ITEMS_COUNT];
    struct ItemSlot bagPocket_PokeBalls[BAG_POKEBALLS_COUNT];
    u16 cursorPosition[POCKETS_COUNT];
    u16 scrollPosition[POCKETS_COUNT];
    u8 filler[0x2];
    u16 pocket;
};

EWRAM_DATA struct BagMenuStruct *gBagMenu = 0;
EWRAM_DATA struct BagStruct gBagPositionStruct = {0};
static EWRAM_DATA struct ListBuffer1 *sListBuffer1 = 0;
static EWRAM_DATA struct ListBuffer2 *sListBuffer2 = 0;
EWRAM_DATA u16 gSpecialVar_ItemId = 0;
static EWRAM_DATA struct TempWallyStruct *sTempWallyBag = 0;
static EWRAM_DATA bool8 sRegisterSubMenu = FALSE;

extern u8 *const gPocketNamesStringsTable[];
extern u8* gReturnToXStringsTable[];
extern const u8 EventScript_SelectWithoutRegisteredItem[];
extern const u16 gUnknown_0860F074[];

void ResetBagScrollPositions(void)
{
    gBagPositionStruct.pocket = ITEMS_POCKET;
    memset(gBagPositionStruct.cursorPosition, 0, 10);
    memset(gBagPositionStruct.scrollPosition, 0, 10);
}

void CB2_BagMenuFromStartMenu(void)
{
    GoToBagMenu(RETURN_LOCATION_FIELD, POCKETS_COUNT, CB2_ReturnToFieldWithOpenMenu);
}


void sub_81AABB0(void)
{
    if (!InBattlePyramid())
        GoToBagMenu(RETURN_LOCATION_BATTLE, POCKETS_COUNT, CB2_SetUpReshowBattleScreenAfterMenu2);
    else
        GoToBattlePyramidBagMenu(1, CB2_SetUpReshowBattleScreenAfterMenu2);
}

void CB2_ChooseBerry(void)
{
    GoToBagMenu(RETURN_LOCATION_FIELD_2, BERRIES_POCKET, CB2_ReturnToFieldContinueScript);
}

void ChooseBerrySetCallback(void (*callback)(void))
{
    GoToBagMenu(RETURN_LOCATION_FIELD_3, BERRIES_POCKET, callback);
}

void CB2_GoToSellMenu(void)
{
    GoToBagMenu(RETURN_LOCATION_SHOP, POCKETS_COUNT, CB2_ExitSellMenu);
}

void sub_81AAC14(void)
{
    GoToBagMenu(RETURN_LOCATION_PC, POCKETS_COUNT, sub_816B31C);
}

void ApprenticeOpenBagMenu(void)
{
    GoToBagMenu(RETURN_LOCATION_FIELD_6, POCKETS_COUNT, CB2_ApprenticeExitBagMenu);
    gSpecialVar_0x8005 = ITEM_NONE;
    gSpecialVar_Result = FALSE;
}

void FavorLadyOpenBagMenu(void)
{
    GoToBagMenu(RETURN_LOCATION_FIELD_4, POCKETS_COUNT, CB2_FavorLadyExitBagMenu);
    gSpecialVar_Result = FALSE;
}

void QuizLadyOpenBagMenu(void)
{
    GoToBagMenu(RETURN_LOCATION_FIELD_5, POCKETS_COUNT, CB2_QuizLadyExitBagMenu);
    gSpecialVar_Result = FALSE;
}

void GoToBagMenu(u8 bagMenuType, u8 pocketId, void ( *postExitMenuMainCallback2)())
{
    u8 temp;
    gBagMenu = AllocZeroed(sizeof(struct BagMenuStruct));
    if (gBagMenu == 0)
    {
        SetMainCallback2(postExitMenuMainCallback2);
    }
    else
    {
        if (bagMenuType != RETURN_LOCATION_UNCHANGED)
            gBagPositionStruct.location = bagMenuType;
        if (postExitMenuMainCallback2)
            gBagPositionStruct.bagCallback = postExitMenuMainCallback2;
        if (pocketId < POCKETS_COUNT)
            gBagPositionStruct.pocket = pocketId;
        temp = gBagPositionStruct.location - (POCKETS_COUNT - 1);
        if (temp <= 1)
            gBagMenu->unk81B = 1;
        gBagMenu->mainCallback2 = 0;
        gBagMenu->unk81A = 0xFF;
        gBagMenu->unk81E = -1;
        gBagMenu->unk81F = -1;
        memset(gBagMenu->spriteId, 0xFF, sizeof(gBagMenu->spriteId));
        memset(gBagMenu->windowPointers, 0xFF, 10);
        SetMainCallback2(CB2_Bag);
    }
}

void c2_bag_3(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    do_scheduled_bg_tilemap_copies_to_vram();
    UpdatePaletteFade();
}

void vblank_cb_bag_menu(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_Bag(void)
{
    while(sub_81221EC() != TRUE && SetupBagMenu() != TRUE && sub_81221AC() != TRUE) {};
}

bool8 SetupBagMenu(void)
{
    u32 index;
    u8 taskId;

    switch (gMain.state)
    {
    case 0:
        SetVBlankHBlankCallbacksToNull();
        clear_scheduled_bg_copies_to_vram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        gMain.state++;
        break;
    case 2:
        FreeAllSpritePalettes();
        gMain.state++;
        break;
    case 3:
        ResetPaletteFade();
        gPaletteFade.bufferTransferDisabled = TRUE;
        gMain.state++;
        break;
    case 4:
        ResetSpriteData();
        gMain.state++;
        break;
    case 5:
        gMain.state++;
        break;
    case 6:
        if (sub_81221AC() == FALSE)
            ResetTasks();
        gMain.state++;
        break;
    case 7:
        BagMenu_InitBGs();
        gBagMenu->unk834 = 0;
        gMain.state++;
        break;
    case 8:
        if (!LoadBagMenu_Graphics())
            break;
        gMain.state++;
        break;
    case 9:
        SetupBagMenu_Textboxes();
        gMain.state++;
        break;
    case 10:
        sub_81ABA6C();
        SetPocketListPositions();
        sub_81ABAE0();
        gMain.state++;
        break;
    case 11:
        AllocateBagItemListBuffers();
        gMain.state++;
        break;
    case 12:
        LoadBagItemListBuffers(gBagPositionStruct.pocket);
        gMain.state++;
        break;
    case 13:
        BagMenu_PrintPocketNames(gPocketNamesStringsTable[gBagPositionStruct.pocket], 0);
        BagMenu_CopyPocketNameToWindow(0);
        BagMenu_DrawPocketIndicatorSquare(gBagPositionStruct.pocket, 1);
        gMain.state++;
        break;
    case 14:
        taskId = sub_81AB1F0(gBagPositionStruct.location);
        gTasks[taskId].data[0] = ListMenuInit(&gMultiuseListMenuTemplate, gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket], gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]);
        gTasks[taskId].data[3] = 0;
        gTasks[taskId].data[8] = 0;
        gMain.state++;
        break;
    case 15:
        AddBagVisualSprite(gBagPositionStruct.pocket);
        gMain.state++;
        break;
    case 16:
        sub_80D4FAC();
        gMain.state++;
        break;
    case 17:
        bag_menu_add_pocket_scroll_arrow_indicators_maybe();
        bag_menu_add_list_scroll_arrow_indicators_maybe();
        gMain.state++;
        break;
    case 18:
        BagMenu_PrepareTMHMMoveWindow();
        gMain.state++;
        break;
    case 19:
        BlendPalettes(-1, 16, 0);
        gMain.state++;
        break;
    case 20:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        gPaletteFade.bufferTransferDisabled = FALSE;
        gMain.state++;
        break;
    default:
        SetVBlankCallback(vblank_cb_bag_menu);
        SetMainCallback2(c2_bag_3);
        return TRUE;
    }
    return FALSE;
}

void BagMenu_InitBGs(void)
{
    ResetVramOamAndBgCntRegs();
    memset(gBagMenu->tilemapBuffer, 0, 0x800);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBgTemplates_ItemMenu, 3);
    SetBgTilemapBuffer(2, gBagMenu->tilemapBuffer);
    ResetAllBgsCoordinates();
    schedule_bg_copy_tilemap_to_vram(2);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
}

bool8 LoadBagMenu_Graphics(void)
{
    switch (gBagMenu->unk834)
    {
        case 0:
            reset_temp_tile_data_buffers();
            decompress_and_copy_tile_data_to_vram(2, gBagScreen_Gfx, 0, 0, 0);
            gBagMenu->unk834++;
            break;
        case 1:
            if (free_temp_tile_data_buffers_if_possible() != TRUE)
            {
                LZDecompressWram(gBagScreen_GfxTileMap, gBagMenu->tilemapBuffer);
                gBagMenu->unk834++;
            }
            break;
        case 2:
            if (!IsWallysBag() && gSaveBlock2Ptr->playerGender != MALE)
                LoadCompressedPalette(gBagScreenFemale_Pal, 0, 0x40);
            else
                LoadCompressedPalette(gBagScreenMale_Pal, 0, 0x40);
            gBagMenu->unk834++;
            break;
        case 3:
            if (IsWallysBag() == TRUE || gSaveBlock2Ptr->playerGender == MALE)
                LoadCompressedSpriteSheet(&gBagMaleSpriteSheet);
            else
                LoadCompressedSpriteSheet(&gBagFemaleSpriteSheet);
            gBagMenu->unk834++;
            break;
        case 4:
            LoadCompressedSpritePalette(&gBagPaletteTable);
            gBagMenu->unk834++;
            break;
        default:
            LoadListMenuArrowsGfx();
            gBagMenu->unk834 = 0;
            return TRUE;
    }
    return FALSE;
}

u8 sub_81AB1F0(u8 a)
{
    u8 taskId;
    if (a == 10)
        taskId = CreateTask(Task_WallyTutorialBagMenu, 0);
    else
        taskId = CreateTask(Task_BagMenu, 0);
    return taskId;
}

void AllocateBagItemListBuffers(void)
{
    sListBuffer1 = Alloc(sizeof(struct ListBuffer1));
    sListBuffer2 = Alloc(sizeof(struct ListBuffer2));
}

void LoadBagItemListBuffers(u8 pocketId)
{
    u16 i;
    struct BagPocket *pocket = &gBagPockets[pocketId];
    struct ListMenuItem *subBuffer;

    if (!gBagMenu->hideCloseBagText)
    {
        for (i = 0; i < gBagMenu->numItemStacks[pocketId] - 1; i++)
        {
            GetItemName(sListBuffer2->name[i], pocket->itemSlots[i].itemId);
            subBuffer = sListBuffer1->subBuffers;
            subBuffer[i].name = sListBuffer2->name[i];
            subBuffer[i].id = i;
        }
        StringCopy(sListBuffer2->name[i], gText_CloseBag);
        subBuffer = sListBuffer1->subBuffers;
        subBuffer[i].name = sListBuffer2->name[i];
        subBuffer[i].id = -2;
    }
    else
    {
        for (i = 0; i < gBagMenu->numItemStacks[pocketId]; i++)
        {
            GetItemName(sListBuffer2->name[i], pocket->itemSlots[i].itemId);
            subBuffer = sListBuffer1->subBuffers;
            subBuffer[i].name = sListBuffer2->name[i];
            subBuffer[i].id = i;
        }
    }
    gMultiuseListMenuTemplate = sItemListMenu;
    gMultiuseListMenuTemplate.totalItems = gBagMenu->numItemStacks[pocketId];
    gMultiuseListMenuTemplate.items = sListBuffer1->subBuffers;
    gMultiuseListMenuTemplate.maxShowed = gBagMenu->numShownItems[pocketId];
}

void GetItemName(s8 *dest, u16 itemId)
{
    switch (gBagPositionStruct.pocket)
    {
        case TMHM_POCKET:
            StringCopy(gStringVar2, gMoveNames[ItemIdToBattleMoveId(itemId)]);
            if (itemId >= ITEM_HM01)
            {
                ConvertIntToDecimalStringN(gStringVar1, itemId - ITEM_HM01 + 1, STR_CONV_MODE_LEADING_ZEROS, 1);
                StringExpandPlaceholders(dest, gText_ClearTo11Var1Clear5Var2);
            }
            else
            {
                ConvertIntToDecimalStringN(gStringVar1, itemId - ITEM_TM01 + 1, STR_CONV_MODE_LEADING_ZEROS, 2);
                StringExpandPlaceholders(dest, gText_NumberVar1Clear7Var2);
            }
            break;
        case BERRIES_POCKET:
            ConvertIntToDecimalStringN(gStringVar1, itemId - ITEM_CHERI_BERRY + 1, STR_CONV_MODE_LEADING_ZEROS, 2);
            CopyItemName(itemId, gStringVar2);
            StringExpandPlaceholders(dest, gText_NumberVar1Clear7Var2);
            break;
        default:
            CopyItemName(itemId, dest);
            break;
    }
}

void BagMenu_MoveCursorCallback(s32 a, bool8 b, struct ListMenu *unused)
{
    if (b != 1)
    {
        PlaySE(SE_SELECT);
        ShakeBagVisual();
    }
    if (gBagMenu->unk81A == 0xFF)
    {
        RemoveBagItemIconSprite(1 ^ gBagMenu->unk81B_1);
        if (a != -2)
           AddBagItemIconSprite(BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, a), gBagMenu->unk81B_1);
        else
           AddBagItemIconSprite(-1, gBagMenu->unk81B_1);
        gBagMenu->unk81B_1 ^= 1;
        if (!gBagMenu->unk81B_3)
            BagMenu_PrintDescription(a);
    }
}

void PrintItemQuantityPlusGFX(u8 rboxId, s32 item_index_in_pocket, u8 a)
{
    u16 itemId;
    u16 itemQuantity;
    bool8 unique;
    int offset;
    if (item_index_in_pocket != -2)
    {
        if (gBagMenu->unk81A != 0xFF)
        {
            if (gBagMenu->unk81A == (u8)item_index_in_pocket)
                BagMenu_PrintCursor(a, 2);
            else
                BagMenu_PrintCursor(a, -1);
        }
        itemId = BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, item_index_in_pocket);
        itemQuantity = BagGetQuantityByPocketPosition(gBagPositionStruct.pocket + 1, item_index_in_pocket);
        if (itemId >= ITEM_HM01 && itemId <= ITEM_HM08)
            BlitBitmapToWindow(rboxId, gBagMenuHMIcon_Gfx, 8, a - 1, 16, 16);
        if (gBagPositionStruct.pocket == BERRIES_POCKET)
        {
            ConvertIntToDecimalStringN(gStringVar1, itemQuantity, STR_CONV_MODE_RIGHT_ALIGN, 3);
            StringExpandPlaceholders(gStringVar4, gText_xVar1);
            offset = GetStringRightAlignXOffset(7, gStringVar4, 0x77);
            BagMenu_Print(rboxId, 7, gStringVar4, offset, a, 0, 0, -1, 0);
        }
        else if (gBagPositionStruct.pocket != KEYITEMS_POCKET && (unique = ItemId_GetImportance(itemId)) == FALSE)
        {
            ConvertIntToDecimalStringN(gStringVar1, itemQuantity, STR_CONV_MODE_RIGHT_ALIGN, 2);
            StringExpandPlaceholders(gStringVar4, gText_xVar1);
            offset = GetStringRightAlignXOffset(7, gStringVar4, 0x77);
            BagMenu_Print(rboxId, 7, gStringVar4, offset, a, unique, unique, -1, unique);
        }
        else
        {
            if (gSaveBlock1Ptr->registeredItemSelect && gSaveBlock1Ptr->registeredItemSelect == itemId)
                BlitBitmapToWindow(rboxId, sSelectButtonGfx, 0x60, a - 1, 0x18, 16);

            if (gSaveBlock1Ptr->registeredItemL && gSaveBlock1Ptr->registeredItemL == itemId)
                BlitBitmapToWindow(rboxId, sLButtonGfx, 0x60, a - 1, 0x18, 16);

            if (gSaveBlock1Ptr->registeredItemR && gSaveBlock1Ptr->registeredItemR == itemId)
                BlitBitmapToWindow(rboxId, sRButtonGfx, 0x60, a - 1, 0x18, 16);
        }
    }
}

void BagMenu_PrintDescription(int a)
{
    const u8 *str;
    if (a != -2)
    {
        str = ItemId_GetDescription(BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, a));
    }
    else
    {
        StringCopy(gStringVar1, gReturnToXStringsTable[gBagPositionStruct.location]);
        StringExpandPlaceholders(gStringVar4, gText_ReturnToVar1);
        str = gStringVar4;
    }
    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    BagMenu_Print(1, 1, str, 3, 1, 0, 0, 0, 0);
}

void BagMenu_PrintCursor_(u8 a, u8 b)
{
    BagMenu_PrintCursor(ListMenuGetYCoordForPrintingArrowCursor(a), b);
}

void BagMenu_PrintCursor(u8 a, u8 b)
{
    if (b == 0xFF)
        FillWindowPixelRect(0, PIXEL_FILL(0), 0, a, GetMenuCursorDimensionByFont(1, 0), GetMenuCursorDimensionByFont(1, 1));
    else
        BagMenu_Print(0, 1, gText_SelectorArrow2, 0, a, 0, 0, 0, b);

}

void bag_menu_add_pocket_scroll_arrow_indicators_maybe(void)
{
    if (gBagMenu->unk81E == 0xFF)
        gBagMenu->unk81E = AddScrollIndicatorArrowPairParameterized(SCROLL_ARROW_UP, 0xAC, 12, 0x94, gBagMenu->numItemStacks[gBagPositionStruct.pocket] - gBagMenu->numShownItems[gBagPositionStruct.pocket], 0x6E, 0x6E, &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket]);
}

void sub_81AB824(void)
{
    if (gBagMenu->unk81E != 0xFF)
    {
        RemoveScrollIndicatorArrowPair(gBagMenu->unk81E);
        gBagMenu->unk81E = 0xFF;
    }
    sub_81AB89C();
}

void bag_menu_add_list_scroll_arrow_indicators_maybe(void)
{
    if (gBagMenu->unk81B != 1 && gBagMenu->unk81F == 0xFF)
        gBagMenu->unk81F = AddScrollIndicatorArrowPair(&gBagScrollArrowsTemplate, &gBagPositionStruct.unk6);
}

void sub_81AB89C(void)
{
    if (gBagMenu->unk81F != 0xFF)
    {
        RemoveScrollIndicatorArrowPair(gBagMenu->unk81F);
        gBagMenu->unk81F = 0xFF;
    }
}

void FreeBagItemListBuffers(void)
{
    Free(sListBuffer2);
    Free(sListBuffer1);
    FreeAllWindowBuffers();
    Free(gBagMenu);
}

void Task_FadeAndCloseBagMenu(u8 taskId)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = TaskCloseBagMenu_2;
}

void TaskCloseBagMenu_2(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    if (!gPaletteFade.active)
    {
        DestroyListMenuTask(data[0], &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket], &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]);
        if (gBagMenu->mainCallback2 != 0)
            SetMainCallback2(gBagMenu->mainCallback2);
        else
            SetMainCallback2(gBagPositionStruct.bagCallback);
        sub_81AB824();
        ResetSpriteData();
        FreeAllSpritePalettes();
        FreeBagItemListBuffers();
        DestroyTask(taskId);
    }
}

void UpdatePocketItemList(u8 pocketId)
{
    u16 i;
    struct BagPocket *pocket = &gBagPockets[pocketId];
    switch (pocketId)
    {
        case TMHM_POCKET:
        case BERRIES_POCKET:
            SortBerriesOrTMHMs(pocket);
            break;
        default:
            CompactItemsInBagPocket(pocket);
            break;
    }
    gBagMenu->numItemStacks[pocketId] = 0;
    for (i = 0; i < pocket->capacity && pocket->itemSlots[i].itemId; i++)
        gBagMenu->numItemStacks[pocketId]++;

    if (!gBagMenu->hideCloseBagText)
        gBagMenu->numItemStacks[pocketId]++;

    if (gBagMenu->numItemStacks[pocketId] > 8)
        gBagMenu->numShownItems[pocketId] = 8;
    else
        gBagMenu->numShownItems[pocketId] = gBagMenu->numItemStacks[pocketId];
}

void sub_81ABA6C(void)
{
    u8 i;
    for (i = 0; i < POCKETS_COUNT; i++)
        UpdatePocketItemList(i);
}

void SetInitialScrollAndCursorPositions(u8 pocketId)
{
    sub_812225C(&gBagPositionStruct.scrollPosition[pocketId], &gBagPositionStruct.cursorPosition[pocketId], gBagMenu->numShownItems[pocketId], gBagMenu->numItemStacks[pocketId]);
}

static void SetPocketListPositions(void)
{
    u8 i;
    for (i = 0; i < POCKETS_COUNT; i++)
        SetInitialScrollAndCursorPositions(i);
}

void sub_81ABAE0(void)
{
    u8 i;
    for (i = 0; i < POCKETS_COUNT; i++)
        sub_8122298(&gBagPositionStruct.scrollPosition[i], &gBagPositionStruct.cursorPosition[i], gBagMenu->numShownItems[i], gBagMenu->numItemStacks[i], 8);
}

u8 GetItemListPosition(u8 pocketId)
{
    return gBagPositionStruct.scrollPosition[pocketId] + gBagPositionStruct.cursorPosition[pocketId];
}

void DisplayItemMessage(u8 taskId, u8 fontId, const u8 *str, void ( *callback)(u8 taskId))
{
    s16* data = gTasks[taskId].data;

    data[10] = AddItemMessageWindow(4);
    FillWindowPixelBuffer(data[10], PIXEL_FILL(1));
    DisplayMessageAndContinueTask(taskId, data[10], 10, 13, fontId, GetPlayerTextSpeedDelay(), str, callback);
    schedule_bg_copy_tilemap_to_vram(1);
}

void BagMenu_InitListsMenu(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];
    bag_menu_RemoveBagItem_message_window(4);
    DestroyListMenuTask(data[0], scrollPos, cursorPos);
    UpdatePocketItemList(gBagPositionStruct.pocket);
    SetInitialScrollAndCursorPositions(gBagPositionStruct.pocket);
    LoadBagItemListBuffers(gBagPositionStruct.pocket);
    data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *scrollPos, *cursorPos);
    schedule_bg_copy_tilemap_to_vram(0);
    set_callback3_to_bag(taskId);
}

void sub_81ABC3C(u8 a)
{
    PrintItemDepositAmount(BagMenu_AddWindow(a), 1);
}

void PrintItemDepositAmount(u8 windowId, s16 numDeposited)
{
    u8 numDigits = (gBagPositionStruct.pocket == BERRIES_POCKET) ? 3 : 2;
    ConvertIntToDecimalStringN(gStringVar1, numDeposited, STR_CONV_MODE_LEADING_ZEROS, numDigits);
    StringExpandPlaceholders(gStringVar4, gText_xVar1);
    AddTextPrinterParameterized(windowId, 1, gStringVar4, GetStringCenterAlignXOffset(1, gStringVar4, 0x28), 2, 0, 0);
}

void PrintItemSoldAmount(int windowId, int numSold, int moneyEarned)
{
    u8 numDigits = (gBagPositionStruct.pocket == BERRIES_POCKET) ? 3 : 2;
    ConvertIntToDecimalStringN(gStringVar1, numSold, STR_CONV_MODE_LEADING_ZEROS, numDigits);
    StringExpandPlaceholders(gStringVar4, gText_xVar1);
    AddTextPrinterParameterized(windowId, 1, gStringVar4, 0, 1, -1, 0);
    PrintMoneyAmount(windowId, 38, 1, moneyEarned, 0);
}

void Task_BagMenu(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];
    u16 select;
    if (sub_81221EC() != TRUE && !gPaletteFade.active)
    {
        switch (GetSwitchBagPocketDirection())
        {
            case 1:
                SwitchBagPocket(taskId, -1, 0);
                return;
            case 2:
                SwitchBagPocket(taskId, 1, 0);
                return;
        }
        if ((select = (gMain.newKeys & SELECT_BUTTON)))
        {
            if (sub_81AC2C0() == 1)
            {
                ListMenuGetScrollAndRow(data[0], scrollPos, cursorPos);
                if ((*scrollPos + *cursorPos) != gBagMenu->numItemStacks[gBagPositionStruct.pocket] - 1)
                {
                    PlaySE(SE_SELECT);
                    BagMenu_SwapItems(taskId);
                }
            }
            return;
        }
        else if (JOY_NEW(START_BUTTON))
        {
            PlaySE(SE_SELECT);
            sub_81AB824();
            BagMenu_PrintCursor_(data[0], 2);
            ListMenuGetScrollAndRow(data[0], scrollPos, cursorPos);
            gTasks[taskId].func = Task_LoadBagSortOptions;
            //gUnknown_08614054[0](taskId);
        }
        else
        {
            int listPosition = ListMenu_ProcessInput(data[0]);
            ListMenuGetScrollAndRow(data[0], scrollPos, cursorPos);
            switch (listPosition)
            {
                case LIST_NOTHING_CHOSEN:
                    break;
                case LIST_CANCEL:
                    if (gBagPositionStruct.location == 5)
                    {
                        PlaySE(SE_HAZURE);
                        break;
                    }
                    PlaySE(SE_SELECT);
                    gSpecialVar_ItemId = select;
                    gTasks[taskId].func = Task_FadeAndCloseBagMenu;
                    break;
                default: // A_BUTTON
                    PlaySE(SE_SELECT);
                    sub_81AB824();
                    BagMenu_PrintCursor_(data[0], 2);
                    data[1] = listPosition;
                    data[2] = BagGetQuantityByPocketPosition(gBagPositionStruct.pocket + 1, listPosition);
                    gSpecialVar_ItemId = BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, listPosition);
                    sBagMenuTasks[gBagPositionStruct.location](taskId);
                    break;
            }
        }
    }
}

void set_callback3_to_bag(u8 taskId)
{
    bag_menu_add_pocket_scroll_arrow_indicators_maybe();
    bag_menu_add_list_scroll_arrow_indicators_maybe();
    ClearWindowTilemap(3);
    ClearWindowTilemap(4);
    PutWindowTilemap(1);
    schedule_bg_copy_tilemap_to_vram(0);
    gTasks[taskId].func = Task_BagMenu;
}

u8 GetSwitchBagPocketDirection(void)
{
    u8 LRKeys;
    if (gBagMenu->unk81B != 0)
        return 0;
    LRKeys = GetLRKeysPressed();
    if ((gMain.newKeys & DPAD_LEFT) || LRKeys == MENU_L_PRESSED)
    {
        PlaySE(SE_SELECT);
        return 1;
    }
    if ((gMain.newKeys & DPAD_RIGHT) || LRKeys == MENU_R_PRESSED)
    {
        PlaySE(SE_SELECT);
        return 2;
    }
    return 0;
}

void ChangeBagPocketId(u8 *bagPocketId, s8 deltaBagPocketId)
{
    if (deltaBagPocketId == 1 && *bagPocketId == POCKETS_COUNT - 1)
        *bagPocketId = 0;
    else if (deltaBagPocketId == -1 && *bagPocketId == 0)
        *bagPocketId = POCKETS_COUNT - 1;
    else
        *bagPocketId += deltaBagPocketId;
}

void SwitchBagPocket(u8 taskId, s16 deltaBagPocketId, u16 a3)
{
    s16* data = gTasks[taskId].data;
    u8 pocketId;

    data[13] = 0;
    data[12] = 0;
    data[11] = deltaBagPocketId;
    if (a3 == 0)
    {
        ClearWindowTilemap(0);
        ClearWindowTilemap(1);
        DestroyListMenuTask(data[0], &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket], &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]);
        schedule_bg_copy_tilemap_to_vram(0);
        gSprites[gBagMenu->spriteId[2 + (gBagMenu->unk81B_1 ^ 1)]].invisible = TRUE;
        sub_81AB824();
    }
    pocketId = gBagPositionStruct.pocket;
    ChangeBagPocketId(&pocketId, deltaBagPocketId);
    if (deltaBagPocketId == 1)
    {
        BagMenu_PrintPocketNames(gPocketNamesStringsTable[gBagPositionStruct.pocket], gPocketNamesStringsTable[pocketId]);
        BagMenu_CopyPocketNameToWindow(0);
    }
    else
    {
        BagMenu_PrintPocketNames(gPocketNamesStringsTable[pocketId], gPocketNamesStringsTable[gBagPositionStruct.pocket]);
        BagMenu_CopyPocketNameToWindow(8);
    }
    BagMenu_DrawPocketIndicatorSquare(gBagPositionStruct.pocket, 0);
    BagMenu_DrawPocketIndicatorSquare(pocketId, 1);
    FillBgTilemapBufferRect_Palette0(2, 11, 14, 2, 15, 16);
    schedule_bg_copy_tilemap_to_vram(2);
    SetBagVisualPocketId(pocketId, 1);
    RemoveBagSprite(1);
    AddSwitchPocketRotatingBallSprite(deltaBagPocketId);
    SetTaskFuncWithFollowupFunc(taskId, sub_81AC10C, gTasks[taskId].func);
}

void sub_81AC10C(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (!sub_81221AC() && !IsWallysBag())
    {
        switch (GetSwitchBagPocketDirection())
        {
            case 1:
                ChangeBagPocketId(&gBagPositionStruct.pocket, data[11]);
                SwitchTaskToFollowupFunc(taskId);
                SwitchBagPocket(taskId, -1, 1);
                return;
            case 2:
                ChangeBagPocketId(&gBagPositionStruct.pocket, data[11]);
                SwitchTaskToFollowupFunc(taskId);
                SwitchBagPocket(taskId, 1, 1);
                return;
        }
    }
    switch (data[13])
    {
        case 0:
            sub_81AC23C(data[12]);
            if (!(++data[12] & 1))
            {
                if (data[11] == 1)
                    BagMenu_CopyPocketNameToWindow((u8)(data[12] >> 1));
                else
                    BagMenu_CopyPocketNameToWindow((u8)(8 - (data[12] >> 1)));
            }
            if (data[12] == 16)
                data[13]++;
            break;
        case 1:
            ChangeBagPocketId(&gBagPositionStruct.pocket, data[11]);
            LoadBagItemListBuffers(gBagPositionStruct.pocket);
            data[0] = ListMenuInit(&gMultiuseListMenuTemplate, gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket], gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]);
            PutWindowTilemap(1);
            PutWindowTilemap(2);
            schedule_bg_copy_tilemap_to_vram(0);
            bag_menu_add_pocket_scroll_arrow_indicators_maybe();
            bag_menu_add_list_scroll_arrow_indicators_maybe();
            SwitchTaskToFollowupFunc(taskId);
    }
}

void sub_81AC23C(u8 a)
{
    FillBgTilemapBufferRect_Palette0(2, 17, 14, a + 2, 15, 1);
    schedule_bg_copy_tilemap_to_vram(2);
}

void BagMenu_DrawPocketIndicatorSquare(u8 x, u8 is_current_bag)
{
    if (is_current_bag == 0)
        FillBgTilemapBufferRect_Palette0(2, 0x1017, x + 5, 3, 1, 1);
    else
        FillBgTilemapBufferRect_Palette0(2, 0x102B, x + 5, 3, 1, 1);
    schedule_bg_copy_tilemap_to_vram(2);
}

bool8 sub_81AC2C0(void)
{
    if (gBagPositionStruct.location <= 1)
    {
        u8 temp = gBagPositionStruct.pocket - 2;
        if (temp > 1)
            return TRUE;
    }
    return FALSE;
}

void BagMenu_SwapItems(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    ListMenuSetUnkIndicatorsStructField(data[0], 16, 1);
    data[1] = gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket] + gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];
    gBagMenu->unk81A = data[1];
    CopyItemName(BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, data[1]), gStringVar1);
    StringExpandPlaceholders(gStringVar4, gText_MoveVar1Where);
    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
    sub_80D4FEC(data[1]);
    sub_81AB89C();
    BagMenu_PrintCursor_(data[0], 2);
    gTasks[taskId].func = sub_81AC3C0;
}

void sub_81AC3C0(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    int input;

    if (sub_81221EC() != TRUE)
    {
        if (gMain.newKeys & SELECT_BUTTON)
        {
            PlaySE(SE_SELECT);
            ListMenuGetScrollAndRow(data[0], &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket], &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]);
            sub_81AC498(taskId);
        }
        else
        {
            input = ListMenu_ProcessInput(data[0]);
            ListMenuGetScrollAndRow(data[0], &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket], &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]);
            sub_80D4FC8(0);
            sub_80D4FEC(gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]);
            switch (input)
            {
                case LIST_NOTHING_CHOSEN:
                    break;
                case LIST_CANCEL:
                    PlaySE(SE_SELECT);
                    if (gMain.newKeys & A_BUTTON)
                        sub_81AC498(taskId);
                    else
                        sub_81AC590(taskId);
                    break;
                default:
                    PlaySE(SE_SELECT);
                    sub_81AC498(taskId);
            }
        }
    }
}

void sub_81AC498(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];
    u16 realPos = (*scrollPos + *cursorPos);

    if (data[1] == realPos || data[1] == (realPos - 1))
        sub_81AC590(taskId);
    else
    {
        MoveItemSlotInList(gBagPockets[gBagPositionStruct.pocket].itemSlots, data[1], realPos);
        gBagMenu->unk81A = -1;
        DestroyListMenuTask(data[0], scrollPos, cursorPos);
        if (data[1] < realPos)
            gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]--;
        LoadBagItemListBuffers(gBagPositionStruct.pocket);
        data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *scrollPos, *cursorPos);
        sub_80D4FC8(1);
        bag_menu_add_list_scroll_arrow_indicators_maybe();
        gTasks[taskId].func = Task_BagMenu;
    }
}

void sub_81AC590(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];

    gBagMenu->unk81A = -1;
    DestroyListMenuTask(data[0], scrollPos, cursorPos);
    if (data[1] < (*scrollPos + *cursorPos))
        gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket]--;
    LoadBagItemListBuffers(gBagPositionStruct.pocket);
    data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *scrollPos, *cursorPos);
    sub_80D4FC8(1);
    bag_menu_add_list_scroll_arrow_indicators_maybe();
    gTasks[taskId].func = Task_BagMenu;
}

void SetUpBagMenuActionItems(u8 unused)
{
    switch (gBagPositionStruct.location - 1)
    {
        case 0:
        case 9:
            if (ItemId_GetBattleUsage(gSpecialVar_ItemId))
            {
                gBagMenu->unk820 = sInBattleItemMenuActions;
                gBagMenu->unk828 = NELEMS(sInBattleItemMenuActions);
            }
            else
            {
                gBagMenu->unk820 = &sInBattleNullUsageMenuActions;
                gBagMenu->unk828 = 1;
            }
            break;
        case 4:
            gBagMenu->unk820 = gUnknown_08614047;
            gBagMenu->unk828 = 4;
            break;
        case 8:
            if (!ItemId_GetImportance(gSpecialVar_ItemId) && gSpecialVar_ItemId != ITEM_ENIGMA_BERRY)
            {
                gBagMenu->unk820 = gUnknown_0861404B;
                gBagMenu->unk828 = 2;
            }
            else
            {
                gBagMenu->unk820 = &sInBattleNullUsageMenuActions;
                gBagMenu->unk828 = 1;
            }
            break;
        case 6:
            if (!ItemId_GetImportance(gSpecialVar_ItemId) && gSpecialVar_ItemId != ITEM_ENIGMA_BERRY)
            {
                gBagMenu->unk820 = gUnknown_0861404D;
                gBagMenu->unk828 = NELEMS(gUnknown_0861404D);
            }
            else
            {
                gBagMenu->unk820 = &sInBattleNullUsageMenuActions;
                gBagMenu->unk828 = 1;
            }
            break;
        case 7:
            if (!ItemId_GetImportance(gSpecialVar_ItemId) && gSpecialVar_ItemId != ITEM_ENIGMA_BERRY)
            {
                gBagMenu->unk820 = sInBattleBerryActions;
                gBagMenu->unk828 = NELEMS(sInBattleBerryActions);
            }
            else
            {
                gBagMenu->unk820 = &sInBattleNullUsageMenuActions;
                gBagMenu->unk828 = 1;
            }
            break;
        case 1:
        case 2:
        case 3:
        case 5:
        default:
            if (sub_81221AC() == TRUE || InUnionRoom() == TRUE)
            {
                if (gBagPositionStruct.pocket == KEYITEMS_POCKET || !sub_8122148(gSpecialVar_ItemId))
                {
                    gBagMenu->unk820 = &sInBattleNullUsageMenuActions;
                    gBagMenu->unk828 = 1;
                }
                else
                {
                    gBagMenu->unk820 = gUnknown_08614044;
                    gBagMenu->unk828 = NELEMS(gUnknown_08614044);
                }
            }
            else
            {
                switch (gBagPositionStruct.pocket)
                {
                    case ITEMS_POCKET:
                        gBagMenu->unk820 = &gBagMenu->unk824;
                        gBagMenu->unk828 = NELEMS(sItemPocketMenuActions);
                        memcpy(&gBagMenu->unk824, &sItemPocketMenuActions, NELEMS(sItemPocketMenuActions));
                        if (ItemIsMail(gSpecialVar_ItemId) == TRUE)
                            gBagMenu->unk824 = MENU_ACTION_CHECK;
                        break;
                    case KEYITEMS_POCKET:
                        gBagMenu->unk820 = &gBagMenu->unk824;
                        if (sRegisterSubMenu == FALSE)
                        {
                            gBagMenu->unk828 = 4;
                            memcpy(&gBagMenu->unk824, &sKeyItemMenuActions, NELEMS(sKeyItemMenuActions));

                            // check replacing USE with WALK
                            if (gSpecialVar_ItemId == ITEM_MACH_BIKE || gSpecialVar_ItemId == ITEM_ACRO_BIKE)
                            {
                                if (TestPlayerAvatarFlags(6))
                                    gBagMenu->unk824 = MENU_ACTION_WALK;
                            }
                        }
						else
                        {
                            gBagMenu->unk828 = 4;
                            memcpy(&gBagMenu->unk824, &sRegisterMenuActions, NELEMS(sRegisterMenuActions));
                            //sRegisterSubMenu = FALSE;
                        }

                        if (gSaveBlock1Ptr->registeredItemSelect == gSpecialVar_ItemId)
                            gBagMenu->unk825 = MENU_ACTION_DESELECT;
                        else if (gSaveBlock1Ptr->registeredItemL == gSpecialVar_ItemId)
                            gBagMenu->unk825 = MENU_ACTION_DESELECT;
                        else if (gSaveBlock1Ptr->registeredItemR == gSpecialVar_ItemId)
                            gBagMenu->unk825 = MENU_ACTION_DESELECT;
                        break;
                    case BALLS_POCKET:
                        gBagMenu->unk820 = sPokeBallMenuActions;
                        gBagMenu->unk828 = NELEMS(sPokeBallMenuActions);
                        break;
                    case TMHM_POCKET:
                        gBagMenu->unk820 = sTmHmMenuActions;
                        gBagMenu->unk828 = NELEMS(sTmHmMenuActions);
                        break;
                    case BERRIES_POCKET:
                        gBagMenu->unk820 = sBerriesMenuActions;
                        gBagMenu->unk828 = NELEMS(sBerriesMenuActions);
                        break;
                }
            }
    }
    if (gBagPositionStruct.pocket == TMHM_POCKET)
    {
        ClearWindowTilemap(1);
        PrintTMHMMoveData(gSpecialVar_ItemId);
        PutWindowTilemap(3);
        PutWindowTilemap(4);
        schedule_bg_copy_tilemap_to_vram(0);
    }
    else
    {
        CopyItemName(gSpecialVar_ItemId, gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_Var1IsSelected);
        FillWindowPixelBuffer(1, PIXEL_FILL(0));
        BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
    }
    if (gBagMenu->unk828 == 1)
        sub_81ACAF8(BagMenu_AddWindow(0));
    else if (gBagMenu->unk828 == 2)
        sub_81ACAF8(BagMenu_AddWindow(1));
    else if (gBagMenu->unk828 == 4)
        sub_81ACB54(BagMenu_AddWindow(2), 2, 2);
    else
        sub_81ACB54(BagMenu_AddWindow(3), 2, 3);
}

void sub_81ACAF8(u8 a)
{
    AddItemMenuActionTextPrinters(a, 7, 8, 1, 0, 16, gBagMenu->unk828, sItemMenuActions, gBagMenu->unk820);
    InitMenuInUpperLeftCornerPlaySoundWhenAPressed(a, gBagMenu->unk828, 0);
}

void sub_81ACB54(u8 a, u8 b, u8 c)
{
    sub_8198DBC(a, 7, 8, 1, 0x38, b, c, sItemMenuActions, gBagMenu->unk820);
    sub_8199944(a, 0x38, b, c, 0);
}

void unknown_item_menu_type(u8 taskId)
{
    SetUpBagMenuActionItems(taskId);
    if (gBagMenu->unk828 <= 2)
        gTasks[taskId].func = Task_HandleInBattleItemMenuInput;
    else
        gTasks[taskId].func = Task_HandleOutOfBattleItemMenuInput;
}

void Task_HandleInBattleItemMenuInput(u8 taskId)
{
    if (sub_81221EC() != TRUE)
    {
        s8 r4 = Menu_ProcessInputNoWrap();
        switch (r4)
        {
            case MENU_NOTHING_CHOSEN:
                break;
            case MENU_B_PRESSED:
                PlaySE(SE_SELECT);
                sItemMenuActions[4].func.void_u8(taskId);
                break;
            default:
                PlaySE(SE_SELECT);
                sItemMenuActions[gBagMenu->unk820[r4]].func.void_u8(taskId);
                break;
        }
    }
}

void Task_HandleOutOfBattleItemMenuInput(u8 taskId)
{
    if (sub_81221EC() != TRUE)
    {
        s8 cursorPos = Menu_GetCursorPos();
        if (gMain.newKeys & DPAD_UP)
        {
            if (cursorPos > 0 && sub_81ACDFC(cursorPos - 2))
            {
                PlaySE(SE_SELECT);
                sub_8199134(0, -1);
            }
        }
        else if (gMain.newKeys & DPAD_DOWN)
        {
            if (cursorPos < (gBagMenu->unk828 - 2) && sub_81ACDFC(cursorPos + 2))
            {
                PlaySE(SE_SELECT);
                sub_8199134(0, 1);
            }
        }
        else if ((gMain.newKeys & DPAD_LEFT) || GetLRKeysPressed() == MENU_L_PRESSED)
        {
            if ((cursorPos & 1) && sub_81ACDFC(cursorPos - 1))
            {
                PlaySE(SE_SELECT);
                sub_8199134(-1, 0);
            }
        }
        else if ((gMain.newKeys & DPAD_RIGHT) || GetLRKeysPressed() == MENU_R_PRESSED)
        {
            if (!(cursorPos & 1) && sub_81ACDFC(cursorPos + 1))
            {
                PlaySE(SE_SELECT);
                sub_8199134(1, 0);
            }
        }
        else if (gMain.newKeys & A_BUTTON)
        {
            PlaySE(SE_SELECT);
            sItemMenuActions[gBagMenu->unk820[cursorPos]].func.void_u8(taskId);
        }
        else if (gMain.newKeys & B_BUTTON)
        {
            PlaySE(SE_SELECT);
            sItemMenuActions[4].func.void_u8(taskId);
        }
    }
}

bool8 sub_81ACDFC(s8 a)
{
    if (a < 0)
        return FALSE;
    if (a > gBagMenu->unk828)
        return FALSE;
    if (gBagMenu->unk820[a] == MENU_ACTION_COUNT)
        return FALSE;
    return TRUE;
}

void BagMenu_RemoveSomeWindow(void)
{
    if (gBagMenu->unk828 == 1)
        BagMenu_RemoveWindow(0);
    else if (gBagMenu->unk828 == 2)
    {
        BagMenu_RemoveWindow(1);
    }
    else if (gBagMenu->unk828 == 4)
    {
        BagMenu_RemoveWindow(2);
    }
    else
        BagMenu_RemoveWindow(3);
}

void ItemMenu_UseOutOfBattle(u8 taskId)
{
    if (ItemId_GetFieldFunc(gSpecialVar_ItemId))
    {
        BagMenu_RemoveSomeWindow();
        if (CalculatePlayerPartyCount() == 0 && ItemId_GetType(gSpecialVar_ItemId) == 1)
            BagMenu_PrintThereIsNoPokemon(taskId);
        else
        {
            FillWindowPixelBuffer(1, PIXEL_FILL(0));
            schedule_bg_copy_tilemap_to_vram(0);
            if (gBagPositionStruct.pocket != BERRIES_POCKET)
                ItemId_GetFieldFunc(gSpecialVar_ItemId)(taskId);
            else
                ItemUseOutOfBattle_Berry(taskId);
        }
    }
}

void ItemMenu_Toss(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    BagMenu_RemoveSomeWindow();
    data[8] = 1;
    if (data[2] == 1)
    {
        BagMenu_TossItems(taskId);
    }
    else
    {
        CopyItemName(gSpecialVar_ItemId, gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_TossHowManyVar1s);
        FillWindowPixelBuffer(1, PIXEL_FILL(0));
        BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
        sub_81ABC3C(7);
        gTasks[taskId].func = Task_ChooseHowManyToToss;
    }
}

void BagMenu_TossItems(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    CopyItemName(gSpecialVar_ItemId, gStringVar1);
    ConvertIntToDecimalStringN(gStringVar2, data[8], STR_CONV_MODE_LEFT_ALIGN, 3);
    StringExpandPlaceholders(gStringVar4, gText_ConfirmTossItems);
    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
    BagMenu_YesNo(taskId, 5, &sYesNoTossFunctions);
}

void BagMenu_CancelToss(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    BagMenu_PrintDescription(data[1]);
    BagMenu_PrintCursor_(data[0], 0);
    set_callback3_to_bag(taskId);
}

void Task_ChooseHowManyToToss(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput(&data[8], data[2]) == TRUE)
    {
        PrintItemDepositAmount(gBagMenu->unk817, data[8]);
    }
    else if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        BagMenu_RemoveWindow(7);
        BagMenu_TossItems(taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(SE_SELECT);
        BagMenu_RemoveWindow(7);
        BagMenu_CancelToss(taskId);
    }
}

void BagMenu_ConfirmToss(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    CopyItemName(gSpecialVar_ItemId, gStringVar1);
    ConvertIntToDecimalStringN(gStringVar2, data[8], STR_CONV_MODE_LEFT_ALIGN, 3);
    StringExpandPlaceholders(gStringVar4, gText_ThrewAwayVar2Var1s);
    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
    gTasks[taskId].func = Task_ActuallyToss;
}

void Task_ActuallyToss(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];

    if (gMain.newKeys & (A_BUTTON | B_BUTTON))
    {
        PlaySE(SE_SELECT);
        RemoveBagItem(gSpecialVar_ItemId, data[8]);
        DestroyListMenuTask(data[0], scrollPos, cursorPos);
        UpdatePocketItemList(gBagPositionStruct.pocket);
        SetInitialScrollAndCursorPositions(gBagPositionStruct.pocket);
        LoadBagItemListBuffers(gBagPositionStruct.pocket);
        data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *scrollPos, *cursorPos);
        schedule_bg_copy_tilemap_to_vram(0);
        set_callback3_to_bag(taskId);
    }
}


void ItemMenu_Give(u8 taskId)
{
    BagMenu_RemoveSomeWindow();
    if (!itemid_80BF6D8_mail_related(gSpecialVar_ItemId))
    {
        DisplayItemMessage(taskId, 1, gText_CantWriteMail, sub_81AD350);
    }
    else if (!ItemId_GetImportance(gSpecialVar_ItemId))
    {
        if (CalculatePlayerPartyCount() == 0)
            BagMenu_PrintThereIsNoPokemon(taskId);
        else
        {
            gBagMenu->mainCallback2 = CB2_ChooseMonToGiveItem;
            Task_FadeAndCloseBagMenu(taskId);
        }
    }
    else
    {
        BagMenu_PrintItemCantBeHeld(taskId);
    }
}

void BagMenu_PrintThereIsNoPokemon(u8 taskId)
{
    DisplayItemMessage(taskId, 1, gText_NoPokemon, sub_81AD350);
}

void BagMenu_PrintItemCantBeHeld(u8 taskId)
{
    CopyItemName(gSpecialVar_ItemId, gStringVar1);
    StringExpandPlaceholders(gStringVar4, gText_Var1CantBeHeld);
    DisplayItemMessage(taskId, 1, gStringVar4, sub_81AD350);
}

void sub_81AD350(u8 taskId)
{
    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        BagMenu_InitListsMenu(taskId);
    }
}

void ItemMenu_CheckTag(u8 taskId)
{
    gBagMenu->mainCallback2 = DoBerryTagScreen;
    Task_FadeAndCloseBagMenu(taskId);
}

void ItemMenu_Cancel(u8 taskId)
{
    s16* data = gTasks[taskId].data;
	sRegisterSubMenu = FALSE;
    BagMenu_RemoveSomeWindow();
    BagMenu_PrintDescription(data[1]);
    schedule_bg_copy_tilemap_to_vram(0);
    schedule_bg_copy_tilemap_to_vram(1);
    BagMenu_PrintCursor_(data[0], 0);
    set_callback3_to_bag(taskId);
}

void ItemMenu_UseInBattle(u8 taskId)
{
    if (ItemId_GetBattleFunc(gSpecialVar_ItemId))
    {
        BagMenu_RemoveSomeWindow();
        ItemId_GetBattleFunc(gSpecialVar_ItemId)(taskId);
    }
}

void CB2_ReturnToBagMenuPocket(void)
{
    GoToBagMenu(RETURN_LOCATION_UNCHANGED, POCKETS_COUNT, NULL);
}

void item_menu_type_2(u8 taskId)
{
    if (!itemid_80BF6D8_mail_related(gSpecialVar_ItemId))
    {
        DisplayItemMessage(taskId, 1, gText_CantWriteMail, sub_81AD350);
    }
    else if (!sub_8122148(gSpecialVar_ItemId))
    {
        CopyItemName(gSpecialVar_ItemId, gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_Var1CantBeHeldHere);
        DisplayItemMessage(taskId, 1, gStringVar4, sub_81AD350);
    }
    else if (gBagPositionStruct.pocket != KEYITEMS_POCKET && !ItemId_GetImportance(gSpecialVar_ItemId))
    {
        Task_FadeAndCloseBagMenu(taskId);
    }
    else
    {
        BagMenu_PrintItemCantBeHeld(taskId);
    }
}

void item_menu_type_b(u8 taskId)
{
    if (ItemIsMail(gSpecialVar_ItemId) == TRUE)
        DisplayItemMessage(taskId, 1, gText_CantWriteMail, sub_81AD350);
    else if (gBagPositionStruct.pocket != KEYITEMS_POCKET && !ItemId_GetImportance(gSpecialVar_ItemId))
        gTasks[taskId].func = Task_FadeAndCloseBagMenu;
    else
        BagMenu_PrintItemCantBeHeld(taskId);
}

void DisplaySellItemAskString(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (ItemId_GetPrice(gSpecialVar_ItemId) == 0)
    {
        CopyItemName(gSpecialVar_ItemId, gStringVar2);
        StringExpandPlaceholders(gStringVar4, gText_CantBuyKeyItem);
        DisplayItemMessage(taskId, 1, gStringVar4, BagMenu_InitListsMenu);
    }
    else
    {
        data[8] = 1;
        if (data[2] == 1)
        {
            bag_menu_AddMoney_window();
            sub_81AD680(taskId);
        }
        else
        {
            CopyItemName(gSpecialVar_ItemId, gStringVar2);
            StringExpandPlaceholders(gStringVar4, gText_HowManyToSell);
            DisplayItemMessage(taskId, 1, gStringVar4, sub_81AD730);
        }
    }
}

void sub_81AD680(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    ConvertIntToDecimalStringN(gStringVar1, (ItemId_GetPrice(gSpecialVar_ItemId) / 2) * data[8], STR_CONV_MODE_LEFT_ALIGN, 6);
    StringExpandPlaceholders(gStringVar4, gText_ICanPayVar1);
    DisplayItemMessage(taskId, 1, gStringVar4, sub_81AD6E4);
}

void sub_81AD6E4(u8 taskId)
{
    BagMenu_YesNo(taskId, 6, &sYesNoSellItemFunctions);
}

void BagMenu_CancelSell(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    bag_menu_remove_money_window();
    bag_menu_RemoveBagItem_message_window(4);
    BagMenu_PrintCursor_(data[0], 0);
    set_callback3_to_bag(taskId);
}

void sub_81AD730(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u8 windowId = BagMenu_AddWindow(8);

    PrintItemSoldAmount(windowId, 1, (ItemId_GetPrice(gSpecialVar_ItemId) / 2) * data[8]);
    bag_menu_AddMoney_window();
    gTasks[taskId].func = sub_81AD794;
}

void sub_81AD794(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput(&data[8], data[2]) == TRUE)
    {
        PrintItemSoldAmount(gBagMenu->unk818, data[8], (ItemId_GetPrice(gSpecialVar_ItemId) / 2) * data[8]);
    }
    else if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        BagMenu_RemoveWindow(8);
        sub_81AD680(taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(SE_SELECT);
        BagMenu_PrintCursor_(data[0], 0);
        bag_menu_remove_money_window();
        BagMenu_RemoveWindow(8);
        bag_menu_RemoveBagItem_message_window(4);
        set_callback3_to_bag(taskId);
    }
}

void BagMenu_ConfirmSell(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    CopyItemName(gSpecialVar_ItemId, gStringVar2);
    ConvertIntToDecimalStringN(gStringVar1, (ItemId_GetPrice(gSpecialVar_ItemId) / 2) * data[8], STR_CONV_MODE_LEFT_ALIGN, 6);
    StringExpandPlaceholders(gStringVar4, gText_TurnedOverVar1ForVar2);
    DisplayItemMessage(taskId, 1, gStringVar4, sub_81AD8C8);
}

void sub_81AD8C8(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];

    PlaySE(SE_REGI);
    RemoveBagItem(gSpecialVar_ItemId, data[8]);
    AddMoney(&gSaveBlock1Ptr->money, (ItemId_GetPrice(gSpecialVar_ItemId) / 2) * data[8]);
    DestroyListMenuTask(data[0], scrollPos, cursorPos);
    UpdatePocketItemList(gBagPositionStruct.pocket);
    SetInitialScrollAndCursorPositions(gBagPositionStruct.pocket);
    LoadBagItemListBuffers(gBagPositionStruct.pocket);
    data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *scrollPos, *cursorPos);
    BagMenu_PrintCursor_(data[0], 2);
    PrintMoneyAmountInMoneyBox(gBagMenu->unk819, GetMoney(&gSaveBlock1Ptr->money), 0);
    gTasks[taskId].func = sub_81AD9C0;
}

void sub_81AD9C0(u8 taskId)
{
    if (gMain.newKeys & (A_BUTTON | B_BUTTON))
    {
        PlaySE(SE_SELECT);
        bag_menu_remove_money_window();
        BagMenu_InitListsMenu(taskId);
    }
}

void DisplayDepositItemAskString(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    data[8] = 1;
    if (data[2] == 1)
    {
        sub_81ADB14(taskId);
    }
    else
    {
        CopyItemName(gSpecialVar_ItemId, gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_DepositHowManyVar1);
        FillWindowPixelBuffer(1, PIXEL_FILL(0));
        BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
        sub_81ABC3C(7);
        gTasks[taskId].func = sub_81ADA7C;
    }
}

void sub_81ADA7C(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput(&data[8], data[2]) == TRUE)
    {
        PrintItemDepositAmount(gBagMenu->unk817, data[8]);
    }
    else if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        BagMenu_RemoveWindow(7);
        sub_81ADB14(taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(SE_SELECT);
        BagMenu_PrintDescription(data[1]);
        BagMenu_PrintCursor_(data[0], 0);
        BagMenu_RemoveWindow(7);
        set_callback3_to_bag(taskId);
    }
}

void sub_81ADB14(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    if (ItemId_GetImportance(gSpecialVar_ItemId))
    {
        BagMenu_Print(1, 1, gText_CantStoreImportantItems, 3, 1, 0, 0, 0, 0);
        gTasks[taskId].func = sub_81ADC0C;
    }
    else if (AddPCItem(gSpecialVar_ItemId, data[8]) == TRUE)
    {
        CopyItemName(gSpecialVar_ItemId, gStringVar1);
        ConvertIntToDecimalStringN(gStringVar2, data[8], STR_CONV_MODE_LEFT_ALIGN, 3);
        StringExpandPlaceholders(gStringVar4, gText_DepositedVar2Var1s);
        BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);
        gTasks[taskId].func = Task_ActuallyToss;
    }
    else
    {
        BagMenu_Print(1, 1, gText_NoRoomForItems, 3, 1, 0, 0, 0, 0);
        gTasks[taskId].func = sub_81ADC0C;
    }
}

void sub_81ADC0C(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (gMain.newKeys & (A_BUTTON | B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BagMenu_PrintDescription(data[1]);
        BagMenu_PrintCursor_(data[0], 0);
        set_callback3_to_bag(taskId);
    }
}

bool8 IsWallysBag(void)
{
    if (gBagPositionStruct.location == 10)
        return TRUE;
    return FALSE;
}

void PrepareBagForWallyTutorial(void)
{
    u32 i;

    sTempWallyBag = AllocZeroed(sizeof(struct TempWallyStruct));
    memcpy(sTempWallyBag->bagPocket_Items, gSaveBlock1Ptr->bagPocket_Items, sizeof(gSaveBlock1Ptr->bagPocket_Items));
    memcpy(sTempWallyBag->bagPocket_PokeBalls, gSaveBlock1Ptr->bagPocket_PokeBalls, sizeof(gSaveBlock1Ptr->bagPocket_PokeBalls));
    sTempWallyBag->pocket = gBagPositionStruct.pocket;
    for (i = 0; i <= 4; i++)
    {
        sTempWallyBag->cursorPosition[i] = gBagPositionStruct.cursorPosition[i];
        sTempWallyBag->scrollPosition[i] = gBagPositionStruct.scrollPosition[i];
    }
    ClearItemSlots(gSaveBlock1Ptr->bagPocket_Items, BAG_ITEMS_COUNT);
    ClearItemSlots(gSaveBlock1Ptr->bagPocket_PokeBalls, BAG_POKEBALLS_COUNT);
    ResetBagScrollPositions();
}

void RestoreBagAfterWallyTutorial(void)
{
    u32 i;

    memcpy(gSaveBlock1Ptr->bagPocket_Items, sTempWallyBag->bagPocket_Items, sizeof(sTempWallyBag->bagPocket_Items));
    memcpy(gSaveBlock1Ptr->bagPocket_PokeBalls, sTempWallyBag->bagPocket_PokeBalls, sizeof(sTempWallyBag->bagPocket_PokeBalls));
    gBagPositionStruct.pocket = sTempWallyBag->pocket;
    for (i = 0; i <= 4; i++)
    {
        gBagPositionStruct.cursorPosition[i] = sTempWallyBag->cursorPosition[i];
        gBagPositionStruct.scrollPosition[i] = sTempWallyBag->scrollPosition[i];
    }
    Free(sTempWallyBag);
}

void DoWallyTutorialBagMenu(void)
{
    PrepareBagForWallyTutorial();
    AddBagItem(ITEM_POTION, 1);
    AddBagItem(ITEM_POKE_BALL, 1);
    GoToBagMenu(RETURN_LOCATION_BATTLE_2, ITEMS_POCKET, CB2_SetUpReshowBattleScreenAfterMenu2);
}

void Task_WallyTutorialBagMenu(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        switch (data[8])
        {
            case 0x66:
                PlaySE(SE_SELECT);
                SwitchBagPocket(taskId, 1, 0);
                data[8]++;
                break;
            case 0xCC:
                PlaySE(SE_SELECT);
                BagMenu_PrintCursor_(data[0], 2);
                gSpecialVar_ItemId = ITEM_POKE_BALL;
                SetUpBagMenuActionItems(taskId);
                data[8]++;
                break;
            case 0x132:
                PlaySE(SE_SELECT);
                BagMenu_RemoveSomeWindow();
                DestroyListMenuTask(data[0], 0, 0);
                RestoreBagAfterWallyTutorial();
                Task_FadeAndCloseBagMenu(taskId);
                break;
            default:
                data[8]++;
                break;
        }
    }
}

void unknown_ItemMenu_Show(u8 taskId)
{
    gSpecialVar_0x8005 = gSpecialVar_ItemId;
    gSpecialVar_Result = 1;
    BagMenu_RemoveSomeWindow();
    Task_FadeAndCloseBagMenu(taskId);
}

void CB2_ApprenticeExitBagMenu(void)
{
    gFieldCallback = Apprentice_EnableBothScriptContexts;
    SetMainCallback2(CB2_ReturnToField);
}

void unknown_ItemMenu_Give2(u8 taskId)
{
    RemoveBagItem(gSpecialVar_ItemId, 1);
    gSpecialVar_Result = 1;
    BagMenu_RemoveSomeWindow();
    Task_FadeAndCloseBagMenu(taskId);
}

void CB2_FavorLadyExitBagMenu(void)
{
    gFieldCallback = FieldCallback_FavorLadyEnableScriptContexts;
    SetMainCallback2(CB2_ReturnToField);
}

void unknown_ItemMenu_Confirm2(u8 taskId)
{
    gSpecialVar_Result = 1;
    BagMenu_RemoveSomeWindow();
    Task_FadeAndCloseBagMenu(taskId);
}

void CB2_QuizLadyExitBagMenu(void)
{
    gFieldCallback = FieldCallback_QuizLadyEnableScriptContexts;
    SetMainCallback2(CB2_ReturnToField);
}

void BagMenu_PrintPocketNames(const u8 *pocketName1, const u8 *pocketName2)
{
    struct WindowTemplate window = {0, 0, 0, 0, 0, 0, 0};
    u16 windowId;
    int offset;

    window.width = 16;
    window.height = 2;
    windowId = AddWindow(&window);
    FillWindowPixelBuffer(windowId, PIXEL_FILL(0));
    offset = GetStringCenterAlignXOffset(1, pocketName1, 0x40);
    BagMenu_Print(windowId, 1, pocketName1, offset, 1, 0, 0, -1, 1);
    if (pocketName2)
    {
        offset = GetStringCenterAlignXOffset(1, pocketName2, 0x40);
        BagMenu_Print(windowId, 1, pocketName2, offset + 0x40, 1, 0, 0, -1, 1);
    }
    CpuCopy32((u8*)GetWindowAttribute(windowId, WINDOW_TILE_DATA), gBagMenu->pocketNameBuffer, 0x400);
    RemoveWindow(windowId);
}

void BagMenu_CopyPocketNameToWindow(u32 a)
{
    u8 (* r4)[32][32];
    u8* windowAttribute;
    int b;
    if (a > 8)
        a = 8;
    r4 = &gBagMenu->pocketNameBuffer;
    windowAttribute = (u8*)GetWindowAttribute(2, WINDOW_TILE_DATA);
    CpuCopy32(r4[0][a], windowAttribute, 0x100);
    b = a + 16;
    CpuCopy32(r4[0][b], windowAttribute + 0x100, 0x100);
    CopyWindowToVram(2, 2);
}

void SetupBagMenu_Textboxes(void)
{
    u8 i;

    InitWindows(gUnknown_08614174);
    DeactivateAllTextPrinters();
    LoadUserWindowBorderGfx(0, 1, 0xE0);
    LoadMessageBoxGfx(0, 10, 0xD0);
    sub_819A2BC(0xC0, 1);
    LoadPalette(&gUnknown_0860F074, 0xF0, 0x20);
    for (i = 0; i < 3; i++)
    {
        FillWindowPixelBuffer(i, PIXEL_FILL(0));
        PutWindowTilemap(i);
    }
    schedule_bg_copy_tilemap_to_vram(0);
    schedule_bg_copy_tilemap_to_vram(1);
}

void BagMenu_Print(u8 windowId, u8 fontId, const u8 *str, u8 left, u8 top, u8 letterSpacing, u8 lineSpacing, u8 speed, u8 h)
{
    AddTextPrinterParameterized4(windowId, fontId, left, top, letterSpacing, lineSpacing, sFontColorTable[h], speed, str);
}

u8 sub_81AE124(u8 a)
{
    return gBagMenu->windowPointers[a];
}

u8 BagMenu_AddWindow(u8 a)
{
    u8 *ptr = &gBagMenu->windowPointers[a];
    if (*ptr == 0xFF)
    {
        *ptr = AddWindow(&gUnknown_086141AC[a]);
        DrawStdFrameWithCustomTileAndPalette(*ptr, 0, 1, 14);
        schedule_bg_copy_tilemap_to_vram(1);
    }
    return *ptr;
}

void BagMenu_RemoveWindow(u8 a)
{
    u8 *ptr = &gBagMenu->windowPointers[a];
    if (*ptr != 0xFF)
    {
        ClearStdWindowAndFrameToTransparent(*ptr, 0);
        ClearWindowTilemap(*ptr);
        RemoveWindow(*ptr);
        schedule_bg_copy_tilemap_to_vram(1);
        *ptr = 0xFF;
    }
}

u8 AddItemMessageWindow(u8 a)
{
    u8 *ptr = &gBagMenu->windowPointers[a];
    if (*ptr == 0xFF)
        *ptr = AddWindow(&gUnknown_086141AC[a]);
    return *ptr;
}

void bag_menu_RemoveBagItem_message_window(u8 a)
{
    u8 *ptr = &gBagMenu->windowPointers[a];
    if (*ptr != 0xFF)
    {
        ClearDialogWindowAndFrameToTransparent(*ptr, FALSE);
        // This ClearWindowTilemap call is redundant, since ClearDialogWindowAndFrameToTransparent already calls it.
        ClearWindowTilemap(*ptr);
        RemoveWindow(*ptr);
        schedule_bg_copy_tilemap_to_vram(1);
        *ptr = 0xFF;
    }
}

void BagMenu_YesNo(u8 a, u8 b, const struct YesNoFuncTable *funcTable)
{
    CreateYesNoMenuWithCallbacks(a, &gUnknown_086141AC[b], 1, 0, 2, 1, 14, funcTable);
}

void bag_menu_AddMoney_window(void)
{
    u8 windowId = BagMenu_AddWindow(9);
    PrintMoneyAmountInMoneyBoxWithBorder(windowId, 1, 14, GetMoney(&gSaveBlock1Ptr->money));
    AddMoneyLabelObject(19, 11);
}

void bag_menu_remove_money_window(void)
{
    BagMenu_RemoveWindow(9);
    RemoveMoneyLabelObject();
}

void BagMenu_PrepareTMHMMoveWindow(void)
{
    FillWindowPixelBuffer(3, PIXEL_FILL(0));
    blit_move_info_icon(3, 19, 0, 0);
    blit_move_info_icon(3, 20, 0, 12);
    blit_move_info_icon(3, 21, 0, 24);
    blit_move_info_icon(3, 22, 0, 36);
    CopyWindowToVram(3, 2);
}

void PrintTMHMMoveData(u16 itemId)
{
    u8 i;
    u16 moveId;
    const u8* text;

    FillWindowPixelBuffer(4, PIXEL_FILL(0));
    if (itemId == ITEM_NONE)
    {
        for (i = 0; i < 4; i++)
            BagMenu_Print(4, 1, gText_ThreeDashes, 7, i * 12, 0, 0, -1, 4);
        CopyWindowToVram(4, 2);
    }
    else
    {
        moveId = ItemIdToBattleMoveId(itemId);
        blit_move_info_icon(4, gBattleMoves[moveId].type + 1, 0, 0);
        if (gBattleMoves[moveId].power <= 1)
        {
            text = gText_ThreeDashes;
        }
        else
        {
            ConvertIntToDecimalStringN(gStringVar1, gBattleMoves[moveId].power, STR_CONV_MODE_RIGHT_ALIGN, 3);
            text = gStringVar1;
        }
        BagMenu_Print(4, 1, text, 7, 12, 0, 0, -1, 4);
        if (gBattleMoves[moveId].accuracy == 0)
        {
            text = gText_ThreeDashes;
        }
        else
        {
            ConvertIntToDecimalStringN(gStringVar1, gBattleMoves[moveId].accuracy, STR_CONV_MODE_RIGHT_ALIGN, 3);
            text = gStringVar1;
        }
        BagMenu_Print(4, 1, text, 7, 24, 0, 0, -1, 4);
        ConvertIntToDecimalStringN(gStringVar1, gBattleMoves[moveId].pp, STR_CONV_MODE_RIGHT_ALIGN, 3);
        BagMenu_Print(4, 1, gStringVar1, 7, 36, 0, 0, -1, 4);
        CopyWindowToVram(4, 2);
    }
}
static void ResetRegisteredItem(u16 item)
{
    if (gSaveBlock1Ptr->registeredItemSelect == item)
        gSaveBlock1Ptr->registeredItemSelect = ITEM_NONE;
    else if (gSaveBlock1Ptr->registeredItemL == item)
        gSaveBlock1Ptr->registeredItemL = ITEM_NONE;
    else if (gSaveBlock1Ptr->registeredItemR == item)
        gSaveBlock1Ptr->registeredItemR = ITEM_NONE;
}

static void ItemMenu_FinishRegister(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];

    DestroyListMenuTask(data[0], scrollPos, cursorPos);
    LoadBagItemListBuffers(gBagPositionStruct.pocket);
    data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *scrollPos, *cursorPos);
    schedule_bg_copy_tilemap_to_vram(0);
    ItemMenu_Cancel(taskId);
}

static void ItemMenu_Register(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];
    int listPosition;

    BagMenu_RemoveSomeWindow();
    sRegisterSubMenu = TRUE;
    listPosition = ListMenu_ProcessInput(data[0]);
    ListMenuGetScrollAndRow(data[0], scrollPos, cursorPos);
    sub_81AB824();
    BagMenu_PrintCursor_(data[0], 2);
    data[1] = listPosition;
    data[2] = BagGetQuantityByPocketPosition(gBagPositionStruct.pocket + 1, listPosition);
    gSpecialVar_ItemId = BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, listPosition);
    sBagMenuTasks[gBagPositionStruct.location](taskId);
}

static void ItemMenu_RegisterSelect(u8 taskId)
{
    if (gSaveBlock1Ptr->registeredItemSelect == gSpecialVar_ItemId)
        gSaveBlock1Ptr->registeredItemSelect = 0;
    else
        gSaveBlock1Ptr->registeredItemSelect = gSpecialVar_ItemId;

    gTasks[taskId].func = ItemMenu_FinishRegister;
}

static void ItemMenu_RegisterL(u8 taskId)
{
    if (gSaveBlock1Ptr->registeredItemL == gSpecialVar_ItemId)
        gSaveBlock1Ptr->registeredItemL = ITEM_NONE;
    else
        gSaveBlock1Ptr->registeredItemL = gSpecialVar_ItemId;

    gTasks[taskId].func = ItemMenu_FinishRegister;
}

static void ItemMenu_RegisterR(u8 taskId)
{
    if (gSaveBlock1Ptr->registeredItemR == gSpecialVar_ItemId)
        gSaveBlock1Ptr->registeredItemR = ITEM_NONE;
    else
        gSaveBlock1Ptr->registeredItemR = gSpecialVar_ItemId;

    gTasks[taskId].func = ItemMenu_FinishRegister;
}

static void ItemMenu_Deselect(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];
    int listPosition = ListMenu_ProcessInput(data[0]);

    ResetRegisteredItem(BagGetItemIdByPocketPosition(gBagPositionStruct.pocket + 1, listPosition));
    gTasks[taskId].func = ItemMenu_FinishRegister;
}

#define tUsingRegisteredKeyItem data[3]
bool8 UseRegisteredKeyItemOnField(u8 button)
{
    u8 taskId;
    u16 registeredItem;

    if (InUnionRoom() == TRUE || InBattlePyramid() || InBattlePike() || InMultiPartnerRoom() == TRUE)
        return FALSE;

    HideMapNamePopUpWindow();
    ChangeBgY_ScreenOff(0, 0, 0);

    switch (button)
    {
    case 0:
        registeredItem = gSaveBlock1Ptr->registeredItemSelect;
        break;
    case 1:
        registeredItem = gSaveBlock1Ptr->registeredItemL;
        break;
    case 2:
        registeredItem = gSaveBlock1Ptr->registeredItemR;
        break;
    default:
        return FALSE;
    }

    if (registeredItem != ITEM_NONE)
    {
        if (CheckBagHasItem(registeredItem, 1) == TRUE)
        {
            ScriptContext2_Enable();
            FreezeEventObjects();
            sub_808B864();
            sub_808BCF4();
            gSpecialVar_ItemId = registeredItem;
            taskId = CreateTask(ItemId_GetFieldFunc(registeredItem), 8);
            gTasks[taskId].tUsingRegisteredKeyItem = TRUE;
            return TRUE;
        }
        else
        {
            switch (button)
            {
            case 0:
                gSaveBlock1Ptr->registeredItemSelect = ITEM_NONE;
                break;
            case 1:
                gSaveBlock1Ptr->registeredItemL = ITEM_NONE;
                break;
            case 2:
                gSaveBlock1Ptr->registeredItemR = ITEM_NONE;
                break;
            }
        }
    }

    ScriptContext1_SetupScript(EventScript_SelectWithoutRegisteredItem);
    return TRUE;
}

#undef tUsingRegisteredKeyItem

// bag sorting
enum BagSortOptions
{
    SORT_ALPHABETICALLY,
    SORT_BY_TYPE,
    SORT_BY_AMOUNT, //greatest->least
};
enum ItemSortType
{
	ITEM_TYPE_FIELD_USE,
	ITEM_TYPE_HEALTH_RECOVERY,
	ITEM_TYPE_STATUS_RECOVERY,
	ITEM_TYPE_PP_RECOVERY,
	ITEM_TYPE_STAT_BOOST_DRINK,
	ITEM_TYPE_STAT_BOOST_WING,
	ITEM_TYPE_EVOLUTION_STONE,
	ITEM_TYPE_EVOLUTION_ITEM,
	ITEM_TYPE_BATTLE_ITEM,
	ITEM_TYPE_FLUTE,
	ITEM_TYPE_STAT_BOOST_HELD_ITEM,
	ITEM_TYPE_HELD_ITEM,
	ITEM_TYPE_GEM,
	ITEM_TYPE_PLATE,
	ITEM_TYPE_MEMORY,
	ITEM_TYPE_DRIVE,
	ITEM_TYPE_INCENSE,
	ITEM_TYPE_MEGA_STONE,
	ITEM_TYPE_Z_CRYSTAL,
	ITEM_TYPE_NECTAR,
	ITEM_TYPE_SELLABLE,
	ITEM_TYPE_RELIC,
	ITEM_TYPE_SHARD,
	ITEM_TYPE_FOSSIL,
	ITEM_TYPE_MAIL,
};
static const u8 sText_SortItemsHow[] = _("Sort items how?");
static const u8 sText_Name[] = _("name");
static const u8 sText_Type[] = _("type");
static const u8 sText_Amount[] = _("amount");
static const u8 sText_ItemsSorted[] = _("Items sorted by {STR_VAR_1}!");
static const u8 *const sSortTypeStrings[] = 
{
    [SORT_ALPHABETICALLY] = sText_Name,
    [SORT_BY_TYPE] = sText_Type,
    [SORT_BY_AMOUNT] = sText_Amount,
};

static const u8 sBagMenuSortItems[] =
{
    MENU_ACTION_BY_NAME,
    MENU_ACTION_BY_TYPE,
    MENU_ACTION_BY_AMOUNT,
    MENU_ACTION_CANCEL,
};

static const u8 sBagMenuSortKeyItems[] =
{
    MENU_ACTION_BY_NAME,
    MENU_ACTION_CANCEL,
};

static const u8 sBagMenuSortPokeBallsBerries[] =
{
    MENU_ACTION_BY_NAME,
    MENU_ACTION_BY_AMOUNT,
    MENU_ACTION_COUNT,
    MENU_ACTION_CANCEL,
};

const u16 gItemsByType[ITEMS_COUNT] =
{
    [ITEM_REPEL] = ITEM_TYPE_FIELD_USE,
    [ITEM_SUPER_REPEL] = ITEM_TYPE_FIELD_USE,
    [ITEM_MAX_REPEL] = ITEM_TYPE_FIELD_USE,
    [ITEM_ESCAPE_ROPE] = ITEM_TYPE_FIELD_USE,
    [ITEM_HEART_SCALE] = ITEM_TYPE_FIELD_USE,

    [ITEM_POTION] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_FULL_RESTORE] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_MAX_POTION] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_HYPER_POTION] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_SUPER_POTION] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_REVIVE] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_MAX_REVIVE] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_FRESH_WATER] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_SODA_POP] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_LEMONADE] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_MOOMOO_MILK] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_ENERGY_POWDER] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_ENERGY_ROOT] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_REVIVAL_HERB] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_BERRY_JUICE] = ITEM_TYPE_HEALTH_RECOVERY,
    [ITEM_SACRED_ASH] = ITEM_TYPE_HEALTH_RECOVERY,

    [ITEM_ANTIDOTE] = ITEM_TYPE_STATUS_RECOVERY,
    [ITEM_BURN_HEAL] = ITEM_TYPE_STATUS_RECOVERY,
    [ITEM_ICE_HEAL] = ITEM_TYPE_STATUS_RECOVERY,
    [ITEM_AWAKENING] = ITEM_TYPE_STATUS_RECOVERY,
    [ITEM_PARALYZE_HEAL] = ITEM_TYPE_STATUS_RECOVERY,
    [ITEM_FULL_HEAL] = ITEM_TYPE_STATUS_RECOVERY,
    [ITEM_LAVA_COOKIE] = ITEM_TYPE_STATUS_RECOVERY,
    
    [ITEM_HONEY] = ITEM_TYPE_STATUS_RECOVERY,
    [ITEM_BIG_MALASADA] = ITEM_TYPE_STATUS_RECOVERY,
    [ITEM_OLD_GATEAU] = ITEM_TYPE_STATUS_RECOVERY,
    [ITEM_HEAL_POWDER] = ITEM_TYPE_STATUS_RECOVERY,
    
    [ITEM_ETHER] = ITEM_TYPE_PP_RECOVERY,
    [ITEM_MAX_ETHER] = ITEM_TYPE_PP_RECOVERY,
    [ITEM_ELIXIR] = ITEM_TYPE_PP_RECOVERY,
    [ITEM_MAX_ELIXIR] = ITEM_TYPE_PP_RECOVERY,

    [ITEM_HP_UP] = ITEM_TYPE_STAT_BOOST_DRINK,
    [ITEM_PROTEIN] = ITEM_TYPE_STAT_BOOST_DRINK,
    [ITEM_IRON] = ITEM_TYPE_STAT_BOOST_DRINK,
    [ITEM_CARBOS] = ITEM_TYPE_STAT_BOOST_DRINK,
    [ITEM_CALCIUM] = ITEM_TYPE_STAT_BOOST_DRINK,
    [ITEM_RARE_CANDY] = ITEM_TYPE_STAT_BOOST_DRINK,
    [ITEM_PP_UP] = ITEM_TYPE_STAT_BOOST_DRINK,
    [ITEM_ZINC] = ITEM_TYPE_STAT_BOOST_DRINK,
    [ITEM_PP_MAX] = ITEM_TYPE_STAT_BOOST_DRINK,
    
    [ITEM_ABILITY_CAPSULE] = ITEM_TYPE_STAT_BOOST_DRINK,
    [ITEM_HEALTH_WING] = ITEM_TYPE_STAT_BOOST_WING,
    [ITEM_MUSCLE_WING] = ITEM_TYPE_STAT_BOOST_WING,
    [ITEM_RESIST_WING] = ITEM_TYPE_STAT_BOOST_WING,
    [ITEM_GENIUS_WING] = ITEM_TYPE_STAT_BOOST_WING,
    [ITEM_CLEVER_WING] = ITEM_TYPE_STAT_BOOST_WING,
    [ITEM_SWIFT_WING] = ITEM_TYPE_STAT_BOOST_WING,
    [ITEM_PRETTY_WING] = ITEM_TYPE_STAT_BOOST_WING,
    
    [ITEM_POWER_BRACER] = ITEM_TYPE_STAT_BOOST_HELD_ITEM,
    [ITEM_POWER_BELT] = ITEM_TYPE_STAT_BOOST_HELD_ITEM,
    [ITEM_POWER_LENS] = ITEM_TYPE_STAT_BOOST_HELD_ITEM,
    [ITEM_POWER_BAND] = ITEM_TYPE_STAT_BOOST_HELD_ITEM,
    [ITEM_POWER_ANKLET] = ITEM_TYPE_STAT_BOOST_HELD_ITEM,
    [ITEM_POWER_WEIGHT] = ITEM_TYPE_STAT_BOOST_HELD_ITEM,
    [ITEM_MACHO_BRACE] = ITEM_TYPE_STAT_BOOST_HELD_ITEM,

    [ITEM_SUN_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_MOON_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_FIRE_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_THUNDER_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_WATER_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_LEAF_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_DAWN_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_DUSK_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_SHINY_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_ICE_STONE] = ITEM_TYPE_EVOLUTION_STONE,
    [ITEM_OVAL_STONE] = ITEM_TYPE_EVOLUTION_STONE,

    [ITEM_KINGS_ROCK] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_DEEP_SEA_TOOTH] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_DEEP_SEA_SCALE] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_EVERSTONE] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_METAL_COAT] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_DRAGON_SCALE] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_UP_GRADE] = ITEM_TYPE_EVOLUTION_ITEM,

    [ITEM_PROTECTOR] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_MAGMARIZER] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_PRISM_SCALE] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_SACHET] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_WHIPPED_DREAM] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_RAZOR_CLAW] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_RAZOR_FANG] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_REAPER_CLOTH] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_DUBIOUS_DISC] = ITEM_TYPE_EVOLUTION_ITEM,
    [ITEM_ELECTIRIZER] = ITEM_TYPE_EVOLUTION_ITEM,

    [ITEM_GUARD_SPEC] = ITEM_TYPE_BATTLE_ITEM,
    [ITEM_DIRE_HIT] = ITEM_TYPE_BATTLE_ITEM,
    [ITEM_X_ATTACK] = ITEM_TYPE_BATTLE_ITEM,
    [ITEM_X_DEFENSE] = ITEM_TYPE_BATTLE_ITEM,
    [ITEM_X_SPEED] = ITEM_TYPE_BATTLE_ITEM,
    [ITEM_X_ACCURACY] = ITEM_TYPE_BATTLE_ITEM,
    [ITEM_X_SP_ATK] = ITEM_TYPE_BATTLE_ITEM,
	[ITEM_X_SP_DEF] = ITEM_TYPE_BATTLE_ITEM,
    [ITEM_POKE_DOLL] = ITEM_TYPE_BATTLE_ITEM,
    [ITEM_FLUFFY_TAIL] = ITEM_TYPE_BATTLE_ITEM,

    [ITEM_BRIGHT_POWDER] = ITEM_TYPE_HELD_ITEM,
    [ITEM_WHITE_HERB] = ITEM_TYPE_HELD_ITEM,
    [ITEM_EXP_SHARE] = ITEM_TYPE_HELD_ITEM,
    [ITEM_QUICK_CLAW] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SOOTHE_BELL] = ITEM_TYPE_HELD_ITEM,
    [ITEM_MENTAL_HERB] = ITEM_TYPE_HELD_ITEM,
    [ITEM_CHOICE_BAND] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SILVER_POWDER] = ITEM_TYPE_HELD_ITEM,
    [ITEM_AMULET_COIN] = ITEM_TYPE_HELD_ITEM,
    [ITEM_CLEANSE_TAG] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SOUL_DEW] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SMOKE_BALL] = ITEM_TYPE_HELD_ITEM,
    [ITEM_FOCUS_BAND] = ITEM_TYPE_HELD_ITEM,
    [ITEM_LUCKY_EGG] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SCOPE_LENS] = ITEM_TYPE_HELD_ITEM,
    [ITEM_LEFTOVERS] = ITEM_TYPE_HELD_ITEM,
    [ITEM_LIGHT_BALL] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SOFT_SAND] = ITEM_TYPE_HELD_ITEM,
    [ITEM_HARD_STONE] = ITEM_TYPE_HELD_ITEM,
    [ITEM_MIRACLE_SEED] = ITEM_TYPE_HELD_ITEM,
    [ITEM_BLACK_GLASSES] = ITEM_TYPE_HELD_ITEM,
    [ITEM_BLACK_BELT] = ITEM_TYPE_HELD_ITEM,
    [ITEM_MAGNET] = ITEM_TYPE_HELD_ITEM,
    [ITEM_MYSTIC_WATER] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SHARP_BEAK] = ITEM_TYPE_HELD_ITEM,
    [ITEM_POISON_BARB] = ITEM_TYPE_HELD_ITEM,
    [ITEM_NEVER_MELT_ICE] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SPELL_TAG] = ITEM_TYPE_HELD_ITEM,
    [ITEM_TWISTED_SPOON] = ITEM_TYPE_HELD_ITEM,
    [ITEM_CHARCOAL] = ITEM_TYPE_HELD_ITEM,
    [ITEM_DRAGON_FANG] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SILK_SCARF] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SHELL_BELL] = ITEM_TYPE_HELD_ITEM,
    [ITEM_LUCKY_PUNCH] = ITEM_TYPE_HELD_ITEM,
    [ITEM_METAL_POWDER] = ITEM_TYPE_HELD_ITEM,
    [ITEM_THICK_CLUB] = ITEM_TYPE_HELD_ITEM,
    [ITEM_STICK] = ITEM_TYPE_HELD_ITEM,

    [ITEM_ADAMANT_ORB] = ITEM_TYPE_HELD_ITEM,
    [ITEM_LUSTROUS_ORB] = ITEM_TYPE_HELD_ITEM,
    [ITEM_GRISEOUS_ORB] = ITEM_TYPE_HELD_ITEM,
    [ITEM_EXPERT_BELT] = ITEM_TYPE_HELD_ITEM,
    [ITEM_POWER_HERB] = ITEM_TYPE_HELD_ITEM,
    [ITEM_WIDE_LENS] = ITEM_TYPE_HELD_ITEM,
    [ITEM_ZOOM_LENS] = ITEM_TYPE_HELD_ITEM,
    [ITEM_DESTINY_KNOT] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SMOOTH_ROCK] = ITEM_TYPE_HELD_ITEM,
    [ITEM_DAMP_ROCK] = ITEM_TYPE_HELD_ITEM,
    [ITEM_HEAT_ROCK] = ITEM_TYPE_HELD_ITEM,
    [ITEM_ICY_ROCK] = ITEM_TYPE_HELD_ITEM,
    [ITEM_BIG_ROOT] = ITEM_TYPE_HELD_ITEM,
    [ITEM_LIGHT_CLAY] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SAFETY_GOGGLES] = ITEM_TYPE_HELD_ITEM,
    [ITEM_ROCKY_HELMET] = ITEM_TYPE_HELD_ITEM,
    [ITEM_WEAKNESS_POLICY] = ITEM_TYPE_HELD_ITEM,
    [ITEM_ASSAULT_VEST] = ITEM_TYPE_HELD_ITEM,
    [ITEM_EVIOLITE] = ITEM_TYPE_HELD_ITEM,
    [ITEM_ABSORB_BULB] = ITEM_TYPE_HELD_ITEM,
    [ITEM_AIR_BALLOON] = ITEM_TYPE_HELD_ITEM,
    [ITEM_ADRENALINE_ORB] = ITEM_TYPE_HELD_ITEM,
    [ITEM_BINDING_BAND] = ITEM_TYPE_HELD_ITEM,
    [ITEM_CELL_BATTERY] = ITEM_TYPE_HELD_ITEM,
    [ITEM_EJECT_BUTTON] = ITEM_TYPE_HELD_ITEM,
    [ITEM_FLOAT_STONE] = ITEM_TYPE_HELD_ITEM,
    [ITEM_FOCUS_SASH] = ITEM_TYPE_HELD_ITEM,
    [ITEM_GRIP_CLAW] = ITEM_TYPE_HELD_ITEM,
    [ITEM_IRON_BALL] = ITEM_TYPE_HELD_ITEM,
    [ITEM_LAGGING_TAIL] = ITEM_TYPE_HELD_ITEM,
    [ITEM_LUMINOUS_MOSS] = ITEM_TYPE_HELD_ITEM,
    [ITEM_QUICK_POWDER] = ITEM_TYPE_HELD_ITEM,
    [ITEM_METRONOME] = ITEM_TYPE_HELD_ITEM,
    [ITEM_MUSCLE_BAND] = ITEM_TYPE_HELD_ITEM,
    [ITEM_PROTECTIVE_PADS] = ITEM_TYPE_HELD_ITEM,
    [ITEM_RED_CARD] = ITEM_TYPE_HELD_ITEM,
    [ITEM_RING_TARGET] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SHED_SHELL] = ITEM_TYPE_HELD_ITEM,
    [ITEM_SNOWBALL] = ITEM_TYPE_HELD_ITEM,
    [ITEM_STICKY_BARB] = ITEM_TYPE_HELD_ITEM,
    [ITEM_TERRAIN_EXTENDER] = ITEM_TYPE_HELD_ITEM,
    [ITEM_WISE_GLASSES] = ITEM_TYPE_HELD_ITEM,
    [ITEM_ELECTRIC_SEED] = ITEM_TYPE_HELD_ITEM,
    [ITEM_GRASSY_SEED] = ITEM_TYPE_HELD_ITEM,
    [ITEM_MISTY_SEED] = ITEM_TYPE_HELD_ITEM,
    [ITEM_PSYCHIC_SEED] = ITEM_TYPE_HELD_ITEM,
    [ITEM_LIFE_ORB] = ITEM_TYPE_HELD_ITEM,
    [ITEM_TOXIC_ORB] = ITEM_TYPE_HELD_ITEM,
    [ITEM_FLAME_ORB] = ITEM_TYPE_HELD_ITEM,
    [ITEM_BLACK_SLUDGE] = ITEM_TYPE_HELD_ITEM,
    [ITEM_CHOICE_SPECS] = ITEM_TYPE_HELD_ITEM,
    [ITEM_CHOICE_SCARF] = ITEM_TYPE_HELD_ITEM,
    [ITEM_FIST_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_SKY_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_TOXIC_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_EARTH_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_STONE_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_INSECT_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_SPOOKY_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_IRON_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_FLAME_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_SPLASH_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_MEADOW_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_ZAP_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_MIND_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_ICICLE_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_DRACO_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_DREAD_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_PIXIE_PLATE] = ITEM_TYPE_PLATE,
    [ITEM_FIGHTING_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_FLYING_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_POISON_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_GROUND_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_ROCK_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_BUG_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_GHOST_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_STEEL_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_FIRE_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_WATER_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_GRASS_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_ELECTRIC_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_PSYCHIC_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_ICE_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_DRAGON_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_DARK_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_FAIRY_MEMORY] = ITEM_TYPE_MEMORY,
    [ITEM_BURN_DRIVE] = ITEM_TYPE_DRIVE,
    [ITEM_DOUSE_DRIVE] = ITEM_TYPE_DRIVE,
    [ITEM_SHOCK_DRIVE] = ITEM_TYPE_DRIVE,
    [ITEM_CHILL_DRIVE] = ITEM_TYPE_DRIVE,
    [ITEM_NORMAL_GEM] = ITEM_TYPE_GEM,
    [ITEM_FIGHTING_GEM] = ITEM_TYPE_GEM,
    [ITEM_FLYING_GEM] = ITEM_TYPE_GEM,
    [ITEM_POISON_GEM] = ITEM_TYPE_GEM,
    [ITEM_GROUND_GEM] = ITEM_TYPE_GEM,
    [ITEM_ROCK_GEM] = ITEM_TYPE_GEM,
    [ITEM_BUG_GEM] = ITEM_TYPE_GEM,
    [ITEM_GHOST_GEM] = ITEM_TYPE_GEM,
    [ITEM_STEEL_GEM] = ITEM_TYPE_GEM,
    [ITEM_FIRE_GEM] = ITEM_TYPE_GEM,
    [ITEM_WATER_GEM] = ITEM_TYPE_GEM,
    [ITEM_GRASS_GEM] = ITEM_TYPE_GEM,
    [ITEM_ELECTRIC_GEM] = ITEM_TYPE_GEM,
    [ITEM_PSYCHIC_GEM] = ITEM_TYPE_GEM,
    [ITEM_ICE_GEM] = ITEM_TYPE_GEM,
    [ITEM_DRAGON_GEM] = ITEM_TYPE_GEM,
    [ITEM_DARK_GEM] = ITEM_TYPE_GEM,
    [ITEM_FAIRY_GEM] = ITEM_TYPE_GEM,

    [ITEM_SEA_INCENSE] = ITEM_TYPE_INCENSE,
    [ITEM_LAX_INCENSE] = ITEM_TYPE_INCENSE,
    [ITEM_LUCK_INCENSE] = ITEM_TYPE_INCENSE,
    [ITEM_FULL_INCENSE] = ITEM_TYPE_INCENSE,
    [ITEM_ODD_INCENSE] = ITEM_TYPE_INCENSE,
    [ITEM_PURE_INCENSE] = ITEM_TYPE_INCENSE,
    [ITEM_ROCK_INCENSE] = ITEM_TYPE_INCENSE,
    [ITEM_ROSE_INCENSE] = ITEM_TYPE_INCENSE,
    [ITEM_WAVE_INCENSE] = ITEM_TYPE_INCENSE,

    [ITEM_VENUSAURITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_CHARIZARDITE_X] = ITEM_TYPE_MEGA_STONE,
    [ITEM_CHARIZARDITE_Y] = ITEM_TYPE_MEGA_STONE,
    [ITEM_BLASTOISINITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_BEEDRILLITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_PIDGEOTITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_ALAKAZITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_SLOWBRONITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_GENGARITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_KANGASKHANITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_PINSIRITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_GYARADOSITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_AERODACTYLITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_MEWTWONITE_X] = ITEM_TYPE_MEGA_STONE,
    [ITEM_MEWTWONITE_Y] = ITEM_TYPE_MEGA_STONE,
    [ITEM_AMPHAROSITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_STEELIXITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_SCIZORITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_HERACRONITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_HOUNDOOMINITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_TYRANITARITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_SCEPTILITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_BLAZIKENITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_SWAMPERTITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_GARDEVOIRITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_SABLENITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_MAWILITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_AGGRONITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_MEDICHAMITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_MANECTITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_SHARPEDONITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_CAMERUPTITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_ALTARIANITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_BANETTITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_ABSOLITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_GLALITITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_SALAMENCITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_METAGROSSITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_LATIASITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_LATIOSITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_LOPUNNITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_GARCHOMPITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_LUCARIONITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_ABOMASITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_GALLADITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_AUDINITE] = ITEM_TYPE_MEGA_STONE,
    [ITEM_DIANCITE] = ITEM_TYPE_MEGA_STONE,

    [ITEM_RED_ORB] = ITEM_TYPE_MEGA_STONE,
    [ITEM_BLUE_ORB] = ITEM_TYPE_MEGA_STONE,

    [ITEM_BLUE_FLUTE] = ITEM_TYPE_FLUTE,
    [ITEM_YELLOW_FLUTE] = ITEM_TYPE_FLUTE,
    [ITEM_RED_FLUTE] = ITEM_TYPE_FLUTE,
    [ITEM_BLACK_FLUTE] = ITEM_TYPE_FLUTE,
    [ITEM_WHITE_FLUTE] = ITEM_TYPE_FLUTE,

    [ITEM_RED_NECTAR] = ITEM_TYPE_NECTAR,
    [ITEM_YELLOW_NECTAR] = ITEM_TYPE_NECTAR,
    [ITEM_PINK_NECTAR] = ITEM_TYPE_NECTAR,
    [ITEM_PURPLE_NECTAR] = ITEM_TYPE_NECTAR,

    [ITEM_SHOAL_SALT] = ITEM_TYPE_SELLABLE,
    [ITEM_SHOAL_SHELL] = ITEM_TYPE_SELLABLE,
    [ITEM_TINY_MUSHROOM] = ITEM_TYPE_SELLABLE,
    [ITEM_BIG_MUSHROOM] = ITEM_TYPE_SELLABLE,
    [ITEM_PEARL] = ITEM_TYPE_SELLABLE,
    [ITEM_BIG_PEARL] = ITEM_TYPE_SELLABLE,
    [ITEM_STARDUST] = ITEM_TYPE_SELLABLE,
    [ITEM_STAR_PIECE] = ITEM_TYPE_SELLABLE,
    [ITEM_NUGGET] = ITEM_TYPE_SELLABLE,
    
    [ITEM_RARE_BONE] = ITEM_TYPE_SELLABLE,
    
    [ITEM_RED_SHARD] = ITEM_TYPE_SHARD,
    [ITEM_BLUE_SHARD] = ITEM_TYPE_SHARD,
    [ITEM_YELLOW_SHARD] = ITEM_TYPE_SHARD,
    [ITEM_GREEN_SHARD] = ITEM_TYPE_SHARD,

    [ITEM_HELIX_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_DOME_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_OLD_AMBER] = ITEM_TYPE_FOSSIL,
    [ITEM_ROOT_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_CLAW_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_SKULL_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_ARMOR_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_COVER_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_PLUME_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_JAW_FOSSIL] = ITEM_TYPE_FOSSIL,
    [ITEM_SAIL_FOSSIL] = ITEM_TYPE_FOSSIL,

    [ITEM_ORANGE_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_HARBOR_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_GLITTER_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_MECH_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_WOOD_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_WAVE_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_BEAD_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_SHADOW_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_TROPIC_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_DREAM_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_FAB_MAIL] = ITEM_TYPE_MAIL,
    [ITEM_RETRO_MAIL] = ITEM_TYPE_MAIL,
};

static void AddBagSortSubMenu(void)
{
    switch (gBagPositionStruct.pocket + 1)
    {
        case POCKET_KEY_ITEMS:
            gBagMenu->unk820 = sBagMenuSortKeyItems;
            memcpy(&gBagMenu->unk824, &sBagMenuSortKeyItems, NELEMS(sBagMenuSortKeyItems));
            gBagMenu->unk828 = NELEMS(sBagMenuSortKeyItems);
            break;
        case POCKET_POKE_BALLS:
        case POCKET_BERRIES:
        case POCKET_TM_HM:
            gBagMenu->unk820 = sBagMenuSortPokeBallsBerries;
            memcpy(&gBagMenu->unk824, &sBagMenuSortPokeBallsBerries, NELEMS(sBagMenuSortPokeBallsBerries));
            gBagMenu->unk828 = NELEMS(sBagMenuSortPokeBallsBerries);
            break;
        default:
            gBagMenu->unk820 = sBagMenuSortItems;
            memcpy(&gBagMenu->unk824, &sBagMenuSortItems, NELEMS(sBagMenuSortItems));
            gBagMenu->unk828 = NELEMS(sBagMenuSortItems);
            break;
    }

    StringExpandPlaceholders(gStringVar4, sText_SortItemsHow);
    FillWindowPixelBuffer(1, PIXEL_FILL(0));
    BagMenu_Print(1, 1, gStringVar4, 3, 1, 0, 0, 0, 0);

    if (gBagMenu->unk828 == 2)
        sub_81ACAF8(BagMenu_AddWindow(1));
    else if (gBagMenu->unk828 == 4)
        sub_81ACB54(BagMenu_AddWindow(2), 2, 2);
    else
        sub_81ACB54(BagMenu_AddWindow(3), 2, 3);
}

static void Task_LoadBagSortOptions(u8 taskId)
{
    AddBagSortSubMenu();
    gTasks[taskId].func = Task_HandleOutOfBattleItemMenuInput;
}

#define tSortType data[2]
static void ItemMenu_SortByName(u8 taskId)
{
    gTasks[taskId].tSortType = SORT_ALPHABETICALLY;
    StringCopy(gStringVar1, sSortTypeStrings[SORT_ALPHABETICALLY]);
    gTasks[taskId].func = SortBagItems;
}
static void ItemMenu_SortByType(u8 taskId)
{
    gTasks[taskId].tSortType = SORT_BY_TYPE;
    StringCopy(gStringVar1, sSortTypeStrings[SORT_BY_TYPE]);
    gTasks[taskId].func = SortBagItems;
}
static void ItemMenu_SortByAmount(u8 taskId)
{
    gTasks[taskId].tSortType = SORT_BY_AMOUNT; //greatest->least
    StringCopy(gStringVar1, sSortTypeStrings[SORT_BY_AMOUNT]);
    gTasks[taskId].func = SortBagItems;
}

static void SortBagItems(u8 taskId)
{
    s16* data = gTasks[taskId].data;

    BagMenu_RemoveSomeWindow();
    //sItemDescriptionPocket = 0; //Sorting Items
    StringCopy(gStringVar1, sSortTypeStrings[tSortType]);
    StringExpandPlaceholders(gStringVar4, sText_ItemsSorted);
    DisplayItemMessage(taskId, 1, gStringVar4, Task_SortFinish);
}

static void Task_SortFinish(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    u16* scrollPos = &gBagPositionStruct.scrollPosition[gBagPositionStruct.pocket];
    u16* cursorPos = &gBagPositionStruct.cursorPosition[gBagPositionStruct.pocket];

    if (gMain.newKeys & (A_BUTTON | B_BUTTON))
    {
        //BagPrintTextOnWindow(ShowBagWindow(6, 3), 2, gStringVar4, 0, 2, 1, 0, 0, 1);
        SortItemsInBag(gBagPositionStruct.pocket, tSortType);
        bag_menu_RemoveBagItem_message_window(4);
        DestroyListMenuTask(data[0], scrollPos, cursorPos);
        SetInitialScrollAndCursorPositions(gBagPositionStruct.pocket);
        LoadBagItemListBuffers(gBagPositionStruct.pocket);
        data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *scrollPos, *cursorPos);
        schedule_bg_copy_tilemap_to_vram(0);
        set_callback3_to_bag(taskId);
    }
}

static void SortItemsInBag(u8 pocket, u8 type)
{
    struct ItemSlot* itemMem;
    u16 itemAmount;
    s8 (*func)(struct ItemSlot*, struct ItemSlot*);

    switch (pocket)
    {
    case ITEMS_POCKET:
        itemMem = gSaveBlock1Ptr->bagPocket_Items;
        itemAmount = BAG_ITEMS_COUNT;
        break;
    case KEYITEMS_POCKET:
        itemMem = gSaveBlock1Ptr->bagPocket_KeyItems;
        itemAmount = BAG_KEYITEMS_COUNT;
        break;
    case BALLS_POCKET:
        itemMem = gSaveBlock1Ptr->bagPocket_PokeBalls;
        itemAmount = BAG_POKEBALLS_COUNT;
        break;
    case BERRIES_POCKET:
        itemMem = gSaveBlock1Ptr->bagPocket_Berries;
        itemAmount = BAG_BERRIES_COUNT;
        break;
    case TMHM_POCKET:
        itemMem = gSaveBlock1Ptr->bagPocket_TMHM;
        itemAmount = BAG_TMHM_COUNT;
        break;
    default:
        return;
    }

    switch (type)
    {
    case SORT_ALPHABETICALLY:
        MergeSort(itemMem, 0, itemAmount - 1, CompareItemsAlphabetically);
        break;
    case SORT_BY_AMOUNT:
        MergeSort(itemMem, 0, itemAmount - 1, CompareItemsByMost);
        break;
    default:
        MergeSort(itemMem, 0, itemAmount - 1, CompareItemsByType);
        break;
    }
}

static void MergeSort(struct ItemSlot* array, u32 low, u32 high, s8 (*comparator)(struct ItemSlot*, struct ItemSlot*))
{
    u32 mid;

    if (high <= low)
        return;

    mid = low + (high - low) / 2;
    MergeSort(array, low, mid, comparator); //Sort left half.
    MergeSort(array, mid + 1, high, comparator); //Sort right half.
    Merge(array, low, mid, high, comparator); //Merge results.
}

static void Merge(struct ItemSlot* array, u32 low, u32 mid, u32 high, s8 (*comparator)(struct ItemSlot*, struct ItemSlot*))
{
    u32 i = low;
    u32 j = mid + 1;
    u32 k;
    struct ItemSlot aux[high + 1];

    for (k = low; k <= high; ++k)
        aux[k] = array[k];

    for (k = low; k <= high; ++k)
    { //Merge back to a[low..high]
        if (i > mid)
            array[k] = aux[j++];
        else if (j > high)
            array[k] = aux[i++];
        else if (comparator(&aux[j], &aux[i]) < 0)
            array[k] = aux[j++];
        else
            array[k] = aux[i++];
    }
}

static s8 CompareItemsAlphabetically(struct ItemSlot* itemSlot1, struct ItemSlot* itemSlot2)
{
    u16 item1 = itemSlot1->itemId;
    u16 item2 = itemSlot2->itemId;
    int i;
    const u8 *name1;
    const u8 *name2;

    if (item1 == ITEM_NONE)
        return 1;
    else if (item2 == ITEM_NONE)
        return -1;

    name1 = ItemId_GetName(item1);
    name2 = ItemId_GetName(item2);

    for (i = 0; ; ++i)
    {
        if (name1[i] == EOS && name2[i] != EOS)
            return -1;
        else if (name1[i] != EOS && name2[i] == EOS)
            return 1;
        else if (name1[i] == EOS && name2[i] == EOS)
            return 0;

        if (name1[i] < name2[i])
            return -1;
        else if (name1[i] > name2[i])
            return 1;
    }

    return 0; //Will never be reached
}

static s8 CompareItemsByMost(struct ItemSlot* itemSlot1, struct ItemSlot* itemSlot2)
{
    u16 quantity1 = GetBagItemQuantity(&itemSlot1->quantity);
    u16 quantity2 = GetBagItemQuantity(&itemSlot2->quantity);

    if (itemSlot1->itemId == ITEM_NONE)
        return 1;
    else if (itemSlot2->itemId == ITEM_NONE)
        return -1;

    if (quantity1 < quantity2)
        return 1;
    else if (quantity1 > quantity2)
        return -1;

    return CompareItemsAlphabetically(itemSlot1, itemSlot2); //Items have same quantity so sort alphabetically
}

static s8 CompareItemsByType(struct ItemSlot* itemSlot1, struct ItemSlot* itemSlot2)
{
    //Null items go last
    u8 type1 = (itemSlot1->itemId == ITEM_NONE) ? 0xFF : gItemsByType[itemSlot1->itemId];
    u8 type2 = (itemSlot2->itemId == ITEM_NONE) ? 0xFF : gItemsByType[itemSlot2->itemId];

    if (type1 < type2)
        return -1;
    else if (type1 > type2)
        return 1;

    return CompareItemsAlphabetically(itemSlot1, itemSlot2); //Items are of same type so sort alphabetically
}