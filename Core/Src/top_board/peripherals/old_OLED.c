#include "old_OLED.h"
#include "ssd1306/bitmap.h"

#include "wheels.h"

///////////////////////////////////////////////////// STRUCTS

static const unsigned char* bitmap_icons[8] = {
  bitmap_icon_3dcube,
  bitmap_icon_battery,
  bitmap_icon_dashboard,
  bitmap_icon_fireworks,
  bitmap_icon_gps_speed,
  bitmap_icon_knob_over_oled,
  bitmap_icon_parksensor,
  bitmap_icon_turbo
};


static char menu_items[NUMBER_OF_MENU_ITEMS][MAX_MENU_NAME_LENGTH] = {
	{"Info"},
	{"Self-Test"},
	{"Sensors"},
	{"Control"},
	{"String5"},
	{"String6"},
	{"String7"},
	{"String8"}
};

uint8_t submenu_item_length[NUMBER_OF_MENU_ITEMS] = {4,4,3,3,3,3,3,3}; //how many sub-menus
static char submenu_items[NUMBER_OF_MENU_ITEMS][NUMBER_OF_SUBMENU_ITEMS][MAX_SUBMENU_NAME_LENGTH] = {
	{"Strings", "Variables", "Nothing", "Also Nothing"},
	{"Test All", "Motors", "Kicker", "Dribbler"},
	{"Test7", "Test8", "Test9"},
	{"Strings", "PID Values", "Test12"},
	{"Test13", "Test14", "Test15"},
	{"Test16", "Test17", "Test18"},
	{"Test19", "Test20", "Test21"},
	{"Test22", "Test23", "Test24"}
};



typedef struct{
	int32_t content;
	char name[MAX_VAR_NAME_LENGTH];
} variable_Elem;

typedef struct{
	uint8_t arraySizes[NUMBER_OF_VARIABLE_PAGES];
	variable_Elem *arrays[NUMBER_OF_VARIABLE_PAGES];
} variable_Array;


typedef struct{
	char name[MAX_STRING_LENGTH];
} string_Elem;

typedef struct{
	uint8_t arraySizes[NUMBER_OF_DATA_PAGES];
	string_Elem *arrays[NUMBER_OF_DATA_PAGES];
} string_Array;

///////////////////////////////////////////////////// VARIABLES

variable_Array variableArray;
string_Array stringArray;
static int8_t menu_selector[4] = {0};
static int8_t current_page = 0;
static uint8_t endOfPage = 0;
static int16_t increment = 0;


///////////////////////////////////////////////////// PRIVATE FUNCTION DECLARATIONS

static void bootScreen();
static void mainMenu(char itemNames[][MAX_MENU_NAME_LENGTH], const unsigned char* bitmaps[], uint8_t length, int8_t *scrollwheel);
static void dataPage(char menuName[], string_Array stringarray, uint8_t submenuid, int8_t *scrollwheel);
static void variablePage(char menuName[], variable_Array variablearray, uint8_t submenuid, int16_t *increment, int8_t *scrollwheel);
static void subMenu(char menuName[], char stringArray[][MAX_STRING_LENGTH], uint8_t length, int8_t *scrollwheel);
static void nothingToSee(char menuName[]);
static void underConstruction();
static void page0();
static void page1();
static void page2();
static void page3();

static void submenu0();
static void submenu1();
static void submenu2();
static void submenu3();
static void submenu4();
static void submenu5();
static void submenu6();
static void submenu7();

static void motorSelfTest();
static inline uint8_t constrain(uint8_t value, uint8_t min, uint8_t max);

static void menu_Update();
static void menu_Select(uint8_t page, uint8_t select0, uint8_t select1, uint8_t select2, uint8_t select3);
static void menu_NextPage();
static void menu_PreviousPage();
static void menu_NextItem();
static void menu_PreviousItem();


///////////////////////////////////////////////////// PUBLIC FUNCTION IMPLEMENTATIONS


Menu_StatusTypeDef menu_Init(){
	for(int i = 0; i< NUMBER_OF_VARIABLE_PAGES; i++){ // initialize to 0
		variableArray.arraySizes[i] = 0;
		variableArray.arrays[i] = NULL;
	}
	for(int i = 0; i< NUMBER_OF_DATA_PAGES; i++){ // initialize to 0
		stringArray.arraySizes[i] = 0;
		stringArray.arrays[i] = NULL;
	}

	menu_Update();

	return MENU_OK;
}


