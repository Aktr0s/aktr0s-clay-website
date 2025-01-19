#define CLAY_EXTEND_CONFIG_RECTANGLE Clay_String link;
#define CLAY_EXTEND_CONFIG_IMAGE Clay_String sourceURL;
#define CLAY_EXTEND_CONFIG_TEXT bool disablePointerEvents;
#define CLAY_IMPLEMENTATION
#include "clay.h"

double windowWidth = 1024, windowHeight = 768;
float modelPageOneZRotation = 0;
uint32_t ACTIVE_RENDERER_INDEX = 0;

const uint32_t FONT_ID_BODY_16 = 0;
const uint32_t FONT_ID_TITLE_56 = 1;
const uint32_t FONT_ID_BODY_24 = 2;
const uint32_t FONT_ID_BODY_36 = 3;
const uint32_t FONT_ID_TITLE_36 = 4;
const uint32_t FONT_ID_MONOSPACE_24 = 5;

const Clay_Color COLOR_LIGHT = (Clay_Color) {244, 235, 230, 255};
const Clay_Color COLOR_LIGHT_HOVER = (Clay_Color) {224, 215, 210, 255};
const Clay_Color COLOR_RED = (Clay_Color) {185,70,67, 255};
const Clay_Color COLOR_RED_HOVER = (Clay_Color) {148, 46, 8, 255};
const Clay_Color COLOR_ORANGE = (Clay_Color) {225, 138, 50, 255};
const Clay_Color COLOR_BLUE = (Clay_Color) {111, 173, 162, 255};

// Colors for top stripe
const Clay_Color COLOR_TOP_BORDER_1 = (Clay_Color) {71, 13, 33, 255};
const Clay_Color COLOR_TOP_BORDER_2 = (Clay_Color) {156, 15, 72, 255};
const Clay_Color COLOR_TOP_BORDER_3 = (Clay_Color) {185,70,67, 255};
const Clay_Color COLOR_TOP_BORDER_4 = (Clay_Color) {214, 125, 62, 255};
const Clay_Color COLOR_TOP_BORDER_5 = (Clay_Color) {232,177,137, 255};


#define RAYLIB_VECTOR2_TO_CLAY_VECTOR2(vector) (Clay_Vector2) { .x = (vector).x, .y = (vector).y }

Clay_TextElementConfig headerTextConfig = (Clay_TextElementConfig) { .fontId = 2, .fontSize = 24, .textColor = {61, 26, 5, 255} };
Clay_TextElementConfig imTextConfig = (Clay_TextElementConfig) { .fontId = 1, .fontSize = 24, .textColor = {61, 26, 5, 255} };

typedef enum {
    MOBILE,
    DESKTOP
} DeviceType;