void menu_Loop(){
	if(getButtonState(4)>50){//up
		resetButtonState(4);
		menu_PreviousItem();

	}
	if(getButtonState(2)>50){//down
		resetButtonState(2);
		menu_NextItem();

	}

	if(getButtonState(3)){//ok
		if(getButtonState(3)>500){//long press
			resetButtonState(3);
			menu_PreviousPage();
		}else if(getButtonState(3)>50){//short press
			resetButtonState(3);
			menu_NextPage();
		}

	}

	if(getButtonState(1)){//right
		if(getButtonState(1)>1500){//very very long press
			increment +=1000;
		}else if(getButtonState(1)>800){//very long press
			increment +=100;
		}else if(getButtonState(1)>300){//long press
			increment +=10;
		}else if(getButtonState(1)>50){//short press
			increment +=1;
		}

		resetButtonState(1);
	}

	if(getButtonState(0)){//left

		if(getButtonState(0)>1500){//very very long press
			increment -=1000;
		}else if(getButtonState(0)>800){//very long press
			increment -=100;
		}else if(getButtonState(0)>300){//long press
			increment -=10;
		}else if(getButtonState(0)>50){//short press
			increment -=1;
		}

		resetButtonState(0);
	}

}

Menu_StatusTypeDef menu_SetString(uint8_t item, uint8_t position, char* str){//set the data
	if((item > NUMBER_OF_DATA_PAGES- 1) || position > STRINGS_PER_PAGE){ //if values are out of bound
		return MENU_OUT_OF_BOUND;
	}
	if(stringArray.arraySizes[item] == 0){//if array does not exist, create it
		stringArray.arrays[item] = (string_Elem*)malloc((position+1) * sizeof(string_Elem));
		if(stringArray.arrays[item] == NULL){
			return MENU_MEM_ALLOC_FAILED;
		}
	}
	if(position >= stringArray.arraySizes[item]){//is element does not exist, expand array
		stringArray.arrays[item] = (string_Elem*)realloc(stringArray.arrays[item], (position+1) * sizeof(string_Elem)); //expand array
		if(stringArray.arrays[item] == NULL){
			return MENU_MEM_ALLOC_FAILED; //error
		}
		stringArray.arraySizes[item] = position + 1;
	}

	strcpy(stringArray.arrays[item][position].name, str);
	return MENU_OK;
}

Menu_StatusTypeDef menu_SetVariable(uint8_t item, uint8_t position, int32_t variable){//set the variables
	if(position >= variableArray.arraySizes[item]){
		return MENU_OUT_OF_BOUND; //return if slot does not exist
	}
	variableArray.arrays[item][position].content = variable;
	return MENU_OK;
}


Menu_StatusTypeDef menu_SetVariableName(uint8_t item, uint8_t position, char* variableName){//set variable names
	if((item > NUMBER_OF_VARIABLE_PAGES - 1) || position > VARIABLES_PER_PAGE){ //if values are out of bound
		return MENU_OUT_OF_BOUND;
	}
	if(variableArray.arraySizes[item] == 0){//if array does not exist, create it
		variableArray.arrays[item] = (variable_Elem*)malloc((position+1) * sizeof(variable_Elem));
		if(variableArray.arrays[item] == NULL){
			return MENU_MEM_ALLOC_FAILED;
		}
	}
	if(position >= variableArray.arraySizes[item]){//is element does not exist, expand array
		variableArray.arrays[item] = (variable_Elem*)realloc(variableArray.arrays[item], (position+1) * sizeof(variable_Elem)); //expand array
		if(variableArray.arrays[item] == NULL){
			return MENU_MEM_ALLOC_FAILED; //error
		}
		variableArray.arraySizes[item] = position + 1;
	}

	strcpy(variableArray.arrays[item][position].name, variableName);
	variableArray.arrays[item][position].content = 0;
	return MENU_OK;
}



int32_t menu_GetVariable(uint8_t item, uint8_t position){
	return variableArray.arrays[item][position].content;
}

void menu_DataUpdate(){ //only updates if data is actually visible
	switch(current_page){
		//case 2:
		case 3:
			menu_Update();
			break;
	}
}




///////////////////////////////////////////////////// PRIVATE FUNCTION IMPLEMENTATIONS

void menu_Update(){

	switch(current_page){// item select page
	case 0://logo page
		page0();
		break;

	case 1: //main menu page
		page1();
		break;

	case 2: //sub-menu page
		page2();
		break;

	case 3:
		page3();
		break;
	}


}

static void page0(){
	bootScreen();
}

static void page1(){
	mainMenu(menu_items, bitmap_icons, NUMBER_OF_MENU_ITEMS, &menu_selector[1]);
}

static void page2(){
	switch(menu_selector[1]){
		case 0://info
		case 1://self-test
		case 2://sensors
		case 3://control
		case 4:
		case 5:
		case 6:
		case 7:
			subMenu(menu_items[menu_selector[1]], submenu_items[menu_selector[1]], submenu_item_length[menu_selector[1]], &menu_selector[2]);
			break;

		default:
			menu_PreviousPage();
			break;
	}
}

static void page3(){
	switch(menu_selector[1]){
		case 0://info
			submenu0();
			break;
		case 1://self-test
			submenu1();
			break;
		case 2://sensors
			submenu2();
			break;
		case 3://control
			submenu3();
			break;
		case 4:
			submenu4();
			break;
		case 5:
			submenu5();
			break;
		case 6:
			submenu6();
			break;
		case 7:
			submenu7();
			break;

		default:
			menu_PreviousPage();
			break;
	}
}

static void submenu0(){
	switch(menu_selector[2]){
		case 0:
			dataPage(submenu_items[menu_selector[1]][menu_selector[2]], stringArray, 0, &menu_selector[3]);
			break;
		case 1:
			variablePage(submenu_items[menu_selector[1]][menu_selector[2]], variableArray, 0, &increment, &menu_selector[3]);
			break;
//		case 2:
//			break;
//		case 3:
//			break;

		default:
			underConstruction();
			//Menu_PreviousPage();
			break;
	}
}

static void submenu1(){//self-test
	switch(menu_selector[2]){
		case 0://test all

			break;
		case 1://motors
			motorSelfTest();
			break;
		case 2://kicker
			break;
		case 3://dribbler
			break;
	}
	menu_PreviousPage();
}


static void submenu2(){
	menu_PreviousPage();
}

static void submenu3(){
	switch(menu_selector[2]){
		case 0:

			break;
		case 1:
			break;
//		case 2:
//			break;
//		case 3:
//			break;

		default:
			menu_PreviousPage();
			break;
	}
}

static void submenu4(){
	menu_PreviousPage();
}
static void submenu5(){
	menu_PreviousPage();
}
static void submenu6(){
	menu_PreviousPage();
}
static void submenu7(){
	menu_PreviousPage();
}

static void motorSelfTest(){
	SSD1306_Fill(0);
	SSD1306_GotoXY (0,0);
	SSD1306_Puts ("Motor Test", &Font_11x18, 1);
	SSD1306_GotoXY (0,20);
	SSD1306_Puts ("Ensure the wheels", &Font_7x10, 1);
	SSD1306_GotoXY (0,31);
	SSD1306_Puts ("  are lifted up!", &Font_7x10, 1);
	SSD1306_GotoXY (0,50);
	SSD1306_Puts ("Press OK to start.", &Font_7x10, 1);
	SSD1306_UpdateScreen();
	while(1){
		if(getButtonState(3)){
			resetButtonState(3);
			break;
		}
	}

	SSD1306_Fill(0);
	SSD1306_GotoXY (0,0);
	SSD1306_Puts ("Running Test", &Font_11x18, 1);
	SSD1306_GotoXY (0,20);
	SSD1306_Puts ("Wait until", &Font_7x10, 1);
	SSD1306_GotoXY (0,31);
	SSD1306_Puts ("test is finished.", &Font_7x10, 1);
	SSD1306_GotoXY (0,50);
	SSD1306_Puts (".............", &Font_7x10, 1);
	SSD1306_UpdateScreen();

	uint8_t working[4] = {0};

	for(int motor = 0; motor < 4; motor++){//motors

		HAL_Delay(10);
		if(wheels_DriverPresent(motor) != MOTOR_OK) continue; //check if motor driver is connected
		working[motor]++;//increment if passes test

		encoder_ResetCounter(motor);
		wheels_SetPWM(motor, 100);

		for(int i = 0; i < 50; i++){ // max 0.5 sec long
			if(encoder_GetCounter(motor) > 100){
				working[motor]++;//increment if passes test
				break;
			}
			HAL_Delay(10);
		}
		wheels_SetPWM(motor, 0);

		if(working[motor] != 2) continue;//check if previous test passed

		HAL_Delay(50);

		encoder_ResetCounter(motor);
		wheels_SetPWM(motor, -100);

		for(int i = 0; i < 50; i++){ // max .5 sec long
			if(encoder_GetCounter(motor) < -100){
				working[motor]++;//increment if passes test
				break;
			}
			HAL_Delay(10);
		}
		wheels_SetPWM(motor, 0);
	}

	char tempstr[20];

	SSD1306_Fill(0);
	SSD1306_GotoXY (0,0);
	SSD1306_Puts ("Motor Test", &Font_11x18, 1);
	SSD1306_GotoXY (0,20);
	SSD1306_Puts ("Finished", &Font_7x10, 1);

	sprintf(tempstr, "RF: %u, RB:%u", working[0], working[1]);
	SSD1306_GotoXY (0,31);
	SSD1306_Puts (tempstr, &Font_7x10, 1);

	sprintf(tempstr, "LB:%u, LF:%u", working[2], working[3]);
	SSD1306_GotoXY (0,42);
	SSD1306_Puts (tempstr, &Font_7x10, 1);
	SSD1306_GotoXY (0,55);
	SSD1306_Puts ("Press OK to exit.", &Font_7x10, 1);
	SSD1306_UpdateScreen();
	while(1){
		if(getButtonState(3)){
			resetButtonState(3);
			break;
		}
	}
}