void LandingPage(DeviceType type){
    if (type == DESKTOP) {
        CLAY(CLAY_ID("LandingPage1Desktop"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(.min = windowHeight - 70) }, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}, .padding = {50,50,0,0} })) {
            CLAY(CLAY_ID("LandingPage1"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) }, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER}, .padding = { 32,32,32, 32 }, .childGap = 32 }), CLAY_BORDER({ .left = { 2, COLOR_RED }, .right = { 2, COLOR_RED } })) {
                CLAY(CLAY_ID("LeftText"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_PERCENT(0.55f) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
                    CLAY_TEXT(CLAY_STRING("Hi! And welcome on my site. I’m a retro tech enthusiast and mainly C++ programmer with uncommon passions."), CLAY_TEXT_CONFIG({ .fontSize = 56, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_RED }));
                    CLAY(CLAY_ID("LandingPageSpacer"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(32) } })) {}
                    CLAY_TEXT(CLAY_STRING("C'mon look down and see!"), CLAY_TEXT_CONFIG({ .fontSize = 36, .fontId = FONT_ID_TITLE_36, .textColor = COLOR_ORANGE }));
                }
                CLAY(CLAY_ID("RightImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.40) }, .childAlignment = {.x = CLAY_ALIGN_X_CENTER} })) {
                    CLAY(CLAY_ID("RightImageInner"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 568) }}), CLAY_IMAGE({ .sourceDimensions = {1080, 1080}, .sourceURL = CLAY_STRING("/images/pfp.png")})) {}
                }
            }
        }
    } else if (type == MOBILE) {
        CLAY(CLAY_ID("LandingPage1Mobile"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(.min = windowHeight - 70) }, .childAlignment = {CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}, .padding = { 16,16,32, 32 }, .childGap = 32 })) {
            CLAY(CLAY_ID("LeftText"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW(0) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
                CLAY_TEXT(CLAY_STRING("Hi! And welcome on my site. I’m a retro tech enthusiast and mainly C++ programmer with uncommon passions."), CLAY_TEXT_CONFIG({ .fontSize = 48, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_RED }));
                CLAY(CLAY_ID("LandingPageSpacer"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(32) } })) {}
                CLAY_TEXT(CLAY_STRING("C'mon look down and see!"), CLAY_TEXT_CONFIG({ .fontSize = 32, .fontId = FONT_ID_TITLE_36, .textColor = COLOR_ORANGE }));
            }
            CLAY(CLAY_ID("RightImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.40) }, .childAlignment = {.x = CLAY_ALIGN_X_CENTER} })) {
                CLAY(CLAY_ID("RightImageInner"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 568) }}), CLAY_IMAGE({ .sourceDimensions = {1080, 1080}, .sourceURL = CLAY_STRING("/images/pfp.png")})) {}
            }
        }
    }
    
}


void WelcomingBlocks(DeviceType type){
    if (type == DESKTOP) {
        CLAY(CLAY_ID("WelcomingBlocksOuter"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0) } })) {
            CLAY(CLAY_ID("WelcomingBlocksInner"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0) }, .childAlignment = { .y = CLAY_ALIGN_Y_CENTER } }), CLAY_BORDER({ .betweenChildren = { .width = 2, .color = COLOR_RED } })) {
                Clay_TextElementConfig *textConfig = CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_BODY_24, .textColor = COLOR_RED });
                CLAY(CLAY_ID("TextBoxOuter"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_PERCENT(0.5f) }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {50,50,32, 32}, .childGap = 8 })) {
                    CLAY(CLAY_ID("TextOuter1"), CLAY_LAYOUT({ .padding = {8,8,4, 4} }), CLAY_RECTANGLE({ .color = COLOR_BLUE, .cornerRadius = CLAY_CORNER_RADIUS(8) })) {
                        CLAY_TEXT(CLAY_STRING("Here, Look!"), CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_BODY_24, .textColor = COLOR_LIGHT }));
                    }
                    CLAY_TEXT(CLAY_STRING("I love retro tech. Old computers, Learning how to switch 1B!ts0 & $Byt3s to make things work."), textConfig);
                    CLAY_TEXT(CLAY_STRING("I also adore Physical Storage Media."), textConfig);
                    CLAY_TEXT(CLAY_STRING("MO Disks, Floppy Disks, CD (Yes, they are considered obsolete :<), Tape Drives. You got it!"), textConfig);
                }
                CLAY(CLAY_ID("AboutGithubOuter"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_PERCENT(0.5f) }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {50,50,32,32}, .childGap = 8 })) {
                    CLAY(CLAY_ID("TextOuter2"), CLAY_LAYOUT({ .padding = {8,8,4, 4} }), CLAY_RECTANGLE({ .color = COLOR_BLUE, .cornerRadius = CLAY_CORNER_RADIUS(8) })) {
                        CLAY_TEXT(CLAY_STRING("About my Projects."), CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_BODY_24, .textColor = COLOR_LIGHT }));
                    }
                    CLAY_TEXT(CLAY_STRING("Below there are some of my lil projects I decided to make public."), textConfig);
                    CLAY_TEXT(CLAY_STRING("Im also not very advanced in programming (at least in my opinion) \nSo please don’t treat my projects as bad, they are just to have fun and learn."), textConfig);
                }
            }
        }
    } else if (type == MOBILE) {
        CLAY(CLAY_ID("WelcomingBlocksInner"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW(0) } }), CLAY_BORDER({ .betweenChildren = { .width = 2, .color = COLOR_RED } })) {
            Clay_TextElementConfig *textConfig = CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_BODY_24, .textColor = COLOR_RED });
            CLAY(CLAY_ID("TextBoxOuter"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW(0) }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {16,16,32, 32}, .childGap = 8 })) {
                CLAY(CLAY_ID("TextOuter"), CLAY_LAYOUT({ .padding = {8,8,4, 4} }), CLAY_RECTANGLE({ .color = COLOR_BLUE, .cornerRadius = CLAY_CORNER_RADIUS(8) })) {
                    CLAY_TEXT(CLAY_STRING("Here, Look!"), CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_BODY_24, .textColor = COLOR_LIGHT }));
                }
                CLAY_TEXT(CLAY_STRING("I love retro tech. Old computers, Learning how to switch 1B!ts0 & $Byt3s to make things work."), textConfig);
                CLAY_TEXT(CLAY_STRING("I also adore Physical Storage Media."), textConfig);
                CLAY_TEXT(CLAY_STRING("MO Disks, Floppy Disks, CD (Yes, they are considered obsolete :<), Tape Drives. You got it!"), textConfig);
            }
            CLAY(CLAY_ID("AboutGithubOuter"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW(0) }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {16, 16, 32, 32}, .childGap = 8 })) {
                CLAY(CLAY_ID("TextOuter2"), CLAY_LAYOUT({ .padding = {8,8,4, 4} }), CLAY_RECTANGLE({ .color = COLOR_BLUE, .cornerRadius = CLAY_CORNER_RADIUS(8) })) {
                    CLAY_TEXT(CLAY_STRING("About my Projects."), CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_BODY_24, .textColor = COLOR_LIGHT }));
                }
                CLAY_TEXT(CLAY_STRING("Below there are some of my lil projects I decided to make public."), textConfig);
                CLAY_TEXT(CLAY_STRING("Im also not very advanced in programming (at least in my opinion) \nSo please don’t treat my projects as bad, they are just to have fun and learn."), textConfig);
            }
        }
    }
}