void menu_Select(uint8_t page, uint8_t select0, uint8_t select1, uint8_t select2, uint8_t select3){ //used to manually select a state of the menu
	menu_selector[0]  = (int8_t)select0;
	menu_selector[1]  = (int8_t)select1;
	menu_selector[2]  = (int8_t)select2;
	menu_selector[3]  = (int8_t)select3;
	current_page = page;

	if(current_page < 0) {current_page = 0;};
	if(current_page >= NUMBER_OF_MENU_PAGES) {current_page = NUMBER_OF_MENU_PAGES-1;};
	menu_Update();
}

void menu_NextItem(){
	menu_selector[current_page]++;
	menu_Update();
}

void menu_PreviousItem(){
	menu_selector[current_page]--;
	menu_Update();
}

void menu_NextPage(){
	increment = 0; //set the incrementer to 0 when switching pages
	if(!endOfPage){
		current_page++;
		if(current_page < 0) {current_page = 0;};
		if(current_page >= NUMBER_OF_MENU_PAGES) {current_page = NUMBER_OF_MENU_PAGES-1;};
		menu_Update();
	}
}
void menu_PreviousPage(){
	increment = 0; //set the incrementer to 0 when switching pages
	menu_selector[current_page] = 0; // reset the scrollwheel of the sub menu
	endOfPage = 0; // not end of page anymore
	current_page--;
	if(current_page < 0) {current_page = 0;};
	if(current_page >= NUMBER_OF_MENU_PAGES) {current_page = NUMBER_OF_MENU_PAGES-1;};
	menu_Update();

}

static inline uint8_t constrain(uint8_t value, uint8_t min, uint8_t max) {
    return (value < min) ? min : ((value > max) ? max : value);
}

/* Drawing functions */
static void bootScreen(){
	SSD1306_Fill(0); // first clear the screen before drawing the logo
	SSD1306_DrawBitmap(0, 0, rtt_logo, 128, 64, 1);
	SSD1306_UpdateScreen(); // update screen
}

static void mainMenu(char itemNames[][MAX_MENU_NAME_LENGTH], const unsigned char* bitmaps[], uint8_t length, int8_t *scrollwheel){
	int8_t item_sel_previous;
	int8_t item_sel_next;

	if(*scrollwheel >= length) {*scrollwheel = 0;};
	if(*scrollwheel < 0) {*scrollwheel = length-1;};

	item_sel_previous = *scrollwheel - 1;
	if(item_sel_previous < 0) {item_sel_previous = length-1;};
	item_sel_next = *scrollwheel + 1;
	if(item_sel_next >= length) {item_sel_next = 0;};

	SSD1306_Fill(0);
	SSD1306_GotoXY (26,8);
	SSD1306_Puts (itemNames[item_sel_previous], &Font_7x10, 1); //previous item
	SSD1306_DrawBitmap(4, 2, bitmaps[item_sel_previous], 16, 16, 1);

	SSD1306_GotoXY (26,30);
	SSD1306_Puts (itemNames[menu_selector[1]], &Font_7x10, 1); //current item
	SSD1306_DrawBitmap(4, 24, bitmaps[*scrollwheel], 16, 16, 1);

	SSD1306_GotoXY (26,52);
	SSD1306_Puts (itemNames[item_sel_next], &Font_7x10, 1); //next item
	SSD1306_DrawBitmap(4, 46, bitmaps[item_sel_next], 16, 16, 1);

	SSD1306_DrawBitmap(0, 22, bitmap_item_sel_outline , 128, 21, 1); //selected item background

	SSD1306_DrawBitmap(115, 0, bitmap_scrollbar_background , 8, 64, 1); //scrollbar background
	SSD1306_DrawFilledRectangle(119, 64/length*(*scrollwheel), 3, 64/length, 1); //scrollbar

	SSD1306_UpdateScreen();
}