void DungeonMixPage(DeviceType type) {
    if (type == DESKTOP) {
        CLAY(CLAY_ID("DungeonMixPageDesktop"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIT(.min = windowHeight - 50) }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {50,50,0,0} })) {
            CLAY(CLAY_ID("DungeonPage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) }, .childAlignment = { 0, CLAY_ALIGN_Y_CENTER }, .padding = { 32,32,32, 32 }, .childGap = 32 }), CLAY_BORDER({ .left = { 2, COLOR_RED }, .right = { 2, COLOR_RED } })) {
                CLAY(CLAY_ID("DungeonPageLeftText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.5) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
                    CLAY_TEXT(CLAY_STRING("Dungeon Mix"), CLAY_TEXT_CONFIG({ .fontSize = 52, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_RED }));
                    CLAY(CLAY_ID("DungeonPageSpacer"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 16) } })) {}
                    CLAY_TEXT(CLAY_STRING("Very simple game that i began developing when i started C in my classes."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
                    CLAY_TEXT(CLAY_STRING("The 'Mix' gameplay is focused on imputing two numbers and calculating almost random value inflicted by inputed numbers."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
                    CLAY_TEXT(CLAY_STRING("It has simple save system, as well as money and selling system."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
                    CLAY(CLAY_ID("LinkDungeonOuter"), CLAY_LAYOUT(), CLAY_RECTANGLE({ .link = CLAY_STRING("https://github.com/aktr0s/Dungeon-Mix"), .color = {0,0,0,0} })) {
                        CLAY_TEXT(CLAY_STRING("Click here to check github page."), CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontId = FONT_ID_BODY_24, .fontSize = 24, .textColor = COLOR_ORANGE }));
                    }
                }
                CLAY(CLAY_ID("DungeonPageImageSpacer"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0) } })) {}
                CLAY(CLAY_ID("DungeonPageRightImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.3) }, .childAlignment = {.x = CLAY_ALIGN_X_CENTER} })) {
                    CLAY(CLAY_ID("DungeonPageRightImageInner"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 568) } }), CLAY_IMAGE({ .sourceDimensions = {743, 1456}, .sourceURL = CLAY_STRING("/images/dm.png") })) {}
                }
            }
        }
    } else if (type == MOBILE) {
        CLAY(CLAY_ID("DungeonMixPageMobile"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIT(.min = windowHeight - 50) }, .childAlignment = {CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER}, .padding = {16,16,32, 32}, .childGap = 16 })) {
            CLAY(CLAY_ID("DungeonPageLeftText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
                CLAY_TEXT(CLAY_STRING("Dungeon Mix"), CLAY_TEXT_CONFIG({ .fontSize = 48, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_RED }));
                CLAY(CLAY_ID("DungeonPageSpacer"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 16) } })) {}
                CLAY_TEXT(CLAY_STRING("Very simple game that i began developing when i started C in my classes."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
                CLAY_TEXT(CLAY_STRING("The 'Mix' gameplay is focused on imputing two numbers and calculating almost random value inflicted by inputed numbers."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
                CLAY_TEXT(CLAY_STRING("It has simple save system, as well as money and selling system."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
            }
            CLAY(CLAY_ID("DungeonPageRightImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 200) }, .childAlignment = {.x = CLAY_ALIGN_X_CENTER} })) {
                CLAY(CLAY_ID("DungeonPageRightImageInner"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 568) } }), CLAY_IMAGE({ .sourceDimensions = {743, 1456}, .sourceURL = CLAY_STRING("/images/dm.png") } )) {}
            }
        }
    }
}

void LCNPage(DeviceType type){
    if (type == DESKTOP) {
        CLAY(CLAY_ID("LCNPageDesktop"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIT(.min = windowHeight - 50) }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {50,50,0,0} }),CLAY_RECTANGLE({ .color = COLOR_RED })) {
            CLAY(CLAY_ID("LCNPage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) }, .childAlignment = { 0, CLAY_ALIGN_Y_CENTER }, .padding = { 32,32,32, 32 }, .childGap = 32 }), CLAY_BORDER({ .left = { 2, COLOR_LIGHT }, .right = { 2, COLOR_LIGHT } })) {
                CLAY(CLAY_ID("LCNPageLeftImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.5) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
                        CLAY(CLAY_ID("LCNPageLeftImageInner"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0) } }), CLAY_IMAGE({ .sourceDimensions = {845, 503}, .sourceURL = CLAY_STRING("/images/lcn.png") })) {}
                }
                CLAY(CLAY_ID("LCNPageRightText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.50) },.layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
                    CLAY_TEXT(CLAY_STRING("Lua Console Notepad (LCN)"), CLAY_TEXT_CONFIG({ .fontSize = 52, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_LIGHT }));
                    CLAY(CLAY_ID("LCNSpacer"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 16) } })) {}
                    CLAY_TEXT(CLAY_STRING("This is interesting and started as class assignment to make a notepad in whatever language that runs in terminal."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
                    CLAY_TEXT(CLAY_STRING("I wanted it to be portable and lightweight so it stayed in Lua even though i could use Java or Python"), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
                    CLAY_TEXT(CLAY_STRING("It came out better than i expected. It's very 'Vim' like since you use command line to do stuff."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
                    CLAY_TEXT(CLAY_STRING("It also does not use a single library, everything is written manually (Maybe because there was no library to use :P)"), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
                    CLAY(CLAY_ID("LinkLCNOuter"), CLAY_LAYOUT(), CLAY_RECTANGLE({ .link = CLAY_STRING("https://github.com/aktr0s/LuaConsoleNotepad"), .color = {0,0,0,0} })) {
                        CLAY_TEXT(CLAY_STRING("Click here to check github page."), CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontId = FONT_ID_BODY_24, .fontSize = 24, .textColor = COLOR_ORANGE }));
                    }

                }
            }
        }
    } else if (type == MOBILE) {
        CLAY(CLAY_ID("LCNPageMobile"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIT(.min = windowHeight - 50) }, .childAlignment = {CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER}, .padding = {16,16,32, 32}, .childGap = 16 }),CLAY_RECTANGLE({ .color = COLOR_RED})) {
            CLAY(CLAY_ID("LCNPageLeftText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
                CLAY_TEXT(CLAY_STRING("Lua Console Notepad (LCN)"), CLAY_TEXT_CONFIG({ .fontSize = 48, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_LIGHT }));
                CLAY(CLAY_ID("LCNPageSpacer"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 16) } })) {}
                CLAY_TEXT(CLAY_STRING("This is interesting and started as class assignment to make a notepad in whatever language that runs in terminal."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
                CLAY_TEXT(CLAY_STRING("I wanted it to be portable and lightweight so it stayed in Lua even though i could use Java or Python"), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
                CLAY_TEXT(CLAY_STRING("It came out better than i expected. It's very 'Vim' like since you use command line to do stuff."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
                CLAY_TEXT(CLAY_STRING("It also does not use a single library, everything is written manually (Maybe because there was no library to use :P)"), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_LIGHT }));
            }
            CLAY(CLAY_ID("LCNPageRightImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0) }, .childAlignment = {.x = CLAY_ALIGN_X_CENTER} })) {
                CLAY(CLAY_ID("LCNPageRightImageInner"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 568) } }), CLAY_IMAGE({ .sourceDimensions = {845, 503}, .sourceURL = CLAY_STRING("/images/lcn.png") } )) {}
            }
        }
    }
}