static void subMenu(char menuName[], char stringArray[][MAX_STRING_LENGTH], uint8_t length, int8_t *scrollwheel){
	int8_t scrollwheel_previous;
	int8_t scrollwheel_next;
	int8_t scrollwheel_2next;

	if(*scrollwheel >= length) {*scrollwheel = 0;};
	if(*scrollwheel < 0) {*scrollwheel = length-1;};

	scrollwheel_previous = *scrollwheel - 1;
	if(scrollwheel_previous < 0) {scrollwheel_previous = length-1;};
	scrollwheel_next = *scrollwheel + 1;
	if(scrollwheel_next >= length) {scrollwheel_next = 0;};
	scrollwheel_2next = scrollwheel_next + 1;
	if(scrollwheel_2next >= length) {scrollwheel_2next = 0;};

	SSD1306_Fill(0);
	SSD1306_GotoXY (0,0);
	SSD1306_Puts (menuName, &Font_11x18, 1);
	SSD1306_GotoXY (0,20);
	SSD1306_Puts (stringArray[scrollwheel_previous], &Font_7x10, 1);
	SSD1306_GotoXY (0,31);

	char tempString[MAX_STRING_LENGTH];
	sprintf(tempString, ">%s<",stringArray[*scrollwheel]);

	SSD1306_Puts (tempString, &Font_7x10, 1);
	SSD1306_GotoXY (0,43);
	SSD1306_Puts (stringArray[scrollwheel_next], &Font_7x10, 1);
	SSD1306_GotoXY (0,53 );
	SSD1306_Puts (stringArray[scrollwheel_2next], &Font_7x10, 1);

	SSD1306_DrawBitmap(115, 0, bitmap_scrollbar_background , 8, 64, 1); //scrollbar background
	SSD1306_DrawFilledRectangle(119, 64/length*(*scrollwheel), 3, 64/length, 1); //scrollbar

	SSD1306_UpdateScreen();
}

static void dataPage(char menuName[], string_Array stringarray, uint8_t submenuid, int8_t *scrollwheel){ //takes strings and displays them
	int8_t scrollwheel_previous;
	int8_t scrollwheel_next;
	int8_t scrollwheel_2next;

	uint8_t length = stringarray.arraySizes[submenuid];
	if(!length) {//if length is 0, return from this function
		nothingToSee(menuName);
		return;
	}

	if(*scrollwheel >= length) {*scrollwheel = 0;};
	if(*scrollwheel < 0) {*scrollwheel = length-1;};

	scrollwheel_previous = *scrollwheel - 1;
	if(scrollwheel_previous < 0) {scrollwheel_previous = length-1;};
	scrollwheel_next = *scrollwheel + 1;
	if(scrollwheel_next >= length) {scrollwheel_next = 0;};
	scrollwheel_2next = scrollwheel_next + 1;
	if(scrollwheel_2next >= length) {scrollwheel_2next = 0;};

	SSD1306_Fill(0);
	SSD1306_GotoXY (0,0);
	SSD1306_Puts (menuName, &Font_11x18, 1);
	SSD1306_GotoXY (0,20);
	SSD1306_Puts (stringarray.arrays[submenuid][scrollwheel_previous].name, &Font_7x10, 1);
	SSD1306_GotoXY (0,31);
	SSD1306_Puts (stringarray.arrays[submenuid][*scrollwheel].name, &Font_7x10, 1);
	SSD1306_GotoXY (0,43);
	SSD1306_Puts (stringarray.arrays[submenuid][scrollwheel_next].name, &Font_7x10, 1);
	SSD1306_GotoXY (0,53 );
	SSD1306_Puts (stringarray.arrays[submenuid][scrollwheel_2next].name, &Font_7x10, 1);

	SSD1306_DrawBitmap(115, 0, bitmap_scrollbar_background , 8, 64, 1); //scrollbar background
	SSD1306_DrawFilledRectangle(119, 64/length*(*scrollwheel), 3, 64/length, 1); //scrollbar

	SSD1306_UpdateScreen();
	endOfPage = 1;
}