void NixiePage(DeviceType type) {
    if (type == DESKTOP) {
        CLAY(CLAY_ID("NixiePageDesktop"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIT(.min = windowHeight - 50) }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {50,50,0,0} })) {
            CLAY(CLAY_ID("NixiePage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) }, .childAlignment = { 0, CLAY_ALIGN_Y_CENTER }, .padding = { 32,32,32, 32 }, .childGap = 32 }), CLAY_BORDER({ .left = { 2, COLOR_RED }, .right = { 2, COLOR_RED } })) {
                CLAY(CLAY_ID("NixiePageLeftText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.5) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
                    CLAY_TEXT(CLAY_STRING("NixieTextFX"), CLAY_TEXT_CONFIG({ .fontSize = 52, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_RED }));
                    CLAY(CLAY_ID("NixiePageSpacer"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 16) } })) {}
                    CLAY_TEXT(CLAY_STRING("I really wanted to make something object oriented and test SDL2 and was obsessed with Nixie Tubes."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
                    CLAY_TEXT(CLAY_STRING("Thats how i got the idea to make it. It is designed to just add the repo files into your SDL2 project and use it"), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
                    CLAY_TEXT(CLAY_STRING("It has basic control: Position, Size, Flicker (flicker like a light bulb), Clock mode and even more!"), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
                    CLAY_TEXT(CLAY_STRING("There is included documentation generated by Doxygen in the repo."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
                    CLAY(CLAY_ID("LinkNixieOuter"), CLAY_LAYOUT(), CLAY_RECTANGLE({ .link = CLAY_STRING("https://github.com/aktr0s/NixieTextFX"), .color = {0,0,0,0} })) {
                        CLAY_TEXT(CLAY_STRING("Click here to check github page."), CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontId = FONT_ID_BODY_24, .fontSize = 24, .textColor = COLOR_ORANGE }));
                    }
                }
                CLAY(CLAY_ID("NixiePageRightImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_PERCENT(0.5) }, .childAlignment = {.x = CLAY_ALIGN_X_CENTER} })) {
                    CLAY(CLAY_ID("NixiePageRightImageInner"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 568) } }), CLAY_IMAGE({ .sourceDimensions = {921, 392}, .sourceURL = CLAY_STRING("/images/ntf.png") })) {}
                }
            }
        }
    } else if (type == MOBILE) {
        CLAY(CLAY_ID("NixiePageMobile"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIT(.min = windowHeight - 50) }, .childAlignment = {CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER}, .padding = {16,16,32, 32}, .childGap = 16 })) {
            CLAY(CLAY_ID("NixiePageLeftText"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0) }, .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 8 })) {
                CLAY_TEXT(CLAY_STRING("NixieTextFX"), CLAY_TEXT_CONFIG({ .fontSize = 48, .fontId = FONT_ID_TITLE_56, .textColor = COLOR_RED }));
                CLAY(CLAY_ID("NixiePageSpacer"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 16) } })) {}
                CLAY_TEXT(CLAY_STRING("I really wanted to make something object oriented and test SDL2 and was obsessed with Nixie Tubes."), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
                CLAY_TEXT(CLAY_STRING("Thats how i got the idea to make it. It is designed to just add the repo files into your SDL2 project and use it"), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
                CLAY_TEXT(CLAY_STRING("It has basic control: Position, Size, Flicker (flicker like a light bulb), Clock mode and even more!"), CLAY_TEXT_CONFIG({ .fontSize = 28, .fontId = FONT_ID_BODY_36, .textColor = COLOR_RED }));
            }
            CLAY(CLAY_ID("NixiePageRightImage"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 568) }, .childAlignment = {.x = CLAY_ALIGN_X_CENTER} })) {
                CLAY(CLAY_ID("NixiePageRightImageInner"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(.max = 568) } }), CLAY_IMAGE({ .sourceDimensions = {921, 392}, .sourceURL = CLAY_STRING("/images/ntf.png") } )) {}
            }
        }
    }
}


void CreditBlock(DeviceType type){
    if (type == DESKTOP) {
        CLAY(CLAY_ID("CreditBlockOuter"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0) } })) {
            CLAY(CLAY_ID("CreditBlockInner"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0) }, .childAlignment = { .y = CLAY_ALIGN_Y_CENTER } }), CLAY_RECTANGLE({ .color = COLOR_RED })) {
                Clay_TextElementConfig *textConfig = CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_BODY_24, .textColor = COLOR_LIGHT });
                CLAY(CLAY_ID("CreditTextBoxOuter"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {50,50,32, 32}, .childGap = 8 })) {
                    CLAY(CLAY_ID("CreditBlockTextOuter1"), CLAY_LAYOUT({ .padding = {8,8,4, 4} }), CLAY_RECTANGLE({ .color = COLOR_RED_HOVER, .cornerRadius = CLAY_CORNER_RADIUS(8) })) {
                        CLAY_TEXT(CLAY_STRING("Credits"), CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_BODY_24, .textColor = COLOR_LIGHT }));
                    }
                    CLAY_TEXT(CLAY_STRING("This site is HEAVLILY Inspired by Nic Barker Clay Website Example"), textConfig);
                    CLAY(CLAY_ID("LinkCreditWebsiteOuter"), CLAY_LAYOUT(), CLAY_RECTANGLE({ .link = CLAY_STRING("https://github.com/nicbarker/clay/tree/main/examples/clay-official-website"), .color = {0,0,0,0} })) {
                        CLAY_TEXT(CLAY_STRING("Found right here."), CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontId = FONT_ID_BODY_24, .fontSize = 24, .textColor = COLOR_ORANGE }));
                    }
                    CLAY_TEXT(CLAY_STRING("'Aktr0s' name image was generated at www.textstudio.com"), textConfig);
                    CLAY(CLAY_ID("LinkCreditTextImgOuter"), CLAY_LAYOUT(), CLAY_RECTANGLE({ .link = CLAY_STRING("https://www.textstudio.com"), .color = {0,0,0,0} })) {
                        CLAY_TEXT(CLAY_STRING("Found right here."), CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontId = FONT_ID_BODY_24, .fontSize = 24, .textColor = COLOR_ORANGE }));
                    }
                    CLAY_TEXT(CLAY_STRING("If you got any concerns contact me on Twitter (X) at @Acer0sik"), textConfig);
                }
            }
        }
    } else if (type == MOBILE) {
        CLAY(CLAY_ID("CreditBlockInner"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW(0) } }), CLAY_RECTANGLE({ .color = COLOR_RED })) {
            Clay_TextElementConfig *textConfig = CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_BODY_24, .textColor = COLOR_LIGHT });
            CLAY(CLAY_ID("CreditTextBoxOuter"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW(0) }, .childAlignment = {0, CLAY_ALIGN_Y_CENTER}, .padding = {16,16,32, 32}, .childGap = 8 })) {
                CLAY(CLAY_ID("CreditTextOuter"), CLAY_LAYOUT({ .padding = {8,8,4, 4} }), CLAY_RECTANGLE({ .color = COLOR_RED_HOVER, .cornerRadius = CLAY_CORNER_RADIUS(8) })) {
                    CLAY_TEXT(CLAY_STRING("Credits"), CLAY_TEXT_CONFIG({ .fontSize = 24, .fontId = FONT_ID_BODY_24, .textColor = COLOR_LIGHT }));
                }
                CLAY_TEXT(CLAY_STRING("This site is HEAVLILY Inspired by Nic Barker Clay Website Example"), textConfig);
                CLAY(CLAY_ID("LinkCreditWebsiteOuter"), CLAY_LAYOUT(), CLAY_RECTANGLE({ .link = CLAY_STRING("https://github.com/nicbarker/clay/tree/main/examples/clay-official-website"), .color = {0,0,0,0} })) {
                        CLAY_TEXT(CLAY_STRING("Found right here."), CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontId = FONT_ID_BODY_24, .fontSize = 24, .textColor = COLOR_ORANGE }));
                    }
                    CLAY_TEXT(CLAY_STRING("'Aktr0s' name image was generated at www.textstudio.com"), textConfig);
                    CLAY(CLAY_ID("LinkCreditTextImgOuter"), CLAY_LAYOUT(), CLAY_RECTANGLE({ .link = CLAY_STRING("https://www.textstudio.com"), .color = {0,0,0,0} })) {
                        CLAY_TEXT(CLAY_STRING("Found right here."), CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontId = FONT_ID_BODY_24, .fontSize = 24, .textColor = COLOR_ORANGE }));
                    }
                    CLAY_TEXT(CLAY_STRING("If you got any concerns contact me on Twitter (X) at @Acer0sik"), textConfig);
                }
        }
    }
}