static void variablePage(char menuName[], variable_Array variablearray, uint8_t submenuid, int16_t *increment, int8_t *scrollwheel){ //takes variables together with their names(strings) and displays them
	int8_t scrollwheel_previous;
	int8_t scrollwheel_next;
	int8_t scrollwheel_2next;

	uint8_t length = variablearray.arraySizes[submenuid];
	if(!length) {//if length is 0, return from this function
		nothingToSee(menuName);
		return;
	}

	if(*scrollwheel >= length) {*scrollwheel = 0;};
	if(*scrollwheel < 0) {*scrollwheel = length-1;};

	scrollwheel_previous = *scrollwheel - 1;
	if(scrollwheel_previous < 0) {scrollwheel_previous = length-1;};
	scrollwheel_next = *scrollwheel + 1;
	if(scrollwheel_next >= length) {scrollwheel_next = 0;};
	scrollwheel_2next = scrollwheel_next + 1;
	if(scrollwheel_2next >= length) {scrollwheel_2next = 0;};

	variablearray.arrays[submenuid][*scrollwheel].content += *increment; //increment variable by the value of "increment" can be negative

	*increment = 0;

	char tempString[4][MAX_STRING_LENGTH];

	sprintf(tempString[0], "%s:%ld", 		variablearray.arrays[submenuid][scrollwheel_previous].name, 	variablearray.arrays[submenuid][scrollwheel_previous].content);
	sprintf(tempString[1], "%s:%ld <==", 	variablearray.arrays[submenuid][*scrollwheel].name, 			variablearray.arrays[submenuid][*scrollwheel].content);
	sprintf(tempString[2], "%s:%ld", 		variablearray.arrays[submenuid][scrollwheel_next].name, 		variablearray.arrays[submenuid][scrollwheel_next].content);
	sprintf(tempString[3], "%s:%ld", 		variablearray.arrays[submenuid][scrollwheel_2next].name, 		variablearray.arrays[submenuid][scrollwheel_2next].content);


	SSD1306_Fill(0);
	SSD1306_GotoXY (0,0);
	SSD1306_Puts (menuName, &Font_11x18, 1);
	SSD1306_GotoXY (0,20);
	SSD1306_Puts (tempString[0], &Font_7x10, 1);
	SSD1306_GotoXY (0,31);
	SSD1306_Puts (tempString[1], &Font_7x10, 1);
	SSD1306_GotoXY (0,43);
	SSD1306_Puts (tempString[2], &Font_7x10, 1);
	SSD1306_GotoXY (0,53 );
	SSD1306_Puts (tempString[3], &Font_7x10, 1);

	SSD1306_DrawBitmap(115, 0, bitmap_scrollbar_background , 8, 64, 1); //scrollbar background
	SSD1306_DrawFilledRectangle(119, 64/length*(*scrollwheel), 3, 64/length, 1); //scrollbar

	SSD1306_UpdateScreen();
	endOfPage = 1;
}

static void nothingToSee(char menuName[]){
	SSD1306_Fill(0);
	SSD1306_GotoXY (0,0);
	SSD1306_Puts (menuName, &Font_11x18, 1);
	SSD1306_GotoXY (0,20);
	SSD1306_Puts ("Nothing to see...", &Font_7x10, 1);
	SSD1306_GotoXY (0,31);
	SSD1306_Puts ("No, really,", &Font_7x10, 1);
	SSD1306_GotoXY (0,43);
	SSD1306_Puts ("This page is empty", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

static void underConstruction(){
	SSD1306_Fill(0);
	SSD1306_GotoXY (0,0);
	SSD1306_Puts ("The page is under", &Font_7x10, 1);
	SSD1306_GotoXY (0,10);
	SSD1306_Puts ("construction.", &Font_7x10, 1);
	SSD1306_GotoXY (0,20);

	SSD1306_Puts ("Here is a", &Font_7x10, 1);
	SSD1306_GotoXY (0,31);
	SSD1306_Puts ("Penguin,", &Font_7x10, 1);
	SSD1306_GotoXY (0,43);
	SSD1306_Puts ("to keep you", &Font_7x10, 1);
	SSD1306_GotoXY (0,53);
	SSD1306_Puts ("company.", &Font_7x10, 1);

	SSD1306_DrawBitmap(80, 8, penguin, 48, 56, 1);
	SSD1306_UpdateScreen();

}