Clay_RenderCommandArray CreateLayout(bool mobileScreen) {
    Clay_BeginLayout();
    CLAY(CLAY_ID("OuterContainer"), CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) } }), CLAY_RECTANGLE({ .color = COLOR_LIGHT })) {
        CLAY(CLAY_ID("Header"), CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(50) }, .childAlignment = { 0, CLAY_ALIGN_Y_CENTER }, .childGap = 16, .padding = { 32,32,0,0 } })) {
            CLAY_TEXT(CLAY_STRING("I'm"), &imTextConfig);
            CLAY(CLAY_ID("myName"),CLAY_LAYOUT({ .sizing = {CLAY_SIZING_FIXED(110)} }), CLAY_IMAGE({ .sourceDimensions = {512, 205}, .sourceURL = CLAY_STRING("/images/aktr0s.png") })) {}
            CLAY(CLAY_ID("Spacer"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW(0) } })) {}
            if (!mobileScreen) {
                CLAY(CLAY_LAYOUT({ .padding = {16, 16, 6, 6} }),
                    CLAY_RECTANGLE({ .cornerRadius = CLAY_CORNER_RADIUS(10), .link = CLAY_STRING("https://x.com/Acer0sik"), .color = Clay_Hovered() ? COLOR_LIGHT_HOVER : COLOR_LIGHT }),
                    CLAY_BORDER_OUTSIDE_RADIUS(2, COLOR_BLUE, 10)
                ) {
                    CLAY_TEXT(CLAY_STRING("Twitter"), CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontId = FONT_ID_BODY_24, .fontSize = 24, .textColor = {61, 26, 5, 255} }));
                }
                CLAY(CLAY_LAYOUT({ .padding = {16, 16, 6, 6} }),
                    CLAY_RECTANGLE({ .cornerRadius = CLAY_CORNER_RADIUS(10), .link = CLAY_STRING("https://github.com/nicbarker/clay"), .color = Clay_Hovered() ? COLOR_LIGHT_HOVER : COLOR_LIGHT }),
                    CLAY_BORDER_OUTSIDE_RADIUS(2, COLOR_BLUE, 10)
                ) {
                    CLAY_TEXT(CLAY_STRING("Github"), CLAY_TEXT_CONFIG({ .disablePointerEvents = true, .fontId = FONT_ID_BODY_24, .fontSize = 24, .textColor = {61, 26, 5, 255} }));
                }
            }
        }
        Clay_LayoutConfig topBorderConfig = (Clay_LayoutConfig) { .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(4) }};
        CLAY(CLAY_ID("TopBorder1"), CLAY_LAYOUT(topBorderConfig), CLAY_RECTANGLE({ .color = COLOR_TOP_BORDER_5 })) {}
        CLAY(CLAY_ID("TopBorder2"), CLAY_LAYOUT(topBorderConfig), CLAY_RECTANGLE({ .color = COLOR_TOP_BORDER_4 })) {}
        CLAY(CLAY_ID("TopBorder3"), CLAY_LAYOUT(topBorderConfig), CLAY_RECTANGLE({ .color = COLOR_TOP_BORDER_3 })) {}
        CLAY(CLAY_ID("TopBorder4"), CLAY_LAYOUT(topBorderConfig), CLAY_RECTANGLE({ .color = COLOR_TOP_BORDER_2 })) {}
        CLAY(CLAY_ID("TopBorder5"), CLAY_LAYOUT(topBorderConfig), CLAY_RECTANGLE({ .color = COLOR_TOP_BORDER_1 })) {}
        CLAY(CLAY_ID("OuterScrollContainer"),
            CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) }, .layoutDirection = CLAY_TOP_TO_BOTTOM }),
            CLAY_SCROLL({ .vertical = true }),
            CLAY_BORDER({ .betweenChildren = {2, COLOR_RED} })
        ) {
            if (mobileScreen) {
                LandingPage(MOBILE);
                WelcomingBlocks(MOBILE);
                DungeonMixPage(MOBILE);
                LCNPage(MOBILE);
                NixiePage(MOBILE);
                CreditBlock(MOBILE);
            } else {
                LandingPage(DESKTOP);
                WelcomingBlocks(DESKTOP);
                DungeonMixPage(DESKTOP);
                LCNPage(DESKTOP);
                NixiePage(DESKTOP);
                CreditBlock(DESKTOP);
            }
        }
    }

    return Clay_EndLayout();
}

bool debugModeEnabled = false;

CLAY_WASM_EXPORT("UpdateDrawFrame") Clay_RenderCommandArray UpdateDrawFrame(float width, float height, float mouseWheelX, float mouseWheelY, float mousePositionX, float mousePositionY, bool isTouchDown, bool isMouseDown, bool arrowKeyDownPressedThisFrame, bool arrowKeyUpPressedThisFrame, bool dKeyPressedThisFrame, float deltaTime) {
    windowWidth = width;
    windowHeight = height;
    Clay_SetLayoutDimensions((Clay_Dimensions) { width, height });
    
    Clay_SetCullingEnabled(false);
    Clay_SetExternalScrollHandlingEnabled(true);


    Clay_SetPointerState((Clay_Vector2) {mousePositionX, mousePositionY}, isMouseDown || isTouchDown);

    
    bool isMobileScreen = windowWidth < 750;
    
    return CreateLayout(isMobileScreen);
    //----------------------------------------------------------------------------------
}

